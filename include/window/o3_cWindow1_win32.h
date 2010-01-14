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
#ifndef O3_C_WINDOW1_WIN32_H
#define O3_C_WINDOW1_WIN32_H

#include <shared/o3_tools_win32.h>

namespace o3 {

struct cWindow1 : cWindow1Base, iWindow, iWindowProc
{
    static const BYTE     CTRL = 1; 
	static const BYTE     ALT  = 2;  
	static const BYTE     SHIFT = 4; 
	static const BYTE     ESC  = 8;    

    cWindow1()
        : m_hwnd(0), m_icon_s(NULL), m_icon_l(NULL), m_color(0), m_done(false)
    {}

    cWindow1(HWND hwnd, bool chained = false)
        : m_hwnd(hwnd), m_icon_s(NULL), m_icon_l(NULL), m_done(false), m_color(0)
    {
        if (chained)
        {
            // if the hwnd already use the windowlong parameter
            // to point to an iWindowProc object with the message
            // handler function, we can store that pointer.
            // With other words we chain the wndProc functions,
            // first cWindow1::wndProc will be called then if
            // there was an original wndProc function for this hwnd
            // and the message was not handled, it will be 
            // propogated to the other (original) wndProc.

            iWindowProc *wnd_proc = ((iWindowProc*)GetWindowLongPtr( hwnd, GWL_USERDATA ));
            if (wnd_proc)
                m_prev_proc = wnd_proc;

            SetWindowLongPtr( hwnd, GWL_USERDATA, (LONG_PTR) siWindowProc(this).ptr());
        }
    }

    virtual ~cWindow1()
    {

        if (m_icon_s) {
            ::DestroyIcon(m_icon_s);   
            m_icon_s = NULL;
        }    
        if (m_icon_l) {
            ::DestroyIcon(m_icon_l);   
            m_icon_l = NULL;
        }    

        if (m_hwnd) {
            DestroyWindow(m_hwnd);
            m_hwnd = 0;
        }
    }

    o3_begin_class(cWindow1Base)
        o3_add_iface(iWindow)
        o3_add_iface(iWindowProc)
    o3_end_class()

    siWindowProc           m_prev_proc;
    HICON               m_icon_s;
    HICON               m_icon_l;
    HWND                m_hwnd;
    siScr               m_onclose;
    siScr               m_onend;
    siWeak              m_ctx;
    int                 m_color;
    bool                m_done;

    #include "o3_cWindow1_win32_scr.h" 

    // TODO: get rid of this ASAP:

    o3_ext("cO3") o3_get static siWindow window(iCtx* ctx)
    {
        Var v = ctx->value("appWindow");
        siWindow ret = v.toScr();
        if (ret)
            return ret;

        HWND hwnd = (HWND) siCtx1(ctx)->appWindow();
        if (!hwnd)
            return ret;

        ret = o3_new(cWindow1)(hwnd);
        v = ret;
        ctx->setValue("appWindow", v);
        return ret;
    }

    o3_ext("cO3") o3_fun static siWindow createWindow(iUnk*, const char* caption, int x, int y, 
        int width, int height, int style = 0)
    {            
        return create(0, caption, x, y, width, height, style);
    }

    o3_fun siWindow createWindow(const char* caption, int x, int y, 
        int width, int height, int style = 0)
    {
        return create(m_hwnd, caption, x, y, width, height, style);
    }

    static siWindow create(HWND parent, const char* caption, int x, int y, 
        int width, int height, int style = 0)
    {
        // register o3 default window class, if needed
        WNDCLASSW wnd_class;        
        regWndClass(wnd_class);

        // convert o3 style flags to native flags
        DWORD flags = getFlags(style);
        if (parent)
            flags |= WS_CHILD;

        // create the object and the window
        cWindow1* ret = o3_new(cWindow1)();
        ret->m_hwnd = CreateWindowExW(0,o3_wnd_class_name, 
            WStr(caption).ptr(), flags, x, y, width, height, 
            parent, 0, GetModuleHandle(0), (LPVOID)(iWindowProc*)ret);  
        
        return ret;
    }

    static DWORD getFlags(int)
    {
        // TODO: implement
        DWORD flags = WS_SYSMENU | WS_TABSTOP | WS_EX_CONTROLPARENT | WS_VISIBLE; 
        return flags;
    }

     virtual int x()
    {
        RECT r;
        ::GetWindowRect(m_hwnd, &r);
        return r.left;
    }

     virtual int y()
    {
        RECT r;
        ::GetWindowRect(m_hwnd, &r);
        return r.top;    
    }

    o3_get virtual int clientX()
    {
        RECT w,c;
        ::GetWindowRect(m_hwnd,&w);
        ::GetClientRect(m_hwnd,&c);
        int bdr = ((w.right-w.left)-c.right)/2;
        return (w.right - w.left) - c.right - bdr;            
    }

    o3_get virtual int clientY()
    {
        RECT w,c;
        ::GetWindowRect(m_hwnd,&w);
        ::GetClientRect(m_hwnd,&c);
        int bdr = ((w.right-w.left)-c.right)/2;
        return (w.bottom - w.top) -c.bottom - bdr;    
    }
                    
     virtual int height()
    {
        RECT r;
        ::GetWindowRect(m_hwnd, &r);
        return r.bottom - r.top;        
    }

     virtual int width()
    {
        RECT r;
        ::GetWindowRect(m_hwnd, &r);
        return r.right - r.left;            
    }

     virtual int setX(int x) 
    {
        RECT r;
        ::GetWindowRect(m_hwnd, &r);
        ::MoveWindow ( m_hwnd, x, r.top, r.right - r.left, r.bottom - r.top, TRUE);
        return this->x();
    }
    
     virtual int setY(int y) 
    {
        RECT r;
        ::GetWindowRect(m_hwnd, &r);
        ::MoveWindow( m_hwnd, r.left, y, r.right - r.left, r.bottom - r.top, TRUE);
        return this->y();    
    }

     virtual int setHeight(int h) 
    {
        RECT r;
        ::GetWindowRect(m_hwnd, &r);
        ::MoveWindow( m_hwnd, r.left, r.top, r.right - r.left, h, TRUE);
        return height();    
    }

     virtual int setWidth(int w) 
    {
        RECT r;
        ::GetWindowRect(m_hwnd, &r);
        ::MoveWindow( m_hwnd, r.left, r.top, w, r.bottom - r.top, TRUE);
        return width();        
    }

    o3_fun virtual void minimize()
    {
        ::ShowWindow(m_hwnd, SW_MINIMIZE);
    }

    o3_fun virtual void maximize() 
    {
        ::ShowWindow(m_hwnd, SW_MAXIMIZE);
    }

    o3_fun virtual void restore() 
    {
        ::ShowWindow(m_hwnd, SW_RESTORE);
    }

    o3_fun virtual void close() 
    {
        ::PostMessage(m_hwnd,WM_CLOSE,0,0);
    }

    o3_set virtual bool setVisible(bool visible)     
    {
        ::ShowWindow(m_hwnd, visible ? SW_SHOW : SW_HIDE);
        ::UpdateWindow(m_hwnd);
        return visible;
    }

    o3_get virtual bool showButtons()
    {
        return true;        
    }

    o3_set virtual bool setShowButtons(bool show) 
    {        
        LONG style = ::GetWindowLong(m_hwnd, GWL_STYLE);        
        
        if ( (style & WS_SYSMENU) && !show)
            style -= WS_SYSMENU;

        if ( !(style & WS_SYSMENU) && show)
            style += WS_SYSMENU;

        ::SetWindowLong(m_hwnd, GWL_STYLE, style);
        ::SetWindowPos(m_hwnd,HWND_NOTOPMOST,0,0,0,0,
            SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE);
        return show;
    }

    o3_get virtual Str caption() 
    {
        WStr caption;
        caption.reserve(4096);
        ::GetWindowTextW(m_hwnd, caption.ptr(), 4096);
        caption.resize(strLen(caption.ptr()));
        return caption;
    }

    o3_set virtual Str setCaption(const Str& caption_string) 
    {      
        ::SetWindowTextA(m_hwnd, caption_string.ptr());
        ::InvalidateRect(m_hwnd,0,TRUE);
        return caption_string;
    }

    o3_set virtual void setIcon(const Str& name_of_icon) 
    {
        // get the icon from the rsc
        Buf icon = ((cSys*) g_sys)->resource(name_of_icon);
        if (icon.empty())
            return; // some error report should be here...

        // use the buf as icon
        useIcon(icon);
    }

    o3_fun virtual Str open()
    {
        return openFileDialog(m_hwnd);
    }

    o3_fun virtual void useIcon(const Buf& icon_data)
    {
        if (m_icon_s) {
            ::DestroyIcon(m_icon_s);
            m_icon_s = NULL;
        }

        if (m_icon_l) {
            ::DestroyIcon(m_icon_l);
            m_icon_l = NULL;
        }

        // get the default small icon size on the curretn system
        int def_x_s = ::GetSystemMetrics(SM_CXSMICON);
        int def_y_s = ::GetSystemMetrics(SM_CYSMICON);
        int def_x_l = ::GetSystemMetrics(SM_CXICON);
        int def_y_l = ::GetSystemMetrics(SM_CYICON);

        // select the best icon from the icon lib data
        int offset_s = ::LookupIconIdFromDirectoryEx((PBYTE)icon_data.ptr(), 
            TRUE, def_x_s, def_y_s, LR_DEFAULTCOLOR);     

        int offset_l = ::LookupIconIdFromDirectoryEx((PBYTE)icon_data.ptr(), 
            TRUE, def_x_l, def_y_l, LR_DEFAULTCOLOR);     

        if (offset_s != 0) {     

            // create the icon
            // NOTE: you might wonder what is that 0x30000 so here is the doc:
            // MSDN: " Specifies the version number of the icon or cursor format 
            // for the resource bits pointed to by the pbIconBits parameter. 
            // This parameter can be 0x00030000. "  !!!
            // I hope that now you're just as happy as me when I read this... anyway:
            m_icon_s = ::CreateIconFromResourceEx((PBYTE)icon_data.ptr() + offset_s, 0, 
                TRUE, 0x30000, def_x_s, def_y_s, LR_DEFAULTCOLOR);     
        }

        if (offset_l != 0) {
            m_icon_l = ::CreateIconFromResourceEx((PBYTE)icon_data.ptr() + offset_l, 0, 
                TRUE, 0x30000, def_x_l, def_y_l, LR_DEFAULTCOLOR);             
        }

        ::SendMessageW(m_hwnd,WM_SETICON,ICON_SMALL,(LPARAM)m_icon_s);
        ::SendMessageW(m_hwnd,WM_SETICON,ICON_BIG,(LPARAM)m_icon_l);
    }

    virtual void* handle()
    {
        return m_hwnd;
    }

    virtual LRESULT CALLBACK wndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
            // if a button is clicked cButton1 object probably need to do a callback
            // let's resend the message so the cButton1 object can handle it
            case WM_COMMAND:
                if(IsWindow((HWND)lParam))SendMessage( (HWND) lParam, WM_COMMAND, wParam, lParam); 
                break;

	        case WM_DESTROY:
	        {
		        PostQuitMessage(0);
		        return(TRUE);
	        }

            case WM_CLOSE: {
                // if there is an onclose cb set, we call it and based on its return
                // value we interrupt or not the close process ("for are you sure you 
                // want to close?" kind of validation...)
                siCtx ctx(m_ctx);
                if (!ctx)
                    break;

                if (m_onclose) {
                    Var ret(g_sys);                     
                    int id = m_onclose->resolve(ctx,"__self__",false);
                    m_onclose->invoke(ctx, ACCESS_CALL, id, 0, 0, &ret);
                    // if the cb returns true lets send the signal to end the modal 
                    if (ret.toBool()) 
                        Delegate(ctx, m_onend)(this);
                }
                else 
                    Delegate(ctx, m_onend)(this);                
                
                m_hwnd = 0;
                break;
            }

            case WM_CTLCOLORSTATIC:{
                    if (!IsWindow((HWND)lParam))
                        return DefWindowProc(hwnd, uMsg, wParam, lParam);
                     
                    iWindowProc* wnd_proc = 
                        ((iWindowProc*)GetWindowLongPtr( (HWND)lParam, GWL_USERDATA ));                       
                    
                    if (!wnd_proc)
                        return DefWindowProc(hwnd, uMsg, wParam, lParam);

                    cWindow1* wnd = (cWindow1*) wnd_proc; 
                    SetBkMode((HDC)wParam,TRANSPARENT);
                    if (wnd->m_color == 1)
                        return (LRESULT)GetSysColorBrush(COLOR_BTNFACE);
                    return (LRESULT)GetStockObject( wnd->m_color );
                    }
        }
        if (m_prev_proc)
            return m_prev_proc->wndProc(hwnd, uMsg, wParam, lParam);

        return(DefWindowProc(hwnd, uMsg, wParam, lParam));
    }

    static void sendKeyUp(BYTE VKey) 
    {
        BYTE ScanCode = LOBYTE(::MapVirtualKey(VKey, 0));
        keyboardEvent(VKey, ScanCode, KEYEVENTF_KEYUP);
    }

    static void sendKeyDown(BYTE VKey, bool GenUpMsg) 
    {
        BYTE ScanCode = 0;
        // Get scancode
        ScanCode = LOBYTE(::MapVirtualKey(VKey, 0));

        keyboardEvent(VKey, ScanCode, 0);
        if (GenUpMsg)
          keyboardEvent(VKey, ScanCode, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP);
    }

    static void keyboardEvent(BYTE VKey, BYTE ScanCode, LONG Flags) 
    {
        keybd_event(VKey, ScanCode, Flags, 0);      
    }

    o3_fun bool focus() 
    {
      if (m_hwnd == NULL)
        return false;

      ::SendMessage(m_hwnd, WM_SYSCOMMAND, SC_HOTKEY, (LPARAM) m_hwnd);
      ::SendMessage(m_hwnd, WM_SYSCOMMAND, SC_RESTORE, (LPARAM) m_hwnd);
      
      ::ShowWindow(m_hwnd, SW_SHOW);
      ::SetForegroundWindow(m_hwnd);
      ::SetFocus(m_hwnd);

      return true;
    }

    static void sendKey(BYTE VKey, BYTE flags) 
    {           
        if (flags&SHIFT) sendKeyDown(VK_SHIFT, false);
        if (flags&CTRL) sendKeyDown(VK_CONTROL, false);
        if (flags&ALT) sendKeyDown(VK_MENU, false);
        if (flags&ESC) sendKeyDown(VK_ESCAPE, false);
        sendKeyDown(VKey, true);
        if (flags&SHIFT) sendKeyUp(VK_SHIFT);
        if (flags&CTRL) sendKeyUp(VK_CONTROL);
        if (flags&ALT) sendKeyUp(VK_MENU);
        if (flags&ESC) sendKeyUp(VK_ESCAPE);
    }

    // sending key event, the virtual key events sent out will be handled by the window
    // in focus
    o3_ext("cO3") o3_fun static void sendKeyEvent(const char* keys) 
    {           				        
        const char* d = keys; 
		BYTE buf_new[256];
        BYTE flags = 0;

		while (*d)
		{			            
            while (*d && *d == '[') {
                const char* d2 = d+1;
                if (strEquals(d2,"ALT") && d2[3] == ']') {
                    flags|=ALT;
                    d = d2 + 4;
                } else if (strEquals(d2,"CTRL") && d2[4] == ']') {
                    flags|=CTRL;
                    d = d2 + 5;
                } else if (strEquals(d2,"ESC") && d2[3] == ']') {
                    flags|=ESC;
                    d = d2 + 4;
                } else if (strEquals(d2,"SHIFT") && d2[5] == ']') {
                    flags|=SHIFT;
                    d = d2 + 6;
                } else 
                    break;
            }			

			int32_t vkey = VkKeyScanW( *d );
			int32_t scan = MapVirtualKey( vkey&0xff,0 );
			if( vkey & 0x100 ) flags |= SHIFT;

			// DWORD wparm = vkey&0xff;
			DWORD lparm = (scan<<16)+1;

            buf_new[VK_SHIFT] = (flags&SHIFT) ? 0x80 : 0x0;					
            buf_new[VK_CONTROL] = (flags&CTRL) ? 0x80 : 0x0;					
            buf_new[VK_MENU] = (flags&ALT) ? 0x80 : 0x0; 
            if (flags&ALT)
                lparm|=0x20000000;


            sendKey((BYTE) vkey, flags);
			flags = 0;
			
			d++; 
		}
    }

    o3_ext("cO3") o3_fun static void mouseTo(int x, int y, iWindow* wnd = 0)
    {        
        // db_assert(x>=0 && y>=0);
        static DWORD cx = GetSystemMetrics(SM_CXSCREEN);
        static DWORD cy = GetSystemMetrics(SM_CYSCREEN);

        double dx(0),dy(0);
        if (wnd) {
            dx = 65535 * (double) (wnd->x()) / (double) cx;
            dy = 65535 * (double) (wnd->y()) / (double) cy;
        }

        double X = 65535 * (double) x / (double) cx;
        double Y = 65535 * (double) y / (double) cy;
        mouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE,
            (DWORD) (X + dx),(DWORD) (Y + dy), 0, 0);
    }

    o3_ext("cO3") o3_fun static void mouseLeftClick()
    {
        mouse_event( MOUSEEVENTF_LEFTDOWN,0,0,0,0);
        mouse_event( MOUSEEVENTF_LEFTUP,0,0,0,0);
    }

    o3_ext("cO3") o3_fun static void mouseRightClick()
    {
        mouse_event( MOUSEEVENTF_RIGHTDOWN,0,0,0,0);
        mouse_event( MOUSEEVENTF_RIGHTUP,0,0,0,0);
    }

    // installer related:

    o3_ext("cO3") o3_fun static int alertBox(const char* caption, const char* message, const char* mode=0, siEx* ex=0) 
    {
        WStr wcaption = Str(caption);
        WStr wmessage = Str(message);

        if (!mode || !strLen(mode)) {
            int ret = MessageBoxW(
                NULL,
                wmessage,
                wcaption,
                MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2
            );
            return (ret == IDYES ? 1 : 0); 
        }else if (strEquals(mode, "retrycancel")) {
            int ret = MessageBoxW(
                NULL,
                wmessage,
                wcaption,
                MB_ICONWARNING | MB_RETRYCANCEL | MB_DEFBUTTON2
            );
            return (ret == IDRETRY ? 1 : 0); 
        }else{
            o3_set_ex (ex_invalid_value);
            return -1;
        }
    }

    o3_fun void destroy()
    {
        if (m_hwnd) {
                DestroyWindow(m_hwnd);
            m_hwnd = 0;            
        }
    }

    o3_set siScr setOnclose(iCtx *ctx, iScr* onclose) 
    {
        m_ctx = ctx;
        return m_onclose =  onclose;
    }

    o3_set siScr setOnend(iCtx *ctx, iScr* onend) 
    {
        m_ctx = ctx;
        return m_onend =  onend;
    }
};

}

#endif // O3_C_WINDOW1_WIN32_H
