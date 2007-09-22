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

/**
 * Search by address
 */
function _shn_cr_srch_rst_address($camp_name,$type='all'){
	global $global;
	$db=$global['db'];
?>
	<h1><?php echo _("Search Results")?></h1>
	<div id ="result">
	<table>
        <thead>
        	<td><?php echo _("Shelter Name")?></td>
            <td><?php echo _("Location")?></td>
            <td><?php echo _("Address")?></td>
         	<td><?php echo _("Shelter Type")?></td>
            <td><?php echo _("Total Count")?></td>
            <td><?php echo _("Capacity")?></td>
        </thead>
        <tbody>
<?php
       	if($_REQUEST['edt']=='true')
			$edt=true;
		
		// Specific Type search
			
		$query = " select cg.name,cg.address,loc.name as loc_name," .
				" total,capacity from camp_general as cg, camp_reg as cr,location as loc " .
				"where cg.c_uuid=cr.c_uuid AND cg.location_id=loc.loc_uuid " .
				((null==$camp_name)?"":" AND cg.address LIKE '%{$camp_name}%' ") ;
		//echo "q=".$query;
				
		$res_cmp =$db->Execute($query);   
		while (!$res_cmp->EOF){ 					
?> 
			<tr>
			<td><a href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $res_cmp->fields['name']?>">
<?php echo $res_cmp->fields['name']?>&nbsp;</a><?php if($edt)?>
<a href="index.php?mod=cr&act=ecmp&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _("edit")?>]</a>
<a href="index.php?mod=cr&act=eppl&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _("eplcnt")?>]</a>
<a href="index.php?mod=cr&act=ebed&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _("ebdcnt")?>]</a>




<?php ;?></td>
  					<td><?php echo $res_cmp->fields['loc_name']?></td>
  					<td><?php echo $res_cmp->fields['address']?></td>
  					<td><?php echo "All"?></td>
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
?>
	<h1><?php echo _("Search Results")?></h1>
	<div id ="result">
	<table>
        <thead>
        	<td><?php echo _("{$conf['mod_cr_alt']} Name")?></td>
            <td><?php echo _("Location")?></td>
            <td><?php echo _("Address")?></td>
         	<td><?php echo _("{$conf['mod_cr_alt']} Type")?></td>
            <td><?php echo _("Total Count")?></td>
            <td><?php echo _("Capacity")?></td>
        </thead>
        <tbody>
<?php
       	if($_REQUEST['edt']=='true')
			$edt=true;
		
		// Specific Type search
			
		$query = " select cg.name,cg.address,loc.name as loc_name," .
				 " option_description, ".
				 " total,capacity from camp_general as cg, camp_reg as cr,location as loc " .
				 ", field_options as fo " .
				 " where cg.c_uuid=cr.c_uuid AND cg.location_id=loc.loc_uuid " .
				(($type=="all")?"":" AND option_code='{$type}' ") .
				 " AND field_name='opt_camp_type' " .
				 " AND opt_camp_type=fo.option_code " .
				((null==$camp_name)?"":" AND cg.name LIKE '%{$camp_name}%' ") ;
				
		$res_cmp =$db->Execute($query);   
		while (!$res_cmp->EOF){ 					
?> 
			<tr>
			<td><a href="index.php?mod=cr&act=ecmp&seq=view&cmp_id=<?php echo $res_cmp->fields['name']?>">
<?php echo $res_cmp->fields['name']?>&nbsp;</a><?php if($edt)?>
<a href="index.php?mod=cr&act=ecmp&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _("edit")?>]</a>

<?php //Removing hospital functionality from search?>
<!--<a href="index.php?mod=cr&act=eppl&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _("eplcnt")?>]</a>
<a href="index.php?mod=cr&act=ebed&seq=disp&cmp_id=<?php echo $res_cmp->fields['name']?>">[<?php echo _("ebdcnt")?>]</a>-->




<?php ;?></td>
  					<td><?php echo $res_cmp->fields['loc_name']?></td>
  					<td><?php echo $res_cmp->fields['address']?></td>
  					<td><?php echo (($type=="all")?"All": "{$res_cmp->fields['option_description']}")?></td>
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
	<h1><?=_("Search for {$conf['mod_cr_alt']} by Name")?></h1>
<?php
	shn_form_fopen("srch",null,array('req_message'=>false));
	shn_form_fsopen(_("Search"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_text(_("Name of {$conf['mod_cr_alt']}"),'cmp_id','size="30"');
   	shn_form_opt_select("opt_camp_type",_("{$conf['mod_cr_alt']} Type"),null,array('all'=>true));
   	//set edit functionality in result
   	if($edit)
	 	shn_form_hidden(array('edt'=>'true'));
   	shn_form_fsclose();
 	shn_form_submit(_("Search"));
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
	<h1><?=_("Search {$conf['mod_cr_alt']} by Address")?></h1>
<?php
	shn_form_fopen("srch_address",null,array('req_message'=>false));
	shn_form_fsopen(_("Search"));
	shn_form_hidden(array('seq'=>'commit'));
	shn_form_text(_($conf['mod_cr_alt']." Address "),'cmp_id','size="40"');
   	if($edit=='true')
   		shn_form_hidden(array('edt'=>'true'));
	shn_form_submit(_("Search"));
	shn_form_fclose();
}



?>

