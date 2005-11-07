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
?>
	<h1><center>Camps Registry</center></h1>
	<br>
<?php
	//shn_cr_arpt();
?>
	<p>The Camps Registry is the central Registry to manage Camps and individual Camp Management Systems<br>
	This Registry can be used to add camps, edit camps, view information on camps based on different categories and to search for camps.  </p><br>
	
	
	<div id="left">
	<div id="heading">Camp Information</div>
	Camp Name : <br/>
	</div>
	
	<div id="center">
	<div id="heading">Victim Information</div>
	No of Victims : <br/>
	</div>
	
	<div id="right">
	<div id="heading">Service Information</div>
	Services : <br/>
	</div>
	<?php 
	
		shn_cr_srpt();
	
}
function shn_cr_stat(){
}

function shn_cr_srch(){

  global $global;
  include($global['approot'].'/mod/cr/search.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
  switch($_REQUEST['seq']){
		case 'next'		:
		            	echo "Search Results";
		           	 	break;
		case 'commit'	:
									_shn_cr_srch_rst($_POST['cmp_id'],$_POST['opt_camp_type']);
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
									if(_shn_cr_validate_error())
										_shn_cr_cadd_start(true);
									else
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

function shn_cr_ecmp(){
	global $global;
  include($global['approot'].'/mod/cr/edit.inc');
	require_once($global['approot'].'/inc/handler_form.inc');

	// check action sequence
	switch($_REQUEST['seq']){
		case 'chk'		:
									//if(_shn_cr_validate_error())
										//_shn_cr_edt_start(true);
									//else
									_shn_cr_cedt_chk();
									break;
		case 'commit'	:
		            	_shn_cr_cedt_commit();
		            	break;
		case 'disp'		:
										_shn_cr_cedt_start();
									break;	
		default 			:
									_shn_cr_search_edt_frm();
		            	//_shn_cr_cedt_start();
		            	break;
		}
																																																						
}


function shn_cr_rpt(){
 global $global;
 include($global['approot'].'/mod/cr/reports.inc');
 require_once($global['approot'].'/inc/handler_form.inc');

 // check action sequence
 switch($_REQUEST['seq']){
 case 'viewall'    :
					      echo "Reports";
								break;
 case 'commit' :
                _shn_cr_rpt_rst();
                break;
 case 'viewloc' :
 								echo "loc";
                _shn_cr_rpt_rst();
                break;
 default       :
 								echo "default";
								_shn_cr_rpt();
								break;
																																																									     }
																																																										 
}

function shn_cr_arpt(){
	global $global;
	include($global['approot'].'/mod/cr/reports.inc');
	_shn_cr_rpt_all(); 
}

function shn_cr_lrpt(){
	global $global;
 	include($global['approot'].'/mod/cr/reports.inc');
	_shn_cr_rpt_loc();
}


function shn_cr_srpt(){
	global $global;
 	include($global['approot'].'/mod/cr/reports.inc');
	_shn_cr_rpt_summary();
}

function shn_cr_acma(){
}

function shn_cr_view(){
				}
								 

				?>
