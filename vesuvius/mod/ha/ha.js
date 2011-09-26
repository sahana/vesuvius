/**
 * @name         Hospital Administration
 * @version      2.1
 * @package      ha
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0926
 */

ha_show_message('Loading Hospitals...');
setTimeout('ha_show_hospitals();', 1500);

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




function ha_delete(incident_id) {
	ha_append_log('Removing Hospital #<b>' + incident_id + '</b> ...<br>');
	setTimeout('ha_perform_delete('+incident_id+', confirm(\'Are you sure you want to remove this Hospital? Removing this Hospital will orphan all data that was attached to it. If you are certain that you have removed all related data then you may proceeed; otherwise press CANCEL to abort this operation.\'));', 100);
}



function ha_get_data() {
	var r = new Object();
	r.hospital_uuid                  = $("#hospital_uuid").val();
	alert(r.hospital_uuid);
	r.name                           = $("#name").val();
	r.short_name                     = $("#short_name").val();
	r.street1                        = $("#street1").val();
	r.street2                        = $("#street2").val();
	r.city                           = $("#city").val();
	r.county                         = $("#county").val();
	r.region                         = $("#region").val();
	r.postal_code                    = $("#postal_code").val();
	r.country                        = $("#country").val();
	r.latitude                       = $("#latitude").val();
	r.longitude                      = $("#longitude").val();
	r.phone                          = $("#phone").val();
	r.fax                            = $("#fax").val();
	r.email                          = $("#email").val();
	r.www                            = $("#www").val();
	r.npi                            = $("#npi").val();
	r.patient_id_prefix              = $("#patient_id_prefix").val();
	r.patient_id_suffix_fixed_length = $("#patient_id_suffix_fixed_length").val();
	r.icon_url                       = $("#icon_url").val();
	r.legalese                       = $("#legalese").val();
	r.legaleseAnon                   = $("#legaleseAnon").val();

	if($("#patient_id_suffix_variable:checked").val() == "default") {
		r.patient_id_suffix_variable = 1;
	} else {
		r.patient_id_suffix_variable = 0;
	}

	if($("#photo_required:checked").val() == "default") {
		r.photo_required = 1;
	} else {
		r.photo_required = 0;
	}

	if($("#honor_no_photo_request:checked").val() == "default") {
		r.honor_no_photo_request = 1;
	} else {
		r.honor_no_photo_request = 0;
	}

	if($("#photographer_name_required:checked").val() == "default") {
		r.photographer_name_required = 1;
	} else {
		r.photographer_name_required = 0;
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
			parts.push(str);
		}
	}
	var json = parts.join(",");
	if(is_list) {
		return '[' + json + ']';//Return numerical JSON
	}
	return '{' + json + '}';//Return associative JSON
}



// from http://goo.gl/CLJxF
function htmlspecialchars(string, quote_style, charset, double_encode) {
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


