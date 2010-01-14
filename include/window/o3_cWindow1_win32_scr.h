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
#ifndef O3_C_WINDOW1_WIN32_SCR_H
#define O3_C_WINDOW1_WIN32_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cWindow1",     0,                  0,          0,  cWindow1Base::clsTraits()   },
            {   0,  Trait::TYPE_FUN,    "cWindow1",     "createWindow",     clsInvoke,  0,  0                           },
            {   1,  Trait::TYPE_GET,    "cWindow1",     "clientX",          clsInvoke,  1,  0                           },
            {   2,  Trait::TYPE_GET,    "cWindow1",     "clientY",          clsInvoke,  2,  0                           },
            {   3,  Trait::TYPE_FUN,    "cWindow1",     "minimize",         clsInvoke,  3,  0                           },
            {   4,  Trait::TYPE_FUN,    "cWindow1",     "maximize",         clsInvoke,  4,  0                           },
            {   5,  Trait::TYPE_FUN,    "cWindow1",     "restore",          clsInvoke,  5,  0                           },
            {   6,  Trait::TYPE_FUN,    "cWindow1",     "close",            clsInvoke,  6,  0                           },
            {   7,  Trait::TYPE_SET,    "cWindow1",     "visible",          clsInvoke,  7,  0                           },
            {   8,  Trait::TYPE_GET,    "cWindow1",     "showButtons",      clsInvoke,  8,  0                           },
            {   8,  Trait::TYPE_SET,    "cWindow1",     "showButtons",      clsInvoke,  9,  0                           },
            {   9,  Trait::TYPE_GET,    "cWindow1",     "caption",          clsInvoke,  10, 0                           },
            {   9,  Trait::TYPE_SET,    "cWindow1",     "caption",          clsInvoke,  11, 0                           },
            {   10, Trait::TYPE_SET,    "cWindow1",     "icon",             clsInvoke,  12, 0                           },
            {   11, Trait::TYPE_FUN,    "cWindow1",     "open",             clsInvoke,  13, 0                           },
            {   12, Trait::TYPE_FUN,    "cWindow1",     "useIcon",          clsInvoke,  14, 0                           },
            {   13, Trait::TYPE_FUN,    "cWindow1",     "focus",            clsInvoke,  15, 0                           },
            {   14, Trait::TYPE_FUN,    "cWindow1",     "destroy",          clsInvoke,  16, 0                           },
            {   15, Trait::TYPE_SET,    "cWindow1",     "onclose",          clsInvoke,  17, 0                           },
            {   16, Trait::TYPE_SET,    "cWindow1",     "onend",            clsInvoke,  18, 0                           },            
            {   17, Trait::TYPE_GET,    "cWindow1",     "BOLD",             clsInvoke,  19, 0                           },
            {   18, Trait::TYPE_GET,    "cWindow1",     "ITALIC",           clsInvoke,  20, 0                           },
            {   19, Trait::TYPE_GET,    "cWindow1",     "UNDERLINE",        clsInvoke,  21, 0                           },
            {   20, Trait::TYPE_GET,    "cWindow1",     "STRIKEOUT",        clsInvoke,  22, 0                           },
            {   0,  Trait::TYPE_END,    "cWindow1",     0,                  0,          0,  0                           }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cWindow1",     0,                  0,          0,  0   },
            {   0,  Trait::TYPE_GET,    "cO3",          "window",           extInvoke,  0,  0   },
            {   1,  Trait::TYPE_FUN,    "cO3",          "createWindow",     extInvoke,  1,  0   },
            {   2,  Trait::TYPE_FUN,    "cO3",          "sendKeyEvent",     extInvoke,  2,  0   },
            {   3,  Trait::TYPE_FUN,    "cO3",          "mouseTo",          extInvoke,  3,  0   },
            {   4,  Trait::TYPE_FUN,    "cO3",          "mouseLeftClick",   extInvoke,  4,  0   },
            {   5,  Trait::TYPE_FUN,    "cO3",          "mouseRightClick",  extInvoke,  5,  0   },
            {   6,  Trait::TYPE_FUN,    "cO3",          "alertBox",         extInvoke,  6,  0   },
            {   0,  Trait::TYPE_END,    "cWindow1",     0,                  0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cWindow1* pthis1 = (cWindow1*) pthis;

        switch (index) {
        case 0:
            if (argc > 5)
                *rval = pthis1->createWindow(argv[0].toStr(), argv[1].toInt(),
                                             argv[2].toInt(), argv[3].toInt(),
                                             argv[4].toInt(), argv[5].toInt());
            else
                *rval = pthis1->createWindow(argv[0].toStr(), argv[1].toInt(),
                                             argv[2].toInt(), argv[3].toInt(),
                                             argv[4].toInt());
            break;
        case 1:
            *rval = pthis1->clientX();
            break;
        case 2:
            *rval = pthis1->clientY();
            break;
        case 3:
            pthis1->minimize();
            break;
        case 4:
            pthis1->maximize();
            break;
        case 5:
            pthis1->restore();
            break;
        case 6:
            pthis1->close();
            break;
        case 7:
            *rval = pthis1->setVisible(argv[0].toBool());
            break;
        case 8:
            *rval = pthis1->showButtons();
            break;
        case 9:
            *rval = pthis1->setShowButtons(argv[0].toBool());
            break;
        case 10:
            *rval = pthis1->caption();
            break;
        case 11:
            *rval = pthis1->setCaption(argv[0].toStr());
            break;
        case 12:
            pthis1->setIcon(argv[0].toStr());
            break;
        case 13:
            *rval = pthis1->open();
            break;
        case 14:
            if (siBuf buf = argv[0].toScr())
                pthis1->useIcon(buf->unwrap());
            break;
        case 15:
            *rval = pthis1->focus();
            break;
        case 16:
            pthis1->destroy();
            break;
        case 17:
            *rval = pthis1->setOnclose(ctx, argv[0].toScr());
            break;
        case 18:
            *rval = pthis1->setOnend(ctx, argv[0].toScr());
            break;
        case 19:
            *rval = 1;
            break;
        case 20:
            *rval = 2;
            break;
        case 21:
            *rval = 4;
            break;
        case 22:
            *rval = 8;
            break;
        };
        return 0;
    }

    static siEx extInvoke(iScr* tgt, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        siEx ex;

        switch (index) {
        case 0:
            *rval = window(ctx);
            break;
        case 1:
            if (argc > 5)
                *rval = createWindow(tgt, argv[0].toStr(),
                                     argv[1].toInt(), argv[2].toInt(),
                                     argv[3].toInt(), argv[4].toInt(),
                                     argv[5].toInt());
            else
                *rval = createWindow(tgt, argv[0].toStr(),
                     argv[1].toInt(), argv[2].toInt(),
                     argv[3].toInt(), argv[4].toInt());
            break;
        case 2:
            sendKeyEvent(argv[0].toStr());
            break;
        case 3:
            if (argc > 2)
                mouseTo(argv[0].toInt(), argv[1].toInt(),
                        siWindow(argv[2].toScr()));
            else
                mouseTo(argv[0].toInt(), argv[1].toInt());
            break;
        case 4:
            mouseLeftClick();
            break;
        case 5:
            mouseRightClick();
            break;
        case 6:
            *rval = alertBox(argv[0].toStr(), argv[1].toStr(), argc>2 ? argv[2].toStr() : Str(),
                             &ex);
        };
        return ex;
    }


#endif // O3_C_WINDOW1_WIN32_SCR_H