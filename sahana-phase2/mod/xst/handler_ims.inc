<?php
/**
 *
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Ishan Liyanage <ishan@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 */
 
 function _shn_get_victims()
{
	// print ('test');
	/*require_once('../3rd/adodb/adodb.inc.php');
	require_once('../conf/sysconf.inc.php');
	//Make the connection to $global['db']
	$db = NewADOConnection($conf['db_engine']);
	$db ->Connect($conf['db_host'].($conf['db_port']?':'.$conf['db_por
t']:''),$conf['db_user'],$conf['db_pass'],$conf['db_name']);*/
    global $global;
    $db=$global['db'];
    $level=1;
	$head_name=$_GET{"head_name"};
	//$victim_array=array();

	//$search="select p.p_uuid as pid, pg.opt_group_type as group_type,gd.head_uuid as head_uuid,pe.full_name as full_name,pe.family_name as family_name,pe.l10n_name as local_name,i.serial as serial,c.contact_value as address  from person_to_pgroup as p inner join pgroup as pg on pg.g_uuid =p.g_uuid inner join group_details as gd on gd.g_uuid=p.g_uuid inner join person_uuid as pe on pe.p_uuid = p.p_uuid left join identity_to_person as i on (i.p_uuid = p.p_uuid and i.opt_id_type='idcard') left join contact as c on (c.pgoc_uuid= p.p_uuid and c.opt_contact_type='address') where pe.full_name='$head_name' or pe.family_name='$head_name' or pe.l10n_name='$head_name' or i.serial='$head_name';";
	$search="select p.p_uuid as pid, pe.full_name as full_name, pe.family_name as family_name from person_to_pgroup as p inner join pgroup as pg on pg.g_uuid =p.g_uuid inner join group_details as gd on gd.g_uuid=p.g_uuid inner join person_uuid as pe on pe.p_uuid = p.p_uuid left join identity_to_person as i on (i.p_uuid = p.p_uuid and i.opt_id_type='idcard') left join contact as c on (c.pgoc_uuid= p.p_uuid and c.opt_contact_type='address') where pe.full_name='$head_name' or pe.family_name='$head_name' or pe.l10n_name='$head_name' or i.serial='$head_name';";
	$res=$db->Execute($search);
	$i=0;
	if(!$res->EOF && $res!=NULL)
	{
		while(!$res->EOF && $res!=NULL)
		{

			//$name=$res->fields['first_name']." " .$res->fields['last_name'];
			$victim_array=$victim_array.",".$res->fields['0'];
			$victim_array=$victim_array.",".$res->fields['1']." ".$res->fields['2'];

			//$victim_array[$i]=$i;
			$i=$i+1;
			$res->MoveNext();
		}
		//return $victim_array;
		echo $victim_array;
	}
	else
	{
		echo "null";
	}


}
