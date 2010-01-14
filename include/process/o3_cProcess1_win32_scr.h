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
#ifndef O3_C_PROCESS1_WIN32_SCR_H
#define O3_C_PROCESS1_WIN32_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cProcess1",    0,                  0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_GET,    "cProcess1",    "output",           clsInvoke,  0,  0                   },
            {   1,  Trait::TYPE_GET,    "cProcess1",    "name",             clsInvoke,  1,  0                   },
            {   2,  Trait::TYPE_GET,    "cProcess1",    "dead",             clsInvoke,  2,  0                   },
            {   3,  Trait::TYPE_GET,    "cProcess1",    "outcode",          clsInvoke,  3,  0                   },
            {   4,  Trait::TYPE_FUN,    "cProcess1",    "run",              clsInvoke,  4,  0                   },
            {   5,  Trait::TYPE_FUN,    "cProcess1",    "runSelf",          clsInvoke,  5,  0,                  },
            {   6,  Trait::TYPE_FUN,    "cProcess1",    "runSelfElevated",  clsInvoke,  6,  0                   },
            {   7,  Trait::TYPE_FUN,    "cProcess1",    "runSimple",        clsInvoke,  7,  0                   },
            {   8,  Trait::TYPE_GET,    "cProcess1",    "valid",            clsInvoke,  8,  0                   },
            {   9,  Trait::TYPE_GET,    "cProcess1",    "pid",              clsInvoke,  9,  0                   },
            {   10, Trait::TYPE_SET,    "cProcess1",    "ondeath",          clsInvoke,  10, 0                   },
            {   11, Trait::TYPE_SET,    "cProcess1",    "onreceive",        clsInvoke,  11, 0                   },
            {   12, Trait::TYPE_FUN,    "cProcess1",    "receive",          clsInvoke,  12, 0                   },
            {   13, Trait::TYPE_FUN,    "cProcess1",    "send",             clsInvoke,  13, 0                   },
            {   14, Trait::TYPE_FUN,    "cProcess1",    "kill",             clsInvoke,  14, 0                   }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cProcess1",    0,          0,          0,  0   },
            {   0,  Trait::TYPE_FUN,    "cO3",          "createProcess",  extInvoke,  0,  0   },
            {   0,  Trait::TYPE_END,    "cProcess1",    0,          0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cProcess1* pthis1 = (cProcess1*) pthis;

        switch (index) {
        case 0:
            *rval = pthis1->m_output;
            break;
        case 1:
            *rval = pthis1->m_name;
            break;
        case 2:
            *rval = pthis1->m_dead;
            break;
        case 3:
            *rval = pthis1->m_outcode;
            break;
        case 4:
            *rval = pthis1->run(ctx, argv[0].toStr());
            break;
        case 5:
            *rval = pthis1->runSelf(ctx);
            break;
        case 6:
            pthis1->runSelfElevated(ctx);
            break;
        case 7:
            pthis1->runSimple(argv[0].toStr());
            break;
        case 8:
            *rval = pthis1->valid();
            break;
        case 9:
            *rval = pthis1->pid();
            break;
        case 10:
            pthis1->setOndeath(ctx, argv[0].toScr());
            break;
        case 11:
            pthis1->setOnreceive(ctx, argv[0].toScr());
            break;
        case 12:
            if (argc > 0)
                *rval = pthis1->receive(ctx, argv[0].toInt());
            else
                *rval = pthis1->receive(ctx);
            break;
        case 13:
            pthis1->send(argv[0].toStr(), (size_t) argv[1].toInt());
            break;
        case 14:
            pthis1->kill();
            break;
        }
        return 0;
    }

    static siEx extInvoke(iScr*, iCtx*, int index, int argc,
                          const Var* argv, Var* rval)
    {
        switch (index) {
        case 0:
            if (argc > 1)
                *rval = createProcess(argv[0].toStr(), argv[1].toInt());
            else if (argc > 0)
                *rval = createProcess(argv[0].toStr());
            else
                *rval = createProcess();
            break;
        }
        return 0;
    }

#endif // O3_C_PROCESS1_WIN32_SCR_H
