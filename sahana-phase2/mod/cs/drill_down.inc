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
 
	if(isset($_REQUEST['id']))
	{
		$cat_itm_arr = _shn_cs_get_next_lvl_cats_itms($_REQUEST['id']);
		$in_array = array();
		$parent_id_arr = _shn_cs_recursive_parent_search($in_array,$_REQUEST['id']);
		array_pop($parent_id_arr);
		$parent_id_arr = array_reverse($parent_id_arr);
		//print_r($parent_id_arr);
		
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
	}
	else
	{
		$cat_itm_arr = _shn_cs_get_main_cats();
	}
  ?>
  <h1><?= (_("Drill down report")) ?></h1>
  <p><?= _('Here you are able to view the catalog hierarchy as a drill down report. All the catalogs and sub catalogs which are having child catalogs or items will be displayed as active links.'); ?></p>
  <?php
  	print "Go to : ".$breadcrumb_str."<br /><br />";
  
 	?>
 	<div id="result">
 	<table>
    	<thead>
        	<td><strong><?=_("Name")?></strong></td>
        	<td><strong><?=_("Item/catalog")?></strong></td>
			<td><strong><?=_("Keyword")?></strong></td>
    	</thead>
    	<TBODY>
    	<?php
    	
    	$count = count($cat_itm_arr);
    	
    	for($x=0;$x<$count;$x++)
    	{
		$itm_cat_id = $cat_itm_arr[$x];
    	$query="SELECT * FROM ct_catalogue WHERE ct_uuid ='$itm_cat_id'";
    	$res=$db->Execute($query);	
    		
    	   	while(!$res==NULL && !$res->EOF)
		    {
		    $name=$res->fields["name"];
		    $description=$res->fields["description"];
		    $cat_id=$res->fields["ct_uuid"];
		    $final_flag=$res->fields["final_flag"];
		    $keyword=$res->fields["keyword"];
		    $parent_ID=$res->fields["parentid"];
		
		    ?>
		    <tr>
		    	<?php
		    		if(_shn_cs_has_next_lvl($cat_id))
		    		{
		    			?>
		    			<td><a href="index.php?mod=cs&amp;act=drill_down&amp;id=<?php echo $cat_id ?>"><?php print $name ;?></a></td>
		    			<?php
		    		}
		    		else
		    		{
		    			?>
		    			<td><?php print $name ;?></td>
		    			<?php    			
		    		}
		    	?>
		    
		    
		        
		        <?php if($final_flag=='0' && $parent_ID == '0') { ?>
		            <td>&nbsp;&nbsp;<?php print "Main catalog" ; ?></td>
		        <?php } elseif($final_flag=='0' && $parent_ID != '0') { ?>
			    <td>&nbsp;&nbsp;<?php print "Sub catalog" ; ?></td>
		        <?php } else { ?>
		            <td>&nbsp;&nbsp;<?php print "Item" ; ?></td>
		        <?php } ?>
		           <td><?php print $keyword ;?></td>
		    </tr>
		    <?php  
		    $res->MoveNext();

	
    		}//end of while loop	    		
    	}// end of for loop
    	
    	?>
    
    
    
    	</TBODY>    
	</table>
 	</div>
 	
 	<?php

 
 function _shn_cs_get_main_cats()
 {
    global $global;
    $db=$global['db'];
    $query="SELECT ct_uuid FROM ct_catalogue WHERE parentid ='0'";
    $res=$db->Execute($query);
    
    $main_cat_id_arr = array();

    while(!$res==NULL && !$res->EOF)
    {
    	array_push($main_cat_id_arr,$res->fields["ct_uuid"]);
    	$res->MoveNext();
    }
    
   return $main_cat_id_arr;
 }
 
 function _shn_cs_get_next_lvl_cats_itms($parent_id)
 {
    global $global;
    $db=$global['db'];
    $query="SELECT ct_uuid FROM ct_catalogue WHERE parentid ='$parent_id'";
    $res=$db->Execute($query);
    
    $next_cat_id_arr = array();

    while(!$res==NULL && !$res->EOF)
    {
    	array_push($next_cat_id_arr,$res->fields["ct_uuid"]);
    	$res->MoveNext();
    }
    
   return $next_cat_id_arr;
 }
 
 function _shn_cs_has_next_lvl($id)
 {
    global $global;
    $db=$global['db'];
    $query="SELECT ct_uuid FROM ct_catalogue WHERE parentid ='$id'";
    $res=$db->Execute($query);
    
    $recs = 0;
    
    while(!$res==NULL && !$res->EOF)
    {
    	$recs++;
    	$res->MoveNext();
    }

	if($recs == 0)
	{
		return FALSE;
	}
	else
	{
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
    $db=$global['db'];

    if($parent_id_in == '0')
    {
    	array_push($in_array,$parent_id_in);
    	return $in_array;
    }
    else
    {
    	array_push($in_array,$parent_id_in);
    	$query="SELECT parentid FROM ct_catalogue WHERE ct_uuid ='$parent_id_in'";
    	$res=$db->Execute($query);
    	$par_par_id = $res->fields["parentid"];
    	return _shn_cs_recursive_parent_search($in_array,$par_par_id);
    }
}
 
?>