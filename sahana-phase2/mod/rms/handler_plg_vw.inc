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
    
    shn_form_fopen("vw_plg",null,array('req_message'=>false));

    shn_form_fsopen('Pledge ID');
    shn_form_hidden(array('seq'=>'view1'));
    shn_form_text('Pledge ID','plg_id','size="15"');
    shn_form_fsclose();
    shn_form_submit('View');
    shn_form_fclose();
    print "<br/>";
    
    if ($_POST['seq'] == 'view1')
    {
        $plg_id = $_POST['plg_id'];
        
        $sql = "SELECT * FROM rms_pledge WHERE plg_id=$plg_id";    
        $rs_r = $global['db']->Execute($sql);
        
        if ($rs_r == null || 1 > $rs_r->RecordCount())
        {
            _shn_rms_adderror("<em>'$plg_id'</em> is not a valid pledge id");
            _shn_rms_showerrors();
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

if ($_REQUEST['seq'] == 'view')
{
    $id = $_REQUEST['plg_id'];
    _shn_rms_plg_view($id);
}

?>