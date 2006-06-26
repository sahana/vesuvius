<?php
/** 
* 
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
 * Show GIS Map with Wiki info
 */
function show_wiki_map()
{
	global $global;
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_map();
}

function add_wiki_detail()
{
	
}

function show_wiki_add_detail($errors=false)
{
	if($errors){
		echo "Errors";
	}
	global $global;
	include_once $global['approot']."/inc/lib_form.inc";
?>
	<h2><?=_("Add Wiki Detail")?></h2>
<?php
	$type_help="yo";
	$url_help="type url";
	$date_help="type date";
	
	shn_form_fopen(awk);
	shn_form_fsopen(_("Main Details"));
	shn_form_text(_("Name of Detail"),"wiki_name",'size="50"',array('req'=>true,'help'=>$type_help));
	shn_form_opt_select("opt_wikimap_type",_("Wiki Type"),array('help'=>$type_help));
	shn_form_textarea(_("Detail Summary"),"wiki_text",'size="50"');
	shn_form_fsclose();
	shn_form_fsopen(_("Extra Details"));
	shn_form_text(_("URL"),"wiki_url",'size="50"',array('help'=>$url_help));
	shn_form_text(_("Date of Event"),"wiki_evnt_date",'size="50"',array('help'=>$date_help));
	shn_form_fsclose();
	shn_form_fsopen(_("Wikimap Options"));
	shn_form_text(_("Author"),"wiki_author",'size="50"',array('help'=>$type_help));
	shn_form_checkbox(_("Publicly Editable"),"edit_public");
	shn_form_fsclose();
	shn_form_submit(_("Add Detail"));
	shn_form_fclose();
}
?>
