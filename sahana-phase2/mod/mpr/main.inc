<?php
/* $Id: main.inc,v 1.9 2005-11-07 04:14:00 janakawicks Exp $ */

/**Main home page of the Missing Person Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author	  Chamindra de Silva <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";

function shn_mpr_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen("Missing Person Registry");

    shn_mod_menuitem("default","Home");
    shn_mod_menuitem("search&type=all","Search for a Person");
    shn_mod_menuitem("search&type=found","Search for a Found Person");
    shn_mod_menuitem("addmp","Report a Missing Person");
    shn_mod_menuitem("search&type=missing","Edit a Missing Person");
    shn_mod_menuitem("search&type=missing","Report a Found Person");
#    shn_mod_menuitem("test","Test");
#    shn_mod_menuitem("stats","Statistics");

    shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 
	


function shn_mpr_default()
{
    global $global;
    require($global['approot'].'mod/mpr/home.inc');
}

function shn_mpr_fndmp()
{
    global $global;

    $header=array('method'=>'POST','action'=>'index.php?mod=mpr&act=addmp','id'=>'formset');
    shn_form_open($header,false);

?>  <input type="text" value="hello"/>          <?php

    shn_form_close();
}

function shn_mpr_editmp()
{
    global $global;
    require($global['approot'].'mod/mpr/edit.inc');
}

function shn_mpr_addmp()
{
    global $global;
    require($global['approot'].'mod/mpr/add.inc');
}

function shn_mpr_search()
{
    global $global;
    echo "<h2>Search</h2>";
    require($global['approot'].'mod/mpr/search.inc');
}

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

//Put some where else
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

function shn_get_field_opt($value,$field_name)
{

    global $global;
    return $global['db']->GetOne("SELECT option_description FROM field_options WHERE option_code = '$value' AND field_name='$field_name'");
}

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

?>

