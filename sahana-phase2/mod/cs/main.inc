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

function shn_cs_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // The  module menu
	shn_mod_menuopen(_("Catalogue System"));
	shn_mod_menuitem("default",_("Home"));
	shn_mod_menuitem("search",_("Search"));
	shn_mod_menuitem("addmain",_("Add Main Catalogue"));
	shn_mod_menuitem("addunit",_("Add Measurement Unit"));
	shn_mod_menuitem("addsub",_("Add Sub Catalogue"));
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
	require_once('search.inc');
	shn_cs_search_cat();
}

function shn_cs_search_submit()
{
	echo "<h1>Search Result</h1>";
	require_once('search.inc');
	_shn_cs_search_submit_result();
}


function shn_cs_addmain()
{
	echo "<h1>Add Main Catalogue</h1>";
	?>
	<p><?= _(' This feature allows to add root catalogues. After adding the root catalogues, sub-categories can be added under them.'); ?></p>
	<?php

	require_once('add.inc');
	shn_cs_addmain_form();

}

function shn_cs_addsub()
{
	echo "<h1>Add Sub Category</h1>";
	?>
	<p><?= _('This feature allows to add sub category under any category'); ?></p>
	<?php

	require_once('add.inc');
	shn_cs_addsub_form1();
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
	_shn_cs_addsub_form1_result();
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

function shn_cs_addunit_form_submit()
{
	echo "<h1>Add Measurement Unit</h1>";
	require_once('add.inc');
	
	if(_shn_cs_validate_unitform())
	{
	display_errors();
	shn_cs_addunit_form();
	}
	else
	{
	_shn_cs_addunit_form_result();
	}

}


function shn_cs_viewedit()
{
	echo "<h1>View And Edit</h1>";
	require_once('edit.inc');
	shn_cs_edit_form();
}

function shn_cs_edit_submit()
{
	echo "<h1>Edit Result</h1>";
	require_once('edit.inc');
	_shn_cs_edit_form_result();
}

function shn_cs_form1_submit()
{
	echo"<h1>Edit Result</h1>";
	require_once('edit.inc');
	shn_cs_edit_form1_result();
	
}

function shn_cs_form2_submit()
{
	echo"<h1>Edit Result</h1>";
	include_once('edit.inc');
	shn_cs_edit_form1_submit_result();
	
}




?>

