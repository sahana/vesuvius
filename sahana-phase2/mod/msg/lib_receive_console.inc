<?php
/**
* Library containing functions used in receive console
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* Sahana - http://sahana.sourceforge.net
* 
* @author   	J P Fonseka <jo@respere.com>
* @copyright  	Respere - http://respere.com/
* @version 		$Id: lib_receive_console.inc,v 1.5 2009-08-22 17:17:22 ravithb Exp $
* @package 		Sahana - http://sahana.lk/
* @subpackage 	messaging   
* @license   	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


    global $global;
    include_once $global['approot']."/3rd/xajax/xajax.inc.php";
    $global['xajax']= new xajax('index.php?mod=msg&act=receive_popup&stream=text');
    $global['xajax']->registerFunction('_shn_msg_message_list');
    $global['xajax']->registerFunction('_shn_msg_message');
    $global['xajax']->registerFunction('_shn_msg_stored_message');
    $global['xajax']->registerFunction('_shn_msg_tpl_message');
    $global['xajax']->processRequests();

function _shn_msg_popup_page(){
    ?>
    <html>
        <head>
            <meta/>
            <title>Sahana | Message Recive Console</title>
            <style>
                html, body{ margin: 0; padding: 0; font: 100%/125% Arial, Helvetica, sans-serif; }
                body { font-size: 0.8em;}
                table { border-collapse: collapse; }
                thead th { text-align:center; padding:.25em; font-size: 0.8em; }
                td { padding:5px 5px 0 5px; border:1px solid #ccc; font-size: 0.8em;}
            </style>
        </head>
        <body style="padding:0px;">
            <?php
                _shn_msg_popup_div();
            ?>
        </body>
    </html>
    <?php
}


function _shn_msg_popup_div(){
    global $global;
    global $conf;
    ?>
        <div id="console_holder">
            <div id="receive_console" style="border:10px solid #D6EDFF;width:750px;height:420px;overflow : auto;border-top:0px; " >
            <div id="rc_heading" style="padding:5px; font-weight:bold;background:#D6EDFF;"><?php echo _t('New Messages')?></div>
                <table border="0" cellpadding="0" cellspacing="0" >
                    <thead>
                        <tr>
                        <th width="427px"><?php echo _t('Sender')?></th>
                        <th width="125px"><?php echo _t('Number')?></th>
                        <th width="90px"><?php echo _t('Date')?></th>
                        <th width="75px"><?php echo _t('Time')?></th>
                        </tr>
                    </thead>
                </table>
                <div id="message_list" style="width:100%;height:280px;overflow : auto; ">
                </div>
                <div id="message" style="border-top:10px solid #D6EDFF;height:70px;overflow : auto; padding-top:10px; padding:5px;"  >
                    <span></span>
                </div>
            </div>
            <?php  
                $global['xajax']->printJavascript("res/js"); 
            ?>
            <script language="javascript">
                xajax__shn_msg_message_list();
                msg_start_rc_refresh();

                var inv;
                var consoleWindow;
                var rconsole;

                function msg_stop_rc_refresh(){
                    clearInterval(inv);
                }

                function msg_start_rc_refresh(){
                    inv=setInterval("xajax__shn_msg_message_list()", <?php echo  $conf['msg_rc_refresh_rate']; ?>);
                }

                function msg_popout_rconsole(but){
                    //msg_remove_rconsole();
                    consoleWindow=window.open('index.php?mod=msg&act=receive_popup&stream=text','popup','width=770,height=430,scrollbars=no,resizable=no,toolbar=no,directories=no,location=no,menubar=no,status=no,left=0,top=0');
                    rconsole=document.getElementById('receive_console');
                    rconsole.parentNode.removeChild(rconsole);
                    but.style.display='none';
                    //document.getElementById('show_but').style.display='none';
                    //document.getElementById('hide_but').style.display='none';
                    msg_stop_rc_refresh();
                }
                
                function msg_show_rconsole(){
                    var ch=document.getElementById('console_holder');
                    ch.appendChild(rconsole);
                }
                
                var cline;
                function msg_select_line(line){
                    if(cline == null) cline=line; 
                    cline.style.background = '#FFF';
                    cline.style.color='#000';
                    line.style.background = '#777';
                    line.style.color='#FFF';
                    cline=line;
                }

                function msg_change_rc_heading(caption){
                    var ch=document.getElementById('rc_heading');
                    ch.innerHTML=caption;
                }

                function msg_click_search(){
                    var b;
                    if(consoleWindow){
                        msg_show_rconsole();
                        b=' ';
                    }
                    else
                        b=': <a onclick="msg_rc_new()">&lt; <?php echo _t('Back to New Messages') ?></a>';
                    xajax__shn_msg_message_list(xajax.getFormValues('search'));
                    msg_stop_rc_refresh();
                    msg_change_rc_heading('<?php echo _t('Search Results')?> '+b);
                    //document.getElementById('show_but').style.display='none';
                    //document.getElementById('hide_but').style.display='none';
                    document.getElementById('pop_but').style.display='none';
                }

                function msg_rc_new(){
                    msg_start_rc_refresh();
                    msg_change_rc_heading('<?php echo _t('New Messages')?>');
                    xajax__shn_msg_message_list();
                    document.getElementById('pop_but').style.display='inline';
                    document.getElementById('search').value='';
                }
            </script>
        </div>
    <?php
}

function _shn_msg_message_list($search=''){
    global $global;
    $datefn = $global['db']->SQLDate('Y-m-d','received');
    $timefn = $global['db']->SQLDate('H:i:s','received');
    $sql="SELECT $datefn AS date, $timefn AS time, p.full_name AS name, m.*  FROM msg_received_messages as m LEFT JOIN msg_people_contact as p ON (p.primary_mobile = m.sender OR p.secondary_mobile = m.sender) ";
    //if a search values is set modify the sql
    if(isset($search)){
        $sql.=" WHERE ( p.full_name LIKE '%{$search['search']}%' OR m.message LIKE '%{$search['search']}%') ";
    }

    //add the limit and the order
    $sql.= "ORDER BY m.received DESC LIMIT 100 ";
    $req=$global['db']->Execute($sql);

    $html.='<table cellpadding="0" cellspacing="0">';
    foreach($req as $msg){
        $html.="<tr onclick=\"msg_select_line(this,{$msg['id']});xajax__shn_msg_message('{$msg['id']}')\" style=\"cursor:pointer\">";
        $html.="  <td width=\"420px\">";
        $html.= (isset($msg['name']))?$msg['name']:'<span style="color:#aaa">'._t('Anonymous...').'</span>';
        $html.="</td>";
        $html.="  <td width=\"120px\" align=\"center\">{$msg['sender']}</td>";
        $html.="  <td width=\"80px\" align=\"center\">{$msg['date']}</td>";
        $html.="  <td width=\"70px\" align=\"center\">{$msg['time']}</td>";
        $html.="</tr>";
    } 
    $html.='</table>';
    $global['xajax_res']= new xajaxResponse();
    $global['xajax_res']->addAssign("message_list","innerHTML", $html);
    return $global['xajax_res']->getXML();
}

function _shn_msg_message($id){
    global $global;
    $sql="SELECT message FROM msg_received_messages where id = $id";
    $html=$global['db']->GetOne($sql);
    $global['xajax_res']= new xajaxResponse();
    $global['xajax_res']->addAssign("message","innerHTML", $html);
    return $global['xajax_res']->getXML();
}

function _shn_msg_stored_message($msgid){
    global $global;
    $global['xajax_res']= new xajaxResponse();
    $sql="select message_content from msg_stored_messages where m_uuid = '$msgid'";
    $res=$global['db']->GetOne($sql);
    if(!$res){echo 'Error deleting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";}
    $html.="<div id='message'>$res</div>";
    $global['xajax_res']->addAssign("message_container","innerHTML", $html);
    return $global['xajax_res']->getXML();
}

function _shn_msg_tpl_message($msgid){
    global $global;
    $global['xajax_res']= new xajaxResponse();
    $sql="select message_content from msg_tpl_messages where m_uuid = '$msgid'";
    $res=$global['db']->GetOne($sql);
    if(!$res){echo 'Error deleting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";}
    $html.="<textarea name='message' id='message' cols='18' rows='13' tabindex='5' onclick='remove_help()' onkeyup='limit_message();' >$res</textarea>";
    $global['xajax_res']->addAssign("message_container","innerHTML", $html);
    return $global['xajax_res']->getXML();
}
