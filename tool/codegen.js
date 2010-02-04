var includeTrace = false, 
    log = false, 
    immLog = false, 
    logFileName = 'codegenLog.txt',
    errFileName = 'codegenErr.txt';

function include(file) {
    if (includeTrace)
        o3.print('include: ' + file + '\n');
    var data = o3.cwd.get(file).data;
    if (!data.length && includeTrace)
        o3.print('open file failed!');
    else        
        eval(data);        
    
    if (includeTrace)    
        o3.print('include finished: ' + file + '\n');
}

function fileWriter(fileName) {
    return function(str) {
        o3.cwd.get('../' + fileName).data = str;
    }
}

include("../o3_Reporter.js");
include("../o3_FileHandler.js");
include("../o3_Parser.js");
include("../o3_Generator.js");

Reporter.immediate = immLog;

var file,args = o3.args;
if (args.length > 1) {
    file = o3.fs.get(args[1]);
    if (file.exists) 
        FileHandler.scanFiles(file);            
    else
        Reporter.generalError('File does not exists: ', file.path, '.\n');        
} 
else {
    Reporter.generalError('No starting dir was specified.\n');
}

if (!Reporter.immediate && log) 
    Reporter.dumpLogs();

Reporter.logWriter = fileWriter(logFileName);
Reporter.errorWriter = fileWriter(errFileName);    
Reporter.dumpLogs();
Reporter.dumpErrors();

