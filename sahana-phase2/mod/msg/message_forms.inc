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
* @author	Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package	sahana
* @subpackage	ims
* @tutorial
* @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/
//include_once $global['approot']."/inc/lib_form.inc";
function _shn_msg_add_group()
{
?>
    <h1 align="center"><?php print _("Add Groups"); ?> </h1>
<?php

    global $global;
   // $module = $global['module'];
    $form_opts['name']="add_group_form";
    
    
    shn_form_fopen("add_group_actions",null,$form_opts);
    shn_form_fsopen("Add Groups");
    shn_form_text(_("Group Name : "),'group_name','size="50"',array('req'=>true,'help'=>_('Name of the Group')));

    ?><div class="info"><?=_("If you want to enter multiple e-mail addresses and multiple mobile numbers, please seperate them by only using a comma.");?></div><br /><?

    shn_form_textarea(_("e-mail address/es : "),'email','size="40"',array('req'=>true));
    shn_form_textarea(_("Mobile Number/s : "),'mobile_number','size="40"',array('req'=>true));
    shn_form_fsclose();
    $extra_opts['br']=false;
    $extra_opts['req']=false;
?>
<center>
<?php
    shn_form_button(_("Save"),"onClick='change_action(\"save\")'",$extra_opts);
    shn_form_button(_("Clear"),"onClick='change_action(\"clear\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
    //shn_form_submit(_("Save"));
?>
</center>
<?php
    shn_form_fclose();
}


function _shn_msg_add_group_actions()
{
    global $global;
    $db=$global["db"];

    $group_name=trim($_POST['group_name']);
    $email=trim($_POST['email']);
    $mobile_number=trim($_POST['mobile_number']);

    $id = shn_create_uuid("messaging");
    //print $id;

    $sql1="INSERT INTO messaging_group (group_uuid,group_name,address,mobile) VALUES ('$id','$group_name','$email','$mobile_number');";
	$msg1 = $db->Execute($sql1);

    $_POST['group_name']="";
    $_POST['email']="";
    $_POST['mobile_number']="";
    add_confirmation('Your data has been submitted successfully');
    shn_msg_add_group();
   

}

function _shn_msg_validate_add_group()
{
    $error_flag=false;
    
    $group_name=trim($_POST['group_name']);
    $email=trim($_POST['email']);
    $mobile_number=trim($_POST['mobile_number']);

    $email_array=array();
    $email_array=split(",",$email);
    $number_of_address=count($email_array);

    $mobile_array=array();
    $mobile_array=split(",",$mobile_number);
    $number_of_mobiles=count($mobile_array);

    if($group_name==NULL)
    {
	add_error(SHN_ERR_MSG_GROUP_NAME_INCOMPLETE);
        $error_flag=true;
    }
    if($email==null && $mobile_number==NULL)
    {
	add_error(SHN_ERR_MSG_EMAIL_MOBILE_INCOMPLETE);
        $error_flag=true;
    }
    if(!$email==NULL)
    {
	for($i=0;$i<$number_of_address;$i++)
	{
	    $email_address=$email_array[$i];
	    if(!shn_valid_email($email_address))
	    {
		add_error(SHN_ERR_MSG_EMAIL);
                $error=true;
	    }
	}
    }
    if(!$mobile_number==NULL)
    {
	for($i=0;$i<$number_of_mobiles;$i++)
	{
	    $mobile_temp=$mobile_array[$i];
	    if(!is_numeric($mobile_temp))
            {
                add_error(SHN_ERR_MSG_NUMERIC_VALUE_MOBILE);
                $error_flag=true;
            }
	}
    }

    return $error_flag;
    
}

function _shn_msg_edit_group()
{
    global $global;
    $db=$global["db"];

?>
    <h1 align="center"><?php print _("Edit Groups"); ?> </h1>
<?php
    
    shn_form_fopen(null);
    shn_form_fsopen(null);

?>
    <div id ="result">
    <table>
        <thead>
        <td><?=_("Group Name");?></td>
        <td><?=_("Mail IDs/Phone Numbers Count");?></td>
        <td><?=_("Action");?></td>
        </thead>
    <tbody>
<?php

    $sql1="SELECT * FROM messaging_group;";
    $msg1=$db->Execute($sql1);
    
    while(!$msg1==NULL && !$msg1->EOF)
    {
	//$count_email=0;
        //$count_sms=0;
	$group_uuid = $msg1->fields['group_uuid'];
	$group_name = $msg1->fields['group_name'];
	$email_address = $msg1->fields['address'];
	$mobile = $msg1->fields['mobile'];

	$array_address=array();
        $array_address=split(",",$email_address);
        $number_of_address=count($array_address);

	$array_mobile=array();
	$array_mobile=split(",",$mobile);
	$number_of_mobiles=count($array_mobile);

?>
	<tr>
	<td><center><?php print $group_name;?></center></td>
	<td><center><?php print ($number_of_address." mail IDs/".$number_of_mobiles." phone numbers");?></center></td>
	<td><center><a href="index.php?mod=msg&act=edit_group_item&group_uuid=<?php echo $group_uuid;?>"><?php print ("View and Edit");?></a></center></td>
	</tr>
<?php
	
	$msg1->MoveNext();
    }
?>
	</tbody>
	</table>
<?php

    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_msg_edit_group_form($group_uuid)
{
?>
    <h1 align="center"><?php print _("View and Edit Group"); ?> </h1>
<?php

    global $global;
    $db=$global['db'];

    $sql1="SELECT * FROM messaging_group WHERE group_uuid='$group_uuid';";
    $msg1=$db->Execute($sql1);

    $group_name=$msg1->fields['group_name'];
    $address=$msg1->fields['address'];
    $mobile=$msg1->fields['mobile'];
   // $module = $global['module'];
    $form_opts['name']="view_edit_group_form";
    
    
    shn_form_fopen("view_edit_group_actions",null,$form_opts);
    shn_form_fsopen("Add Group");
    shn_form_text(_("Group Name : "),'group_name','size="50"',array('req'=>true,'value'=>$group_name,'help'=>_('Name of the Group')));
    ?><div class="info"><?=_("If you want to enter multiple e-mail addresses and multiple mobile numbers, please seperate them by only using a comma.");?></div><br /><?
    shn_form_textarea(_("e-mail address/es : "),'email','size="40"',array('req'=>true,'value'=>$address));
    shn_form_textarea(_("Mobile Number/s : "),'mobile_number','size="40"',array('req'=>true,'value'=>$mobile));
    shn_form_fsclose();
    $extra_opts['br']=false;
    $extra_opts['req']=false;
?>
<center>
<?php
    shn_form_button(_("Save"),"onClick='change_action_view_edit(\"edit\")'",$extra_opts);
    shn_form_button(_("Delete"),"onClick='change_action_view_edit(\"delete\")'",$extra_opts);
    shn_form_button(_("Close"),"onClick='change_action_view_edit(\"close\")'",$extra_opts);

    shn_form_hidden(array('group_uuid'=>$group_uuid));
    
    shn_form_hidden(array('action'=>'0'));
    //shn_form_submit(_("Save"));
?>
</center>
<?php
    shn_form_fclose();	
}

function _shn_validate_edit_group()
{
    $error_flag=false;

    $group_name=trim($_POST['group_name']);
    $email=trim($_POST['email']);
    $mobile_number=trim($_POST['mobile_number']);

    $email_array=array();
    $email_array=split(",",$email);
    $number_of_address=count($email_array);

    $mobile_array=array();
    $mobile_array=split(",",$mobile_number);
    $number_of_mobiles=count($mobile_array);

    if($group_name==NULL)
    {
	add_error(SHN_ERR_MSG_GROUP_NAME_INCOMPLETE);
        $error_flag=true;
    }
    if($email==NULL && $mobile_number==NULL)
    {
	add_error(SHN_ERR_MSG_EMAIL_MOBILE_INCOMPLETE);
        $error_flag=true;
    }
    if(!$email==NULL)
    {
	for($i=0;$i<$number_of_address;$i++)
	{
	    $email_address=$email_array[$i];
	    if(!shn_valid_email($email_address))
	    {
		add_error($email_address." ".SHN_ERR_MSG_EMAIL);
                $error=true;
  		//break;
	    }
	}
    }
    if(!$mobile_number==NULL)
    {
	for($i=0;$i<$number_of_mobiles;$i++)
	{
	    $mobile_temp=$mobile_array[$i];
	    if(!is_numeric($mobile_temp))
            {
                add_error($mobile_temp." ".SHN_ERR_MSG_NUMERIC_VALUE_MOBILE);
                $error_flag=true;
		//break;
            }
	}
    }

    return $error_flag;
}


function _shn_msg_list_group()
{
    global $global;
    $db=$global["db"];

?>
    <h1 align="center"><?php print _("List Groups"); ?> </h1>
<?php
    
    shn_form_fopen(null);
    shn_form_fsopen(null);

?>
    <div id ="result">
    <table>
        <thead>
        <td><?=_("Group Name");?></td>
        <td><?=_("e-mails IDs");?></td>
        <td><?=_("Mobile Numbers");?></td>
        </thead>
    <tbody>
<?php
    $sql1="SELECT * FROM messaging_group;";
    $msg1=$db->Execute($sql1);

    while(!$msg1==NULL && !$msg1->EOF)
    {

	$group_uuid=$msg1->fields['group_uuid'];
	$group_name=$msg1->fields['group_name'];
	$address=$msg1->fields['address'];
	$mobile=$msg1->fields['mobile'];

	$address_array=array();
	$address_array=split(',',$address);
	$count_addresses=count($address_array);

	$mobile_array=array();
	$mobile_array=split(',',$mobile);
	$count_mobiles=count($mobile_array);

?>
    <tr>
    <td><center><?php print $group_name;?></center></td>
    <td><center>
<?php
    for($i=0;$i<$count_addresses;$i++)
    {
	 print $address_array[$i];
?>
	<br>
<?php
	
    }
    $count_addresses=0;
?>
    </center>
    </td>
    <td>
    <center>
<?php

    for($j=0;$j<$count_mobiles;$j++)
    {
	print $mobile_array[$j];
?>
	<br>
<?php
    }
    $count_mobiles=0;
?>
    </center>
    </td>
    </tr>
<?php

	$msg1->MoveNext();
    }
?>
    </tbody>
    </table>
    </div>
<?php
    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_msg_send_group()
{
?>
    <h1 align="center"><?php print _("Send Group"); ?> </h1>
<?php

    global $global;
    $db=$global['db'];

    $sql1="SELECT * FROM messaging_group;";
    $msg1=$db->Execute($sql1);
    $group_array=array();

    while(!$msg1==NULL && !$msg1->EOF)
    {
	$group_array[$msg1->fields['group_uuid']]=$msg1->fields['group_name'];
	$msg1->MoveNext();
    }
   // $module = $global['module'];
    $form_opts['name']="send_group_form";
    
    
    shn_form_fopen("send_group_action");
    shn_form_fsopen("Message Details");
    shn_form_textarea(_("Message : "),'message','size="40"',array('req'=>true, 'help'=>_('Enter Your message here')));

    shn_form_multi_select('group_select',$group_array,_("Group/s Selection"),'size="5" multiple="true"',array('req'=>true,'help'=>_('Select the Group or Groups')));
   // shn_form_select($group_array,_('Group Selection'),'group_select','size="1"',null);
    //shn_form_opt_multi_select('group_select','','multiple="true"',$extra_opts);
    shn_form_fsclose();

    //shn_form_radio(null,_("Undefined"),'undefined','size="2"',null);
    shn_form_fsopen("Undefined");
    //$options=array('item' => 'Item','catalogue' => 'Catalogue');
    //shn_form_radio($options,'','item_cat_radio');
    shn_form_checkbox(_("Undefined:"),'undefined',null,null);
    //shn_form_radio(null,_("Undefined"),'undefined','size="2"',null);
    shn_form_textarea(_("e-mail : "),'email','size="40"',array('req'=>true, 'help'=>_('Enter Your email here')));
    shn_form_textarea(_("Phone Number : "),'phone','size="40"',array('req'=>true, 'help'=>_('Enter Your Phone Number here')));
    
    shn_form_fsclose();
    
    shn_form_submit("Submit");
    //$extra_opts['br']=false;
    //$extra_opts['req']=false;
?>

<?php
    shn_form_fclose();

}

function _shn_msg_send_group_action()
{
    $message=trim($_POST['message']);
    $group_select=$_POST['group_select'];
    $undefined=trim($_POST['undefined']);
    $email=trim($_POST['email']);
    $phone=trim($_POST['phone']);

    //print_r($group_select);
    print_r($group_select);

    
}

function _shn_msg_customized_messaging()
{
?>
    <h1 align="center"><?php print _("Customized Messaging"); ?> </h1>
<?php

    global $global;
    $db=$global['db'];

    $form_opts['name']="customized_messaging_form";
    
    
    shn_form_fopen("customized_messaging_actions",null,$form_opts);
    shn_form_fsopen("Messaging");
    shn_form_textarea(_("Message : "),'message','size="40" maxlength="10"',array('req'=>true));
    shn_form_textarea(_("e-mail address/es : "),'email','size="40"',array('req'=>true));
    shn_form_textarea(_("Mobile Number/s : "),'mobile_number','size="40"',array('req'=>true));
    shn_form_fsclose();
    $extra_opts['br']=false;
    $extra_opts['req']=false;
?>
<center>
<?php
    shn_form_button(_("Send"),"onClick='change_action_customized_messaging(\"send\")'",$extra_opts);
    shn_form_button(_("Clear"),"onClick='change_action_customized_messaging(\"clear\")'",$extra_opts);
    //shn_form_button(_("Close"),"onClick='change_action_customized_messaging(\"close\")'",$extra_opts);

    //shn_form_hidden(array('group_uuid'=>$group_uuid));
    
    shn_form_hidden(array('action'=>'0'));
    //shn_form_submit(_("Save"));
?>
</center>
<?php
    shn_form_fclose();	
}

function _shn_msg_validate_customized_messaging()
{
    $error_flag=false;

    $message=trim($_POST['message']);
    $email=trim($_POST['email']);
    $mobile_number=trim($_POST['mobile_number']);

    $email_array=array();
    $email_array=split(",",$email);
    $number_of_address=count($email_array);

    $mobile_array=array();
    $mobile_array=split(",",$mobile_number);
    $number_of_mobiles=count($mobile_array);

    if($message==NULL)
    {
	add_error(SHN_ERR_MSG_MESSAGE_INCOMPLETE);
        $error_flag=true;
    }
    if($email==NULL && $mobile_number==NULL)
    {
	add_error(SHN_ERR_MSG_EMAIL_MOBILE_INCOMPLETE);
        $error_flag=true;
    }
    if(!$email==NULL)
    {
	for($i=0;$i<$number_of_address;$i++)
	{
	    $email_address=$email_array[$i];
	    if(!shn_valid_email($email_address))
	    {
		add_error($email_address." ".SHN_ERR_MSG_EMAIL);
                $error=true;
  		//break;
	    }
	}
    }
    if(!$mobile_number==NULL)
    {
	for($i=0;$i<$number_of_mobiles;$i++)
	{
	    $mobile_temp=$mobile_array[$i];
	    if(!is_numeric($mobile_temp))
            {
                add_error($mobile_temp." ".SHN_ERR_MSG_NUMERIC_VALUE_MOBILE);
                $error_flag=true;
		//break;
            }
	}
    }

    return $error_flag;
}

function _shn_msg_customized_messaging_actions()
{
    $message=trim($_POST['message']);
    $email=trim($_POST['email']);
    $mobile_number=trim($_POST['mobile_number']);

    $email_array=array();
    $email_array=split(",",$email);
    $number_of_address=count($email_array);

    $mobile_array=array();
    $mobile_array=split(",",$mobile_number);
    $number_of_mobiles=count($mobile_array);
}

?>

<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.add_group_form.submit();
         return;
    }
</script>

<script type="text/javascript">
    function change_action_view_edit(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.view_edit_group_form.submit();
         return;
    }
</script>

<script type="text/javascript">
    function change_action_customized_messaging(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.customized_messaging_form.submit();
         return;
    }
</script>
