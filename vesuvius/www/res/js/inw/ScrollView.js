/**
 * @name         INW ScrollView Object
 * @version      1.6
 * @package      inw
 * @author       Merwan Rodriguez <rodriguezmer@mail.nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

var ScrollView = {

	init : function() {
		ScrollView.pause();
		$("#glass").css({ height : $(document).height() }).show().html("<div style='position: absolute; font-size: 14pt; top: 50%; left: 45%'>Loading...<BR /><img src=\"res/img/loader.gif\" /></div>");
		Globals.aPerson = [];  // this directly applies to DetailsView, it's here as a kludge
		Globals.initDone = 1;
		if ( $("#content").css("display") != "none" ) // if not in full screen mode.
			Globals.maxRows = Math.ceil(($(window).height()-210)/300) > 4 ? 4 : Math.ceil(($(window).height()-210)/300);

		Globals.Q2 = ScrollView.initQArray();
		Globals.Q = ScrollView.initQArray();

		Globals.nextRow = 0;


		Globals.personList = [];
		Globals.personListOld = [];

		Globals.scroll    = new Array(false, false, false);
		Globals.scrollCount = new Array(0, 0, 0);

		$("#displayMode").val("handsFree");

		ScrollView.initHTML();
		ScrollView.loadScroller();
		$("#scrollControls").show();

		if ( !Globals.isiPad ) {
			$("#printLink").show();
			ScrollView.play();
			$("#glass").css({ height : $(document).height() }).html("").hide();
		} else {
			setTimeout(function () {
							$("#glass").css({ height : $(document).height() }).html("").hide();
							ScrollView.play();
						}, 5000);

		}



	},

	initQArray : function() {
		var tmpArray = new Array();
		for (var i = 0; i < Globals.maxRows; i++)
			tmpArray[i] = new Array();

		return tmpArray;
	},

	initHTML : function() {
		var content = $("#scrolling_content"),
			tempDiv = $("<div></div>"),

		    rowWrapper = $("<div></div>")
							.css ({ width : "100%",
									position: "relative",
									overflow: "hidden",
									paddingBottom : "0px"}),

			leftArrow = $("<div></div>")
						    .addClass("transparent")
							.addClass(Globals.isiPad ? "directionControl_iPad" : "directionControl")
							.css({ background : "url(../res/img/scroller_arrows_left.png) center no-repeat",
								   left       : 0 })
						    .html("&nbsp;"),

			scrollingRow = $("<div></div>")
							 .addClass("innerRow"),

			rightArrow = $("<div></div>")
				.addClass("transparent")
				.addClass(Globals.isiPad ? "directionControl_iPad" : "directionControl")
				.css({ background : "url(../res/img/scroller_arrows_right.png) center no-repeat",
				       right      : 0})
				.html("&nbsp;"),

			clearDiv = $("<div></div>").css({ clear: "both" });


		for ( var i = 0; i < Globals.maxRows; i++ ) {
			var tempRowWrapper = rowWrapper.clone().attr({ id : "row_" + i + "_wrapper" }),
				tempScrollingRow = scrollingRow.clone().attr({ id : "row_" + i }),
				rowNum = i;
			tempRowWrapper.append(leftArrow.clone().attr({id : i }).click(function() {
										ScrollView.pause();
										ScrollView.reDraw_v3("left",  $(this).attr("id"), 500);
										setTimeout(function() { ScrollView.play(); }, 1000)
									}))
						  .append(tempScrollingRow)
						  .append(rightArrow.clone().attr({id : i }).click(function() {
										ScrollView.pause();
										ScrollView.reDraw_v3("right", $(this).attr("id"), 500);
										setTimeout(function() { ScrollView.play(); }, 1000)
									}))

			tempDiv.append(tempRowWrapper);
		}

		tempDiv.append(clearDiv);
		content.html("").append(tempDiv);
		$("#pager").hide();
		$("#perPageWrapper").hide();
	},

	initTimer : function() {
		clearInterval(Globals.reDrawIntervalId);
		Globals.reDrawIntervalId = setInterval(function() {
				for( var i = 0; i < Globals.maxRows; i++ )
					ScrollView.reDraw_v3("right", i);
			}, Globals.scrollSpeed);
	},

	update : function() {
		if (Globals.initDone != 0) {
			var count = 0;
			for (var person in Globals.personList)
				if (Globals.personList[person].hasOwnProperty('uuid')) {
					count++;
					ScrollView.getPersonData(Globals.personList[person]);
					if ( count > 100 ) {
						setTimeout(ScrollView.update, 3000) // wait 3 seconds! this is for IE8-/FF3.0- not to lose their patience on big sets.
						break;
					}
				}
		}
	},

	loadScroller : function() {
		var freshUuids = [];
		if ( Globals.resultSet && Globals.resultSet.length > 0 ) {
			Globals.initDone = 1;
			var tempResultCount = Globals.totalResults > 1000 ? 1000 : Globals.totalResults; //solr maxes out at 1000 count (for practical uses)
			var i = 0;
			while ( Globals.resultSet[i] ) {
				p = new Person();
				p.init( Globals.resultSet[i] );

				// if status is changed, delete from Globals.personListOld and Q so it gets readded.
				if (Globals.personListOld[ p.uuid ]
					&& ( Globals.mostRecent && Date.parse(p.statusSahanaUpdated.replace('@','')) > Date.parse(Globals.mostRecent.replace('@','')) )) {
					ScrollView.removePersonFromQ(p.uuid);
					delete Globals.personListOld[ p.uuid ];
				}
				if ( !Globals.personListOld[p.uuid] ) {
					Globals.personList[p.uuid] = Globals.personListOld[p.uuid] = p;
				}
				freshUuids.push( p.uuid );
				i += 1;
			}
			// CHECK FOR UUIDs TO REMOVE
			var fuLength = freshUuids.length;
			for ( var i = 0; i < fuLength; i++ ) {
				if ( !Globals.personListOld[freshUuids[i]] ) {
					delete Globals.personListOld[ freshUuids[ i ] ];
					ScrollView.removePersonFromQ( freshUuids[ i ] );
				}
			}
			if ( Object.size( Globals.personList ) === 0 ) {
				Globals.initDone = 0;
			}
		} else {
			ScrollView.pause();
			var snmf = document.getElementById( 'sNoMatchesFound' ).value;
			document.getElementById( 'infoLine1' ).innerHTML = '<span style="color: red; font-weight: bold;">'+snmf+'</span>';
			Globals.initDone = 0;
		}
		ScrollView.update();
	},

	getPersonData : function(person) {
		if (isNaN(person.imageHeight)) {
			person.imageHeight = 0;
		}

		// incremental row assignments
		person.row = Globals.nextRow;

	  ScrollView.addPersonToQ(person);

	  delete Globals.personList[person.uuid];

		if (Object.size(Globals.personList) == 0) {
			Globals.initDone = 0;
		}
	},

	addPersonToQ : function(person) {
		var newWidth, newHeight, locationString, topOverlayString, triangleString;
		var skip  = false;

		var writeOnDiv = false;

		// check if we are excluding this particular person from being displayed
		for (var s = 0; s < Globals.uuidSkipList.length; s++) {
			if (Globals.uuidSkipList[s] == person.uuid) {
				skip = true;
			}
		}

		// queue the person
		if (!skip) {
			// check for null names
			if ((person.name == null) || (person.name == "")) {
				person.name = "unknown";
			}

			triangleString = "";

			// check for null images
			if (person.imageUrl == null || person.imageUrl == "" || person.imageHeight == 0) {
				writeOnDiv = true;
				person.imageWidth  = Globals.imageHeight;
				person.imageHeight = Globals.imageHeight;
				person.image = new Image();
				if (person.age != null) {
					if (person.age > 17) {
						if (person.gender != null) {
							if (person.gender == "mal") {
								// man
								person.image.src="res/img/s2man.png";
							} else if (person.gender == "fml") {
								// woman
								person.image.src="res/img/s3woman.png";
							} else {
								// unknown
								person.image.src="res/img/s4unknown.png";
							}
						} else  {
							// unknown
							person.image.src="res/img/s4unknown.png";
						}
					} else {
						if (person.gender != null) {
							if (person.gender == "mal") {
								// boy
								person.image.src="res/img/s0boy.png";
							} else if (person.gender == "fml") {
								// girl
								person.image.src="res/img/s1girl.png";
							} else {
								// unknown
								person.image.src="res/img/s4unknown.png";
							}
						} else {
							// unknown
							person.image.src="res/img/s4unknown.png";
						}
					}
				} else {
					// unknown
					person.image.src="res/img/s4unknown.png";
				}
			} else {
				// calculate new image dimensions
				newHeight = Globals.imageHeight;
				newWidth  = newHeight/person.imageHeight*person.imageWidth;
				person.imageWidth  = newWidth;
				person.imageHeight = newHeight;
				person.image = new Image();
				person.image.src = person.imageUrl;
			}

			person.opacity = 0.0;
			Globals.personListOld[person.uuid] = person;  // save newest changes to use in details pane.

			var tempColor = "#"+person.tagColor,
				tempWidth = (person.imageWidth+(2*Globals.imageBorder))+"px",
				tempHeight = (person.imageHeight+(2*Globals.imageBorder))+"px";

			var newDiv  = $("<div></div>")
						   .attr({ id: "row"+person.row+"picture"+Globals.Q2[person.row].length,
								  style: "background-color:" + tempColor + ";width: " + tempWidth + ";height:" +tempHeight,
								  className: "picture"
								 });

			if (!writeOnDiv)
				newDiv.html('<img onclick="Utils.showDetail(Globals.personListOld[\''+person.uuid+'\'])" id="row'+person.row+'picture'+Globals.Q2[person.row].length+'i" style="height: '+person.imageHeight+'px; width: '+person.imageWidth+'px;" src="'+person.image.src+'" onMouseOver="ScrollView.info('+person.row+', '+Globals.Q2[person.row].length+')" onMouseOut="ScrollView.unfade('+person.row+', '+Globals.Q2[person.row].length+')" alt="photo of person">');
			else {
				newDiv = Utils.pictureDetails(newDiv, person);
			}

			if ( Globals.mostRecent && Date.parse(person.statusSahanaUpdated.replace('@','')) > Date.parse(Globals.mostRecent.replace('@','')) )
				newDiv.append("<div class='pictureLabel'>New or Updated</div>");

			if ( !$("#row_" + person.row + " > div:last-child").offset() || $("#row_" + person.row + " > div:last-child").offset().left > -800 ) {

				$("#row_" + person.row)
					.append(newDiv).parent().height($("#row_" + person.row).height());
				Globals.scrollCount[person.row]++;
			}

			Globals.Q[person.row].push(person);
			Globals.Q2[person.row].push(newDiv);

			if ( $("#row_" + person.row + " > div:last-child").offset().left <= 205)
				Globals.scroll[person.row] = true;
			else
				Globals.scroll[person.row] = false;

			Globals.nextRow++;
			if (Globals.nextRow == Globals.maxRows) {
				Globals.nextRow = 0;
			}
		}
	},

	info : function(row, pos) {
		var slide = document.getElementById('row'+row+'picture'+pos+'i') || document.getElementById('row'+row+'picture'+pos+'_details');
		slide.style.opacity = '0.75';
		slide.style.filter = 'alpha(opacity=75)';
	},

	unfade : function(row, pos) {
		var slide = document.getElementById('row'+row+'picture'+pos+'i') || document.getElementById('row'+row+'picture'+pos+'_details');
		if ( slide ) { // avoiding a strange exception being thrown
			slide.style.opacity = '1';
			slide.style.filter = 'alpha(opacity=100)';
		}
	},

	removePersonFromQ : function (uuid) {
		for (var row = 0; row <= 2; row++ ) {
			for (var i = 0; i < Globals.Q[row].length; i++) {
				if ( Globals.Q[row][i].uuid == uuid) {
					Globals.Q[row].remove(i);
					Globals.Q2[row].remove(i);
					return;
				}
			}
		}
	},

	pause : function() {
		clearInterval(Globals.reDrawIntervalId);
		$("#speedDisplay").html("Paused").show();
	},

	play : function() {
		ScrollView.initTimer();
		$("#speedDisplay").html("Playing").show().fadeOut(5000);
	},

	// bi-directional.
	reDraw_v3 : function(direction, row, speed) {

		if (Globals.scroll[row]) {
			var modifier = -1;
			if ( !Globals.Q2[row][Globals.scrollCount[row]] )
				Globals.scrollCount[row] = 0;

			var tempRight = 0;

			if ($("#row_" + row).css("right") != "auto")
				tempRight = parseInt($("#row_" + row).css("right"));

			if (direction == "right") {
				$("#row_" + row).append(Globals.Q2[row][Globals.scrollCount[row]]);
				var personUuid = Globals.Q2[row][Globals.scrollCount[row]].attr("id");
				Globals.scrollCount[row]++;
				Globals.scrollRightEnd[row]++;
				if ( Globals.scrollCount[row] >= Globals.Q2[row].length )
					Globals.scrollCount[row] = 0;

				if ( Globals.scrollRightEnd[row] >= Globals.Q2[row].length )
					Globals.scrollRightEnd[row] = 0;

				(function(row) {
					$("#row_" + row)
						.animate( { right: "-=" + $("#row_" + row + " > div:first-child").width() + "px" },
								  {duration: speed || 950,
									 easing: "easeInBack",
								   complete:
											function() {
												$("#row_" + row).css( { right: "0px" } );
												$("#row_" + row + " > div:first-child").detach();
											}
								})
				})(row);

			}
			else {
				Globals.scrollCount[row]--;
				Globals.scrollRightEnd[row]--;
				if ( Globals.scrollCount[row] < 0 )
					Globals.scrollCount[row] = Globals.Q2[row].length - 1;

				if ( Globals.scrollRightEnd[row] < 0 )
					Globals.scrollRightEnd[row] = Globals.Q2[row].length - 1;

				var tWidth = Globals.Q2[row][ Globals.scrollRightEnd[row] ].css("width")
				Globals.Q2[row][ Globals.scrollRightEnd[row] ]
						 .width(0)
						 .insertBefore("#row_" + row + " > div:first-child")
  						 .animate({ width: "+=" + tWidth },
						  		  {duration: speed || 900,
								   callback:
										function() {
											$("#row_" + row + " > div:last-child").detach();
										},
									easing: "easeInOutCirc"
									});
			}
		}
	},

	increaseSpeed : function() {

		if ( Globals.scrollSpeed > 1000 )
			Globals.scrollSpeed -= 1000;

		$("#speedDisplay").html("Time between slides: " + ((Globals.scrollSpeed-1000) / 1000) + "s").show().fadeOut(5000);

		ScrollView.initTimer();

	},

	decreaseSpeed : function() {
		if ( Globals.scrollSpeed < 5000 )
			Globals.scrollSpeed += 1000;

		$("#speedDisplay").html("Time between slides: " + ((Globals.scrollSpeed-1000) / 1000) + "s").show().fadeOut(5000);

		ScrollView.initTimer();
	},

	goFullScreen : function() {
		if ( !Globals.isiPad && !confirm("Before switching to full screen mode, click Cancel and do the following:\n " +
				" For Windows: press F11. \n " +
				" For Mac OS X: Press Shift+Control+F.\n " +
				" Click OK if your browser is already in full screen mode" ) )
			return Globals.displayMode ? "interactive" : "handsfree";
		else {
			$("#scrolling_content, #detailsPane, #glass, #exitFullScreen, #exitFullScreenIpad").appendTo("body");
				$("#scrolling_content").css(
					{ top: 0,
					  left: 0,
					  height: "100%",
					  width: "100%",
					  position: "absolute"}).show();
			$("#headerText, #build, #dt_print, #content, #pager, #perPageWrapper, #printLink, #disaster_selekta, #header, #footer, #menu, #searchForm, #blueBack, #blueBack, #wrapper_menu, #skip, #menuwrap").hide();
			$("body").css({backgroundColor : "white" });
			Globals.maxRows = Math.ceil($(window).height()/350) > 4 ? 4 : Math.ceil($(window).height()/350)
			Globals.imageHeight = Math.floor(($(window).height() - (2*(Globals.rowPadding+Globals.imageBorder))) / Globals.maxRows);
			Globals.initDone = 1;
			searchSubset();
			$(document).bind("keyup", function(event) {
					if ( event.keyCode == 27 )
						ScrollView.exitFullScreen();
			});
			setTimeout(function() { if ( !Globals.isiPad ) { $("#exitFullScreen").show().fadeOut(4000) }
									else { $("#exitFullScreenIpad").show();  }}, 1000);
		}
	},

	exitFullScreen : function() {
		$(document).unbind("keyup");
		$("#headerText, #dt_print, #content, #pager, #perPageWrapper, #printLink, #disaster_selekta, #header, #footer,  #menu, #searchForm, #blueBack, #blueBack, #wrapper_menu, #skip, #menuwrap").show();
		$("#scrolling_content, #detailsPane, #glass").insertAfter("#beforeScrollingContent");
		$("#scrolling_content").css({ position: "relative" });
                // Why did someone code this? Comment out for PL-345.
		//$("body").css({backgroundColor : "#6289C0" });
		$("#exitFullScreenIpad").hide();
		Globals.initDone = 1;

		// reset to old values
		Globals.maxRows = Math.ceil(($(window).height()-210)/300) > 4 ? 4 : Math.ceil(($(window).height()-210)/300);
		Globals.imageHeight = Math.floor(($(window).height() - Globals.headerHeight - Globals.footerHeight - (2*(Globals.rowPadding+Globals.imageBorder))) / Globals.maxRows);

		searchSubset();
	}
}





