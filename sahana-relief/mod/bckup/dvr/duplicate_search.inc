<?php
/**
 *Major functions to search for duplicate entries of a disaster victim
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Viraj Edirisinghe
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ($global['approot'] . '/inc/lib_form.inc');
include_once ($global['approot'] . '/inc/lib_misc.inc');
include_once ($global['approot'] . '/mod/dvr/lib.inc');

global $global;
_shn_dvr_print_header(_t("Duplicate Search"));

/**
 * //////////////////////////////////////////////////////////////////////////////////////////////
 */
switch ($_REQUEST['seq']) {
    case 'search' :
        {
            _shn_duplicate_search_default();
            //$_POST['p_uuid']= $_SESSION['dvr']['person2']['id'];
            /* $_SESSION['general'] = false;
            if (isset($_POST['gen'])) {
            $_SESSION['general'] = true;
            }*/

            $posts['nic'] = $_POST['nic']; $posts['mob'] = $_POST['mob'];
            $posts['pas'] = $_POST['pas']; $posts['tel'] = $_POST['tel'];
            $posts['lcn'] = $_POST['lcn']; $posts['name'] = $_POST['name'];

            $duplicates = array();
            $duplicates = _shn_dvr_get_victims($posts);
            $_SESSION['dvr']['duplicates']=$duplicates;

            listing($duplicates);

            break;
        }
    case 'back' :
        {
            _shn_duplicate_search_default();
            $_SESSION['dvr']['back']=true;
            $duplicates=$_SESSION['dvr']['duplicates'];
            listing($duplicates);
        }

    default :
        {
            if($_SESSION['dvr']['back']==true)
            {
                $_SESSION['dvr']['back']=false;
                break;
            }
            _shn_duplicate_search_default();
        }


}
/////////////////////////////////////////////////////////////////////////////hgugu


function _shn_duplicate_search_default()
{
    shn_form_fopen("duplicate_search", null, false);
    shn_form_hidden(array('seq'=>'search'));

    shn_form_fsopen(_t('Select Fields'));
    //	shn_form_checkbox("General Search",'gen');
    //	print '<br>';print '<br>';
    shn_form_checkbox("Full Name",'name');
    shn_form_checkbox("Identity Card Number",'nic');
    shn_form_checkbox("License",'lcn');
    shn_form_checkbox("Passport Number",'pas');
    shn_form_checkbox("Mobile",'mob');
    shn_form_checkbox("Telephone",'tel');


    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    if (isset($_REQUEST['seq']) == false) {
        shn_form_fclose();
    }
}

function listing($duplicates)
{
    print '<br>' . '<br>' . '<br>';
    //shn_form_fopen("duplicate_search", null, false);
    //	$duplicates = array();
    //	$duplicates = _shn_dvr_get_victims($options);
    $diff_entries = array();
    $entries = array();
    if ($duplicates) {
        //if(count($duplicates)>10){
        shn_form_fsopen(_t("Duplicates"));
        ?>
<div id="result">
<table>
	<thead>
		<tr>
			<td><?php echo _t("Entry Name")?></td>
			<td><?php echo _t("Mobile")?></td>
			<td><?php echo _t("Telephone")?></td>
			<td><?php echo _t("NIC")?></td>
			<td><?php echo _t("Passport")?></td>
			<td><?php echo _t("Licence")?></td>
			<td><?php echo _t("Compare")?></td>
			<!-- jhdhjsskkak -->
		</tr>
	</thead>
	<?php
	foreach ($duplicates as $dup) {
	    if(in_array($dup['entry_id'], $diff_entries)) {
	        array_push($entries[$dup['entry_id']], $dup['dup_id']);
	    } else {
	        $entries[$dup['entry_id']] = array();
	        array_push($diff_entries, $dup['entry_id']);
	        array_push($entries[$dup['entry_id']], $dup['dup_id']); //var_dump($dup['dup_id']);
	        ?>
	<tr>
		<td><a
			href='index.php?mod=dvr&act=edit_individual&p_uuid=<?php echo $dup['entry_id']?>'><b><?php echo $dup['entry_name']?></b></a></td>
		<td><?php echo $dup['entry_mobile']?></td>
		<td><?php echo $dup['entry_telephone']?></td>
		<td><?php echo $dup['entry_nic']?></td>
		<td><?php echo $dup['entry_pass']?></td>
		<td><?php echo $dup['entry_lic']?></td>

		<td><a
			href='index.php?mod=dvr&act=compare_duplicates&p_uuid1=<?php echo $dup['entry_id']?>'>Show</a></td>

	</tr>
	<?php
}
}//echo "<pre>";var_dump($entries['pre6p-9']);echo "</pre>";?>
</table>
</div>
<?php
$_SESSION['entries'] = $entries; //echo "<pre>";var_dump($_SESSION['entries']);echo "</pre>";
//}
/////////////////////////////////////////////////////////////////////////////////////////////////
/*else{


shn_form_fsopen(_t("Duplicates"));
?>
<div id ="result">
<table>
<thead>
<tr>
<td><?php echo _t("Entry Name")?></td>
<td><?php echo _t("Mobile")?></td>
<td><?php echo _t("Telephone")?></td>
<td><?php echo _t("Duplicate Entry")?></td>
<td><?php echo _t("Mobile (Duplicate)")?></td>
<td><?php echo _t("Telephone")?></td>
<td><?php echo _t("Compare")?></td>
<td><?php echo _t("Delete duplicate")?></td>
</tr>
</thead>
<?foreach($duplicates as $dup){ ?>
<tr>
<td><a href='index.php?mod=dvr&act=edit_individual&p_uuid=<?php echo $dup['entry_id']?>'><b><?php echo $dup['entry_name']?></b></a></td>
<td><?php echo $dup['entry_mobile']?></td>
<td><?php echo $dup['entry_telephone']?></td>
<td><a href='index.php?mod=dvr&act=edit_individual&p_uuid=<?php echo $dup['dup_id']?>'><b><?php echo $dup['dup_name']?></b></a></td>
<td><?php echo $dup['dup_mobile']?></td>
<td><?php echo $dup['dup_telephone']?></td>
<td><a href='index.php?mod=dvr&act=compare_duplicates&p_uuid1=<?php echo $dup['entry_id']?>&p_uuid2=<?php echo $dup['dup_id']?>'>Compare</a></td>
<td><a href='index.php?mod=dvr&act=delete_individual&p_uuid=<?php echo $dup['dup_id']?>' onClick="javascript: return confirmdelete('<?php echo $dup['dup_id']?>')">Delete</a></td>
</tr>

<?php

}//print $xx.',';
?></table>
</div>
<?php

}*/
/////////////////////////////////////////////////////////////////////////////////////////////////////
}

else {
    _shn_html_print_alert(_("No duplicates found."));
}

shn_form_fsclose();
shn_form_fclose();
}

/////////////////////////////////////////////////////////////////////////////

/**
 * get the entries from the database
 *
 * @return unknown
 */
function _shn_dvr_get_victims($options)
{
    global $global;
    //$sql = "CREATE VIEW duplicates AS SELECT p.p_uuid as id,p.full_name as name,c.contact_value as mobile,t.contact_value as tele,n.serial as nic,dl.serial as drv_lic,ps.serial as passport FROM person_uuid p,contact c,contact t,identity_to_person n,identity_to_person ps,identity_to_person dl WHERE p.p_uuid=c.pgoc_uuid AND p.p_uuid=t.pgoc_uuid AND c.opt_contact_type='mobile' AND t.opt_contact_type='telephone' AND p.p_uuid=n.p_uuid AND p.p_uuid=ps.p_uuid AND p.p_uuid=dl.p_uuid AND n.opt_id_type='idcard' AND ps.opt_id_type='pas' AND dl.opt_id_type='dln'";
    //$global['db']->Execute($sql);
    //person_details-p_uuid,birth_date,opt_age_group,opt_gender

    //$sql = "SELECT a.id AS ent_id,a.name AS ent_name,a.tele AS ent_tele,b.tele AS dup_tele, b.name AS dup_name, a.mobile AS ent_mob,b.id AS dup_id,b.mobile AS dup_mob FROM duplicates a,duplicates b WHERE a.id!=b.id AND ((a.mobile=b.mobile AND a.mobile!='') OR a.name=b.name OR (a.name=b.name AND a.tele=b.tele AND a.tele!=''))";

    ////// For Distinct names
    //$sql = "SELECT DISTINCT a.id AS ent_id,a.name AS ent_name,a.tele AS ent_tele,a.nic AS ent_nic,a.passport AS ent_ps,a.drv_lic AS ent_lic, a.mobile AS ent_mob";

    ////// For Both Duplicate pair
    $sql = "SELECT a.id AS ent_id,a.name AS ent_name,a.tele AS ent_tele,a.nic AS ent_nic,a.passport AS ent_ps,a.drv_lic AS ent_lic, a.mobile AS ent_mob, b.tele AS dup_tele, b.name AS dup_name,b.id AS dup_id,b.mobile AS dup_mob ,b.nic AS dup_nic,b.passport AS dup_ps,b.drv_lic AS dup_lic";

    $sql = $sql . " FROM (SELECT p.p_uuid as id,p.full_name as name,c.contact_value as mobile,t.contact_value as tele,n.serial as nic,dl.serial as drv_lic,ps.serial as passport FROM person_uuid p,contact c,contact t,identity_to_person n,identity_to_person ps,identity_to_person dl WHERE p.p_uuid=c.pgoc_uuid AND p.p_uuid=t.pgoc_uuid AND c.opt_contact_type='mobile' AND t.opt_contact_type='telephone' AND p.p_uuid=n.p_uuid AND p.p_uuid=ps.p_uuid AND p.p_uuid=dl.p_uuid AND n.opt_id_type='idcard' AND ps.opt_id_type='pas' AND dl.opt_id_type='dln' ORDER BY name) a,"
    . "(SELECT p.p_uuid as id,p.full_name as name,c.contact_value as mobile,t.contact_value as tele,n.serial as nic,dl.serial as drv_lic,ps.serial as passport FROM person_uuid p,contact c,contact t,identity_to_person n,identity_to_person ps,identity_to_person dl WHERE p.p_uuid=c.pgoc_uuid AND p.p_uuid=t.pgoc_uuid AND c.opt_contact_type='mobile' AND t.opt_contact_type='telephone' AND p.p_uuid=n.p_uuid AND p.p_uuid=ps.p_uuid AND p.p_uuid=dl.p_uuid AND n.opt_id_type='idcard' AND ps.opt_id_type='pas' AND dl.opt_id_type='dln' ORDER BY name DESC) b"
    . " WHERE a.id!=b.id AND (";

    //if($_SESSION['general'] == true)
    //{
        $sql = $sql . "(a.mobile=b.mobile AND a.mobile!='') OR "
        . "(a.nic=b.nic AND a.nic!='') OR "
        . "(a.drv_lic=b.drv_lic AND a.drv_lic!='') OR "
        . "(a.passport=b.passport AND a.passport!='') OR "
        . "(a.name=b.name AND a.tele=b.tele AND a.tele!='') OR "
        . "a.name=b.name";
        $sql = $sql . ")";
        //}
        //else{
        if (isset($options['nic'])) {
            $sql = $sql . " AND (a.nic=b.nic AND a.nic!='')";
        }
        if (isset($options['mob']))	{
            $sql = $sql . " AND (a.mobile=b.mobile AND a.mobile!='')";
        }
        if (isset($options['lcn'])) {
            $sql = $sql . " AND (a.drv_lic=b.drv_lic AND a.drv_lic!='')";
        }
        if (isset($options['pas'])) {
            $sql = $sql . " AND (a.passport=b.passport AND a.passport!='')";
        }
        if (isset($options['tel'])) {
            $sql = $sql . " AND (a.name=b.name AND a.tele=b.tele AND a.tele!='')";
        }
        if (isset($options['name'])) {
            $sql = $sql . " AND a.name=b.name";
        }
        //$sql = $sql.")";

        //}



        //////////////////////////
        //$sql = $sql." AND a.gender=b.gender";

        $res = $global['db']->GetAll($sql);
        $res_count = count($res);
        $count = $res_count / 2 - 1;
        $result = array();

        //$sql = "DROP VIEW duplicates";
        //$global['db']->Execute($sql);

        $i = 0;

        foreach ($res as $r) {
            $result[$i]['entry_id'] = $r['ent_id'];
            $result[$i]['entry_name'] = $r['ent_name'];
            $result[$i]['entry_mobile'] = $r['ent_mob'];
            $result[$i]['entry_telephone'] = $r['ent_tele'];
            $result[$i]['entry_nic'] = $r['ent_nic'];
            $result[$i]['entry_lic'] = $r['ent_lic'];
            $result[$i]['entry_pass'] = $r['ent_ps'];

            $result[$i]['dup_id'] = $r['dup_id'];
            $result[$i]['dup_name'] = $r['dup_name'];
            $result[$i]['dup_mobile'] = $r['dup_mob'];
            $result[$i]['dup_telephone'] = $r['dup_tele'];

            //if($i==$count)
            //break;
            $i++;
        }
        //$results = refinary();
        return $result;
        }

        function _shn_dvr_find_duplicates()
        {
            $a = array();
            $a = _shn_dvr_get_victims();
            $count = count($a);
            $b = array();
            for ($j = 0; $j <= $count; $j++) {
                for ($k = $count - 1; $k >= 0; $k--) {
                    if ($j < $k) {
                        if ($a[$j]['name'] == $a[$k]['name'] && $a[$j]['name'] != null) {
                            $c = array();
                            $c['entry'] = $a[$j];
                            $c['dup'] = $a[$k];
                            array_push($b,$c);
                        } elseif ($a[$j]['mobile'] == $a[$k]['mobile'] && $a[$j]['mobile'] != null) {
                            $c = array();
                            $c['entry'] = $a[$j];
                            $c['dup'] = $a[$k];
                            array_push($b,$c);

                        } elseif ($a[$j]['tele'] == $a[$k]['tele'] && $a[$j]['name'] == $a[$k]['name'] && $a[$j]['tele'] != null) {
                            $c = array();
                            $c['entry'] = $a[$j];
                            $c['dup'] = $a[$k];
                            array_push($b,$c);
                        }
                        //array_push($b['dup'],$a[$k]);
                    } else {
                        break;
                    }
                }


            }
            return $b;
        }

        ?>


<script language="JavaScript">

function confirmdelete(name)
{
return confirm('This person '+name+' will be permanently deleted');
}


</script>


