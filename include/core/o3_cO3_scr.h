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
#ifndef O3_C_O3_SCR_H
#define O3_C_O3_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cO3",  0,              0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_GET,    "cO3",  "args",         clsInvoke,  0,  0                   },
            {   1,  Trait::TYPE_FUN,    "cO3",  "loadModule",   clsInvoke,  1,  0                   },
            {   2,  Trait::TYPE_FUN,    "cO3",  "wait",         clsInvoke,  2,  0                   },
            {   3,  Trait::TYPE_FUN,    "cO3",  "exit",         clsInvoke,  3,  0                   },
            {   4,  Trait::TYPE_GET,    "cO3",  "versionInfo",  clsInvoke,  4,  0                   },
            {   0,  Trait::TYPE_END,    "cO3",  0,              0,          0,  0                   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cO3* pthis1 = (cO3*) pthis;

        switch (index) {
        case 0:
            *rval = o3_new(tScrVec<Str>)(pthis1->args());
            break;
        case 1:
            *rval = pthis1->loadModule(ctx, argv[0].toStr());
            break;
        case 2:
            pthis1->wait(ctx, argc > 0 ? argv[0].toInt32() : -1);
            break;
        case 3:
            pthis1->exit(argc > 0 ? argv[0].toInt32() : 0);
            break;
        case 4:
            *rval = pthis1->versionInfo();
            break;
        };
        return 0;
    }

#endif // O3_C_O3_SCR_H
