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

	function shn_pr_print_person_list()
	{	
		echo "<h2>" . _t('Person List') . "</h2>";

		shn_form_fopen('list_person','pr', null);		
		shn_form_fsopen(_t('Person Search'));
		shn_form_text(_t('Any Name'),'any_name',null,null);
		shn_form_opt_select('opt_gender',_t('Gender'),'',array('value'=>$person->opt_gender));
		shn_form_date(_t('Date of Birth'),'birth_date',array('value'=>$person->birth_date));
		shn_form_opt_select('opt_religion',_t('Religion'),'',array('value'=>$person->opt_religion));
		shn_form_text(_t('Occupation'),'occupation','',array('value'=>$person->occupation));
		shn_form_fsclose();
		shn_form_submit(_('Search'),'name="search"');
		shn_form_fclose();
		
		$sql = Data::get_person_list_sql($_POST);
		
		$res = shn_paging_get_report($sql,10,null,array("post"=>true,"return"=>true));	
		if($res != null){
	    	$results = $res->GetAll();
		}
	
	    if(count($results)==0){
	        return;
	    }
	    
		$edit_url ='index.php?mod=pr&amp;act=list_person&amp;act_type=edit';
		$del_url ='index.php?mod=pr&amp;act=list_person&amp;act_type=delete';
		$view_url= 'index.php?mod=pr&amp;act=list_person&amp;act_type=view';
		
		$headers = array(_t('First Name') , _t('Last Name'),_t("Middle Name"), _t('Nick Name') , _t('Title'), _t('DOB') , _t('Religion'),_t('Gender'),_t('Occupation'));
		//var_dump($results);
		foreach($results as $key => $result){
			$results[$key]['religion'] = Data::get_field_option_description('opt_religion', $results[$key]['religion']);
			$results[$key]['gender'] = Data::get_field_option_description('opt_gender', $results[$key]['gender']);
		}
		
		$actions = array('del'=>$del_url,'view'=>$view_url,'edit'=>$edit_url);
		
	    shn_table_result($results,$headers,$actions ,array('action'=>$del_url,'del'=>true));
	}

