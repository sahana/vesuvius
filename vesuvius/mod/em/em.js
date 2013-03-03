/**
 * @name         Event Manager
 * @version      16
 * @package      em
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1205
 */


em_show_events();

// Google Maps junx

var latitude = '';
var longitude = '';
var geocoder;
var map;
var marker;

function getLocation(pos) {
	latitude = pos.coords.latitude;
	longitude = pos.coords.longitude;
	load_map();
	geocoder.geocode({'latLng': marker.getPosition()}, function(results, status) {
		if (status == google.maps.GeocoderStatus.OK) {
			if (results[0]) {
				$('#address').val(results[0].formatted_address);
				$('#latitude').val(marker.getPosition().lat());
				$('#longitude').val(marker.getPosition().lng());
			}
		}
	});
}


function unknownLocation() {
	alert('Could not find location');
}


function detect_load() {
	navigator.geolocation.getCurrentPosition(getLocation, unknownLocation);
}


function load_map(latitude, longitude, street) {
	if(latitude == null || longitude == null) {
		latitude = 39;
		longitude = -77.101;
	}
	var latlng = new google.maps.LatLng(latitude, longitude);
	var config = {
		zoom: 13,
		center: latlng,
		disableDefaultUI: true,
		navigationControl: true,
		navigationControlOptions: {
			style: google.maps.NavigationControlStyle.ZOOM_PAN
		},
		mapTypeControl: true,
		mapTypeControlOptions: {
			style: google.maps.MapTypeControlStyle.DROPDOWN_MENU
		},
		mapTypeId: google.maps.MapTypeId.ROADMAP
	};
	map = new google.maps.Map(document.getElementById("mapCanvas"), config);

	geocoder = new google.maps.Geocoder();

	marker = new google.maps.Marker({
		map: map,
		draggable: true
	});

	$(function() {
		$("#address").autocomplete({

			// This bit uses the geocoder to fetch address values
			source: function(request, response) {
				geocoder.geocode( {'address': request.term }, function(results, status) {
					response($.map(results, function(item) {
						return {
							label:  item.formatted_address,
							value: item.formatted_address,
							latitude: item.geometry.location.lat(),
							longitude: item.geometry.location.lng()
						}
					}));
				})
			},

			// This bit is executed upon selection of an address
			select: function(event, ui) {
				$("#latitude").val(ui.item.latitude);
				$("#longitude").val(ui.item.longitude);
				var location = new google.maps.LatLng(ui.item.latitude, ui.item.longitude);
				marker.setPosition(location);
				map.setCenter(location);
			}
		});
	});

	// Add listener to marker for reverse geocoding
	google.maps.event.addListener(marker, 'drag', function() {
		geocoder.geocode({'latLng': marker.getPosition()}, function(results, status) {
			if (status == google.maps.GeocoderStatus.OK) {
				if (results[0]) {
					$('#address').val(results[0].formatted_address);
					$('#latitude').val(marker.getPosition().lat());
					$('#longitude').val(marker.getPosition().lng());
				}
			}
		});
	});

	$("#latitude").val(latitude);
	$("#longitude").val(longitude);
	$("#address").val(street);
	var location = new google.maps.LatLng(latitude, longitude);
	marker.setPosition(location);
	map.setCenter(location);

}




function em_delete(incident_id) {
	em_append_log('Deleting Event #<b>' + incident_id + '</b> (this operation may take a long time on large events) ...<br>');
	setTimeout('em_perform_delete('+incident_id+', confirm(\'Are you sure you want to delete this incident? Doing so will delete all person data along with the associated image and voicenote data. If you are sure then you may proceeed; otherwise please press CANCEL to abort this operation.\'));', 100);
}

function em_purge(incident_id) {
	em_append_log('Purging Event #<b>' + incident_id + '</b> (this operation may take a long time on large events) ...<br>');
	setTimeout('em_perform_purge('+incident_id+', confirm(\'Are you sure you want to purge all person data from this incident? If you are sure then you may proceeed; otherwise please press CANCEL to abort this operation.\'));', 100);
}



function em_get_data() {
	var r = new Object();
	r.latitude         = $("#latitude").val();
	r.longitude        = $("#longitude").val();
	r.longName         = htmlspecialchars($("#longName").val());
	r.shortName        = $("#shortName").val();
	r.eventDescription = htmlspecialchars($("#eventDescription").val());
	r.externalReport   = htmlspecialchars($("#externalReport").val());
	r.eventParent      = $("#eventParent").val();
	r.eventType        = $("#eventType").val();
	r.eventVisibility  = $("#eventVisibility").val();
	r.eventDate        = $("#eventDate").val();
	r.eventId          = $("#eventId").val();
	r.pfifUrl          = $("#pfifUrl").val();
	r.pfifSync         = $("#pfifSync:checked").val();
	r.street           = $("#address").val();
	r.eventClosed      = $("#eventClosed:checked").val();

	if($("#eventDefault:checked").val() == "default") {
		r.eventDefault = 1;
	} else {
		r.eventDefault = 0;
	}

	var rj = array2json(r);
	return(rj);
}



// converts array to json for export >> from: http://goo.gl/ZVNnr
function array2json(arr) {
	var parts = [];
	var is_list = (Object.prototype.toString.apply(arr) === '[object Array]');

	for(var key in arr) {
		var value = arr[key];
		if(typeof value == "object") { //Custom handling for arrays
			if(is_list) {
				parts.push(array2json(value)); // :RECURSION:
			} else {
				parts[key] = array2json(value); // :RECURSION:
			}
		} else {
			var str = "";
			if(!is_list) {
				str = '"' + key + '":';
			}
			// Custom handling for multiple data types
			if(typeof value == "number") {
				str += value; //Numbers
			} else if(value === false) {
				str += 'false'; //The booleans
			} else if(value === true) {
				str += 'true';
			} else {
				str += '"' + value + '"'; //All other things
			}
			// todo: Is there any more datatype we should be in the lookout for? (Functions?)
			parts.push(str);
		}
	}
	var json = parts.join(",");
	if(is_list) {
		return '[' + json + ']';//Return numerical JSON
	}
	return '{' + json + '}';//Return associative JSON
}


function initDate() {
	$("#eventDate").datepicker({ dateFormat: 'yy-mm-dd' });
}



// from http://goo.gl/CLJxF
function htmlspecialchars(string, quote_style, charset, double_encode) {
	// http://kevin.vanzonneveld.net
	// +   original by: Mirek Slugen
	// +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
	// +   bugfixed by: Nathan
	// +   bugfixed by: Arno
	// +    revised by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
	// +    bugfixed by: Brett Zamir (http://brett-zamir.me)
	// +      input by: Ratheous
	// +      input by: Mailfaker (http://www.weedem.fr/)
	// +      reimplemented by: Brett Zamir (http://brett-zamir.me)
	// +      input by: felix
	// +    bugfixed by: Brett Zamir (http://brett-zamir.me)
	// %        note 1: charset argument not supported
	// *     example 1: htmlspecialchars("<a href='test'>Test</a>", 'ENT_QUOTES');
	// *     returns 1: '&lt;a href=&#039;test&#039;&gt;Test&lt;/a&gt;'
	// *     example 2: htmlspecialchars("ab\"c'd", ['ENT_NOQUOTES', 'ENT_QUOTES']);
	// *     returns 2: 'ab"c&#039;d'
	// *     example 3: htmlspecialchars("my "&entity;" is still here", null, null, false);
	// *     returns 3: 'my &quot;&entity;&quot; is still here'
	var optTemp = 0, i = 0,
	noquotes = false;

	if (typeof quote_style === 'undefined' || quote_style === null) {
		quote_style = 2;
	}
	string = string.toString();
	if (double_encode !== false) {
		// Put this first to avoid double-encoding
		string = string.replace(/&/g, '&amp;');
	}
	string = string.replace(/</g, '&lt;').replace(/>/g, '&gt;');

	var OPTS = {
		'ENT_NOQUOTES': 0,
		'ENT_HTML_QUOTE_SINGLE': 1,
		'ENT_HTML_QUOTE_DOUBLE': 2,
		'ENT_COMPAT': 2,
		'ENT_QUOTES': 3,
		'ENT_IGNORE': 4
	};
	if (quote_style === 0) {
		noquotes = true;
	}
	if (typeof quote_style !== 'number') {
		// Allow for a single string or an array of string flags
		quote_style = [].concat(quote_style);
		for (i = 0; i < quote_style.length; i++) {
			// Resolve string input to bitwise e.g. 'PATHINFO_EXTENSION' becomes 4
			if (OPTS[quote_style[i]] === 0) {
				noquotes = true;
			} else if (OPTS[quote_style[i]]) {
				optTemp = optTemp | OPTS[quote_style[i]];
			}
		}
		quote_style = optTemp;
	}
	if (quote_style & OPTS.ENT_HTML_QUOTE_SINGLE) {
		string = string.replace(/'/g, '&#039;');
	}
	if (!noquotes) {
		string = string.replace(/"/g, '&quot;');
	}

	return string;
}


