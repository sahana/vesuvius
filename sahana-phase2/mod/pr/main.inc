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
         *
	 */

	include_once $global['approot'] . '/inc/lib_menu.inc';
	include_once $global['approot'] . '/inc/lib_form.inc';
	include_once $global['approot'] . '/inc/lib_location.inc';
	include_once $global['approot'] . '/inc/lib_errors.inc';
	include_once $global['approot'] . '/inc/lib_paging.inc';
	include_once $global['approot'] . '/inc/lib_xajax.inc';
	include_once $global['approot'] . '/inc/lib_uuid.inc';
	include_once $global['approot'] . '/inc/lib_chart.inc';
	include_once $global['approot'] . '/inc/lib_image.inc';
	
	include_once 'handler_js.inc';
	
	include_once 'handler_class/data_class.php';
	include_once 'handler_class/person_class.php';
	include_once 'handler_class/group_class.php';
	include_once 'handler_class/address_class.php';	
	include_once 'handler_class/identity_class.php';
	
	include_once 'handler_form/address_form.inc';
	include_once 'handler_form/identity_form.inc';
	
	include_once 'handler_form/pr_form.inc';
	include_once 'handler_form/person_form.inc';
	include_once 'handler_list/person_list.inc';
	include_once 'handler_table.inc';
	include_once 'handler_form/group_form.inc';
	include_once 'handler_list/group_list.inc';
	
	include_once 'handler_person_rpt.inc';
	include_once 'handler_group_rpt.inc';
	
	include_once 'lib_person.inc';
	
	function shn_pr_mainmenu()
	{
		include_once 'handler_submenu.inc';
		shn_pr_submenu();
	}
	
	function shn_pr_default()
	{
		include_once 'home.inc';
	}
	
	function shn_pr_add_person() 
	{		
		_shn_pr_add_person();
	}
	
	function shn_pr_list_person()
	{
		switch($_GET['act_type'])		
		{
			case 'edit':
				_shn_pr_add_person($_GET['p_uuid']);
				break;
			case 'delete':
				shn_pr_person_delete();
				break;
			case 'view':
				shn_pr_person_view();
				break;
			default :
				shn_pr_print_person_list();
				break;			
		}
	}
	
	function shn_pr_person_delete()
	{
		if($_GET['p_uuid'] != null){
			$res = Person::delete_person($_GET['p_uuid']);			
			if($res){
				add_confirmation(_t('Selected person(s) has/have been successfully deleted'));
			}
			else{
				add_error(_t('Error'));
			}
		}
		else if(isset($_POST['delete'])){			
			if(is_array($_POST['record_no']) && count($_POST['record_no']) != 0){
				$res = false;
				foreach($_POST['record_no'] as $rec){
					$res = Person::delete_person($rec);					
				}				
				
				if($res){
					add_confirmation(_t('Select person(s) has/have been successfully deleted'));
				}
				else{
					add_error(_t('Error'));
				}
			}
			else{
				add_error(_t('Please select person(s) to delete'));
			}
			
		}
		shn_pr_print_person_list();	
	}
	
	function shn_pr_group_delete()
	{
		if($_GET['g_uuid'] != null){
			$res = Group::delete_group($_GET['g_uuid']);
			
			if($res){
				add_confirmation(_t('Selected group(s) has/have been successfully deleted'));
			}
			else{
				add_error(_t('Error'));
			}
		}
		else if(isset($_POST['delete'])){			
			if(is_array($_POST['record_no']) && count($_POST['record_no']) != 0){
				$res = false;
				foreach($_POST['record_no'] as $rec){					
					$res = Group::delete_group($rec);					
				}				
				
				if($res){
					add_confirmation(_t('Select person(s) has/have been successfully deleted'));
				}
				else{
					add_error(_t('Error'));
				}
			}
			else{
				add_error(_t('Please select person(s) to delete.'));
			}
			
		}
	}
	
	function shn_pr_person_view()
	{
		$person = New Person();
		
		if($_GET['p_uuid'] != null){			
			$person->get_person_information($_GET['p_uuid']);			
		}
		else{			
			add_information(_t('Please select a person'));
			return;
		}
		
		shn_pr_print();
		
		shn_pr_person_information($person);
	}
	
	function shn_pr_add_group()
	{
		_shn_pr_add_group();
	}
	
	function shn_pr_list_group()
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
				shn_pr_group_view();
				break;
			default :				
				shn_pr_print_list_group();
				break;
			
		}
	}
	
	function shn_pr_group_view()
	{	
		$group = New Group();
		
		if($_GET['g_uuid'] != null){			
			$group->get_group_information($_GET['g_uuid']);
		}
		else{			
			add_information(_t('Please select a group'));
			return;
		}
		
		echo "<a name='top'></a>";
		echo "<h2>". _t('Group Information')."</h2>";
		
		shn_pr_print();
		
		shn_pr_group_information($group);
	}
	
	function shn_pr_person_rpt()
	{
		echo "<h2>". _t('Person Report')."</h2>";
		
		shn_pr_print();
				
		_shn_pr_person_rpt();
	}
	
	function shn_pr_group_rpt()
	{
		echo "<h2>". _t('Group Report')."</h2>";
		
		shn_pr_print();
				
		_shn_pr_group_rpt();
	}
	
	function shn_pr_print()
	{
		echo "<p align='right'>";		
		echo "<a href='JavaScript:window.print();'><strong>" . _t('Print this page') . "</strong></a>";		
		echo "<br/>";
		echo "</p>";
	}
	
	function shn_text_pr_gender(){		
		$array = Data::get_pr_gender();
		$data = $array['data'];
		$label = $array['label'];
		foreach($data as $d){
			$total += $d;
		}		
		foreach($data as $key=>$d){
			$data[$key] = round(($d/$total*100),2);
		}
		
		$g = new graph();
		$g->bg_colour='#FFFFFF';	
		$g->pie(60,'#505050','{font-size: 10px; color: #404040;');		
		$g->pie_values( $data, $label );		
		$g->pie_slice_colours( array('#31A43F','#A79810','#D21389') );		
		$g->set_tool_tip( ' Label: #x_label#<br>Value: #val#%' );	
		$g->title( 'Gender', '{font-size:14px; color: #d01f3c}' );
		echo $g->render();
	}
	
	function shn_text_pr_religion(){		
		$array = Data::get_pr_religion();
		$data = $array['data'];
		$label = $array['label'];
		foreach($data as $d){
			$total += $d;
		}		
		foreach($data as $key=>$d){
			$data[$key] = round(($d/$total*100),2);
		}
		
		$g = new graph();
		$g->bg_colour='#FFFFFF';	
		$g->pie(60,'#505050','{font-size: 10px; color: #404040;');		
		$g->pie_values( $data, $label );		
		$g->pie_slice_colours( array('#31A43F','#A79810','#D21389') );		
		$g->set_tool_tip( ' Label: #x_label#<br>Value: #val#%' );	
		$g->title( 'Religion', '{font-size:14px; color: #d01f3c}' );
		echo $g->render();
	}
	
	function shn_text_pr_martial_status(){		
		$array = Data::get_pr_martial_status();
		$data = $array['data'];
		$label = $array['label'];
		foreach($data as $d){
			$total += $d;
		}		
		foreach($data as $key=>$d){
			$data[$key] = round(($d/$total*100),2);
		}
		
		$g = new graph();
		$g->bg_colour='#FFFFFF';	
		$g->pie(60,'#505050','{font-size: 10px; color: #404040;');		
		$g->pie_values( $data, $label );		
		$g->pie_slice_colours( array('#31A43F','#A79810','#D21389') );		
		$g->set_tool_tip( ' Label: #x_label#<br>Value: #val#%' );	
		$g->title( 'Martial Status', '{font-size:14px; color: #d01f3c}' );
		echo $g->render();
	}
	
	function shn_image_pr_pr()
	{    
	    shn_show_image_stream($_GET['x_uuid'], false, null, false, 'pr');
	}
	
	function shn_pr_person_api()
	{
		_shn_pr_person_api();
	}
