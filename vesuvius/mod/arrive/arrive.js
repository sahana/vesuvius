/**
 * @name         Arrival Rate
 * @version      2
 * @package      arrive
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1206
 */


// other vars
window.last_arrival_time = null;
window.all_events = true;
window.increments = 0;

// check if we came in with an anchor variable...
if(self.document.location.hash.substring(1) == 'false') {
	window.all_events = false;
	arrive_append_log('Showing arrivals from <b>only the current event</b>.');
} else {
	arrive_append_log('Showing arrivals from <b>ALL events</b>.');
}


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
	window.history.pushState(null, null, '#'+window.all_events);
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
		window.location.reload();
	}
}


fetch(1);
arrive_show_list('false', window.all_events);
setInterval('fetch(0)', 5000);



