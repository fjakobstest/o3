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

o3.assert = function(pred) {
	if (!eval(pred))
		o3.print(pred + "\n");
}

var   string = "The quick brown fox jumps over the lazy dog";
var   hex    = "54 68 65 20 71 75 69 63 6B 20 62" + " " +
               "72 6F 77 6E 20 66 6F 78 20 6A 75" + " " +
               "6D 70 73 20 6F 76 65 72 20 74 68" + " " +
               "65 20 6C 61 7A 79 20 64 6F 67 00";
var   base64 = "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZwAA=";

hexBlob = o3.blob.fromHex;(hex);
o3.assert("hexBlob");
o3.assert("hexBlob.length = (hex.length + 1) / 3");
o3.assert("hexBlob.toString() == string");
o3.assert("hexBlob.toBase64() == base64");

base64Blob = o3.blob.fromBase64(base64);
o3.assert("base64Blob");
o3.assert("base64Blob.length = (base64.length - 2) * 3 / 4");
o3.assert("base64Blob.toString() == string");
o3.assert("base64Blob.toHex() == hex");

o3.print("YAY!"); 