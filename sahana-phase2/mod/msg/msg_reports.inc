<?php
/**
*
* Reporting section for messages
* 
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Mifan Careem <mifan@respere.com>
* @author     J P Fonseka <jo@respere.com>
* @copyright  Respere - http://respere.com/
* @package	  Sahana - http://sahana.lk/
* @subpackage msg
* @version 	  $Id: msg_reports.inc,v 1.4 2009-08-22 17:17:22 ravithb Exp $
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

include_once $global['approot']."/inc/lib_paging.inc";


function shn_msg_basic_sent_report()
{
	
	global $global;
    $db=$global['db'];
?>
    <h1><?php echo _t("Sent Messages")?></h1>
<?php
	$query = "select * from msg_sent_messages as msm,msg_message as mm " .
			" where msm.msg_uuid=mm.msg_uuid order by message_sent_time desc";
	
	//@todo: enable paging here
	$res = $db->Execute($query);
?>
<div id ="result">
   <table>
        <thead>
            <td><?php echo _t("Recipient")?></td>
            <td><?php echo _t("Sent Time")?></td>
            <td><?php echo _t("Sender")?></td>
            <td><?php echo _t("Message")?></td>
        </thead>
        <tbody>
<?php    
	while(!$res->EOF){
?>
		 <tr>
			<td><?php echo $res->fields['recipient_number'];?></td>
			<td><?php echo $res->fields['message_sent_time'];?></td>
			<td><?php echo $res->fields['sender_id'];?></td>
			<td><?php echo $res->fields['message_content'];?></td>
		 </tr>
<?php
		$res->MoveNext();
	}
?>
		</tbody>
	</table>
<?php
}



function shn_msg_basic_rcvd_report()
{
?>
    <h1><?php echo _t("Received Messages")?></h1>
<?php
    global $global;

    $datefn = $global['db']->SQLDate('Y-m-d','received');
    $timefn = $global['db']->SQLDate('H:i:s','received');
    $sql="SELECT $datefn AS date, $timefn AS time, p.full_name AS name, m.message, m.sender  FROM msg_received_messages as m LEFT JOIN msg_people_contact as p ON (p.primary_mobile = m.sender OR p.secondary_mobile = m.sender) ";
    //if a search values is set modify the sql
    if(isset($_POST['submit'])&&$_POST['submit']=='Filter'){
        $sql .= " WHERE ( ";
        if(!$_POST['sender']==''){
            $sql.=" p.full_name LIKE '%{$_POST['search']}%' AND";
        }
        if(!$_POST['number']==''){
            $sql.=" m.sender LIKE '%{$_POST['number']}%' AND";
        }
        if(!$_POST['message']==''){
            $sql.=" m.message LIKE '%{$_POST['message']}%' AND";
        }
        if(!$_POST['date']==''){
            $sql.=" m.received like '{$_POST['date']}%' AND";
        }
        //dumy condition
            $sql.=" 1=1 )";
    }

    shn_form_fopen('rcvd_rpt','',array('req_message'=>false,'id'=>'search'));
    shn_form_fsopen("Filter Messages");
    shn_form_text('Sender','sender','');
    shn_form_text('Number','number','');
    shn_form_date('Date','date');
    shn_form_text('Message','message','');
    shn_form_fsclose();
    shn_form_submit('Filter','name="submit"');
    shn_form_submit('Show all messages','name="submit"');
    shn_form_fclose();
    //add the limit and the order
    $sql.= "ORDER BY m.received DESC";

 
    $result_set=shn_paging_get_report($sql,2,null,array("post"=>true,"return"=>true));
//    $req=$global['db']->Execute($sql);
?>
    <div id='result'>
    <table>
        <thead>
            <tr>
            <td><?php echo _t('Sender') ?></td>	
            <td><?php echo _t('Number') ?></td>	
            <td><?php echo _t('Date') ?></td>	
            <td><?php echo _t('Time') ?></td>	
            <td><?php echo _t('Message') ?></td>
            </tr>
        </thead>
        <tbody>
<?php
    foreach($result_set as $message){
?>
    <tr>
            <td><?php echo (isset($message['name']))?$message['name']:'<span style="color:#777">'._t('Anonymous...').'</span>'; ?></td>
            <td><?php echo $message['sender'] ?></td>
            <td><?php echo $message['date'] ?></td>
            <td><?php echo $message['time'] ?></td>
            <td><?php echo $message['message'] ?></td>
    </tr>
<?php
    }
?>
        </tbody>
    </table>
    </div>
<?php
}
