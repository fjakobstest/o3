/*
 * Copyright (C) 2010 Javeline BV
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this library; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#ifndef O3_C_PROCESS1_WIN32_H
#define O3_C_PROCESS1_WIN32_H

#include <shared/o3_tools_win32.h>

namespace o3{

    struct cProcess1 : cScr {

        cProcess1()
            : m_stdin_r(0)
            , m_stdin_w(0)
            , m_stdout_r(0)
            , m_stdout_w(0)
            , m_dead(m_dead) 
            , m_outcode(0) 
        {
            m_p_info.hProcess = 0;            
        }

        virtual ~cProcess1() 
        {
        }

        o3_begin_class(cScr)
        o3_end_class();

        HANDLE                  m_stdin_r; 
        HANDLE                  m_stdin_w; 
        HANDLE                  m_stdout_r; 
        HANDLE                  m_stdout_w;
        OVERLAPPED              m_overlapped;
        siEvent                 m_readevent;
        siHandle                m_hprocess;
        PROCESS_INFORMATION     m_p_info;
        DWORD                   m_av;
        siScr                   m_onreceive;
        siScr                   m_ondeath;
        siWeak                  m_ctx;
        siListener              m_r_listener;
        siListener              m_e_listener;
        o3_get_imm() Str        m_output;
        o3_get_imm() Str        m_name;
        char                    m_first;
        o3_get_imm() bool       m_dead;
        o3_get_imm() int        m_outcode;

        #include "o3_cProcess1_win32_scr.h"

        o3_fun int run(iCtx* ctx, const char* app) 
        {
            WStr wapp = Str(app);
            m_ctx = ctx;
            return run(ctx, wapp, 0); 
        }

        o3_fun int runSelf(iCtx* ctx)
        {
            m_ctx = ctx;
            DWORD error = run(ctx, getSelfPath(), 0);
            return ((int)error);    
        }

        o3_fun void runSelfElevated(iCtx* ctx) 
        {
            m_ctx = ctx;
            if (!runElevated( ctx, getSelfPath().ptr() ))
                return;
        }

        o3_fun void runSimple(const char* cmd) 
        {
            WStr wcmd = Str(cmd);
            runSimple(wcmd);
        }

        o3_get bool valid() 
        {
            return m_hprocess ? true : false;
        }

        o3_get int pid() 
        {
            return (int) m_p_info.dwProcessId;
        }

        o3_set void setOndeath(iCtx* ctx, iScr* cb) 
        {
            m_ctx = ctx;
            m_ondeath = cb;
        }

        o3_set void setOnreceive(iCtx* ctx, iScr* cb) 
        {
            m_ctx = ctx;
            m_onreceive = cb;
        }

        o3_fun Str receive(iCtx* ctx, int timeout = 0) 
        {            
            ctx->loop()->wait( timeout );
            if (!m_onreceive) {
                Str ret = m_output;                
                m_output.clear();
                return ret;
            }
            return Str();
        }

        o3_fun void send(const char* input, size_t size)
        {
            unsigned long bread;
            WaitForInputIdle( m_p_info.hProcess, 1000);
            WriteFile(m_stdin_w,input,(DWORD)size,&bread,NULL); 
        }
        
        o3_fun void kill() 
        {
            if(m_hprocess){
                TerminateProcess((HANDLE)m_hprocess->handle(), 0 );
                closeHandles();
                m_hprocess = 0;
                m_p_info.hProcess = 0;
                m_p_info.hThread = 0;
                m_output.clear();
            }            
        }

        o3_ext("cO3") o3_fun static siScr createProcess(const char* name = 0, int pid = 0) 
        {
            cProcess1* ret = o3_new(cProcess1)() ;
            ret->m_p_info.dwProcessId = (DWORD) pid;
            ret->m_name = name;
            if(pid) {
                ret->m_p_info.hProcess = OpenProcess(SYNCHRONIZE|PROCESS_TERMINATE, FALSE,pid);
                ret->m_hprocess = o3_new(cHandle)(ret->m_p_info.hProcess);
            }
            return ret;
        }

        DWORD run(iCtx* ctx, const wchar_t* app, const wchar_t* currdir=0) 
        {
            STARTUPINFOW si;
            SECURITY_ATTRIBUTES sa;
            SECURITY_DESCRIPTOR sd;
            OSVERSIONINFO osv;
            osv.dwOSVersionInfoSize = sizeof(osv);
            GetVersionEx(&osv);
            // DWORD retval = 0;
            if (osv.dwPlatformId == VER_PLATFORM_WIN32_NT) {
                //initialize security descriptor (Windows NT)
                InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
                SetSecurityDescriptorDacl(&sd, true, NULL, false);
                sa.lpSecurityDescriptor = &sd;
            }
            else sa.lpSecurityDescriptor = NULL;
            sa.nLength = sizeof(SECURITY_ATTRIBUTES);
            //allow inheritable handles
            sa.bInheritHandle = TRUE;         
            
            HANDLE hSaveStdout = NULL;
            HANDLE hSaveStdin = NULL;

            hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE);
            //create stdout pipe
            if (!createPipeEx(&m_stdout_r,&m_stdout_w,&sa,0,FILE_FLAG_OVERLAPPED,0)) {
                closeHandles();
                return (DWORD) -1;
            }

            if( !SetStdHandle(STD_OUTPUT_HANDLE, m_stdout_w) ) {
                closeHandles();
                return (DWORD) -1;
            }

            HANDLE stdout_rddup;
            if( ! DuplicateHandle(    GetCurrentProcess(), 
                                    m_stdout_r,
                                    GetCurrentProcess(),
                                    &stdout_rddup,
                                    0,
                                    FALSE,
                                    DUPLICATE_SAME_ACCESS ) ) {
                closeHandles();
                return (DWORD) -1;
            }

            CloseHandle( m_stdout_r );m_stdout_r = stdout_rddup;

            //Save the handle to the current STDOUT.
            hSaveStdin = GetStdHandle(STD_INPUT_HANDLE);

            if (!createPipeEx(&m_stdin_r,&m_stdin_w,&sa,0,FILE_FLAG_OVERLAPPED,0))
                return (DWORD) -1;

            if( !SetStdHandle(STD_INPUT_HANDLE, m_stdin_r) ) {
                closeHandles();
                return (DWORD) -1;
            }
            HANDLE stdin_wrdup;
            //Duplicate the write handle to the pipe so it is not inherited.
            if( ! DuplicateHandle(  GetCurrentProcess(),
                                    m_stdin_w,
                                    GetCurrentProcess(),
                                    &stdin_wrdup,
                                    0,
                                    FALSE,
                                    DUPLICATE_SAME_ACCESS )) {
                closeHandles();
                return (DWORD) -1;
            }
            CloseHandle( m_stdin_w );m_stdin_w = stdin_wrdup;

            ZeroMemory( &si, sizeof(STARTUPINFO) );
            si.cb = sizeof(STARTUPINFO);  

            //The dwFlags member tells CreateProcess how to make the process.
            //STARTF_USESTDHANDLES validates the hStd* members. STARTF_USESHOWWINDOW
            //validates the wShowWindow member.

            si.dwFlags = STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_SHOWDEFAULT;//showflags;
            //set the new handles for the child process
            si.hStdOutput    = m_stdout_w;
            si.hStdError    = m_stdout_w;     
            si.hStdInput    = m_stdin_r;
 
            //spawn the child process
            WStr cmd = app;
            if ( ! CreateProcessW(  NULL,cmd.ptr(),
                                    NULL,
                                    NULL,
                                    TRUE,
                                    CREATE_NO_WINDOW,
                                    NULL,
                                    currdir,
                                    &si,
                                    &m_p_info ) ) {
                closeHandles();
                return (DWORD) -1;
            }
       
            m_readevent = g_sys->createEvent();
            ZeroMemory( &m_overlapped, sizeof(OVERLAPPED) );
            m_overlapped.hEvent = m_readevent;
            m_output.reserve(1);               
            ReadFile(m_stdout_r, &m_first, 1,&m_av,&m_overlapped);
            // int e = GetLastError();

            m_r_listener = ctx->loop()->createListener(m_readevent.ptr(),0,
                    Delegate(this, &cProcess1::onReceive));
            m_hprocess = o3_new(cHandle)(m_p_info.hProcess);
            m_e_listener = ctx->loop()->createListener(m_hprocess.ptr(), 0, 
                    Delegate(this, &cProcess1::onDeath));

            SetStdHandle(STD_INPUT_HANDLE, hSaveStdin);
            SetStdHandle(STD_OUTPUT_HANDLE, hSaveStdout);
         
            return m_p_info.dwProcessId;
        }

        bool runElevated( iCtx* ctx, const wchar_t* path, const wchar_t* parameters = NULL, const wchar_t* dir = NULL ) 
        {
            m_name = path;

            SHELLEXECUTEINFOW shex;

            memset( &shex, 0, sizeof( shex) );

            shex.cbSize        = sizeof( SHELLEXECUTEINFOW );
            shex.fMask        = SEE_MASK_NOCLOSEPROCESS;
            shex.hwnd        = 0;
            shex.lpVerb        = L"runas";
            shex.lpFile        = path;
            shex.lpParameters  = parameters;
            shex.lpDirectory    = dir;
            shex.nShow        = SW_NORMAL;

            ::ShellExecuteExW( &shex );
            m_p_info.hProcess = shex.hProcess;
            // DWORD e = GetLastError();

            if (m_p_info.hProcess )
                m_hprocess = o3_new(cHandle)(m_p_info.hProcess);
                m_e_listener = ctx->loop()->createListener(m_hprocess.ptr(), 0, 
                        Delegate(this, &cProcess1::onDeath));

            m_p_info.dwProcessId = (DWORD) -1;
            //TODO: procefss ID? 
            return (int)shex.hInstApp > 32;
        } 

        void runSimple(wchar_t* cmd) 
        {
            STARTUPINFOW si;
            PROCESS_INFORMATION pi;

            ZeroMemory( &si, sizeof(si) );
            si.cb = sizeof(si);
            ZeroMemory( &pi, sizeof(pi) );

            // Start the child process. 
            CreateProcessW( NULL,   // No module name (use command line)
                cmd,        // Command line
                NULL,           // Process handle not inheritable
                NULL,           // Thread handle not inheritable
                FALSE,          // Set handle inheritance to FALSE
                0,              // No creation flags
                NULL,           // Use parent's environment block
                NULL,           // Use parent's starting directory 
                &si,            // Pointer to STARTUPINFO structure
                &pi );           // Pointer to PROCESS_INFORMATION structure

            //m_p_info = pi;
        }

        void closeHandles() 
        {
            if (m_stdin_r)  CloseHandle(m_stdin_r);
            if (m_stdin_w)  CloseHandle(m_stdin_w);
            if (m_stdout_r) CloseHandle(m_stdout_r);
            if (m_stdout_w) CloseHandle(m_stdout_w);
            
            m_stdin_r = 0;m_stdin_w = 0;m_stdout_r = 0;m_stdout_w = 0;
        }

        bool readResult() 
        {
            // unsigned long exit=0;  //process exit code
            unsigned long bread;   //bytes read
            unsigned long avail;   //bytes available

            size_t oldsize = m_output.size();
            m_output.reserve(oldsize+1); m_output.ptr()[oldsize] = m_first; m_output.resize(oldsize+1);            
            PeekNamedPipe(m_stdout_r,0,0,0,&avail,NULL);
            if (avail != 0) {
                m_output.reserve(oldsize + avail+1);                
                ReadFile(m_stdout_r, m_output.ptr() + oldsize + 1, avail,&bread,NULL);
                m_output.resize(oldsize + bread + 1);
                ZeroMemory( &m_overlapped, sizeof(OVERLAPPED) );
                ResetEvent(m_readevent);                
                m_overlapped.hEvent = m_readevent;
                ReadFile(m_stdout_r, &m_first, 1,&m_av,&m_overlapped);
            }
            return true;            
        }

        void onReceive(iUnk*)
        {
            readResult();
                     
            //casting it to strong ref first, then checking, then do the callback
            if (m_onreceive) {
                //onreceive->invoke(iScr::INVOKE_TYPE_CALL, 0, 0, 0, 0, g_sys);
                Delegate(siCtx(m_ctx), m_onreceive)(this);
                m_output.clear();
            }
        }

        void onDeath(iUnk*) 
        {
            DWORD outcode;
            int32_t ret = GetExitCodeProcess(m_hprocess->handle(),&outcode); 
            m_outcode = (int) outcode;

            if (!ret || m_outcode != STILL_ACTIVE) {
                m_dead = m_outcode < 0;
                m_r_listener = 0;
                m_e_listener = 0;
                m_p_info.hProcess = 0;
                m_hprocess = 0;
                // DWORD error = GetLastError();                                       
            }     

            if (m_ondeath)
                Delegate(siCtx(m_ctx), m_ondeath)(this);

        }

        // NOTE: These functions are only here to that the process component
        // will compile against the current base. We will have to decide later
        // on a common interface for the component on each platform.
        siStream in()
        {
            return 0; // TODO: Implement
        }

        siStream setIn(iStream* in)
        {
            return in;; // TODO: Implement
        }

        siStream out()
        {
            return 0; // TODO: Implement
        }

        siStream setOut(iStream* out)
        {
            return out; // TODO: Implement
        }

        siStream err()
        {
            return 0; // TODO: Implement
        }

        siStream setErr(iStream* err)
        {
            return err; // TODO: Implement
        }

        void exec(const char* args)
        {
            // TODO: Implement
            args;
        }
    };

}

#endif // O3_C_PROCESS1_WIN32_H