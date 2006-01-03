<?php
/* $Id: main.inc,v 1.15 2006-01-03 05:06:29 janakawicks Exp $ */

/**Main home page of the Missing Person Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author	  Chamindra de Silva <chamindra@opensource.lk>
* @author	  Janaka Wickramasinghe <janaka@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";

/* {{{ Main Menu */
/**
 * shn_mpr_mainmenu 
 * 
 * @access public
 * @return void
 */
function shn_mpr_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen("Missing Person Registry");

    shn_mod_menuitem("default","Home");
    shn_mod_menuitem("search&type=all","Search for a Person");
    shn_mod_menuitem("addmp&type=missing","Report a Missing Person");
    shn_mod_menuitem("search&type=missing","Edit a Missing Person");
    shn_mod_menuitem("addmp&type=found","Report a Found Person");
#    shn_mod_menuitem("test","Test");
#    shn_mod_menuitem("stats","Statistics");

    shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
/* }}} */	

/* {{{ Action: Test */
/**
 * shn_mpr_test 
 * 
 * @access public
 * @return void
 */
function shn_mpr_test()
{
    global $global;
    require($global['approot'].'mod/mpr/test.inc');
}
/* }}} */

/* {{{ Action: Default (Home Page) */
/**
 * shn_mpr_default 
 * 
 * @access public
 * @return void
 */
function shn_mpr_default()
{
    global $global;
    require($global['approot'].'mod/mpr/home.inc');
}
/* }}} */

/* {{{ Action: Find */
/**
 * shn_mpr_fndmp 
 * 
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
 * shn_mpr_editmp 
 * 
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
            echo '<h1 align="center">Edit Missing Person Entry</h1>';
	        if(shn_mpr_editmp_validate()){
                shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
	        }else
	            shn_mpr_editmp_entry(true);
	    break;
	    
        case 'trackers' :
            echo '<h1 align="center">Edit Missing Person Entry</h1>';
            shn_mpr_editmp_upload();
        break;
	    case 'upload_pic' :
            echo '<h1 align="center">Edit Missing Person Entry</h1>';
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
        	echo '<h1 align="center">Edit Missing Person Entry</h1>';
	        $_POST = null;
	        $_SESSION['mpr_add']['add_tracker'] = null;
	        echo '<h1 align="center">Add a tracker to '.
	            $_SESSION['mpr_edit']['entry']['full_name'].' </h1>';
            $_SESSION['mpr_add']['add_tracker']['p_uuid'] = $_SESSION['mpr_edit']['entry']['p_uuid'];
	        // TODO: check the p_uuid exists or not *** VERY URGENT
	        shn_mpr_addmp_reporter();
	    break;

        case 'report_person' :
            echo '<h1 align="center">Edit Missing Person Entry</h1>';
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
                echo '<h1 align="center">Add a tracker to
'.$_SESSION['mpr_add']['add_tracker']['name'].' </h1>';
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
            echo '<h1 align="center">Edit Missing Person Entry</h1>';
            //TODO : Clean the input
            $tracker_uuid = $_GET['tracker_id'];
            shn_edit_del_tracker ($_SESSION['mpr_edit']['entry']['p_uuid'],
                $tracker_uuid);
            shn_edit_show_trackers($_SESSION['mpr_edit']['entry']['p_uuid']);
            
        break;
	    default:
            echo '<h1 align="center">Edit Missing Person Entry</h1>';
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
 * shn_mpr_viewmp 
 * 
 * @access public
 * @return void
 */
function shn_mpr_viewmp()
{
    global $global;
    require($global['approot'].'mod/mpr/view.inc');
    echo '<h1 align="center">View Person</h1>';
    shn_mpr_view($_GET['id']);
}
/* }}} */

/* {{{ Action: Add Tracker */
/**
 * shn_mpr_add_tracker 
 * 
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
                    // TODO: redirect back to search results (that'll be great)
                    shn_mpr_default();                
                    $_SESSION['mpr_add']['add_tracker']=null;
                }
            }else{
                echo '<h1 align="center">Add a tracker to
'.$_SESSION['mpr_add']['add_tracker']['name'].' </h1>';
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
                echo '<h1 align="center">Add a tracker to '.$_GET['name'].' </h1>';
                $_SESSION['mpr_add']['add_tracker']['p_uuid'] =
$_GET['id'];
                $_SESSION['mpr_add']['add_tracker']['name'] =
$_GET['name'];
                // TODO: check the p_uuid exists or not *** VERY URGENT
                shn_mpr_addmp_reporter();
        break;
    }
}
/* }}} */

/* {{{ Action: Delete Tracker */
function shn_mpr_del_tracker()
{
    global $global;
    
            if(shn_mpr_addmp_reporter_validate()){
                shn_mpr_addmp_insert_reporter($_SESSION['mpr_add']['add_tracker']['p_uuid']);
                // TODO: rediddrect back to search results (that'll be great)
                #shn_mpr_default();                
                $_SESSION['mpr_add']['add_tracker']=null;
            }else{
                echo '<h1 align="center">Add a tracker to
'.$_SESSION['mpr_add']['add_tracker']['name'].' </h1>';
                shn_mpr_addmp_reporter(true);
            }
}
/* }}} */

/* {{{ Action: Add */
/**
 * shn_mpr_addmp 
 * 
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
        $heading = '<h1 align="center">Found Person Entry</h1>';
    elseif($_SESSION['mpr_add']['entry_type'] == 'missing')
        $heading = '<h1 align="center">Missing Person Entry</h1>';

    //Controller
	switch ($_REQUEST['seq']) {
	    case 'entry':
	        if(shn_mpr_addmp_validate()){
	            //clean the $_POST to remove the conflicts
	            $_POST = null;
                echo $heading;
                echo '<h2 align="center">(Upload Person\'s Picture)</h2>';
	            shn_mpr_addmp_upload();
	        }else{
                echo $heading;
                echo '<h2 align="center">(Person Details)</h2>';
	            shn_mpr_addmp_entry(true);
            }
	    break;

        case 'tracker_back' :
            echo $heading;
            echo '<h2 align="center">(Reporting Person)</h2>';
            shn_mpr_addmp_reporter();
        break;
	
        case 'tracker_select' :
            $_SESSION['mpr_add']['entry']['tracker_id'] = $_GET['tracker_id'];
            echo $heading;
            echo '<h2 align="center">(Final Confirmation)</h2>';
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
                    echo '<h2 align="center">(Final Confirmation)</h2>';
	                shn_mpr_addmp_confirm();
                }
	        }else{
                echo $heading;
                echo '<h2 align="center">(Reporting Person)</h2>';
                shn_mpr_addmp_reporter(true);
            }
	    break;
	
	    case 'upload_pic' :
	        if(shn_mpr_addmp_upload_pic()){
                echo $heading;
                echo '<h2 align="center">(Reporting Person)</h2>';
                shn_mpr_addmp_reporter();
	        }else{
                echo $heading;
                echo '<h2 align="center">(Upload Person\'s Picture)</h2>';
                shn_mpr_addmp_upload(true);
            }
	    break;
	
	    case 'commit' :
	        shn_mpr_addmp_commit();
	    break;
	
	    default:
            echo $heading;
            echo '<h2 align="center">(Person Details)</h2>';
	        shn_mpr_addmp_entry();
        break;
	}
}
/* }}} */

/* {{{ Action: Search */
/**
 * shn_mpr_search 
 * 
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
 * shn_mpr_search_adv 
 * 
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
 * shn_mpr_addmp 
 * 
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
 * shn_mpr_status 
 * 
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
//Put some where else
/**
 * shn_show_thumb 
 * 
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
        echo "Image Not Available";
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
    <a title="Click to see the original size" href="#" onclick="window.open('<?=$url?>','hello','width=<?=$width?>,height=<?=$height?>,scrollbars=no,status=no');return false;" >
    <img border="0" src="tmp/<?='thumb_'.$p_uuid.'.'.$ext?>" />
    </a>
<?php
    return true;
}
/* }}} */

/* {{{ get field option description */
/**
 * shn_get_field_opt 
 * 
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
 * shn_image_resize 
 * 
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

