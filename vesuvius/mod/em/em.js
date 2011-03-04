/**
 * @name         Event Manager
 * @version      1.1
 * @package      em
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0302
 */

em_show_message('Loading Events...');
setTimeout('em_show_events();', 1500);

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
	em_append_log('Deleting Event #<b>' + incident_id + '</b> ...<br>');
	setTimeout('em_perform_delete('+incident_id+', confirm(\'Are you sure you want to delete this incident? Deleting this incident will orphan all data that was attached to it. If you are certain that you have removed all related data already (through Delete a Person module and similar modules) then you may proceeed; otherwise press please CANCEL to abort this operation.\'));', 100);
}



function em_get_data() {
	var r = new Object();
	r.latitude         = $("#latitude").val();
	r.longitude        = $("#longitude").val();
	r.longName         = $("#longName").val();
	r.shortName        = $("#shortName").val();
	r.eventDescription = $("#eventDescription").val();
	r.eventParent      = $("#eventParent").val();
	r.eventType        = $("#eventType").val();
	r.eventVisibility  = $("#eventVisibility").val();
	r.eventDate        = $("#eventDate").val();
	r.eventId          = $("#eventId").val();
	r.street           = $("#address").val();

	if($("#eventDefault:checked").val() == "default") {
		r.eventDefault = 1;
	} else {
		r.eventDefault = 0;
	}
	if($("#eventClosed:checked").val() == "closed") {
		r.eventClosed = 1;
	} else {
		r.eventClosed = 0;
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
