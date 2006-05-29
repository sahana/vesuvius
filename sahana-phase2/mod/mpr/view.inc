<?php
/* $Id: view.inc,v 1.4 2006-05-29 08:22:29 mahesh_kks Exp $ */

/**Main home page of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	  Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/* {{{ Add Confirm Form */
/**
 * Confirm Form
 * 
 * @access public
 * @return void
 */
function shn_mpr_view($p_uuid)
{
    shn_form_fopen("",null);
    shn_form_fsopen(_("Details"));
    shn_show_thumb_url($p_uuid,$conf['mod_mpr']['upload_picture']['savehandler' ],'mpr', 'addmp_img');
?>
    <hr>
<?php
    $arr_info = _shn_mpr_get_details($p_uuid);
    //Identity
    if(isset($arr_info['idcard']) ||
            isset($arr_info['passport']) ||
            isset($arr_info['drv_license']) ) {
        shn_form_fsopen(_("Identity"));
        $identity_section = true;
    }
    if(isset($arr_info['idcard']))
        shn_form_label(_('Identity Card Number'),$arr_info['idcard']);
    if(isset($arr_info['passport']))
        shn_form_label(_('Passport Number'),$arr_info['passport']);
    if(isset($arr_info['drv_license']))
        shn_form_label(_('Driving License'),$arr_info['drv_license']);
    if($identity_section)
        shn_form_fsclose();

    //Basic Details
    if(isset($arr_info['full_name']) ||
            isset($arr_info['family_name']) ||
            isset($arr_info['local_name']) ||
            isset($arr_info['dob']) ||
            isset($arr_info['opt_age_group']) ||
            isset($arr_info['opt_gender']) ||
            isset($arr_info['opt_marital_status']) ||
            isset($arr_info['opt_religion']) ||
            isset($arr_info['opt_race']) ) {
        shn_form_fsopen(_("Basic Details"));
        $basic_section = true;
    }
    if(isset($arr_info['full_name']))
        shn_form_label(_('Full Name'),$arr_info['full_name']);
    if(isset($arr_info['family_name']))
        shn_form_label(_('Family Name'),$arr_info['family_name']);
    if(isset($arr_info['l10n_name']))
        shn_form_label(_('Local Name'),$arr_info['l10n_name']);
    if(isset($arr_info['dob']))
        shn_form_label(_('Date of Birth'),$arr_info['dob']);
    if(isset($arr_info['opt_age_group']))
        shn_form_label(_('Age Group',shn_get_field_opt($arr_info['opt_age_group']),'opt_age_group'));
    if(isset($arr_info['opt_gender']))
        shn_form_label(_('Gender',shn_get_field_opt($arr_info['opt_gender']),'opt_gender'));
    if(isset($arr_info['opt_marital_status']))
        shn_form_label(_('Marital Status',shn_get_field_opt($arr_info['opt_marital_status']),'opt_marital_status'));
    if(isset($arr_info['opt_religion']))
        shn_form_label(_('Religion',shn_get_field_opt($arr_info['opt_religion']),'opt_religion'));
    if(isset($arr_info['opt_race']))
        shn_form_label(_('Race',shn_get_field_opt($arr_info['opt_race']),'opt_race'));
    if($basic_section)
        shn_form_fsclose();

    //Physical Details
    if(isset($arr_info['opt_eye_color']) ||
            isset($arr_info['opt_skin_color']) ||
            isset($arr_info['opt_hair_color']) ||
            isset($arr_info['height']) ||
            isset($arr_info['weight']) || 
            isset($arr_info['physical_comments'])) {
        shn_form_fsopen(_("Physical Details"));
        $physical_section = true;
    }
    if(isset($arr_info['opt_eye_color']))
        shn_form_label(_('Eye Colour',shn_get_field_opt($arr_info['opt_eye_color']),'opt_eye_color'));
    if(isset($arr_info['opt_skin_color']))
        shn_form_label(_('Skin Colour',shn_get_field_opt($arr_info['opt_skin_color']),'opt_skin_color'));
    if(isset($arr_info['opt_hair_color']))
        shn_form_label(_('Hair Colour',shn_get_field_opt($arr_info['opt_hair_color']),'opt_hair_color'));
    if(isset($arr_info['height']))
        shn_form_label(_('Height'),$arr_info['height']);
    if(isset($arr_info['weight']))
        shn_form_label(_('Weight'),$arr_info['weight']);
    if(isset($arr_info['physical_comments']))
        shn_form_label(_('Comments'),$arr_info['physical_comments']);
    if($physical_section)
        shn_form_fsclose();

    //Contact Details
    if(isset($arr_info['address']) || 
            isset($arr_info['zip']) ||
            isset($arr_info['phone']) ||
            isset($arr_info['mobile']) ){
        shn_form_fsopen(_("Contact Details"));
        $contact_section = true;
    }
    if(isset($arr_info['address']))
        shn_form_label(_('Address'),$arr_info['address']);
    if(isset($arr_info['zip']))
        shn_form_label(_('Postal Code'),$arr_info['zip']);
    if(isset($arr_info['phone']))
        shn_form_label(_('Home Phone'),$arr_info['phone']);
    if(isset($arr_info['mobile']))
        shn_form_label(_('Mobile'),$arr_info['mobile']);
    if($contact_section)
        shn_form_fsclose();

    if(isset($arr_info['opt_blood_type']) ||
            isset($arr_info['last_seen']) ||
            isset($arr_info['last_clothing']) ||
            isset($arr_info['comments']) ) {
        shn_form_fsopen(_("Other Details"));
        $other_section = true;
    }
    //Other Details
    if(isset($arr_info['opt_blood_type']))
        shn_form_label(_('Blood Type',shn_get_field_opt($arr_info['opt_blood_type']),'opt_blood_type'));
    if(isset($arr_info['last_seen']))
        shn_form_label(_('Last Seen'),$arr_info['last_seen']);
    if(isset($arr_info['last_clothing']))
        shn_form_label(_('Last Clothing'),$arr_info['last_clothing']);
    if(isset($arr_info['comments']))
        shn_form_label(_('Comments'),$arr_info['comments']);
    if($other_section)
        shn_form_fsclose();

    //Reporting Person
    shn_form_fsopen(_("People that are tracking"));
    foreach($arr_info['trk_people'] as $info){
        echo '<a title="'._('View').'" '.
            'href="index.php?mod=mpr&act=viewmp&id='.
            $info['rep_uuid'].
            '" >'. $info['full_name'] . '</a>'.
            ' -- '. $info['relation'] . '<br />';
    }
    shn_form_fsclose();

 
?>
    <p align="center"><a href="index.php?mod=mpr&act=editmp&id=<?=$p_uuid; ?>"
><?= _('Click to edit'); ?></a></p>
    <p><a href="#" onCLick="history.back()"><?= _('Back'); ?></a></p>
<?php
    shn_form_fclose();
}
/* }}} */

/**
 * Fetches the details
 * 
 * @param mixed $p_uuid 
 * @access protected
 * @return void
 */
function _shn_mpr_get_details($p_uuid)
{
    global $global;
    
    $sql = "SELECT
		a.full_name, a.family_name, a.l10n_name,
		b.serial as idcard, c.serial as passport, d.serial as drv_license,
		e.birth_date as dob, f.comments as physical_comments, f.height, f.weight,
		g.contact_value as phone, h.contact_value as mobile, i.contact_value as
		email,
		j.address, j.postcode as zip,
		k.last_seen, k.last_clothing, k.comments  
		FROM person_uuid a
		LEFT OUTER JOIN identity_to_person b ON b.p_uuid = a.p_uuid AND
		b.opt_id_type = 'nic'
		LEFT OUTER JOIN identity_to_person c ON c.p_uuid = a.p_uuid AND
		c.opt_id_type = 'pas'
		LEFT OUTER JOIN identity_to_person d ON d.p_uuid = a.p_uuid AND
		d.opt_id_type = 'dln'
		LEFT OUTER JOIN person_details e ON e.p_uuid = a.p_uuid
		LEFT OUTER JOIN person_physical f ON f.p_uuid = a.p_uuid
		LEFT OUTER JOIN contact g ON g.pgoc_uuid = a.p_uuid AND g.opt_contact_type
		= 'curr'
		LEFT OUTER JOIN contact h ON h.pgoc_uuid = a.p_uuid AND h.opt_contact_type
		= 'cmob'
		LEFT OUTER JOIN contact i ON i.pgoc_uuid = a.p_uuid AND i.opt_contact_type
		= 'emai'
		LEFT OUTER JOIN location_details j ON j.poc_uuid = a.p_uuid
		LEFT OUTER JOIN person_missing k ON k.p_uuid = a.p_uuid
		WHERE a.p_uuid = '$p_uuid'";
    $array = $global['db']->GetRow($sql);
    
    $sql_tracking_list = 
        "SELECT
        a.relation, a.rep_uuid, b.full_name FROM 
        person_to_report a
        INNER JOIN person_uuid b ON a.rep_uuid = b.p_uuid 
        WHERE a.p_uuid = '$p_uuid'";
    $arr_rep = $global['db']->GetAll($sql_tracking_list);
    $array['trk_people'] = $arr_rep ;
    return $array; 
}
?>
