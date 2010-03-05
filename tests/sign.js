// Configuration settings

var	key_path = "C:\\Development\\o3modules\\tests\\prv_key.h",
	in_path  = "C:\\Development\\o3modules\\tests\\license.txt",
	out_path = "C:\\Development\\o3modules\\tests\\license.out",
	check_path = "C:\\Development\\o3modules\\tests\\license.bin1",
	check_path2 = "C:\\Development\\o3modules\\tests\\license.bin2",

// Components
	fs     = o3.fs(),

// Get private key
	data = fs.get(key_path).data,

	mod     = data.match(/.*mod.*{(.*)}/)[1],
	prv_exp = data.match(/.*prv_exp.*{(.*)}/)[1];

function dehexify(str) {
	return str.replace(/\s|\t|\n/g, "")
		  .replace(/0x/g, "")
                  .replace(/,/g, " ")
}

mod     = o3.blob.fromHex(dehexify(mod));
prv_exp = o3.blob.fromHex(dehexify(prv_exp));

// Sign input file using private key
var text   = fs.get(in_path).data,
	digest = o3.sha1.hash(text),
	enc;

enc = o3.rsa.encrypt(digest, mod, prv_exp);	
digest = enc.toBase64();

fs.get(check_path).blob = enc;
fs.get(check_path2).blob = o3.blob.fromBase64(digest);

var valid = digest

// Write signed data to output file
fs.get(out_path).data = text + "\n\n" + digest;