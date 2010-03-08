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
#ifndef O3_C_O3_H
#define O3_C_O3_H

namespace o3 {

o3_cls(cLoadProgress);
struct cLoadProgress : cScr {
	typedef iHttp::ReadyState ReadyState;

	cLoadProgress()
		: m_state(ReadyState::READY_STATE_UNINITIALIZED)
		, m_bytes_received(0)
	{
		m_mutex = g_sys->createMutex();
	}

	virtual ~cLoadProgress()
	{

	}
	
	o3_begin_class(cScr)
	o3_end_class()

	o3_glue_gen()

	Str m_file_name;
	size_t m_bytes_received;
	ReadyState m_state;
	siMutex m_mutex;

	o3_enum("ReadyState",
		READY_STATE_UNINITIALIZED,
		READY_STATE_LOADING,
		READY_STATE_LOADED,
		READY_STATE_INTERACTIVE,
		READY_STATE_COMPLETED);

	o3_get size_t bytesReceived()
	{
		o3_trace3 trace;
		Lock lock(m_mutex);

		return m_bytes_received;
	}

	o3_get ReadyState readyState()
	{
		o3_trace3 trace;
		Lock lock(m_mutex);

		return m_state;
	}

	o3_get Str fileName()
	{
		o3_trace3 trace;
		Lock lock(m_mutex);

		return m_file_name;
	}

	void setFileName(const Str& name)
	{
		o3_trace3 trace;
		Lock lock(m_mutex);

		m_file_name = name;
	}

	void setState(ReadyState state)
	{
		o3_trace3 trace;
		Lock lock(m_mutex);

		m_state = state;
	}

	void setBytesReceived(size_t bytes_received)
	{
		o3_trace3 trace;
		Lock lock(m_mutex);

		m_bytes_received = bytes_received;
	}
};

struct cO3 : cScr {
    tVec<Str>   m_args;
    tVec<Str>   m_envs;
	siWeak		m_ctx;	
	tList<Str>  m_to_load;
	tList<Str>  m_approved;
	siScr		m_onload;
	siScr		m_onprogress;
	bool		m_loading;
	scLoadProgress	m_load_progress;

    cO3(int argc, char** argv, char** envp)
		: m_loading(false)
	{
        if (argv)
            while (*argv)
                m_args.push(*argv++);
        if (envp)
            while (*envp)
                m_envs.push(*envp++);

		m_load_progress = o3_new(cLoadProgress);		
    }

    ~cO3()
    {
    }

    o3_begin_class(cScr)
    o3_end_class()

	o3_glue_gen()

    o3_get tVec<Str> args()
    {
        return m_args;
    }

    o3_get tVec<Str> envs()
    {
        return m_envs;
    }

    o3_fun bool loadModule(iCtx* ctx, const char* name) 
    {
        o3_trace3 trace;

        return ctx->mgr()->loadModule(name);
    }

	o3_fun void require(iCtx* ctx, const Str& module)
	{
#ifdef O3_PLUGIN
		m_to_load.pushBack(module);
#else
		ctx->mgr()->loadModule(module);
#endif
	}

	o3_fun void loadModules(iCtx* ctx, iScr* onload, iScr* onprogress=0) 
	{
		o3_trace3 trace;
		// if a load is in progress the second call should fail
		if (m_loading)
			return;

		m_onload = onload;
		m_onprogress = onprogress;
		m_ctx = ctx;
		approveModules();

		// start loading
		m_to_load.clear();
		ctx->mgr()->pool()->post(Delegate(this, &cO3::moduleLoading),
			o3_cast this);
	}

	void approveModules() 
	{
		siMgr mgr = siCtx(m_ctx)->mgr();

		// read settings
		tMap<Str, int> settings = mgr->readSettings();

		// approval
		Str name;
		tList<Str> to_approve, approved;		
		for (tList<Str>::Iter it = m_to_load.begin(); 
			it != m_to_load.end(); ++it) {				
				if ( settings[*it])
					m_approved.pushBack(*it);
				else
					to_approve.pushBack(*it);
		}

		approved = approve(to_approve);
		m_approved.append(approved.begin(), approved.end()); 

		// save settings
		for (tList<Str>::Iter it = approved.begin(); 
			it != approved.end(); ++it) 
			settings[*it]=1;		
		mgr->writeSettings(settings);
	}

	void moduleLoading(iUnk* pthis)
	{
		siCtx ctx = siCtx(m_ctx);
		siMgr mgr = ctx->mgr();		
		tList<Str>::Iter
			it = m_approved.begin(),
			end = m_approved.end();	
		
		for (; it != end; ++it) {
			if ( ! mgr->loadModule(*it)) {
				m_load_progress->setFileName(*it);
				Buf downloaded = mgr->downloadComponent(ctx,*it,
					Str(),Delegate(this, &cO3::onStateChange), 
					Delegate(this, &cO3::onProgress));
				size_t s = downloaded.size();
			}
		}

		m_approved.clear();
		ctx->loop()->post(Delegate(this, &cO3::onLoad),pthis);
	}

	void onLoad(iUnk*)
	{
		m_loading = false;
		Delegate(siCtx(m_ctx),m_onload)(this);
	}

	void onStateChange(iUnk* http)
	{
		siHttp ihttp = http;
		m_load_progress->setState(
			ihttp->readyState());
		Delegate(siCtx(m_ctx), m_onprogress)(
			siScr(m_load_progress));
	}

	void onProgress(iUnk* http)
	{
		siHttp ihttp = http;
		m_load_progress->setBytesReceived(
			ihttp->bytesReceived());
		Delegate(siCtx(m_ctx), m_onprogress)(
			siScr(m_load_progress));
	}

    o3_fun void wait(iCtx* ctx, int timeout = -1)
    {
        o3_trace3 trace;

        ctx->loop()->wait(timeout);
    }

    o3_fun void exit(int status = 0)
    {
        o3_trace3 trace;

        ::exit(status);
    }

    o3_get Str versionInfo()
    {		
        o3_trace3 trace;

        return "v0.9";    
    }

	tList<Str> approve( const tList<Str>& to_approve ) 
	{				
		tList<Str> approved;
		if(to_approve.empty())
			return approved;
		
		Str msg;		
		for (tList<Str>::ConstIter it = to_approve.begin(); 
			it != to_approve.end(); ++it) {	
				msg.append(*it);
				msg.append("\n");
		}

		if (g_sys->approvalBox(msg, "O3 approval"))		
			approved = to_approve;

		return approved;
	}


};

}

#endif // O3_C_O3_H
