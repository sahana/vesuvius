/**
 * @name         INW Details View Object
 * @version      1.6
 * @package      inw
 * @author       Merwan Rodriguez <rodriguezmer@mail.nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

var DetailsView =
{
	drawPage : function() {
		var scont = $("#scrolling_content");

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

		scont.html("").append(tempDiv).append("<div style='clear:both'></div>").show();

		if ( Globals.searchMode == "solr" )
			this.setPager();
	},

	createStub : function(person) {
		var image = $("<img />").attr({ /*id : "picture_" + person.uuid,*/
							src : person.imageUrl,
							alt : isNaN(person.imageHeight) ? "no photo available" : "photo of person" })
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
		var statusTab =
			$("<div></div>").css("background-color", "#" + person.tagColor)
							.addClass("status")
							.html(person.statusSahanaFull);

		var edxl_id = $("<div></div>").css("float", "right")
									  .append("<div style='clear:both'></div>")
									  .html(person.mass_casualty_id);

		statusTab.append(edxl_id);

		var name = $("<div></div>").addClass("stubName").html(person.name);

		var details = $("<ul></ul>").addClass("stubDetails");
		var dataName = $("<span></span>").addClass("dataName");
		var dataValue = $("<span></span>").addClass("dataValue");

		details.append($("<li></li>").append(dataName.clone().html("Age:")).append(dataValue.clone().html(person.displayAge)));
		details.append($("<li></li>").append(dataName.clone().html("Gender:")).append(dataValue.clone().html(person.gender)));
		details.append($("<li></li>").append(dataName.clone().html("Updated:")).append(dataValue.clone().html(person.statusSahanaUpdated + " UTC")));


		var div =
			$("<div></div>")
				.addClass("stubText")
				/*.attr("id", person.uuid)*/
				.append(name)
				.append(statusTab)
				.append(details);

		return div;
	},

	setPager : function() {

		$("#pager").html("").css({display: "block"});
		$("#pager2").html("").css({display: "block"});
		$("#perPageWrapper").css({display: "block"});
		$("#sortBy").css({display: "block"});

		if ( Globals.searchMode == "sql" ) {
			if ( Globals.currPage == 1 && Globals.hasNextPage )
				$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + (Globals.currPage + 1) + "; searchSubset(true)'><img src='res/img/inw_next.png' alt='next page'/> </a>");
			else {
				if ( Globals.currPage != 1 )
					$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + (Globals.currPage - 1) + "; searchSubset(true)'><img src='res/img/inw_prev.png' alt='previous page'/></a>")
				if ( Globals.hasNextPage )
					$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + (Globals.currPage + 1) + "; searchSubset(true)'><img src='res/img/inw_next.png' alt='next page'/></a>" );
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
				$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + firstLabel + "; searchSubset(true)'> ... </a>");

			for ( var i = firstLabel; i <= lastLabel; i++ )
				if ( i != Globals.currPage)
					$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = parseInt(this.innerHTML); searchSubset(true)'>" + i + "</a>");
				else
					$("#pager").append("<span style='text-decoration: underline; font-weight: bold; margin-right:10px;'>" + i + "</span>");

			if ( lastLabel != lastPage )
				$("#pager").append("<a href='#' style='margin-right:10px;' onclick='Globals.currPage = " + lastLabel + "; searchSubset(true)'> ... </a>");

			$("#recordsFound").html(Utils.addCommas($("#recordsFound").html()));
		}
                $("#pager2").append($("#pager").clone().contents());
	}
};
