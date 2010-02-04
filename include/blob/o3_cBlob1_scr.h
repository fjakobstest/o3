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
#ifndef O3_C_BLOB1_SCR_H
#define O3_C_BLOB1_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cBlob1",   0,              0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_FUN,    "cBlob1",   "__self__",     clsInvoke,  0,  0                   },
            {   1,  Trait::TYPE_FUN,    "cBlob1",   "fromString",   clsInvoke,  1,  0                   },
            {   2,  Trait::TYPE_FUN,    "cBlob1",   "fromHex",      clsInvoke,  2,  0                   },
            {   3,  Trait::TYPE_FUN,    "cBlob1",   "fromBase64",   clsInvoke,  3,  0                   },                      
            {   0,  Trait::TYPE_END,    "cBlob1",   0,              0,          0,  0                   }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cBlob1",   0,              0,          0,  0   },
            {   0,  Trait::TYPE_GET,    "cO3",      "blob",         extInvoke,  0,  0   },
            {   1,  Trait::TYPE_FUN,    "cScrBuf",  "toString",     extInvoke,  1,  0   },
            {   2,  Trait::TYPE_FUN,    "cScrBuf",  "toHex",        extInvoke,  2,  0   },
            {   3,  Trait::TYPE_FUN,    "cScrBuf",  "toBase64",     extInvoke,  3,  0   },
            {   4,  Trait::TYPE_FUN,    "cScrBuf",  "replace",      extInvoke,  4,  0   },            
            {   5,  Trait::TYPE_FUN,    "cScrBuf",  "replaceUtf16", extInvoke,  5,  0   },              
            {   0,  Trait::TYPE_END,    "cBlob1",   0,              0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cBlob1* pthis1 = (cBlob1*) pthis;

        switch (index) {
        case 0:
            if (argc > 0) {
                if (argv[0].type() == Var::TYPE_STR ||
                    argv[0].type() == Var::TYPE_WSTR)
                    *rval = o3_new(cScrBuf)(pthis1->__self__(argv[0].toStr()));
                else
                    *rval = o3_new(cScrBuf)(pthis1->__self__(ctx,
                                                             argv[0].toInt32()));
            } else 
                *rval = o3_new(cScrBuf)(pthis1->__self__(ctx));
            break;
        case 1:
            *rval = o3_new(cScrBuf)(pthis1->fromString(argv[0].toStr()));
            break;
        case 2:
            *rval = o3_new(cScrBuf)(pthis1->fromHex(argv[0].toStr()));
            break;
        case 3:
            *rval = o3_new(cScrBuf)(pthis1->fromBase64(argv[0].toStr()));
            break;
        };
        return 0;
    }

    static siEx extInvoke(iScr* pthis, iCtx* ctx, int index, int, const Var* argv,
                          Var* rval)
    {
        switch (index) {
        case 0:
            *rval = blob(ctx);
            break;
        case 1:
            *rval = toString((cScrBuf*) pthis);
            break;
        case 2:
            *rval = toHex((cScrBuf*) pthis);
            break;
        case 3:
            *rval = toBase64((cScrBuf*) pthis);
            break;
        case 4:
            if (argv[0].type()==Var::TYPE_STR)
                replace(pthis, argv[0].toStr(), argv[1].toStr());
            else
                replace(pthis, siBuf(argv[0].toScr()), siBuf(argv[1].toScr()));            
            break;
        case 5:
            if (argv[0].type()==Var::TYPE_WSTR)
                replaceUtf16(pthis, argv[0].toWStr(), argv[1].toWStr());
            else
                replaceUtf16(pthis, argv[0].toStr(), argv[1].toStr());
            break;

        };
        return 0;
    }


#endif // O3_C_BLOB1_SCR_H
