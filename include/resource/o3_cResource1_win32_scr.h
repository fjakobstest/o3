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
#ifndef O3_C_RESOURCE1_WIN32_SCR_H
#define O3_C_RESOURCE1_WIN32_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cResource1",    0,             0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_FUN,    "cResource1",   "unpack",       clsInvoke,  0,  0                   },
            {   1,  Trait::TYPE_FUN,    "cResource1",   "list",         clsInvoke,  1,  0                   },
            {   2,  Trait::TYPE_FUN,    "cResource1",   "get",          clsInvoke,  2,  0                   },
            {   3,  Trait::TYPE_FUN,    "cResource1",   "protocolOpen", clsInvoke,  3,  0                   },
            {   0,  Trait::TYPE_END,    "cResource1",    0,             0,          0,  0                   }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cResource1",    0,             0,          0,  0   },
            {   0,  Trait::TYPE_GET,    "cO3",          "resources",    extInvoke,  0,  0   },
            {   0,  Trait::TYPE_END,    "cResource1",    0,             0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int,
                          const Var* argv, Var* rval)
    {
        cResource1* pthis1 = (cResource1*) pthis;
        siEx ex;

        switch (index) {
        case 0:
            pthis1->unpack(ctx, siFs(argv[0].toScr()), &ex);
            break;
        case 1:
            *rval = o3_new(tScrVec<Str>)(pthis1->list());
            break;
        case 2:
            *rval = o3_new(cScrBuf)(pthis1->get(argv[0].toStr()));
            break;
        case 3:
            *rval = pthis1->protocolOpen(argv[0].toStr());
            break;
        };
        return ex;
    }

    static siEx extInvoke(iScr*, iCtx* ctx, int index, int, const Var* ,
                          Var* rval)
    {
        switch (index) {
        case 0:
            *rval = resources(ctx);
            break;
        }
        return 0;
    }

#endif // O3_C_RESOURCE1_WIN32_SCR_H
