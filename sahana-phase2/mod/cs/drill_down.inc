<?php
/**
 * Drill Down catalog 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
 
 
	global $global;
	$db=$global['db'];
	$breadcrumb_str = "<a href='index.php?mod=cs&amp;act=drill_down'>"."root"."</a>";
   	?>
  	<h1><?php echo  (_t("Drill down report")) ?></h1>
  	<p><?php echo  _t('Here you are able to view the catalog hierarchy as a drill down report. All the catalogs and sub catalogs which are having child catalogs or items will be displayed as active links.'); ?></p>
  	<?php
 
	if(isset($_REQUEST['id'])) {
		$cat_itm_arr = _shn_cs_get_next_lvl_cats_itms($_REQUEST['id']);
		$in_array = array();
		$parent_id_arr = _shn_cs_recursive_parent_search($in_array,$_REQUEST['id']);
		array_pop($parent_id_arr);
		$parent_id_arr = array_reverse($parent_id_arr);
	
		for($x=0;$x<count($parent_id_arr);$x++)
		{
			$par_id = $parent_id_arr[$x];
    		$query="SELECT * FROM ct_catalogue WHERE ct_uuid ='$par_id'";
    		$res=$db->Execute($query);	
    		
    	   	while(!$res==NULL && !$res->EOF)
		    {
			    $name = $res->fields["name"];
			    $id = $res->fields["ct_uuid"];
			    $breadcrumb_str .= ">>";
				$breadcrumb_str .= "<a href='index.php?mod=cs&amp;act=drill_down&amp;id=".$id."'>".$name."</a>"; 
				
				$res->MoveNext();
		    }
		}
	} else {
		$cat_itm_arr = _shn_cs_get_main_cats();
	}
	
	?>
	<p><?php echo _t("Go to : ")?><?php print $breadcrumb_str; ?></p>
 	<br />
 	<div id="result">
 	<table>
    	<thead>
        	<td><strong><?php echo _t("Name")?></strong></td>
        	<td><strong><?php echo _t("Item/catalog")?></strong></td>
			<td><strong><?php echo _t("Keyword")?></strong></td>
    	</thead>
    	<TBODY>
    	<?php

    		$res = $cat_itm_arr;
    	   	while(!$res==NULL && !$res->EOF) {
		    
		    $name = $res->fields["name"];
		    $description = $res->fields["description"];
		    $cat_id = $res->fields["ct_uuid"];
		    $final_flag = $res->fields["final_flag"];
		    $keyword = $res->fields["keyword"];
		    $parent_ID = $res->fields["parentid"];
		
		    ?>
		    <tr>
		    	<?php
		    		if(_shn_cs_has_next_lvl($cat_id)) {
		    			?>
		    			<td><a href="index.php?mod=cs&amp;act=drill_down&amp;id=<?php echo $cat_id ?>"><?php print $name ;?></a></td>
		    			<?php
		    		} else {
		    			?>
		    			<td><?php print $name ;?></td>
		    			<?php    			
		    		}
		    	?>
		        
		        <?php if($final_flag=='0' && $parent_ID == '0') { ?>
		            <td>&nbsp;&nbsp;<?php print _t("Main catalog") ; ?></td>
		        <?php } elseif($final_flag=='0' && $parent_ID != '0') { ?>
			    <td>&nbsp;&nbsp;<?php print _t("Sub catalog") ; ?></td>
		        <?php } else { ?>
		            <td>&nbsp;&nbsp;<?php print _t("Item"); ?></td>
		        <?php } ?>
		           <td><?php print $keyword ;?></td>
		    </tr>
		    <?php  
		    $res->MoveNext();

    		}//end of while loop	    		
    	?>
    
    	</TBODY>    
	</table>
 	</div>
 	
 	<?php

 
 function _shn_cs_get_main_cats()
 {
	$query = "SELECT * FROM ct_catalogue WHERE parentid ='0'";
	$max_record = intval(_shn_cs_get_max_rec_page());
    $main_cat_arr = shn_paging_get_report($query,$max_record,NULL,array('post'=>false, 'return'=>true));
    
   	return $main_cat_arr;
 }
 
 function _shn_cs_get_next_lvl_cats_itms($parent_id)
 {
 	$query = "SELECT * FROM ct_catalogue WHERE parentid ='$parent_id'";
 	$max_record = intval(_shn_cs_get_max_rec_page());
   	$next_cat_arr = shn_paging_get_report($query,$max_record,NULL,array('post'=>false, 'return'=>true));
    
	return $next_cat_arr;
 }
 
 function _shn_cs_has_next_lvl($id)
 {
    global $global;
    $db = $global['db'];
    $query = "SELECT ct_uuid FROM ct_catalogue WHERE parentid ='$id'";
    $res = $db->Execute($query);
    
    $recs = 0;
    
    while(!$res == NULL && !$res->EOF) {
    	$recs++;
    	$res->MoveNext();
    }

	if($recs == 0) {
		return FALSE;
	} else {
		return TRUE;
	}
 }
 
 /**.
 *This function do a recurcive search to find the parents of a particular catalog/ item
 * @access private
 * @return array
 */
function _shn_cs_recursive_parent_search($in_array,$parent_id_in)
{
    global $global;
    $db = $global['db'];

    if($parent_id_in == '0') {
    	array_push($in_array,$parent_id_in);
    	return $in_array;
    } else {
    	array_push($in_array,$parent_id_in);
    	$query="SELECT parentid FROM ct_catalogue WHERE ct_uuid ='$parent_id_in'";
    	$res=$db->Execute($query);
    	$par_par_id = $res->fields["parentid"];
    	return _shn_cs_recursive_parent_search($in_array,$par_par_id);
    }
}

function _shn_cs_get_max_rec_page()
{
	global $global;
    $db = $global['db'];
    
    $query = "SELECT option_code FROM field_options WHERE field_name='opt_cs_page_record'";
    $res = $db->Execute($query);
    $max_rec = $res->fields["option_code"];	
    
    return $max_rec;
}
 
