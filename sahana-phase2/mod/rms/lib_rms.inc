<?php
/**
* library of Common rms functions
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

$global['rms_db_dbug'] = false;

$global['person_id'] = $_SESSION['user_id'];

$_SESSION['rms_errors'] = null;

if ($global['person_id'])
    $global['org_id'] = $global['person_id'];
else
    $global['org_id'] = $_SESSION['org_id'];


function _shn_rms_search_home()
{
//    shn_form_fopen("sc_req",null,array('req_message'=>false));
//    shn_form_hidden(array('seq'=>'req_sch'));
//    shn_form_fsopen('Search Keyword');
//    shn_form_text('Enter Search Keyword','kword');
//    shn_form_fsclose();
//    shn_form_submit('Search');
//    shn_form_fclose();
?>
<form method="POST" action="index.php?mod=rms&act=sc_req">
    <input type="hidden" name="seq" value="req_sch">
    <strong><?php print _("Search for a Request") ?></strong> : 
    <input type="text" name="kword" />
    <input type="submit" value="Search"/>
</form>
<?php    
}

function _shn_rms_show_headder($sub='')
{
?>
<h2><?=_("Sahana Request Management System")?></h2>
<?php
if ($sub != '')
    print "<h3>" . _("$sub") . "</h3>";
}

/**
 * Some Simple Error Handling
 */
function _shn_rms_adderror($err_msg)
{
    $_SESSION['rms_errors'][] = $err_msg;
}

function _shn_rms_showerrors()
{
    if (!isset($_SESSION['rms_errors']))
        return false;
    $errors = $_SESSION['rms_errors'];
?>
<div id="error">
    <p><em><?php print _("Oops... the following errors were encountered")?>:</em></p>
    <ul>
<?php
    foreach ( $errors as $err )
    {
?>
    <li><?=$err?></li>
<?php
    }
?>
    </ul>
</div>    
<?php
    $_SESSION['rms_errors'] = null;
}

function _shn_rms_errorcount()
{
    return count($_SESSION['rms_errors']);
}

/**
 * debug  function
 */
function db_dbug($sql,$msg)
{
    global $global;
    if ($global['rms_db_dbug'])
        print "<br/>SQL Statement: $sql" . "<br/>Debug Message: $msg";
}

function temp_show_required()
{
    print '<strong><font color="red">**</font></strong> ';    
}

function show_frm_error($error)
{
    if($error != '')
        print "<div id='error'>[$error]</div>";
}

function is_requester($req_id,$user_id)
{
    global $global;
    $sql = "SELECT req_id,user_id " .
            "FROM rms_request " .
            "WHERE req_id=$req_id AND user_id=$user_id";
    $rs = $global['db']->Execute($sql);
    
    if (1 > $rs->RecordCount())
        return false;
    
    return true;
}

function is_a_requester($user_id)
{
    global $global;
    $sql = "SELECT req_id,user_id " .
            "FROM rms_request " .
            "WHERE user_id=$user_id";
    $rs = $global['db']->Execute($sql);
    
    if (1 > $rs->RecordCount())
        return false;
    
    return true;
}

function is_req_open($req_id)
{
    global $global;
    $sql = "SELECT req_id,status " .
            "FROM rms_request " .
            "WHERE req_id=$req_id AND status='open'";
    $rs = $global['db']->Execute($sql);
    
    if (1 > $rs->RecordCount())
        return false;
    
    return true;
}

function count_req()
{
    global $global;
    $sql = "SELECT count(req_id) FROM rms_request";
    $rs = $global['db']->Execute($sql);
    return $rs->fields[0];
}

function count_user_req($user_id)
{
    global $global;
    $sql = "SELECT count(req_id) FROM rms_request WHERE user_id=$user_id";
    $rs = $global['db']->Execute($sql);
    return $rs->fields[0];
}

function count_user_reqff($user_id)
{
    global $global;
    $sql = "SELECT COUNT(DISTINCT(req.req_id)) " .
            "FROM rms_req_ff ff, rms_req_item itm, rms_request req " .
            "WHERE itm.req_item_id=ff.req_item_id AND req.req_id=itm.req_id " .
            "AND req.user_id=$user_id";
            
    $rs = $global['db']->Execute($sql);
    return $rs->fields[0];
}

function count_user_reqstat($user_id,$stat)
{
    global $global;
    $sql = "SELECT COUNT(req_id) FROM rms_request " .
            "WHERE user_id='$user_id' AND status='$stat'";
            
    $rs = $global['db']->Execute($sql);
    return $rs->fields[0];
}

function count_org_req($org_id) //not functional yet
{
    global $global;
    $sql = "SELECT count(req_id) FROM rms_request WHERE user_id=$user_id";
    $rs = $global['db']->Execute($sql);
    return $rs->fields[0];
}

function get_district_list($name,$dist='')
{
    global $global;
    $sql = "SELECT location_id,name FROM location WHERE opt_location_type=3";
    $rs = $global['db']->Execute($sql);
    $select = "<select name='$name'>\n";
    $rs_arr = $rs->GetAll();
    
    foreach ($rs_arr as $r)
    {
        if($r[0] != $dist)
            $select .= "\t<option value=" . $r[0] . ">" . $r[1] . "</option>\n";
        else
            $select .= "\t<option selected value=" . $r[0] . ">" . $r[1] . "</option>\n";
    }
    $select .= "</select>\n";
    print $select;
}

function get_district_name($dist_id)
{
    global $global;
    $sql = "SELECT name FROM location WHERE location_id=$dist_id";
    $rs = $global['db']->Execute($sql);
    
    return $rs->fields[0];
}

function get_category_name($cat_id)
{
    global $global;
    $sql = "SELECT category FROM rms_req_category WHERE cat_id=$cat_id";
    $rs = $global['db']->Execute($sql);
    
    return $rs->fields[0];
}

function get_cat_id($cat_name)
{
    global $global;
    $sql = "SELECT cat_id FROM rms_req_category WHERE category='$cat_name'";
    $rs = $global['db']->Execute($sql);
    
    return $rs->fields[0];
}

function get_unit_name($unit_id)
{
    global $global;
    $sql = "SELECT unit FROM rms_req_units WHERE unit_id=$unit_id";
    $rs = $global['db']->Execute($sql);
    
    return $rs->fields[0];
}

function get_unit_id($unit_name)
{
    global $global;
    $sql = "SELECT unit_id FROM rms_req_units WHERE unit='$unit_name'";
    $rs = $global['db']->Execute($sql);
    
    return $rs->fields[0];
}

function get_donor_name($id)
{
    global $global;
    
    $sql = "SELECT name FROM rms_req_donor WHERE req_donor_id = $id";    
    $recordSet_cat = $global['db']->Execute($sql);
    
    $rec = $recordSet_cat->getArray(); 
    return $rec[0][0];
}

function get_plg_category($id)
{
    global $global;
    
    $sql = "SELECT category FROM rms_req_category WHERE cat_id = $id";    
    $recordSet_cat = $global['db']->Execute($sql);
    
    $rec = $recordSet_cat->getArray(); 
    return $rec[0][0];
}

function show_rms_categories($value)
{
    global $global;
    $sql = "SELECT cat_id,category FROM  rms_req_category";
    $rs = $global['db']->Execute($sql);
    
    if (isset($_GET['stat']))
        $stat = $_GET['stat'];
    else
        $stat = open;
        
    $url = "index.php?mod=rms&act=vw_req&amp;user=all&amp;stat=$stat&amp;filter=cat_id";
    
    $select = "<br/><br/><div><form action='$url' name=req_fil_cat method=post>\n";
    $select .= _("Filter by Category");
    $select .= "<select name='value' onChange='submit();'>\n";
    $rs_arr = $rs->GetAll();
    foreach ($rs_arr as $r)
    {
        if($r[0] != $value)
            $select .= "\t<option value=" . $r[0] . ">" . $r[1] . "</option>\n";
        else
            $select .= "\t<option selected='selected' value=" . $r[0] . ">" . $r[1] . "</option>\n";
    }
    $select .= "</select>\n" .
               "</form>\n" .
               "</div>";
    print $select;
}

function show_rms_heading()
{
?>
    <h1> <?php print _("Request Management System") ?></h1>
<?php
}


function show_rms_initform()
{
    $today = date("Y-m-d");
    if (!$_SESSION['rms_errors'])
    {        
?>
        <fieldset>
            <legend><?php print _("New Request") ?></legend>
            <label><?php print _("Request Date") ?></label> 
            <input readonly="readonly" type="text" id="req_date" value="<?php print $today ?>" name="req_date" size="40" maxlength="40"/><br/>
            <label><?php print _("Requester Name") ?></label> 
            <input type="text" name="req_name" size="40" maxlength="40"/><?php print temp_show_required(); ?><br/>
            <label><?php print _("Requester Contact") ?></label> 
            <input type="text" name="req_contact" size="40" maxlength="40"/><?php print temp_show_required(); ?><br/>
            <label><?php print _("Requester Address") ?></label> 
            <textarea name="req_address" rows="3" cols="50" wrap="off"></textarea><br/>
            <label><?php print _("Site Name") ?></label> 
            <input type="text" name="req_site_name" size="40" maxlength="40"/><?php print temp_show_required(); ?><br/>
            <label><?php print _("Site District") ?></label>
            <?php get_district_list("req_site_district") ?><?php print temp_show_required(); ?>
            <br/>
            <label><?php print _("Site Address") ?></label> 
            <textarea name="req_site_address" rows="3" cols="50" wrap="off"></textarea><br/>
            <label><?php print _("Comments") ?></label> 
            <textarea name="req_comments" rows="3" cols="50" wrap="off"></textarea><br/>
        </fieldset>
<?php
    }
    else
    {
        $values = $_SESSION['rms_mform_values'];
        $errors = $_SESSION['rms_form_errors'];
        //print_r ($values);
?>
        <fieldset>
            <legend><?php print _("New Request") ?></legend>
            <label><?php print _("Request Date") ?></label> 
            <input readonly="readonly" type="text" id="req_date" value="<?php print $today ?>" name="req_date" size="40" maxlength="40"/><br/>
            
            <label><?php print _("Requester Name") ?></label> 
            <input type="text" name="req_name" value="<?php print $values['req_name'] ?>" size="40" maxlength="40"/>
            <?php print temp_show_required(); ?> <?php show_frm_error($errors['req_name']) ?><br/>
            
            <label><?php print _("Requester Contact") ?></label> 
            <input type="text" name="req_contact" value="<?php print $values['req_contact'] ?>" size="40" maxlength="40"/>
            <?php print temp_show_required(); ?> <?php show_frm_error($errors['req_contact']) ?><br/>
            
            <label><?php print _("Requester Address") ?></label> 
            <textarea name="req_address" rows="3" cols="50" wrap="off"><?php print $values['req_address'] ?></textarea> <?php show_frm_error($errors['req_address']) ?><br/>
            
            <label><?php print _("Site Name") ?></label> 
            <input type="text" name="req_site_name" value="<?php print $values['req_site_name'] ?>" size="40" maxlength="40"/>
            <?php print temp_show_required(); ?> <?php show_frm_error($errors['req_site_name']) ?><br/>
            
            <label><?php print _("Site District") ?></label>
            <?php get_district_list("req_site_district",$values['req_site_district']) ?>
            <?php print temp_show_required() ?>  <?php show_frm_error($errors['req_site_district']) ?>
            <br/>
            
            <label><?php print _("Site Address") ?></label> 
            <textarea name="req_site_address" rows="3" cols="50" wrap="off"><?php print $values['req_site_address'] ?></textarea> 
             <?php show_frm_error($errors['req_site_address']) ?><br/>
            
            <label><?php print _("Comments") ?></label> 
            <textarea name="req_comments" rows="3" cols="50" wrap="off"><?php print $values['req_comments'] ?></textarea> <?php show_frm_error($errors['req_comments']) ?><br/>
        </fieldset>
<?php
    }
}

function clean_frm_val(&$val)
{
    $val = trim($val);
}

function rms_validate_mform($mode=0)
{
    $_SESSION['rms_errors'] = false;
    $vals = $_SESSION['rms_mform_values'] = rms_get_initvals();
    
    array_walk($vals, 'clean_frm_val');
    
    if ($mode == 1)
    {
        
        if(!isset($vals['req_date']))
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_date"]= _("Please enter a valid date");        
        }
        
        if($vals['req_name']=='')
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_name"]= _("Please enter a name"); 
        }
        
        if($vals['req_contact']=='')
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_contact"]= _("Please enter contact information");        
        }
        
    //    if($vals['req_address']=='')
    //    {
    //        $_SESSION['rms_errors'] = true;
    //    }
    
        if($vals['req_site_name']=='')
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_site_name"]= _("Please enter a valid site name");
        }
        
        if($vals['req_site_district']=='')
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_site_district"]= _("Please select a valid district");
        }
        
    //    if($vals['req_site_address']=='')
    //    {
    //        $_SESSION['rms_errors'] = true;
    //    }
    }
    
    if ($mode == 2)   //handling fulfill data
    {
        $ff_quantity = $_POST['ff_quantity'];
        $_SESSION['rms_donor_name'] = $_POST['ff_d_name'];
        $_SESSION['rms_donor_contact'] = $_POST['ff_d_contact'];
        $_SESSION['rms_donor_comments'] = $_POST['ff_d_comments'];
        //$_SESSION['rms_ff_quantity'] = $ff_quantity;
                
        if(!is_numeric($ff_quantity))
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["ff_quantity"]= _("The Quantity has to be a numeric value");
        }
    }
    else
    {
        //Item info
        $req_category = $_POST['req_category'];
        $req_item = $_POST['req_item'];
        $req_units = $_POST['req_units'];
        $req_quantity = $_POST['req_quantity'];
        $req_priority = $_POST['req_priority'];
        
        $item_vlas = array("req_category"=>$req_category,
                           "req_item"=>$req_item,
                           "req_units"=>$req_units,
                           "req_quantity"=>$req_quantity,
                           "req_priority"=>$req_priority
                           );
        
        array_walk($item_vlas,'clean_frm_val');
        
        if($req_category=='')
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_category"]= _("Please select a valid category");
        }
        
        if($req_item=='')
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_item"]= _("Please enter a valid item");
        }
        
    //    if($req_units=='')
    //    {
    //        $_SESSION['rms_errors'] = true;
    //        $err_msgs["req_units"]= "Please enter a valid units";
    //    }
        
        if($req_quantity=='')
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_quantity"]= _("Please enter a valid quantity");
        }
        
        if(!is_numeric($req_quantity))
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_quantity"]= _("The Quantity has to be a numeric value");
        }
        
        if($req_priority=='')
        {
            $_SESSION['rms_errors'] = true;
            $err_msgs["req_priority"]= _("Please select a valid priority");
        }
    }
    
    $_SESSION['rms_iform_values'] = $item_vlas;
        
    $_SESSION['rms_form_errors'] = $err_msgs;
    
    return !$_SESSION['rms_errors'];
}

/**
 * Fetch the initial request values 
 * from POST Data or the DB.
 */ 
function rms_get_initvals()
{
    global $global;
    $rms_init_vals[]='';
    
    if ($_GET['stat'] == 'add')
    {
        $rms_init_vals['req_date'] = $_POST['req_date'];
        $rms_init_vals['req_name'] = $_POST['req_name'];
        $rms_init_vals['req_contact'] = $_POST['req_contact'];
        $rms_init_vals['req_address'] = $_POST['req_address'];
        $rms_init_vals['req_site_name'] = $_POST['req_site_name'];
        $rms_init_vals['req_site_district'] = $_POST['req_site_district'];
        $rms_init_vals['req_site_address'] = $_POST['req_site_address'];
        $rms_init_vals['req_comments'] = $_POST['req_comments'];
    } 
    else
    {
        $req_id = $_REQUEST['req_id'];
        $sql = "SELECT * FROM rms_request WHERE req_id=$req_id";
        
        $recordSet = $global['db']->Execute($sql);
        if ($recordSet === false)
        {
            $msg = $global['db']->ErrorMsg();
            db_dbug($sql,$msg);
        }
        db_dbug($sql,$msg);
        
        $rms_init_vals['req_date'] = $recordSet->fields[1];
        $rms_init_vals['req_name'] = $recordSet->fields[2];
        $rms_init_vals['req_contact'] = $recordSet->fields[3];
        $rms_init_vals['req_address'] = $recordSet->fields[4];
        $rms_init_vals['req_site_name'] = $recordSet->fields[5];
        $rms_init_vals['req_site_district'] = $recordSet->fields[6];
        $rms_init_vals['req_site_address'] = $recordSet->fields[7];
        $rms_init_vals['req_comments'] = $recordSet->fields[8];
        $rms_init_vals['user_id'] = $recordSet->fields[10];
        
        $recordSet->Close();
    }
    return $rms_init_vals;
}


/**
 * Display the initial request information
 */ 
function show_init_vals($legend)
{
    $vals = rms_get_initvals();
?>
    <fieldset>
    <legend><?php print $legend ?></legend>
        <label><?php print _("Request Date") ?></label><value><?php print $vals['req_date']?></value><br/>
        <label><?php print _("Requester Name") ?></label><value><?php print $vals['req_name']?></value><br/>
        <label><?php print _("Requester Contact") ?></label><value><?php print $vals['req_contact']?></value><br/>
        <label id="txtarea"><?php print _("Requester Address") ?></label><value id="txtarea"><?php print nl2br($vals['req_address'])?></value><br/>
        <label><?php print _("Site Name") ?></label><value><?php print $vals['req_site_name']?></value><br/>
        <label><?php print _("Site District") ?></label><value><?php print get_district_name($vals['req_site_district']);?></value><br/>
        <label id="txtarea"><?php print _("Site Address") ?></label><value id="txtarea"><?php print nl2br($vals['req_site_address'])?></value><br/>
        <label id="txtarea"><?php print _("Comments") ?></label><value id="txtarea"><?php print nl2br($vals['req_comments'])?></value><br/>
    </fieldset>
<?php
    return $vals['user_id'];
}


/**
 * Show the list of items added
 */
function show_items_table($req_id, $remove_on)
{
    if(!$req_id)
        $req_id = $_REQUEST['req_id'];
    global $global;
        
    $sql = "SELECT req.req_item_id,cat.category,req.item,req.units,req.quantity,pri.priority " .
            "FROM rms_req_category cat, rms_req_priority pri, rms_req_item req " .
            "WHERE req.req_id=$req_id AND pri.priority_id=req.priority_id " .
            "AND cat.cat_id=req.cat_id";
    
    $recordSet = $global['db']->Execute($sql);
    if ($recordSet === false)
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    }

    if (!$recordSet->EOF)
    {
        $global['items'] = true;
?>
        <fieldset>
        <legend><?php print _("Items") ?></legend>
        <table>
            <tr id="head">
                <td><?php print _("Category") ?></td>
                <td><?php print _("Item") ?></td>
                <td><?php print _("Units") ?></td>
                <td><?php print _("Quantity") ?></td>
                <td><?php print _("Priority") ?></td>
                <?php if($remove_on) {?>
                    <td>&nbsp;</td>
                <?php } ?>
            </tr>
<?php 
        while (!$recordSet->EOF)
        {   
?>
            <tr>
                <td>
                <value id="big"><?php print $recordSet->fields[1] ?></value>
                </td>
                <td>
                <value id="big"><?php print $recordSet->fields[2] ?></value>
                </td>
                <td>
                <value id="small"><?php print $recordSet->fields[3] ?></value>
                </td>
                <td>
                <value id="small"><?php print $recordSet->fields[4] ?></value>
                </td>
                <td>
                <value id="big"><?php print $recordSet->fields[5] ?></value>
                </td>
                <?php if($remove_on) {?>                
                <td>                
                <a id="table" href="index.php?mod=rms&amp;act=new_req&amp;stat=more_itms&amp;remove_item=<?php print $recordSet->fields['0'] ?>&amp;req_id=<?php print $req_id?>#items_form">remove</a>
                </td>
                <?php } ?>                
            </tr>    
<?php
            $recordSet->MoveNext();
        }
?>
        </table>
        </fieldset>
<?php
    }
    $recordSet->Close();
?>
<?php
}

/**
 * Show add items form
 */
function show_item_fields($req_id)
{
    global $global;
    
    $sql = "SELECT cat_id,category FROM rms_req_category";    
    $recordSet_cat = $global['db']->Execute($sql);
    
    $sql = "SELECT priority_id,priority FROM rms_req_priority";    
    $recordSet_pri = $global['db']->Execute($sql);
    
    if ($recordSet_cat !== false && $recordSet_pri !== false)
    {
        $ivalues = $_SESSION['rms_iform_values'];
        $errors = $_SESSION['rms_form_errors'];
        unset($_SESSION['rms_iform_values']);
        $_SESSION['rms_form_errors'] ='';
       
?>
    <fieldset>
    <legend><?php print _("Add Items") ?></legend>
        <input type="hidden" name="req_id" value="<?php print $req_id?>">
        <label><?php print _("Category") ?></label>
        <select name="req_category">
        <?php 
            if (!$recordSet_cat->EOF)
            {
                $rs_arr_cat = $recordSet_cat->GetAll();
                foreach ($rs_arr_cat as $rec)
                {
                    if ($rec['cat_id'] != $ivalues['req_category'])
                    {
        ?>
                    <option value="<?php print $rec['cat_id']?>">
                        <?php print $rec['category']?>
                    </option>
        <?php
                    }
                    else
                    {
        ?>
                    <option selected="selected" value="<?php print $rec['cat_id']?>">
                        <?php print $rec['category']?>
                    </option>
        <?php
                    }
                }
            }
        ?>            
        </select><?php print temp_show_required(); ?><?php show_frm_error($errors['req_category']) ?><br/>    
        <label><?php print _("Item") ?></label> 
        <textarea name="req_item" rows="3" cols="50" wrap="off"><?php print $ivalues['req_item']?></textarea><?php print temp_show_required(); ?>
        <?php show_frm_error($errors['req_item']) ?><br/>
        <label><?php print _("Units") ?></label> 
        <input type="text" value="<?php print $ivalues['req_units']?>" name="req_units" size="20" maxlength="20"/><br/>
        <label><?php print _("Quantity") ?></label> 
        <input type="text" name="req_quantity" value="<?php print $ivalues['req_quantity']?>" size="20" maxlength="20"/><?php print temp_show_required(); ?>
        <?php show_frm_error($errors['req_quantity']) ?><br/>
        <label><?php print _("Priority") ?></label>
        <select name="req_priority">
        <?php 
            if (!$recordSet_pri->EOF)
            {
                $rs_arr_pri = $recordSet_pri->GetAll();
                foreach ($rs_arr_pri as $rec)
                {
                    if ($rec['priority_id'] != $ivalues['priority_id'])
                    {
        ?>
                    <option value="<?php print $rec['priority_id']?>">
                        <?php print $rec['priority']?>
                    </option>
        <?php
                    }
                    else
                    {
        ?>
                    <option selected="selected" value="<?php print $rec['priority_id']?>">
                        <?php print $rec['priority']?>
                    </option>
        <?php
                    }
                }
            }
        ?>
        </select><?php print temp_show_required(); ?>
        <?php show_frm_error($errors['req_priority']) ?><br/>
        <input type="submit" name="req_add" value="Add"/>
    </fieldset>    
<?php
    $recordSet_cat->Close();
    $recordSet_pri->Close();
    }
    else
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,"Populate the initial tables");
    }
}


/**
 * Get list of categories for a request
 */
function get_request_categories($req_id)
{
    global $global;
    $sql = "SELECT DISTINCT(cat.cat_id), cat.category FROM rms_req_item req,rms_req_category cat " .
            "WHERE req.req_id=$req_id AND cat.cat_id=req.cat_id;";
    
    $recordSet = $global['db']->Execute($sql);
    if (!$recordSet === false)
    {
        return $recordSet;  
    }
    else
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    }    
}

/**
 * Display the list of requests
 */
function show_request_list($filter='none',$value,$user='all',$status='open')
{
    global $global;
    $user_id = $global['person_id'];
    $seq = '';
    $list_of = "All Uers";
    $filtered_by = '';
    
    if (isset($_GET['stat']))
        $status = $_GET['stat'];
    
    if (isset($_GET['user']))
        $user = $_GET['user'];
    
    $url = "index.php?mod=rms&amp;act=vw_req" .
            "&amp;user=$user&amp;stat=$status";
                    
    $where = "WHERE status='$status'";
    $where_fil = "status='$status' AND";
    
    if ($user == 'all' && $status == 'all')
    {
        $where = '';
        $where_fil = '';
    } 
    else if ($user == 'user' && $status == 'all')
    {
        $where = "WHERE user_id=$user_id";
        $where_fil = "user_id=$user_id AND";
        $list_of = "User :$user_id";
    }
    else if ($user == 'user' && $status != 'all')
    {
        $where = "WHERE user_id=$user_id AND status='$status'";
        $where_fil = "req.user_id=$user_id  AND req.status='$status' AND";
        $list_of = "User :$user_id";
    }
    
    
    if($filter == '' || $filter == 'none')
        $sql = "SELECT * FROM rms_request $where ORDER BY req_date DESC";
    else
    {
        $sql="SELECT DISTINCT(req.req_id), req.req_date, req.name, req.site_name, req.site_district " .
                "FROM rms_request req, rms_req_item itm " .
                "WHERE $where_fil itm.$filter=$value AND req.req_id=itm.req_id " .
                "ORDER BY req_date DESC;";
        
        $filtered_by = "Filtered by Category : " . get_category_name($value);
    }
    
    
    //print "<br/>" .$sql;
    $recordSet = $global['db']->Execute($sql);
    if ($recordSet !== false)
    {            
?>
   <h3><?php print _("List of") .   ucfirst($status) . _("requests for ") . $list_of . "&nbsp;" . $filtered_by?></h3>
   <div id ="result">
    <table>
        <thead>
            <td><?php print _("ID") ?></td>
            <td><?php print _("Date/Time") ?></td>
            <td width="150"><?php print _("Requester") ?></td>
            <td width="75"><?php print _("Site") ?></td>
            <td width="75"><?php print _("District") ?></td>
            <td width=""><?php print _("Categories") ?></td>
            <td><?php print _("View") ?></td>
        </thead>
        <tbody>
<?php 
        while (!$recordSet->EOF)
        {   
?>
    
        <tr>
        <td><?php print  $recordSet->fields['req_id'] ?></td>
        <td><?php print  $recordSet->fields['req_date'] ?></td>
        <td><?php print  $recordSet->fields['name'] ?></td>
        <td><?php print  $recordSet->fields['site_name'] ?></td>
        <td><?php print  get_district_name($recordSet->fields['site_district']); ?></td>
        <td>
            
        
            
                
                <?php 
                    $rs = get_request_categories($recordSet->fields['req_id']);                                        
                    while (!$rs->EOF)
                    {
                ?>
                 <a href="<?php print $url;?>&amp;filter=cat_id&amp;value=<?php print ($rs->fields['cat_id']); ?>">
                    <?php print ($rs->fields['category']); ?>
                 </a>                        
                 <?php 
                        $rs->MoveNext();
                        
                        if(!$rs->EOF)
                            print ", ";
                    }
                ?>
                </td>
                <td><a href="index.php?mod=rms&amp;act=vw_req&amp;seq=detail&amp;req_id=<?php print $recordSet->fields['req_id'] ?>#list">View</a></td>
        </tr>
<?php
            $recordSet->MoveNext();
        }
?>
      </tbody>
  </table>
  </div>
<?php
    $recordSet->Close();
    }
    else
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    }
?>
<?php
}


function show_ffitems_table($modify_on=false,$is_fulfill=true)
{
    $req_id = $_GET['req_id'];
    global $global;
    $user_id = $global['person_id'];
    
    $sql = "SELECT ff.req_ff_id, req.req_item_id, cat.category, req.item, " .
                "req.units, req.quantity,ff.quantity,pri.priority, ff.ff_status " .
            "FROM rms_req_category cat, rms_req_priority pri, rms_req_item req, " .
                "rms_req_ff ff " .
            "WHERE req.req_id=$req_id " .
            "AND pri.priority_id=req.priority_id " .
            "AND cat.cat_id=req.cat_id " .
            "AND ff.req_item_id=req.req_item_id ";
            //"AND ff.user_id=$user_id";
    
    $rs_ff = $global['db']->Execute($sql);
    $list = '';
    
    
    //db_dbug($sql,$rs_ff);
    while (!$rs_ff->EOF)
    {
        $list .=  $rs_ff->fields[1];
        
        $rs_ff->MoveNext();
        if (!$rs_ff->EOF)
            $list .= ','; 
    }
    if ($list == '')
        $list = '-1';
    
    $sql = "SELECT req.req_item_id,req.item FROM rms_req_item req " .
            "WHERE req.req_id=$req_id ";
            //"AND req_item_id NOT IN ($list)";
               
    $rs_itms = $global['db']->Execute($sql);
    
    
    $sql = "SELECT req.req_item_id,cat.category,req.item,req.units,req.quantity," .
                "pri.priority,ff.req_item_id,ff.user_id,SUM(ff.quantity),ff.ff_status " .
                "FROM rms_req_category cat, rms_req_priority pri, " .
                "rms_req_item req LEFT JOIN rms_req_ff ff ON ff.req_item_id=req.req_item_id " .
                "WHERE req.req_id=$req_id " .
                "AND pri.priority_id=req.priority_id " .
                "AND cat.cat_id=req.cat_id " .
                "GROUP BY req.item";
                
    $rs = $global['db']->Execute($sql);
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        db_dbug($sql,$msg);
    }

    if (!$rs->EOF)
    {
?>
        <fieldset>
        <legend><?php print _("Current Fulfill Status") ?></legend>
        <table>
            <tr id="head">
                <td><?php print _("Category") ?></td>
                <td><?php print _("Item") ?></td>
                <td><?php print _("Units") ?></td>
                <td><?php print _("Qty - Needed [Fulfilled]") ?></td>
                <td><?php print _("Priority") ?></td>
                <?php if($modify_on) {?>
                    <td>&nbsp;</td>
                <?php } ?>
            </tr>
<?php 
        while (!$rs->EOF)
        {   
?>
            <tr>
                <td>
                <value id="big"><?php print $rs->fields[1] ?></value>
                </td>
                <td>
                <value id="big"><?php print $rs->fields[2] ?></value>
                </td>
                <td>
                <value id="small"><?php print $rs->fields[3] ?></value>
                </td>
                <td>
                <value id="med">
                <?php print $rs->fields[4] ?> 
                [ <?php (!$rs->fields[8]?print 0:print $rs->fields[8]) ?> ]
                </value>
                </td>
                <td>
                <value id="big"><?php print $rs->fields[5] ?></value>
                </td>
                <?php if($modify_on) {?>                
                <td>&nbsp;</td>
                <?php } ?>                
            </tr>    
<?php
            $rs->MoveNext();
        }
?>
            </table>
        </fieldset>
<?php
        $rs_ff->MoveFirst();
        if ($is_fulfill && !$rs_ff->EOF)
        {
?>
        <br/>
        <fieldset>
        <legend><?php print _("Newly Added") ?></legend>
        <table>
            <tr id="head">
                <td><?php print _("Category") ?></td>
                <td><?php print _("Item") ?></td>
                <td><?php print _("Units") ?></td>
                <td><?php print _("Qty - Needed/Fulfilled (Status)") ?></td>
                <?php if($modify_on) {?>
                    <td>&nbsp;</td>
                <?php } ?>
            </tr>
<?php        
        while (!$rs_ff->EOF)
        {   
?>
            <tr>
                <td>
                <value id="big"><?php print $rs_ff->fields[2] ?></value>
                </td>
                <td>
                <value id="big"><?php print $rs_ff->fields[3] ?></value>
                </td>
                <td>
                <value id="small"><?php print $rs_ff->fields[4] ?></value>
                </td>
                <td>
                <value id="big">
                <?php print $rs_ff->fields[6] ?> ( <?php print $rs_ff->fields[8] ?> )
                </value>
                </td>
                <?php if($modify_on) {?>                
                <td>                
                <a id="table" href="index.php?mod=rms&amp;act=fulfill_req&amp;seq=ff_modify&amp;ff_item_id=<?php print $rs_ff->fields['0'] ?>&amp;req_id=<?php print $req_id?>#items_form">Modify</a>
                </td>
                <?php } ?>                
            </tr>    
<?php
            $rs_ff->MoveNext();
        }
?>
        </table>
        </fieldset>
<?php
        }
    }
    
    if ($is_fulfill && !$rs_itms->EOF)
    {
        $errors = $_SESSION['rms_form_errors'];
?>
    <br/>
    
    <fieldset>
    <legend><?php print _("Fulfilment information") ?></legend>
        <div name="new_donor">
        <label><?php print _("Donor Name") ?></label>
        <input type="text" value="<?php print $_SESSION['rms_donor_name'] ?>" name="ff_d_name" size="20" maxlength="20"/><br/>
        <label><?php print _("Donor Contact") ?></label>
        <input type="text" value="<?php print $_SESSION['rms_donor_contact'] ?>" name="ff_d_contact" size="20"maxlength="20"/><br/>
        <label>Comments</label>
        <textarea name="ff_d_comments" rows="3" cols="50" wrap="off"><?php print $_SESSION['rms_donor_comments'] ?></textarea><br/>
        </div>
        <label>Keep Donor info.</label><input type="checkbox" name="ff_same_donor" value="same_donor"><br/>
        <label><?php print _("Item") ?></label>
        <select name="ff_item">
        <?php
            $rs_arr_itms = $rs_itms->GetAll();
            foreach ($rs_arr_itms as $rec)
            {
        ?>
            <option value="<?php print $rec[0]?>"><?php print $rec[1]?></option>
        <?php
            }
        ?>            
        </select><br/>
        <label><?php print _("Quantity") ?></label> 
        <input type="text" name="ff_quantity" size="20" maxlength="20"/>
        <?php show_frm_error($errors['ff_quantity']) ?><br/>
        <label><?php print _("Status") ?></label>
        <select name="ff_status">
            <option value="Under Consideration">Under Consideration</option>
            <option selected value="On Route">On Route</option>
            <option value="Delivered">Delivered</option>
            <option value="Withdrawn">Withdrawn</option> 
        </select>
        <br/>
        <br/>
        <input type="submit" name="ff_add" value="Add Items"/> 
        </fieldset>
<?php
    }
}

function get_rms_catlist()
{
    global $global;
    
    $sql = "SELECT cat_id,category FROM rms_req_category";    
    $recordSet_cat = $global['db']->Execute($sql);
    
    $recs = $recordSet_cat->getArray(); 
    $list = array();
    foreach ($recs as $rec)
    {
        $list[$rec[0]] = $rec[1];
    }
    return $list;
}

function get_rms_itemunits()
{
    global $global;
    
    $sql = "SELECT * FROM rms_req_units";    
    $rs = $global['db']->Execute($sql);
    
    $recs = $rs->getArray(); 
    $list = array();
    foreach ($recs as $rec)
    {
        $list[$rec[0]] = sprintf("%s [%s]",$rec[1],$rec[2]);
    }
    return $list;
}

/**
 * plg stuff
 * should go to lib_plg..
 */
 
 function _shn_rms_plg_view($id)
 {
    global $global;
        
    $sql =  "SELECT p.plg_id AS plg_id,p.date AS date, p.cat_id AS cat_id, p.item AS item, p.units AS units, p.quantity AS quantity, p.status AS status, p.user_id AS uid, d.name AS name, d.contact AS contact, d.comments AS comments FROM rms_pledge p, rms_req_donor d WHERE p.plg_id=$id AND p.user_id=d.req_donor_id";
    
    $rs = $global['db']->Execute($sql);
    if($rs == null)
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
    }
    
    $rs = $rs->GetArray();
    $rs = $rs[0];
?>
<br/>
<div>
<h4><?=_("Detailed Pledge Information"); ?></h4>
</div>
<div id ="result">
<table>
<tbody>
<tr><td width="100"><?=_("Pledge ID"); ?></td><td width="200"><?=$rs['plg_id']?></td></tr>
<tr><td><?=_("Date"); ?></td><td><?=$rs['date']?></td></tr>
<tr><td><?=_("Name"); ?></td><td><?=$rs['name']?></td></tr>
<tr><td><?=_("Contact"); ?></td><td><?=$rs['contact']?></td></tr>
<tr><td><?=_("Address"); ?></td><td><?=$rs['address']?></td></tr>
<tr><td><?=_("Comments"); ?></td><td><?=$rs['comments']?></td></tr>
<tr><td><?=_("Category"); ?></td><td><?=get_category_name($rs['cat_id'])?></td></tr>
<tr><td><?=_("Item"); ?></td><td><?=$rs['item']?></td></tr>
<tr><td><?=_("Units"); ?></td><td><?=get_unit_name($rs['units']);?></td></tr>
<tr><td><?=_("Quantity"); ?></td><td><?=$rs['quantity']?></td></tr>
<tbody>
</table>
</div>
<br/>
<?php
    #change Status    
    shn_form_fopen("stat_plgs",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>''));
    shn_form_hidden(array('from'=>'view'));             
    shn_form_hidden(array('plg_id'=>$rs['plg_id']));
    shn_form_submit(_("Change Status"),"shorter");
    shn_form_fclose();
    
    #remove pledge
    _shn_rms_plg_showdelbutton($rs['plg_id']);
}

function _shn_rms_plg_showdelbutton($id)
{
    shn_form_fopen("del_plg",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'confirm'));
    shn_form_hidden(array('plg_id'=>$id));            
    shn_form_submit(_("Remove Pledge"),"short");
    shn_form_fclose();
}


/**
 * 
 */
function _shn_rms_addoption($field_name,$option_code,$option_description)
{
	$sql = "INSERT INTO field_options " .
			"VALUES('$field_name','$option_code','$option_description')";
	if ($global['db']->Execute($sql) === false)
    {
    	$msg = "Error inserting field option.<br/>" . $global['db']->ErrorMsg();
        _shn_rms_adderror($msg);
        return false;
    }
    
    return true;
}

function _shn_rms_addcategory($name,$desc="")
{
	global $global;

    $sql = "SELECT category FROM rms_req_category WHERE category='$name'";
    $rs = $global['db']->Execute($sql);
    
    if (1 > $rs->RecordCount())
    {     
        $sql = "INSERT INTO rms_req_category (category,description) VALUES('$name','$desc')";    
        $global['db']->Execute($sql);
        return $global['db']->Insert_ID();
    }
    
    return false;
}

function _shn_rms_addunit($name,$desc="")
{
	global $global;

    $sql = "SELECT unit FROM rms_req_units WHERE unit='$name'";
    $rs = $global['db']->Execute($sql);
    
    if (1 > $rs->RecordCount())
    {     
        $sql = "INSERT INTO rms_req_units (unit,description) VALUES('$name','$desc')";    
        $global['db']->Execute($sql);
        return $global['db']->Insert_ID();
    }
    
    return false;
}


/**
 * lib_rms_person
 */
function _shn_rms_donor_getname($id)
{
	$sql = "SELECT name FROM rms_req_donor";
}

?>
