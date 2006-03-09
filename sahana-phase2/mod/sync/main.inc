<?php
/* $Id: main.inc,v 1.1 2006-03-09 09:17:32 janakawicks Exp $ */

/**
 * Main Controller of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Chamindra de Silva <chamindra@opensource.lk>
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once($global['approot']."/inc/lib_st_ajax.inc");

/* {{{ Main Menu */
/**
 * This function defines the menu list.
 * @access public
 * @return void
 */
function shn_sync_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen(_("Synchonization Module"));

    shn_mod_menuitem("default",_("Home"));
    shn_mod_menuitem("dsc",_("Discovery Servers"));
    shn_mod_menuitem("inst",_("Sync With Sahana Instance"));
    shn_mod_menuitem("bcst",_("Broadcast Avalibility"));
    shn_mod_menuitem("down",_("Download Data"));
    shn_mod_menuitem("up",_("Upload Data"));

    shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
/* }}} */	

/* {{{ Action: Discovery Servers */
/**
 *
 * This is a Discovery Servers.
 *
 * @access public
 * @return void
 */
function shn_sync_dsc()
{
    global $global;
    require_once($global['approot'].'mod/sync/discovery.inc');
    shn_sync_descovery_form();
}
/* }}} */

/* {{{ Action: Dump Data */
/**
 *
 * This is a Dumping data.
 *
 * @access public
 * @return void
 */
function shn_sync_down()
{
    global $global;
    global $conf;
    require_once($global['approot'].'mod/sync/down.inc');
    
    //link to download the base
?>
<a href="stream.php?stream_type=xml&mod=sync&act=down&type=base">Download base data</a><br />
<?php
    //link to download the modules
    //get the list of modules
    $sql = "SELECT module_id FROM modules WHERE active = TRUE group by 1";
    $arr = $global['db']->GetAll($sql);
    foreach ($arr as $mods){
?>
<a href="stream.php?stream_type=xml&mod=sync&act=down&type=module&module_type=<?=$mods['module_id'];?>">Download <?=$conf['mod_'.$mods['module_id'].'_name'];?> Data </a><br />
<?php
    }
}
/* }}} */

/* {{{ Action: Default (Home Page) */
/**
 * 
 * This function displays the home page of the missing person registry
 *
 * @access public
 * @return void
 */
function shn_sync_default()
{
    global $global;
    require($global['approot'].'mod/sync/home.inc');
}
/* }}} */

/* {{{ Action: Find */
/**
 * This function displays the basic search form
 * @deprecated 
 * @todo shn_mpr_fndmp to be removed 
 * @access public
 * @return void
 */
function shn_mpr_fndmp()
{
    global $global;

    $header=array('method'=>'POST','action'=>'index.php?mod=mpr&act=addmp','id'=>'formset');
    shn_form_open($header,false);

?>  <input type="text" value="hello"/>          <?php

    shn_form_close();
}
/* }}} */

/* {{{ Action: Edit */
/**
 * This is the MPR Edit Controller
 * @access public
 * @return void
 */
function shn_mpr_editmp()
{
    global $global;
    require($global['approot'].'mod/mpr/edit.inc');
    require_once($global['approot'].'mod/mpr/add.inc');
	//validation
	switch ($_REQUEST['seq']) {
	
	    case 'entry':
            echo '<h1 align="center">'._('Edit Missing Person Entry').'</h1>';
	        if(shn_mpr_editmp_validate()){
                shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
	        }else
	            shn_mpr_editmp_entry(true);
	    break;
	    
        case 'trackers' :
            echo '<h1 align="center">'._('Edit Missing Person Entry').'</h1>';
            shn_mpr_editmp_upload();
        break;
	    case 'upload_pic' :
            echo '<h1 align="center">'._('Edit Missing Person Entry').'</h1>';
	        if(! shn_mpr_editmp_upload_pic())
	            shn_mpr_editmp_upload(true);
	        else
	            shn_mpr_editmp_confirm();
	    break;
	
	    case 'commit' :
	        shn_mpr_editmp_commit();
            //Send Back to the Main Page
            shn_mpr_default();
	    break;

        case 'add_tracker' :
            echo '<h1 align="center">'._('Edit Missing Person Entry').'</h1>';
	        $_POST = null;
	        $_SESSION['mpr_add']['add_tracker'] = null;
	        echo '<h1 align="center">'._('Add a tracker to').' '.
	            $_SESSION['mpr_edit']['entry']['full_name'].' </h1>';
            $_SESSION['mpr_add']['add_tracker']['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	        // todo: check the p_uuid exists or not *** VERY URGENT
	        shn_mpr_addmp_reporter();
	    break;

        case 'report_person' :
            echo '<h1 align="center">'._('Edit Missing Person Entry').'</h1>';
            if(shn_mpr_addmp_reporter_validate() || isset($_GET['offset']) ){
                if($_POST['reported_before'] == 'yes' || isset($_GET['offset']) ) {
                    require_once($global['approot'].'mod/mpr/search.inc');
                    if(isset($_GET['offset'])){
                        $arr = shn_mpr_search_result_vw($_SESSION['mpr']['search']['subquery'],
                            $_GET['offset'],true);
                        shn_mpr_search_select($arr);
                    }else{
                        $search_sql = new SearchQuery();
                        $search_sql->set_name($_POST['rep_full_name']);
                        $search_sql->set_address($_POST['rep_address']);
                        $search_sql->set_phone($_POST['rep_phone']);
                        $arr = shn_mpr_search_result_vw($search_sql->get_sql(),-1,true);
                        shn_mpr_search_select($arr);
                    }
                }else{
                    shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['add_tracker']['p_uuid']);
                    shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']); 
                    $_SESSION['mpr_add']['add_tracker']=null;
                }
            }else{
                echo '<h1 align="center">'._('Add a tracker to').' '.$_SESSION['mpr_add']['add_tracker']['name'].' </h1>';
                shn_mpr_addmp_reporter(true);
            }            
        break; 
        case 'tracker_select' :
            shn_add_person_to_report ( $_SESSION['mpr_edit']['entry']['p_uuid'],
                $_GET['tracker_id'], $_SESSION['mpr_add']['report_person']['rep_relation']);
            $_SESSION['mpr_add']['add_tracker']=null;
            shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
        break;
        case 'del_tracker' :
            echo '<h1 align="center">'._('Edit Missing Person Entry').'</h1>';
            //todo : Clean the input
            $tracker_uuid = $_GET['tracker_id'];
            shn_edit_del_tracker ($_SESSION['mpr_edit']['entry']['p_uuid'],
                $tracker_uuid);
            shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
            
        break;
	    default:
            echo '<h1 align="center">'._('Edit Missing Person Entry').'</h1>';
	        //load details
	        $_SESSION['mpr_edit']['entry'] = null;
	        shn_mpr_editmp_load($_GET['id']);
	        shn_mpr_editmp_entry();            
	    break;
	
    }

}
/* }}} */

/* {{{ Action: View */
/**
 * This is the MPR View Controller
 * @access public
 * @return void
 */
function shn_mpr_viewmp()
{
    global $global;
    require($global['approot'].'mod/mpr/view.inc');
    echo '<h1 align="center">'._('View Person').'</h1>';
    shn_mpr_view($_GET['id']);
}
/* }}} */

/* {{{ Action: Add Tracker */
/**
 * This is the MPR Add Tracker Controller
 * @access public
 * @return void
 */
function shn_mpr_add_tracker()
{
    global $global;
    require($global['approot'].'mod/mpr/add.inc');
    //Controller
    switch ($_REQUEST['seq']) {
	    case 'report_person' :
            if(shn_mpr_addmp_reporter_validate()){
                 if($_POST['reported_before'] == 'yes') {
                    require_once($global['approot'].'mod/mpr/search.inc');
                    $search_sql = new SearchQuery();
                    $search_sql->set_name($_POST['rep_full_name']);
                    $search_sql->set_address($_POST['rep_address']);
                    $search_sql->set_phone($_POST['rep_phone']);
                    $arr = shn_mpr_search_result_vw($search_sql->get_sql(),-1,-1,true);
                    shn_mpr_search_select($arr);
                }else{
                    shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['add_tracker']['p_uuid']);
                    // todo: redirect back to search results (that'll be great)
                    shn_mpr_default();                
                    $_SESSION['mpr_add']['add_tracker']=null;
                }
            }else{
                echo '<h1 align="center">'._('Add a tracker to').' '.$_SESSION['mpr_add']['add_tracker']['name'].' </h1>';
                shn_mpr_addmp_reporter(true);
            }
        break;
        
        case 'tracker_select' :
            shn_add_person_to_report ( $_SESSION['mpr_add']['add_tracker']['p_uuid'], 
                $_GET['tracker_id'], $_SESSION['mpr_add']['report_person']['rep_relation']);
            shn_mpr_default();
            $_SESSION['mpr_add']['add_tracker']=null;
        break;

        default:
            //clean the $_POST to remove the conflicts
                $_POST = null;
                $_SESSION['mpr_add']['add_tracker'] = null;
                echo '<h1 align="center">'._('Add a tracker to').' '.$_GET['name'].' </h1>';
                $_SESSION['mpr_add']['add_tracker']['p_uuid'] =
$_GET['id'];
                $_SESSION['mpr_add']['add_tracker']['name'] =
$_GET['name'];
                // todo: check the p_uuid exists or not *** VERY URGENT
                shn_mpr_addmp_reporter();
        break;
    }
}
/* }}} */

/* {{{ Action: Delete Tracker */
/**
 * This is the MPR Delete Tracker Controller
 * @access public
 * @return void
 */
function shn_mpr_del_tracker()
{
    global $global;
    
            if(shn_mpr_addmp_reporter_validate()){
                shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['add_tracker']['p_uuid']);
                // todo: rediddrect back to search results (that'll be great)
                #shn_mpr_default();                
                $_SESSION['mpr_add']['add_tracker']=null;
            }else{
                echo '<h1 align="center">'._('Add a tracker to').' '.$_SESSION['mpr_add']['add_tracker']['name'].' </h1>';
                shn_mpr_addmp_reporter(true);
            }
}
/* }}} */

/* {{{ Action: Add */
/**
 * This is the MPR Add Controller
 * @access public
 * @return void
 */
function shn_mpr_addmp()
{
    global $global;
    require($global['approot'].'mod/mpr/add.inc');

    if($_GET['type'] == 'found')
        $_SESSION['mpr_add']['entry_type'] = 'found';
    elseif($_GET['type'] == 'missing')
        $_SESSION['mpr_add']['entry_type'] = 'missing';

    if($_SESSION['mpr_add']['entry_type'] == 'found')
        $heading = '<h1 align="center">'._('Found Person Entry').'</h1>';
    elseif($_SESSION['mpr_add']['entry_type'] == 'missing')
        $heading = '<h1 align="center">'._('Missing Person Entry').'</h1>';

    //Controller
	switch ($_REQUEST['seq']) {
	    case 'entry':
	        if(shn_mpr_addmp_validate()){
	            //clean the $_POST to remove the conflicts
	            $_POST = null;
                echo $heading;
                echo '<h2 align="center">('._('Upload Person\'s Picture').')</h2>';
	            shn_mpr_addmp_upload();
	        }else{
                echo $heading;
                echo '<h2 align="center">('._('Person Details').')</h2>';
	            shn_mpr_addmp_entry(true);
            }
	    break;

        case 'tracker_back' :
            echo $heading;
            echo '<h2 align="center">('._('Reporting Person').')</h2>';
            shn_mpr_addmp_reporter();
        break;
	
        case 'tracker_select' :
            $_SESSION['mpr_add']['entry']['tracker_id'] = $_GET['tracker_id'];
            echo $heading;
            echo '<h2 align="center">('._('Final Confirmation').')</h2>';
            shn_mpr_addmp_confirm();
        break;

	    case 'report_person' :
	        if(shn_mpr_addmp_reporter_validate() || isset($_GET['offset'])){
                //if reported before then send to the search 
                if($_POST['reported_before'] == 'yes' || isset($_GET['offset'])) {
                    require_once($global['approot'].'mod/mpr/search.inc');
                    if(isset($_GET['offset'])){
                        $arr = shn_mpr_search_result_vw($_SESSION['mpr']['search']['subquery'], 
                            $_GET['offset'],true);
                        shn_mpr_search_select($arr);
                    }else{
                        $search_sql = new SearchQuery();
                        $search_sql->set_name($_POST['rep_full_name']);
                        $search_sql->set_address($_POST['rep_address']);
                        $search_sql->set_phone($_POST['rep_phone']); 
                        $arr = shn_mpr_search_result_vw($search_sql->get_sql(),-1,true);
                        shn_mpr_search_select($arr);
                    }
                }else{
                    echo $heading;
                    echo '<h2 align="center">('._('Final Confirmation').')</h2>';
	                shn_mpr_addmp_confirm();
                }
	        }else{
                echo $heading;
                echo '<h2 align="center">('._('Reporting Person').')</h2>';
                shn_mpr_addmp_reporter(true);
            }
	    break;
	
	    case 'upload_pic' :
	        if(shn_mpr_addmp_upload_pic()){
                echo $heading;
                echo '<h2 align="center">('._('Reporting Person').')</h2>';
                shn_mpr_addmp_reporter();
	        }else{
                echo $heading;
                echo '<h2 align="center">('._('Upload Person\'s Picture').')</h2>';
                shn_mpr_addmp_upload(true);
            }
	    break;
	
	    case 'commit' :
	        shn_mpr_addmp_commit();
	    break;
	
	    default:
            echo $heading;
            echo '<h2 align="center">('._('Reporting Person').')</h2>';
	        shn_mpr_addmp_entry();
        break;
	}
}
/* }}} */

/* {{{ Action: Search */
/**
 * This is the Search Controller
 * @access public
 * @return void
 */
function shn_mpr_search()
{
    global $global;
    echo '<h1 align="center">Search</h1>';
    require($global['approot'].'mod/mpr/search.inc');

    //Controller for Normal Search
	if($_GET['act']=='search'){
	    switch ($_REQUEST['seq']) {
	        case 'result' :
	            shn_mpr_search_default();
                if($_GET['offset'])
                    shn_mpr_search_result_vw($_SESSION['mpr']['search']['subquery'],
                        $_GET['offset']);
                else{
    	            $search_sql = new SearchQuery();
                    $search_sql->set_name($_POST['name']);
                    $search_sql->set_serial_no($_POST['idcard']);
                    $search_sql->isvictim = true; 
                    if ($_REQUEST['type'] == 'missing')
                        $search_sql->missing_only = true; 
                    $arr = shn_mpr_search_result_vw($search_sql->get_sql());
                }
	        break;
	        default:
	            shn_mpr_search_default();
	        break;
	
	    }
	//Controller for Advance Search
	}elseif($_GET['act']=='search_adv'){
	    switch ($_POST['seq']) {
	        case 'result' :
	            shn_mpr_search_result();
	        break;
	        default:
	            shn_mpr_search_advance();
	        break;
	
	    }
	}
}
/* }}} */

/* {{{ Action: Advance Search */
/**
 * This is the Advance Search Controller
 * @todo Add Advance Filters
 * @access public
 * @return void
 */
function shn_mpr_search_adv()
{
    global $global;
    echo '<h1 align="center">Search</h1>';
    require($global['approot'].'mod/mpr/search.inc');
}
/* }}} */

/* {{{ Action: Audit */
/**
 * This is the Auditing Controller
 * @todo Need to discuss this further
 * @access public
 * @return void
 */
function shn_mpr_auditmp()
{
    global $global;
    require($global['approot'].'mod/mpr/audit.inc');
    shn_audit_show($_GET['id']);
}
/* }}} */

/* {{{ Status */
/**
 * This is function change the status from missing to alive and well
 * @access public
 * @return void
 */
function shn_mpr_status()
{
    global $global;

    //clean and check
    $update_array['p_uuid'] = shn_db_clean($_GET['id']);
    if(! $global['db']->Execute("SELECT p_uuid FROM person_status WHERE p_uuid = {$update_array['p_uuid']}") ){
        shn_mpr_default();
    }else {
	    //flush and refill baby
	    $global['db']->Execute("DELETE FROM person_status WHERE p_uuid = {$update_array['p_uuid']}");
        $update_array['p_uuid'] = $_GET['id'];
	    //Insert Into person_status mis
	    $update_array['opt_status'] = 'ali';
	    shn_db_insert($update_array,'person_status');
	    //reset $update_array 
	    $update_array = null;
	    shn_mpr_default();
    }
}
/* }}} */

/* {{{ Show Thumbnail */
/**
 *
 * This is function show the tumbnail if available and say "Image not
 * available" otherwise
 *
 * @todo Need to move to a different file, possibly to a library.
 * @param mixed $p_uuid 
 * @access public
 * @return void
 */
function shn_show_thumb($p_uuid)
{
    global $global;
    
    //Since we don't know the extension
    $file = $global['approot'].'www/tmp/thumb_'.$p_uuid.'*';
 
    //Need a better way
    $filename = `ls $file`;
    $filename = trim($filename);
    
    $ext = substr($filename,strlen($file),(strlen($filename)-strlen($file)));
    
    //if image is not available 
    if(! file_exists($global['approot']."www/tmp/ori_$p_uuid.$ext") ){
        echo _("Image Not Available");
        return false;
    }
        

    $info = getimagesize($global['approot']."www/tmp/ori_$p_uuid.$ext");
    $height = $info[1]+20;
    $width = $info[0]+20;
 
    $url = $_SERVER["SERVER_NAME"].$_SERVER["PHP_SELF"];
    //remove the index.php
    $url = substr($url,0,strlen($url)-9);
    //add http://
    $url = 'http://'.$url."/tmp/ori_$p_uuid.$ext";
?>
    <a title="<?= _('Click to see the original size'); ?>" href="#" onclick="window.open('<?=$url?>','hello','width=<?=$width?>,height=<?=$height?>,scrollbars=no,status=no');return false;" >
    <img border="0" src="tmp/<?='thumb_'.$p_uuid.'.'.$ext?>" />
    </a>
<?php
    return true;
}
/* }}} */

/* {{{ get field option description */
/**
 *
 * Shows the Description of the field_option, when given the vaule
 *
 * @todo Need to move this to a library.
 * @param mixed $value 
 * @param mixed $field_name 
 * @access public
 * @return void
 */
function shn_get_field_opt($value,$field_name)
{

    global $global;
    return $global['db']->GetOne("SELECT option_description FROM field_options WHERE option_code = '$value' AND field_name='$field_name'");
}
/* }}} */

/* {{{ Image Resize */
/**
 *
 * This function can resize a given image and save it to the given
 * location. 
 *
 * @todo Need to move this out to a library, e.g. image library
 * @param mixed $src_path 
 * @param mixed $desc_path 
 * @param mixed $width 
 * @param mixed $height 
 * @access public
 * @return void
 */
function shn_image_resize($src_path,$desc_path,$width,$height)
{
    $info = getimagesize($src_path);
    if(! $info)
        return false;

    $width_orig = $info[0];
    $height_orig = $info[1];

    if ($width && ($width_orig < $height_orig)) {
       $width = ($height / $height_orig) * $width_orig;
    } else {
       $height = ($width / $width_orig) * $height_orig;
    }
    
    $image_p = imagecreatetruecolor($width, $height);

    list($ignore,$mime) = split("\/",$info['mime']);
    $func = 'imagecreatefrom'.$mime;
    $image = $func($src_path);

    imagecopyresampled($image_p, $image, 0, 0, 0, 0, $width, $height, $width_orig, $height_orig);
    $func2 = 'image'.$mime;
    $func2($image_p,$desc_path,100);
}
/* }}} */

?>

