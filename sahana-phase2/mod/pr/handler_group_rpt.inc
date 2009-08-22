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

	function shn_pr_group_information($group)
	{			
		shn_pr_print_group_information($group);
		
		$mem_count = 1;
		
		echo "<p>";
		echo "<a name='member_$mem_count'></a><strong>" . _t('Member'). " #$mem_count" . "</strong>&nbsp;&nbsp;&nbsp;&nbsp;<a href='#top'>". _t('Top') ."</a>";
		echo "</p>";
		
		shn_pr_person_information($group, $mem_count, true);
		
		if(is_array($group->group_members) && count($group->group_members) != 0){
			
			foreach($group->group_members as $p_uuid){								
				if($p_uuid != $group->group_head_id){
					$person = New Person();
					$person->get_person_information($p_uuid);
					++$mem_count;
					echo "<p>";
					echo "<a name='member_$mem_count'></a><strong>" . _t('Member'). " #$mem_count" . "</strong>&nbsp;&nbsp;&nbsp;&nbsp;<a href='#top'>". _t('Top') ."</a>";
					echo "</p>";			
					shn_pr_person_information($person);
				}				
			}
		}
	}
	
	function shn_pr_print_group_information($group)
	{		
		$results = Data::get_group_member_list($group->g_uuid);
		
		echo "<strong>" . _t('Group Type') . "</strong>" . "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;: " . ucfirst($group->group_type);
		echo "<br/>";
		echo "<strong>" ._t('Group Head Name'). "</strong>" . "&nbsp;&nbsp;&nbsp; : " . $group->full_name;
		echo "<br/>";
		echo "<br/>";
		//echo "<h4>" . _t('Group Member(s) List') . "</h4>";
				
		echo "<table width='50%'>";
		echo "<thead>";
		echo "<tr>";
		echo "<td>" . _t('No'). "</td>";
		echo "<td>" . _t('Full Name'). "</td>";
		echo "<td>" . _t('Relationship'). "</td>";
		echo "</tr>";
		echo "</thead>";
		echo "<tbody>";
		$count = 1;
		foreach($results as $key => $result){
			$relationship = Group::get_relationship_name($results[$key][4]);
			$full_name =  ucfirst($results[$key][2]) . ' ' . ucfirst($results[$key][3]);
			echo "<tr>";
			echo "<td align='center'>" . $count . "</td>";
			echo "<td><a href='#member_$count'>" . $full_name . "</a></td>";
			echo "<td>" . $relationship . "</td>";
			echo "</tr>";	
			$count++;
		}
		echo "</tbody>";
	    echo "</table>";
	    echo "<br />";
	}	
	
	function _shn_pr_group_rpt()
	{	
		echo "<table width='100%'>";
		echo "<thead>";
		echo "<tr>";
		echo "<td>" ._t('No'). "</td>";
		echo "<td>" ._t('Full Name'). "</td>";
		echo "<td>" ._t('Group Type'). "</td>";
		echo "<td>" ._t('Relationship'). "</td>";
		echo "<td>" ._t('Gender'). "</td>";
		echo "<td>" ._t('DOB'). "</td>";		
		echo "<td>" ._t('Address'). "</td>";
		echo "<td>" ._t('Occupation'). "</td>";
		echo "</tr>";
		echo "</thead>";
		echo "<tbody>";
		
		$results = Data::get_group_id_list();
		$person_count = 1;
		
		if(is_array($results) && count($results) != 0){
			foreach($results as $result){
				$group = New Group();
				$group->get_group_information($result['g_uuid']);
								
				$detail_url = "index.php?mod=pr&amp;act=list_group&amp;act_type=view&amp;g_uuid=" . $result['g_uuid'];				
				
				echo "<tr>";
				echo "<td align='center'>" . $person_count++ . "</td>";
				echo "<td><a href='$detail_url' target='_blank'>" . $group->full_name . "</a></td>";				
				echo "<td>" . $group->group_type . "</td>";
				echo "<td>" . $group->relationship_type . "</td>";
				echo "<td>" . $group->gender . "</td>";
				echo "<td>" . $group->birth_date . "</td>";				
				echo "<td>" . $group->address . "</td>";
				echo "<td>" . $group->occupation . "</td>";
				echo "</tr>";
				
				$detail_url = '';
			}
		}
		echo "</tbody>";
		echo "</table>";
	}
	