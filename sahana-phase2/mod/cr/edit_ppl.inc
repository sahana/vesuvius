<?php

/* $Id: edit_ppl.inc,v 1.7 2008-01-30 04:35:18 prabath321 Exp $ */
/* $Id: edit_ppl.inc,v 1.7 2008-01-30 04:35:18 prabath321 Exp $ */

/**Update functions for  CR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera <isuru@opensource.lk>
*
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

global $editid;
function _shn_cr_cedt_start($errors=false){
	if($errors)
		display_errors();
	global $global;
	$db = $global['db'];
?>
<h2><?php echo _t("Update Existing Victims")?></h2>
<?php
	/*$query="select c_uuid from camp_general where name='{$_REQUEST['cmp_id']}'";
	$res=$db->Execute($query);
	$editid=$res->fields['c_uuid'];*/
	$editid=$_REQUEST['cmp_id'];
	$_SESSION['editid']=$editid;
	
	_shn_cr_get_session($editid);
	shn_form_fopen(eppl);
	shn_form_fsopen(_t("General Details"));
	shn_form_hidden(array('seq'=>'chk'));
?>
<table>
<tr>
<td>
<?php	
	shn_form_text(_t("Men"),"men",'size="5"',array('value'=>$_SESSION['camp_men']));
?>
</td><td>

<?php
	shn_form_text(_t("Capacity"),"capacity",'size="5"',array('value'=>$_SESSION['camp_capacity']));
?>
</td>
</tr>

<tr>
<td>
<?php
	shn_form_text(_t("Women"),"women",'size="5"',array('value'=>$_SESSION['camp_women']));
?>
</td><td>

<?php
	shn_form_text(_t("Capacity"),"capacity1",'size="5"',array('value'=>$_SESSION['camp_capacity']));
?>
</td>
</tr>


<tr>
<td>
<?php
	shn_form_text(_t("Children"),"children",'size="5"',array('value'=>$_SESSION['camp_children']));
?>
</td><td>

<?php
	shn_form_text(_t("Capacity"),"capacity2",'size="5"',array('value'=>$_SESSION['camp_capacity']));
?>
</td>
</tr>

</table>
<?php
	shn_form_text(_t("Total Infected"),"infected_count",'size="5"',array('value'=>$_SESSION['camp_infected']));




	shn_form_submit("Update");
	shn_form_fsclose();
	shn_form_fclose();
}





function _shn_cr_cedt_chk($errors=false){
	if($errors)
		display_errors;
	
	global $global;

	$_SESSION['camp_infected']=$_POST['infected_count'];

	$_SESSION['camp_capacity']=$_POST['capacity'];

	$_SESSION['camp_men']=$_POST['men'];
	$_SESSION['camp_women']=$_POST['women'];
	$_SESSION['camp_children']=$_POST['children'];
	$_SESSION['camp_total']= $_SESSION['camp_men']+ $_SESSION['camp_women']+ $_SESSION['camp_children'];

}

function _shn_cr_validate_error(){
	clean_errors();
	$error_flag=false;


if(!(null == ($_POST['family']))){
		if(!is_numeric(trim($_POST['infected_count']))){
			add_error(_t("The infected count is not a valid number"));
			$error_flag=true;
		}
	}
if(!(null == ($_POST['capacity']))){
                if(!is_numeric(trim($_POST['capacity']))){
                        add_error(_t("The capacity is not a valid number"));
                        $error_flag=true;
                }
        }

	if(!(null == ($_POST['men']))){
		if(!is_numeric(trim($_POST['men']))){
			add_error(_t("The men count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['women']))){
		if(!is_numeric(trim($_POST['women']))){
			add_error(_t("The women count is not a valid number"));
			$error_flag=true;
		}
	}
	if(!(null == ($_POST['children']))){
		if(!is_numeric(trim($_POST['children']))){
			add_error(_t("The children count is not a valid number"));
			$error_flag=true;
		}
	}
	

	
	return $error_flag;
}


/**
 * populate session variables from database
 * @param camp_id	the retrieved camp id
*/

function _shn_cr_get_session($camp_id){
	global $global;
	$db = $global['db'];
	
	$query="SELECT a.name,a.location_id,a.opt_camp_type,a.address,admin_name,admin_no,family,total,men,women,children,capacity FROM camp_general a LEFT OUTER JOIN camp_reg b on a.c_uuid=b.c_uuid WHERE a.c_uuid='{$camp_id}'";
	
	$res = $db->Execute($query);
	$_SESSION['camp_infected']=$res->fields['family'];
	$_SESSION['camp_men']=$res->fields['men'];
	$_SESSION['camp_women']=$res->fields['women'];
	$_SESSION['camp_children']=$res->fields['children'];
	$_SESSION['camp_total']=$res->fields['total'];
    $_SESSION['camp_capacity']=$res->fields['capacity'];
											
}


function _shn_cr_cedt_commit(){
//insert to database;
	global $global;
	global $editid;
	$db = $global['db'];

	$q="UPDATE camp_general SET capacity={$_SESSION['camp_capacity']} WHERE c_uuid='{$_SESSION['editid']}'";
	$res = $db->Execute($q);
	
	$q="UPDATE camp_reg SET men='{$_SESSION['camp_men']}',women='{$_SESSION['camp_women']}',family='{$_SESSION['camp_infected']}',children='{$_SESSION['camp_children']}',total='{$_SESSION['camp_total']}' WHERE c_uuid='{$_SESSION['editid']}'";


	//$q="update camp_reg set men='{$_SESSION['camp_men']}'  where c_uuid='{$_SESSION['editid']}'";
	$res = $db->Execute($q);
?>

<h2><?= add_confirmation(_t("You have succesfully edited the people count ").$_SESSION['camp_name']);?></h2>


</tbody>
</table>
</div>

</ul>
<br><br>
<p><?php echo _t("Use the navigation menu to continue")?></p>
<?php	
}

?>

