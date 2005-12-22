<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 

/**
 * New Pledge form
 */
if ($_POST['seq'] == 'confirm')
{
    shn_form_fopen("new_plg",null,array('req_message'=>false));
    shn_form_fsopen('Confirmation');
    
?>

<h4><?=_("Please Confirm the information"); ?></h4>
<table>
<tr><td width="100"><?=_("Date"); ?></td><td width="200"><?=$_POST['date']?></td></tr>
<tr><td><?=_("Name"); ?></td><td><?=$_POST['name']?></td></tr>
<tr><td><?=_("Contact"); ?></td><td><?=$_POST['contact']?></td></tr>
<tr><td><?=_("Address"); ?></td><td><?=$_POST['address']?></td></tr>
<tr><td><?=_("Comments"); ?></td><td><?=$_POST['comments']?></td></tr>
<tr><td><?=_("Category"); ?></td><td><?=get_category_name($_POST['cat_id'])?></td></tr>
<tr><td><?=_("Item"); ?></td><td><?=$_POST['item']?></td></tr>
<tr><td><?=_("Units"); ?></td><td><?=$_POST['units']?></td></tr>
<tr><td><?=_("Quantity"); ?></td><td><?=$_POST['quantity']?></td></tr>
</table>
<br/>
<div><h4>
<?php

    if(!isset($_POST['name']) || $_POST['contact'] == '')
    {
        _shn_rms_adderror("Please enter a name");
    }
    
    if(!isset($_POST['contact']) || $_POST['contact'] == '')
    {
        _shn_rms_adderror("Please add a contact");
    }
    
    if(!isset($_POST['item']) || $_POST['item'] == '')
    {
        _shn_rms_adderror("Please add a item");
    }
    
    if(!isset($_POST['quantity']) || $_POST['quantity'] == '')
    {
        _shn_rms_adderror("Please add a quantity");
    }
    
    if(0<_shn_rms_errorcount())
    {
        _shn_rms_adderror("Please go <em>Back</em> and correct the errors");
        _shn_rms_showerrors();
        
        #more details button
        shn_form_fopen("new_plg",null,array('req_message'=>false));
        shn_form_hidden(array('seq'=>'addplg'));         
        //shn_form_hidden($_POST);   
        shn_form_submit('<--Back',"shorter");
        shn_form_fclose();
        return false;
    }

    print _("If the information is correct please press 'Finish'.");
    print _("If you need to change some details"); 
    print _("please"); 
?> <a href="javascript:;" onClick="history.back();"><?=_("click here")?></a><?=_("to go back")?>.</h4></div>
<?php
    
    $_SESSION['rms_plg_added'] = false;
    
    shn_form_hidden($_POST);
    shn_form_hidden(array('seq'=>'add'));    
    shn_form_fsclose();
    shn_form_submit('Finish');
    shn_form_fclose();   
}
elseif ($_POST['seq'] == 'add')
{
    global $global;
    $date = $_POST['date'];
    $name  = $_POST['name'];
    $contact  = $_POST['contact'];
    $location  = $_POST['location'];
    $comments  = $_POST['comments'];
    $cat_id  = $_POST['cat_id'];
    $item  = $_POST['item'];
    $units  = $_POST['units'];
    $quantity  = $_POST['quantity'];
    
    
    $sql = "INSERT INTO rms_req_donor (name, contact, comments) " .
            "VALUES ('$name', '$contact', '$comments')";
    
    if ($global['db']->Execute($sql) === false)
    {
        $msg = $global['db']->ErrorMsg();
        print $msg . "<br/>" . $sql;
        db_dbug($sql,$msg);
    }
    elseif (!$_SESSION['rms_plg_added'])
    {
        $user_id = $global['db']->Insert_ID();
        $sql = "INSERT INTO rms_pledge (date, cat_id, item, units, " .
                "quantity, user_id ) " .
               "VALUES ('$date', $cat_id, '$item', '$units', " .
                "$quantity, $user_id)";
        
        
        #print "<br/>" . $sql;
        
        if ($global['db']->Execute($sql) === false)
        {
            $msg = $global['db']->ErrorMsg();
            print $msg . "<br/>" . $sql;
            db_dbug($sql,$msg);
            $_SESSION['rms_plg_added'] = false;
        }
        $_SESSION['rms_plg_added'] = true;
        $_SESSION['rms_plg_new_id'] = $global['db']->Insert_ID();
        
        _shn_rms_plg_endadd($_SESSION['rms_plg_new_id']);
        
    }
    else 
         _shn_rms_plg_endadd($_SESSION['rms_plg_new_id']);
}
elseif ($_POST['seq'] == 'addplg')
{
    $usr_id = $_POST['id'];
    
    $user = false;
    if ($user == true)
    {
        $today = date("Y-m-d");
        
        shn_form_fopen("new_plg",null);
        
        shn_form_hidden(array('seq'=>'confirm'));
        
        shn_form_fsopen('Donor Contact Information');
        shn_form_text('Date','date',null,array('value'=>$today));
        shn_form_text('Name','name');
        shn_form_text('Contact','contact');
        shn_form_textarea('Address','address');
        shn_form_textarea('Comments','comments');
        shn_form_fsclose();
        
        shn_form_fsopen('Pledge Details');
        shn_form_select(get_rms_catlist(),"Category","cat_id");
        shn_form_textarea('Item','item');
        shn_form_text('Units','units');
        shn_form_text('Quantity','quantity');
        shn_form_fsclose();
        shn_form_submit('Add');
        shn_form_fclose();
    }    
    else
    {
        _shn_rms_adderror("some error");


        if ($_SESSION['rms_errors'] != null)
            _shn_rms_showerrors();
        
        _shn_rms_get_usrid();    
    }
}
else
{
    $today = date("Y-m-d");
    
    shn_form_fopen("new_plg",null);
    
    shn_form_hidden(array('seq'=>'confirm'));
    
    shn_form_fsopen('Donor Contact Information');
    shn_form_text('Date','date',null,array('value'=>$today));
    shn_form_text('Name','name',array('req'=>'true'));
    shn_form_text('Contact','contact',array('req'=>'true'));
    shn_form_textarea('Address','address');
    shn_form_textarea('Comments','comments');
    shn_form_fsclose();
    shn_form_fsopen('Pledge Details');
    shn_form_select(get_rms_catlist(),"Category","cat_id");
    shn_form_textarea('Item','item',array('req'=>'true'));
    shn_form_text('Units','units');
    shn_form_text('Quantity','quantity',array('req'=>'true'));
    shn_form_fsclose();
    shn_form_submit('Add');
    shn_form_fclose();
}
//else
//{
//    _shn_rms_get_usrid();
//}
//
//function _shn_rms_get_usrid()
//{
// print ('If you have a user id please enter it bellow and enter, If you are a new Donor please <a href="index.php?mod=rms&amp;act=new_plg&amp;seq=newusr">enter here</a>.')

//    $today = date("Y-m-d");
//    
//    shn_form_fopen("new_plg",null);
//    
//    shn_form_hidden(array('seq'=>'addplg'));
//    
//    shn_form_fsopen('User ID');
//    shn_form_text('User_ID','id');
//    shn_form_fsclose();
//    shn_form_submit('Enter');
//    shn_form_fclose();
//}

function _shn_rms_plg_endadd($plg_id)
{
?>
    <div class=error>
    <h3>The Pledge was successfully added</h3>
    <strong>The pledge ID : <?=$plg_id?></strong>
    </div>
<?php
}
?>

