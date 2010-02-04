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
#ifndef O3_C_FS1_BASE_H
#define O3_C_FS1_BASE_H

namespace o3 {

o3_cls(cFs1Base);

struct cFs1Base : cScr, iFs {
    enum Type {
        TYPE_INVALID,
        TYPE_DIR,
        TYPE_FILE,
        TYPE_LINK
    };    

    siWeak m_ctx;
    siScr m_onchange;

    o3_begin_class(cScr)
        o3_add_iface(iFs)
    o3_end_class()

    o3_glue_gen()

    o3_enum("Type", INVALID, DIR, FILE, LINK);

    virtual o3_get bool valid() = 0;

    virtual o3_get bool exists() = 0;

    virtual o3_get Type type() = 0;

    virtual o3_get bool isDir()
    {
        o3_trace3 trace;

        return type() == TYPE_DIR;
    }

    virtual o3_get bool isFile()
    {
        o3_trace3 trace;

        return type() == TYPE_FILE;
    }

    virtual o3_get bool isLink()
    {
        o3_trace3 trace;

        return type() == TYPE_LINK;
    }

    virtual o3_get int64_t accessedTime() = 0;

    virtual o3_get int64_t modifiedTime() = 0;

    virtual o3_get int64_t createdTime() = 0;

    virtual o3_get size_t size() = 0;

    virtual o3_get Str path() = 0;

    virtual o3_get Str name()
    {
        o3_trace3 trace;
        Str path = this->path();
        const char* path1 = path;
        const char* name = path1 + 1;

        while (*path1++)
            if (*path1 == '/')
                name = path1 + 1;
        return name;
    }

    virtual o3_set Str setName(const char* name, siEx*)
    {
        o3_trace3 trace;
        Str path = this->path();
        char* path1 = path;
        char* name1 = path1 + 1;

        while (*path1++)
            if (*path1 == '/')
                name1 = path1 + 1;
        *name1 = 0;
        move(get(path + name));
        return name;
    }

    virtual o3_fun siFs get(const char* path) = 0;

    virtual o3_get siFs parent()
    {
        o3_trace3 trace;

        return get("..");
    }

    virtual o3_get bool hasChildren() = 0;

    virtual o3_fun tVec<Str> scandir(const char* path) = 0;

    virtual o3_get tVec<siFs> children() = 0;

    virtual o3_fun bool createDir() = 0;

    virtual o3_fun bool createFile() = 0;

    virtual o3_fun bool createLink(iFs* to) = 0;

    virtual o3_fun bool remove(bool deep = true) = 0;

    virtual o3_fun siFs copy(iFs* to)
    {
        o3_trace3 trace;
        scFs1Base to1 = (cFs1Base*) to;
        tVec<siFs> nodes;

        switch (type()) {
        case TYPE_DIR:
            to1->createDir();
            nodes = children();
            for (size_t i = 0; i < nodes.size(); ++i) 
                to1->copy(to1->get(((cFs1Base*) nodes[i].ptr())->name()));
	    	break;
    	case TYPE_FILE:
            if (to1->isDir())
                to1 = (cFs1Base*) to1->get(name()).ptr();
            to1->setBlob(blob());
		    break;
        default:
            return 0;
	    }
        return to1; 
    }

    virtual o3_fun siFs move(iFs* to)
    {
        // TODO: since the exceptions are removed from the fs methods for some reason
        // again, there is no way to find out here if the copy went alright or not
        // 1., if the copy failed, and the remove succeeds we lost the file...
        // 2., if it was a dir some copies can fail while the rest succeeds, so 
        // only those files/subdirs should be removed that has been copied successfully
        // conclusion: it needs to be reimplemented properly ASAP 

        o3_trace3 trace;

        siFs ret = copy(to);
        remove();
        return ret;
    }

    virtual o3_fun siStream open(const char* mode, siEx* ex = 0) = 0;

    virtual o3_get bool canRead()
    {
        o3_trace3 trace;

        return open("r") ? true : false;
    }

    virtual o3_get bool canWrite()
    {
        o3_trace3 trace;

        return open("a") ? true : false;
    }

    virtual o3_get Buf blob()
    {
        o3_trace3 trace;
        siStream stream = open("r");

        return stream ? Buf(stream.ptr()) : Buf();
    }

    virtual o3_set Buf setBlob(const Buf& buf)
    {
        o3_trace3 trace;
        siStream stream = open("w");

        if (!stream)
            return Buf();
        stream->write(buf.ptr(), buf.size());
        return buf;
    }

    virtual o3_set Buf setBlob(iStream* stream)
    {
        o3_trace3 trace;

        return setBlob(Buf(stream));
    }

    virtual o3_get Str data()
    {
        o3_trace3 trace;

        return blob();
    }

    virtual o3_set Str setData(const Str& str)
    {
        o3_trace3 trace;
        Buf buf(str);

        if (buf.size() > 0)
            buf.resize(buf.size() - sizeof(char));
        return setBlob(buf);
    }

    virtual o3_get siScr onchange()
    {
        o3_trace3 trace;

        return m_onchange;
    }

    virtual o3_set siScr setOnchange(iCtx* ctx, iScr* onchange)
    {
        o3_trace3 trace;

        m_ctx = ctx;
        if (m_onchange)
            stopListening();
        if (m_onchange = onchange)
            startListening();
        return m_onchange;
    }

    virtual o3_get siStream fopen(const char* path, const char* mode)
    {
        o3_trace3 trace;

        return get(path)->open(mode);
    }

    virtual o3_get size_t fseek(iStream* stream, size_t pos)
    {
        o3_trace3 trace;

        return stream->setPos(pos);
    }

    virtual o3_get Str fread(iStream* stream, size_t size)
    {
        o3_trace3 trace;

        return Str(Buf(stream, size)); 
    }

    virtual o3_get size_t fwrite(iStream* stream, const Str& str)
    {
        o3_trace3 trace;

        return stream->write(str.ptr(), str.size());
    }

    virtual o3_get bool fflush(iStream* stream)
    {
        o3_trace3 trace;

        return stream->flush();
    }

    virtual o3_get bool fclose(iStream* stream)
    {
        o3_trace3 trace;

        return stream->close();
    }

    virtual void startListening() = 0;

    virtual void stopListening() = 0;
};

}

#endif // O3_C_FS1_BASE_H
