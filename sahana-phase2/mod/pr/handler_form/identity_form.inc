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

	function shn_pr_identity_information($person)
	{		
		shn_form_fsopen(_t('Identity Information'));
		shn_form_hidden(array('i_uuid'=>$person->i_uuid));
		shn_form_opt_select('opt_identity_type', _t("Identity Type"), null, array('br'=>false));
		shn_form_text('','identity_value','',array('br'=>false));
		shn_form_button(_t('Add'),'onclick="pr_add_identity(identity_value,opt_identity_type);"',null);
		echo "<span class='msg' style='display:none' id='number_exist_msg'></span>";		
		echo "<br />";
		echo "<div id='identity_list'>";		
		if(is_array($person->identity_list) && count($person->identity_list) != 0){
			foreach($person->identity_list as $identity){
				echo "<div id='{$identity['identity_type']}'>";
				shn_form_text($identity['option_description'], $identity['identity_type'], null, array('value'=>$identity['identity_value'],'br'=>false));
				shn_form_button('Remove','onclick= "pro_remove_identity(\''.$identity['identity_type'].'\')"',null);
				echo "</div>";				
			}
		}
		echo "</div>";
		shn_form_fsclose();
	}

	