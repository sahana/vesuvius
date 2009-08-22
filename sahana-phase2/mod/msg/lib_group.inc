<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Respere | http://respere.com/
* @package		Sahana - http://sahana.lk/
* @subpackage   msg
* @tutorial
* @version		$Id: lib_group.inc,v 1.13 2009-08-22 17:17:22 ravithb Exp $
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*  
*/

include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';
include_once($global['approot'].'/mod/msg/handler_contacts.inc');


/*
@function	Generic function to display all groups
*/
function shn_msg_list_groups($choice)
{
	
	// get the list of group types from the db
	$list=_shn_msg_tell_type_name();
	foreach ($list as $grp_type){
		// this will creat a cadge for each group category
		shn_form_fopen("", null,array('req_message'=>false));
			shn_form_fsopen("$grp_type Group");
				//this section will handle 'groups' under each sub-category
				_shn_msg_list_grp_with_link($grp_type);
			shn_form_fsclose();
		shn_form_fclose();
	}
}

/*
@function	Display inside the group
*/
function shn_msg_view_group($id)
{
	// get detail  info about the group
	$group=_shn_msg_get_group_details($id);
	//print_r($group);
	$name=$group['name'];
	
	shn_form_fopen("", null,array('req_message'=>false));
		shn_form_fsopen("Information of $name Group");
		?><!-- draw the table -->
		<table>
  			<tr>
    			<td>Group Name</td>
    			<td><strong><font color=green><?print $name; ?></font></strong></td>
  			</tr>
  			<tr>
  				<td>Group Type</td>
  				<td><font color=green><?print $group['type']; ?></font></td>
  			</tr>
  			<tr>
  				<td>Description</td>
  				<td><font color=green><?print $group['desc']; ?></font></td>
  			</tr>
  			<tr>
  				<td>Created Date</td>
  				<td><font color=green><?print $group['created_date'] ?></font></td>
  			</tr>
  			<tr>
  				<td>Members</td>
  				<td><font color=blue><?_shn_msg_member_list($id, $name=true);?></font></td>
  			</tr>
		</table>

		<?php
				shn_form_fsclose();
		/*shn_form_fsopen("Member Information");
		
		shn_form_fsclose();*/
	shn_form_fclose();
}

/*
@function	creatre (and display) a list of members in perticular group
*/
function _shn_msg_member_list($group_id)
{
	$members=shn_msg_show_members($group_id, $name=true);
	foreach($members as $person_id => $person){
		//print $id." ".$person."<br>";
		?> <a href="index.php?mod=msg&act=select_person&id=<?print $person_id; ?>&grpid=<?print $group_id; ?>"><?php print $person; ?></a><?php
				print "<br>";
	}
}

/*
@function	Retrieve Group details
*/
function _shn_msg_get_group_details($id)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	$q=" select * from msg_people_group where m_uuid='$id';";
	$res=$db->Execute($q);
	
	$group[name]="{$res->fields['grp_name']}";
	$group[desc]="{$res->fields['grp_des']}";
	$group[type]="{$res->fields['grp_type_desc']}";
	$group[created_date]="{$res->fields['grp_created_date']}";
	
	return $group;
}

/*
@function	this will give list of groups that given individual is a member  
*/
function shn_msg_show_membership($person_id)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	$q="select group_id from msg_group_membership where person_id='$person_id';";
	$res=$db->Execute($q);
	
	$x=0;
	while (!$res->EOF)
	{
		$group_list[$x]="{$res->fields['group_id']}";
		$x=$x+1;
		$res->MoveNext();
	}
	return $group_list;
}

/*
@function	this will give list of person_ids that are members of a given group
@note		pass $name if it's needed a list of names of the members, otherwise 
			function will pass only list of member ids
*/
function shn_msg_show_members($group_id, $name)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	$q="select person_id from msg_group_membership where group_id='$group_id';";
	$res1=$db->Execute($q);
	
	$x=0;
	while (!$res1->EOF)
	{
		$member_list[$x]="{$res1->fields['person_id']}";
		$x=$x+1;
		$res1->MoveNext();
	}
	//print_r($member_list);
	if(!$name){ // return "person_ids"
		
		return $member_list;
	} else { // return "person_names"
		$x=0;
		foreach($member_list as $member_id){
			
			$q="select name from msg_people_contact where m_uuid='$member_id';";
			$res2=$db->Execute($q);
			//$name_list[$x]="{$res2->fields['name']}";
			$name_list[$member_id]="{$res2->fields['name']}";
			$x=$x+1;
		}
		//print_r($name_list);
		return $name_list;	
	} // end of else
}

/*
@function	this will update the group information
*/
function shn_msg_update_group($store,$group_id,$group_name,$description,$type)
{
	
		
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
		
	if($store==""){ // if DONOT want to store
	// get the group details, based on the group_id	
		
		// get group id from the url
		$group_id=$_GET['id'];
		
		$q="select grp_name,grp_des,grp_type,grp_type_desc from msg_people_group where m_uuid='$group_id';";
		$res=$db->Execute($q);
		
		$group_name="{$res->fields['grp_name']}";
		$description="{$res->fields['grp_des']}";
		$type="{$res->fields['grp_type']}";
		
		// display the edit from (using add form)
		shn_msg_contact_add_group($group_name,$group_id,$description,$type);
		
	} else { // if want to store
	// store the updated values to the db
	
		/*$group_name=$_POST['grp_name'];
		$description=$_POST['desc'];
		$type=$_POST['type'];*/
		
		// get the type name
		$type_desc=_shn_msg_tell_type_name($type);
		
		$q="update msg_people_group set grp_name='$group_name', grp_des='$description', grp_type='$type', grp_type_desc='$type_desc' where m_uuid='$group_id';";
		$res=$db->Execute($q);
		
		//print $q;
		if($res){
			add_confirmation("Updated the <strong>".$group_name."</strong> group!");
			//show the modified list again
			shn_msg_list_groups();
		} else {
			add_error("Can not update the <strong>".$group_name."</strong> group!");
		}	
	}
	
}


/*
@function	this will delete the group from the system
*/
function shn_msg_delete_group($group_id)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	$q1="delete from msg_people_group where m_uuid='$group_id';";
	$q2="delete from msg_group_membership where group_id='$group_id';";
	
	$res1=$db->Execute($q1);
	$res2=$db->Execute($q2);
	
	If(($res1)&&($res2)){
		add_confirmation("Group was deleted from the system!");
	} else {
		add_error("Group can not be deleted from the system!");
	}
	
}



