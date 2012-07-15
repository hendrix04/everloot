    function toggle_visibility(id) {

       var e = document.getElementById(id);

       if(e.style.display == 'block')

          e.style.display = 'none';

       else

          e.style.display = 'block';

    }

//-->

<!-- Copyright 2006,2007 Bontrager Connection, LLC

// http://bontragerconnection.com/ and http://www.willmaster.com/

// Version: July 28, 2007

// Modified by Dethdlr on 24 Jan 2012 to keep divs on the screen when they are near the bottom or right.

var cX = 0; var cY = 0; var rX = 0; var rY = 0;

function UpdateCursorPosition(e){ cX = e.pageX; cY = e.pageY;}

function UpdateCursorPositionDocAll(e){ cX = event.clientX; cY = event.clientY;}

if(document.all) { document.onmousemove = UpdateCursorPositionDocAll; }

else { document.onmousemove = UpdateCursorPosition; }

function AssignPosition(d) {

if(self.pageYOffset) {

	rX = self.pageXOffset;

	rY = self.pageYOffset;

	}

else if(document.documentElement && document.documentElement.scrollTop) {

	rX = document.documentElement.scrollLeft;

	rY = document.documentElement.scrollTop;

	}

else if(document.body) {

	rX = document.body.scrollLeft;

	rY = document.body.scrollTop;

	}

if(document.all) {

	cX += rX; 

	cY += rY;

	}
	

var iebody=(document.compatMode && document.compatMode!="BackCompat")? document.documentElement : document.body

var docwidth=(window.innerWidth)? window.innerWidth-15 : iebody.clientWidth-15;
var docheight=(window.innerHeight)? window.innerHeight-18 : iebody.clientHeight-15;

var scrollLeft=window.pageXOffset? window.pageXOffset : iebody.scrollLeft
var scrollTop=window.pageYOffset? window.pageYOffset : iebody.scrollTop

cX=(cX+d.offsetWidth-scrollLeft>docwidth)? cX-d.offsetWidth : cX 
cY=(cY+d.offsetHeight-scrollTop>docheight)? cY-d.offsetHeight-18 : cY 

cX=(cX<1)? 1: cX;
cY=(cY<1)? 1: cY;

d.style.left = (cX+10) + "px";

d.style.top = (cY+10) + "px";

}

function HideContent(d) {

if(d.length < 1) { return; }

document.getElementById(d).style.display = "none";

}

function ShowContent(d) {

if(d.length < 1) { return; }

var dd = document.getElementById(d);

dd.style.display = "block";

AssignPosition(dd);


}

function ReverseContentDisplay(d) {

if(d.length < 1) { return; }

var dd = document.getElementById(d);

AssignPosition(dd);

if(dd.style.display == "none") { dd.style.display = "block"; }

else { dd.style.display = "none"; }

}