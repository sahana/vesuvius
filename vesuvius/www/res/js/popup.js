/**
 * @name         Sahana Popup Javascript
 * @version      1.1
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0408
 */

// store variables to control where the popup will appear relative to the cursor position
// positive numbers are below and to the right of the cursor, negative numbers are above and to the left
var xOffset = 30;
var yOffset = -5;

function showPopup(targetObjectId, eventObj, HelpId) {
	document.getElementById('help_popup').innerHTML = '';
	document.getElementById('help_popup').innerHTML = help_arr[HelpId];
	var notIE = true;

	var IE6 = (navigator.appVersion.indexOf('MSIE 6.')==-1) ? false : true;
	var IE7 = (navigator.appVersion.indexOf('MSIE 7.')==-1) ? false : true;
	var IE8 = (navigator.appVersion.indexOf('MSIE 8.')==-1) ? false : true;
	if(IE6 || IE7 || IE8) {
		var ie = explode('<br>', help_arr[HelpId]);
		alert(ie[1]);
		notIE = false;
	}

	if(eventObj && notIE) {
		// hide any currently-visible popups
		hideCurrentPopup();

		// stop event from bubbling up any farther
		eventObj.cancelBubble = true;

		// move popup div to current cursor position
		// (add scrollTop to account for scrolling for IE)
		var newXCoordinate = (eventObj.pageX) ? eventObj.pageX + xOffset : eventObj.x + xOffset + ((document.body.scrollLeft) ? document.body.scrollLeft:document.documentElement.scrollLeft);
		var newYCoordinate = (eventObj.pageY) ? eventObj.pageY + yOffset : eventObj.y + yOffset + ((document.body.scrollTop)  ? document.body.scrollTop:document.documentElement.scrollTop);

		moveObject(targetObjectId, newXCoordinate, newYCoordinate);

		// and make it visible
		if(changeObjectVisibility(targetObjectId, 'visible')) {
			// if we successfully showed the popup
			// store its Id on a globally-accessible object
			window.currentlyVisiblePopup = targetObjectId;
			return true;
		} else {
			// we couldn't show the popup, boo hoo!
			return false;
		}
	} else {
		// there was no event object, so we won't be able to position anything, so give up
		return false;
	}
}



function hideCurrentPopup() {
	// note: we've stored the currently-visible popup on the global object window.currentlyVisiblePopup
	if(window.currentlyVisiblePopup) {
		changeObjectVisibility(window.currentlyVisiblePopup, 'hidden');
		window.currentlyVisiblePopup = false;
	}
}



// ***********************
// hacks and workarounds *
// ***********************

// initialize hacks whenever the page loads
//window.onload = function run(){initializeHacks();showMem();ie_hack_for_large_tables();}

// setup an event handler to hide popups for generic clicks on the document
document.onclick = hideCurrentPopup;

function initializeHacks() {
    // this ugly little hack resizes a blank div to make sure you can click
    // anywhere in the window for Mac MSIE 5
    if ((navigator.appVersion.indexOf('MSIE 5') != -1)
    && (navigator.platform.indexOf('Mac') != -1)
    && getStyleObject('blankDiv')) {
    window.onresize = explorerMacResizeFix;
    }
    resizeBlankDiv();
    // this next function creates a placeholder object for older browsers
    // createFakeEventObj();
}

function createFakeEventObj() {
    // create a fake event object for older browsers to avoid errors in function call
    // when we need to pass the event object to functions
    if (!window.event) {
    window.event = false;
    }
} // createFakeEventObj

function resizeBlankDiv() {
    // resize blank placeholder div so IE 5 on mac will get all clicks in window
    if ((navigator.appVersion.indexOf('MSIE 5') != -1)
    && (navigator.platform.indexOf('Mac') != -1)
    && getStyleObject('blankDiv')) {
    getStyleObject('blankDiv').width = document.body.clientWidth - 20;
    getStyleObject('blankDiv').height = document.body.clientHeight - 20;
    }
}

function explorerMacResizeFix () {
    location.reload(false);
}



function getStyleObject(objectId) {
    // cross-browser function to get an object's style object given its id
    if(document.getElementById && document.getElementById(objectId)) {
    // W3C DOM
    return document.getElementById(objectId).style;
    } else if (document.all && document.all(objectId)) {
    // MSIE 4 DOM
    return document.all(objectId).style;
    } else if (document.layers && document.layers[objectId]) {
    // NN 4 DOM.. note: this won't find nested layers
    return document.layers[objectId];
    } else {
    return false;
    }
} // getStyleObject

function changeObjectVisibility(objectId, newVisibility) {
    // get a reference to the cross-browser style object and make sure the object exists
    var styleObject = getStyleObject(objectId);
    if(styleObject) {
    styleObject.visibility = newVisibility;
    return true;
    } else {
    // we couldn't find the object, so we can't change its visibility
    return false;
    }
} // changeObjectVisibility

function moveObject(objectId, newXCoordinate, newYCoordinate) {
    // get a reference to the cross-browser style object and make sure the object exists
    var styleObject = getStyleObject(objectId);
    if(styleObject) {
    styleObject.left = newXCoordinate + 'px';
    styleObject.top = newYCoordinate + 'px';
    return true;
    } else {
    // we couldn't find the object, so we can't very well move it
    return false;
    }
} // moveObject





function explode (delimiter, string, limit) {
	// http://kevin.vanzonneveld.net
	// +     original by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
	// +     improved by: kenneth
	// +     improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
	// +     improved by: d3x
	// +     bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
	// *     example 1: explode(' ', 'Kevin van Zonneveld');
	// *     returns 1: {0: 'Kevin', 1: 'van', 2: 'Zonneveld'}
	// *     example 2: explode('=', 'a=bc=d', 2);
	// *     returns 2: ['a', 'bc=d']
	var emptyArray = {
		0: ''
	};

	// third argument is not required
	if (arguments.length < 2 || typeof arguments[0] == 'undefined' || typeof arguments[1] == 'undefined') {
		return null;
}

if (delimiter === '' || delimiter === false || delimiter === null) {
	return false;
}

if (typeof delimiter == 'function' || typeof delimiter == 'object' || typeof string == 'function' || typeof string == 'object') {
	return emptyArray;
	}

	if (delimiter === true) {
		delimiter = '1';
	}

	if (!limit) {
		return string.toString().split(delimiter.toString());
	} else {
		// support for limit argument
		var splitted = string.toString().split(delimiter.toString());
		var partA = splitted.splice(0, limit - 1);
		var partB = splitted.join(delimiter.toString());
		partA.push(partB);
		return partA;
	}
	}