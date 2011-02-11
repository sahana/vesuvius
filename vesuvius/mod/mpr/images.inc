<?php
/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    <package>
 * @subpackage <subpackage>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */



function shn_mpr_manage_images_form($id,$url) {
	if($errors) {
		display_errors();
	}
	shn_form_fopen("addmp",null,array('enctype'=>'enctype="multipart/form-data"'));
	shn_form_hidden(array('seq'=>'upload_pic'));
	shn_form_fsopen(_t('Add Another Picture'));
	shn_form_upload(_t('Upload Picture'),"picture");
	shn_form_fsclose();
	shn_form_submit(_t('Next'));
	shn_form_fclose();
	?><table><tr><td></td><td></td><td></td><td></td><td></td><td></td></tr></table><?php
}