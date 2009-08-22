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
* @author        Pradeeper <pradeeper@respere.com>
* @copyright     Respere - http://respere.com/
* @package       Sahana - http://sahana.lk/
* @subpackage    msg
* @tutorial
* @version       $Id: lib_contact.inc,v 1.4 2009-08-22 17:17:22 ravithb Exp $
* @license       http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*  
*/

/*
@function    Display person details
*/

function shn_msg_view_person($id)
{
    $person=_shn_msg_fetch_person_details($id);
    $name=$person['name'];
    
    shn_form_fopen("", null,array('req_message'=>false));
        shn_form_fsopen("$name's Information");
        ?>
        <table>
            <tr>
                <td>Name</td>
                <td><strong><font color=green><?print ($person['name']); ?></font></strong></td>
              </tr>
              <tr>
                <td>Full Name</td>
                <td><strong><font color=green><?print ($person['full_name']); ?></font></strong></td>
              </tr>
              <tr>
                  <td>Address</td>
                  <td><font color=green><?print $person['address']; ?></font></td>
              </tr>
              <tr>
                  <td>Primary Contact</td>
                  <td><font color=green><?print $person['primary_method']; ?></font></td>
              </tr>
              <tr>
                  <td>Primary Mobile</td>
                  <td><font color=green><?print $person['primary_mobile'] ?></font></td>
              </tr>
              <tr>
                  <td>Secondary Mobile</td>
                  <td><font color=green><?print $person['secondary_mobile'] ?></font></td>
              </tr>
              <tr>
                  <td>Primary Email</td>
                  <td><font color=green><?print $person['primary_email'] ?></font></td>
              </tr>
              <tr>
                  <td>Secondary Email</td>
                  <td><font color=green><?print $person['secondary_email'] ?></font></td>
              </tr>
              <tr>
                  <td>Date Entered</td>
                  <td><font color=silver><?print $person['added_date'] ?></font></td>
              </tr>
              
        </table><?php
        shn_form_fsclose();
    shn_form_fclose();    
}


/*
@function    This will fetch person details for shn_msg_view_person
*/
function _shn_msg_fetch_person_details($id)
{
    global $global;
    global $conf;
    $db = $global['db'];
    
    $q="select * from msg_people_contact where m_uuid='$id';";
    $res=$db->Execute($q);
    
    while (!$res->EOF){
        $person['name']="{$res->fields['name']}";
        $person['full_name']="{$res->fields['full_name']}";
        $person['address']="{$res->fields['address']}";
        $person['primary_method']="{$res->fields['primary_method']}";
        $person['primary_mobile']="{$res->fields['primary_mobile']}";
        $person['secondary_mobile']="{$res->fields['secondary_mobile']}";
        $person['primary_email']="{$res->fields['primary_email']}";
        $person['secondary_email']="{$res->fields['secondary_email']}";
        $person['added_date']="{$res->fields['added_date']}";
        
        $res->MoveNext();
    }
    
    return $person;
}


/**
* @function     This will draw a contact list drop down
* @param    id text area id where the numbers should add 
*/
function _shn_msg_contact_dropdown($name){
    global $global;
?>
<div  style="width:260px;height:430px;float:left;">
<span style="font-weight:bold; color:#555;">Contacts</span>&nbsp;
<div id="contact_holder" style="overflow:auto;width:260px;height:380px;border:1px solid #ccc;">
<script type="text/javascript">
    var djConfig = { isDebug: false };
</script>
<script type="text/javascript" src="res/js/dojo_msg/dojo.js">/*_*/</script>
<script type="text/javascript">
    dojo.require("dojo.lang.*");
    dojo.require("dojo.widget.Tree");
</script>
<script type="text/javascript">
var treeDat = {
    treeNodes: [
               <?php
               $sql="select m_uuid, grp_name , grp_type from msg_people_group";
               $res=$global['db']->Execute($sql);
               if($res&&$res->RecordCount()>0){
               ?>
                    { title:"<a onclick='msg_add_number(\"<all:groups>\")' ><strong>Groups</strong></a>",
            children:[
                            <?php
                                foreach($res as $cont){
                                        $c="{".$cont['m_uuid'].":".$cont['grp_name'].":".$cont['grp_type']."}";
                                        $list.="\n{title: \"<a onclick='msg_add_number(\\\"$c\\\")'>{$cont['grp_name']}</a>\" },";
                                }
                                rtrim($list,",");
                                echo $list;
                            ?>
            ]
            },
                <?php
                }
                $sql="select group_name,mobile from messaging_group";
                $res=$global['db']->Execute($sql);
                if($res&&$res->RecordCount()>0){
                foreach($res as $cont)$all.=$cont['mobile']." , ";
                ?>
                    { title:"<a onclick='msg_add_number(\"<?php echo $all ?>\")' ><strong>AddHoc Groups</strong></a>",
            children:[
                            <?php
                            foreach($res as $cont)
                                $alist.="\n{title: \"<a onclick='msg_add_number(\\\"{$cont['mobile']}\\\")'>{$cont['group_name']}</a>\" },";
                                rtrim($alist,",");
                                echo $alist;
                            ?>
            ]
            },
                <?php
                }
                $sql="select name , primary_mobile from msg_people_contact";
                $res=$global['db']->Execute($sql);
                if($res&&$res->RecordCount()>0){
                ?>
                    { title:"<strong>Individuals</strong>",
            children:[
                            <?php
                            foreach($res as $cont)
                                $ilist.="{title: \"<a onclick='msg_add_number(\\\"{$cont['primary_mobile']}\\\")'>{$cont['name']}</a>\" },\n";

                                rtrim($ilist,",");
                                echo $ilist;
                            ?>
            ]
            }
                <?php
                }
                ?>
    ]
};



</script>

<script type="text/javascript">
var TreeBuilder = {
    buildTreeNodes:function (dataObjs, treeParentNode){
        for(var i=0; i<dataObjs.length;i++){
            var node =  dojo.widget.createWidget("TreeNode",{
                title:dataObjs[i].title,
                expandLevel:99,
                widgetId:(((treeParentNode)?treeParentNode.widgetId:"root_")+"_"+i)
            });
            treeParentNode.addChild(node);
            treeParentNode.registerChild(node,i);
            if(dataObjs[i].children){
                this.buildTreeNodes(dataObjs[i].children, node);
            }
        }
    },
    buildTree:function (){
        var myTreeWidget = dojo.widget.createWidget("Tree",{
            widgetId:"myTreeWidget",
            DNDMode:"between",
            DNDAcceptTypes:["myTreeWidget"]
        });
        this.buildTreeNodes(treeDat.treeNodes,myTreeWidget);
        var treeContainer = document.getElementById("myWidgetContainer");
        var placeHolder = document.getElementById("treePlaceHolder");
        treeContainer.replaceChild(myTreeWidget.domNode,placeHolder);
    }
}

dojo.addOnLoad(function(){
    TreeBuilder.buildTree();
    });
</script>
<div id="myWidgetContainer"
    style="">
    <span id="treePlaceHolder"
        style="background-color:#F00; color:#FFF;">
        Loading tree widget...
    </span>

</div>
<!--
            <ul id="dhtmlgoodies_tree" class="dhtmlgoodies_tree">
                <li><a href="#">Sahana Contacts</a>
                    <ul>
                        <?php
                        $sql="select m_uuid, grp_name , grp_type from msg_people_group";
                        $res=$global['db']->Execute($sql);
                        if($res&&$res->RecordCount()>0){
                        ?>
                        <li><a href="#" onclick="msg_add_number('<all:groups>')">Groups</a>
                            <ul>
                                <?php
                                foreach($res as $cont){
                                    $c="{".$cont['m_uuid'].":".$cont['grp_name'].":".$cont['grp_type']."}";
                                    echo "<li><a href=\"#\" onclick=\"msg_add_number('$c')\">{$cont['grp_name']}</a></li>\n";
                                }
                                ?>
                            </ul>
                        </li>
                        <?php
                        }
                        $sql="select group_name,mobile from messaging_group";
                        $res=$global['db']->Execute($sql);
                        if($res&&$res->RecordCount()>0){
                            foreach($res as $cont)$all.=$cont['mobile']." , ";
                            echo "<li><a href='#' onclick='msg_add_number( \"$all\")'>Adhoc Groups</a>\n";
                            echo '<ul>';
                            foreach($res as $cont)
                                echo "<li class='dhtmlgoodies_sheet.gif'><a href='#' onclick='msg_add_number( \"{$cont['mobile']}\")'>{$cont['group_name']}</a></li>\n";
                            echo '</ul>';
                            echo "</li>";
                        }
                        $sql="select name , primary_mobile from msg_people_contact";
                        $res=$global['db']->Execute($sql);
                        if($res&&$res->RecordCount()>0)
                            foreach($res as $cont)
                                echo "<li class='dhtmlgoodies_sheet.gif'><a href='#' onclick='msg_add_number(\" {$cont['primary_mobile']} \")'>{$cont['name']}</a></li>";
                        ?>
                    </ul>
                </li>
            </ul>-->
            <script type="text/javascript">
            function msg_add_number(number){
                var to=document.getElementById('<?php echo $name; ?>');
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
    </div>
</div>
<?php
}


//got to put this function in to a appropriate place
function _shn_msg_message_ui($message=null){
//the message interface should change depending on the selected message type
?>
<div style="margin-left:210px;float:left;">
    <div id="message_container">
<?php
        if(isset($message)){
        ?>
        <textarea name="message" id="message" cols="18" rows="13" tabindex="5" onclick="remove_help()" onkeyup="limit_message();" wrap="hard" readonly="1" ><?php echo $message?></textarea>
        <?php
        }
        else{
        ?>
        <textarea name="message" id="message" cols="18" rows="13" tabindex="5" onclick="remove_help()" onkeyup="limit_message();" wrap="hard" >Click here to type your message..</textarea>
        <?php
        }
?>
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
</script>
<?php
}

