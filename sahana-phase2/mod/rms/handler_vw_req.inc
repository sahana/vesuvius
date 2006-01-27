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
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package
* @subpackage
* @tutorial
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


_shn_rms_show_headder(_("View Request using the <em>Request ID</em>"));

    global $global;

    if ($_POST['seq'] == 'view')
    {
        $req_id = $_POST['req_id'];

        $sql = "SELECT * FROM rms_request WHERE req_id=$req_id";
        $rs_r = $global['db']->Execute($sql);

        if (1 > $rs_r->RecordCount())
        {
            print "not a valid request id";
        }
        else
        {
            $recordSet = $rs_r;
?>

         <div id ="result">
        <table>
        <thead>
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
                    <?php print ($rs->fields['category']); ?>
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
        }
}
?>