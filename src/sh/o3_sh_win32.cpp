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

#include <core/o3_core.h>
#include <js/o3_js.h>
//#include <test/o3_proto_v1.h>
#include "xml/o3_xml.h"
//#include "socket/o3_socket.h"
#include "fs/o3_fs.h"
#include "blob/o3_blob.h"
#include "console/o3_console.h"
#include "http/o3_http.h"
#include "process/o3_process.h"
#include "protocol/o3_protocol.h"
#include "resource/o3_resource.h"
#include "screen/o3_screen.h"
#include "window/o3_window.h"
#include "tools/o3_tools.h"
#include "process/o3_process.h"
#include "test/o3_test.h" 
//#include "canvas/o3_cCanvas1_win32.h"


//int WINAPI WinMain(HINSTANCE hi, HINSTANCE hp, LPSTR arg, int show){
int main(int argc, char **argv) {

    using namespace o3;  

    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED); 

    cSys sys;

    siMgr mgr = o3_new(cMgr)();
    siCtx ctx = o3_new(cJs1)(mgr, --argc, ++argv);
   
    
    //mgr->addExtTraits(cCanvas1::extTraits());
    mgr->addExtTraits(cFs1::extTraits());
    mgr->addExtTraits(cHttp1::extTraits());
    mgr->addExtTraits(cBlob1::extTraits());
    mgr->addExtTraits(cConsole1::extTraits());
    mgr->addExtTraits(cXml1::extTraits());
    //mgr->addExtTraits(cJs1::extTraits());
    //js.mgr()->addExtTraits(cSocket1::extTraits());
    mgr->addExtTraits(cResource1::extTraits());
    mgr->addExtTraits(cResourceBuilder1::extTraits());
    mgr->addExtTraits(cScreen1::extTraits());
	mgr->addExtTraits(cProcess1::extTraits());
	mgr->addExtTraits(cTest1::extTraits());

    //WSADATA wsd;
    //int rc = WSAStartup(MAKEWORD(2,2), &wsd);

    bool wait = true;
    int ret = 0;
    {// scope the local vars        
        for(int i = 0; i < argc;i++){
            if(strEquals(argv[i],"-w")) wait = true;
        }
                
        FILE* in;
        if (argc<1)
            return -1;

        // TODO: since this file is windows only, this fopen should be replaced by createFile
        in = fopen( argv[0] , "r");
        if (!in)
            return -2;                                

        const ::size_t DATA_SIZE = 1;
        char data[DATA_SIZE];
        ::size_t size;
        
        Str script;
        while (!feof(in)) {
            size = fread(data, sizeof(char), DATA_SIZE, in);
            if (ferror(in)){                  
                return -3;
            }

            script.append(data, size);
        }

        //EVAL SCRIPT
        Var rval;
        rval = ctx->eval(script);
        
        Str err = rval.toStr();
        //fprintf(stdout, "%s", err.ptr()); 
        siCtx1(ctx)->tear();
    }
    
    CoUninitialize(); 

    // if(wait)
	// getc(stdin);

    //WSACleanup();
    return ret;
}  

