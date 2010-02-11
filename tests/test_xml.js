var xml_data = [];
xml_data.push(
"<p:project name=\"Javeline PlatForm\" xmlns:p=\"http://www.javeline.com/2008/Processor\">\n",
"    <p:settings\n",
"      buildnr  = \"{String(++cwd.get('jpfbuildnr.txt').data).pad('0', 4) &amp;&amp; ''}\"\n",
"      verbose  = \"2\"\n",
"      version  = \"1.0.{buildnr}.RC1\"\n",
"      name     = \"jpf_{version.replace(/\./g, '_')}\"\n",
"      out      = \"/Development/processor/processor/var/run/{name}\"\n",
"      cwd      = \"{cwd.path}\"\n",
"      tmp      = \"/Development/processor/processor/tmp\"\n",
"      platform = \"/Development/processor/processor/var/jpf\"\n",
"      release  = \"~\">\n",
"    </p:settings>\n",
"\n",
"    <p:process>\n",
"        <p:combine\n",
"          type     = \"script\"\n",
"          defines  = \"1\"\n",
"          strip    = \"1\"\n",
"          group    = \"jpf\"\n",
"          output   = \"{tmp}/jpf_release.js\"\n",
"          filehead = \"1\" />\n",
"\n",
"        <!--p:docgen input=\"{tmp}/jpf_release.js\" cache=\"{tmp}\">\n",
"            <p:xsd       output = \"{out}/docs/{name}.xsd\" />\n",
"            <p:html      output = \"{out}/docs/htmlart.html\" />\n",
"            <p:jsdebug   output = \"{out}/docs/jsdebug.html\" />\n",
"            <p:refguide  output = \"{out}/docs/refguide/{name}/\" />\n",
"            <p:scriptdoc output = \"{out}/docs/{name}.xml\" />\n",
"        </p:docgen-->\n",
"\n",
"        <!--p:encoder\n",
"          flags    = \"jsmode|codeinmap|cisproc|warncodeinstring|remap|gensemi\"\n",
"          debug    = \"leavenl|genline|\"\n",
"          fixedsym = \"{cwd}/jpf_sym.txt\"\n",
"          remapsym = \"{tmp}/{name}.map\"\n",
"          input    = \"{tmp}/{name}_combined.js\"\n",
"          output   = \"(out)/{name}_debug.js\" /-->\n",
"\n",
"        <!--p:copy\n",
"          group    = \"resources\"\n",
"          output   = \"{out}/{filename}\" />\n",
"\n",
"        <p:docgen input=\"{out}/{name}_debug.js\">\n",
"            <p:xsd       output = \"{out}/docs/{name}.xsd\" />\n",
"            <p:refguide  output = \"{out}/docs/refguide/{name}/\" />\n",
"            <p:scriptdoc output = \"{out}/docs/{name}.xml\" />\n",
"        </p:docgen>\n",
"\n",
"        <p:combine\n",
"          type   = \"xml\"\n",
"          root   = \"skins\"\n",
"          prefix = \"j\"\n",
"          xmlns  = \"http://www.javeline.com/2005/PlatForm\"\n",
"          group  = \"windows_skin\"\n",
"          output = \"{out}/win_skins.xml\" />\n",
"\n",
"        <p:targz\n",
"          input  = \"{out}\"\n",
"          output = \"{release}/{name}.tar.gz\" />\n",
"\n",
"        <p:zip\n",
"          input  = \"{out}\"\n",
"          output = \"{release}/{name}.zip\" />\n",
"\n",
"        <p:http />\n",
"        <p:svn />\n",
"        <p:s3 />\n",
"        <p:scp />\n",
"\n",
"        <p:unittest /-->\n",
"    </p:process>\n",
"\n",
"    <p:files>\n",
"        <p:node path=\"{platform}\" mask=\"*.js\" group=\"jpf\"> <!-- inheritable -->\n",
"            <p:node path=\"jpack_begin.js\" />\n",
"            <p:node path=\"jpf.js\" />\n",
"            <p:node path=\"core\" />\n",
"            <p:node path=\"elements\">\n",
"                <p:node path=\"_base\" />\n",
"            </p:node>\n",
"            <p:node path=\"jpack_end.js\" />\n",
"        </p:node>\n",
"\n",
"        <p:node path=\"{platform}\" group=\"resources\" recursive=\"false\">\n",
"            <p:node path=\"core/lib/offline/network_check.txt\" />\n",
"            <p:node path=\"core/lib/storage/jpfStorage.swf\" />\n",
"            <p:node path=\"elements/audio/null.mp3\" />\n",
"            <p:node path=\"elements/audio/soundmanager2.swf\" />\n",
"            <p:node path=\"elements/audio/soundmanager2_flash9.swf\" />\n",
"            <p:node path=\"elements/video/ClearOverPlayMute.swf\" />\n",
"            <p:node path=\"elements/video/FAVideo.swf\" />\n",
"            <p:node path=\"elements/video/wmvplayer.xaml\" />\n",
"        </p:node>\n",
"\n",
"        <!--p:node path=\"{platform}/skins/trunk\" group=\"windows_skin\" mask=\"*.xml\" >\n",
"            <p:node path=\"win2005/src\" />\n",
"        </p:node-->\n",
"    </p:files>\n",
"\n",
"    <p:defines defaults=\"defines.xml\">\n",
"        <p:define name=\"__JPFVERSION\" value=\"{version}\"/>\n",
"        <p:define name=\"__WITH_CDN\" value=\"1\" />\n",
"        <p:define name=\"__PACKAGED\" value=\"1\"/>\n",
"        <p:define name=\"__PROCESSED\" value=\"1\"/>\n",
"        <p:define name=\"__WITH_UNSAFE_XMLHTTP\" value=\"1\" />\n",
"        <!-- include all available cryptography classes -->\n",
"        <p:define name=\"__WITH_BASE64\" value=\"1\" />\n",
"        <p:define name=\"__WITH_BLOWFISH\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MD4\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MD5\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SHA1\" value=\"1\" />\n",
"        <p:define name=\"__WITH_RSA\" value=\"1\" />\n",
"        <p:define name=\"__WITH_BARRETT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_BIGINT\" value=\"1\" />\n",
"        <!-- include all available general options -->\n",
"        <p:define name=\"__WITH_ABSTRACTEVENT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_APP_DEFAULTS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_AUTH\" value=\"1\" />\n",
"        <p:define name=\"__WITH_BACKBUTTON\" value=\"1\" />\n",
"        <p:define name=\"__WITH_COOKIE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_CONTEXTMENU\" value=\"1\" />\n",
"        <p:define name=\"__WITH_CONVENIENCE_API\" value=\"1\" />\n",
"        <p:define name=\"__WITH_CSS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_CSS_BINDS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_DATE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_DATA_INSTRUCTIONS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_DRAGMODE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_DRAW\" value=\"0\" />\n",
"        <p:define name=\"__ENABLE_DRAW_CANVAS\" value=\"0\" />\n",
"        <p:define name=\"__ENABLE_DRAW_VML\" value=\"0\" />\n",
"        <p:define name=\"__WITH_VISUALIZER\" value=\"0\" />\n",
"        <p:define name=\"__WITH_ECMAEXT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_ENTITY_ENCODING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_EVENT_BUBBLING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_FLASH\" value=\"1\" />\n",
"        <p:define name=\"__WITH_FLOW\" value=\"1\" />\n",
"        <p:define name=\"__WITH_FOCUS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_WINDOW_FOCUS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_GRID\" value=\"1\" />\n",
"        <p:define name=\"__WITH_HOTKEY\" value=\"1\" />\n",
"        <p:define name=\"__WITH_HOTKEY_PROPERTY\" value=\"1\" />\n",
"        <p:define name=\"__WITH_HTML_PARSING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_HTML_POSITIONING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_HTTP_CACHE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_ICONMAP\" value=\"1\" />\n",
"        <p:define name=\"__WITH_INCLUDES\" value=\"1\" />\n",
"        <p:define name=\"__WITH_INLINE_DATABINDING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_JML_BINDINGS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_KEYBOARD\" value=\"1\" />\n",
"        <p:define name=\"__WITH_LANG_SUPPORT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_LOCKING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MODEL_VALIDATION\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MOUSESCROLL\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MULTISELECT_BINDINGS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_NAMESERVER\" value=\"1\" />\n",
"        <p:define name=\"__WITH_NS_SUPPORT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OPACITY_RUNTIME_FIX\" value=\"1\" />\n",
"        <p:define name=\"__WITH_PARTIAL_JML_LOADING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_PLANE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_POPUP\" value=\"1\" />\n",
"        <p:define name=\"__WITH_PRINTER\" value=\"1\" />\n",
"        <p:define name=\"__WITH_PROPERTY_BINDING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_QUERYAPPEND\" value=\"1\" />\n",
"        <p:define name=\"__WITH_REGISTRY\" value=\"1\" />\n",
"        <p:define name=\"__WITH_RESIZE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SCROLLBAR\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SILVERLIGHT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SKIN_CHANGE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SORTING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SPLITTERS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_TASKBAR_FLASHING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_TWEEN\" value=\"1\" />\n",
"        <p:define name=\"__WITH_UNDO_KEYS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_UTILITIES\" value=\"1\" />\n",
"        <p:define name=\"__WITH_VECTOR\" value=\"1\" />\n",
"        <!-- include all available JML Core objects -->\n",
"        <p:define name=\"__WITH_ACTIONTRACKER\" value=\"1\" />\n",
"        <p:define name=\"__WITH_COMPONENT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_CLASS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_WINDOW\" value=\"1\" />\n",
"        <p:define name=\"__WITH_XMLDATABASE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SMARTBINDINGS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SCRIPT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_APPSETTINGS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_IEPNGFIX\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SETTINGS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_RSB\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MODEL\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STATE\" value=\"1\" />\n",
"        <!-- include all available Local Storage objects -->\n",
"        <p:define name=\"__WITH_STORAGE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STORAGE_AIR\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STORAGE_AIR_FILE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STORAGE_AIR_SQL\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STORAGE_GEARS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STORAGE_HTML5\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STORAGE_FLASH\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STORAGE_DESKRUN\" value=\"1\" />\n",
"        <p:define name=\"__WITH_STORAGE_MEMORY\" value=\"1\" />\n",
"        <!-- include all available Offline mode objects -->\n",
"        <p:define name=\"__WITH_OFFLINE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_TRANSACTIONS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_MODELS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_MODEL\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_STATE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_QUEUE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_DETECTOR\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_APPLICATION\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_GEARS\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OFFLINE_STATE_REALTIME\" value=\"1\" />\n",
"        <!-- include all available Runtime Support objects (browsers) -->\n",
"        <p:define name=\"__SUPPORT_IE\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_IE5\" value=\"1\" />\n",
"        <p:define name=\"__WITH_POPUP_IE\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_GECKO\" value=\"1\" />\n",
"        <p:define name=\"__WITH_ELEMENT_FROM_POINT\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_SAFARI\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_SAFARI2\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_CHROME\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_OPERA\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_IE_API\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_GEARS\" value=\"1\" />\n",
"        <p:define name=\"__SUPPORT_JAW\" value=\"0\" />\n",
"        <!-- include all available Language Parsers -->\n",
"        <p:define name=\"__PARSE_GET_VARS\" value=\"1\" />\n",
"        <p:define name=\"__PARSER_JML\" value=\"1\" />\n",
"        <p:define name=\"__WITH_EXPLICIT_LOWERCASE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_SKIN_AUTOLOAD\" value=\"1\" />\n",
"        <p:define name=\"__WITH_HTML5\" value=\"1\" />\n",
"        <p:define name=\"__PARSER_XSLT\" value=\"1\" />\n",
"        <p:define name=\"__PARSER_JSLT\" value=\"1\" />\n",
"        <p:define name=\"__PARSER_JS\" value=\"1\" />\n",
"        <p:define name=\"__PARSER_XPATH\" value=\"1\" />\n",
"        <p:define name=\"__PARSER_XSD\" value=\"1\" />\n",
"        <p:define name=\"__PARSER_URL\" value=\"1\" />\n",
"        <!-- include all available Teleport classes -->\n",
"        <p:define name=\"__WITH_TELEPORT\" value=\"1\" />\n",
"        <p:define name=\"__TP_IFRAME\" value=\"1\" />\n",
"        <p:define name=\"__TP_SOCKET\" value=\"1\" />\n",
"        <p:define name=\"__TP_WEBDAV\" value=\"1\" />\n",
"        <p:define name=\"__TP_XMPP\" value=\"1\" />\n",
"        <p:define name=\"__TP_RPC\" value=\"1\" />\n",
"        <p:define name=\"__TP_RPC_CGI\" value=\"1\" />\n",
"        <p:define name=\"__TP_RPC_HEADER\" value=\"1\" />\n",
"        <p:define name=\"__TP_RPC_JPHP\" value=\"1\" />\n",
"        <p:define name=\"__TP_RPC_JSON\" value=\"1\" />\n",
"        <p:define name=\"__TP_RPC_REST\" value=\"1\" />\n",
"        <p:define name=\"__TP_RPC_SOAP\" value=\"1\" />\n",
"        <p:define name=\"__TP_RPC_XMLRPC\" value=\"1\" />\n",
"        <!-- include all available JML node types and JML features -->\n",
"        <p:define name=\"__WITH_JMLNODE\" value=\"1\" />\n",
"        <p:define name=\"__JWINDOW\" value=\"1\" />\n",
"        <p:define name=\"__WITH_ALIGNMENT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_ALIGNXML\" value=\"1\" />\n",
"        <p:define name=\"__WITH_ALIGN_TEMPLATES\" value=\"1\" />\n",
"        <p:define name=\"__WITH_ANCHORING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_CACHE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_DATABINDING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_DELAYEDRENDER\" value=\"1\" />\n",
"        <p:define name=\"__WITH_DOCKING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_DRAGDROP\" value=\"1\" />\n",
"        <p:define name=\"__WITH_EDITMODE\" value=\"0\" />\n",
"        <p:define name=\"__WITH_INTERACTIVE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_OUTLINE\" value=\"1\" />\n",
"        <p:define name=\"__WITH_JMLDOM\" value=\"1\" />\n",
"        <p:define name=\"__WITH_JMLDOM_XPATH\" value=\"1\" />\n",
"        <p:define name=\"__WITH_JMLDOM_W3C_XPATH\" value=\"1\" />\n",
"        <p:define name=\"__WITH_JMLDOM_FULL\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MEDIA\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MULTIBINDING\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MULTI_LANG\" value=\"1\" />\n",
"        <p:define name=\"__WITH_MULTISELECT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_PRESENTATION\" value=\"1\" />\n",
"        <p:define name=\"__WITH_RENAME\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_AUTORENAME\" value=\"1\" />\n",
"        <p:define name=\"__WITH_TRANSACTION\" value=\"1\" />\n",
"        <p:define name=\"__WITH_VALIDATION\" value=\"1\" />\n",
"        <p:define name=\"__WITH_VIRTUALVIEWPORT\" value=\"1\" />\n",
"        <p:define name=\"__WITH_XFORMS\" value=\"0\" />\n",
"        <p:define name=\"__WITH_XSD\" value=\"1\" />\n",
"        <!-- binding options -->\n",
"        <p:define name=\"__ENABLE_BINDING_JSLT\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_BINDING_XSLT\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_BINDING_METHOD\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_BINDING_EVAL\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_BINDING_MASKS\" value=\"1\" />\n",
"        <!-- include all rule transformation methods -->\n",
"        <p:define name=\"__ENABLE_BINDING_JSLT\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_BINDING_XSLT\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_BINDING_METHOD\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_BINDING_EVAL\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_BINDING_MASKS\" value=\"1\" />\n",
"        <!-- include all components -->\n",
"        <p:define name=\"__ENABLE_BUTTON_ACTIONS\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_WINDOW_WIDGET\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_TEXTBOX_MASKING\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_TEXTBOX_AUTOCOMPLETE\" value=\"1\" />\n",
"        <p:define name=\"__ENABLE_TABSCROLL\" value=\"1\" />\n",
"        <p:define name=\"__INC_ALL\" value=\"1\" />\n",
"    </p:defines>\n",
"\n",
"    <!--<p:include src=\"\" />-->\n",
"</p:project>");

diffNodes = function(node1, node2){
	if (node1.nodeName != node2.nodeName) return "different nodeNames: " + node1.nodeName + " != " + node2.nodeName;
	if (node1.nodeValue != node2.nodeValue) return "different nodeValues";
	if (node1.nodeType != node2.nodeType) return "different nodeTypes";
	if (node1.parentNode.nodeName != node2.parentNode.nodeName) return "different parent nodeNames";
	if (node1.childNodes.length != node2.childNodes.length) return "different child numbers";
	if (node1.firstChild.nodeName != node2.firstChild.nodeName) return "different firstChild names";
	if (node1.attributes.length != node2.attributes.length) return "different attribute numbers"
	return false;
}

diffNodesRec = function(node1, node2){
	var l, i, e, a, b;
	if (node1.nodeName != node2.nodeName) return "different nodeNames: " + node1.nodeName + " != " + node2.nodeName;
	if (node1.nodeValue != node2.nodeValue) return "different nodeValues";
	if (node1.nodeType != node2.nodeType) return "different nodeTypes";
//	if (node1.parentNode.nodeName != node2.parentNode.nodeName) return "different parent nodeNames";
	l = node1.childNodes.length;
	if (l != node2.childNodes.length) return "different child numbers";
	for (i=l-1; i>=0; i--) {
		if (e = diffNodesRec(node1.childNodes[i], node2.childNodes[i])) return e;
	}
	if (node1.attributes || node2.attributes) {
		l = node1.attributes.length
		if (l != node2.attributes.length) return "different attribute numbers"
		for (i=l-1; i>=0; i--) {
			a = node1.attributes[i];
			b = node2.attributes[i];
			if ( (a.name != b.name) || (a.value != b.value) ) return "different attributes: [" + a.name + ", " + a.value + "] != [" + b.name + ", " + b.value + "].";
		}
	}
	return false;
}
var failed = function(message){
	return "ERROR: " + test + ' ' + v + ' : ' + message + "\n";
}

var test = 'XML',
	xml_text = xml_data.join(""),
	mxml = o3.xml.parseFromString(xml_text),
	v,
	result, 
	last = o3.argc > 1 ? o3.argv[1] : null, 
	foundLast = last ? false : true, 
	stdErr = o3.stdErr,
	tests = {	
	//node types : chardata, document, element
	'xmlNodeBasic':function(){			
			if (mxml.nodeType != 9) return failed("Document node should have a XML_DOCUMENT_NODE type (9)");
			var node = mxml.firstChild;
			if (node.nodeType != 1) return failed("First child should have a XML_ELEMENT_NODE type (1)");			
		    var str = node.nodeName;
			if (mxml.ownerDocument.type == 9) return failed("(on doc. node) ownerDocument does not return a document");
			if (node.ownerDocument.type == 9) return failed("(on elem. node) ownerDocument does not return a document");
			if (str != "project") return failed("name of the root node should be [p:project] but it is: [" + str + "]");
			node = node.attributes[0];
			if (node.ownerDocument.type == 9) return failed("(attr. node) ownerDocument does not return a document");
			if (node.nodeType != 2) return failed("Attribute node should have a XML_ATTRIBUTE_NODE type (2)");
			str = node.nodeValue;						
			if (str != "Javeline PlatForm") return failed("name of the first attribute should be [Javeline PlatForm] but it is: [" + str + "]");
            node.nodeValue = "JP";
			str = node.nodeValue;
			if (str != "JP") return failed("new value of attribute should be: [JP] but it is: [" + str + "]");			                        

		return true;
	},
	'xmlNodeTraverse':function(){		
            var childern, parent, str, leafnode,i;
			if (! mxml.hasChildNodes) return failed("Document node should have children...");
			parent = mxml.firstChild;
			if (! parent.hasChildNodes) return failed("First child of the doc element should have children...");
			children = parent.childNodes;
			i = children.length;
			if (parent.firstChild.name != children[0].name) return failed("First child is not consistent (children[0] != firstChild)");			
            if (parent.lastChild.name != children[i-1].name) return failed("Last child is not consistent (children[length - 1] != lastChild)");								
            if (parent.firstChild.nextSibling.name != children[1].name) return failed("First child is not consistent (children[1] != firstChildnextSibling)");			
            if (parent.lastChild.previousSibling.name != children[i-2].name) return failed("Last child is not consistent (children[length - 2] != lastChild.previousSibling)");			
			str = parent.name;
			i--;           
            for (; i>0; --i) {
				if (children[i].parentNode.name != str) return failed("child " + i + ": parent node is incorrect");
				if (! children[i].hasChildNodes) 
					if (children[i].childNodes.length != 0) return failed("child " + i + ": hasChildNode is inconsistent");					
			}         
		return true;
	},
	'attributes':function(){
			var node, attr,attr2, attributes, str, attrname, value, i = 0, name;
			attrname = "verbose";		
			node = mxml.firstChild.childNodes[1];
			attributes = node.attributes;
			var settings = [];
			settings["buildnr"]  = "{String(++cwd.get('jpfbuildnr.txt').data).pad('0', 4) && ''}"
			settings["verbose"]  = "2"
			settings["version"]  = "1.0.{buildnr}.RC1"
			settings["name"]     = "jpf_{version.replace(/\./g, '_')}"
			settings["out"]      = "/Development/processor/processor/var/run/{name}"
			settings["cwd"]      = "{cwd.path}"
			settings["tmp"]      = "/Development/processor/processor/tmp"
			settings["platform"] = "/Development/processor/processor/var/jpf"
			settings["release"]  = "~";		
            for (i = attributes.length - 1; i>=0; --i) {
            name = attributes[i].name;
				if (settings[name] != attributes[i].value) 
				    return failed(i + ". attribute on element node \"settings\" is: \n[" 
				        + name + ":" + attributes[i].value + "] instead of: \n["
				        + name + ":" + settings[name] + "]");
			}
			attr = attributes.getNamedItem(attrname);
            attr2 = node.getAttributeNode(attrname);
			if (attr.name != attrname)	return failed("attribute [" + attrname + "] could not be found");
            if (attr.value != 2)	    return failed("attribute [" + attrname + "] has invalid value, it should be [2] but it is: [" + attr.value +"]");
            if (attr2.name != attrname)	return failed("attribute [" + attrname + "] could not be found (via ElementNode)");
            if (attr2.value != 2)	    return failed("attribute [" + attrname + "] has invalid value (via ElementNode), it should be [2] but it is: [" + attr2.value +"]");					
            if (node.getAttribute(attrname) != 2)	    return failed("attribute [" + attrname + "] has invalid value (via ElementNode.getAttribute), it should be [2] but it is: [" + node.getAttribute("verbose") +"]");				
			node.setAttribute(attrname, 5);
			attr = attributes.getNamedItem(attrname);           
			attr2 = node.getAttributeNode(attrname);
			if (attr.name != attrname)	return failed("attribute [" + attrname + "] could not be found after its value has been changed");
			if (attr.value != 5)	    return failed("attribute [" + attrname + "] has invalid value, it has been changed to [5] but it is: [" + attr.value +"]");			
			if (attr2.value != 5)	    return failed("attribute [" + attrname + "] has invalid value (via ElementNode), it has been changed to [5] but it is: [" + attr2.value +"]");			
			if (node.getAttribute(attrname) != 5)	    return failed("attribute [" + attrname + "] has invalid value (via ElementNode.getAttribute), it has been changed to [5] but it is: [" + node.getAttribute("verbose") +"]");							
            node.removeAttribute(attrname);
			attr = attributes.getNamedItem(attrname);		
            if (attr)	return failed("attribute [" + attrname + "] can be found after it has been removed");		
            if (node.getAttributeNode(attrname)) return failed("attribute [" + attrname + "] can be found after it has been removed (via getAttributeNode)");		
            if (node.getAttribute(attrname)) return failed("attribute [" + attrname + "] can be found after it has been removed (via getAttribute)");	
		return true;
	},
	'xmlNodeModify':function(){
			var node, removed, project, i, e;
			project = mxml.firstChild;
			node = project.childNodes[1]; //settings
            removed = project.removeChild(node);
			project.insertBefore(removed, project.childNodes[3]);
			if ((project.childNodes[0].nodeName != "text")
			 || (project.childNodes[1].nodeName != "text")
			 || (project.childNodes[2].nodeName != "process")
			 || (project.childNodes[3].nodeName != "settings"))
				return failed("removing node \"settings\" and adding it back after node \"process\" failed.");
			
			node = project.childNodes[2].cloneNode(true);
			project.replaceChild(node, project.firstChild);
			if (e = diffNodes(project.firstChild, project.childNodes[2])) 
				return failed("Cloning node \"process\" and replacing the first text node with it failed. " + e);
			
            node = project.childNodes[2].cloneNode(true);
			project.childNodes[1].replaceNode(node);
			if (e = diffNodes(project.childNodes[1], project.childNodes[2])) 
				return failed("Cloning node \"process\" and replacing the second text node with it failed. " + e);
			
			node = project.childNodes[3].cloneNode(true);
			project.appendChild(node);
			if (e = diffNodes(project.lastChild, project.childNodes[3])) 
				return failed("Cloning node \"settings\" and appending it to node \"project\" failed. " + e);	
		return true;	
	},
	'XPATH':function(){
			var node, selectedNodes, single, i, l;
			node = mxml.firstChild;
			selectedNodes = node.selectNodes("//p:define");
			l = selectedNodes.length;
			if (selectedNodes[0].getAttribute("name") != "__JPFVERSION") 
				return failed("'name' attribute for the first selected node should be [__JPFVERSION] but was: [" + selectedNodes[0].getAttribute("name") + "]");
			if (selectedNodes[77].getAttribute("name") != "__WITH_XMLDATABASE") 
				return failed("'name' attribute for the first selected node should be [__WITH_XMLDATABASE] but was: [" + selectedNodes[77].getAttribute("name") + "]");
			if (selectedNodes[l-2].getAttribute("name") != "__ENABLE_TABSCROLL") 
				return failed("'name' attribute for the first selected node should be [__ENABLE_TABSCROLL] but was: [" + selectedNodes[l-2].getAttribute("name") + "]");	
			
			single = node.selectSingleNode("//p:define");
			if (single.getAttribute("name") != "__JPFVERSION")
				return failed("'name' attribute for selectSingleNode should be [__JPFVERSION] but was: [" + single.getAttribute("name") + "]");
		return true;
	}/*,
	'serialize':function(){        
			var str = mxml.firstChild.xml;			
			var mxml2 = o3.xml.parseFromString(str);			
			if (e = diffNodesRec(mxml.firstChild, mxml2.firstChild)) return failed(e);
		return true;	
	}*/
}

for (v in tests) {
    if(foundLast) {
		o3.print(v + '\n');	
		result = tests[v]().toString();
		if (result != 'true')
			stdErr.write(result);
	}
	else {
		foundLast = (v == last);
	}
}

