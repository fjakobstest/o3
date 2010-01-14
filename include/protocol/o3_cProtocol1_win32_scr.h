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
#ifndef O3_C_PROTOCOL1_WIN32_SCR_H
#define O3_C_PROTOCOL1_WIN32_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cProtocol1",   0,              0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_FUN,    "cProtocol1",   "addSource",    clsInvoke,  0,  0                   },
            {   0,  Trait::TYPE_END,    "cProtocol1",   0,              0,          0,  0                   }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cProtocol1",   0,                  0,          0,  0   },
            {   0,  Trait::TYPE_FUN,    "cProtocol1",   "protocolHandler",  extInvoke,  0,  0   },
            {   0,  Trait::TYPE_END,    "cProtocol1",   0,                  0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx*, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cProtocol1* pthis1 = (cProtocol1*) pthis;

        switch (index) {
        case 0:
            if (argc > 1)
                *rval = pthis1->addSource(argv[0].toScr(), argv[0].toStr());
            else
                *rval = pthis1->addSource(argv[0].toScr());
            break;
        };
        return 0;
    }
  
    static siEx extInvoke(iScr*, iCtx* ctx, int index, int, const Var*,
                          Var* rval)
    {
        switch (index) {
        case 0:
            *rval = protocolHandler(ctx);
        }
        return 0;
    }

#endif // O3_C_PROTOCOL1_WIN32_SCR_H
