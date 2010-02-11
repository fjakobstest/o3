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
#ifndef O3_PROCESS_H
#define O3_PROCESS_H

#include "o3_cProcess1Base.h"
#include "o3_cProcess1.h"

#ifdef O3_WITH_GLUE
#include "o3_scr_cProcess1Base.h"
#ifdef O3_POSIX
#include "o3_scr_cProcess1_posix.h"
#else
#include "o3_scr_cProcess1_win32.h"
#endif // O3_POSIX
#endif // O3_WITH_GLUE

#endif // O3_PROCESS_H
