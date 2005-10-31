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


$global['rms_db_dbug'] = false;
$global['org_id'] = '10001';
$global['person_id'] = '10002';


/**
 * debug  function
 */
function db_dbug($sql,$msg)
{
    global $global;
    if ($global['rms_db_dbug'])
        print "<br/>SQL Statement: $sql" . "<br/>Debug Message: $msg";
}

/**
 * get locations
 */
function get_loc_list($loc_type)
{
    $sql = "SELECT * FROM location WHERE opt_location_type = $loc_type";
    
    
}


function show_rms_heading()
{
?>
    <!-- RMS -->
    <h2> <?php print _("The Request Management System") ?></h2><br/>
<?php
}


function show_rms_initform()
{
    $today = date("Y-m-d");
?>
<fieldset>
    <legend><?php print _("New Request") ?></legend>
    <label><?php print _("Request Date") ?></label> <input type="text" id="req_date" value="<?php print $today ?>" name="req_date" size="40" maxlength="40"/><br/>
    <label><?php print _("Requester Name") ?></label> <input type="text" name="req_name" size="40" maxlength="40"/><br/>
    <label><?php print _("Requester Contact") ?></label> <input type="text" name="req_contact" size="40" maxlength="40"/><br/>
    <label><?php print _("Requester Address") ?></label> <textarea name="req_address" rows="5" cols="50" wrap="off"></textarea><br/>
    <label><?php print _("Site Name") ?></label> <input type="text" name="req_site_name" size="40" maxlength="40"/><br/>
    <label><?php print _("Site District") ?></label>
    <select name="req_site_district">
        <option value="023">Anuradhapura</option>
        <option value="024">Colombo</option>
        <option value="025">Gall</option>
    </select><br/>
    <label><?php print _("Site Address") ?></label> <textarea name="req_site_address" rows="5" cols="50" wrap="off"></textarea><br/>
    <label><?php print _("Comments") ?></label> <textarea name="req_comments" rows="5" cols="50" wrap="off"></textarea><br/>
</fieldset>

<?php
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
        <label id="txtarea"><?php print _("Requester Address") ?></label><value id="txtarea"><?php print $vals['req_address']?></value><br/>
        <label><?php print _("Site Name") ?></label><value><?php print $vals['req_site_name']?></value><br/>
        <label><?php print _("Site District") ?></label><value><?php print $vals['req_site_district']?></value><br/>
        <label id="txtarea"><?php print _("Site Address") ?></label><value id="txtarea"><?php print $vals['req_site_address']?></value><br/>
        <label id="txtarea"><?php print _("Comments") ?></label><value id="txtarea"><?php print $vals['req_comments']?></value><br/>
    </fieldset>
<?php
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
                <td><?php print _("Item") ?>Item</td>
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
       
?>
    <fieldset>
    <legend><?php print _("Add Items") ?></legend>
        <input type="hidden" name="req_id" value="<?php print $req_id?>">
        <label><?php print _("Category") ?></label>
        <select name="req_category">
        <?php 
            if (!$recordSet_cat->EOF)
            {
                foreach ($recordSet_cat as $rec)
                {
        ?>
                    <option value="<?php print $rec['cat_id']?>">
                        <?php print $rec['category']?>
                    </option>
        <?php
                }
            }
        ?>            
        </select><br/>    
        <label><?php print _("Item") ?></label> <textarea name="req_item" rows="5" cols="50" wrap="off"></textarea><br/>
        <label><?php print _("Units") ?></label> <input type="text" name="req_units" size="20" maxlength="20"/><br/>
        <label><?php print _("Quantity") ?></label> <input type="text" name="req_quantity" size="20" maxlength="20"/><br/>
        <label><?php print _("Priority") ?></label>
        <select name="req_priority">
        <?php 
            if (!$recordSet_pri->EOF)
            {
                foreach ($recordSet_pri as $rec)
                {
        ?>
                <option value="<?php print $rec['priority_id']?>">
                    <?php print $rec['priority']?>
                </option>
        <?php
                }
            }
        ?>
        </select><br/>
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
function show_request_list($filter,$value)
{
    global $global;
    
    if(!$filter || $filter === "all")
        $sql = "SELECT * FROM rms_request ORDER BY req_date DESC";
    else
        $sql="SELECT DISTINCT(req.req_id), req.req_date, req.name, req.site_name, req.site_district " .
                "FROM rms_request req, rms_req_item itm " .
                "WHERE itm.$filter=$value AND req.req_id=itm.req_id " .
                "ORDER BY req_date DESC;";
    
    $recordSet = $global['db']->Execute($sql);
    if ($recordSet !== false)
    {            
?>
        
<?php 
        while (!$recordSet->EOF)
        {   
?>
            <div id="sres">
            <a href="index.php?mod=rms&amp;act=vw_req&amp;seq=detail&amp;req_id=<?php print $recordSet->fields['req_id'] ?>#list">
                [<?php print $recordSet->fields['req_date'] ?>] 
                Requested by : [ <?php print $recordSet->fields['name'] ?>] for 
                <?php print $recordSet->fields['site_name'] ?> ( <?php print $recordSet->fields['site_district'] ?> : District name)
            </a>
                <br/>Item Categories: <label>
                <?php 
                    $rs = get_request_categories($recordSet->fields['req_id']);                                        
                    while (!$rs->EOF)
                    {
                ?>
                 <a href="index.php?mod=rms&amp;act=vw_req&amp;filter=cat_id&amp;value=<?php print ($rs->fields['cat_id']); ?>">
                    <?php print ($rs->fields['category']); ?>
                 </a>                        
                 <?php 
                        $rs->MoveNext();
                        
                        if(!$rs->EOF)
                            print ", ";
                    }
                ?>
                </label>
            </div><br/>
<?php
            $recordSet->MoveNext();
        }
?>
      
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



function show_ffitems_table($modify_on)
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
            "AND ff.req_item_id=req.req_item_id " .
            "AND ff.user_id=$user_id";
    
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
            "WHERE req.req_id=$req_id " .
            "AND req_item_id NOT IN ($list)";
               
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
                <td><?php print _("Item") ?>Item</td>
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
                <value id="big">
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
        if (!$rs_ff->EOF)
        {
?>
        <br/>
        <fieldset>
        <legend><?php print _("Newly Added") ?></legend>
        <table>
            <tr id="head">
                <td><?php print _("Category") ?></td>
                <td><?php print _("Item") ?>Item</td>
                <td><?php print _("Units") ?></td>
                <td><?php print _("Qty - Needed/Fulfilled (Status)") ?></td>
                <td><?php print _("Priority") ?></td>
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
    
    if (!$rs_itms->EOF)
    {
?>
    <br/>
    
    <fieldset>
    <legend><?php print _("Fulfilment information") ?></legend>
        <label><?php print _("Item") ?></label>
        <select name="ff_item">
        <?php
            
            foreach ($rs_itms as $rec)
            {
        ?>
            <option value="<?php print $rec[0]?>"><?php print $rec[1]?></option>
        <?php
            }
        ?>            
        </select><br/>
        <label><?php print _("Quantity") ?></label> 
        <input type="text" name="ff_quantity" size="20" maxlength="20"/><br/>
        <label><?php print _("Status") ?></label>
        <select name="ff_status">
            <option value="Under Consideration">Under Consideration</option>
            <option value="On Route">On Route</option>
            <option value="Delivered">Delivered</option>
            <option value="Withdrawn">Withdrawn</option> 
        </select><br/>
        <input type="submit" name="ff_add" value="Add"/> 
        </fieldset>
<?php
    }
}
?>