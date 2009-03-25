<?php
shn_pnm_generaterss() {
	$query = "select link, headline, description from `pnm_headlines` limit 15";
	global $global;
	global $conf;
	$db=$global['db'];
	$res=$db->Execute('Query');

	while ($line = mysql_fetch_assoc($res))
		{
		    $return[] = $line;
		}




	$now = date("D, d M Y H:i:s T");

	$output = "<?xml version=\"1.0\"?>
		    <rss version=\"2.0\">
		        <channel>
		            <title>SAHANA Media and Press RSS</title>
		            <link>http://www.tracypeterson.com/RSS/RSS.php</link>
		            <description>This is the RSS feed of sahana media and press</description>
		            <language>en-us</language>
		            <pubDate>$now</pubDate>
		            <lastBuildDate>$now</lastBuildDate>
		            <docs>http://someurl.com</docs>
		            <managingEditor>nishantha@opensource.lk</managingEditor>
		            <webMaster>nishantha@opensource.lk</webMaster>
		    ";
		    
	//foreach ($return as $line)
	{
	    $output .= "<item><title>".htmlentities($line['headline'])."</title>
		            <link>".htmlentities($line['link'])."</link>
		            
	<description>".htmlentities(strip_tags($line['description']))."</description>
		        </item>";
	}
	$output .= "</channel></rss>";
	header("Content-Type: application/rss+xml");
	echo $output;
}
?>

