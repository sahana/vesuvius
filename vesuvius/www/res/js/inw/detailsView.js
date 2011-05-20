/**
 * @name         INW Details View Object
 * @version      1.6
 * @package      inw
 * @author       Merwan Rodriguez <rodriguezmer@mail.nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

var DetailsView =
{
	drawPage : function() {
		var content = $("#scrolling_content");

		clearInterval(Globals.reDrawIntervalId);
		$("#scrollControls").hide();
		$("#displayMode").val("interactive");
		$("#printLink").show();

		var tempDiv = $("<div></div>");
		for ( var i = 0; i < Globals.resultSet.length; i++ ) {
			var p = new Person();

			if ( Globals.resultSet[i])
				p.init(Globals.resultSet[i]);
			else break;

			Globals.aPerson[p.uuid] = p;  //for the future.
				var stub = DetailsView.createStub(p);
				tempDiv.append(stub);
		}

		content.html("").append(tempDiv).append("<div style='clear:both'></div>").show()

		if ( Globals.searchMode == "solr" )
			this.setPager();

	},

	createStub : function(person) {
		var image = $("<img />").attr({ id : "picture_" + person.uuid,
										src : person.imageUrl })
								.addClass("stubPicture"),

			tempStub =  $("<div style='background-color: " + person.tagRGBA + "'></div>")
							   .css({border: "1px solid #" + person.tagColor, background : person.tagRGBA + " url(" + person.hospitalIcon + ") no-repeat right top"})
							   .addClass("ieStubBorder")
							   .addClass("stub")
							   .append(image)
							   .append(DetailsView.createInfoTag(person))
							   .click(function() { Utils.showDetail(Globals.aPerson[person.uuid]) });
		return tempStub;
	},

	createInfoTag : function(person) {
		var statusTab = $("<div class='status' id='status_" + person.uuid + "' style='background-color:#" + person.tagColor + "'>" + person.statusSahanaFull + "</div>");

		// should build this correctly (minimize mixing of html w/ javascript) in the future.
		var div = $("<div style='width: 210px;float:left; margin: 5px 5px 5px 5px; font-weight:700' id='" + person.uuid + "'></div>")
					.append("<div  id='name_" + person.uuid + "' style='overflow:hidden;white-space: nowrap; width: 170px;text-overflow: ellipsis; margin-bottom:3px;'>" + person.name + "</div>")
					.append(statusTab)
					.append("<div id='ageGender_" + person.uuid + "' style='float:left;font-weight:normal'><div style='float: left;width:55px;text-align:right;font-weight:bold;margin-right:5px;'>Age:</div> " + person.ageGroup + "<br /> <div style='float: left;width:55px;text-align:right;font-weight:bold;margin-right:5px;'>Gender:</div> " + person.gender + "</div>")
					.append("<div id='updated_" + person.uuid + "'style='float:left;white-space:nowrap;font-weight:normal'><div style='float: left;width:55px;text-align:right;font-weight:bold;margin-right:5px;'>Updated:</div> "
								+ person.statusSahanaUpdated + " UTC" );

		return div;
	},

	setPager : function() {

		$("#pager").html("").css({display: "block"});
		$("#perPageWrapper").css({display: "block"});
		$("#sortBy").css({display: "block"});
		
		if ( Globals.searchMode == "sql" ) {
			if ( Globals.currPage == 1 && Globals.hasNextPage )
				$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + (Globals.currPage + 1) + "; searchSubset()'><img src='res/img/inw_next.png' /> </a>");
			else {
				if ( Globals.currPage != 1 )
					$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + (Globals.currPage - 1) + "; searchSubset()'><img src='res/img/inw_prev.png' /></a>")
				if ( Globals.hasNextPage )
					$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + (Globals.currPage + 1) + "; searchSubset()'><img src='res/img/inw_next.png' /></a>" );
			}
		} else { 
			var lastPage = Globals.perPage == "All" ? 1 : Math.ceil(Globals.totalResults / Globals.perPage),
				currPage = Globals.currPage, //local reference == faster.
				firstLabel = currPage - 5 < 1 ? 1 : currPage - 5,
				lastLabel;
				
			if ( currPage + 5 > lastPage )
				lastLabel = lastPage;
			else if ( lastPage < 11 )
				lastLabel = lastPage;
			else if ( currPage + 5 < 11 )
				lastLabel = 11;
			else 
				lastLabel = currPage + 5;

			$("#pager").append("Page - ");
			if ( firstLabel != 1 )
				$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + firstLabel + "; searchSubset()'> ... </a>");

			for ( var i = firstLabel; i <= lastLabel; i++ )
				if ( i != Globals.currPage)
					$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = parseInt(this.innerHTML); searchSubset()'>" + i + "</a>");
				else
					$("#pager").append("<span style='text-decoration: underline; font-weight: bold; margin-right:10px;'>" + i + "</span>");

			if ( lastLabel != lastPage )
				$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + lastLabel + "; searchSubset()'> ... </a>");
				
			$("#recordsFound").html(Utils.addCommas($("#recordsFound").html()));
		}
	}
};