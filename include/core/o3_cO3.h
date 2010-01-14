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
#ifndef O3_C_O3_H
#define O3_C_O3_H

namespace o3 {

struct cO3 : cScr {
    tVec<Str> m_args;

    cO3(int argc, char** argv)
    {
        while (argc--)
            m_args.push(*argv++);
    }

    ~cO3()
    {
    }

    o3_begin_class(cScr)
    o3_end_class()

#include "o3_cO3_scr.h"

    o3_get tVec<Str> args()
    {
        return m_args;
    }

    o3_fun bool loadModule(iCtx* ctx, const char* name) 
    {
        o3_trace3 trace;

        return ctx->mgr()->loadModule(name);
    }

    o3_fun void wait(iCtx* ctx, int timeout = -1)
    {
        o3_trace3 trace;

        ctx->loop()->wait(timeout);
    }

    o3_fun void exit(int status = 0)
    {
        o3_trace3 trace;

        ::exit(status);
    }

    o3_get Str versionInfo()
    {
        o3_trace3 trace;

        return "v1.0";    
    }

};

}

#endif // O3_C_O3_H
