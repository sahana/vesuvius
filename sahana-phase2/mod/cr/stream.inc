<?php
/*
 * Created on Apr 6, 2006
 *
 * To change the template for this generated file go to
 * Window - Preferences - PHPeclipse - PHP - Code Templates
 */
 function shn_cr_default()
 {
 	echo "hello";
 }
 function shn_cr_loadmap()
 {
	global $global; 
 	include($global['approot'].'/inc/lib_gis/plugins/google_maps/handler_google_maps.inc');
 	
 	load_map($_GET['wkey'],$_GET['ekey']);
 	
 }
 function shn_cr_acmp(){
	global $global;
  include($global['approot'].'/mod/cr/camp.inc');
	require_once($global['approot'].'/inc/handler_form.inc');

	// check action sequence
	switch($_REQUEST['seq']){
		case 'chk'		:
									if($conf['gis']=='false'){
										if(_shn_cr_validate_error())
											_shn_cr_cadd_start(true);
									}
										_shn_cr_cadd_chk();
									break;
		case 'commit'	:
		            	_shn_cr_cadd_commit();
		            	break;
		case 'gis'		:
									if(_shn_cr_validate_error())
									  _shn_cr_cadd_start(true);
									else								
										_shn_cr_sel_map();
									break;
		default 			:
		            	_shn_cr_cadd_start();
		            	break;
		}
																																																						
}

