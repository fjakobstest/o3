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
#ifndef O3_DEBUG_H
#define O3_DEBUG_H

#ifdef O3_TRACE
#define o3_trace \
struct Trace { \
    Trace() \
    { \
        o3::traceEnter(__FILE__, __LINE__); \
    } \
    \
    ~Trace() \
    { \
        o3::traceLeave(); \
    } \
}
#else
#define o3_trace struct
#endif // O3_TRACE

#if (O3_TRACE <= 0)
#define o3_trace0 o3_trace
#else
#define o3_trace0 struct
#endif

#if (O3_TRACE <= 1)
#define o3_trace1 o3_trace
#else
#define o3_trace1 struct
#endif

#if (O3_TRACE <= 2)
#define o3_trace2 o3_trace
#else
#define o3_trace2 struct
#endif

#if (O3_TRACE <= 3)
#define o3_trace3 o3_trace
#else
#define o3_trace3 struct
#endif

#ifdef O3_ASSERT
#define o3_assert(pred) ((void) ((pred) ? 0 \
                                        : (o3::assert(#pred, \
                                                      __FILE__, \
                                                      __LINE__), \
                                          0)))
#else
#define o3_assert(pred) ((void) 0)
#endif // O3_ASSERT

namespace o3 {

inline void traceEnter(const char* file, int line);

inline void traceLeave();

inline void assert(const char* pred, const char* file, int line);

}

#endif // O3_DEBUG_H
