/*
 * Copyright (C) 2010 Ajax.org BV
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
#ifndef O3_I_HOST_H
#define O3_I_HOST_H

namespace o3 {

struct iHost;
struct iScr;

o3_iid(iHost, 0xa90343fe, 
	   0x297b, 
	   0x494e, 
	   0x93, 0xe, 0x39, 0xe4, 0x98, 0xa9, 0x74, 0x41);


struct iHost : iUnk {
    virtual void attachDOMListener() = 0;
	
	virtual void setOndblclick(Delegate) = 0;	
	virtual void setOnclick(Delegate) = 0;
	virtual void setOnmousedown(Delegate) = 0;
	virtual void setOnmouseup(Delegate) = 0;
	virtual void setOnmousemove(Delegate) = 0;
	virtual void setOnmousewheel(Delegate) = 0;

	virtual void setOnkeyup(Delegate) = 0;
	virtual void setOnkeydown(Delegate) = 0;
	virtual void setOnkeypress(Delegate) = 0;

	virtual Delegate ondblclick() = 0;	
	virtual Delegate onclick() = 0;
	virtual Delegate onmousedown() = 0;
	virtual Delegate onmouseup() = 0;
	virtual Delegate onmousemove() = 0;
	virtual Delegate onmousewheel() = 0;

	virtual Delegate onkeyup() = 0;
	virtual Delegate onkeydown() = 0;
	virtual Delegate onkeypress() = 0;
};

}

#endif // O3_I_HOST_H
