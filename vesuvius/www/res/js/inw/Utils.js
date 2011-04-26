/**
 * @name         INW Utils Object
 * @version      1.6
 * @package      inw
 * @author       Merwan Rodriguez <rodriguezmer@mail.nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

var Utils = {
	/**
	 * true = interactive
	 * false = handsFree
	**/
	displayMode : function(mode) {
		if ( mode == "fullScreen" )
			mode = ScrollView.goFullScreen();

		Globals.displayMode = (mode == 'interactive');
		Globals.currPage = 1;
		Globals.initDone = 1;
		Globals.personListOld = [];
		searchSubset();
	},

	showDetail : function(person) {

		var doc = document;

		//pause the scroll
		if ( !Globals.displayMode )
			ScrollView.pause();

		$("#glass").css({ height : $(document).height() }).show();

		$("#detailsPane")
		  .css({left: Math.round($(window).width()/2)-400+'px',
				 top: Math.round($(window).height()/2)-250 + Utils.realScrollTop() + 'px'
				 })
		  .show();

		$("#dt_uuid").html(person.uuid)
		$("#dt_fullName").html(person.name || "N/A");
		$("#dt_age").html(person.ageGroup || "N/A");
		$("#dt_gender").html(person.gender || "N/A");
		$("#dt_status").html(person.statusSahanaFull || "N/A");
		$("#dt_statusSahanaUpdated").html(person.statusSahanaUpdated + " UTC" );
		$("#dt_location").html(person.location || "N/A");
		$("#dt_comments").html(person.comments || "N/A");
		
		inw_getNotes(person.uuid) 
		$("#dt_notesTab > a").html("Notes");
		
		if ( $("#shortName").val() == "sendai2011" ) // obviously a hack.
			$("#dt_eapLink > a").attr("href", "http://japan.person-finder.appspot.com/view?lang=en&id=" + person.uuid ).attr("target", "_new");
		else 
			$("#dt_eapLink > a").attr("href", "index.php?mod=eap&act=edit&uuid=" + person.encodedUUID);
			
		if ( person.hospitalIcon != "" )
			$("#dt_hospitalIcon").html("<img src='" + person.hospitalIcon + "' />");
		else
			$("#dt_hospitalIcon").html("");

		$("#dt_image").html('<img style="position:relative;max-height:300px;max-width:300px" src="'+person.imageUrl+'">');

		// Utils.loadMap();
	},

	closeDetail : function() {
		var doc = document;

		//play the scroll
		if ( !Globals.displayMode )
			ScrollView.play();
			
		if ( $("#dt_notesTab > a").html() === "Info" )
			Utils.showNotes();

		$("#glass").hide();
		$("#detailsPane").hide();
		
		$("#dt_noteDates, #noteDatesLabel, #dt_image > div, #dt_notes > *").remove();
		$("#jsonNotes").val("");
		
		
		if ($("#map_canvas").css("visibility") === "visible")
			Utils.showMap();
	},

	printDetail : function() {
		tmp = window.open("res/details.php?uuid=" + document.getElementById("dt_uuid").innerHTML);
	},

	map : null, //should move this to global maybe.

	loadMap : function() {
		var latlng = new google.maps.LatLng(-34.397, 150.644);
		var myOptions = {
		  zoom: 8,
		  center: latlng,
		  mapTypeId: google.maps.MapTypeId.ROADMAP
		};
		map = new google.maps.Map(document.getElementById("map_canvas"), myOptions);
		var geocoder = Utils.codeAddress();
	},
	
	loadNotes : function() {
		var jsonNotes = $.parseJSON($("#jsonNotes").val()); // expecting [{"note_id":"asahi.com\/note.0000a5f9cddbaa47f2e4917bf931d78d.1","date":"2011-04-11 21:16:54","author":"?????? ????????","found":null,"status":"believed_alive","lastSeen":null,"text":"???????????? URL???????????"},{"note_id":...
		
		if ( !jsonNotes ) { 
			$("#dt_notesTab").hide(); 
			return; 
		} 
		else $("#dt_notesTab").show();
		
		var noteDates = $("<ul></ul>").attr("id", "dt_noteDates").css({"display" : "none", "max-height" : "400px"}),
			   jsonLength = jsonNotes.length;
		
		$("#dt_noteDates").html(""); // blank out
		
		for ( var i = 0; i < jsonLength; i++) {
			var link = 	$("<li></li>").attr({ "id" : "note_" + i })
									  .append(
											$("<a></a>")
												.html(jsonNotes[i]["date"])
												.attr("href", "javascript:Utils.showNoteContent(" + i + ")" )
										);
			noteDates.append(link);
		}
		
		var label = $("<label></label>").attr("id", "noteDatesLabel").css({"text-align": "left", "float" : "left", "display": "none", "width" : "100px"}).html("Available Notes");

		$("#dt_image").append(label).append("<div style='clear:both'></div>").append(noteDates);
	},
	
	showNoteContent : function(noteNumber) {
		var noteContent = $("#dt_notes"),
			jsonNotes   = $.parseJSON($("#jsonNotes").val()),
			noteid		= $("<div></div>").attr("id", "note_author").html(jsonNotes[noteNumber]["note_id"]),
			author      = $("<div></div>").attr("id", "note_author").html(jsonNotes[noteNumber]["author"] || "Not Reported"),
			status	 	= $("<div></div>").attr("id","note_status").html(jsonNotes[noteNumber]["status"] || "Not Reported"),
			found	 	= $("<div></div>").attr("id","note_found").html(jsonNotes[noteNumber]["found"] === "true" ? "Yes" : "No"),
			lastSeen 	= $("<div></div>").attr("id","note_lastSeen").html(jsonNotes[noteNumber]["lastSeen"] || "Not Reported"),
			text	 	= $("<textarea></textarea>").attr("id","note_text").html(jsonNotes[noteNumber]["text"])
													.css({"height": "100px",
														  "font-size" : "1.2em",
														  "width" : "355px"}),
			
			legend 		= $("<legend></legend>");
			
			
			
		noteContent.html("")
				   //.append(legend.clone().html("Id")).append(noteid)
				   .append(legend.clone().html("Author")).append(author)
				   .append(legend.clone().html("Status")).append(status)
				   .append(legend.clone().html("Found")).append(found)
				   .append(legend.clone().html("Last Known Location")).append(lastSeen)
				   .append(legend.clone().html("Text")).append(text);
		
		$("#dt_noteDates > li").css("background-color", "transparent");		
		$("#note_" + noteNumber).css("background-color", "#E0ECFF")
		$("#dt_notes_label").html( $("#note_" + noteNumber + " > a").html() );

	},
	
	showNotes : function() {
		$("#detailInfo > div, #detailInfo > label").toggle();
		if ( $("#dt_notesTab > a").html() === "Notes") {
			$("#dt_notesTab > a").html("Info");
			$("#dt_image > img").hide();
			$("#dt_noteDates").show();
			$("#noteDatesLabel").show();
			Utils.showNoteContent(0);
		} else {
			$("#dt_notesTab > a").html("Notes");
			$("#dt_image > img").show();
			$("#dt_noteDates").hide();
			$("#noteDatesLabel").hide();
		}
	},

	showMap : function() {
		if ( $("#map_canvas").css("visibility") === "hidden" ) {
			$("#map_canvas").css({left: 10 + "px",
					 top: 30 + "px",
					 zIndex: 5,
					 visibility: "visible"})

			$("#showMap > a").html("Info");
		} else {
			$("#map_canvas").css({
					 zIndex: 0,
					 visibility: "hidden"})

			$("#showMap > a").html("Map");
		}

		$("#dt_image").toggle();
		$("#detailInfo").toggle();
	},

	codeAddress : function() {
		var geocoder = new google.maps.Geocoder();
		if (geocoder) {
		  geocoder.geocode( { 'address': document.getElementById("dt_location").innerHTML}, function(results, status) {
			if (status == google.maps.GeocoderStatus.OK && document.getElementById("dt_location").innerHTML != "NULL" && document.getElementById("dt_location").innerHTML != "N/A") {
			  map.setCenter(results[0].geometry.location);
			  var marker = new google.maps.Marker({
				  map: map,
				  position: results[0].geometry.location
			  });
			  $("#showMap").show();
			} else {
			  $("#showMap").hide();
			  //alert("Geocode was not successful for the following reason: " + status);
			}
		  });
		}
	},


/*
 *  Takes a jquery object, returns a jquery object (div) w/ details embedded in it
    Maybe should be moved to ScrollView???
 */
	pictureDetails : function(imageDiv, person) {
		var newLayer = $(document.createElement("div"))
						.attr({ id: imageDiv.attr("id") + "_details",
							 style: "height:" + (person.imageHeight - 12) + "px"
							   })
						.addClass("picDetails")
						.click(function() { Utils.showDetail(Globals.personListOld[person.uuid]) });

		newLayer.html("<div style='font-weight:bold'>" + person.name + "</div><br />"
						+  "<span class='statusSahanaFull " + person.tagClass + "' style='margin-left: 10px;color:#" + person.tagColor + ";'>" + person.statusSahanaFull + "</span><br /><br />"
						+  "<div>" + person.statusSahanaUpdated + "</div></br><br />"
						+  "<div>" + person.uuid + "</div><br />");

		var row = person.row,
			pos = Globals.Q[person.row].length;

		newLayer.mouseover(function() { ScrollView.info(row, pos) });
		newLayer.mouseout(function() { ScrollView.unfade(row, pos) });

		imageDiv.append(newLayer);

		return imageDiv;

	},

	changeObserver : function( lastUpdated ) {
		if ( !Globals.lastUpdated ) {
			Globals.lastUpdated = lastUpdated
			return;
		}

		if ( lastUpdated != Globals.lastUpdated ) {
			Globals.mostRecent = Globals.lastUpdated; // saving for later
			Globals.lastUpdated = lastUpdated;
			if ( Globals.displayMode )   
				$("#updateAlerts").fadeIn("slow");
			else {
				$("#updateAlerts2").fadeIn("slow");
				setTimeout(	searchSubset, 60000 );
			}

		}
	},

	ascDesc : function( el ) {
		if ( el.src.indexOf("desc") > 0 ) {
			el.src = "res/img/asc.png";
			el.title = "Ascending (click for descending)";

			if ( $("#selectSort").val() != "" )
				Globals.sortedBy = $("#selectSort").val() + " asc"
		}
		else {
			el.src = "res/img/desc.png";
			el.title = "Descending (click for ascending)"

			if ( $("#selectSort").val() != "" )
				Globals.sortedBy = $("#selectSort").val() + " desc"
		}

		searchSubset();
	},

	sortBy : function( el ) {
		var order = document.getElementById("sortOrderIcon").src.indexOf("desc") > 0 ? "desc" : "asc";
		if ( el.value == "" ) {
			Globals.sortedBy = "";
			$("#sortOrderIcon").hide();
		}
		else {
			Globals.sortedBy = el.value + " " + order;
			$("#sortOrderIcon").show();
		}

		Globals.initDone = 1;

		searchSubset();
	},

	printSet : function() {

		Globals.oldCurrPage = Globals.currPage;
		Globals.currPage = 1;
		Globals.displayMode = true;
		searchSubset();

		setTimeout(function() {
				window.print();
				Globals.perPage = $("#perPage").val();
				Globals.currPage = Globals.oldCurrPage;
				searchSubset();
			}
			, 1000);
	},

	printDetail : function() {
		$("#loadingX").show();
		$("#pager, #perPageWrapper, #printLink, #scrolling_content, #header, #footer, #modmenuwrap, #modmenu, #searchForm, #blueBack, #blueBack, #wrapper_menu, #skip, #menuwrap, #disaster_selekta").hide();

		$("#printSheet").attr("href", "res/iWall_printIndividual.css");
		setTimeout(function() {
			window.print();

		$("#loadingX").hide();
		$("#pager, #perPageWrapper, #printLink, #scrolling_content, #header, #footer, #modmenuwrap, #modmenu, #searchForm, #blueBack, #blueBack, #wrapper_menu, #skip, #menuwrap, #disaster_selekta").show();
		}, 1000)


	},

	realScrollTop : function() {
		// the joys of web development ( IE! ) :<
		var ie_scrollTop = document.documentElement.scrollTop?document.documentElement.scrollTop:document.body.scrollTop;
		var other_scrollTop = $("body").scrollTop();
		var realScrollTop = ie_scrollTop > other_scrollTop ? ie_scrollTop : other_scrollTop;
		// end awful kludge

		return realScrollTop
	},

	formSearch : function() {
		Globals.mostRecent = undefined;
		Globals.lastUpdated = undefined;
		Globals.initDone = 1;
		Globals.currPage = 1;
		searchSubset();
	},
	isNumber : function(n) {
		return !isNaN(parseFloat(n)) && isFinite(n);
	},
	
	addCommas : function (nStr) { // credit - http://www.mredkj.com/javascript/numberFormat.html
		nStr += '';
		x = nStr.split('.');
		x1 = x[0];
		x2 = x.length > 1 ? '.' + x[1] : '';
		var rgx = /(\d+)(\d{3})/;
		while (rgx.test(x1)) {
			x1 = x1.replace(rgx, '$1' + ',' + '$2');
		}
		return x1 + x2;
	}
};


