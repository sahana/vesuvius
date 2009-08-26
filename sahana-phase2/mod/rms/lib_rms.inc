<?php
/**
 * The Sahana Resquest Management System
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author		Sudheera R. Fernando <sudheera@opensource.lk>
 * @copyright    Lanka Software Foundation - http://www.opensource.lk
 * @package		sahana
 * @subpackage	rms
 * @tutorial
 * @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
 * Public License (LGPL)
 */

include_once $global['approot']."/inc/lib_errors.inc";
function _shn_rms_print_hedder($string=null)
{
	if (!$string)
	print '<h2>' . _t("Welcome to The Sahana ") . shn_get_module_name() . '</h2>';
	else
	print '<h2>' . $string . '</h2>';
}
//added by isuru
function _shn_rms_add_identity($p_uuid,$cardno,$type)
{

	global $global;
	$sql="INSERT INTO identity_to_person (p_uuid,serial,opt_id_type) values('$p_uuid','$cardno','$type') ";
	$global['db']->Execute($sql);

}
function _shn_rms_add_requester($requester)
{
	global $global;

	$p_uuid = shn_create_uuid('p');
	// print $p_uuid;
	$name   = $requester['name'];
	$mobile = $requester['mobile'];
	$tel    = $requester['telephone'];
	$email  = $requester['email'];
	$addr   = $requester['address'];

	$id_type=$requester['opt_id_type'];
	$card_number_pre=$requester['card_number'];
	$card_number=$p_uuid;
	//print $card_number;

	$sql = "INSERT INTO person_uuid (p_uuid, full_name) " .
            "VALUES ('$p_uuid', '$name')";

	if ($global['db']->Execute($sql) === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
	}
	else
	{
		if (trim($mobile) != '')
		_shn_rms_db_addcontact($p_uuid, 'mobile', $mobile);
		if (trim($tel) != '')
		_shn_rms_db_addcontact($p_uuid, 'telephone', $tel);
		if (trim($email) != '')
		_shn_rms_db_addcontact($p_uuid, 'email', $email);
		if (trim($addr) != '')
		_shn_rms_db_addcontact($p_uuid, 'address', $addr);


		if(trim($card_number))
		{
			_shn_rms_add_identity($p_uuid,$card_number,$id_type);
		}

		return $card_number;//return $p_uuid
	}


}
function _shn_rms_is_person($id)
{
	global $global;

	$sql = "SELECT * FROM person_uuid p,identity_to_person i WHERE p.p_uuid=i.p_uuid and i.serial='$id'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		return true;
	}

	return false;
}
function _shn_rms_get_person($id)
{
	global $global;

	// $sql = "SELECT * FROM person_uuid p,identity_to_person i WHERE p.p_uuid=i.p_uuid and i.p_uuid='$id'";
	$sql= "SELECT * FROM person_uuid p WHERE p.p_uuid='$id'";
	$rs = $global['db']->Execute($sql);
	//print $sql;
	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$psn_arr = $rs->GetArray();

		$person['uuid'] = $psn_arr[0]['p_uuid'];
		$person['name'] = $psn_arr[0]['full_name'];
		$person_uuid = $person['uuid'];
		$sql = "SELECT * FROM contact WHERE pgoc_uuid='$person_uuid'";
		$rs_cnt = $global['db']->Execute($sql);

		if ($rs_cnt !== null)
		{
			$rs_cnts = $rs_cnt->GetArray();
			foreach ($rs_cnts as $c)
			{
				$person[$c['opt_contact_type']] = $c['contact_value'];
			}
		}

		return $person;
	}

	// return false;
}
function _shn_rms_is_requester($id)
{
	global $global;

	//$sql = "SELECT * FROM rms_request r,identity_to_person i WHERE i.serial=r.reqstr_uuid and i.serial='$id' ";
	$sql = "SELECT * FROM rms_request WHERE reqstr_uuid='$id' ";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		return true;
	}

	return false;
}
function _shn_rms_get_requester($id)
{
	if (_shn_rms_is_user($id))
	{
		return _shn_rms_get_person($id);
	}

	return false;
}
function _shn_rms_get_requesters()
{
	global $global;

	$sql = "SELECT psn.p_uuid AS p_uuid, psn.full_name AS fullname " .
           "FROM rms_request req, person_uuid psn " .
           "WHERE req.reqstr_uuid=psn.p_uuid";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$psn_arr = $rs->GetArray();

		foreach ($psn_arr as $psn)
		{
			$requesters[$psn['p_uuid']] = $psn['fullname'];
		}

		return $requesters;
	}

	return false;
}
function _shn_rms_get_location($loc_id)
{
	global $global;

	$sql = "SELECT * FROM location_details " .
            "WHERE location_id='$loc_id'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		return $rs[0];
	}

	return false;
}
function _shn_rms_get_locations()
{
	global $global;

	$sql = "SELECT loc.location_id " .
           "FROM location_details loc,rms_request req " .
           "WHERE loc.poc_uuid=req.reqstr_uuid";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();

		foreach ($rs as $r)
		{
			//$locations[$r[0]] = $r[0];
			$id=$r[0];
			//print $id;
			$locations[$r[0]] = _shn_rms_get_location_name($id);
		}

		return $locations;
	}

	return false;
}
function _shn_rms_add_requester_loc($id, $location)
{
	global $global;

	$poc_uuid = $id;

	$location_id = $location['id'];
	$type = $location['type'];
	$address = $location['address'];
	$postcode = $location['postcode'];
	$gis = $location['gis'];

	$sql = "INSERT INTO location_details ( " .
                                           "poc_uuid, " .
                                           "location_id, " .
                                           "opt_person_loc_type, " .
                                           "address, " .
                                           "postcode, " .
                                           "long_lat) " .
            "VALUES ('$poc_uuid', '$location_id', '$type', '$address', " .
                    "'$postcode', '$gis')";

	if ($global['db']->Execute($sql) === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else
	{
		return true;
	}
}
//**************************************************************
//return poc_uuid and location id from location_details
function _shn_rms_get_requester_locs($id)
{
	global $global;
	$db = $global['db'];
	// $sql = "SELECT poc_uuid, location_id FROM location_details " .
	//         "WHERE poc_uuid='$id'";
	$sql = "SELECT DISTINCT loc_uuid FROM rms_request WHERE reqstr_uuid='$id'";
	//$sql = "SELECT DISTINCT location.name FROM rms_request,location WHERE rms_request.reqstr_uuid='$id'";

	$rec = $db->Execute($sql);
	$loc =array();
	$i = 0;
	if ($rec === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	} elseif (1 <= $rec->RecordCount()){
		While(!$rec->EOF)
		{

			$loc[$i] = $rec->fields['loc_uuid'];
			// $loc[$i] = $rec->fields['name'];

			$rec->MoveNext();
			$i++;
		}
		//$rs = $global['db']->Execute($sql);


		return $loc;
	}
	/* if ($rs === false)
	 {
	 $msg = $global['db']->ErrorMsg();
	 add_error($msg . '<br />' . $sql);
	 display_errors();
	 return false;
	 }
	 elseif (1 <= $rs->RecordCount())
	 {
	 $rs = $rs->GetArray();
	 foreach ($rs as $r){
	 $locs[$r['loc_uuid']] = $r['loc_uuid'];
	 //echo $r['loc_uuid'];
	 return $locs;
	 }*/






	//}

	// return false;
}
function _shn_rms_get_shnuser()
{
	$user_id = 'p-999';
	return $user_id;
}
function _shn_rms_get_categories()
{
	global $global;

	$sql = "SELECT * FROM ct_catalogue WHERE parentid='0'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		return $rs->GetArray();
	}

	return false;
}
function _shn_rms_get_priorities()
{
	global $global;

	$sql = "SELECT * FROM rms_priority";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		return $rs->GetArray();
	}
	else
	{
		return array();
	}

}
function _shn_rms_get_items($cat_id)
{
	global $global;

	$sql = "SELECT * FROM ct_catalogue WHERE parentid='$cat_id' AND final_flag='1'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		return $rs->GetArray();
	}

	return false;
}
function _shn_rms_get_itm_units($itm_id)
{
	global $global;

	$sql = "SELECT * FROM ct_unit, ct_cat_unit WHERE ct_uuid='$itm_id' " .
            "AND ct_unit.unit_uuid=ct_cat_unit.unit_uuid";

	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		return $rs->GetArray();
	}

	return false;
}
function _shn_rms_get_sub_cat($cat_id)
{
	global $global;

	$sql = "SELECT * FROM ct_catalogue WHERE parentid='$cat_id' AND final_flag='0'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		return $rs->GetArray();
	}

	return false;
}
function _shn_rms_add_item2session($itm, $qty, $pri, $unit, $inv)
{
	if( $itm=='' || _shn_rms_check_catalog_item($itm)) {
		add_error(_t("Please Select a Catalog Item"));
		return false;
	}
	if ($qty != '' && is_numeric($qty) && $qty > 0)	{
		$_SESSION['rms_items'][] = array ($itm, $qty, $pri, $unit, $inv);
		return true;
	} else if ($qty == ''){
		add_error(_t("Quantity is a required field"));
		return false;
	} else {
		add_error(_t("Please Enter a valid Quantity"));
	}
}
function _shn_rms_add_item2session_pl($itm, $qty, $stat, $unit)
{
	if(_shn_rms_check_catalog_item($itm))
	{
		add_error(_t("Please Select a Catalog Item"));
		return false;
	}
	if ($qty != '' && is_numeric($qty))
	{
		$_SESSION['rms_items'][] = array ($itm, $qty, $stat, $unit);
		return true;
	}
	else
	{
		add_error(_t("Please Enter a valid Quantity"));
		return false;
	}
}
function _shn_rms_del_itemfromsession($itm_id)
{
	$items = $_SESSION['rms_items'];
	$_SESSION['rms_items'] = null;

	foreach ($items as $item)
	{
		if ($item[0] != $itm_id)
		$_SESSION['rms_items'][] = $item;
	}
}
function _shn_rms_is_itemadded($item)
{
	if (is_array($_SESSION['rms_items']))
	{
		foreach ($_SESSION['rms_items'] as $itm)
		{
			if ($itm[0] == $item)
			return true;
		}
	}
	return false;
}
function _shn_rms_get_itemname($itm_id)
{
	global $global;

	$sql = "SELECT name FROM ct_catalogue WHERE ct_uuid='$itm_id'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		if ($rs[0][0] != NULL)
			return $rs[0][0];
		else
			return $rs[0]['name'];
	}

	return false;
}
function _shn_rms_get_iunit_name($unit_id)
{
	global $global;

	$sql = "SELECT name FROM ct_unit WHERE unit_uuid='$unit_id'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		if($rs[0][0] != NULL)
			return $rs[0][0];
		else
			return $rs[0]['name'];
	}

	return false;
}
function _shn_rms_get_priorityname($pri_id)
{
	global $global;

	$sql = "SELECT priority FROM rms_priority WHERE pri_uuid='$pri_id'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else{
		$res=$rs->fields["priority"];
	  	return $res;
	}
//	elseif (1 <= $rs->RecordCount())
//	{
//		$rs = $rs->GetArray();
//		return $rs[0][0];
//	}

	return false;
}
/***
 * Request Specific functions
 */
function _shn_rms_add_request($reqstr_uuid, $loc_uuid)
{
	global $global;

	$req_uuid = shn_create_uuid('r');
	$status = 'open';
	$user_id = 'u-1';
	$date = $_SESSION['rms']['req']['date'];
	//print $date;
	$sql1 = "INSERT INTO rms_request_date (req_uuid, date) VALUES ('{$req_uuid}', '{$date}')";
//print $sql1;
	$res = $global['db']->Execute($sql1);

	$sql = "INSERT INTO rms_request (req_uuid, reqstr_uuid, loc_uuid, status, user_id) " .
            "VALUES ('$req_uuid', '$reqstr_uuid', '$loc_uuid', '$status', '$user_id')";

	if ($global['db']->Execute($sql) === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
	}
	else
	{
		_shn_rms_add_reqitems($req_uuid);
		return $req_uuid;
	}

}
function _shn_rms_add_reqitems($req_uuid)
{
	global $global;

	foreach ($_SESSION['rms_items'] as $item)
	{
		$item_uuid = $item[0];
		$quantity = $item[1];
		$pri_uuid = $item[2];
		$unit = $item[3];

		$sql = "INSERT INTO rms_req_item " .
                "VALUES ('$item_uuid', $quantity, '$pri_uuid', '$req_uuid', '$unit')";

		if ($global['db']->Execute($sql) === false)
		{
			$msg = $global['db']->ErrorMsg();
			add_error($msg . '<br />' . $sql);
			display_errors();
		}
	}
}
function _shn_rms_get_recordcount($table, $fstr)
{
	global $global;

	$sql = "SELECT COUNT(*) FROM $table";
	$sql .= $fstr;
	$rs = $global['db']->Execute($sql);

	$rs = $rs->GetArray();
	return $rs[0][0];
}
function _shn_rms_get_reqitems($req_uuid)
{
	global $global;

	$sql = "SELECT * FROM rms_req_item WHERE req_uuid='$req_uuid'";

	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		return $rs;
	}
}
function _shn_rms_get_plgitems($plg_uuid)
{
	global $global;

	$sql = "SELECT * FROM rms_plg_item WHERE plg_uuid='$plg_uuid'";

	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		return $rs;
	}
}
function _shn_rms_get_itm_category($itm_id)
{
	$sql = "SELECT DISTINCT(cat.ct_uuid),cat.name " .
           "FROM ct_catalogue itm, ct_catalogue cat " .
           "WHERE itm.parentid=cat.ct_uuid " .
           "AND itm.ct_uuid='$itm_id'";

	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		$cat[$rs[0][0]] = $rs[0][1];
		return $cat;
	}

	return false;
}
/***
 * Donor Functions
 */
function _shn_rms_add_donor($donor)
{
	global $global;
//var_dump($donor);
	$p_uuid = shn_create_uuid('p');
	$name   = $donor['name'];
	$mobile = $donor['mobile'];
	$tel    = $donor['telephone'];
	$email  = $donor['email'];
	$addr   = $donor['address'];
	$card_number=  $donor['card_number'];
	$card_type=  $donor['card_type'];
	$_SESSION['rms']['add_donor']['org_id'] = $donor['org_id'];
	//print $org_id;
	//print $p_uuid;
	$card_number=$p_uuid;
	//print $card_number;

	$sql = "INSERT INTO person_uuid (p_uuid, full_name) " .
            "VALUES ('$p_uuid', '$name')";

	if ($global['db']->Execute($sql) === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
	}
	else
	{
		if (trim($mobile) != '')
		_shn_rms_db_addcontact($p_uuid, 'mobile', $mobile);
		if (trim($email) != '')
		_shn_rms_db_addcontact($p_uuid, 'email', $email);
		if (trim($addr) != '')
		_shn_rms_db_addcontact($p_uuid, 'address', $addr);
		if (trim($tel) != '')
		_shn_rms_db_addcontact($p_uuid, 'telephone', $tel);
		if(trim($card_number))
		{
			_shn_rms_add_identity($p_uuid,$card_number,$card_type);
		}
		return $p_uuid;
	}
}
function _shn_rms_is_donor($id)
{
	global $global;

	$sql = "SELECT * FROM rms_pledge WHERE donor_uuid='$id'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		return true;
	}

	return false;
}
function _shn_rms_get_donor($id)
{
	if (_shn_rms_is_donor($id))
	{
		return _shn_rms_get_person($id);
	}

	return false;
}
function _shn_rms_get_donors()
{
	global $global;

	$sql = "SELECT psn.p_uuid AS p_uuid, psn.full_name AS fullname " .
           "FROM rms_pledge plg, person_uuid psn " .
           "WHERE plg.donor_uuid=psn.p_uuid";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$psn_arr = $rs->GetArray();

		foreach ($psn_arr as $psn)
		{
			$donors[$psn['p_uuid']] = $psn['fullname'];
		}

		return $donors;
	}

	return false;
}
function _shn_rms_add_pledge($donor_uuid)
{
	global $global;
	//print $donor_uuid;
	$plg_uuid = shn_create_uuid('pl');
	$status = 'Not Confirmed';
	$user_id = 'u-1';
	
	$org_id = $_SESSION['rms']['add_donor']['org_id'];

	$sql = "INSERT INTO rms_pledge (plg_uuid, donor_uuid, status, user_id) " .
            "VALUES ('$plg_uuid', '$donor_uuid', '$status', '$user_id')";
	
	$sql1 = "INSERT INTO rms_org (plg_uuid, org_id) VALUES ('{$plg_uuid}', '$org_id')";
	$res = $global['db']->Execute($sql1);
	
	$_SESSION['rms']['add_donor']['donor_uuid'] = $donor_uuid;
	
	if ($global['db']->Execute($sql) === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else
	{
		_shn_rms_add_plgitems($plg_uuid);
		return $plg_uuid;
	}
	
	
}

function _shn_rms_get_item_name($catalog_id)
{
	global $global;
	$db = $global['db'];
	$parent_id_arr = shn_cs_get_parentid_arr($catalog_id);
	//var_dump($parent_id_arr);
	$item_name_array = array();
	
	for($i=0; $i<count($parent_id_arr); $i++)
	{
		if($i==0)
		{
			$sql = "SELECT name FROM ct_catalogue WHERE ct_uuid ='$catalog_id'";
		}
		else
		{
			$j = $i-1;
			$cat = $parent_id_arr[$j];
			$sql = "SELECT name FROM ct_catalogue WHERE ct_uuid='$parent_id_arr[$j]'";
		}
		$res = $db->Execute($sql);
		$item_name_array[$i] = $res->fields['name'];
		//print $sql;			
		
	}
	$item_name_array = array_reverse($item_name_array);
	//var_dump($item_name_array);
	$i=0;
	
	
	
	foreach($item_name_array as $key=>$value)
	{
		if($key==0)
		{
			$item_name = $value;
		}
		else
		{
			$item_name = $item_name.'->'.$value;
		}
	}
	return $item_name;
}

function _shn_rms_add_plgitems($plg_uuid)
{
	global $global;
	$db = $global['db'];
	
	$donor_uuid = $_SESSION['rms']['add_donor']['donor_uuid'];
	$org_id = $_SESSION['rms']['add_donor']['org_id'];
	$item_array = array();
	$item_history = array();

	foreach ($_SESSION['rms_items'] as $item)
	{
		$item_uuid = $item[0];
		$quantity = $item[1];
		$unit = $item[3];
		$inv = $item[4];
		
		$item_array['catalog_id'] = $item_uuid;
		$item_array['inv_id'] = $inv;
		$item_array['suplier_id'] = $donor_uuid;
		$item_array['item_name'] = _shn_rms_get_item_name($item_uuid);
		$item_array['amount'] = $quantity;
		$item_array['unit'] = $unit;
		$item_array['state'] = 'available';
		$item_array['inserted_date'] = date('Y-m-d');
		//var_dump($item_array);
		$insert_item = $db->AutoExecute('ims_item_records', $item_array, 'INSERT');
		if($insert_item === true)
		{
			$q = "SELECT MAX(item_id) FROM ims_item_records";
			$recset = $db->Execute($q);
			$item_id = $recset->fields['MAX(item_id)'];
			$item_history['item_id'] = $item_id;
			$item_history['first_amount'] = $quantity;
			$item_history['unit'] = $unit;
			
			$item_his = $db->AutoExecute('ims_item_amount_history', $item_history, 'INSERT');
			
		}
		
		

		$sql = "INSERT INTO rms_plg_item (item_uuid, quantity, plg_uuid, unit, inventory) " .
                "VALUES ('$item_uuid', $quantity, '$plg_uuid', '$unit', '$inv')";

		if ($global['db']->Execute($sql) === false)
		{
			$msg = $global['db']->ErrorMsg();
			add_error($msg . '<br />' . $sql);
			display_errors();
		}
	}
}
function _shn_rms_add_ff($req_uuid, $item_uuid, $plg_uuid, $qty)
{
	global $global;

	//$plg_uuid = shn_create_uuid('ff');
	//$user_id = 'u-1';

	$sql = "INSERT INTO rms_fulfil (req_uuid, item_uuid, plg_uuid, quantity) " .
            "VALUES ('$req_uuid', '$item_uuid', '$plg_uuid', $qty)";

	if ($global['db']->Execute($sql) === false)
	{
		$msg = $global['db']->ErrorMsg();
		//add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else
	{
		return true;
	}

}
/***
 * Html template helpers
 */
function _shn_html_inform_add($message)
{
	$_SESSION['html_info'][] = $message;
}
function _shn_html_inform_show()
{
	if (!isset($_SESSION['html_info']) || empty($_SESSION['html_info']))
	return false;

	$infor_msgs = $_SESSION['html_info'];

	?>
<div id="error"><!-- TODO: change style -->
<p><em><?php print _t("Information") . ' :'?></em></p>
<ul>
<?php
foreach ( $infor_msgs as $info )
{
	?>
	<li><?=$info?></li>
	<?php
}
?>
</ul>
</div>
<?php
$_SESSION['html_info'] = null;
}
function _shn_html_print_alert($alert)
{
	?>
<div class="alert"><!-- TODO: change style --> <strong><?php print _t("Alert") . " : $alert"?></strong>
</div>
	<?php
}
function _shn_html_print_message($msg,$br = false)
{
	$br_str = '';
	if ($br == true)
	$br_str = '<br />';
	?>
<div class="message"><strong><?php print $msg?></strong> <?php print $br_str ?>
</div>
	<?php
}
function _shn_rms_get_request($req_uuid)
{
	global $global;
	$sql = "SELECT * FROM rms_request WHERE req_uuid='$req_uuid'";

	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		return $rs[0];
	}
	else
	{
		return false;
	}
}
function _shn_rms_get_pledge($plg_uuid)
{
	global $global;
	$sql = "SELECT * FROM rms_pledge WHERE plg_uuid='$plg_uuid'";

	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		return $rs[0];
	}
}
function _shn_rms_is_reqstatus($status)
{
	$stats = array ('open', 'closed');

	foreach ($stats as $stat)
	{
		if ($stat == $status)
		{
			return true;
		}
	}

	return false;
}
function _shn_rms_is_plgstatus($status)
{
	$stats = array ('delivered', 'not_confirmed', 'confirmed', 'discarded');

	foreach ($stats as $stat)
	{
		if ($stat == $status)
		{
			return true;
		}
	}

	return false;
}
function _shn_rms_view_requester($reqstr_id, $summary=false)
{
	print '<div id="note2">';
	print '<h4>' . _t("Requester Information") . '</h4>';

	//$requester = _shn_rms_get_person($reqstr_id);
	$requester = _shn_rms_get_requester($reqstr_id);
	
	/*if (!$summary)
	{
		///$tmp_str = '<strong>' . _t("RequesterID") . '</strong>';
		//$tb_reqstr[] = array($tmp_str , $reqstr_id);
		$tb_reqstr[] = array('<strong>' . _t("Full Name") . '</strong>', $requester['name']);
		//$tb_reqstr[] = array('<strong>' . _t("Address") . '</strong>', $requester['address']);
		//$tb_reqstr[] = array('<strong>' . _t("email") . '</strong>', $requester['email']);
		//$tb_reqstr[] = array('<strong>' . _t("Mobile") . '</strong>', $requester['mobile']);
		//$tb_reqstr[] = array('<strong>' . _t("Telephone") . '</strong>', $requester['telephone']);

		$width=array('20%');
		shn_html_table($tb_reqstr,null,null,array('class'=>'layout','width'=>$width));
	}
	else
	{*/
		?>


<strong>Requester Name</strong>
:
		<?=$requester['name']?>
		<?php
//}
print '</div>';
}
function _shn_rms_view_donor($donor_id, $summary=false)
{
	print '<div id="note2">';
	//print '<h4>' . _t("Donor Contact Information") . '</h4>';
	print '<h4>' . _t("Donor Information") . '</h4>';

	$donor = _shn_rms_get_person($donor_id);
	if (!$summary)
	{
		$tmp_str = '<strong>' . _t("Donor ID") . '</strong>';
		//$tb_donor[] = array($tmp_str , $donor_id);
		$tb_donor[] = array('<strong>' . _t("Full Name") . '</strong>', $donor['name']);
		//$tb_donor[] = array('<strong>' . _t("email") . '</strong>', $donor['email']);
		//$tb_donor[] = array('<strong>' . _t("Mobile") . '</strong>', $donor['mobile']);
		//$tb_donor[] = array('<strong>' . _t("Telephone") . '</strong>', $donor['telephone']);
		//$tb_donor[] = array('<strong>' . _t("Address") . '</strong>', $donor['address'])

		$width=array('20%');
		shn_html_table($tb_donor,null,null,array('class'=>'layout','width'=>$width));
	}
	else
	{
		?>
<strong>Donor ID</strong>
:
		<?=$donor_id?>
<br />
<strong><?php echo _t("Donor Name")?></strong>
:
		<?=$donor['name']?>
		<?php
}
print '</div>';
}
function _shn_rms_view_location($loc_id, $summary=false)
{
	print '<div id="note2">';
	//print '<h4>' . _t("Request Location Information") . '</h4>';
	/*=====================================================================
    if(_shn_rms_is_location($loc_id)) {
        $location = _shn_rms_get_location_name($loc_id);
    }elseif(_shn_rms_is_camp($loc_id)) {;
        $location = _shn_rms_get_camp_name($loc_id);
    }elseif(_shn_rms_is_org($loc_id)) {
        $location = _shn_rms_get_org_name($loc_id);
    }
	//=====================================================================
	
	
	if (!$summary)
	{
		//$tmp_str = '<strong>' . _t("Location ID") . '</strong>';
		//$tb_loc[] = array($tmp_str , $loc_id);
		$tb_loc[] = array('<strong>' . _t("Location") . '</strong>', $location);
		//$tb_loc[] = array('<strong>' . _t("Location Type") . '</strong>', $location['opt_person_loc_type']);
		// $tb_loc[] = array('<strong>' . _t("Address") . '</strong>', $location['address']);
		// $tb_loc[] = array('<strong>' . _t("Post code") . '</strong>', $location['postcode']);
		//$tb_loc[] = array('<strong>' . _t("GIS") . '</strong>', $location['long_lat']);

		$width=array('20%');
		shn_html_table($tb_loc,null,null,array('class'=>'layout','width'=>$width));
	}
	else
	{*/
	$location = _shn_rms_get_name($loc_id);
		?>

<strong><?php echo _t("Location")?></strong>
:
		<?=$location?>
		<?php
//}
print '</div>';
}

function _shn_rms_view_req_item($req_id, $req_item){
	global $global;
	
	$sql = "SELECT quantity,pri_uuid FROM rms_req_item WHERE req_uuid = '$req_id' AND item_uuid = '$req_item'";
	$res = $global['db']->Execute($sql);
	$fulfiled = 0;
	if ($res->RecordCount() > 0){
		$sql2 = "SELECT SUM(quantity) as qty FROM rms_fulfil WHERE req_uuid = '$req_id' AND item_uuid = '$req_item'";
		$res2 = $global['db']->Execute($sql2);
		if ($res2->RecordCount() > 0){
			$fulfiled = $res2->fields[0];
		}
		$tb_items[] = array (
		_shn_rms_get_itemname($req_item),
		$res->fields['quantity'],
		$fulfiled,
		_shn_rms_get_priorityname($res->fields['pri_uuid'])
		);
	}
	$th_items[] = array (_t("Item"), _t("Quantity"), _t("Fulfiled Quantity"), _t("Item Priority"));
	print '<h4>' . _t("Requested Item") . '</h4>';
	shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	print '<br />';
}

function _shn_rms_view_reqitems($req_id)
{
	global $global;

	$rms_items = _shn_rms_get_reqitems($req_id);
	$th_items[] = array (_t("Item"), _t("Quantity"), _t("Fulfiled Quantity"), _t("Item Priority"), _t("Select to fulfill"));
	foreach ($rms_items as $itm)
	{
		$sql = "SELECT SUM(quantity) AS qty FROM rms_fulfil WHERE req_uuid = '$req_id' AND item_uuid = '$itm[0]'";
		$res = $global['db']->Execute($sql);
		//$res = $db->Execute($sql);
		if ($res === false){
			$msg = $global['db']->ErrorMsg();
       		add_error($msg.' <br> '.$sql);
       		display_errors();
		}
		else{
			if($res->RecordCount() > 0){
				$fulfiled = $res->fields['qty'];
			}
			else{
				$fulfiled = 0;
			}
			
		}
		$sel_url = '<a href=index.php?mod=rms&amp;act=mng_ff' .
                        '&amp;seq=sel_plg&amp;req_id=' . $req_id .'&amp;itm_id='.$itm[0].'>' .
                        _t("Select") . '</a>';
		//print_r($itm);
		$tb_items[] = array (
		_shn_rms_get_itemname($itm[0]),
		$itm[1] . " " . _shn_rms_get_iunit_name($itm[4]) . "",
		$fulfiled,
		_shn_rms_get_priorityname($itm[2]),
		$sel_url
		);
	}

	print '<h4>' . _t("Request Items") . '</h4>';
	shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	print '<br />';

}
function _shn_rms_view_reqff($req_id)
{
	global $global;
	$rms_items = array();

	// @TODO: check compatibility of the sql statement
	$sql = "SELECT req.req_uuid AS req_uuid, req.unit AS unit, req.item_uuid AS item_uuid, " .
                "req.pri_uuid AS pri_uuid, " .
                "ff.plg_uuid AS plg_uuid, req.quantity AS req_qty, " .
                "ff.quantity AS ff_qty, ff.ff_date AS ff_date " .
           "FROM rms_req_item req LEFT JOIN rms_fulfil ff " .
           "ON ff.item_uuid=req.item_uuid " .
           "AND req.req_uuid=ff.req_uuid " .
           "WHERE req.req_uuid='$req_id'";
           
    $extra_opt=array('return'=>true, 'post'=>true);
	//$rs=shn_paging_get_report($sql,5,$headers=NULL,$extra_opt);
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	elseif (1 <= $rs->RecordCount())
	{
		$rs = $rs->GetArray();
		$rms_items = $rs;
	}
	else
	{
		return false;
	}

	$th_items[] = array (_t("Item"), _t("Priority"), _t("Fulfiled"), _t("Date"));
	foreach ($rms_items as $itm)
	{
		$sel_url = '<a href=index.php?mod=rms&amp;act=mng_ff' .
                    '&amp;seq=sel_plg' .
                    '&amp;req_id=' . $req_id .
                    '&amp;itm_id=' . $itm['item_uuid'] .'>' .
		_t("Select") . '</a>';
		$tb_items[] = array (
		_shn_rms_get_itemname($itm['item_uuid']),
		_shn_rms_get_priorityname($itm['pri_uuid']),
		$itm['ff_qty'],
		$itm['ff_date']
		//$sel_url
		);
	}

	print '<h4>' . _t("Request Fulfilment Status") . '</h4>';
	shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	print '<br />';
}
function _shn_rms_view_request($req_id)
{
	$request = _shn_rms_get_request($req_id);
	if (!$request)
	return false;
	$date = $request['date'];
	$status = $request['status'];
	$shn_usr = $request['user_id'];
	
	$_SESSION['rms_ls_reqstr']=$request['reqstr_uuid'];

	//print '<h3>' . _t("The Request ID: ") . $req_id . '</h3>';
	//print '<br />';
	_shn_rms_view_requester($request['reqstr_uuid']);
	//print '<br />';
	_shn_rms_view_location($request['loc_uuid']);
	print '<br />';
	_shn_rms_view_reqitems($req_id);
	print '<br />';
	_shn_rms_view_reqff($req_id);
}
function _shn_rms_view_plgitems($plg_id)
{
	global $global;

	$rms_items = _shn_rms_get_plgitems($plg_id);
	$th_items[] = array (_t("Item"), _t("Quantity"));
	foreach ($rms_items as $itm)
	{
		$tb_items[] = array (
		_shn_rms_get_itemname($itm[0]),
		$itm[1] . " " . _shn_rms_get_iunit_name($itm[4]) . ""
		);
	}

	print '<h4>' . _t("Pledge Items") . '</h4>';
	shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
	print '<br />';

}
function _shn_rms_view_pledge($plg_id)
{
	$pledge = _shn_rms_get_pledge($plg_id);
	$date = $pledge['date'];
	$status = $pledge['status'];
	$shn_usr = $pledge['user_id'];

	//print '<h3>' . _t("The Pledge ID: ") . $plg_id . '</h3>';
	//print '<br />';
	_shn_rms_view_donor($pledge['donor_uuid']);
	print '<br />';
	_shn_rms_view_plgitems($plg_id);
}
function _shn_rms_request_setstat($req_id, $stat)
{
	global $global;

	$sql = "UPDATE rms_request SET status='$stat' WHERE req_uuid='$req_id'";
	$insert_array['req_uuid'] = $req_id;
	$insert_array['status_date'] = date('Y-m-d');
	//print 'testaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa';
	$q = "SELECT req_uuid FROM rms_request_status_date WHERE req_uuid='$req_id'";
	$rset = $global['db']->Execute($q);
	if($rset->RecordCount()==0)
	{
		$res = $global['db']->AutoExecute('rms_request_status_date', $insert_array, 'INSERT');
		//print $res;
	}
	else
	{
		$res = $global['db']->AutoExecute('rms_request_status_date', $insert_array, 'UPDATE', "req_uuid = '".$req_id."'");
		//print $res;
	}
	

	if ($global['db']->Execute($sql) === false || $res===false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else
	{
		return true;
	}
}
function _shn_rms_pledge_setstat($plg_id, $stat)
{
	global $global;

	$sql = "UPDATE rms_pledge SET status='$stat' WHERE plg_uuid='$plg_id'";

	if ($global['db']->Execute($sql) === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else
	{   
		$sql = "UPDATE rms_plg_item SET status='$stat' WHERE plg_uuid='$plg_id'";
		
		if ($global['db']->Execute($sql)===false) {
			$msg = $global['db']->ErrorMsg();
		    add_error($msg . '<br />' . $sql);
		    display_errors();
		    return false;
		}else {
			return true;
		}
	}
}

/**
 * 
 * Generates the java script required for AJAX functionality
 *
 * @param mixed $to
 * @access public
 * @return void
 */
function _shn_rms_ct_cat_js($max,$form,$change,$item_flag=false){
	global $global;
	$fetch_server="index.php?";
	?>
<script type="text/javascript">
    var url = "<?php echo $fetch_server?>"; 
       var curlevel=0;
     var http;
     var null_data;
      var max=<?php echo $max ?>;
    function getHTTPObject() {
        var xmlhttp;
        //conditional compliation
        /*@cc_on
        @if (@_jscript_version >= 5)
            try {
                xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
            } catch (e) {
                try {
                    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                } catch (E) {
                    xmlhttp = false;
                }
            }
        @else
            xmlhttp = false;
        @end @*/

        if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
            try {
                xmlhttp = new XMLHttpRequest();
            } catch (e) {
            xmlhttp = false;
            }
        }
    return xmlhttp;
    }

    // The callback funtion
    function handleHttpResponse(){
        if (http.readyState == 4) { // Split the comma delimited response into an array  
                results = http.responseText.split(",");
            if (results[0]!="null"){
                    null_data=false;
                    curlevel=curlevel+1;
                     var x=document.getElementsByName(curlevel);
                     x[0].style.visibility='visible';
                    j=0;
                 var x=document.getElementsByName(curlevel);
                for (i=0; i<=x[0].options.length+1; i++){
                        x[0].options[0]=null;
                    }
                    for (i=1; i<results.length-1; i=i+2, j++){
                         opt = document.createElement("option") ;
                          opt.value = results[i] ;
                          opt.text = results[i+1].replace(/[^A-Za-z]$/,"");
                          x[0].options[j] = opt;
                        x[0].selectedIndex=-1;
                    }
                }else{
                    null_data=true;
                }

            for (i=max; i>curlevel; i=i-1){
                 var x=document.getElementsByName(i);
                 x[0].style.visibility='hidden';
                 
             }
       
        } 
    }

    function update_next_level(selection,level){
         curlevel=level;
    var item_flag = "<?php echo $item_flag?>"; 
        http = getHTTPObject();
        var url2=url + "act=sub_cat&mod=xst&stream=text&cat=" + selection+"&flag="+item_flag;
          http.open("GET", url2, true); 
//        http.onreadystatechange = null; 
        http.onreadystatechange = function(){}; 
        http.onreadystatechange = handleHttpResponse; 
        http.send(null);
    }
    
           function set_name_submit()
    {
            var name="";
            var element="";
            var last_lvl;
            if(null_data==true){
                last_lvl= curlevel+1 ;
            } else{
                last_lvl= curlevel;
            }
            for(i=0;i<last_lvl;i++){
                    element="\""+i+"\"";
                var x=document.getElementsByName(i);
                if(i+1==last_lvl){
                    name=name+x[0].options[x[0].selectedIndex].text;
                }else{
                    name=name+x[0].options[x[0].selectedIndex].text+"->";
                }
        }
        
        var x=document.getElementsByName("<?php echo $change?>");
        x[0].value=name;
        document.<?php echo $form;?>.submit();
        return;
    }
    
     var x=document.getElementsByName(0);
     x[0].selectedIndex=-1;
    for (i=max; i>0; i=i-1){
            var x=document.getElementsByName(i);
        x[0].style.visibility='hidden';
    }
    

</script>
	<?php
}
/**
 * shn_location
 * Generates a set of select boxes with locations with in the given levels. Will add to the form.
 * @param mixed $from
 * @param mixed $to
 * @access public
 * @return void
 */
function _shn_rms_ct_cat($max,$form,$item_flag=false)
{

	$parent_array=array();

	global $global;
	$db=$global["db"];

	if($item_flag==true)
	{
		$query="SELECT name,ct_uuid FROM ct_catalogue WHERE parentid='0' AND final_flag='0' ";
		$res=$db->Execute($query);
	}
	else
	{
		$query="SELECT name,ct_uuid FROM ct_catalogue WHERE parentid='0' ";
		$res=$db->Execute($query);
	}

	while(!$res==NULL && !$res->EOF)
	{
		$parent_array[$res->fields["ct_uuid"]]=$res->fields["name"];
		$res->MoveNext();
	}

	if($parent_array==null){
		$parent_array["1"]=_t("None");
		shn_form_fsopen(_t('Information'));
		?>
<p><?= _t('There is no any root catalogue found. '); ?><a
	href="index.php?mod=cs&act=addmain">Add root Catalogue</a><?= _t(' First'); ?></p>

		<?php
		shn_form_fsclose();
}

else{
	shn_form_fsopen(_t("Select the root Category"));
	$select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,0)';
	shn_form_select($parent_array,'',0,$select_opts,null);
	shn_form_fsclose();
	shn_form_fsopen(_t('Select the sub category'));
	for($i=1;$i<$max+1;$i++){
		$select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,'.$i.') visible="false"';
		shn_form_select(null,'',$i,$select_opts,null);
	}
	_shn_rms_ct_cat_js($max,$form,"item_name",$item_flag);
	shn_form_hidden(array('item_name'=>""));
	//_shn_cs_item_name_javascript("item_name",$max,$form);
	//shn_form_button(_t("Next"),"onClick='set_name_submit()'");
	shn_form_fsclose();

	//shn_form_submit(_t("Next"));
}
}
function _shn_rms_get_location_name($bsd_village)
{
	global $global;
	$db=$global['db'];

	$string_array=array();
	$i=0;

	while($bsd_village!=NULL)
	{
		$sql2="SELECT * FROM location WHERE loc_uuid='$bsd_village'";
		$ims2=$db->Execute($sql2);
		//print $sql2;
		$parent_id=$ims2->fields['parent_id'];
		$name=$ims2->fields['name'];
		//array_push($string_array,$location_id=>$name);
		$string_array[$i]=$name;
		//print_r($string_array[$i]);
		$i=$i+1;

		$bsd_village=$parent_id;
	}

	for($j=$i-2;$j>=0;$j--)
	{
		//print $string_array[$j];
		//print "\n";
		$string=$string_array[$j];
		if($j==$i-2)
		{
			$location=$string;
		}
		else
		{
			$location=$location."->".$string;
		}

	}

	return $location;


}
function _shn_rms_check_catalog_item($itm)
{
	global $global;
	$db=$global['db'];

	$sql="SELECT * FROM ct_catalogue WHERE parentid='$itm';";
	$res=$db->Execute($sql);
	//print $sql;
	if(!$res->EOF)
	{
		return true;
	}
	else
	{
		return false;
	}
}

function _shn_rms_requester_add_new_loc_t()
{
    global $global;
    $location_id = shn_location_get_form_submit_loc(); 
    $p_uuid = $_SESSION['rms_reqstr_id'];
    /*if($_POST['camps'] != 0 || $_POST['orgs'] != 0){
    	$location_id = ($_POST['camps'] != 0)?$_POST['camps'] : $_POST['orgs'];*/
    	if(_shn_rms_requester_search_loc_t($location_id,$p_uuid)) { //if location already exists
    		add_error(_t("Location already exists"));
    	}else {
	
    		$sql = "INSERT INTO ext_location( " .
                                           "p_uuid, " .
                                           "loc_uuid) " .
            	"VALUES ('$p_uuid', '$location_id')";
    
    		if($global['db']->Execute($sql) === false) {
        		$msg = $global['db']->ErrorMsg();
        		add_error($msg . '<br />' . $sql);
        		display_errors();
        		return false;
    		}else {
    			add_confirmation(_t("Location added successfully"));
        		return true;
    		}
    	}
/*
    }
    else{
    
    	if(isset($_POST['loc_select_1'])==true && strlen($_POST['loc_select_1'])>0 && $_POST['loc_select_1']!="0") { //if a location is selected

    		$lvl=1;
    		$range= shn_get_range();
    		while ($lvl!=($range["end"])+1) {
    			$var1='rms_'.$lvl;
    			$var2='loc_select_'.$lvl;
    	    	$_SESSION[$var1]=$_POST[$var2];
    	    	$lvl++;
    		}
        
     		$location_id=_shn_rms_get_locid($range["end"]);
        	if(_shn_rms_requester_search_loc_t($location_id,$p_uuid)) { //if location already exists
    			add_error(_t("Location already exists"));
    		}else {
	
    			$sql = "INSERT INTO ext_location( " .
                                           "p_uuid, " .
                                           "loc_uuid) " .
            		"VALUES ('$p_uuid', '$location_id')";
    
    			if($global['db']->Execute($sql) === false) {
        			$msg = $global['db']->ErrorMsg();
        			add_error($msg . '<br />' . $sql);
        			display_errors();
        			return false;
    			}else {
    				add_confirmation(_t("Location added successfully"));
        			return true;
    			}
    		}
    //------------------ORG---------------------------------------------------------
    //if an organization is selected, but it does not belong to any location
    	}elseif((isset($_POST['loc_select_1'])==false || strlen($_POST['loc_select_1'])<0 || $_POST['loc_select_1']=="0") && $_POST['loc']=='loc_org' && (isset($_POST['orgs'])==true && strlen($_POST['orgs'])>0 && $_POST['orgs']!="0")){
        	$location_id= $_POST['orgs'];
        	if(_shn_rms_requester_search_loc_t($location_id,$p_uuid)) {
    			add_error(_t("Location already exists"));
    		}else{
    			$sql = "INSERT INTO ext_location( " .
                                           "p_uuid, " .
                                           "loc_uuid) " .
            		"VALUES ('$p_uuid', '$location_id')";
    
    			if($global['db']->Execute($sql) === false) {
        			$msg = $global['db']->ErrorMsg();
        			add_error($msg . '<br />' . $sql);
        			display_errors();
        			return false;
    			}else {
    				add_confirmation(_t("Location added successfully"));
        			return true;
    			}
    		}
    //------------------camp--------------------------------------------------------
    //if a camp is selected, but it does not belong to any location		
    	}elseif((isset($_POST['loc_select_1'])==false || strlen($_POST['loc_select_1'])<0 || $_POST['loc_select_1']=="0") && $_POST['loc']=='loc_camp' && (isset($_POST['camps'])==true && strlen($_POST['camps'])>0 && $_POST['camps']!="0")) {
    		$location_id= $_POST['camps'];
        	if(_shn_rms_requester_search_loc_t($location_id,$p_uuid)) {
    			add_error(_t("Location already exists"));
    		}else{
    			$sql = "INSERT INTO ext_location( " .
                                           "p_uuid, " .
                                           "loc_uuid) " .
            		"VALUES ('$p_uuid', '$location_id')";
    
    			if($global['db']->Execute($sql) === false) {
        			$msg = $global['db']->ErrorMsg();
        			add_error($msg . '<br />' . $sql);
        			display_errors();
        			return false;
    			}else {
    				add_confirmation(_t("Location added successfully"));
        			return true;
    			}
    		}
    
    //-------else-------------------------------------------------------	
    	}else{ //if any location or camp or organization is not selected..
    		add_warning(_t("Select the location first"));
    	}
   	}*/
}



function _shn_rms_requester_search_loc_t($loc_id,$p_uuid)
{
	global $global;

	$sql = "SELECT loc_uuid FROM ext_location WHERE loc_uuid ='$loc_id' AND p_uuid='$p_uuid'";
	$rec = $global['db']->Execute($sql);

	if ($rec->EOF)
	{
		return false;
	}else{
		return true;
	}
}
function _shn_rms_display_location_array($loc)
{
	$locations_array=array();

	//$bsda_village = array();

	shn_form_fopen("req_new",null,array('req_message'=>false,'anchor'=>'items'));
	$info=_t("Select a location where the request is related.")."<br />";
	$info.=_t("If you want to make the request for a new location, add the location first.")."<br />";
	?>
<div class="info"><?php echo $info;?></div>
<br />
	<?

	shn_form_hidden(array('seq'=>'get_loc'));
	shn_form_fsopen(_t("Existing Location"));
    //============================New==================================
    foreach($loc as $loc_id) {
    $loc_obj = new Location();
/*
        if(_shn_rms_is_location($loc_id)) {
            $bsda_village = _shn_org_location_string($loc_id);
        }elseif(_shn_rms_is_camp($loc_id)) {;
            $bsda_village = _shn_rms_get_camp_name($loc_id);
        }elseif(_shn_rms_is_org($loc_id)) {
        	$bsda_village = _shn_rms_get_org_name($loc_id);
        }*/
        $bsda_village = $loc_obj->get_record($loc_id);
        $bsda_village = $bsda_village['name'];
        $locations_array[$loc_id]= $bsda_village;
    }
    //====================old=======================================
//	foreach($loc as $loc_id)
//	{
//		$bsda_village = _shn_org_location_string($loc_id);   //return the location
//		$locations_array[$loc_id]= $bsda_village;
//	}
    //=========================================================================

	shn_form_select($locations_array,_t("Location"), 'loc');

	shn_form_fsclose();
	shn_form_submit(_t("Next"));
	print '<br />';
	print '<br />';

	shn_form_fclose();
}

/**
 * return location array
 * fro
 */
function _shn_rms_get_location_array($p_id)
{
	global $global;
	$db = $global['db'];

	$sql = "SELECT DISTINCT loc_uuid FROM ext_location WHERE p_uuid='$p_id'";

	$rec = $db->Execute($sql);
	$loc =array();
	$i = 0;
	if ($rec === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	} elseif (1 <= $rec->RecordCount()){
		While(!$rec->EOF)
		{

			$loc[$i] = $rec->fields['loc_uuid'];
			$rec->MoveNext();
			$i++;
		}

		return $loc;
	}
}
/**
 * To get all excisting locations from ext_location table 
 */
function _shn_rms_get_all_locations()
{
    global $global;
	$db = $global['db'];

	$sql = "SELECT DISTINCT loc_uuid FROM ext_location";

	$rec = $db->Execute($sql);
	$loc =array();
	$i = 0;
	if ($rec === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	} elseif (1 <= $rec->RecordCount()){
		While(!$rec->EOF)
		{

			$loc[$i] = $rec->fields['loc_uuid'];
			$rec->MoveNext();
			$i++;
		}

		return $loc;
	}
}
/**
 * Get the Location name instead of location string
 * From ext_location table
 */
function _shn_rms_location_string($loc)
{
    global $global;
    $db=$global["db"];

    $q="SELECT name FROM location WHERE loc_uuid='$loc'";
    $res=$db->Execute($q);
    if(res==null) { 
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false; 
    }else{
        $location=$location.$res->Fields("name");
        return $location;
    }
}
/**
 * check 'group_id' of logged user from 'sys_user_to_group' table;
 * 
 * whether user is admin of RMS;
 */
function _shn_rms_get_user_group()
{
	global $global;
	$id=$_SESSION['user_id'];
	$gid=1; 				//according to the user roles.. of user groups..
	$db=$global["db"];
	$sql="SELECT * FROM sys_user_to_group WHERE p_uuid='$id' AND group_id='$gid'";
	$rs=$db->Execute($sql);
	
	//if you want to check for a different user group, just change the following number according to the group
	//this will affect to the req_sch and plg_sch.
	
	if(1 <=$rs->RecordCount()) {
        return true;
	}elseif($rs===false) {
	$msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
		
	}else{
		return false;
	}
}

/**
 * function to get the category, for a particular item.
 * 
 */
function _shn_rms_get_parent_catalogue($item_id)
{
	global $global;	
	$db=$global['db'];

//	if($item_id == '0')
//	{
//		//return $item_id.'eliye';
//		return $item_id.'eliye';
//	}
	//else
	//{
	  while($item_id != '0')
	  {
   	    $q="SELECT * FROM ct_catalogue WHERE ct_uuid='$item_id'";
        $res_temp=$db->Execute($q);
	      
         if ($rs === false)
           {
            $msg = $global['db']->ErrorMsg();
            add_error($msg . '<br />' . $sql);
            display_errors();
            return false;
           }
    
        $parent_id = $res_temp->fields['parentid'];
        if($parent_id=='0')
        {
           return $item_id;}
        //echo $parent_id;
        else
        {
          $item_id = $parent_id;
        }
        //echo $item_id.'while';
	 // }
      
	}
    //_shn_rms_get_parent_catalogue($res_temp->fields['parentid'],$cat_arr);
}
/**
 *  
 */
function _shn_rms_get_cataloguename($item_id)
{
	global $global;
	$db=$global['db'];
	$sql = "SELECT name FROM ct_catalogue WHERE ct_uuid='$item_id'";
	$rec = $db->Execute($sql);
    
    if ($rec === false)
	 {
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	  }
	 elseif (0 <= $rec->RecordCount())
	 {
	 	$rec = $rec->GetArray();
	 	return $rec[0][0];
	 }
    
	return false;
}

/**
 * return the name according to the given item id
 *
 * @param unknown_type $item_id
 * @return unknown
 */
function _shn_rms_get_cat_name($item_id)
{
	global $global;
	$db=$global['db'];
	$sql = "SELECT name FROM ct_catalogue WHERE ct_uuid='$item_id'";
	$rec = $db->Execute($sql);
    
    if ($rec === false)
	 {
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	  }
	  else{
	  	$res=$rec->fields["name"];
	  	return $res;
	  }
	return false;
}

/**
 * is_user
 *
 * @param unknown_type $id
 * @return unknown
 */
function _shn_rms_is_user($id)
{
    global $global;
    
    $sql = "SELECT * FROM person_uuid WHERE p_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    { 
            $msg = $global['db']->ErrorMsg();
            add_error($msg . '<br />' . $sql);
            display_errors();
            return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return true;
    }
    
    return false;
}
/**
 * Check whether there is a location, according to the given id
 * 
 */
function _shn_rms_is_location($id)
{
    global $global;
    
    $sql = "SELECT * FROM location WHERE loc_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return true;
    }
    
    return false;	
}
/**
 * Check whether there is a camp, according to the given id
 */
function _shn_rms_is_camp($id)
{
	global $global;
    
    $sql = "SELECT * FROM camp_general WHERE c_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return true;
    }
    
    return false;
}
/**
 * Check whether there is an organization, according to the given id
 */
function _shn_rms_is_org($id)
{
	global $global;
    
    $sql = "SELECT * FROM org_main WHERE o_uuid='$id'";
    $rs = $global['db']->Execute($sql);
    
    if ($rs === false)
    {
        $msg = $global['db']->ErrorMsg();
        add_error($msg . '<br />' . $sql);
        display_errors();
        return false;
    }
    elseif (1 <= $rs->RecordCount())
    {
        return true;
    }
    
    return false;
}
/**
 * To get inventory name according to the given id;
 */
function _shn_rms_get_inventory_name($inv_uuid)
{
    global $global;

	$sql = "SELECT * FROM ims_inventory_records WHERE inv_uuid='$inv_uuid'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else
	{
		$name=$rs->fields['inventory_name'];
		return $name;
	}
}

/**
 * get the camp name according to a given id
 * from camp_general table
 */
function _shn_rms_get_camp_name($id)
{
    global $global;

	$sql = "SELECT * FROM camp_general WHERE c_uuid='$id'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else
	{
		$name=$rs->fields['name'];
		return $name;
	}
}

/**
 * get the organization name according to the given id
 * from org_main table
 */
function _shn_rms_get_org_name($id)
{
    global $global;

	$sql = "SELECT * FROM org_main WHERE o_uuid='$id'";
	$rs = $global['db']->Execute($sql);

	if ($rs === false)
	{
		$msg = $global['db']->ErrorMsg();
		add_error($msg . '<br />' . $sql);
		display_errors();
		return false;
	}
	else
	{
		$name=$rs->fields['name'];
		return $name;
	}
}

/**
 * return the name of the location,camp or orgaosation according to the given id
 */
function _shn_rms_get_name($loc)
{
	if(_shn_rms_is_location($loc)) {
    	$bsda_village = _shn_rms_get_location_name($loc);
    }elseif(_shn_rms_is_camp($loc)) {
        $bsda_village = _shn_rms_get_camp_name($loc);
    }elseif(_shn_rms_is_org($loc)) {
        $bsda_village = _shn_rms_get_org_name($loc);
    }
    return $bsda_village;
}

/**
 * return the lowest level id of the location
 */
function _shn_rms_get_locid($range_end)
{	
	for($range_end; $range_end>0; $range_end--) {
		$var='rms_'.$range_end;
	    if($_SESSION[$var]!=null && $_SESSION[$var]!="0")
		    return $_SESSION[$var];
	}
}

?>
