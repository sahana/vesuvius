f<?php
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
    shn_form_fopen("new_plg",null);
    shn_form_fsopen('Confirmation');
    
?>

<h4><?=_("Please Confirm the information"); ?></h4>
<label><?=_("Date"); ?></label><value><?=$_POST['date']?></value>
<label><?=_("Name"); ?></label><value><?=$_POST['name']?></value>
<label><?=_("Contact"); ?></label><value><?=$_POST['contact']?></value>
<label><?=_("Address"); ?></label><value><?=$_POST['address']?></value>
<label><?=_("Comments"); ?></label><value><?=$_POST['comments']?></value>
<label><?=_("Category"); ?></label><value><?=get_category_name($_POST['cat_id'])?></value>
<label><?=_("Item"); ?></label><value><?=$_POST['item']?></value>
<label><?=_("Units"); ?></label><value><?=$_POST['units']?></value>
<label><?=_("Quantity"); ?></label><value><?=$_POST['quantity']?></value>
<br>
<h4>If the information is correct please press 'Finish'. 
If you need to change some details please <a href="javascript:;" onClick="history.back();">click here</a> to go back.</h4>
<?php
    
    shn_form_hidden($_POST);
    shn_form_hidden(array('seq'=>'add'));    
    shn_form_fsclose();
    shn_form_submit('Finish');
    shn_form_fclose();   
    print_r($_POST);
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
    else
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
        }
        
        print "Pledge added";
    }
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
elseif ($_GET['seq'] == 'newusr')
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
    _shn_rms_get_usrid();
}

function _shn_rms_get_usrid()
{
?>
If you have a user id please enter it bellow and enter, If you are a new Donor please <a href="index.php?mod=rms&amp;act=new_plg&amp;seq=newusr">enter here</a>.
<?php
    $today = date("Y-m-d");
    
    shn_form_fopen("new_plg",null);
    
    shn_form_hidden(array('seq'=>'addplg'));
    
    shn_form_fsopen('User ID');
    shn_form_text('User_ID','id');
    shn_form_fsclose();
    shn_form_submit('Enter');
    shn_form_fclose();
}
?>

