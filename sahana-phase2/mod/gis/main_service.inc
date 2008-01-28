
<?php
/**
 * PHP version 4 and 5
 *
 * @author      thinesh Thusinthaka
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage service
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
 
  
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_uuid.inc";
//include_once $global['approot'].'/mod/ims/lib_ims.inc';

  

function shn_service_mainmenu() 
{      
    global $global;
    $module = $global['module'];

    // The  module menu
	shn_mod_menuopen(_("GIS"));
	shn_mod_menuitem("viewedit",_("View & Edit"));	
	shn_mod_menuitem("addmain",_("Feed Add"));	
	shn_mod_menuitem("Home",_("Home"));
	//shn_mod_menuitem("Feed_Acess",_("feedacess"));
	shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 



function shn_service_addmain_form_submit()
{       
	echo "<h1>Add Main Catalogue Result</h1>";
	require_once('add.inc');
	
	if(_shn_service_validate_addmainform())
	{
	display_errors();
	shn_service_addmain_form();
	}
	else
	{
	_shn_service_addmain_form_result();
	}
}



//this function for adding new item Feed in system.
function shn_service_addmain()
{      
	echo "<h1>Add Feeds to Catalogue</h1>";
	?>	
	<p><?= _('Here you are able to add new Feed data items'); ?></p>
	<?php
	require_once('add.inc');
	shn_service_addmain_form();	
}
//have to connect add.inc file inside here to function handling


	



function shn_service_default()
{include_once ('home.inc');
}
function shn_service_viewedit()
{  include_once ('view.inc');
	shn_service_edit_form();
   	
}

function shn_service_edit_form_submit()
{
	echo "<h1>View And Edit</h1>";
	require_once('view.inc');

	$selected = trim($_POST['edit_type']);

	if($selected=='none')
		{
		shn_service_edit_form();
		}
		
	else if($selected=='Item')
		{
		shn_service_edit_form();
		show_item_cat_table();
		}
		
	else if($selected=='Unit')
		{
		shn_service_edit_form();
		show_unit_table();
		}
		
	else if($selected=='Unit_types')
		{
		shn_service_edit_form();
		show_unit_type_table();
		}
}


function shn_service_edit_cat_select_submit()
{
	echo"<h1>Edit Catalogue / Item</h1>";
	require_once('view.inc');
	_shn_service_show_cat();	
}

function shn_service_edit_cat_form_submit()
{
	echo"<h1>Edit Catalogue / Item</h1>";
	require_once('view.inc');
	_shn_cs_edit_cat_select_submit_result();	
}


?>
		
	
										




																																																																																																																																																																																																							