/*

Copyright (c) 2002 NuSphere Corporation

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

If you have any questions or comments, please email:

Dietrich Ayala
dietrich@ganx4.com
http://dietrich.ganx4.com/nusoap

NuSphere Corporation
http://www.nusphere.com

*/


//methods used in nusoap.php file under function webDescription()

// POP-UP CAPTIONS...
    function lib_bwcheck(){ //Browsercheck (needed)
        this.ver=navigator.appVersion
        this.agent=navigator.userAgent
        this.dom=document.getElementById?1:0
        this.opera5=this.agent.indexOf("Opera 5")>-1
        this.ie5=(this.ver.indexOf("MSIE 5")>-1 && this.dom && !this.opera5)?1:0;
        this.ie6=(this.ver.indexOf("MSIE 6")>-1 && this.dom && !this.opera5)?1:0;
        this.ie4=(document.all && !this.dom && !this.opera5)?1:0;
        this.ie=this.ie4||this.ie5||this.ie6
        this.mac=this.agent.indexOf("Mac")>-1
        this.ns6=(this.dom && parseInt(this.ver) >= 5) ?1:0;
        this.ns4=(document.layers && !this.dom)?1:0;
        this.bw=(this.ie6 || this.ie5 || this.ie4 || this.ns4 || this.ns6 || this.opera5)
    return this
    
    }
    
    var bw = new lib_bwcheck()
    //Makes crossbrowser object.
    function makeObj(obj){
        this.evnt=bw.dom? document.getElementById(obj):bw.ie4?document.all[obj]:bw.ns4?document.layers[obj]:0;
        if(!this.evnt) return false
        this.css=bw.dom||bw.ie4?this.evnt.style:bw.ns4?this.evnt:0;
        this.wref=bw.dom||bw.ie4?this.evnt:bw.ns4?this.css.document:0;
        this.writeIt=b_writeIt;
        
    return this
    }
    
    // A unit of measure that will be added when setting the position of a layer.
    //var px = bw.ns4||window.opera?"":"px";
    function b_writeIt(text){
        if (bw.ns4){
            this.wref.write(text);this.wref.close()
        }
        else this.wref.innerHTML = text
    }

    //Shows the messages
    var oDesc;
    function popup(divid){
        if(oDesc = new makeObj(divid)){
            oDesc.css.visibility = "visible"
        }
    }
    
    function popout(){ // Hides message
        if(oDesc) oDesc.css.visibility = "hidden"
    }