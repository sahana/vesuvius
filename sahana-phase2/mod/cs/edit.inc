<?php
/**
 * Search Category  
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
 * This function shows a form to select the category.Submit the result to shn_cs_search_submit() in main.inc.
 * @access private
 * @return void
 */
function shn_cs_edit_form()
{
	/*require_once("lib_cs.inc");
	
	shn_form_fopen("edit_submit");
	shn_sub_cat(6);
	shn_form_fclose();*/

	require_once("lib_cs.inc");
	$form_opts['name']='subcat';
    //$form_opts['req_message']=false;
   // shn_form_fopen("view_org_submit",null,$form_opts);
	shn_form_fopen("edit_submit",null,$form_opts);
	shn_sub_cat(6,'subcat');
	shn_form_fclose();



}


/**
 * This function shows the result after processing the POST values from shn_cs_edit_form().
 *This function is called by shn_cs_edit_submit() in main.inc
 * @access private
 * @return void
 */
function _shn_cs_edit_form_result()
{

	global $global;
	$db=$global["db"];

	$cat_id = trim($_POST['0']);
	// this 5 should be replaced by the $max that is retrieved from the DB
	for($i=1;$i<5;$i++)
	{
	$cat_id = trim($_POST[$i]);
	
		if($cat_id==null)
		{
		$cat_id = $_POST[$i-1];
		break;
		}
	}

?>
<table>
	<thead>
		<td><strong><?=_("Category Name")?></strong></td>
		<td><strong><?=_("Description")?></strong></td>
	</thead>
	<TBODY>
	<?php

	global $global;
	$db=$global["db"];

	$query="select name,description from ct_catalogue where ct_uuid='$cat_id' ";
	$res=$db->Execute($query);

	$name=$res->fields["name"];
	$description=$res->fields["description"];

	?>
	<tr>
		<td><a href="index.php?mod=cs&act=form1_submit&id=<?php echo $cat_id ?>"><?php print $name ;?></a></td>
		<td><?php print $description ;?></td>
	</tr>


	</TBODY>
	
</table>

<?php
}


function shn_cs_edit_form1_result()
{

$id = trim($_REQUEST['id']);

global $global;
$db=$global["db"];

$query="select name,description from ct_catalogue where ct_uuid='$id' ";
$res=$db->Execute($query);

//$parentid=$res->fields["parentid"];
$name=$res->fields["name"];
$description=$res->fields["description"];

	$extra_opts['req']=true;
	shn_form_fopen('form2_submit');
	shn_form_fsopen(_('Details Of the catalogue'));
	$extra_opts['value']=$name;
	shn_form_text(_("Category Name   : "),'main_cat_name','size="50"',$extra_opts);
	$extra_opts['req']=false;
	$extra_opts['value']=$description;
	shn_form_text(_("Description   : "),'description','size="50"',$extra_opts);
	shn_form_fsclose();
	
	$parent_id_array=array('0' => $id);
	shn_form_hidden($parent_id_array);

	shn_form_submit(_("Edit"));
	shn_form_fclose();

}

function shn_cs_edit_form1_submit_result()
{
	global $global;
	$db=$global["db"];

	$name = trim($_POST['main_cat_name']);
    	$description = trim($_POST['description']);
	$id = trim($_POST['0']);

	$query="update ct_catalogue set name='$name' , description='$description' where ct_uuid='$id' ";
	$res=$db->Execute($query);	

	?>

	<div id="result_msg">
	<?php echo $name." was succesfully Updated.";?>
	</div>

	<?php

}

?>