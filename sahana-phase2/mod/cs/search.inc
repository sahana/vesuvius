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
function shn_cs_search_cat()
{

	require_once("lib_cs.inc");
	$form_opts['name']='subcat';

	shn_form_fopen("search_submit",null,$form_opts);
	shn_sub_cat(6,'subcat');
	shn_form_fclose();

}

/**
 * This function shows the result after processing the POST values from shn_cs_search_cat().
 *This function is called by shn_cs_search_submit() in main.inc
 * @access private
 * @return void
 */
function _shn_cs_search_submit_result()
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
	<THEAD>
		<TD><strong><?=_("Category Name")?></strong></TD>
		<TD><strong><?=_("Description")?></strong></TD>
	</THEAD>
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
		<td><?php print $name ;?></a></td>
		<td><?php print $description ;?></td>
	</tr>


	</TBODY>
	
</table>

<?php
}

?>