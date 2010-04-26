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
#ifndef O3_CDOM1_H
#define O3_CDOM1_H

namespace o3 {
    struct cDOM1 : cScr {
        cDOM1(iHost* host=0)
			: m_host(host)
		{
        }

		siHost	m_host;
		siScr	m_ondblclick;
		siScr	m_onclick;
		siScr	m_onmousedown;
		siScr	m_onmouseup;
		siScr	m_onmousemove;
		siScr	m_onmousewheel;
		siScr	m_onkeyup;
		siScr	m_onkeydown;
		siScr	m_onkeypress;
		siWeak	m_ctx;

        o3_begin_class(cScr)        
		o3_end_class();

		o3_glue_gen();

		static o3_ext("cO3") o3_get siScr DOM(iCtx* ctx)
		{
			Var var = ctx->value("dom");
			siScr dom = var.toScr();
			if (dom)
				return dom;
			else {
				cDOM1* cdom = o3_new(cDOM1)(ctx->mgr()->host());					
				return ctx->setValue(
					"dom",Var(cdom)).toScr();
			}
		}

		o3_get siScr ondblclick()
		{
			return m_ondblclick;
		}

		o3_set siScr setOndblclick(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOndblclick(Delegate(this, &cDOM1::ondblclickEvent));
			}
			return m_ondblclick = scr;
		}

		void ondblclickEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_ondblclick)(siScr(e));
		}


		o3_get siScr onclick()
		{
			return m_onclick;
		}

		o3_set siScr setOnclick(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOnclick(Delegate(this, &cDOM1::onclickEvent));
			}
			return m_onclick = scr;
		}

		void onclickEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_onclick)(siScr(e));
		}


		o3_get siScr onmousedown()
		{
			return m_onmousedown;
		}

		o3_set siScr setOnmousedown(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOnmousedown(Delegate(this, &cDOM1::onmousedownEvent));
			}
			return m_onmousedown = scr;
		}

		void onmousedownEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_onmousedown)(siScr(e));
		}

		o3_get siScr onmouseup()
		{
			return m_onmouseup;
		}

		o3_set siScr setOnmouseup(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOnmouseup(Delegate(this, &cDOM1::onmouseupEvent));
			}
			return m_onmouseup = scr;
		}

		void onmouseupEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_onmouseup)(siScr(e));
		}


		o3_get siScr onmousemove()
		{
			return m_onmousemove;
		}

		o3_set siScr setOnmousemove(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOnmousemove(Delegate(this, &cDOM1::onmousemoveEvent));
			}
			return m_onmousemove = scr;
		}

		void onmousemoveEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_onmousemove)(siScr(e));
		}


		o3_get siScr onmousewheel()
		{
			return m_onmousewheel;
		}

		o3_set siScr setOnmousewheel(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOnmousewheel(Delegate(this, &cDOM1::onmousewheelEvent));
			}
			return m_onmousewheel = scr;
		}

		void onmousewheelEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_onmousewheel)(siScr(e));
		}

		o3_get siScr onkeyup()
		{
			return m_onkeyup;
		}

		o3_set siScr setOnkeyup(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOnkeyup(Delegate(this, &cDOM1::onkeyupEvent)); 
			}
			return m_onkeyup = scr;
		}

		void onkeyupEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_onkeyup)(siScr(e));
		}

		o3_get siScr onkeydown()
		{
			return m_onkeydown;
		}

		o3_set siScr setOnkeydown(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOnkeydown(Delegate(this, &cDOM1::onkeydownEvent)); 
			}
			return m_onkeydown = scr;
		}

		void onkeydownEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_onkeydown)(siScr(e));
		}


		o3_get siScr onkeypress()
		{
			return m_onkeypress;
		}

		o3_set siScr setOnkeypress(iCtx* ctx, iScr* scr)
		{
			m_ctx = ctx;

			if (m_host) {
				m_host->attachDOMListener();
				m_host->setOnkeypress(Delegate(this, &cDOM1::onkeypressEvent)); 
			}
			return m_onkeypress = scr;
		}

		void onkeypressEvent(iUnk* e)
		{
			Delegate(siCtx(m_ctx),m_onkeypress)(siScr(e));
		}


};

}

#endif // O3_CDOM1_H
