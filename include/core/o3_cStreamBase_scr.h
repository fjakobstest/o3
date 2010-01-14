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
#ifndef O3_C_STREAM_BASE_SCR_H
#define O3_C_STREAM_BASE_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cStreamBase",  0,          0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_GET,    "cStreamBase",  "eof",      clsInvoke,  0,  0                   },
            {   1,  Trait::TYPE_GET,    "cStreamBase",  "error",    clsInvoke,  1,  0                   },
            {   2,  Trait::TYPE_GET,    "cStreamBase",  "pos",      clsInvoke,  2,  0                   },
            {   2,  Trait::TYPE_SET,    "cStreamBase",  "pos",      clsInvoke,  3,  0                   },
            {   3,  Trait::TYPE_FUN,    "cStreamBase",  "readBlob", clsInvoke,  4,  0                   },
            {   4,  Trait::TYPE_FUN,    "cStreamBase",  "read",     clsInvoke,  5,  0                   },
            {   5,  Trait::TYPE_FUN,    "cStreamBase",  "write",    clsInvoke,  6,  0                   },
            {   6,  Trait::TYPE_FUN,    "cStreamBase",  "flush",    clsInvoke,  7,  0                   },
            {   7,  Trait::TYPE_FUN,    "cStreamBase",  "close",    clsInvoke,  8,  0                   },
            {   0,  Trait::TYPE_END,    0,              0,          0,          0,  0                   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx*, int index, int, const Var* argv,
                          Var* rval)
    {
        cStreamBase* pthis1 = (cStreamBase*) pthis;

        switch (index) {
        case 0:
            *rval = pthis1->eof();
            break;
        case 1:
            *rval = pthis1->error();
            break;
        case 2:
            *rval = (int) pthis1->pos();
            break;
        case 3:
            *rval = (int) pthis1->setPos(argv[0].toInt());
            break;
        case 4:
            *rval = o3_new(cScrBuf)(pthis1->readBlob(argv[0].toInt()));
            break;
        case 5:
            *rval = pthis1->read(argv[0].toInt());
            break;
        case 6:
            if (siBuf buf = argv[0].toScr()) 
                *rval = (int) pthis1->write(Buf(buf));
            else 
                *rval = (int) pthis1->write(argv[0].toStr());
            break;
        case 7:
            *rval = pthis1->flush();
            break;
        case 8:
            *rval = pthis1->close();
            break;
        }
        return 0;
    }


#endif // O3_C_STREAM_BASE_SCR_H
