/**
 * @name         Arrival Rate
 * @version      1
 * @package      arrive
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1205
 */



// other vars
window.last_arrival_time = null;
window.all_events = true;

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
	arrive_fetch_last_updated(window.all_events, val);
}

fetch(1);
arrive_show_list('false', window.all_events);
setInterval('fetch(0)', 5000);




/*

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
*/

