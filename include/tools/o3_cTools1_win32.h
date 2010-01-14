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
#ifndef O3_C_TOOLS1_WIN32_H
#define O3_C_TOOLS1_WIN32_H

#include <shared/o3_tools_win32.h>

namespace o3 {

struct cTools1 : cScr{
    cTools1(){}
    virtual ~cTools1(){}

    o3_begin_class(cScr)
    o3_end_class()

    typedef void (WINAPI *REGSVRCUST)(bool, wchar_t*);
    typedef void (WINAPI *UNREGSVRCUST)(bool);

    #include "o3_cTools1_win32_scr.h"

    static Var getProperty(iCtx* ctx, iScr* obj, const char* prop_name)
    {
        if (!obj || !ctx)
            return Var(Var::TYPE_VOID);

        Var ret;
        int scr_id = obj->resolve(ctx, prop_name, false);
        obj->invoke(ctx, ACCESS_GET, scr_id, 0, 0, &ret);
        return ret;
    }

    o3_ext("cO3")
    o3_get static Str tempPath()
    {
        Str ret = tmpPath();            
        backslash2slash(ret);
        return Str(ret);
    }

    o3_ext("cO3")
    o3_get static Str selfPath() 
    {
        Str ret = getSelfPath();
        backslash2slash(ret);
        return Str(ret);
    }

    o3_ext("cO3")
    o3_fun static bool checkIfInstalled(const Str& app)
    {
        WStr app_name(app);
        return o3::checkIfInstalled(app_name);
    }

    o3_ext("cO3")
    o3_fun static bool regDll(const Str& name, bool all_usr)
    {
        //Var rval(g_sys);  
        //getProperty(scr_iscr(0),rval,"name");
        WStr wpath(name);
        HMODULE hModule = LoadLibraryW(wpath.ptr());            
	    REGSVRCUST lpProc = (REGSVRCUST) GetProcAddress(hModule, "DllRegisterServerCust");
        if(lpProc) 
            lpProc(all_usr, wpath.ptr()); 
        else return false;
        FreeLibrary(hModule);
        return true;
    }

    o3_ext("cO3")
    o3_fun static bool unregDll(const Str& name, bool all_usr)
    {
        //WStr wpath(name);
        HMODULE hModule = LoadLibraryA(name.ptr());            
	    UNREGSVRCUST lpProc = (UNREGSVRCUST) GetProcAddress(hModule, "DllUnregisterServerCust");
        if(lpProc) 
            lpProc(all_usr);             
        else return false;
	    FreeLibrary(hModule);
        return true;     
    }

    o3_ext("cO3")
    o3_fun static bool regUninstaller(iCtx* ctx, bool all_usr, iScr* iobj) 
    {
        siScr obj(iobj);
        if (!obj)
            return false;

        WStr name = getProperty(ctx,obj,"name").toWStr();
        WStr exe = getProperty(ctx,obj,"exe").toWStr();
        WStr args = getProperty(ctx,obj,"args").toWStr(); 
        WStr icon = getProperty(ctx,obj,"icon").toWStr();
        WStr path = getProperty(ctx,obj,"path").toWStr();
        WStr dispname = getProperty(ctx,obj,"displayname").toWStr();
        WStr helplink = getProperty(ctx,obj,"helplink").toWStr();
        WStr publisher = getProperty(ctx,obj,"publisher").toWStr(); 
        WStr major = getProperty(ctx,obj,"major").toWStr();
        WStr minor = getProperty(ctx,obj,"minor").toWStr();    

        return uninstallerEntryAdd( all_usr, name, exe, args, icon, path, dispname, 
            helplink, publisher, major, minor );
    }

    o3_ext("cO3")
    o3_fun static bool unregUninstaller(bool all_usr, const Str& name) 
    {         
        WStr wname = WStr(name);
        return uninstallerEntryRemove(all_usr, wname);
    }

    o3_ext("cO3")
    o3_fun static Str getUninstPath(const Str& name) 
    {
        WStr wname = WStr(name);
        return uninstallerPath(wname);    
    }

    o3_ext("cO3")
    o3_fun static bool regMozillaPlugin(iCtx* ctx, bool all_usr, iScr* iobj) 
    {
        siScr obj(iobj);
        if (!obj)
            return false;

        Var rval(g_sys);
        WStr company = getProperty(ctx,obj,"company").toWStr();
        WStr appname = getProperty(ctx,obj,"appname").toWStr();
        WStr version = getProperty(ctx,obj,"version").toWStr();
        WStr path = getProperty(ctx,obj,"path").toWStr();
        WStr product = getProperty(ctx,obj,"product").toWStr();
        WStr description = getProperty(ctx,obj,"description").toWStr();
        WStr mimetype = getProperty(ctx,obj,"mimetype").toWStr();

        return mozillaEntryAdd(all_usr, company, appname, version, path,
            product, description, mimetype );
    }

    o3_ext("cO3")
    o3_fun static bool unregMozillaPlugin(bool all_usr, const Str& company, 
        const Str& app, const Str& version) 
    {
        return mozillaEntryRemove(all_usr, WStr(company), WStr(app), WStr(version));            
    }

    o3_ext("cO3")
    o3_get static bool adminUser() 
    {
        return (TRUE==IsUserAnAdmin());
    }

    o3_ext("cO3")
    o3_get static int winVersionMajor()
    {

        OSVERSIONINFO osvi;

        ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

        GetVersionEx(&osvi);
        return (int)osvi.dwMajorVersion;
    } 
        
    };
}

#endif // O3_C_TOOLS1_WIN32_H