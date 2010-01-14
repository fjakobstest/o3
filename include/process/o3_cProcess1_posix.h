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
#ifndef O3_C_PROCESS1_POSIX_H
#define O3_C_PROCESS1_POSIX_H

#include <stdio.h>
#include <unistd.h>

namespace o3 {

struct cProcess1 : cProcess1Base {
    Str m_name;
    siStream m_in;
    siStream m_out;
    siStream m_err;

    cProcess1(const char* name) : m_name(name)
    {
        m_in = o3_new(cStream)(stdin);
        m_out = o3_new(cStream)(stdout);
        m_err = o3_new(cStream)(stderr);
    }

    o3_begin_class(cProcess1Base)
    o3_end_class()

#include "o3_cProcess1_posix_scr.h"

    static o3_fun o3_ext("cO3") siScr process(const char* name)
    {
        o3_trace3 trace;

        return o3_new(cProcess1)(name);
    }

    siStream in()
    {
        return m_in;
    }

    siStream setIn(iStream* in)
    {
        return m_in = in;
    }

    siStream out()
    {
        return m_out;
    }

    siStream setOut(iStream* out)
    {
        return m_out = out;
    }

    siStream err()
    {
        return m_err;
    }

    siStream setErr(iStream* err)
    {
        return m_err = err;
    }

    void exec(const char* args)
    {
        tVec<Str> argv;
        tVec<char*> argv1;

        argv1.push(m_name);
        if (args) {
            Str args1 = args;
            char* start;
            char* end;

            start = args1.ptr();
            while (chrIsSpace(*start))
                ++start; 
            end = start;
            while (*end) {
                if (chrIsSpace(*end)) {
                    *end = 0;
                    argv.push(start);
                    start = end + 1;
                    while (chrIsSpace(*start))
                        ++start; 
                    end = start;
                } else
                    ++end;
            }
            argv.push(start);
            for (size_t i = 0; i < argv.size(); ++i)
                argv1.push(argv[i].ptr());
        }
        argv1.push(0);
        if (fork() == 0) {
            execvp(m_name.ptr(), argv1.ptr());
        }
    }
};

}

#endif // O3_C_PROCESS1_POSIX_H
