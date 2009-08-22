<?php
/**
 * DSM
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    dsm
 * @subpackage  dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
switch ($_REQUEST['sub']) {
	    case 'location' :
		    {
		    	
			    break;
		    }
	    case 'diagnosis' :
	    	{
	    		
	    	    break;
	    	}
        
	    case 'contact' :
	    	{
	    		_shn_dsm_case_tab_menu();
	    		_shn_dsm_edit_contacts();
	    	    break;
	    	}
	    default :
	    	{
	    		_shn_dsm_case_tab_menu();
	    		_shn_dsm_edit_case();
	    	}
    }

function _shn_dsm_case_tab_menu()
{
	$act = $_GET['act'];
	shn_adm_menuopen(_t("Disease Surviellance Module"));
 
	shn_adm_menuitem($act, _t("General Details"));
	shn_adm_menuitem($act . "&sub=location", _t("Location"));
	shn_adm_menuitem($act . "&sub=diagnosis", _t("Diagnosis"));
	shn_adm_menuitem($act . "&sub=contact", _t("Contact"));
	//shn_adm_menuitem($act . "&sub=risk", _t("Risk Analysis"));
	//shn_adm_menuitem($act . "&sub=cost", _t("Cost Estimation"));
	
	shn_adm_menuclose();
}
  
function _shn_dsm_edit_case()
{
    $pat_id = $_GET['p_uuid'];
    shn_form_fopen('edit_case');
    shn_form_hidden(array('seq'=>'form2'));
	_shn_dsm_populate_case($pat_id);
	shn_form_fsopen(_('General details'));
	shn_form_text(_('Name'),'pat_name','',array('value'=>$_SESSION['edit_case']['pat_name']));
	shn_form_fsclose();
	shn_form_submit(_t('Next'), "name='finish'");
	shn_form_fclose();
}

function _shn_dsm_edit_contacts()
{
	shn_form_fopen('edit_case','',array('req'=>false));
	shn_form_fsopen(_('Contact details'));
	$res = array();
	$res = _dsm_populate_contact($_SESSION['id']);
	shn_form_text(_('Mobile'),'mobile','',array('value'=>$res['mobile']));
	shn_form_text(_('Telephone'),'tele','',array('value'=>$res['telephone']));
	shn_form_text(_('Address'),'add','',array('value'=>$res['address']));
	shn_form_text(_('Email'),'email','',array('value'=>$res['email']));
	shn_form_fsclose();
	shn_form_fclose();
}

function update()
{
	
}
