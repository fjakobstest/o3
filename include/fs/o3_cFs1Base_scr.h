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
#ifndef O3_C_FS1_BASE_SCR_H
#define O3_C_FS1_BASE_SCR_H

    virtual Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = { 
            {   0,  Trait::TYPE_BEGIN,  "cFs1Base", 0,              0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_GET,    "cFs1Base", "TYPE_INVALID", clsInvoke,  0,  0                   },
            {   1,  Trait::TYPE_GET,    "cFs1Base", "TYPE_DIR",     clsInvoke,  1,  0                   },
            {   2,  Trait::TYPE_GET,    "cFs1Base", "TYPE_FILE",    clsInvoke,  2,  0                   },
            {   3,  Trait::TYPE_GET,    "cFs1Base", "TYPE_LINK",    clsInvoke,  3,  0                   },
            {   4,  Trait::TYPE_GET,    "cFs1Base", "valid",        clsInvoke,  4,  0                   },
            {   5,  Trait::TYPE_GET,    "cFs1Base", "exists",       clsInvoke,  5,  0                   },
            {   6,  Trait::TYPE_GET,    "cFs1Base", "type",         clsInvoke,  6,  0                   },
            {   7,  Trait::TYPE_GET,    "cFs1Base", "isDir",        clsInvoke,  7,  0                   },
            {   8,  Trait::TYPE_GET,    "cFs1Base", "isFile",       clsInvoke,  8,  0                   },
            {   9,  Trait::TYPE_GET,    "cFs1Base", "isLink",       clsInvoke,  9,  0                   },
            {   10, Trait::TYPE_GET,    "cFs1Base", "accessedTime", clsInvoke,  10, 0                   },
            {   11, Trait::TYPE_GET,    "cFs1Base", "modifiedTime", clsInvoke,  11, 0                   },
            {   12, Trait::TYPE_GET,    "cFs1Base", "createdTime",  clsInvoke,  12, 0                   },
            {   13, Trait::TYPE_GET,    "cFs1Base", "size",         clsInvoke,  13, 0                   },
            {   14, Trait::TYPE_GET,    "cFs1Base", "path",         clsInvoke,  14, 0                   },
            {   15, Trait::TYPE_GET,    "cFs1Base", "name",         clsInvoke,  15, 0                   },
            {   15, Trait::TYPE_SET,    "cFs1Base", "name",         clsInvoke,  16, 0                   },
            {   16, Trait::TYPE_FUN,    "cFs1Base", "get",          clsInvoke,  17, 0                   },
            {   17, Trait::TYPE_GET,    "cFs1Base", "parent",       clsInvoke,  18, 0                   },
            {   18, Trait::TYPE_GET,    "cFs1Base", "hasChildren",  clsInvoke,  19, 0                   },
            {   19, Trait::TYPE_FUN,    "cFs1Base", "scandir",      clsInvoke,  20, 0                   },
            {   20, Trait::TYPE_GET,    "cFs1Base", "children",     clsInvoke,  21, 0                   },
            {   21, Trait::TYPE_FUN,    "cFs1Base", "createDir",    clsInvoke,  22, 0                   },
            {   22, Trait::TYPE_FUN,    "cFs1Base", "createFile",   clsInvoke,  23, 0                   },
            {   23, Trait::TYPE_FUN,    "cFs1Base", "createLink",   clsInvoke,  24, 0                   },
            {   24, Trait::TYPE_FUN,    "cFs1Base", "remove",       clsInvoke,  25, 0                   },
            {   25, Trait::TYPE_FUN,    "cFs1Base", "copy",         clsInvoke,  26, 0                   },
            {   26, Trait::TYPE_FUN,    "cFs1Base", "move",         clsInvoke,  27, 0                   },
            {   27, Trait::TYPE_FUN,    "cFs1Base", "open",         clsInvoke,  28, 0                   },
            {   28, Trait::TYPE_GET,    "cFs1Base", "canRead",      clsInvoke,  29, 0                   },
            {   29, Trait::TYPE_GET,    "cFs1Base", "canWrite",     clsInvoke,  30, 0                   },
            {   30, Trait::TYPE_GET,    "cFs1Base", "blob",         clsInvoke,  31, 0                   },
            {   30, Trait::TYPE_SET,    "cFs1Base", "blob",         clsInvoke,  32, 0                   },
            {   31, Trait::TYPE_GET,    "cFs1Base", "data",         clsInvoke,  33, 0                   },
            {   31, Trait::TYPE_SET,    "cFs1Base", "data",         clsInvoke,  34, 0                   },
            {   32, Trait::TYPE_GET,    "cFs1Base", "onchange",     clsInvoke,  35, 0                   },
            {   32, Trait::TYPE_SET,    "cFs1Base", "onchange",     clsInvoke,  36, 0                   },
            {   33, Trait::TYPE_FUN,    "cFs1Base", "fopen",        clsInvoke,  37, 0                   },
            {   34, Trait::TYPE_FUN,    "cFs1Base", "fseek",        clsInvoke,  38, 0                   },
            {   35, Trait::TYPE_FUN,    "cFs1Base", "fread",        clsInvoke,  39, 0                   },
            {   36, Trait::TYPE_FUN,    "cFs1Base", "fwrite",       clsInvoke,  40, 0                   },
            {   37, Trait::TYPE_FUN,    "cFs1Base", "fflush",       clsInvoke,  41, 0                   },
            {   38, Trait::TYPE_FUN,    "cFs1Base", "fclose",       clsInvoke,  42, 0                   },
            {   0,  Trait::TYPE_END,    "cFs1Base", 0,              0,          0,  0                   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cFs1Base* pthis1 = (cFs1Base*) pthis;
        siEx ex;

        switch (index) {
        case 0:
            *rval = cFs1Base::TYPE_INVALID;
            break;
        case 1:
            *rval = cFs1Base::TYPE_DIR;
            break;
        case 2:
            *rval = cFs1Base::TYPE_FILE;
            break;
        case 3:
            *rval = cFs1Base::TYPE_LINK;
            break;
        case 4:
            *rval = pthis1->valid();
            break;
        case 5:
            *rval = pthis1->exists();
            break;
        case 6:
            *rval = pthis1->type();
            break;
        case 7:
            *rval = pthis1->isDir();
            break;
        case 8:
            *rval = pthis1->isFile();
            break;
        case 9:
            *rval = pthis1->isLink();
            break;
        case 10:
            *rval = (int) pthis1->accessedTime();
            break;
        case 11:
            *rval = (int) pthis1->modifiedTime();
            break;
        case 12:
            *rval = (int) pthis1->createdTime();
            break;
        case 13:
            *rval = (int) pthis1->size();
            break;
        case 14:
            *rval = pthis1->path();
            break;
        case 15:
            *rval = pthis1->name();
            break;
        case 16:
            *rval = pthis1->setName(argv[0].toStr(), &ex);
            break;
        case 17:
            *rval = pthis1->get(argv[0].toStr());
            break;
        case 18:
            *rval = pthis1->parent();
            break;
        case 19:
            *rval = pthis1->hasChildren();
            break;
        case 20:
            *rval = o3_new(tScrVec<Str>)(pthis1->scandir(argv[0].toStr()));
            break;
        case 21:
            *rval = o3_new(tScrVec<siFs>)(pthis1->children());
            break;
        case 22:
            *rval = pthis1->createDir();
            break;
        case 23:
            *rval = pthis1->createFile();
            break;
        case 24:
            *rval = pthis1->createLink(siFs(argv[0].toScr()));
            break;
        case 25:
            *rval = pthis1->remove(argc > 0 ? argv[0].toBool() : true);
            break;
        case 26:
            *rval = pthis1->copy(siFs(argv[0].toScr()));
            break;
        case 27:
            *rval = pthis1->move(siFs(argv[0].toScr()));
            break;
        case 28:
            *rval = pthis1->open(argv[0].toStr(), &ex);
            break;
        case 29:
            *rval = pthis1->canRead();
            break;
        case 30:
            *rval = pthis1->canWrite();
            break;
        case 31:
            *rval = o3_new(cScrBuf)(pthis1->blob());
            break;
        case 32:
            if (siBuf buf = argv[0].toScr())
                *rval = o3_new(cScrBuf)(pthis1->setBlob(buf->unwrap()));
            else if (siStream stream = argv[0].toScr())
                *rval = o3_new(cScrBuf)(pthis1->setBlob(stream));
            break;
        case 33:
            *rval = pthis1->data();
            break;
        case 34:
            *rval = pthis1->setData(argv[0].toStr());
            break;
        case 35:
            *rval = pthis1->onchange();
            break;
        case 36:
            *rval = pthis1->setOnchange(ctx, argv[0].toScr());
            break;
        case 37:
            *rval = pthis1->fopen(argv[0].toStr(), argv[1].toStr());
            break;
        case 38:
            if (siStream stream = argv[0].toScr())
                *rval = (int) pthis1->fseek(stream, argv[0].toInt32());
            break;
        case 39:
            if (siStream stream = argv[0].toScr())
                *rval = pthis1->fread(stream, argv[0].toInt32());
            break;
        case 40:
            if (siStream stream = argv[0].toScr())
                *rval = (int) pthis1->fwrite(stream, argv[0].toStr());
            break;
        case 41:
            if (siStream stream = argv[0].toScr())
                *rval = pthis1->fflush(stream);
        case 42:
            if (siStream stream = argv[0].toScr())
                *rval = pthis1->fclose(stream);
        }
        return ex;
    }

#endif // O3_C_FS1_BASE_SCR_H
