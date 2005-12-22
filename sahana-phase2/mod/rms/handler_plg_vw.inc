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



    global $global;
    
    shn_form_fopen("vw_plg",null);

    shn_form_fsopen('Pledge ID');
    shn_form_hidden(array('seq'=>'view'));
    shn_form_text('Pledge ID','plg_id','size="15"');
    shn_form_fsclose();
    shn_form_submit('Search');
    shn_form_fclose();
    
    if ($_POST['seq'] == 'view')
    {
        $plg_id = $_POST['plg_id'];
        
        $sql = "SELECT * FROM rms_pledge WHERE plg_id=$plg_id";    
        $rs_r = $global['db']->Execute($sql);
        
        if (1 > $rs_r->RecordCount())
        {
            print "not a valid Pledge id";
        }
        else
        {
            $recordSet = $rs_r;
?>
  
         <div id ="result">
        <table>
        <thead>
            <td><?php print _("Pledge ID") ?></td>
            <td><?php print _("Date/Time") ?></td>
            <td width=""><?php print _("Donor Name") ?></td>
            <td width=""><?php print _("Category") ?></td>
            <td width=""><?php print _("Item") ?></td>
            <td width=""><?php print _("Status") ?></td>
            <td><?php print _("View") ?></td>
        </thead>
        <tbody>
<?php 
        while (!$recordSet->EOF)
        {   
?>
    
        <tr>
        <td><?php print  $recordSet->fields['plg_id'] ?></td>
        <td><?php print  $recordSet->fields['date'] ?></td>
        <td><?php print  get_donor_name($recordSet->fields['user_id']) ?></td>
        <td><?php print  get_plg_category($recordSet->fields['plg_id']) ?></td>
        <td><?php print  $recordSet->fields['item']; ?></td>
        <td><?php print  $recordSet->fields['status'] ?></td>
        <td><a href="index.php?mod=rms&amp;act=vw_plg&amp;seq=view&amp;plg_id=<?php print $recordSet->fields['plg_id'] ?>">View</a></td>
        </tr>
<?php
            $recordSet->MoveNext();
        }
?>
      </tbody>
  </table>
  </div>
<?php
        }
}

if ($_GET['seq'] == 'view')
{
    global $global;
    $id = $_REQUEST['plg_id'];
    
    $sql =  "SELECT p.plg_id AS plg_id,p.date AS date, p.cat_id AS cat_id, p.item AS item, p.units AS units, p.quantity AS quantity, p.status AS status, p.user_id AS uid, d.name AS name, d.contact AS contact, d.comments AS comments FROM rms_pledge p, rms_req_donor d WHERE p.plg_id=$id AND p.user_id=d.req_donor_id";
    
    $rs = $global['db']->Execute($sql);
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
<tr><td><?=_("Units"); ?></td><td><?=$rs['units']?></td></tr>
<tr><td><?=_("Quantity"); ?></td><td><?=$rs['quantity']?></td></tr>
<tbody>
</table>
</div>
<br/>
<?php
}
?>