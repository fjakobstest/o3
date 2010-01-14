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
#ifndef O3_C_WINDOW1_BASE_H
#define O3_C_WINDOW1_BASE_H

namespace o3 {

struct cWindow1Base : cScr {
    o3_begin_class(cScr)
    o3_end_class()

#include "o3_cWindow1Base_scr.h"

    virtual o3_get int x() = 0;

    virtual o3_set int setX(int x) = 0;

    virtual o3_get int y() = 0;

    virtual o3_set int setY(int y) = 0;

    virtual o3_get int width() = 0;

    virtual o3_set int setWidth(int width) = 0;

    virtual o3_get int height() = 0;

    virtual o3_set int setHeight(int height) = 0;
};

}

#endif // O3_C_WINDOW1_BASE_H