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
#ifndef O3_C_TOOLS1_WIN32_SCR_H
#define O3_C_TOOLS1_WIN32_SCR_H

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cO3",  0,                      0,          0,  cScr::clsTraits()   },
            {   1,  Trait::TYPE_GET,    "cO3",  "tempPath",             extInvoke,  0,  0                   },
            {   2,  Trait::TYPE_GET,    "cO3",  "selfPath",             extInvoke,  1,  0                   },
            {   3,  Trait::TYPE_FUN,    "cO3",  "checkIfInstalled",     extInvoke,  2,  0                   },
            {   4,  Trait::TYPE_FUN,    "cO3",  "regDll",               extInvoke,  3,  0                   },
            {   5,  Trait::TYPE_FUN,    "cO3",  "unregDll",             extInvoke,  4,  0                   },
            {   6,  Trait::TYPE_FUN,    "cO3",  "regUninstaller",       extInvoke,  5,  0                   },
            {   7,  Trait::TYPE_FUN,    "cO3",  "unregUninstaller",     extInvoke,  6,  0,                  },
            {   8,  Trait::TYPE_FUN,    "cO3",  "getUninstPath",        extInvoke,  7,  0                   },
            {   9,  Trait::TYPE_FUN,    "cO3",  "regMozillaPlugin",     extInvoke,  8,  0,                  },
            {   10, Trait::TYPE_FUN,    "cO3",  "unregMozillaPlugin",   extInvoke,  9,  0                   },
            {   11, Trait::TYPE_GET,    "cO3",  "adminUser",            extInvoke,  10, 0                   },
            {   12, Trait::TYPE_GET,    "cO3",  "winVersionMajor",      extInvoke,  11, 0                   },
            {   0,  Trait::TYPE_END,    "cO3",  0,                      0,          0,  0                   }
        };

        return TRAITS;
    }

    static siEx extInvoke(iScr*, iCtx* ctx, int index, int,
                          const Var* argv, Var* rval)
    {
        switch (index) {
        case 0:
            *rval = tempPath();
            break;
        case 1:
            *rval = selfPath();
            break;
        case 2:
            *rval = checkIfInstalled(argv[0].toStr());
            break;
        case 3:
            *rval = regDll(argv[0].toStr(), argv[1].toBool());
            break;
        case 4:
            *rval = unregDll(argv[0].toStr(), argv[1].toBool());
            break;
        case 5:
            *rval = regUninstaller(ctx, argv[0].toBool(), argv[1].toScr());
            break;
        case 6:
            *rval = unregUninstaller(argv[0].toBool(), argv[1].toStr());
            break;
        case 7:
            *rval = getUninstPath(argv[0].toStr());
            break;
        case 8:
            *rval = regMozillaPlugin(ctx, argv[0].toBool(), argv[1].toScr());
            break;
        case 9:
            *rval = unregMozillaPlugin(argv[0].toBool(), argv[1].toStr(), argv[2].toStr(),
                                       argv[3].toStr());
            break;
        case 10:
            *rval = adminUser();
            break;
        case 11:
            *rval = winVersionMajor();
            break;
        }
        return 0;
    }

#endif // O3_C_TOOLS1_WIN32_SCR_H