<?php
/**
* The Sahana Messaging Module Send Console
*
* PHP version 5
*
*
* @author		J P Fonseka <hevayo@respere.com>
* @author 		Pradeeper <pradeeper@respere.com>
* @copyright    Respere - http://respere.com/
* @package		Sahana - http://sahana.lk/
* @subpackage   msg
* @tutorial
* @version		$Id: handler_survey.inc,v 1.3 2009-08-22 17:17:22 ravithb Exp $
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

global $global;
include_once ('lib_receive_console.inc');

echo "<h2>"._t('Send Console')."</h2>";

//send console form
shn_form_fopen('send_message',null,array('req'=>false));
shn_form_fsopen(_t('Send Message'));
//shn_form_text('From','from');
?>
<br />
<script type="text/javascript" src="res/js/context-menu.js"></script> 
<script type="text/javascript" src="res/js/folder-tree-static.js"></script>
<div  style="width:260px;height:430px;float:left;">
<span style="font-weight:bold; color:#555;">Contacts</span>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<a href="#" onclick="expandAll('dhtmlgoodies_tree');return false">Expand all</a> |
<a href="#" onclick="collapseAll('dhtmlgoodies_tree');return false">Collapse all</a>
<div id="contact_holder" style="overflow:auto;width:260px;height:380px;border:1px solid #ccc;">
<ul id="dhtmlgoodies_tree" class="dhtmlgoodies_tree">
  <li><a href="#">Sahana Contacts</a>
    <ul>
        <li><a href="#" onclick="msg_add_number('<all:groups>')">Groups</a>
            <ul>
      <?php
                $sql="select m_uuid, grp_name , grp_type_desc from msg_people_group";
                $res=$global['db']->Execute($sql);
                foreach($res as $cont){
                    $c="{".$cont['m_uuid'].":".$cont['grp_name'].":".$cont['grp_type_desc']."}";
                    echo "<li><a href=\"#\" onclick=\"msg_add_number('$c')\">{$cont['grp_name']}</a></li>";
                }
      ?>
            </ul>
        </li>
<!--        <ul>
          <li><a href="#">Group1</a>
            <ul>
              <li class="dhtmlgoodies_sheet.gif"><a href="#" onclick="msg_add_number('077412321')">077412321</a></li>  
              <li class="dhtmlgoodies_sheet.gif"><a href="#" onclick="msg_add_number()">Sub menu item</a></li>  
              <li class="dhtmlgoodies_sheet.gif"><a href="#">Sub menu item</a></li>  
              <li class="dhtmlgoodies_sheet.gif"><a href="#">Sub menu item</a></li>
            </ul>
          </li>
        </ul>-->
      </li>
      <?php
                $sql="select group_name,mobile from messaging_group";
                $res=$global['db']->Execute($sql);
            if($res&&$res->RecordCount()>0){
                foreach($res as $cont)$all.=$cont['mobile']." , ";
                echo "<li><a href='#' onclick='msg_add_number( \"$all\")'>Adhoc Groups</a>";
                echo '<ul>';
                foreach($res as $cont)
                    echo "<li class='dhtmlgoodies_sheet.gif'><a href='#' onclick='msg_add_number( \"{$cont['mobile']}\")'>{$cont['group_name']}</a></li>";
                echo '</ul>';
            }
          ?>
      </li>
    <?php
        $sql="select name , primary_mobile from msg_people_contact";
        $res=$global['db']->Execute($sql);
        foreach($res as $cont)
            echo "<li class='dhtmlgoodies_sheet.gif'><a href='#' onclick='msg_add_number(\" {$cont['primary_mobile']} \")'>{$cont['name']}</a></li>";
    ?>
    </ul>
  </li>
</ul>
	<script type="text/javascript">

var idOfFolderTrees = ['dhtmlgoodies_tree']; 
var imageFolder = 'res/img/'; // Path to images
var folderImage = 'dhtmlgoodies_folder.gif'; // Default folder image
var plusImage = 'dhtmlgoodies_plus.gif'; // [+] icon
var minusImage = 'dhtmlgoodies_minus.gif'; // [-] icon
	</script>
</div>
</div>
<?php

shn_form_textarea('To','to');

/*
//fetch the stored message list
$sql="select m_uuid , message_header from msg_stored_messages;";
$res=$global['db']->Execute($sql);
$stmsg['']="";
foreach($res as $message)
    $stmsg[$message[0]]=$message[1];

shn_form_select($stmsg,'Stored Messages','stmsg','onchange="msg_set_message(this)"');

$sql="select m_uuid , message_header from msg_tpl_messages;";
$res=$global['db']->Execute($sql);
$temsg['']="";
foreach($res as $message)
    $temsg[$message[0]]=$message[1];

shn_form_select($temsg,'Template Messages','temsg','onchange="msg_set_message(this)"');
*/
//the message interface should change depending on the selected message type
?>
<br />
    <div style="margin-left:120px;float:left;">
    <div id="message_container">
        <textarea name="message" id="message" cols="18" rows="13" tabindex="5" onclick="remove_help()" onkeyup="limit_message();" wrap="hard" >Click here to type your message..</textarea>
    </div>
    </div>
<script language="javascript">
    function msg_set_message(msg){
        if(msg.value==''){
            document.getElementById('message_container').innerHTML="<textarea name='message' id='message' cols='18' rows='13' tabindex='5' onclick='remove_help()' onkeyup='limit_message();' wrap='hard' >Click here to type your message..</textarea>"
        }
        else if(msg.id=='stmsg'){
            xajax__shn_msg_stored_message(msg.value);
            document.getElementById('temsg').value='';
        }
        else if(msg.id=='temsg'){
            xajax__shn_msg_tpl_message(msg.value);
            document.getElementById('stmsg').value='';
        }
    }

    function limit_message(){
        var msg=document.getElementById('message');
        if(msg.value.length > 160){
            alert("The message should be bellow 160 Characters");
            msg.value=msg.value.substring(0,160);
        }
    }

    function remove_help(){
        var msg=document.getElementById('message');
        if(msg.value == 'Click here to type your message..'){
            msg.value="";
        }
    }

    function msg_add_number(number){
        var to=document.getElementById('to');
        if(to.value.match(number)==null){
            if(to.value=='')
                to.value= number;
            else
                to.value=to.value + " , " + number;
        }
        else
            alert("The Contact is already added.");
    }
</script>
<?php
$global['xajax']->printJavascript("res/js"); 
shn_form_fsclose();
shn_form_submit('Send Message');
shn_form_fclose();
