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
#ifndef O3_I_FS_H
#define O3_I_FS_H

namespace o3 {

o3_iid(iFs, 0x9F96A731,
            0x53EC,
            0x4E42,
            0xA5, 0x75, 0xFB, 0x5D, 0xD3, 0x43, 0xB3, 0xB4);

struct iFs : iUnk {
    virtual siStream open(const char* mode, siEx* ex = 0) = 0;
};

}

#endif // O3_I_FS_H
