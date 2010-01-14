var mode = o3.args[2];

var src1 = o3.cwd.get("o3_installer_header.bmp");
var src2 = o3.cwd.get("o3_installer_left.bmp");
var src3 = o3.cwd.get("../" + mode + "/npplugin.dll");
var src4 = o3.cwd.get("installer.js");
var src5 = o3.cwd.get("install.ico");
var tgt = o3.cwd.get("../" + mode + "/o3plugin.exe");

function checkFile(file) {
    if (!file.exists) {
        o3.out("file not found: " + file.path);
        return false;
    }
    return true;
}

checkFile(src1);
checkFile(src2);
checkFile(src3);
checkFile(src4);
checkFile(src5);
checkFile(tgt);

var builder = o3.resourceBuilder();
builder.addAsResource(src1);
builder.addAsResource(src2);
builder.addAsResource(src3);
builder.addAsResource(src4);
builder.addAsResource(src5);
builder.buildAndAppend(tgt); 