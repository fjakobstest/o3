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

#include <core/o3_core.h>
#include <js/o3_js.h>

using namespace o3;

int main(int argc, char** argv)
{
    cSys    sys;
    siMgr   mgr = o3_new(cMgr)();
    siCtx   ctx = o3_new(cJs1)(mgr, argc - 1, argv + 1);
    FILE*   stream;
    siEx    ex;

    if (argc < 2)
        return -1;
    stream = fopen(argv[1], "r");
    if (!stream)
        return -1;
    ctx->eval(Str(Buf(siStream(o3_new(cStream)(stream)).ptr())), &ex);
    if (ex) {
        printf("%s\n", ex->message().ptr());
        return -1;
    }
    return 0;
}
