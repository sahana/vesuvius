<?php
	/**
	 *
	 * PHP version 5
	 *
	 * LICENSE: This source file is subject to LGPL license
	 * that is available through the world-wide-web at the following URI:
	 * http://www.gnu.org/copyleft/lesser.html
	 *
	 * @package    Sahana - http://sahana.sourceforge.net
	 * @author     Kethees <sdkethees@gmail.com>
	 * @copyright  Lanka Software Foundation - http://www.opensource.lk
	 */
	

	function print_group_member_list($g_uuid)
	{
		$results = Data::get_group_member_list($g_uuid);
		
		echo "<h4>" . _t('Group Member(s) List') . "</h4>";
				
		//$edit_url ='index.php?mod=pr&amp;act=add_group&amp;act_type=edit&amp;g_uuid='. $g_uuid .'&amp;relation_type='.$relation_type;
		$del_url ='index.php?mod=pr&amp;act=add_group&amp;act_type=delete&amp;g_uuid='. $g_uuid;
		//$view_url= 'index.php?mod=pr&amp;act=add_group&amp;act_type=view&amp;g_uuid='. $g_uuid;
		$view_url= 'index.php?mod=pr&amp;act=list_person&amp;act_type=view';
		
		$headers = array(_t('First Name') , _t('Last Name'),_t("Relationship"));
		echo "<table width='50%'>";
		echo "<thead>";
		echo "<tr>";
		echo "<td>" . _t('Action'). "</td>";
		echo "<td>" . _t('Full Name'). "</td>";
		echo "<td>" . _t('Relationship'). "</td>";
		echo "</tr>";
		echo "</thead>";
		echo "<tbody>";
		foreach($results as $key => $result){
			$relationship = Group::get_relationship_name($results[$key][4]);
			$full_name =  ucfirst($results[$key][2]) . ' ' . ucfirst($results[$key][3]);
			$relation_type = $results[$key][4];
			$edit_url ='index.php?mod=pr&amp;act=add_group&amp;act_type=edit&amp;g_uuid='. $g_uuid .'&amp;relation_type='.$relation_type;
			echo "<tr>";
			?>
	            <td width="60">	        
	            	<a href="<?php echo  "$edit_url&amp;p_uuid={$results[$key][0]}" ?>" title="Edit" >
	                <img src="theme/default/img/tbl_edit.png" alt="edit" /></a>	                    
	                <a href="<?php echo  "$view_url&amp;p_uuid={$results[$key][0]}" ?>" target="_blank" title="View" >
	                <img src="theme/default/img/tbl_view.png" alt="view" /></a>	                    
	                <a href="<?php echo  "$del_url&amp;p_uuid={$results[$key][0]}" ?>" title="Delete"  onclick="return confirmation('delete');">
	                <img src="theme/default/img/tbl_delete.png" alt="delete" /></a>
	             </td>
			<?php
			echo "<td>" . $full_name . "</td>";
			echo "<td>" . $relationship . "</td>";
			echo "</tr>";	
		}
		echo "</tbody>";
	    echo "</table>";
	    echo "<br />";
	}
	
	function _shn_pr_list_group() 
	{
		switch($_GET['act_type']){
			case 'edit':				
				shn_pr_add_group();
				break;
			case 'delete':
				shn_pr_group_delete();
				shn_pr_print_list_group();
				break;
			case 'view':
				echo "view";
				shn_pr_print_list_group();
				break;
			default :				
				shn_pr_print_list_group();
				break;
			
		}
	}
	
	function shn_pr_print_list_group()
	{
		echo "<h2>" . _t('Group List') . "</h2>";
		
		shn_form_fopen('list_group','pr', null);
		
		shn_form_fsopen(_t('Group Search'));
		shn_form_text(_t("Any Name"),'any_name',null,null);		
		shn_form_opt_select('opt_group_type', _t("Group"), null, array('sort'=>'option_code'));		
		shn_form_opt_select('opt_gender',_t('Gender'),'',null);
		shn_form_date(_t('Date of Birth'),'birth_date',null);		
		shn_form_opt_select('opt_religion',_t('Religion'),'',null);		
		shn_form_text(_t('Occupation'),'occupation','',null);
		shn_form_fsclose();		
		shn_form_submit(_t('Search'),'name="search"');
		shn_form_fclose();
		
		$sql = Data::get_group_list_sql($_POST);
		
		$res = shn_paging_get_report($sql,10,null,array("post"=>true,"return"=>true));	
		if($res != null){
	    	$results = $res->GetAll();
		}
	
	    if(count($results)==0){
	        return;
	    }
	    
		$edit_url ='index.php?mod=pr&amp;act=list_group&amp;act_type=edit';
		$del_url ='index.php?mod=pr&amp;act=list_group&amp;act_type=delete';
		$view_url= 'index.php?mod=pr&amp;act=list_group&amp;act_type=view';
		
		$headers = array(_t('Group Head') , _t('Group'),_t('Group Member(s)'));
		$actions = array('del'=>$del_url,'view'=>$view_url,'edit'=>$edit_url);
		
		foreach($results as $key => $result){
			$results[$key]['group_type'] = ucfirst(Data::get_field_option_description('opt_group_type', $results[$key]['group_type']));	
		}
		
	    shn_table_result($results,$headers,$actions ,array('action'=>$del_url,'del'=>true));
	}
