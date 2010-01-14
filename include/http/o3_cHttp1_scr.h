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
#ifndef O3_C_HTTP1_SCR_H
#define O3_C_HTTP1_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cHttp1",   0,                              0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_GET,    "cHttp1",   "READY_STATE_UNINITIALIZED",    clsInvoke,  0,  0                   },
            {   1,  Trait::TYPE_GET,    "cHttp1",   "READY_STATE_LOADING",          clsInvoke,  1,  0                   },
            {   2,  Trait::TYPE_GET,    "cHttp1",   "READY_STATE_LOADING",          clsInvoke,  2,  0                   },
            {   3,  Trait::TYPE_GET,    "cHttp1",   "READY_STATE_INTERACTIVE",      clsInvoke,  3,  0                   },
            {   4,  Trait::TYPE_GET,    "cHttp1",   "READY_STATE_COMPLETED",        clsInvoke,  4,  0                   },
            {   5,  Trait::TYPE_GET,    "cHttp1",   "readyState",                   clsInvoke,  5,  0                   },
            {   6,  Trait::TYPE_FUN,    "cHttp1",   "open",                         clsInvoke,  6,  0                   },
            {   7,  Trait::TYPE_FUN,    "cHttp1",   "setRequestHeader",             clsInvoke,  7,  0                   },
            {   8,  Trait::TYPE_FUN,    "cHttp1",   "send",                         clsInvoke,  8,  0                   },
            {   9,  Trait::TYPE_GET,    "cHttp1",   "statusCode",                   clsInvoke,  9,  0                   },
            {   10, Trait::TYPE_GET,    "cHttp1",   "statusText",                   clsInvoke,  10, 0                   },
            {   11, Trait::TYPE_FUN,    "cHttp1",   "getAllResponseHeaders",        clsInvoke,  11, 0                   },
            {   12, Trait::TYPE_FUN,    "cHttp1",   "getResponseHeader",            clsInvoke,  12, 0                   },
            {   13, Trait::TYPE_GET,    "cHttp1",   "bytesTotal",                   clsInvoke,  13, 0                   },
            {   14, Trait::TYPE_GET,    "cHttp1",   "bytesReceived",                clsInvoke,  14, 0                   },
            {   15, Trait::TYPE_GET,    "cHttp1",   "responseBlob",                 clsInvoke,  15, 0                   },
            {   16, Trait::TYPE_GET,    "cHttp1",   "responseText",                 clsInvoke,  16, 0                   },
            {   17, Trait::TYPE_FUN,    "cHttp1",   "abort",                        clsInvoke,  17, 0                   },
            {   18, Trait::TYPE_GET,    "cHttp1",   "onreadystatechange",           clsInvoke,  18, 0                   },
            {   18, Trait::TYPE_SET,    "cHttp1",   "onreadystatechange",           clsInvoke,  19, 0                   },
            {   19, Trait::TYPE_GET,    "cHttp1",   "onprogress",                   clsInvoke,  20, 0                   },
            {   19, Trait::TYPE_SET,    "cHttp1",   "onprogress",                   clsInvoke,  21, 0                   },
            {   0,  Trait::TYPE_END,    "cHttp1",   0,                              0,          0,  0                   }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cHttp1",  0,       0,          0,  0   },
            {   0,  Trait::TYPE_FUN,    "cO3",     "http",  extInvoke,  0,  0   },
            {   0,  Trait::TYPE_END,    "cHttp1",   0,      0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cHttp1* pthis1 = (cHttp1*) pthis;

        switch (index) {
        case 0:
            *rval = cHttp1::READY_STATE_UNINITIALIZED;
            break;
        case 1:
            *rval = cHttp1::READY_STATE_LOADING;
            break;
        case 2:
            *rval = cHttp1::READY_STATE_LOADED;
            break;
        case 3:
            *rval = cHttp1::READY_STATE_INTERACTIVE;
            break;
        case 4:
            *rval = cHttp1::READY_STATE_COMPLETED;
            break;
        case 5:
            *rval = pthis1->readyState();
            break;
        case 6:
            pthis1->open(argv[0].toStr().ptr(), argv[1].toStr().ptr(),
                         argc > 2 ? argv[2].toBool() : true);
            break;
        case 7:
            pthis1->setRequestHeader(argv[0].toStr().ptr(), argv[1].toStr().ptr());
            break;
        case 8:
            if (siBuf buf = argv[0].toScr())
                pthis1->send(ctx, Buf(buf.ptr()));
            else
                pthis1->send(ctx, argv[0].toStr());
            break;
        case 9:
            *rval = pthis1->statusText();
            break;
        case 10:
            *rval = pthis1->statusCode();
            break;
        case 11:
            *rval = pthis1->getAllResponseHeaders();
            break;
        case 12:
            *rval = pthis1->getResponseHeader(argv[0].toStr());
            break;
        case 13:
            *rval = (int) pthis1->bytesTotal();
            break;
        case 14:
            *rval = (int) pthis1->bytesReceived();
            break;
        case 15:
            *rval = o3_new(cScrBuf)(pthis1->responseBlob());
            break;
        case 16:
            *rval = pthis1->responseText().ptr();
            break;
        case 17:
            pthis1->abort();
            break;
        case 18:
            *rval = pthis1->onreadystatechange();
            break;
        case 19:
            *rval = pthis1->setOnreadystatechange(argv[0].toScr());
            break;
        case 20:
            *rval = pthis1->onprogress();
            break;
        case 21:
            *rval = pthis1->setOnprogress(argv[0].toScr());
        }
        return 0;
    }

    static siEx extInvoke(iScr*, iCtx*, int index, int, const Var*, Var* rval)
    {
        switch (index) {
        case 0:
            *rval = http();
            break;
        }
        return 0;
    }

#endif // O3_C_HTTP1_SCR_H
