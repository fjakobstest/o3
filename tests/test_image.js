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

o3.loadModule("image");
o3.loadModule("console");

o3.print("**** o3 image tests ****\n\n");

var bitmaptypes = new Array("bw", "argb");
for (var testcount=0;testcount<2;testcount++)
{
    var bmpt = bitmaptypes[testcount];
    
    o3.print("**** doing a test run for format: "+ bmpt + "\n");
    
    for (var test = 3;test<5;test++)
    {   
        var w = test * 30;
        var h = (10-test) * 30;
        o3.print("**** testing image with dimensions "+w+","+h+ "\n");
        
        var x = o3.image(w,h, bmpt);
        var color = 0xff0e5fa1;
        x.clear(color);
        var R = Math.min(w,h)/3;
        for (var p = 0;p<w;p++)
        {
            var xx = p;
            var yy = h/2+Math.sin((p*6.283)/w)*h/3;
        
            x.setPixel(xx,yy, 0xffffffff)
            x.line(0,0,w-p*5,p*5, 0x80ffff80)
        }
        
        o3.print("setting a pixel to 0xff607090 and getting it back...\n")
        x.setPixel(2,2, 0xff607090)
        color = x.getPixel(2,2);
        o3.print("result color: "+ color + "\n");
 

        o3.print("width: " + x.width() + "\n");
        o3.print("height: " + x.height() + "\n");
        o3.print("x: " + x.x() + "\n");
        o3.print("y: " + x.y() + "\n");
        o3.print("mode: " + x.mode() + "\n");
        
        o3.print("writing to disk..\n");
        x.savePng("test-" + bmpt + "-"+test+".png");
        o3.print("writing done..\n");
        
        
        o3.print("\n");
    }
}


function drawtocontext(ctx)
{
    ctx.fillStyle = "rgb(200,0,0)";
    ctx.fillRect (10, 10, 55, 50);

    ctx.fillStyle = "rgba(0, 0, 200, 0.5)";
    ctx.fillRect (30, 30, 55, 50);
    
    ctx.moveTo(20,40);
    ctx.lineTo(260,280);
    ctx.lineTo(20,280);
    ctx.closePath();
	
    ctx.moveTo(10,10);
    ctx.lineTo(300,300);
    ctx.lineTo(10,300);
    ctx.closePath();
    
//    ctx.fill();
    ctx.stroke();

	ctx.strokeStyle= "rgb(255,128,0)";
	ctx.beginPath();  
	ctx.moveTo(75,25);  
	ctx.quadraticCurveTo(25,25,25,62.5);  
	ctx.quadraticCurveTo(25,100,50,100);  
	ctx.quadraticCurveTo(50,120,30,125);  
	ctx.quadraticCurveTo(60,120,65,100);  
	ctx.quadraticCurveTo(125,100,125,62.5);  
	ctx.quadraticCurveTo(125,25,75,25);  
	ctx.stroke();  

}


var img = o3.image(300,300, "argb");
img.clear(0xffffffff);
drawtocontext(img);
img.savePng("canvastest.png");
        

'';