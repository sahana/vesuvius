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

	function _shn_pr_person_api()
	{
		echo "<h2>" . _t('Person API Sample'). "</h2>";
			
		shn_form_fopen('person_api','pr');
		shn_form_fsopen(_t('Person full name'));
		shn_form_person();
		shn_form_fsclose();
		shn_form_fclose();
	}
	
	function shn_form_person()
	{
		if(isset($_POST['person_api']) && $_POST['person_api'] == 'person_api'){
			$person = New Person();			
			$p_uuid = $person->save_person_api();
			$full_name = $person->full_name; 
		}
		shn_form_text(_t('Full Name'),'full_name',' disabled="disabled" ', array('br'=>false,'value'=>$full_name));
		shn_form_hidden(array('person_id'=>$p_uuid));
		?>
		<input type="button" value="Add" onclick="popup_show('popup', 'popup_drag', 'popup_exit', 'screen-center', 0, 0); popup_clear(this.form); return false;" />
		<div class="popup_window" id="popup" style="display: none;">
		<div class="form_header" id="popup_drag">
			<img class="form_exit" id="popup_exit" src="theme/default/img/cross2.png" alt="" />
			<center><strong>Person Information</strong></center>
		</div>
		<div class="form_body">
		<br/>		
		<?php
		shn_form_fsopen(_t('Basic Details'));
		shn_form_hidden(array('person_api'=>'person_api'));
		shn_form_text(_t('First Name'),'first_name','', null);
		shn_form_text(_t('Last Name'),'last_name','', null);
		shn_form_text(_t('Occupation'),'occupation','',null);
		shn_form_textarea(_t('Address'),'address','',null);						
		shn_form_text(_t('Telephone'),'telephone','',array('br'=>false));
		shn_form_button(_t('Add'),'onclick="pr_add_number(telephone_list,telephone);"',array('br'=>true));			
		echo "<span class='msg' style='display:none' id='telephone_msg'></span>";
		echo "<ol id='telephone_list'>";
		echo "</ol>";	
		shn_form_fsclose(); 
		echo "<center>";
		shn_form_submit(_t('Save'), 'name="save_person"');
		echo "</center>";
		echo "<br/>";
		?>
		</div>
		</div>
		<?php	
	}
	