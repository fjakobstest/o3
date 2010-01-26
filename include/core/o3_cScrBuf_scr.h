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
#ifndef O3_C_SCR_BUF_SCR_H
#define O3_C_SCR_BUF_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cScrBuf",  0,                  0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_GET,    "cScrBuf",  "length",           clsInvoke,  0,  0                   },
            {   0,  Trait::TYPE_SET,    "cScrBuf",  "length",           clsInvoke,  1,  0                   },
            {   1,  Trait::TYPE_FUN,    "cScrBuf",  "__enumerator__",   clsInvoke,  2,  0                   },
            {   2,  Trait::TYPE_FUN,    "cScrBuf",  "__query__",        clsInvoke,  3,  0                   },
            {   3,  Trait::TYPE_FUN,    "cScrBuf",  "__getter__",       clsInvoke,  4,  0                   },
            {   4,  Trait::TYPE_FUN,    "cScrBuf",  "__setter__",       clsInvoke,  5,  0                   },
            {   0,  Trait::TYPE_END,    0,          0,                  0,          0,  0                   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx*, int index, int, const Var* argv,
                          Var* rval)
    {
        cScrBuf* pthis1 = (cScrBuf*) pthis;

        switch (index) {
        case 0:
            *rval = (int32_t) pthis1->length();
            break;
        case 1:
            *rval = (int32_t) pthis1->setLength((size_t) argv[0].toInt32());
            break;
        case 2:
            *rval = (int32_t) pthis1->__enumerator__((size_t) argv[0].toInt32());
            break;
        case 3:
            *rval = pthis1->__query__((size_t) argv[0].toInt32());
            break;
        case 4:
            *rval = (int32_t) pthis1->__getter__((size_t) argv[0].toInt32());
            break;
        case 5:
            *rval = (int32_t) pthis1->__setter__((size_t) argv[0].toInt32(),
                                                 (uint8_t) argv[1].toInt32());
            break;
        }
        return 0;
    }


#endif // O3_C_SCR_BUF_SCR_H
