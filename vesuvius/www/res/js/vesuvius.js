/**
 * @name         Vesuvius Javascript Library
 * @version      2.0
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0727
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
}



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
}



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
}




function explode(delimiter, string, limit) {
	// http://kevin.vanzonneveld.net

var emptyArray = {
		0: ''
	};

	// third argument is not required
	if(arguments.length < 2 || typeof arguments[0] == 'undefined' || typeof arguments[1] == 'undefined') {
		return null;
	}
	if(delimiter === '' || delimiter === false || delimiter === null) {
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


function strtolower (str) {
	// http://kevin.vanzonneveld.net
	return (str + '').toLowerCase();
}



function str_ireplace (search, replace, subject) {
	// http://kevin.vanzonneveld.net
	// +   original by: Martijn Wieringa
	// +      input by: penutbutterjelly
	// +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
	// +    tweaked by: Jack
	// +   bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
	// +   bugfixed by: Onno Marsman
	// +      input by: Brett Zamir (http://brett-zamir.me)
	// +   bugfixed by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
	// +   bugfixed by: Philipp Lenssen
	// *     example 1: str_ireplace('l', 'l', 'HeLLo');
	// *     returns 1: 'Hello'
	// *     example 2: str_ireplace('$', 'foo', '$bar');
	// *     returns 2: 'foobar'
	var i, k = '';
	var searchl = 0;
	var reg;

	var escapeRegex = function (s) {
		return s.replace(/([\\\^\$*+\[\]?{}.=!:(|)])/g, '\\$1');
	};

	search += '';
	searchl = search.length;
	if (Object.prototype.toString.call(replace) !== '[object Array]') {
		replace = [replace];
		if (Object.prototype.toString.call(search) === '[object Array]') {
			// If search is an array and replace is a string,
			// then this replacement string is used for every value of search
			while (searchl > replace.length) {
				replace[replace.length] = replace[0];
			}
		}
	}

	if (Object.prototype.toString.call(search) !== '[object Array]') {
		search = [search];
	}
	while (search.length > replace.length) {
		// If replace has fewer values than search,
		// then an empty string is used for the rest of replacement values
		replace[replace.length] = '';
	}

	if (Object.prototype.toString.call(subject) === '[object Array]') {
		// If subject is an array, then the search and replace is performed
		// with every entry of subject , and the return value is an array as well.
		for (k in subject) {
			if (subject.hasOwnProperty(k)) {
				subject[k] = str_ireplace(search, replace, subject[k]);
			}
		}
		return subject;
	}
	searchl = search.length;
	for (i = 0; i < searchl; i++) {
		reg = new RegExp(escapeRegex(search[i]), 'gi');
		subject = subject.replace(reg, replace[i]);
	}
	return subject;
}


// find out if the session_id or sess_key are in the url, if so, remove them from the history
// this effectively prevents stupid users from sharing sessions with anyone else
function checkSession() {
	var query = window.location.search.substring(1);
	var params = query.split("&");
	var theOldUrl = window.location.toString();
	var theNewUrl = theOldUrl;
	var doReplace = false;
	for(var i = 0; i < params.length; i++) {
		var pair = params[i].split("=");
		if(strtolower(pair[0]) == 'session_id' || strtolower(pair[0]) == 'sess_key') {
			theNewUrl = str_ireplace(params[i], '', theNewUrl);
			doReplace = true;
		}
	}
	if(doReplace) {
		window.history.replaceState('', '', theNewUrl);
	}
}
checkSession();




