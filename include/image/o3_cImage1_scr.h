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
#ifndef O3_C_IMAGE1_SCR_H
#define O3_C_IMAGE1_SCR_H

    Trait* select()
    {
        return clsTraits();
    }

    static Trait* clsTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cImage1",   0,              0,          0,  cScr::clsTraits()   },
            {   0,  Trait::TYPE_FUN,    "cImage1",   "__self__",     clsInvoke,  0,  0                   },
			{   1,  Trait::TYPE_GET,    "cImage1 ",  "mode",		 clsInvoke,  1,  0                   },
			{   2,  Trait::TYPE_GET,    "cImage1 ",  "width",		 clsInvoke,  2,  0                   },
			{   3,  Trait::TYPE_GET,    "cImage1 ",  "height",		 clsInvoke,  3,  0                   },
			{   4,  Trait::TYPE_GET,    "cImage1 ",  "x",    		 clsInvoke,  4,  0                   },
			{   5,  Trait::TYPE_GET,    "cImage1 ",  "y",	    	 clsInvoke,  5,  0                   },
			{   6,  Trait::TYPE_FUN,    "cImage1 ",  "savePng",	     clsInvoke,  6,  0                   },
			{   7,  Trait::TYPE_FUN,    "cImage1 ",  "clear",	     clsInvoke,  7,  0                   },
			{   8,  Trait::TYPE_FUN,    "cImage1 ",  "setPixel",	 clsInvoke,  8,  0                   },
			{   9,  Trait::TYPE_FUN,    "cImage1 ",  "getPixel",	 clsInvoke,  9,  0                   },
			{  10,  Trait::TYPE_FUN,    "cImage1 ",  "line",	     clsInvoke, 10,  0                   },
			{  11,  Trait::TYPE_SET,    "cImage1 ",  "fillStyle",	 clsInvoke, 11,  0                   },
			{  12,  Trait::TYPE_FUN,    "cImage1 ",  "fillRect",	 clsInvoke, 12,  0                   },
			{  13,  Trait::TYPE_FUN,    "cImage1 ",  "rect",	     clsInvoke, 13,  0                   },

			{  14,  Trait::TYPE_FUN,    "cImage1 ",  "moveTo",	     clsInvoke, 14,  0                   },
			{  15,  Trait::TYPE_FUN,    "cImage1 ",  "lineTo",	     clsInvoke, 15,  0                   },
			{  16,  Trait::TYPE_FUN,    "cImage1 ",  "closePath",	 clsInvoke, 16,  0                   },
			{  17,  Trait::TYPE_FUN,    "cImage1 ",  "stroke",	     clsInvoke, 17,  0                   },
			{  18,  Trait::TYPE_SET,    "cImage1 ",  "strokeStyle",	 clsInvoke, 18,  0                   },
			{  19,  Trait::TYPE_SET,    "cImage1 ",  "strokeWidth",	 clsInvoke, 19,  0                   },
			{  20,  Trait::TYPE_FUN,    "cImage1 ",  "beginPath",	 clsInvoke, 20,  0                   },
			{  21,  Trait::TYPE_FUN,    "cImage1 ",  "quadraticCurveTo", clsInvoke, 21,  0                   },

			{   0,  Trait::TYPE_END,    "cImage1",   0,              0,          0,  0                   }
        };

        return TRAITS;
    }

    static Trait* extTraits()
    {
        static Trait TRAITS[] = {
            {   0,  Trait::TYPE_BEGIN,  "cImage1",   0,              0,          0,  0   },
            {   0,  Trait::TYPE_GET,    "cO3",      "image",         extInvoke,  0,  0   },
            {   0,  Trait::TYPE_END,    "cImage1",   0,              0,          0,  0   }
        };

        return TRAITS;
    }

    static siEx clsInvoke(iScr* pthis, iCtx* ctx, int index, int argc,
                          const Var* argv, Var* rval)
    {
        cImage1* pthis1 = (cImage1*) pthis;

        switch (index) {
        case 0:
			*rval = pthis1->__self__(argv[0].toInt(), argv[1].toInt(), argv[2].toStr() );
            break;
        case 1:
			*rval = pthis1->mode();
            break;
        case 2:
			*rval = (int)pthis1->width();
            break;
        case 3:
			*rval = (int)pthis1->height();
            break;
        case 4:
			*rval = (int)pthis1->x();
            break;
        case 5:
			*rval = (int)pthis1->y();
            break;
        case 6:
			*rval = (int)pthis1->savePng(argv[0].toStr(),NULL); //todo: exception should get an output pointer!
            break;
        case 7:
			pthis1->clear(argv[0].toInt());
            break;
        case 8:
			pthis1->setPixel(argv[0].toInt(),argv[1].toInt(),argv[2].toInt()); 
			break;
        case 9:
			*rval = (int)pthis1->getPixel(argv[0].toInt(),argv[1].toInt());
            break;
		case 10:
			pthis1->line(argv[0].toInt(),argv[1].toInt(),argv[2].toInt(),argv[3].toInt(),argv[4].toInt());
            break;

		case 11:
			pthis1->fillStyle(argv[0].toStr());
            break;
		case 12:
			pthis1->fillRect(argv[0].toDouble(),argv[1].toDouble(),argv[2].toDouble(),argv[3].toDouble());
            break;

		case 13:
			pthis1->rect(argv[0].toInt(),argv[1].toInt(),argv[2].toInt(),argv[3].toInt(),argv[4].toInt());
            break;

		case 14:
			pthis1->moveTo(argv[0].toDouble(),argv[1].toDouble());
            break;

		case 15:
			pthis1->lineTo(argv[0].toDouble(),argv[1].toDouble());
            break;

		case 16:
			pthis1->closePath();
            break;

		case 17:
			pthis1->stroke();
            break;
		case 18:
			pthis1->strokeStyle(argv[0].toStr());
            break;
		case 19:
			pthis1->strokeWidth(argv[0].toDouble());
            break;
		case 20:
			pthis1->beginPath();
            break;
		case 21:
			pthis1->quadraticCurveTo(argv[0].toDouble(),argv[1].toDouble(),argv[2].toDouble(),argv[3].toDouble());
            break;
        };
        return 0;
		argc, ctx;
    }

    static siEx extInvoke(iScr* pthis, iCtx* ctx, int index, int, const Var* argv,
                          Var* rval)
    {
        switch (index) {
        case 0:
            *rval = image(ctx);
            break;
        };
        return 0;
		ctx, argv,pthis;
	}


#endif // O3_C_IMAGE1_SCR_H
