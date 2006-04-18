<?php 
/**
 * Add Category  
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
 */




/**
 * This function shows a form to add main category and submit values to a function in the main.inc
 * @access public
 * @return void
 */


function shn_cs_addmain_form()
{
	$extra_opts['req']=true;
	shn_form_fopen('addmain_form_submit');
	shn_form_fsopen(_('Details Of the catalogue'));
	shn_form_text(_("Name   : "),'main_cat_name','size="50"',$extra_opts);
	shn_form_text(_("Description   : "),'description','size="50"');
	shn_form_fsclose();
	shn_form_submit(_("Add"));
	shn_form_fclose();

}

/**
 * This function shows the result after processing the POST values from shn_cs_addmain_form().
 *This function is called by shn_cs_addmain_form_submit() in main.inc
 * @access private
 * @return void
 */
function _shn_cs_addmain_form_result()
{
	global $global;
	$db=$global["db"];
	$parentid='0';
	$name = trim($_POST['main_cat_name']);
    	$description = trim($_POST['description']);
	
	$id = shn_create_uuid("catalogue");

	$q="insert into ct_catalogue (parentid,ct_uuid,name,description) values($parentid,'$id','$name','$description')";
	$res=$db->Execute($q);
?>

	<div id="result_msg">
	<?php echo $name." was succesfully saved.";?>

	</div>

<?php

}


/**
 * This function shows a form to add a sub category. It calls to a function in lib_cs.inc and submit the result to addsub_form1_submit.
 * @access public
 * @return void
 */

function shn_cs_addsub_form1()
{
	require_once("lib_cs.inc");
	
	shn_form_fopen("addsub_form1_submit");
	shn_sub_cat(6);
	shn_form_fclose();
}


/**
 * This function shows a form to add a sub category.Submit the result to addsub_form2_submit() in main.inc.
 * @access private
 * @return void
 */
function _shn_cs_addsub_form1_result()
{
	global $global;
	$db=$global["db"];

	$parent_id = trim($_POST['0']);
	// this 5 should be replaced by the $max that is retrieved from the DB
	for($i=1;$i<5;$i++)
	{
	$parent_id = trim($_POST[$i]);
	
		if($parent_id==null)
		{
		$parent_id = $_POST[$i-1];
		break;
		}
	}
	$extra_opts['req']=true;
	shn_form_fopen("addsub_form2_submit");
	shn_form_fsopen(_('Sub Category Details'));
	shn_form_text(_("Name   : "),'sub_cat_name','size="50"',$extra_opts);
	shn_form_text(_("Description   : "),'sub_description','size="50"',null);
	shn_form_fsclose();
	shn_form_fsopen(_('Mesurement Units'));	
	
	$myoptions=array();
	$query="select * from ct_unit ";
	$res=$db->Execute($query);

	while(!$res==NULL && !$res->EOF)
	{
	$myoptions[$res->fields['unit_uuid']]=$res->fields['name'];
	$res->MoveNext();
	}

	
	shn_form_multi_select('unit_select',$myoptions, _("Unit"),'size=5 multiple="multiple"' );
	shn_form_fsclose();
	
	//the parent ID is submitted as a hidden variable
	$parent_id_array=array($i => $parent_id);
	shn_form_hidden($parent_id_array);

	shn_form_submit(_("Add"));
	shn_form_fclose();
}

/**
 * This function shows the result after processing the POST values from _shn_cs_addsub_form1_result().
 *This function is called by shn_cs_addsub_form2_submit() in main.inc
 * @access private
 * @return void
 */

function _shn_cs_addsub_form2_result()
{
	global $global;
	$db=$global["db"];

	for($i=1;$i<5;$i++)
	{
	$parent_id = trim($_POST[$i]);
	
		if($parent_id!=null)
		{
		$parent_id = trim($_POST[$i]);
		break;
		}
	}

	$sub_cat_name=trim($_POST['sub_cat_name']);
	$sub_description=trim($_POST['sub_description']);
	$id = shn_create_uuid("catalogue");
	$q="insert into ct_catalogue (parentid,ct_uuid,name,description) values('$parent_id','$id','$sub_cat_name','$sub_description')";
	$res=$db->Execute($q);


	$unit_selected= $_POST["unit_select"];
	$num = sizeof($unit_selected);

	for($i=0;$i<$num;$i++)
	{
	$temp = $unit_selected[$i];
	$q="insert into ct_cat_unit (ct_uuid,unit_uuid) values('$id','$temp')";
	$res=$db->Execute($q);
	
	}

?>

	<div id="result_msg">
	<?php echo $sub_cat_name." was succesfully saved.";?>

	</div>

<?php

}


/**
 * This function shows a form to add Measurement Unit
 * @access public
 * @return void
 */
function shn_cs_addunit_form()
{
	$extra_opts['req']=true;
	shn_form_fopen("addunit_form_submit");
	shn_form_fsopen(_('Measurement Unit'));
	shn_form_text(_("Unit : "),'unit_name','size="50"',$extra_opts);
	shn_form_fsclose();
	shn_form_submit(_("Add"));
	shn_form_fclose();

}

/**
 * This function shows the result after processing the POST values from shn_cs_addunit_form().
 *This function is called by shn_cs_addunit_form_submit() in main.inc
 * @access private
 * @return void
 */

function _shn_cs_addunit_form_result()
{
	global $global;
	$db=$global["db"];
	
	$unit_name=trim($_POST['unit_name']);

	$unit_id=shn_create_uuid("unit");
	$query="insert into ct_unit(unit_uuid,name) values('$unit_id','$unit_name')";
	$res=$db->Execute($query);
	?>

	<div id="result_msg">
	<?php echo $unit_name." was succesfully saved."; ?>

	</div>

	<?php

}



/**
 * This function validates the values entered in add main form.
 *This function is called by shn_cs_addmain_form_submit() in main.inc
 * @access private
 * @return void
 */

function _shn_cs_validate_addmainform()
{
$error_flag=false;
clean_errors();
	
	//this checks whether name entered in the add main form
	if(trim($_POST['main_cat_name'])==null)
	{
	add_error(_("Please Enter the Catalogue Name"));
	$error_flag=true;
	}

return $error_flag;
}

/**
 * This function validates the values entered in add unit form.
 *This function is called by shn_cs_addunit_form_submit() in main.inc
 * @access private
 * @return void
 */

function _shn_cs_validate_unitform()
{
$error_flag=false;
clean_errors();
	
	//this checks whether name entered in the add unit form
	if(trim($_POST['unit_name'])==null)
	{
	add_error(_("Please Enter the Unit Name"));
	$error_flag=true;
	}	

return $error_flag;
}


function _shn_cs_validate_subcatform()
{
$error_flag=false;
clean_errors();
	
	//this checks whether name entered in the add sub category form
	if(trim($_POST['sub_cat_name'])==null)
	{
	add_error(_("Please Enter the Sub Category Name"));
	$error_flag=true;
	}	

return $error_flag;
}

?>