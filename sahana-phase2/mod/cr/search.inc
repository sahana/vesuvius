<?php

/**Search functinalities for CR
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author   Mifan Careem <mifan@opensource.lk>
 * @author   Chathra Hendehewa <chathra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 *
 * @patch author: isuru@opensource.lk
 * @patch author:
 */

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_paging.inc');

/**
 * Search by address
 */
function _shn_cr_srch_rst_address($camp_name,$type='all'){
	global $global;
	$db=$global['db'];
	
	if($_REQUEST['edt']=='true')
	$edt=true;

	// Specific Type search

	$query = " select cg.c_uuid,cg.name,cg.address,cg.location_id," .
				" total,capacity from camp_general as cg, camp_reg as cr " .
				"where cg.c_uuid=cr.c_uuid " .
	((null==$camp_name)?"":" AND cg.address LIKE '%{$camp_name}%' ") ;
	//echo "q=".$query;

// 	$res_cmp =$db->Execute($query);
?>
<h1><?php echo _t("Search Results")?></h1>
<?php
        $res_cmp = shn_paging_get_report($query,10,null,array('post'=>true));
	?>

<div id="result">
<table>
	<thead>
		<td><?php echo _t("Shelter Name")?></td>
		<td><?php echo _t("Location")?></td>
		<td><?php echo _t("Address")?></td>
		<td><?php echo _t("Shelter Type")?></td>
		<td><?php echo _t("Total Count")?></td>
		<td><?php echo _t("Capacity")?></td>
	</thead>
	<tbody>
	<?php
	while (!$res_cmp->EOF){
		$location_name = "";
		$loc_uuid = $res_cmp->Fields('location_id');
		if($loc_uuid != '-1'){
			$sub_query = "SELECT loc.name AS loc_name FROM location AS loc WHERE loc.loc_uuid='".$loc_uuid."'";
			$sub_res = $db->Execute($sub_query);
			if(!$sub_res->EOF){
				$sub_res->MoveFirst();
			}
			$location_name = $sub_res->fields['loc_name'];
		}
		?>
		<tr>
			<td><a
				href="index.php?mod=cr&amp;act=ecmp&amp;seq=view&amp;cmp_id=<?php echo $res_cmp->fields['c_uuid']?>">
				<?php echo $res_cmp->fields['name']?>&nbsp;</a><?php if($edt)?> <a
				href="index.php?mod=cr&amp;act=ecmp&amp;seq=disp&amp;cmp_id=<?php echo $res_cmp->fields['c_uuid']?>">[<?php echo _t("edit")?>]</a>
			<a
				href="index.php?mod=cr&amp;act=eppl&amp;seq=disp&amp;cmp_id=<?php echo $res_cmp->fields['c_uuid']?>">[<?php echo _t("edit people count")?>]</a>

<!-- 			<a -->
<!-- 				href="index.php?mod=cr&act=ebed&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _t("ebdcnt")?>]</a> -->




				<?php ;?></td>
			<td><?php echo $location_name?></td>
			<td><?php echo $res_cmp->fields['address']?></td>
			<td><?php echo _t("All")?></td>
			<td><?php echo $res_cmp->fields['total']?></td>
			<td><?php echo $res_cmp->fields['capacity']?></td>
		</tr>
		<?php
		$res_cmp->MoveNext();
}

?>
	</tbody>
</table>
</div>
<?php
}

/**
 * Display Search by name results
 * Does 'Like' search
 * @access private
 * @param mixed $camp_name Camp Name
 * @param mixed $type Camp type or All types
 */
function _shn_cr_srch_rst($camp_name,$type){
	global $global;
	global $conf;
	$db=$global['db'];
	//$db->debug=true;
	
	if($_REQUEST['edt']=='true')
	$edt=true;

	// Specific Type search

	$query = " select cg.c_uuid,cg.name,cg.address,cg.location_id," .
				 " option_description, ".
				 " total,capacity from camp_general as cg, camp_reg as cr " .
				 ", field_options as fo " .
				 " where cg.c_uuid=cr.c_uuid " .
	(($type=="all")?"":" AND option_code='{$type}' ") .
				 " AND field_name='opt_camp_type' " .
				 " AND opt_camp_type=fo.option_code " .
	((null==$camp_name)?"":" AND cg.name LIKE '%{$camp_name}%' ") ;

	//$res_cmp =$db->Execute($query);
	?>
	<h1><?php echo _t("Search Results")?></h1>
	<?php
        $res_cmp = shn_paging_get_report($query,10,null,array('post'=>true));
	?>

<div id="result">
<table>
	<thead>
		<td><?php echo _t("Shelter Name")?></td>
		<td><?php echo _t("Location")?></td>
		<td><?php echo _t("Address")?></td>
		<td><?php echo _t("Shelter Type")?></td>
		<td><?php echo _t("Total Count")?></td>
		<td><?php echo _t("Capacity")?></td>
	</thead>
	<tbody>
	<?php
	while (!$res_cmp->EOF){
		$location_name = "";
		$loc_uuid = $res_cmp->Fields('location_id');
		if($loc_uuid != '-1'){
			$sub_query = "SELECT loc.name AS loc_name FROM location AS loc WHERE loc.loc_uuid='".$loc_uuid."'";
			$sub_res = $db->Execute($sub_query);
			if(!$sub_res->EOF){
				$sub_res->MoveFirst();
			}
			$location_name = $sub_res->fields['loc_name'];
		}
		?>
		<tr>
			<td><a
				href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $res_cmp->fields['c_uuid']?>">
				<?php echo $res_cmp->fields['name']?>&nbsp;</a><?php if($edt)?> <a
				href="index.php?mod=cr&act=ecmp&seq=disp&cmp_id=<?php echo $res_cmp->fields['c_uuid']?>">[<?php echo _t("edit")?>]</a>

				<?php //Removing hospital functionality from search?> <!--<a href="index.php?mod=cr&act=eppl&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _t("eplcnt")?>]</a>
<a href="index.php?mod=cr&act=ebed&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _t("ebdcnt")?>]</a>-->




				<?php ;?></td>
			<td><?php echo $location_name?></td>
			<td><?php echo $res_cmp->fields['address']?></td>
			<td><?php /*echo (($type=="all")?"All": "{$res_cmp->fields['option_description']}")*/?>
			<?php echo $res_cmp->fields['option_description']?></td>
			<td><?php echo $res_cmp->fields['total']?></td>
			<td><?php echo $res_cmp->fields['capacity']?></td>
		</tr>
		<?php
		$res_cmp->MoveNext();
}

?>
	</tbody>
</table>
</div>
<?php
}


/**
 * Basic Search form to display search input
 * @access private
 * @return void
 */
function _shn_cr_srch($edit=false){
	global $conf;
	?>
<h1><?php echo _t("Search for {$conf['mod_cr_alt']} by Name")?></h1>
	<?php
	shn_form_fopen("srch",null,array('req_message'=>false));
	shn_form_fsopen(_t("Search"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_text(_t("Name of Shelter"),'cmp_id','size="30"');
	shn_form_opt_select("opt_camp_type",_t("Shelter Type"),null,array('all'=>true));
	//set edit functionality in result
	if($edit)
	shn_form_hidden(array('edt'=>'true'));
	shn_form_fsclose();
	shn_form_submit(_t("Search"));
	shn_form_fclose();
}

/**
 * Basic search by address form
 * @access private
 * @return void
 * @param boolean $edit Controls edit functionality in result page
 */
function _shn_cr_srch_address($edit=false){
	global $conf;
	?>
<h1><?php echo _t("Search Shelter by Address")?></h1>
	<?php
	shn_form_fopen("srch_address",null,array('req_message'=>false));
	shn_form_fsopen(_t("Search"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_text(_t($conf['mod_cr_alt']." Address "),'cmp_id','size="40"');
	if($edit=='true')
	shn_form_hidden(array('edt'=>'true'));
	shn_form_submit(_t("Search"));
	shn_form_fclose();
}



?>

