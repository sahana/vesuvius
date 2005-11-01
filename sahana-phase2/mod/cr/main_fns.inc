<?php
/* $Id; */

/**
* Default functions of CR
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


function shn_cr_default(){
}

function shn_cr_stat(){
}

function shn_cr_srch(){

  global $global;
  include($global['approot'].'/mod/cr/search.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
  switch($_REQUEST['seq']){
		case 'next':
		            echo "Search Results";
		            break;
		default :
		            _shn_cr_srch();
		            break;
		}
  
}

function shn_cr_acmp(){
	global $global;
  include($global['approot'].'/mod/cr/camp.inc');
	require_once($global['approot'].'/inc/handler_form.inc');

	// check action sequence
	switch($_REQUEST['seq']){
		case 'chk'		:
									_shn_cr_cadd_chk();
									break;
		case 'commit'	:
		            	_shn_cr_cadd_commit();
		            	break;
		default 			:
		            	_shn_cr_cadd_start();
		            	break;
		}
																																																						
}

function shn_cr_acma(){
}

function shn_cr_view(){
}
?>
