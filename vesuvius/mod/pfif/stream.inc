<?php
/**
 * @name         Person Finder Interchange Format
 * @version      2
 * @package      pfif
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0223
 */

global $global;
global $conf;
require_once($global['approot'].'/mod/pfif/lib_pfif.inc');



/**
 * stream some text...
 * @access public
 * @return string
 */
function shn_text_pfif_default() {
	echo "text";
}



/**
 * stream some rss2...
 * @access public
 * @return string
 */
function shn_xml_pfif_rss2Test() {
	global $global;
	require_once($global['approot'].'/3rd/FeedWriter/FeedWriter.php');


	//Creating an instance of FeedWriter class.
	//The constant RSS2 is passed to mention the version
	$TestFeed = new FeedWriter(RSS2);

	//Setting the channel elements
	//Use wrapper functions for common channel elements
	$TestFeed->setTitle('Testing & Checking the RSS writer class');
	$TestFeed->setLink('http://www.ajaxray.com/projects/rss');
	$TestFeed->setDescription('This is test of creating a RSS 2.0 feed Universal Feed Writer');

	//Image title and link must match with the 'title' and 'link' channel elements for RSS 2.0
	$TestFeed->setImage('Testing the RSS writer class','http://www.ajaxray.com/projects/rss','http://www.rightbrainsolution.com/images/logo.gif');

	//Use core setChannelElement() function for other optional channels
	$TestFeed->setChannelElement('language', 'en-us');
	$TestFeed->setChannelElement('pubDate', date(DATE_RSS, time()));

	//Adding a feed. Genarally this portion will be in a loop and add all feeds.

	//Create an empty FeedItem
	$newItem = $TestFeed->createNewItem();

	//Add elements to the feed item
	//Use wrapper functions to add common feed elements
	$newItem->setTitle('The first feed');
	$newItem->setLink('http://www.yahoo.com');
	//The parameter is a timestamp for setDate() function
	$newItem->setDate(time());
	$newItem->setDescription('This is test of adding CDATA Encoded description by the php <b>Universal Feed Writer</b> class');
	$newItem->setEncloser('http://www.attrtest.com', '1283629', 'audio/mpeg');
	//Use core addElement() function for other supported optional elements
	$newItem->addElement('author', 'admin@ajaxray.com (Anis uddin Ahmad)');
	//Attributes have to passed as array in 3rd parameter
	$newItem->addElement('guid', 'http://www.ajaxray.com',array('isPermaLink'=>'true'));

	//Now add the feed item
	$TestFeed->addItem($newItem);

	//Another method to add feeds from array()
	//Elements which have attribute cannot be added by this way
	$newItem = $TestFeed->createNewItem();
	$newItem->addElementArray(array('title'=>'The 2nd feed', 'link'=>'http://www.google.com', 'description'=>'This is test of feedwriter class'));
	$TestFeed->addItem($newItem);

	//OK. Everything is done. Now genarate the feed.
	$TestFeed->genarateFeed();
}



/**
 * Stream some atom 1.0...
 * @access public
 * @return string
 */
function shn_xml_pfif_atomTest() {
	global $global;
	require_once($global['approot'].'/3rd/FeedWriter/FeedWriter.php');

	// IMPORTANT : No need to add id for feed or channel. It will be automatically created from link.

	//Creating an instance of FeedWriter class.
	//The constant ATOM is passed to mention the version
	$TestFeed = new FeedWriter(ATOM);

	//Setting the channel elements
	//Use wrapper functions for common elements
	$TestFeed->setTitle('Testing the RSS writer class');
	$TestFeed->setLink('http://www.ajaxray.com/rss2/channel/about');

	//For other channel elements, use setChannelElement() function
	$TestFeed->setChannelElement('updated', date(DATE_ATOM , time()));
	$TestFeed->setChannelElement('author', array('name'=>'Anis uddin Ahmad'));

	//Adding a feed item. Generally this portion will be in a loop and add all feeds.

	//Create an empty FeedItem
	$newItem = $TestFeed->createNewItem();

	//Add elements to the feed item
	//Use wrapper functions to add common feed elements
	$newItem->setTitle('The first feed');
	$newItem->setLink('http://www.yahoo.com');
	$newItem->setDate(time());
	//Internally changed to "summary" tag for ATOM feed
	$newItem->setDescription('This is test of adding CDATA Encoded description by the php <b>Universal Feed Writer</b> class');

	//Now add the feed item
	$TestFeed->addItem($newItem);

	//OK. Everything is done. Now genarate the feed.
	$TestFeed->genarateFeed();
}
