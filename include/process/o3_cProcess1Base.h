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
#ifndef O3_C_PROCESS1_BASE_H
#define O3_C_PROCESS1_BASE_H

namespace o3 {

o3_cls(cProcess1Base);

struct cProcess1Base : cScr {
    siCtx m_ctx;
    siScr m_onterminate;

    o3_begin_class(cScr)
    o3_end_class()

#include "o3_cProcess1Base_scr.h"

    virtual o3_get siStream stdin() = 0;

    virtual o3_get siStream setStdin(iStream* in) = 0;

    virtual o3_get siStream stdout() = 0;

    virtual o3_get siStream setStdout(iStream* out) = 0;

    virtual o3_get siStream stderr() = 0;

    virtual o3_get siStream setStderr(iStream* err) = 0;

    virtual o3_get siScr onterminate()
    {
        return m_onterminate;
    }

    virtual o3_set siScr setOnterminate(iCtx* ctx, iScr* onterminate)
    {
        m_ctx = ctx;
        if (m_onterminate = onterminate)
            startListening();
        else
            stopListening();
        return m_onterminate;
    }

    virtual o3_fun void exec(const char* args) = 0;

    virtual o3_get int exitStatus() = 0;

    virtual void startListening() = 0;

    virtual void stopListening() = 0;
};

}

#endif // O3_C_PROCESS1_BASE_H
