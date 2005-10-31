<?php
/* $Id; */

/**
* Default actions for CMS Main
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
 * add new camp
*/
function shn_cms_cadd(){
	global $global;
	include($global['approot'].'/mod/cms/camp.inc');
	require_once($global['approot'].'/inc/handler_form.inc');

	// check action sequence
	switch($_REQUEST['seq']){
	case 'form':
							_shn_cms_cadd_form();
							break;
	case 'chk':
							_shn_cms_cadd_chk();
							break;
	case 'commit':
							echo "New Camp Created";
							break;
	default :
							_shn_cms_cadd_guide();
							break;
	}
	//_shn_cms_cadd();
}

/**
 * edit existing camp
*/
function shn_cms_cedt(){
}

/**
 * close camp
*/
function shn_cms_cext(){
}

/**
 * add new victim
*/
function shn_cms_vadd(){
}
			
/**
 * edit existing victim
*/
function shn_cms_vedt(){
}


/**
 * update victim status
*/
function shn_cms_vupd(){
}


/**
 * add new relief worker
*/
function shn_cms_wadd(){
}

/**
 * edit existing relief worker
*/
function shn_cms_wedt(){
}

/**
 * update relief worker status
*/
function shn_cms_wupd(){
}

/**
 * camp statistics
*/
function shn_cms_stat(){
}

/**
 * search
*/
function shn_cms_srch(){
}





?>
