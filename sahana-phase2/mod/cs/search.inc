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


function shn_cs_search_cat()
{
	$parent_array=array();
	
	global $global;
	$db=$global["db"];
	$query="select name from ct_catalogue where parentid='0' ";
	$res=$db->Execute($query);
	
	while(!$res==NULL && !$res->EOF)
	{
	$temp=$res->fields["name"];
	$parent_array[$temp]=_($temp);
	$res->MoveNext();
	
	}
	shn_form_fopen("search_view");

	if($parent_array==null){
	$parent_array["1"]=_("None");
	shn_form_fsopen(_('Information'));
	?>
	<p><?= _('There is no any root category found. Please add parent category first and Search. '); ?><a href="index.php?mod=cs&act=additems">Add root category</a></p>
	
	<?php
	shn_form_fsclose();
	}
	else{
	shn_form_fsopen(_('Select Search'));	
	shn_form_select($parent_array,_("Select the root Category :"),'itemcat','size="1"',null);
	shn_form_fsclose();
	shn_form_submit(_("Search"));
	
	}
	shn_form_fclose();
}




function _shn_cs_search_view_result()
{
?>
<table>
	<thead>
		<td><strong><?=_("Parent ID")?></strong></td>
		<td><strong><?=_("Category ID")?></strong></td>
		<td><strong><?=_("Category Name")?></strong></td>
		<td><strong><?=_("Description")?></strong></td>
	</thead>
	<TBODY>
	<?php

	global $global;
	$db=$global["db"];

	$itemcat = trim($_POST['itemcat']);
	$query="select name,parentid,ct_uuid,description from ct_catalogue where name='$itemcat' ";
	$res=$db->Execute($query);

	$parentid=$res->fields["parentid"];
	$name=$res->fields["name"];
	$id=$res->fields["ct_uuid"];
	$description=$res->fields["description"];

	if($parentid=='0'){
	?>
	<tr>
		<td><?php print $parentid ;?></td>
		<td><?php print $id ;?></td>
		<td><a href="index.php?mod=cs&act=edit_cat&id=<?php echo $id ?>"><?php print $name ;?></a></td>
		<td><?php print $description ;?></td>
	</tr>
	<?php
	}

	$rootid = $id;

	$query="select name,parentid,ct_uuid,description from ct_catalogue where parentid ='$rootid' ";
	$res=$db->Execute($query);

	
	while(!$res==NULL && !$res->EOF)
	{
	$parentid=$res->fields["parentid"];
	$name=$res->fields["name"];
	$id=$res->fields["ct_uuid"];
	$description=$res->fields["description"];

	?>
		<tr>
		<td><?php print $parentid ;?></td>
		<td><?php print $id ;?></td>
		<td><?php print "----".$name ;?></td>
		<td><?php print $description ;?></td>
	</tr>

	<?php
	$res->MoveNext();
	}//end of while loop
	?>
	</TBODY>
	
</table>


<?php
}

?>