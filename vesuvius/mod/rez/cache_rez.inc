<?
global $global;

require_once ($global['approot'].'/inc/handler_db.inc');
include_once ($global['approot'].'/inc/lib_errors.inc');

function rez_cache_db() {
	$stringFile = fopen($global['approot'].'/res/rez_strings.inc', 'w');
	$q = "
			select *
			from rez_pages
			where rez_visibility = 'Public'
			order by rez_menu_order asc;
		";
	$res = $global['db']->Execute($q);
	if($res){
		// build page descriptions
		while($row = $res->FetchRow() ) {
			fwrite($stringFile, "_t('".$row['rez_page_title']."')\n");
			fwrite($stringFile, "_t('".$row['rez_content']."')\n");
		}
	}
	fclose($stringFile);
}
