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
#ifndef O3_C_FS1_POSIX_SCR_H
#define O3_C_FS1_POSIX_SCR_H

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cFs1",    0,          0,          0,  0   },
            {   0,  Trait::TYPE_GET,    "cO3",     "fs",       extInvoke,  0,  0   },
            {   1,  Trait::TYPE_GET,    "cO3",     "cwd",      extInvoke,  1,  0   },
            {   0,  Trait::TYPE_END,    "cFs1",    0,          0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx extInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        switch (index) {
        case 0:
            *rval = fs(ctx);
            break;
        case 1:
            *rval = cwd(ctx);
            break;
        }
        return 0;
    }

#endif // O3_C_FS1_POSIX_SCR_H
