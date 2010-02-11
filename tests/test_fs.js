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
o3.loadModule('console');
o3.loadModule('fs');

var setup = function(){
	root = o3.cwd;
	wd_name = "testfs";
	wd = root.get(wd_name);
	wd.createDir();
	if(wd.valid && wd.exists)
		return true;
	else return failed("can not create test folder");	
}

var teardown = function(){
	wd.remove(true);
	if (wd.exists)
		return failed("can not delete test folder");
	return true;	
}


var tests = {		
	'validity':function(){	

		if ( ! wd.valid) return failed("working dir is not valid");
		if ( ! wd.exists) return failed("working dir does not exist");
		
		var node = wd.get("notafile.ext");
		if ( ! node.valid) return failed("new node is not valid");
		if ( node.exists) return failed("new node seems to exist but it should not");
		
		node = root.parent;
		if ( node.valid) return failed("parent of the root node should not be valid");
		return true;
	},
	'type':function(){
		if ( ! wd.isDir) return failed("working dir is not a folder?");
		if ( wd.isFile) return failed("working dir is is a file but should be a folder");
		if ( wd.isLink) return failed("working dir is is a link but should be a folder");
		
		var node = wd.get("filea.ext");
		node.createFile();
		if ( ! node.exists ) return failed("could not create filea.ext");
		if ( ! node.isFile ) return failed("filea.ext is not a file");
		if ( node.isDir ) return failed("filea.ext should not be a folder");
		if ( node.isLink ) return failed("filea.ext should not be a link");
		
		node.remove();
		if ( node.exists ) return failed("could not delete filea.ext");
		if ( node.isFile ) return failed("filea.ext should have been deleted");
		if ( node.isDir ) return failed("filea.ext should not be a folder, and should have been deleted");
		if ( node.isLink ) return failed("filea.ext should not be a link, and should have been deleted");		
		return true;
	},
	'datamanip':function(){
		//str mode
		var node = wd.get("content.txt");
		var content = "This is some content.";
		node.data = content;
		if ( ! node.exists ) return failed("could not create content.txt");
		var readback = node.data;
		if ( readback != content ) 
			return failed("(str mode) string written to the file was: [" + content + "] but the result of reading the file is : [" + readback + "]"); 
		
		//stream mode read
		var stream = node.open("r");
		var res = stream.read(3);
		stream.flush();
		if (res != content.substring(0,3)) {
			stream.close();
			return failed("first 3 chars of the data in the file are not correct. Content was : " + content + " Read back result: " + res);
		}
		
		stream.pos = 3;
		res = stream.read(1);
		stream.flush();
		if (res != content.charAt(3)) {
			stream.close();
			return failed("4th character of the data in the file is not correct. Content was: " + content + " Read back result: " + res);	
		}
		
		stream.pos = 0;
		res = "";
		while (!stream.eof)	{
			res += stream.read(1);
			stream.flush();
		}
		if (res != content) {
			stream.close();
			return failed("(stream mode) string written to the file was: [" + content + "] but the result of reading the file is : [" + res + "]"); 
		}
		stream.close();
		
		//stream mode write
		stream = node.open("w");
		stream.pos = 1;
		stream.write("H");
		stream.flush();
		stream.close();
		stream = node.open("r");
		stream.pos = 1;
		res = stream.read(1);
		stream.flush();
		stream.close();
		if (res != "H"){
			return failed("after modification the 2nd char should be: [H] , but it is :[" + res + "]"); 
		}
		
		return true;
	},
	'creation':function(){
		var node = wd.get("file.ext");
		node.createFile();
		if ( ! node.valid ) return failed("could not create file.ext, node is invalid");
		if ( ! node.exists ) return failed("could not create file.ext, node does not exist");
		if ( ! node.isFile ) return failed("could not create file.ext, node is not a file");
		
		node = wd.get("Fodler");
		node.createDir();
		if ( ! node.valid ) return failed("could not create Folder, node is invalid");
		if ( ! node.exists ) return failed("could not create Folder, node does not exist");
		if ( ! node.isDir ) return failed("could not create Folder, node is not a folder");

		node = wd.get("Fodler2/Folder3/Folder4/tmp.txt");
		try{ var a = node.data; return failed("Reading from a file that does not exist should report an error! " + a)}
		catch(e){}
		node.data = "this is a test";
		if (node.data != "this is a test") return failed("recursive directory creation has failed");
		return true;
	},	
	'reposition':function(){
		var node = wd.get("torep.txt");
		node.data = "content";
		var folder = wd.get("folder");
		var dest = folder.get("destfile");
		folder.createDir();
		node.copy(dest);
		if (dest.data != "content") return failed("could not copy file");
		//var dest2 = folder.get("destfile");
		var dest2 = dest.move(wd);
		if (dest2.data != "content") return failed("could not move file");		
		//if (dest.exist) return failed("after moving a file the source remained");
		return true;
	},
	'list':function(){
		var node = wd.get("tolist");
		node.createDir();
		node.get("first").createFile();
		node.get("second").createFile();
		node.get("third").createFile();
		node.get("fourth").createDir();
		var children = node.children;
		var length = children.length;
		if (length != 4) return failed("\'tolist\' folder should contain 4 children but has: " + length);		
		for (var i = 0; i < length; i++){
			if ( ! children[i].exists ) return failed("child " + i + " does not exist");
			if (children[i].isDir) children[i].get("childFile").createFile();		
		}
		if( ! node.get("fourth/childFile").isFile) return failed("childFile could not be created"); 		
		return true;
	},
	'navigation':function(){
		//dir tree to create and navigate on
		//		dir1
		//			dir1_1
		//				dir1_1_1
		//					file1_1_1a
		//					file1_1_1b
		//				file1_1a
		//				file1_1b
		//			dir1_2
		//				file1_2a
		//				file1_2b
		//			file1a
		//			file1b
		//		dir2
		//			.file2a
		//			.file2b
		wd.get("dir1").createDir();
		wd.get("dir1/dir1_1").createDir();
		wd.get("dir1/dir1_1/dir1_1_1").createDir();
		wd.get("dir1/dir1_1/dir1_1_1/file1_1_1a").createFile();
		wd.get("dir1/dir1_1/dir1_1_1/file1_1_1b").createFile();
		wd.get("dir1/dir1_1/file1_1a").createFile();
		wd.get("dir1/dir1_1/file1_1b").createFile();
		wd.get("dir1/dir1_2").createDir();
		wd.get("dir1/dir1_2/file1_2a").createFile();
		wd.get("dir1/dir1_2/file1_2b").createFile();		
		wd.get("dir1/file1a").createFile();
		wd.get("dir1/file1b").createFile();		
		wd.get("dir2").createDir();
		wd.get("dir2/.file2a").createFile();
		wd.get("dir2/.file2b").createFile();
		
		var wd_path = wd.path;
		if (root.get(wd_path).name != wd_name) return failed("getting to the working directory by its path failed from root");
		if (wd.get("/" + wd_path).name != wd_name) return failed("getting to the working directory by its path failed from itself");
		if (wd.get("dir1/dir2/../../dir2/.file2a").name != ".file2a") return failed("path test1 failed");
		if (wd.get("./dir1/./dir2/../../dir2/.file2a").name != ".file2a") return failed("path test2 failed");
		if (wd.get("dir1").get("..").name != wd_name) return failed("path \"..\" does not work");
		var tmpname = wd.get("dir1/dir1_1/dir1_1_1").children[0].parent.name;
		if ( tmpname != "dir1_1_1") return failed("path test3 failed: " + tmpname);
		if (root.parent.valid) return failed ("the parent folder of the file root node should not be reachable (by prop parent)");
		//if (root.get("..").valid) return failed ("the parent folder of the file root node should not be reachable (by get(\"..\"))");
		
		return true;
	},
    'onchange' : function(){
        var node = wd.get("changeme.txt");        
        node.data = "unchanged"
        var changed = false, dirchanged = false;
        node.onchange = function(this_node) {
            changed = true;
            this_node.onchange = 0;
        }
        
        wd.onchange = function(this_node) {
            dirchanged = true;
            this_node.onchange = 0;
        }
        o3.wait(10);
        node.data = "changed";
        o3.wait(1);
        if (!changed)
            return failed("File change notification failed.");
        if (!dirchanged)
            return failed("Dir change notification failed.");
            
        changed = false;
        node.data = "changed2"
        o3.wait(1);
        if (changed)
            return failed("onchange notification reset failed");
 /*  TOFIX:     
        node = wd.get("2changeA");
        var counterA = 0, 
            counterB = 0, 
            str, 
            node2 = wd.get("2changeB");
            
        node.data = "Wait";
        node2.data = "Start";
        
        node.onchange = function(this_node) {            
            o3.print('A\n');
			if (10 == ++counterA)
                this_node.onchange = 0;    
        }

        node2.onchange = function(this_node) {            
            o3.print('B\n');
			if (10 == ++counterB)
                this_node.onchange = 0;    
        }
        
        for(var i=0; i<10; i++) {
			o3.print('wait\n');
			o3.wait(100);			
			node.data = i;
			node2.data = i;
			o3.wait(100);
			if (counterB==10 && counterA==10) {
				break;
			}	
        }

        if (counterB!=10 || counterA!=10) {
			o3.print(counterA + '\n');
			o3.print(counterB + '\n');
			return failed("onchange notification test with two listeners failed");
		}
*/		
        return true;    
    }    
	
}

var failed = function(message){
	return "ERROR: " + test + ' ' + v + ' : ' + message + "\n";
}

var v,
	wd,
	result, 
	test = 'fs';
	last = o3.argc > 1 ? o3.argv[1] : null, 
	foundLast = last ? false : true, 
	stdErr = o3.stdErr;
	
for (v in tests) {
    if(foundLast) {
		o3.print(v + '\n');	
		result = setup();
		if (result != true)
			stdErr.write(result);
		
		result = tests[v]();
		if (result != true)
			stdErr.write(result);
		
		result = teardown();
		if (result != true)
			stdErr.write(result);
	}
	else {
		foundLast = (v == last);
	}
}

