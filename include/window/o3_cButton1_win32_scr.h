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
#ifndef O3_C_BUTTON1_WIN32_SCR_H
#define O3_C_BUTTON1_WIN32_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cButton1",     0,                  0,          0,  cWindow1Base::clsTraits()   },
            {   0,  Trait::TYPE_SET,    "cButton1",     "onclick",          clsInvoke,  0,  0                           },
            {   0,  Trait::TYPE_END,    "cButton1",     0,                  0,          0,  0                           }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cButton1",     0,                  0,          0,  0   },
            {   0,  Trait::TYPE_FUN,    "cWindow1",     "createButton",     extInvoke,  0,  0   },
            {   1,  Trait::TYPE_FUN,    "cWindow1",     "createRButton",    extInvoke,  1,  0   },
            {   0,  Trait::TYPE_END,    "cButton1",     0,                  0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int,
                          const Var* argv, Var* rval)
    {
        cButton1* pthis1 = (cButton1*) pthis;

        switch (index) {
        case 0:
            *rval = pthis1->setOnclick(ctx,argv[0].toScr());
            break;
        };
        return 0;
    }

    static siEx extInvoke(iScr* tgt, iCtx*, int index, int argc,
                          const Var* argv, Var* rval)
    {
        siEx ex;

        switch (index) {
        case 0:
            *rval = createButton(tgt, argv[0].toStr(),
                                     argv[1].toInt(), argv[2].toInt(),
                                     argv[3].toInt(), argv[4].toInt(),
                                     argc > 5 ? argv[5].toInt() : 16, 
                                     argc > 6 ? argv[6].toInt() : 0, &ex);
            break;
        case 1:
            *rval = createRButton(tgt, argv[0].toStr(),
                                      argv[1].toInt(), argv[2].toInt(),
                                      argv[3].toInt(), argv[4].toInt(),
                                      argc > 5 ? argv[5].toInt() : 16, 
                                      argc > 6 ? argv[6].toInt() : 0,
                                      argc > 7 ? argv[7].toInt() : 0);
            break;
        };
        return ex;
    }

#endif // O3_C_BUTTON1_WIN32_SCR_H