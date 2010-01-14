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
#ifndef O3_C_PROCESS1_BASE_SCR_H
#define O3_C_PROCESS1_BASE_SCR_H

    virtual Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = { 
            {   0,  Trait::TYPE_BEGIN,  "cProcess1Base",    0,          0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_GET,    "cProcess1Base",    "in",       clsInvoke,  0,  0                   },
            {   0,  Trait::TYPE_SET,    "cProcess1Base",    "in",       clsInvoke,  1,  0                   },
            {   1,  Trait::TYPE_GET,    "cProcess1Base",    "out",      clsInvoke,  2,  0                   },
            {   1,  Trait::TYPE_SET,    "cProcess1Base",    "out",      clsInvoke,  3,  0                   },
            {   2,  Trait::TYPE_GET,    "cProcess1Base",    "out",      clsInvoke,  4,  0                   },
            {   2,  Trait::TYPE_SET,    "cProcess1Base",    "out",      clsInvoke,  5,  0                   },
            {   3,  Trait::TYPE_FUN,    "cProcess1Base",    "exec",     clsInvoke,  6,  0                   },
            {   0,  Trait::TYPE_END,    "cProcess1Base",    0,          0,          0,  0                   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx*, int index, int,
                          const Var* argv, Var* rval)
    {
        cProcess1Base* pthis1 = (cProcess1Base*) pthis;

        switch (index) {
        case 0:
            *rval = pthis1->in();
            break;
        case 1:
            *rval = pthis1->setIn(siStream(argv[0].toScr()));
            break;
        case 2:
            *rval = pthis1->out();
            break;
        case 3:
            *rval = pthis1->setOut(siStream(argv[0].toScr()));
            break;
        case 4:
            *rval = pthis1->err();
            break;
        case 5:
            *rval = pthis1->setErr(siStream(argv[0].toScr()));
            break;
        case 6:
            pthis1->exec(argv[0].toStr());
            break;
        }
        return 0;
    }

#endif // O3_C_PROCESS1_BASE_SCR_H
