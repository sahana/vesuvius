/**
 * @name         INW Global Object
 * @version      1.6
 * @package      inw
 * @author       Merwan Rodriguez <rodriguezmer@mail.nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */

var Globals = {
	totalRecords : 0,
	totalResults  : null,
	searchTerm    : $.trim(document.getElementById("searchBox").value),
	language      : document.getElementById("language").value,
	refreshRate   : 3500,
	scrollSpeed   : 3000,
	rowPadding    : 18, // # of pixels padding each row
	imagePadding  : 18, // # of pixels padding between images on the same row
	imageBorder   : 4,  // size of the image border in pixels
	headerHeight  : $("#subheader").height() + $("#header").height(), // pixels in height of the header
	footerHeight  : 150,  // pixels in height of the footer
	enableConsole : false,
	nextRow       : 0,
	initDone      : 0,
	uuidSkipList  : new Array("1", "2"), // uuid's to always skip (sahana uuid)
	scrollCount : new Array(-1, -1, -1),
	scrollRightEnd : new Array(0, 0, 0),
	aPerson : [],
	perPage : 25,
	currPage : 1,
	oldCurrPage : 1, // place holder
	maxRows :  Math.ceil(($(window).height()-210)/300) > 4 ? 4 : Math.ceil(($(window).height()-210)/300),
	searchMode : "solr",
	sortedBy : "",  //default value
	json : "",
	displayMode : true,
	personListOld : [], // old list of persons for comparison
	personList : [], // list of people we WILL download information for
	Q : [],
	Q2 : [],
	incident : $("#shortName").val(),
	results : [],
	updaterId : null,
	updaterTimer : 5000,  //5 seconds
	doRefresh : true,
	isiPad : false,
	timeElapsed : 0,
	hasNextPage : false,
	searchTerms : ""
};
