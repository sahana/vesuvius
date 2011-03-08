<?php
/**
 * @name         Missing Person Registry
 * @version      1.5
 * @package      mpr
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0307
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