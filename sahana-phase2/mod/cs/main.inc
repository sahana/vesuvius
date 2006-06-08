<?php


/**
 * Main Controller of the Catalogue System. 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_uuid.inc";
include_once $global['approot'].'/mod/ims/lib_ims.inc';


function shn_cs_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // The  module menu
	shn_mod_menuopen(_("Catalogue System"));
	shn_mod_menuitem("default",_("Home"));
	shn_mod_menuitem("search",_("Search"));
	shn_sub_mod_menuopen(_("Add Catalogue/Item"));
	shn_mod_menuitem("addmain",_("Add Main Catalogue"));
	shn_mod_menuitem("addsub",_("Add Sub Catalogue"));
	shn_mod_menuitem("additem",_("Add Item"));
	shn_sub_mod_menuclose();
	shn_sub_mod_menuopen(_("Add Unit Category/ Unit"));
	shn_mod_menuitem("addunittype",_("Add Measurement Unit Type"));
	shn_mod_menuitem("addunit",_("Add Measurement Unit"));
	shn_sub_mod_menuclose();
	shn_mod_menuitem("viewedit",_("View & Edit"));
	shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 


function shn_cs_default()
{
	include_once ('home.inc');

}

function shn_cs_search()
{
	echo "<h1>Search</h1>";
	?>
	<p><?= _('Select the Search Type in the select box that you need to search. By selecting Catalogue/Item, you are able to Search for a Item or a Catalogue and by selecting Unit, you are able to search for Units.'); ?></p> 
	<?php
	require_once('search.inc');
	shn_cs_search_cat();
}


/**
 * This function recieves submited result from the shn_cs_search_cat() in search.inc.
 * @access private
 * @return void
 */
function shn_cs_select_type_submit()
{
	echo "<h1>Search</h1>";
	require_once('search.inc');
	$selected = trim($_POST['search_type']);

	if($selected=='none')
		{
		shn_cs_search_cat();
		}
	else if($selected=='Item')
		{
		shn_cs_search_cat();
		_shn_cs_cat_form();
		}
	else if($selected=='Unit')
		{
		shn_cs_search_cat();
		_shn_cs_unit_form();
		}	

}


function shn_cs_search_item_submit()
{
	echo "<h1>Search Result</h1>";
	require_once('search.inc');
	

	if(_shn_cs_validate_cat_form())
	{
	display_errors();
	shn_cs_search_cat();
	_shn_cs_cat_form();
	}
	else
	{
	_shn_cs_search_item_cat_submit_result();
	}
	
}

function shn_cs_search_unit_submit()
{
	echo "<h1>Search Result</h1>";
	require_once('search.inc');
	if(_shn_cs_validate_unit_form())
	{
	display_errors();
	shn_cs_search_cat();
	_shn_cs_unit_form();
	}
	else
	{
	_shn_cs_search_unit_submit_result();
	}
}


function shn_cs_addmain()
{
	echo "<h1>Add Main Catalogue</h1>";
	?>
	<p><?= _('Here you are able to add Main catalogue types which are the root Items of the Item tree. Eg. Food, Medicine, clothing, etc.'); ?></p>
	<?php

	require_once('add.inc');
	shn_cs_addmain_form();

}

function shn_cs_addsub()
{
	echo "<h1>Add Sub Category</h1>";
	?>
	<p><?= _('Here you are able to add Sub catalogue types which are under Main catalogues. Eg. Food --> Fruits, Dry food, etc. Fruits, Dry food are sub catalogues. The system administrator should have to specify the Maximum Depth of the Catalogue / Item Tree. Eg: Maximum Depth = 5 will allow you to add catalogues /Items upto 5 levels.'); ?></p>
	<?php

	require_once('add.inc');
	shn_cs_addsub_form1();
}


function shn_cs_addmain_form_submit()
{
	echo "<h1>Add Main Catalogue Result</h1>";
	require_once('add.inc');
	
	if(_shn_cs_validate_addmainform())
	{
	display_errors();
	shn_cs_addmain_form();
	}
	else
	{
	_shn_cs_addmain_form_result();
	}

}

function shn_cs_addsub_form1_submit()
{
	echo "<h1>Add Sub Catalogue Result</h1>";
	require_once('add.inc');
	require_once('lib_cs.inc');
	
	if(_shn_cs_validate_sub_cat_form())
		{
		display_errors();
		shn_cs_addsub_form1();
		}
	else
		{
		_shn_cs_addsub_form1_result();
		}
	
}

function shn_cs_addsub_form2_submit()
{
	echo "<h1>Add Sub Catalogue Result</h1>";
	require_once('add.inc');
	
	if(_shn_cs_validate_subcatform())
	{
	display_errors();
	_shn_cs_addsub_form1_result();
	}
	else
	{
	_shn_cs_addsub_form2_result();
	}

}


function shn_cs_addunit()
{
	echo "<h1>Add Measurement Unit</h1>";
	?>
	<p><?= _(' This feature allows to add measurement unit/units. Before adding a sub category you have to add the measurement unit/units that is  used by the purticular category.'); ?></p>
	<?php
	require_once('add.inc');
	shn_cs_addunit_form();
}

function shn_cs_addunit_select_utype_submit()
{
	echo "<h1>Add Measurement Unit</h1>";
	require_once('add.inc');
	shn_cs_addunit_form();
	_shn_cs_utype_select_submit_result();
}


function shn_cs_addunit_form_submit()
{
	echo "<h1>Add Measurement Unit</h1>";
	require_once('add.inc');
	

	if(_shn_cs_validate_unitform())
	{
	display_errors();
	shn_cs_addunit_form();
	_shn_cs_utype_select_submit_result();
	}
	else
	{
	_shn_cs_addunit_form_result();
	}

}


function shn_cs_additem()
{
	echo "<h1>Add Item</h1>";

	?>
	<p><?= _('Here you are able to add Items which are under catalogues. Eg. Fruits --> Apple,Mango etc. Apple,Mango are Items. The system administrator should have to specify the Maximum Depth of the Catalogue / Item Tree. Eg: Maximum Depth = 5 will allow you to add catalogues /Items upto 5 levels.'); ?></p>
	<?php

	require_once('add.inc');
	shn_cs_additem_form1();
}


function shn_cs_additem_form1_submit()
{
	echo "<h1>Add Item Result</h1>";
	require_once('add.inc');
	require_once('lib_cs.inc');

	if(_shn_cs_validate_sub_cat_form())
		{
		display_errors();
		shn_cs_additem_form1();
		}
	else
		{
		shn_cs_additem_form1_result();
		}
	
}

function shn_cs_additem_form2_submit()
{
	echo "<h1>Add Item Result</h1>";
	
	require_once('add.inc');
	//shn_cs_additem_form2_result();
		if(_shn_cs_validate_additem_form())
		{
		display_errors();
		shn_cs_additem_form1_result();
		}
		else
		{
		shn_cs_additem_form2_result();

		}
}


function shn_cs_viewedit()
{
	echo "<h1>View And Edit</h1>";
	?>
	<p><?= _('Here you are able to view, edit and Delete all the catalogues, Items, Units and Unit Types which are handled by the catalogue system. <b>Using Delete, you will lose all the records of the particular catalogues, Items, Unit or Unit Types.</b>'); ?></p>
	<?php
	require_once('edit.inc');
	shn_cs_edit_form();
}

function shn_cs_edit_form_submit()
{
	echo "<h1>View And Edit</h1>";
	require_once('edit.inc');

	$selected = trim($_POST['edit_type']);

	if($selected=='none')
		{
		shn_cs_edit_form();
		}
	else if($selected=='Item')
		{
		shn_cs_edit_form();
		show_item_cat_table();
		}
	else if($selected=='Unit')
		{
		shn_cs_edit_form();
		show_unit_table();
		
		}
	else if($selected=='Unit_types')
		{
		shn_cs_edit_form();
		show_unit_type_table();
		}
}

function shn_cs_edit_cat_select_submit()
{
	echo"<h1>Edit Catalogue / Item</h1>";
	require_once('edit.inc');
	_shn_cs_edit_cat_select_submit_result();
}

function shn_cs_edit_cat_form_submit()
{
	echo"<h1>Edit Catalogue / Item Result</h1>";
	require_once('edit.inc');
	_shn_cs_edit_cat_form_submit_result();
}

function shn_cs_edit_unit_select_submit()
{
	echo"<h1>Edit Unit</h1>";
	require_once('edit.inc');
	_shn_cs_edit_unit_select_submit_result();
}

function shn_cs_edit_unit_form_submit()
{
	echo"<h1>Edit Unit Result</h1>";
	require_once('edit.inc');
	_shn_cs_edit_unit_form_submit_result();
}

function shn_cs_edit_unittype_select_submit()
{
	echo"<h1>Edit Unit Type</h1>";
	require_once('edit.inc');
	_shn_cs_edit_unittype_select_submit_result();
}

function shn_cs_edit_unit_type_form_submit()
{
	echo"<h1>Edit Unit Type Result</h1>";
	require_once('edit.inc');
	_shn_cs_edit_unit_type_form_submit_result();
}

function shn_cs_addunittype()
{
	echo "<h1>Add Unit Type</h1>";
	require_once('add.inc');
	
	?>
	<p><?= _('Here you are able to add Unit type. For every Unit type you have to add a base unit. Eg. If you add volume as the unit type, Letre can be specified as the base unit.'); ?></p>
	<?php
	
	shn_cs_add_unit_type_form();
}

function shn_cs_addunitform_submit()
{
	echo "<h1>Add Unit Type</h1>";
	require_once('add.inc');


	if(_shn_cs_validate_unit_type_form())
	{
	display_errors();
	shn_cs_add_unit_type_form();
	}
	else
	{
	_shn_cs_add_unit_type_form_result();
	}


	
}

?>

