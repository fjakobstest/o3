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
#ifndef O3_C_RESOURCE_BUILDER1_WIN32_SCR_H
#define O3_C_RESOURCE_BUILDER1_WIN32_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cResourceBuilder1",    0,                  0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_FUN,    "cResourceBuilder1",    "addAsResource",    clsInvoke,  0,  0                   },
            {   1,  Trait::TYPE_FUN,    "cResourceBuilder1",    "buildAndAppend",   clsInvoke,  1,  0                   },
            {   0,  Trait::TYPE_END,    "cResourceBuilder1",    0,                  0,          0,  0                   }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cResourceBuilder1",    0,                  0,          0,  0   },
            {   0,  Trait::TYPE_FUN,    "cO3",                  "resourceBuilder",  extInvoke,  0,  0   },
            {   1,  Trait::TYPE_FUN,    "cFs1",                 "removeResource",   extInvoke,  1,  0   },
            {   0,  Trait::TYPE_END,    "cResourceBuilder1",    0,                  0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx*, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cResourceBuilder1* pthis1 = (cResourceBuilder1*) pthis;

        switch (index) {
        case 0:
            *rval = pthis1->addAsResource(siFs(argv[0].toScr()), argc > 1 ? argv[1].toStr() : 0);
            break;
        case 1:
            pthis1->buildAndAppend(siFs(argv[0].toScr()), 0);
            break;
        };
        return siEx();
    }

    static siEx extInvoke(iScr* pthis, iCtx*, int index, int, const Var* ,
                          Var* rval)
    {
        switch (index) {
        case 0:
            *rval = resourceBuilder();
            break;
        case 1:
            *rval = removeResource(siFs(pthis));
        }
        return 0;
    }

#endif // O3_C_RESOURCE_BUILDER1_WIN32_SCR_H