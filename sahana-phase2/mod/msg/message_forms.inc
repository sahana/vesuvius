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
* @author	Sriganeshan <sri@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package	sahana
* @subpackage	msg
* @tutorial
* @license	http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

global $global;
include_once $global['approot']."/mod/msg/message_group_forms.inc";

function _shn_msg_add_group()
{
?>
    <h1 align="center"><?php print _t("Add Groups"); ?> </h1>
<?php

    global $global;
    $form_opts['name']="add_group_form";
    $form_opts['req_message']=true;
    $extra_opts['cols']="40";
    $extra_opts['rows']="3";
    $extra_opts['req']="true";
    shn_form_fopen("add_group_actions",null,$form_opts);
    shn_form_fsopen("Add Groups");
    ?><div class="info"><?php echo _t("Multiple E-mail addresses or mobile numbers should be entered comma seperatedly.");?><br/><br/>
     <?php echo _t("Phone numbers are limited to 6-20 digits.");?><br/><br/>
     <?php echo _t("Group name is limited to 10 characters.");?></div><br/><br/>
    <?php
    shn_form_text(_t("Group Name : "),'new_group_name','MaxLength=10',array('req'=>true,'help'=>_t('Name of the Group')));
    shn_form_textarea(_t("E-mail address(es) : "),'email','size="30"',$extra_opts);
    shn_form_textarea(_t("Mobile Number(s) : "),'mobile_number','size="30"',$extra_opts);
    shn_form_fsclose();
    $extra_opts['br']=false;
    $extra_opts['req']=false;
?>
<center>
<?php
    shn_form_button(_t("Save"),"onClick='change_action(\"save\")'",$extra_opts);
    shn_form_button(_t("Clear"),"onClick='change_action(\"clear\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
?>
</center>
<?php
    shn_form_fclose();
}

function _shn_msg_add_group_actions()
{
    global $global;
    $db=$global["db"];

    $new_group_name=trim($_POST['new_group_name']);
    //print $new_group_name;
    $email=trim($_POST['email']);
    $mobile_number=trim($_POST['mobile_number']);
    $id = shn_create_uuid("messaging");
    
    $sql1="INSERT INTO messaging_group (group_uuid,group_name,address,mobile) VALUES ('$id','$new_group_name','$email','$mobile_number');";
    $msg1 = $db->Execute($sql1);
    $_POST['new_group_name']="";
    $_POST['email']="";
    $_POST['mobile_number']="";
    add_confirmation('Your group has been added successfully');
    shn_msg_add_group();
  
}

function _shn_msg_validate_add_group($group_name=NULL)
{
    
    global $global;
    $db=$global["db"];
    
    $error_flag=false;
    
    $new_group_name=trim($_POST['new_group_name']);
    $email=trim($_POST['email']);
    $mobile_number=trim($_POST['mobile_number']);
    
    $email_array=array();
    $email_array=split(",",$email);
    $number_of_address=count($email_array);

    $mobile_array=array();
    $mobile_array=split(",",$mobile_number);
    $number_of_mobiles=count($mobile_array);
    

    /*if($group_name==NULL)
    {
	add_error(SHN_ERR_MSG_GROUP_NAME_INCOMPLETE);
        $error_flag=true;
    }*/
    if($email==null && $mobile_number==NULL)
    {
	add_error(SHN_ERR_MSG_EMAIL_MOBILE_INCOMPLETE);
        $error_flag=true;
        
    }
    if(!$email==NULL)
    {
	for($i=0;$i<$number_of_address;$i++)
	{
	    $email_address=trim($email_array[$i]);
           if($email_address==NULL)
           {
	        add_error("remove unnecessary comma in E-mail address(es)");
                $error_flag=true;

           }
	    else if(!shn_valid_email($email_address))
	    {
		add_error($email_address." ".SHN_ERR_MSG_EMAIL);
                $error_flag=true;
	    }
	}
    }
    if(!$mobile_number==NULL)
    {
	for($i=0;$i<$number_of_mobiles;$i++)
	{
	    $mobile_temp=trim($mobile_array[$i]);
            if($mobile_temp==NULL)
            {
            add_error("remove unnecessary comma in Mobile Number(s)");
                $error_flag=true;

             }

         else if(!is_numeric($mobile_temp) || !preg_match('/^[0-9]*$/',$mobile_temp))
            {
                add_error($mobile_temp." is not a valid phone number");
                $error_flag=true;
            }else if(!shn_valid_len_range($mobile_temp,$min=5,$max=21))
             {
		add_error($mobile_temp." "."is not a valid phone number!");
                $error_flag=true;
             }
	}//end of for loop
    }//end of outer most if-else
    if($new_group_name==NULL)
    {
	add_error(SHN_ERR_MSG_GROUP_NAME_INCOMPLETE);
        $error_flag=true;
    }else if($group_name==NULL)
    {    
         
         $sql1="SELECT * FROM messaging_group WHERE group_name='$new_group_name'";
         $msg1 = $db->Execute($sql1);
         $db_group_name = $msg1->fields['group_name'];
          if($db_group_name)
          {
            add_error("A group with the name \"".$new_group_name."\" already exists. Enter a non existent group name!");
            $_POST['group_name']="";
            $error_flag=true;
          }
       
    }
    else
    {
       if(($comparison=strcmp($group_name,$new_group_name))!=0)
       {
         $sql1="SELECT * FROM messaging_group WHERE group_name='$new_group_name'";
         $msg1 = $db->Execute($sql1);
         $db_group_name = $msg1->fields['group_name'];
          if($db_group_name)
          {
            add_error("A group with the name \"".$new_group_name."\" already exists. Enter a non existent group name!");
            $_POST['group_name']="";
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
    <h1 align="center"><?php print _t("Edit Groups"); ?> </h1>
<?php
    
    shn_form_fopen(null,null,array('req_message'=>false));
    shn_form_fsopen(null);

?>
    <id ="result">
    <center>
    <table>
        <thead>
        <td><?php echo _t("Group Name");?></td>
        <td><?php echo _t("Mail IDs/Phone Numbers Count");?></td>
        <td><?php echo _t("Action");?></td>
        </thead>
    <tbody>
<?php

    $sql1="SELECT * FROM messaging_group;";
    $msg1=$db->Execute($sql1);
    
    while(!$msg1==NULL && !$msg1->EOF)
    {

        $number_of_address=0;
        $number_of_mobiles=0;
	$group_uuid = $msg1->fields['group_uuid'];
	$group_name = $msg1->fields['group_name'];
	$email_address = $msg1->fields['address'];
	$mobile = $msg1->fields['mobile'];
        
	$array_address=array();
        $array_address=split(",",$email_address);
        if($array_address[0])
        {
        $number_of_address=count($array_address);
        }else
        {
         $number_of_address=0;
        }
        
	$array_mobile=array();
	$array_mobile=split(",",$mobile);
        if($array_mobile[0])
        {
        $number_of_mobiles=count($array_mobile);
        }else
        {
         $number_of_mobiles=0;
        }
	
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
        </center>
<?php

    shn_form_fsclose();
    shn_form_fclose();
}

function _shn_msg_edit_group_form($group_uuid)
{
?>
    <h1 align="center"><?php print _t("View and Edit Group"); ?> </h1>
<?php

    global $global;
    $db=$global['db'];

    $sql1="SELECT * FROM messaging_group WHERE group_uuid='$group_uuid';";
    $msg1=$db->Execute($sql1);

    $group_name=$msg1->fields['group_name'];
    $address=$msg1->fields['address'];
    $mobile=$msg1->fields['mobile'];
    $form_opts['name']="view_edit_group_form";
    $form_opts['req_message']=true;
    
    shn_form_fopen("view_edit_group_actions",null,$form_opts);
    shn_form_fsopen("Add Group");
        ?><div class="info"><?php echo_t("Multiple E-mail addresses or mobile numbers should be entered comma seperatedly.");?></div><?php
     ?><div class="info"><?php echo _t("Phone numbers are limited to 5-20 digits.");?></div><?php
    ?><div class="info"><?php echo _t("Group name is limited to 10 characters.");?></div><br/><?php
    shn_form_text(_t("Group Name : "),'new_group_name','MaxLength=10',array('req'=>true,'value'=>$group_name,'help'=>_t('Name of the Group')));
    shn_form_textarea(_t("E-mail address(es) : "),'email','size="40"',array('req'=>true,'value'=>$address,'cols'=>"40",'rows'=>"3"));
    shn_form_textarea(_t("Mobile Number(s) : "),'mobile_number','size="40"',array('req'=>true,'value'=>$mobile,'cols'=>"40",'rows'=>"3"));
    shn_form_fsclose();
    $extra_opts['br']=false;
    $extra_opts['req']=false;
?>
<center>
<?php
    shn_form_button(_t("Save"),"onClick='change_action_view_edit(\"edit\")'",$extra_opts);
    shn_form_button(_t("Delete"),"onClick='change_action_view_edit(\"delete\")'",$extra_opts);
    shn_form_button(_t("Close"),"onClick='change_action_view_edit(\"close\")'",$extra_opts);
    shn_form_hidden(array('group_uuid'=>$group_uuid));
    shn_form_hidden(array('group_name'=>$group_name));
    shn_form_hidden(array('action'=>'0'));
    
?>
</center>
<?php
    shn_form_fclose();	
}

function _shn_msg_list_group()
{
    global $global;
    $db=$global["db"];

?>
    <h1 align="center"><?php print _t("List Groups"); ?> </h1>
<?php
    
    shn_form_fopen(null,null,array('req_message'=>false));
    shn_form_fsopen(null);

?>
    <div id ="result">
    <table>
        <thead>
        <td><?php echo _t("Group Name");?></td>
        <td><?php echo _t("e-mails IDs");?></td>
        <td><?php echo _t("Mobile Numbers");?></td>
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
    <h1 align="center"><?php print _t("Send Group"); ?> </h1>
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
    $extra_opts['cols']="40";
    $extra_opts['rows']="3";
    $form_opts['name']="messaging_form";
    $val='';
    shn_form_fopen("send_group_action",null,$form_opts);
    shn_form_fsopen("Message Details");
    ?><div class="info"><?php echo _t("Message content is limited to 160 characters.");?></div><br/><?php
    shn_form_textarea(_t("Message : "),'message','onkeydown="extracheck(this)"',$extra_opts);
// 'onKeyDown=x()'
    shn_form_multi_select('group_select',$group_array,_t("Group(s) Selection"),'size="6" width="20" multiple="true"',array('help'=>_t('Select the Group(s) you wish to message.<br/> hold down the Ctrl key for selecting more than one group')));

    shn_form_fsclose();
    shn_form_submit("Send Message");
?>
<?php
    shn_form_fclose();
}

function _shn_msg_send_group_action(){

  $message=trim($_POST['message']);
  $groups=$_POST['group_select'];
  $cnt_sms=0;
  $cnt_mail=0;
  $status_mail=array();
  $error_flag=false;
    if($message=="")
      {
      add_error(SHN_ERR_MSG_MESSAGE_INCOMPLETE);
      $error_flag=true;
      }
    if(($count_group=count($groups))=='0')
    {
     add_error("Please select a group/groups");
     $error_flag=true;
    }
    if(($kannel_status=shn_check_kannel_status())==0)
     {
      add_error("Kannel has not been started. Please start kannel");
      $error_flag=true;
     }
    if(!$error_flag)
    {
    global $global;
    $db=$global['db'];
    foreach($groups as $group)
    {     
    //print $group;
    $sql1="SELECT * FROM messaging_group WHERE group_uuid ='$group'";
    $msg1=$db->Execute($sql1);
    
    	$address=$msg1->fields['address'];
        $mobile=$msg1->fields['mobile'];
	$address_array=split(',',$address);
	$mobile_array=split(',',$mobile);
        
	$x=count($address_array);
        if($x>0 && trim($address))
        {
          ++$cnt_mail;
          $status_mail=_shn_msg_send_group_mail($message,$address_array);
        }
        
        $a=count($mobile_array);
        if($a>0 && trim($mobile))
        {
          
          ++$cnt_sms;
          $status_sms=shn_send_sms($message,$mobile_array);
        }
   
    if($cnt_mail>0 && $address_array[0])
     {
      /*if($status_mail)
          add_confirmation("mails sent successfully");    
      else
          add_error("Error in sending mails,reconfigure your SMTP settings");
     }*/
          foreach ($status_mail as $key => $value)
            {
            if($value)
            {
             add_confirmation("mail sent successfully to ".$key);
            }
            else
            {
            add_error("Error in sending mail to ".$key.",reconfigure your SMTP settings");
            }
          
          }//end of loop
       }//end of if-else

   if($cnt_sms>0 && $mobile_array[0])
    {  
     /*if($status_sms)
          add_confirmation("sms sent successfully");    
      else
          add_error("Error in sending sms,make sure kannel is up running");*/
      foreach ($status_sms as $key => $value)
          {
            if($value="1")
            {
             add_confirmation("sms sent successfully to ".$key);
            }
            else
            {
            add_error("Error in sending sms to ".$key.",reconfigure your kannel settings");
            }
          
          }//end of loop
    }//end -f if-else

   $_POST['message']="";
  }//end of main foreach
}//end of main if else  
 _shn_msg_send_group();

}

function _shn_msg_customized_messaging()
{
?>
    <h1 align="center"><?php print _t("Customized Messaging"); ?> </h1>
<?php

    global $global;
    $db=$global['db'];
    $extra_opts['cols']="40";
    $extra_opts['rows']="3";
    $extra_opts['req']=true;
    $form_opts['name']="customized_messaging_form";
    $form_opts['req_message']=true;
    shn_form_fopen("customized_messaging_actions",null,$form_opts);
    shn_form_fsopen("Messaging");
    ?><div class="info"><?php echo _t("Multiple E-mail addresses or mobile numbers should be entered comma seperatedly.");?><br/><br/><?php echo _t("Message content is limited to 160 characters.");?><br/><br><?php echo _t("Phone numbers are limited to 6-20 digits.");?>
    </div><?php
    print "<br/>";
    shn_form_textarea(_t("Message : "),'message','onkeydown="extracheck(this)"',$extra_opts);
//onKeyDown=y()
    //$extra_opts['req']=true
    shn_form_textarea(_t("E-mail address(es) : "),'email','size="40"',$extra_opts);
    shn_form_textarea(_t("Mobile Number(s) : "),'mobile_number','size="40"',$extra_opts);
    shn_form_fsclose();
    $extra_opts['br']=false;
    $extra_opts['req']=false;
?>
<center>
<?php
    shn_form_button(_t("Send"),"onClick='change_action_customized_messaging(\"send\")'",$extra_opts);
    shn_form_button(_t("Clear"),"onClick='change_action_customized_messaging(\"clear\")'",$extra_opts);
    
    shn_form_hidden(array('action'=>'0'));
   
?>
</center>
<?php
    shn_form_fclose();	
}

/**
 * Validate messages
 * @author Sri <sri@opensource.lk>
 * @edit Mifan: Gateway independant validation
 */
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
	    //$email_address=$email_array[$i];
            $email_address=trim($email_array[$i]);
	   if(!$email_address==NULL)
           {
	     if(!shn_valid_email($email_address))
	     {
		add_error($email_address." ".SHN_ERR_MSG_EMAIL);
                $error_flag=true;
  		//break;
	     }
           }
                     
	}
    }
    if(($kannel_status=shn_check_kannel_status())==0)
        {
          
         add_error("Kannel has not been started. Please start kannel");
         //print $kannel_status;
         $error_flag=true;
        }
    if(!$mobile_number==NULL)
    {
       /*if(($kannel_status=shn_check_kannel_status())==0)
        {
          
         add_error("Kannel has not been started. Please start kannel");
         //print $kannel_status;
         $error_flag=true;
        }*/   
          for($i=0;$i<$number_of_mobiles;$i++)
	  {
                         
	    $mobile_temp=trim($mobile_array[$i]);
            if(!$mobile_temp==NULL)
            {
	       if(!is_numeric($mobile_temp))
               {
                add_error($mobile_temp." ".SHN_ERR_MSG_NUMERIC_VALUE_MOBILE);
                $error_flag=true;
		//break;
               }if(!shn_valid_len_range($mobile_temp,$min=5,$max=21))
                {
		add_error($mobile_temp." "."is not a valid phone number!");
                $error_flag=true;
                }

            }
	  }

    }//end of if-else
    
    return $error_flag;
}

function _shn_msg_customized_messaging_actions()
{
        
        $message=$_POST['message'];
        $address=$_POST['email'];
        $mobile=$_POST['mobile_number'];

	$address_array=split(',',$address);
	$mobile_array=split(',',$mobile);
        $status_mail=array();
        $cnt_sms=0;
        $cnt_mail=0;
	
        $x=count($address_array);
        if($x>0 && trim($address))
        {
          ++$cnt_mail;
          $status_mail=_shn_msg_send_group_mail($message,$address_array);
        }
 
        $a=count($mobile_array);
        if($a>0 && trim($mobile))
        {
          ++$cnt_sms;
          $status_sms=shn_send_sms($message,$mobile_array);
        }

    if($cnt_mail>0 && $address_array[0])
     {
		
      foreach ($status_mail as $key => $value)
          {
            if($value=="1")
            {
             add_confirmation("mail sent successfully to ".$key);
            }
            else
            {
            add_error("Error in sending mail to ".$key.",reconfigure your SMTP settings");
            }
          
          }//end of loop
      }//end of of if-else

   if($cnt_sms>0 && $mobile_array[0])
    {  
     /*if($status_sms)
          add_confirmation("sms sent successfully");    
      else
          add_error("Error in sending sms,make sure kannel is up running");*/
     foreach ($status_sms as $key => $value)
          {
            if($value="1")
            {
             add_confirmation("sms sent successfully to ".$key);
            }
            else
            {
            add_error("Error in sending sms to ".$key.",reconfigure your kannel settings");
            }
          
          }//end of loop
    } 
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
