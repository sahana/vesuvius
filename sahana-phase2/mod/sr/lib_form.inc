<?php
/**
* The Situation Report (SITRep) Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Respere - http://respere.com/
* @package		sahana
* @subpackage   sr
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*  
*/
include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';
include_once "handler_forms.inc";
include_once "handler_report_store.inc";


function shn_sr_form_create()
{
	// capture basic "report" information
	shn_sr_report_register();
	
	# When form is submitted, check for Alert? is ticked.
	# If it is, then generate a global alert.
	
	
	
	// strore gathered "report" information
	//shn_sr_store_reg_new_report();
	
	// capture other details of the "report"
	//shn_sr_report_detail_form();
}

function shn_sr_form_tabs()
{
	?>
        <div id="submenu_v">
        <?php if(!($tab=="types")) {?><a href="index.php?mod=dir&act=adm_types"><?php }echo '<b>'._t('Add Types').'</b>'?></a>
        <?php if(!($tab=="delete")) {?> <a href="index.php?mod=dir&act=adm_delete"><?php } echo '<b>'._t('Delete Types').'</b>' ?></a>
        <?php if(!($tab=="import")) {?><a href="index.php?mod=dir&act=adm_import"><?php }echo '<b>'._t('Import Data').'</b>' ?></a>
        </div>
        <br>
        <?php
}
