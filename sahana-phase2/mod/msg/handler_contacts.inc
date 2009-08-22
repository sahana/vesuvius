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
* @copyright    Respere - http://respere.com/
* @package		sahana
* @subpackage   msg
* @tutorial
* @version		$Id: handler_contacts.inc,v 1.13 2009-08-22 17:17:22 ravithb Exp $;
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*  
*/

include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';
include_once 'lib_group.inc';

/*
@author		Pradeeper <pradeeper@respere.com>
@function	Generate the add contact form
*/
function shn_msg_form_add_contact($name,$full_name,$address,$group,$method,$mob1,$mob2,$email1,$email2,$person_id)
{
	if($name!="") {
		$tmp="Edit";
		
	} else {
		$tmp="Add";
		$person_id=NULL;
		$id=$_GET['id'];
		
		// get group details
		$group_details=_shn_msg_get_group_details($id);
		$group=$group_details['name'];
	}
	
	
	print "<h2>$tmp Contact</h2>";
	shn_form_fopen("contact_submit", null,array('req_message'=>true));
		shn_form_fsopen("Personal Information");
			if ($tmp=="Edit") {
				shn_form_hidden(array("target"=>"edit_contact","person_id"=>"$person_id"));
			} else {
				shn_form_hidden(array("target"=>"add_contact"));
			}
			shn_form_text("Name : ","name",null,array("req"=>true, 'value'=>"$name"));
			shn_form_text("Full Name : ","full_name","size='40'",array('value'=>"$full_name"));
			shn_form_textarea("Address", "address", $text_opt, array('value'=>"$address"));
		shn_form_fsclose();
		shn_form_fsopen("Group Information");
			//shn_form_multi_select("groups",array("one"=>"one","two"=>"two","three"=>"three"),"Groups : ");
			shn_form_multi_select("groups",shn_msg_basic_group_list(),"Groups : ",array('value'=>"$group"));
		shn_form_fsclose();	
		shn_form_fsopen("Method of Contacting");
			echo "<p>Please select one of the following methods. Select option <u>'Both'</u> for receiving messages from both methods.</p>";
			shn_form_radio(array("mobile"=>"Mobile","email"=>"eMail","both"=>"Both"),"Preferred Method of Contacting : ",'option','$method',array('value'=>""));
			//shn_shn_form_radio(array("mobile"=>"Mobile","email"=>"eMail","both"=>"Both"),"Preferred Method of Contacting : ",'option','',array('value'=>""));
		shn_form_fsclose();
		shn_form_fsopen("Mobile Number Information");
			echo "<p>Please enter valid mobile number. Primary Mobile number will be selected automatically.</p>";
			shn_form_text("Primary Mobile Number : ","mob1","size='10'",array('value'=>"$mob1"));
			shn_form_text("Secondary Mobile Number : ","mob2","size='10'",array('value'=>"$mob2"));
		shn_form_fsclose();
		shn_form_fsopen("eMail Address Information");
			echo "<p>Please enter valid email address. Primary address will be selected automatically.</p>";
			shn_form_text("Primary email : ","email1","size='20'",array('value'=>"$email1"));
			shn_form_text("Secondary email : ","email2","size='20'",array('value'=>"$email2"));
		shn_form_fsclose();
	shn_form_submit("Save", $submit_opts = null);	
	shn_form_fclose();
}


/*
@function	This will edit individual contact using above form
*/
function shn_msg_form_edit_contact($id)
{
	include_once "lib_contact.inc";
	
	// fetch the person information from the db
	$person=_shn_msg_fetch_person_details($id);
	
	$name=$person['name'];
	$full_name=$person['full_name'];
	$address=$person['address'];
	$group=$person['group'];
	$primary_method=$person['primary_method'];
	$mob1=$person['primary_mobile'];
	$mob2=$person['secondary_mobile'];
	$email1=$person['primary_email'];
	$email2=$person['secondary_email'];
	
	// pass values that extracted from the db to the add form
	shn_msg_form_add_contact($name,$full_name,$address,$group,$primary_method,$mob1,$mob2,$email1,$email2,$id);
}


/*
@function	This will store collected individual information in the DB
*/
function _shn_msg_add_contact($person_id)
{
	// collecting post data
	$name=$_POST['name'];
	$fullname=$_POST['full_name'];
	$address=$_POST['address'];
	$method=$_POST['option'];
	$mobile1=$_POST['mob1'];
	$mobile2=$_POST['mob2'];
	$email1=$_POST['email1'];
	$email2=$_POST['email2'];
	$group=$_POST['groups'];
	
	// check whether individual name was submitted
	if($name!=""){
		
		// check the prefered method and process
		switch($method) {

			case mobile:
				if($mobile1!=""){
					// store data in the db
					if($person_id!=""){
						_shn_msg_store_edit_contact($name, $fullname, $address, $method, $mobile1, $mobile2, $email1, $email2, $group,$person_id);
					} else {
						_shn_msg_store_contact($name, $fullname, $address, $method, $mobile1, $mobile2, $email1, $email2, $group);
					}
				} else {
					add_error("If preferred method of receiving messages is <u>Mobile</u>, please provide a valid mobile number as the <u>'Primary Mobile Number'</u>.");
					shn_msg_form_add_contact(); // calling the form	
				}
			break;
				
			case email:
				if($email1!=""){
					// store data in the db
					if($person_id!=""){
						_shn_msg_store_edit_contact($name, $fullname, $address, $method, $mobile1, $mobile2, $email1, $email2, $group,$person_id);
					} else {
						_shn_msg_store_contact($name, $fullname, $address, $method, $mobile1, $mobile2, $email1, $email2, $group);
					}
				} else {
					add_error("If preferred method of receiving messages is <u>eMail</u>, please provide a valid email address as the <u>'Primary email'</u>.");
					shn_msg_form_add_contact(); // calling the form	
				}	
			break;

			case both:
				if(($mobile1!="")&&($email1!="")){
					// store data in the db
					if($person_id!=""){
						_shn_msg_store_edit_contact($name, $fullname, $address, $method, $mobile1, $mobile2, $email1, $email2, $group);
					} else {
						_shn_msg_store_contact($name, $fullname, $address, $method, $mobile1, $mobile2, $email1, $email2, $group);
					}
				} else {
					add_error("If preferred method of receiving messages is <u>Both</u>, please provide a valid mobile number and valid email as the <u>'Primary Mobile Number'</u> and <u>'Primary email'</u>.");
					shn_msg_form_add_contact(); // calling the form	
				}
			break;

			default:
					add_error("Please select <u>Preferred method</u> of sending messages!");
					shn_msg_form_add_contact(); // calling the form	
			break;	
		} // end of switch
		
		
		
	} else { // if name is not submitted
		add_error("<u>Name</u> is missing, please provide the individual name.!");
		shn_msg_form_add_contact(); // calling the form
	}
	
}

/*
@function	Store updated individual information in the db
*/
function _shn_msg_store_edit_contact($name, $fullname, $address, $method, $mobile1, $mobile2, $email1, $email2, $group,$person_id)
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	// update person inforation
	$q="update msg_people_contact set name='$name',full_name='$fullname',address='$address',primary_method='$method',primary_mobile='$mobile1',secondary_mobile='$mobile2',primary_email='$email1',secondary_email='$email2' where m_uuid='$person_id';";
	
	$res=$db->Execute($q);
	
	if($res){
		add_confirmation('Individual details were updated to the system successfully!');
		// show individual information again (next to the confirmation)
		shn_msg_view_person($person_id);
		/*echo "&nbsp;&nbsp;&nbsp;";
		echo "<a href='index.php?mod=msg&act=edit_contact_individual&id=$person_id'>Edit</a>";
		echo "&nbsp;&nbsp;&nbsp;";
		echo "<a href=''>Delete</a>";
		echo "<br>";*/
		// end of showing the information
		
		// Update person id and group id
		foreach ($group as $x => $group_id){
			$q="update msg_group_membership set group_id='$group_id' where person_id='$person_id';";
			$res=$db->Execute($q);
			if(!$res){
				add_error('Can not update group membership information to the database!');
			}
		}// end of 'foreach'
	} else {
		add_error('Can not update!');
	}
}
	
/*
@function	Delete individual information from the db
*/
function _shn_msg_delete_contact($person_id,$option)
{
	//connect db
	global $global;
	global $conf;
	$db = $global['db'];
	
	if($option=="yes") {
		$q1="delete from msg_people_contact where m_uuid='$person_id';"; 
		$q2="delete from msg_group_membership where person_id='$person_id';";
		//print $q;
		$res1=$db->Execute($q1);
		$res2=$db->Execute($q2);
		
		if(($res1)&&($res2)){
			add_confirmation('Contact was deleted successfully!');
		} else {
			add_error('Can not delete the contact from the system!');
		}
	} else {
		add_confirmation('Deletion was cancled!');
	}
	
}

/*
@function	Store individual information in the db
*/
function _shn_msg_store_contact($name, $fullname, $address, $method, $mobile1, $mobile2, $email1, $email2, $group)
{
	global $global;
	global $conf;
	$db = $global['db'];
        
    $person_id=shn_create_uuid('msg');
    
    // store person information
	$q="insert into msg_people_contact (m_uuid, name, full_name, address, primary_method, primary_mobile, secondary_mobile, primary_email, secondary_email) values ('$person_id','$name','$fullname','$address','$method','$mobile1','$mobile2','$email1','$email2');";
	
	$res = $db->Execute($q);
	
	if($res) {
		add_confirmation('Individual details were added to the system successfully! <a href="index.php?mod=msg&act=contact_individual">Click</a> to add another contact.');
		// store person id and group id
		foreach ($group as $x => $group_id){
			$q="insert into msg_group_membership (person_id, group_id) values ('$person_id','$group_id');";
			$res=$db->Execute($q);
			if(!$res){
				add_error('Can not add group membership information to the database!');
			}
		}// end of 'foreach'
		
		// display newly added contact's details
		shn_msg_view_person($person_id);
		
	} else {
		add_error('Can not add individual information to the db! Please contact your Administrator.');
	}
}


/*
@function	This function will add and update contact group/s to the database
*/
function shn_msg_contact_add_group($group_name,$group_id,$description,$type)
{
	if($group_name!="") {
		$tmp="Update";		
	} else {
		$tmp="Add";
		$person_id=NULL;
	}
	
	print "<h2>$tmp Contact Group</h2>";
	shn_form_fopen("contact_submit", null,array('req_message'=>true));
		if ($tmp=="Update") {
				shn_form_hidden(array("target"=>"update_contact_group","group_id"=>"$group_id"));
			} else {
				shn_form_hidden(array("target"=>"add_contact_group"));
			}
		shn_form_fsopen("Group Information");
			shn_form_text("Group Name : ","grp_name",null,array("req"=>true, 'value'=>"$group_name"));
			shn_form_text("Short Description : ","desc","size='30'",array('value'=>"$description"));
			shn_form_opt_select('opt_msg_group_category', "Group Type : ", $select_opts ="",array('value'=>"$type"));
		shn_form_fsclose();
	shn_form_submit("$tmp", $submit_opts = null);
	if($tmp=="Update"){
		shn_form_submit("Cancel",'name="cancel"');	
	}
	shn_form_fclose();		
}


/*
@function	tell the group name when type is given
*/
function _shn_msg_tell_type_name($type)
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];

	if($type!=""){
		// get the type name from the 'field option' table
		$tmp_q="select option_description from field_options where option_code='$type';";
	} else {
		$tmp_q="select option_description from field_options where field_name='opt_msg_group_category';";
	}
	$res=$db->Execute($tmp_q);
	$x=0;
	while (!$res->EOF)
	{
		$tmp[$x]="{$res->fields['option_description']}";
		$x=$x+1;
		$res->MoveNext();
	}
	// remove the duplicates
	$tmp_grp_type_desc=array_unique($tmp);
	if($type!=""){
		$type_desc=$tmp_grp_type_desc[0];
	} else {
		$type_desc=$tmp_grp_type_desc;
	}
	return $type_desc;
}

/*
@function	store information about GROUPS (captured by shn_msg_contact_add_group) to the db
*/
function _shn_msg_add_contact_group()
{
	// connect to db
	global $global;
	global $conf;
	$db = $global['db'];
	
	// collecting post data
	$group_name=$_POST['grp_name'];
	$desc=$_POST['desc'];
	$type=$_POST['opt_msg_group_category'];
	
	// group id
	$uid = shn_create_uuid('msg');
	
		// get the type name
		$type_desc=_shn_msg_tell_type_name($type);	
	//print $type_desc;
	
	if ($group_name!=""){
		$q="insert into msg_people_group (m_uuid, grp_name, grp_des, grp_type_desc, grp_type) values ('$uid','$group_name','$desc','$type_desc','$type');";
		
		$res = $db->Execute($q);
		//print $q;
		if($res) {
			add_confirmation('Group was successfully added to the system. Please <a href="index.php?mod=msg&act=add_contact_group">click</a> to add another group.');
			shn_msg_contact_group();			
		} else {
			add_error('Can not add the group to the system. Please try <a href="index.php?mod=msg&act=add_contact_group">again</a>.<br>');
		}
		
	} else {
		add_error("<u>Group Name</u> is missing, please provide a Group name.!");
		shn_msg_contact_add_group();
	}
}


/*
@function	List GROUPS with urls
*/
function _shn_msg_list_grp_with_link($grp_type)
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	// following query give correct 'grp_type' based on the above $grp_type 		
	$q_type="select * from msg_people_group where grp_type_desc='$grp_type';";
	$res=$db->Execute($q_type);
	$x=0;
	while (!$res->EOF)
	{
		$grp_name="<strong>{$res->fields['grp_name']}</strong><br>";
		$grp_id="{$res->fields['m_uuid']}";
		
		?> <a href="index.php?mod=msg&act=select_group&id=<?print $grp_id; ?>"><?php print $grp_name; ?></a><?php
		$res->MoveNext();
	}
}

/*
@function	Give a list of existing GROUPS from the database | this is for multiple selection menus
*/
function shn_msg_basic_group_list()
{
	global $global;
	global $conf;
	$db = $global['db'];
	
	//$q="select grp_name from msg_people_group;";
	$q="select * from msg_people_group;";
	$res=$db->Execute($q);
	
	$x=0;
	while (!$res->EOF)
	{
		$list["{$res->fields['m_uuid']}"]="{$res->fields['grp_name']}";
		//$x=$x+1;
		$res->MoveNext();
	}
	//print "group contains ";
	//print_r ($list);
	//print "<br>";
	return $list;
}
