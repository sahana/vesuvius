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
* @author       J P Fonseka <jo@respere.com>
* @copyright  	Respere - http://respere.com/
* @package        sahana
* @subpackage   msg
* @tutorial
* @version        $id$
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
* @contribution    This code was developed and contributed to the project 
* by Respere Lanka (Pvt) Ltd.
*/

include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';

/*
@author        Pradeeper <pradeeper@respere.com>
@function    display the forms for survey
*/
function shn_msg_send_survey_form()
{
    Print "<h2>"._t("Send Survey Message")."</h2>";
    shn_form_fopen("contact_submit", null,array('req_message'=>true));
        shn_form_hidden(array("target"=>"send_survey"));
        shn_form_fsopen(_t("Survey Information"));
        shn_form_text(_t("Survey Name")." : ","name",null,array("req"=>true));
        shn_form_text(_t("Key")." : ","key","size='6'",array("req"=>true));
        shn_form_textarea(_t('Question'),'question');
        shn_form_fsclose();
        shn_form_fsopen(_t("Options"));
                        $options=array('2'=>'2','3'=>'3','4'=>'4','5'=>'5','6'=>'6');
                        shn_form_select($options,_t("Number of Options"), 'nopt',"onchange='msg_survey_options(this.value)'", $extra_opts = null);

//javascript function to change the number of options display on the form
?>
<script language="javascript">
    
    function msg_survey_options(number){
        var opt=document.getElementById('opt');
        var x=parseInt(number);
        if(x > 1){
            var html='';
            for(var i=1;i<=x;i++){
                html=html+"<label>" +i+") </label>";
                html=html+"<input type='text' name='opt" + i + "' id='opt" + i + "' value='' tabindex='5' />";
                html=html+"<br /><div class='brake'></div>";
            }
            opt.innerHTML=html;
        }
    }
</script>
<?php
                        //by default it should have two textboxes 
                        echo "<div id='opt'>";
                        if(isset($_POST['nopt'])){
                            $nopt=(int)$_POST['nopt'];
                             for($i=1; $i<=$nopt; $i++){
                                 shn_form_text($i.") ","opt".$i,"",array('value'=>$_POST['opt'.$i]));
                             }
                        }
                        else{
                            shn_form_text("1) ","opt1","");
                            shn_form_text("2) ","opt2","");
                        }
                        echo "</div>";
        shn_form_fsclose();
    shn_form_submit(_t("Next"), $submit_opts = null);    
    shn_form_fclose();    
}

/*
@author        Pradeeper <pradeeper@respere.com>
@author        J P Fonseka <jo@respere.com>
@function    capture the user submistion for shn_msg_send_survey_form
*/
function _shn_msg_send_survey_submistion()
{
    global $global;
    global $conf;
    $db = $global['db'];
    $survey_name=$_POST['name'];
    $key=$_POST['key'];
    $message=$_POST['question'];

    //check if the key and name are set
    if((""==$survey_name) && (""==$key)){
        add_error(_t('Please fill the required fields and resubmit again!'));
        shn_msg_send_survey_form();
        return;
    }

    //check if the key is already in the database
    $key=strtolower($key);
    $q="SELECT count(*) FROM msg_survey WHERE survey_key like '$key';";
    $res = $db->Execute($q);
    if (!$res){
        add_error(_t('Database Error: Please contact the administrator.'));
        add_error(_t('Error : ').$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n");
        shn_msg_send_survey_form();
        return;
    }
    $count=$res->FetchRow();
    $count=$count[0];
    if($count>0){
        add_error(_t('The key already exist in the database, use a different key. '));
        shn_msg_send_survey_form();
        return;
    }

    //if both are ok forword them to the next form
    $survey_msg_id=shn_create_uuid('msg');
    // store survey information
    $q="insert into msg_survey(msg_id, survey_name, survey_key, message) values ('$survey_msg_id','$survey_name','$key','$message');";
    $res = $db->Execute($q);
    //store the survey options
    if(isset($_POST['nopt'])){
        $nopt=(int)$_POST['nopt'];
        for($i=1; $i<=$nopt; $i++){
             $sql="INSERT INTO msg_survey_opt VALUES('$survey_msg_id','$i','".$_POST['opt'.$i]."');";
             $res = $db->Execute($sql);
        }
    }
        
    //If everything is Ok print the send console
    if($res){
        Print "<h2>"._t('Send Survey Message.')."</h2>";
        _shn_msg_send_survey();
    }
    else{
        add_error(_t('Database Error: Please contact the administrator.'));
        add_error(_t('Error : ').$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n");
        shn_msg_send_survey_form();
        return;
    }
}

function _shn_msg_send_survey(){
    shn_form_fopen('send_message',null,array('req'=>false));
    shn_form_fsopen(_t('Send Message'));
    //display the contact drop down
    _shn_msg_contact_dropdown('to');
    ?>
    <br />
    <?php
    shn_form_textarea(_t('To'),'to');
    $message="::Sahana Survey::\n";
    $message.="Key :{$_POST['key']} \n";
    $message.="Q : {$_POST['question']}\n";
    if(isset($_POST['nopt'])){
         $nopt=(int)$_POST['nopt'];
         for($i=1; $i<=$nopt; $i++){
              $message.=$i.") ".$_POST['opt'.$i]."\n";
         }
    }
    _shn_msg_message_ui($message);
    shn_form_fsclose();
    shn_form_submit(_t('Send Message'));
    shn_form_fclose();
}

function _shn_msg_survey_reports(){
    global $global;
    include_once $global['approot']."/inc/lib_paging.inc";
 
    //If a survey is selected print the report
    if(isset($_GET['suid'])){
        _shn_msg_survey_print_report($_GET['suid']);
        return;
    }

    //list the available surveys
    print("<h2>"._t("Survey Reports")."</h2>");
    $sql="select * from msg_survey";
    $result_set=shn_paging_get_report($sql,10,null,array("post"=>true,"return"=>true));
?>
<div id='result'>
    <table>
        <thead>
            <tr>
                <td><?php echo _t('Survey Name') ?></td>    
                <td><?php echo _t('Key') ?></td>    
                <td><?php echo _t('Message') ?></td>    
                <td><?php echo _t('Sent Time') ?></td>    
            </tr>
        </thead>
        <tbody>
<?php
    foreach($result_set as $message){
?>
            <tr>
                <td><a href="index.php?mod=msg&amp;act=survey_rpt&amp;suid=<?php echo $message['msg_id'] ?>"><?php echo $message['survey_name'] ?></a></td>
                <td><?php echo $message['survey_key'] ?></td>
                <td><?php echo $message['message'] ?></td>
                <td><?php echo $message['send_time'] ?></td>
            </tr>
<?php
    }
?>
        </tbody>
    </table>
</div>
<?php
}


function _shn_msg_survey_print_report($suid){
    global $global;
    //get survey info
    $sql="SELECT * FROM msg_survey WHERE msg_id = '$suid'";
    $rec=$global['db']->GetRow($sql);
    $key=$rec['survey_key'];
    //display the survey report of the selected survey
    print("<h2>"._t("Survey Report of :").$rec['survey_name']."</h2>");
    echo "<h3>"._t('Summery')."</h3>";
    echo "<strong>"._t('Question')." : </strong>".$rec['message']."&nbsp;&nbsp;&nbsp;";
    echo "<br />";
    echo "<strong>"._t('Key')." : </strong>".$rec['survey_key'];
    //get survey options
    $sql="SELECT opt_num , opt_val FROM msg_survey_opt WHERE msg_id LIKE '$suid'";
    $rec=$global['db']->Execute($sql);

    //get the responce received
    //first get the total responce count
        $sql="select count(*) from msg_received_messages where message like '$key %'";
        $tc=$global['db']->Execute($sql);
        $total_count=$tc->FetchRow();
        $total_count=$total_count[0];
    ?>
    <table>
        <tr>
            <td><strong><?php echo _t("Option") ?></strong></td>
            <td><strong><?php echo _t("Received Messages")?></strong></td>
            <td><strong><?php echo _t("Percentage")?></strong></td>
        </tr>
    <?php
    foreach($rec as $option){
        $sql="select count(*) from msg_received_messages where message like '$key {$option['opt_num']}' OR message like '$key {$option['opt_val']}';";
        $complement.="message not like '$key {$option['opt_num']}' AND message not like '$key {$option['opt_val']}' AND ";
        $rec=$global['db']->Execute($sql);
        ?>
        <tr>
            <td><?php echo $option['opt_num'].') '.$option['opt_val'] ?></td>
            <td><?php $count=$rec->FetchRow();$count=$count[0];echo $count; ?></td>
            <td><?php echo round(($count/$total_count*100),2)."%" ?></td>
        </tr>
        <?php
    }
    //check the invalied responces
    $sql="select count(*) from msg_received_messages where ".$complement." message like '$key %'";
    $rec=$global['db']->Execute($sql);
    $ic=$rec->FetchRow();
    $ic=$ic[0];
        ?>
        <tr>
            <td><?php echo _t('Invalid') ?></td>
            <td><?php echo " ".$ic ?></td>
            <td><?php echo round(($ic/$total_count*100),2)."%" ?></td>
        </tr>
        <?php
    echo "    </table>";
    echo "<br />";
    echo "<h3>"._t('Respond Messages')."</h3>";
    $datefn = $global['db']->SQLDate('Y-m-d','received');
    $timefn = $global['db']->SQLDate('H:i:s','received');
    $sql="SELECT $datefn AS date, $timefn AS time, p.full_name AS name, m.message, m.sender  FROM msg_received_messages as m LEFT JOIN msg_people_contact as p ON (p.primary_mobile = SUBSTRING(m.sender,4) OR p.secondary_mobile = SUBSTRING(m.sender,4)) WHERE m.message like '$key %' ORDER BY m.message";
    $result_set=shn_paging_get_report($sql,20,null,array("post"=>true,"return"=>true));
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

