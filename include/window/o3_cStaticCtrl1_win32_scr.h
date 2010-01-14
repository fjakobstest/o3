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
#ifndef O3_C_STATIC_CTRL1_WIN32_SCR_H
#define O3_C_STATIC_CTRL1_WIN32_SCR_H

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cStaticCtrl1", 0,                  0,          0,  0   },
            {   0,  Trait::TYPE_FUN,    "cWindow1",     "createTextbox",    extInvoke,  0,  0   },
            {   1,  Trait::TYPE_FUN,    "cWindow1",     "createBlank",      extInvoke,  1,  0   },
            {   2,  Trait::TYPE_FUN,    "cWindow1",     "createSeparator",  extInvoke,  2,  0   },
            {   3,  Trait::TYPE_FUN,    "cWindow1",     "createImgbox",     extInvoke,  3,  0   },
            {   0,  Trait::TYPE_END,    "cStaticCtrl1", 0,                  0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx extInvoke(iScr* tgt, iCtx*, int index, int argc,
                          const Var* argv, Var* rval)
    {
        switch (index) {
        case 0:
            *rval = siWindow(createTextbox(tgt, argv[0].toStr(),
                                               argv[1].toInt(), argv[2].toInt(),
                                               argv[3].toInt(), argv[4].toInt(),
                                               argc > 5 ? argv[5].toInt() : 16, 
                                               argc > 6 ? argv[6].toInt() : 0));
            break;
        case 1:
            *rval = siWindow(createBlank(tgt, argv[0].toInt(),
                                         argv[1].toInt(), argv[2].toInt(),
                                         argv[3].toInt()));
            break;
        case 2:
            *rval = siWindow(createSeparator(tgt, argv[0].toInt(),
                                             argv[1].toInt(), argv[2].toInt()));
            break;
        case 3:
            *rval = siWindow(createImgbox(tgt, argv[0].toStr(),
                                          argv[1].toInt(), argv[2].toInt(),
                                          argv[3].toInt(), argv[4].toInt()));
            break;
        };
        return 0;
    }

#endif // O3_C_STATIC_CTRL1_WIN32_SCR_H