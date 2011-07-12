<?
/**
 * @name         REZ cache script
 * @version      1alpha
 * @package      rez
 * @author       Ramindu Deshapriya <rasade88@gmail.com>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.05.24
 */
global $global;

require_once ($global['approot'].'/inc/handler_db.inc');
include_once ($global['approot'].'/inc/lib_errors.inc');

function rez_cache_db() {
	global $global;
	$stringFile = fopen($global['approot'].'/mod/rez/rez_strings.inc', 'w');
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
			fwrite($stringFile, "_t('RESOURCE_PAGES_TITLE_".strtoupper($row['rez_page_title'])."|".$row['rez_page_title']."')\n");
			fwrite($stringFile, "_t('RESOURCE_PAGES_CONTENT|".$row['rez_content']."')\n");
		}
	}
	fclose($stringFile);
}
