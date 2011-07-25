<?

// define app root since we are outside the main execution thread~index.php
$global['approot'] = getcwd()."/../";

// required libraries
require($global['approot']."/conf/sahana.conf");
require($global['approot']."/3rd/adodb/adodb.inc.php");
require($global['approot']."/inc/handler_db.inc");


/*
function submitSitemap($sitemapURL) {

		$googleLink = "/webmasters/sitemaps/ping?sitemap=" . urlencode($sitemapURL);
		echo "<BR> Link is: $sitemapURL";
		echo "<BR> Link is: $googleLink";

		echo "<BR>Submitting sitemap to Google...";
		$host = "www.google.com";

		$fp = fsockopen( $host, 80, &$errno, &$errstr, 120);
		if( !$fp ) {
		echo "Failed connecting to $host.";
		} else {
				fputs( $fp, "GET $googleLink HTTP/1.0\n");
				fputs( $fp, "Accept: * / *\n");
				fputs( $fp, "\n" , 1);
				$output = "";

		while( !feof( $fp ) ) {
				$output .= fgets( $fp, 1024);
		}

		echo "<BR>Done.";

		echo "<BR>Answer from Google is: <HR>$output";
		}

}
*/

$sXML = "";
$pages = array();

$sXML .=
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n".
"<urlset xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd\" xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\n";


// get a list of all public events and events where the user has access
$q = "
SELECT *, ((UNIX_TIMESTAMP() - rez_timestamp) / 86400) as rez_time
FROM rez_pages;
";

$result = $global['db']->Execute($q);
while (!$result == NULL && !$result->EOF) {
	$pages[] = array('page_title' => $result->fields["rez_page_title"], 'url' => $result->fields["rez_page_id"]);
	$result->MoveNext();
}

if(count($pages)) {
	foreach($pages as $page) {
//		list($sLoc, $sLastMod, $sModifiedDaysDiff) = $aPage;

//		$sChangeFreq = (($sModifiedDaysDiff <= 1) ? "daily" : (($sModifiedDaysDiff <= 7) ? "weekly" : (($sModifiedDaysDiff <= 31) ? "monthly" : "yearly")));

		$sXML .=
"\t<url>\n".
"\t\t<loc>".$page['url']."</loc>\n".
//"\t\t<lastmod>".date("Y-m-d", $sLastMod)."</lastmod>\n".
//"\t\t<changefreq>".$sChangeFreq."</changefreq>\n".
"\t\t<priority>1</priority>\n".
"\t</url>\n";

	}
}

$sXML .= "</urlset>\n";

header('Content-Type: text/xml');
echo $sXML;

/*
$sitemapPath = WB_URL . $fSep . "/sitemap.xml";
submitSitemap($sitemapPath);
*/




