<?php
/**
 * SN main
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Harsha Halgaswatta(harsha.halgaswatta@gmail.com)
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage s
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
include_once $global['approot'] . '/inc/lib_menu.inc';
include_once $global['approot'] . '/inc/handler_form.inc';
include_once $global['approot'] . '/inc/lib_uuid.inc';
include_once $global['approot'] . '/inc/lib_image.inc';
include_once $global['approot'] . '/mod/sn/lib_sn.inc';

function shn_sn_mainmenu()
{
   global $global;
   $moldule = $global['module'];


   if(isset($_SESSION["user_id"]) && $_SESSION["user_id"] == 1){
       	shn_mod_menuopen(('Social Network'));

	    shn_mod_menuitem('ad_admin_home',('Home'));
	    shn_mod_menuitem('ad_view_mem',('View Members'));
	    //shn_mod_menuitem('me_reg',('Authenticate Members'));
	    //shn_mod_menuitem('sh_info', ('Make groups'));
       // shn_mod_menuitem('fr_fa', _t('Send alerts'));
   	    shn_mod_menuclose();
        //unset($_SESSION['admin']);
  }else{
     	shn_mod_menuopen(('Social Network'));
	    shn_mod_menuitem('sn_home',('Home'));
	    shn_mod_menuitem('my_prof',('My Profile'));

	    $usr= _shn_sn_chk_user_in_sn($_SESSION["user_id"]);
	    $fullname= _shn_sn_get_full_name($_SESSION["user_id"]);
	    $_SESSION["full_name"] =$fullname;

	    if($usr){
	        shn_mod_menuitem('sn_friend',('Friends'));
	        shn_mod_menuitem('sn_forums', ('Forums'));
            shn_mod_menuitem('sn_groups', ('Groups'));
	    }else{

	    }

      //shn_mod_menuitem('fr_fa', _t('Friends and Family'));
      //shn_mod_menuitem('share_info', _t('Discussion area'));
	    shn_mod_menuclose();

  }
	  //include the main menu so that the user can navigate outside the module
	include $global['approot'] . '/inc/handler_mainmenu.inc';

     //require $global['approot'] . '/mod/sn/logging.inc';
     //_shn_sn_get_data();


}

function shn_sn_sn_forums()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/sn_forums.inc';
}


function shn_sn_default()
{
	global $global;
	if(isset($_SESSION["user_id"]) && $_SESSION["user_id"] == 1){
	    include_once $global['approot'] . '/mod/sn/admin/admin_home.inc';
	}else{
		include_once $global['approot'] . '/mod/sn/home.inc';
	}

}
function shn_sn_sn_home()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/home.inc';
}

function shn_sn_add_mem()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/me_reg.inc';
}

function shn_sn_sn_friend()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/sn_friends.inc';
}

function shn_sn_mk_group()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/mk_group.inc';
}
function shn_sn_my_prof()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/my_prof.inc';
}

function shn_sn_me_reg()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/me_reg.inc';
}

function shn_sn_log_out()
{
  // unset($_SESSION['test']);
   global $global;
   include_once $global['approot'] . '/mod/sn/log_out.inc';

}

function shn_sn_log_page()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/home.inc';

}
function shn_sn_fog_pwd()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/fog_pwd.inc';

}
function shn_sn_sn_groups()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/sn_group.inc';

}

function shn_sn_cr_groups()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/cr_group.inc';

}

function shn_sn_share_info()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/share_info.inc';

}




function shn_sn_ad_admin_home()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/admin/admin_home.inc';

}

function shn_sn_ad_view_mem()
{
	global $global;
	include_once $global['approot'] . '/mod/sn/admin/view_mem.inc';

}

function shn_image_sn_group_img()
{
    global $global;


    $x_uuid = $_GET['x_uuid'];
    switch ($_GET['stream']) {
        case 'image' :
        {
        	if ($_GET['session']) {
                shn_show_image_stream($x_uuid, true, $_SESSION['sn']['group']['image'],true.'group_image');
            } else {
                if ($_GET['thumbnail']) {
                    shn_show_image_stream($x_uuid, true, null, false,'group_image');
               } else {
                    shn_show_image_stream($x_uuid, false, null, false, 'group_image');
               }
            }
        break;
        }
    }
}
function shn_image_sn_mem_img()
{
    global $global;


    $x_uuid = $_GET['x_uuid'];
    switch ($_GET['stream']) {
        case 'image' :
        {
        	if ($_GET['session']) {
                shn_show_image_stream($x_uuid, true, $_SESSION['sn']['group']['image'],true.'mem_image');
            } else {
                if ($_GET['thumbnail']) {
                    shn_show_image_stream($x_uuid, true, null, false,'mem_image');
               } else {
                    shn_show_image_stream($x_uuid, false, null, false, 'mem_image');
               }
            }
        break;
        }
    }
}


