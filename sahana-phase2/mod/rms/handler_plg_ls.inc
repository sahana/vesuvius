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


_shn_rms_show_headder(_("List of Current Pledges"));



function _shn_rms_get_allplgs()
{
    global $global;

    $filter = $_REQUEST['filter'];
    $order  = $_REQUEST['order'];

    $sql = "SELECT * FROM rms_pledge";

    if(isset($filter) && trim($filter) != -1)
    {
        $str = " WHERE cat_id=$filter";
        $sql .= $str;
    }

    if(trim(isset($order)))
    {
        $str = " ORDER BY $order";
        $sql .= $str;
    }

    $rs = $global['db']->Execute($sql);


    if ($rs == null || $global['db']->ErrorMsg() != null)
    {
        _shn_rms_adderror($global['db']->ErrorMsg());
        _shn_rms_showerrors();
        return false;
    }

    $arr = $rs->GetArray();

    return $arr;
}

function __add_order_url($str)
{
    switch ($str)
    {
        case 'ID' : print "<a href='index.php?mod=rms&amp;act=vw_plgs&amp;order=plg_id'>$str</a>";
                    break;
        case 'Status' : print "<a href='index.php?mod=rms&amp;act=vw_plgs&amp;order=status'>$str</a>";
                    break;
        case 'Category' : print "<a href='index.php?mod=rms&amp;act=vw_plgs&amp;order=cat_id'>$str</a>";
                    break;
        case 'Date' : print "<a href='index.php?mod=rms&amp;act=vw_plgs&amp;order=date'>$str</a>";
                    break;
        case 'Donor' : print "<a href='index.php?mod=rms&amp;act=vw_plgs&amp;order=user_id'>$str</a>";
                    break;
        case 'Item' : print "<a href='index.php?mod=rms&amp;act=vw_plgs&amp;order=item'>$str</a>";
                    break;
    }
}

function _shn_rms_show_plglist()
{
    _shn_rms_plg_showfilter();
    $plgs = _shn_rms_get_allplgs();
?>
<div id ="result">
<table>
    <thead>
        <td width=""><?php __add_order_url('ID') ?></td>
        <td width="70"><?php __add_order_url('Status') ?></td>
        <td width=""><?php __add_order_url('Date') ?></td>
        <td width="120"><?php __add_order_url('Donor') ?></td>
        <td width="100"><?php __add_order_url('Category') ?></td>
        <td width="100"><?php __add_order_url('Item') ?></td>
        <td width=""><?php print _("Change Status") ?></td>
        <td width=""><?php print _("More Details") ?></td>
    </thead>
<?php

    foreach($plgs as $plg)
    {
?>
    <tr id="body">
        <td><?php print  $plg['plg_id']; ?></td>
        <td><?php print  $plg['status']; ?></td>
        <td><?php print  $plg['date']; ?></td>
        <td><?php print  get_donor_name($plg['user_id']); ?></td>
        <td><?php print  get_plg_category($plg['cat_id']); ?></td>
        <td><?php print  $plg['item']; ?></td>
        <td>
        <?php

            shn_form_fopen("stat_plgs",null,array('req_message'=>false));
            shn_form_hidden(array('seq'=>''));
            shn_form_hidden(array('from'=>'list'));
            shn_form_hidden(array('plg_id'=>$plg['plg_id']));
            shn_form_submit('Change Status',"shorter");
            shn_form_fclose();
        ?>
        </td>
        <td>
        <?php
            #more details button
            shn_form_fopen("vw_plgs",null,array('req_message'=>false));
            shn_form_hidden(array('seq'=>'vw_plg'));
            shn_form_hidden(array('id'=>$plg['plg_id']));
            shn_form_submit('More',"shorter");
            shn_form_fclose();
        ?>
        </td>

    </tr>

<?php
    }
?>
</table>
</div>
<?php
}

function _shn_rms_show_plgdetails()
{
    _shn_rms_plg_view($_POST['id']);

    #back button
    shn_form_fopen("vw_plgs",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>''));
    shn_form_submit('Back',"short");
    shn_form_fclose();

}

function _shn_rms_plg_showfilter()
{
    $value = $_REQUEST['filter'];
    _shn_rms_fltcats($value);
    print "<br/>";
}

function _shn_rms_fltcats($value)
{
    global $global;
    $sql = "SELECT cat_id,category FROM  rms_req_category";
    $rs = $global['db']->Execute($sql);

    $url = "index.php?mod=rms&act=vw_req&amp;act=vw_plgs";

    $select = "<div><form action='$url' name=req_fil_cat method=post>\n";
    $select .= _("Filter by Category");
    $select .= "<select name='filter' onChange='submit();'>\n";
    $rs_arr = $rs->GetAll();
    foreach ($rs_arr as $r)
    {
        if($r[0] != $value)
            $select .= "\t<option value=" . $r[0] . ">" . $r[1] . "</option>\n";
        else
            $select .= "\t<option selected='selected' value=" . $r[0] . ">" . $r[1] . "</option>\n";
    }
    $select .= "\t<option value='-1'> All </option>\n";
    $select .= "</select>\n" .
               "</form>\n" .
               "</div>";
    print $select;
}

switch ($_REQUEST['seq'])
{
    case '':
            _shn_rms_show_plglist();
            break;

    case 'vw_plg':
            _shn_rms_show_plgdetails();
            break;
}


?>