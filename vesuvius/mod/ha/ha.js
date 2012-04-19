/**
 * @name         Hospital Administration
 * @version      23
 * @package      ha
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1205
 */

ha_show_hospitals();

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

	//var rj = array2json(r);
	var rj = JSON.stringify(r);
	return(rj);
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


// json2.js PACKED ~ original from http://goo.gl/H2ocu
eval(function(p,a,c,k,e,r){e=function(c){return(c<a?'':e(parseInt(c/a)))+((c=c%a)>35?String.fromCharCode(c+29):c.toString(36))};if(!''.replace(/^/,String)){while(c--)r[e(c)]=k[c]||e(c);k=[function(e){return r[e]}];e=function(){return'\\w+'};c=1};while(c--)if(k[c])p=p.replace(new RegExp('\\b'+e(c)+'\\b','g'),k[c]);return p}('w m;3(!m){m={}}(5(){"1L 1I";5 f(n){7 n<10?\'0\'+n:n}3(6 V.p.q!==\'5\'){V.p.q=5(a){7 X(o.1p())?o.1H()+\'-\'+f(o.1G()+1)+\'-\'+f(o.1E())+\'T\'+f(o.1D())+\':\'+f(o.1C())+\':\'+f(o.1B())+\'Z\':y};G.p.q=1A.p.q=1z.p.q=5(a){7 o.1p()}}w e=/[\\1y\\13\\14-\\15\\18\\19\\1a\\1b-\\1c\\1f-\\1h\\1i-\\1j\\1k\\1l-\\1m]/g,K=/[\\\\\\"\\1v-\\1t\\1s-\\1r\\13\\14-\\15\\18\\19\\1a\\1b-\\1c\\1f-\\1h\\1i-\\1j\\1k\\1l-\\1m]/g,8,A,Y={\'\\b\':\'\\\\b\',\'\\t\':\'\\\\t\',\'\\n\':\'\\\\n\',\'\\f\':\'\\\\f\',\'\\r\':\'\\\\r\',\'"\':\'\\\\"\',\'\\\\\':\'\\\\\\\\\'},l;5 I(b){K.17=0;7 K.R(b)?\'"\'+b.D(K,5(a){w c=Y[a];7 6 c===\'L\'?c:\'\\\\u\'+(\'1d\'+a.1e(0).N(16)).1g(-4)})+\'"\':\'"\'+b+\'"\'}5 E(a,b){w i,k,v,h,C=8,9,2=b[a];3(2&&6 2===\'x\'&&6 2.q===\'5\'){2=2.q(a)}3(6 l===\'5\'){2=l.J(b,a,2)}1F(6 2){z\'L\':7 I(2);z\'M\':7 X(2)?G(2):\'y\';z\'1u\':z\'y\':7 G(2);z\'x\':3(!2){7\'y\'}8+=A;9=[];3(U.p.N.1w(2)===\'[x 1x]\'){h=2.h;B(i=0;i<h;i+=1){9[i]=E(i,2)||\'y\'}v=9.h===0?\'[]\':8?\'[\\n\'+8+9.H(\',\\n\'+8)+\'\\n\'+C+\']\':\'[\'+9.H(\',\')+\']\';8=C;7 v}3(l&&6 l===\'x\'){h=l.h;B(i=0;i<h;i+=1){3(6 l[i]===\'L\'){k=l[i];v=E(k,2);3(v){9.W(I(k)+(8?\': \':\':\')+v)}}}}O{B(k 1o 2){3(U.p.1n.J(2,k)){v=E(k,2);3(v){9.W(I(k)+(8?\': \':\':\')+v)}}}}v=9.h===0?\'{}\':8?\'{\\n\'+8+9.H(\',\\n\'+8)+\'\\n\'+C+\'}\':\'{\'+9.H(\',\')+\'}\';8=C;7 v}}3(6 m.P!==\'5\'){m.P=5(a,b,c){w i;8=\'\';A=\'\';3(6 c===\'M\'){B(i=0;i<c;i+=1){A+=\' \'}}O 3(6 c===\'L\'){A=c}l=b;3(b&&6 b!==\'5\'&&(6 b!==\'x\'||6 b.h!==\'M\')){12 11 1q(\'m.P\');}7 E(\'\',{\'\':a})}}3(6 m.Q!==\'5\'){m.Q=5(c,d){w j;5 S(a,b){w k,v,2=a[b];3(2&&6 2===\'x\'){B(k 1o 2){3(U.p.1n.J(2,k)){v=S(2,k);3(v!==1J){2[k]=v}O{1K 2[k]}}}}7 d.J(a,b,2)}c=G(c);e.17=0;3(e.R(c)){c=c.D(e,5(a){7\'\\\\u\'+(\'1d\'+a.1e(0).N(16)).1g(-4)})}3(/^[\\],:{}\\s]*$/.R(c.D(/\\\\(?:["\\\\\\/1M]|u[0-1N-1O-F]{4})/g,\'@\').D(/"[^"\\\\\\n\\r]*"|1P|1Q|y|-?\\d+(?:\\.\\d*)?(?:[1R][+\\-]?\\d+)?/g,\']\').D(/(?:^|:|,)(?:\\s*\\[)+/g,\'\'))){j=1S(\'(\'+c+\')\');7 6 d===\'5\'?S({\'\':j},\'\'):j}12 11 1T(\'m.Q\');}}}());',62,118,'||value|if||function|typeof|return|gap|partial||||||||length||||rep|JSON||this|prototype|toJSON||||||var|object|null|case|indent|for|mind|replace|str||String|join|quote|call|escapable|string|number|toString|else|stringify|parse|test|walk||Object|Date|push|isFinite|meta|||new|throw|u00ad|u0600|u0604||lastIndex|u070f|u17b4|u17b5|u200c|u200f|0000|charCodeAt|u2028|slice|u202f|u2060|u206f|ufeff|ufff0|uffff|hasOwnProperty|in|valueOf|Error|x9f|x7f|x1f|boolean|x00|apply|Array|u0000|Boolean|Number|getUTCSeconds|getUTCMinutes|getUTCHours|getUTCDate|switch|getUTCMonth|getUTCFullYear|strict|undefined|delete|use|bfnrt|9a|fA|true|false|eE|eval|SyntaxError'.split('|'),0,{}))



