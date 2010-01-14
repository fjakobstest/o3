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
#ifndef O3_C_WINDOW1_BASE_SCR_H
#define O3_C_WINDOW1_BASE_SCR_H

    virtual Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = { 
            {   0,  Trait::TYPE_BEGIN,  "cWindow1Base", 0,          0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_GET,    "cWindow1Base", "x",        clsInvoke,  0,  0                   },
            {   0,  Trait::TYPE_SET,    "cWindow1Base", "x",        clsInvoke,  1,  0                   },
            {   1,  Trait::TYPE_GET,    "cWindow1Base", "y",        clsInvoke,  2,  0                   },
            {   1,  Trait::TYPE_SET,    "cWindow1Base", "y",        clsInvoke,  3,  0                   },
            {   2,  Trait::TYPE_GET,    "cWindow1Base", "width",    clsInvoke,  4,  0                   },
            {   2,  Trait::TYPE_SET,    "cWindow1Base", "width",    clsInvoke,  5,  0                   },
            {   3,  Trait::TYPE_GET,    "cWindow1Base", "height",   clsInvoke,  6,  0                   },
            {   3,  Trait::TYPE_SET,    "cWindow1Base", "height",   clsInvoke,  7,  0                   },
            {   0,  Trait::TYPE_END,    "cWindow1Base", 0,          0,          0,  0                   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx*, int index, int,
                          const Var* argv, Var* rval)
    {
        cWindow1Base* pthis1 = (cWindow1Base*) pthis;

        switch (index) {
        case 0:
            *rval = pthis1->x();
            break;
        case 1:
            *rval = pthis1->setX(argv[0].toInt());
            break;
        case 2:
            *rval = pthis1->y();
            break;
        case 3:
            *rval = pthis1->setY(argv[0].toInt());
            break;
        case 4:
            *rval = pthis1->width();
            break;
        case 5:
            *rval = pthis1->setWidth(argv[0].toInt());
            break;
        case 6:
            *rval = pthis1->height();
            break;
        case 7:
            *rval = pthis1->setHeight(argv[0].toInt());
            break;
        }
        return 0;
    }

#endif // O3_C_WINDOW1_BASE_SCR_H
