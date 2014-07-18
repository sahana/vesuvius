/**
 * @name         Arrival Rate
 * @version      3
 * @package      arrive
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0213
 */


// other vars
window.last_arrival_time = null;
window.all_events = true;
window.increments = 0;

var tmp = self.document.location.hash;
tmp = explode('zZ||Zz', tmp);
var anchor1 = tmp[0];
var anchor2 = tmp[1];

if(typeof anchor1 === 'undefined') {
	window.all_events = true;
} else if(anchor1 == '#false') {
	window.all_events = false;
}
if(typeof anchor2 === 'undefined') {
	window.rezLog = '';
} else {
	window.rezLog = unescape(anchor2);
}
if(window.rezLog == '') {

	if(window.all_events) {
		window.rezLog = 'Showing arrivals from <b>ALL events</b>.';
	} else {
		window.rezLog = 'Showing arrivals from <b>only the current event</b>.';
	}
}

var rL = document.getElementById('rezLog');
rL.innerHTML = window.rezLog;


function updateMenu() {

	if(window.all_events) {
		var a = document.getElementById('allButton');
		a.disabled = true;
		a.style.opacity = '0.2';
		var b = document.getElementById('currentButton');
		b.disabled = false;
		b.style.opacity = '1.0';
	} else {
		var a = document.getElementById('allButton');
		a.disabled = false;
		a.style.opacity = '1.0';
		var b = document.getElementById('currentButton');
		b.disabled = true;
		b.style.opacity = '0.2';
	}
	if(typeof window.history.pushState == 'function') {
		window.history.pushState(null, null, '#'+window.all_events+'zZ||Zz'+escape(window.rezLog));
	} else {
		window.location.href = '#'+window.all_events+'zZ||Zz'+escape(window.rezLog);
	}
}


function updateLastArrival(val, initial) {

	if(window.last_arrival_time != val) {
		window.last_arrival_time = val;
		if(initial == 1) {
			arrive_show_list('false', all_events);
		} else {
			arrive_show_list('true', all_events);
		}
	}
}


function showAll(val) {

	window.all_events = val;
	fetch(1);
	updateMenu();
	arrive_show_list('false', window.all_events);
}


function fetch(val) {

	cleanLog();
	arrive_fetch_last_updated(window.all_events, val);
}


function cleanLog() {

	window.increments++;

	// add a dot to the log every minute...
	if((window.increments % 12) == 0) {
		arrive_add_spacer('.');
	}

	// add a space to the log every ten minutes
	if((window.increments % 120) == 0) {
		arrive_add_spacer(' ');
	}

	// reload the page once an hour to keep the session alive...
	if((window.increments % 720) == 0) {
		setTimeout('reloadPage();', 10000);
	}
}


function reloadPage() {

	var r = document.getElementById('rezLog');
	window.rezLog = r.innerHTML;
	window.rezLog = window.rezLog+'<br>Reloading page to keep session alive.';
	if(typeof window.history.pushState == 'function') {
		window.history.pushState(null, null, '#'+window.all_events+'zZ||Zz'+escape(window.rezLog));
	} else {
		window.location.href = '#'+window.all_events+'zZ||Zz'+escape(window.rezLog);
	}
	window.location.reload();
}

fetch(1);
arrive_show_list('false', window.all_events);
setInterval('fetch(0)', 5000);


//////////// other help functions


function explode (delimiter, string, limit) {

	var emptyArray = {0: ''	};

	// third argument is not required
	if(arguments.length < 2 || typeof arguments[0] == 'undefined' || typeof arguments[1] == 'undefined') {
		return null;
	}

	if(delimiter === '' || delimiter === false || delimiter === null) {
		return false;
	}

	if(typeof delimiter == 'function' || typeof delimiter == 'object' || typeof string == 'function' || typeof string == 'object') {
		return emptyArray;
	}

	if(delimiter === true) {
		delimiter = '1';
	}

	if(!limit) {
		return string.toString().split(delimiter.toString());
	}

	// support for limit argument
	var splitted = string.toString().split(delimiter.toString());
	var partA = splitted.splice(0, limit - 1);
	var partB = splitted.join(delimiter.toString());
	partA.push(partB);
	return partA;
}


