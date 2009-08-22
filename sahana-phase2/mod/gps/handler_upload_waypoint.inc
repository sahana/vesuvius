<?php

/**
* Waypoint Upload Handling for GPS Module
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sriganeshan <sri@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @author     Richard Smith <s0459387@sms.ed.ac.uk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
global $conf;
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/mod/gps/conf.inc";

function shn_gps_feature_temp_save()
{
    if(isset($_SESSION['gps']['file'])) {
        $current_file = $_SESSION['gps']['file'];
        $handle1 = fopen($current_file, "r");
        $contents = fread($handle1, filesize($current_file));
        fclose($handle1);
        $handle2 = fopen("../www/tmp/dom.txt", "w+");
        fwrite($handle2,$contents);
        fclose($handle2);
    }
}

/**
 * parse input file for content in available formats
 *
 * @global <type> $global
 * @global <type> $range
 */
function shn_gps_form_feature_display_upload()
{
    global $global;
    global $conf;
    $file_type_ = $_SESSION['gps']['filetype'];
    require_once $global['approot'] . "/mod/gps/geo_file_factory_upload.inc";
    // Discover and create appropriate file factory
    if ('gpx' == $file_type_){
        $GeoFactory = new GPXFactoryUpload();
    } elseif('gml' == $file_type_){
        $GeoFactory = new GMLFactoryUpload();
    } elseif('kml' === $file_type_){
        $GeoFactory = new KMLFactoryUpload();
    } elseif('georss' == $file_type_){
        $GeoFactory = new GeoRSSFactoryUpload();
    } else {
        add_error(_('File Type Unsuported'));
        return;
    }
    $features = $GeoFactory->shn_sm_geo_get_features();

    print '<h2>' . _("Uploaded Waypoints") . '</h2>';
    shn_form_fopen("upload_seq",null,null);
    shn_form_fsopen(_("Select Features"));
?>
    <center>
    <table>
    <thead>
    <td><?php echo _("Feature Name");?></td>
    <td><?php echo _("Feature Description");?></td>
    <td><?php echo _("Feature Author");?></td>
    <td><?php echo _("Event Date");?></td>
    <td><?php echo _("Point Coordinates");?></td>
    <td><?php echo _("Feature Class");?></td>
    <td><?php echo _("Select To Upload");?></td>
    </thead>
    <tbody>
<?php
    $count = 0;
    require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
    foreach($features as $feature){
        $count++;
        if('' == $feature['f_class']){
            $feature['f_class'] = $conf['gis_feature_type_default'];
        }
        $cls = shn_gis_get_feature_class_uuid($feature['f_class']);
        $coords = $feature['f_coords']
        // @ToDo: Make class editable
?>
        <tr>
        <td><?php echo  $feature['f_name']?></td>
        <td><?php echo  $feature['f_description']?></td>
        <td><?php echo  $feature['f_author']?></td>
        <td><?php echo  $feature['f_event_date']?></td>
        <td><?php echo  $coords?></td>
        <td><?php echo  $cls['c_name']?></td>
        <td><?php echo  shn_form_checkbox($count, $count, null, array('value' => $count))?></td>
        </tr>
<?php
    }
?>
    </tbody>
    </table>
    </center>
<?php
    shn_form_hidden(array('count' => $count));
    shn_form_fsclose();
    shn_form_fsopen('Options');
    shn_form_hidden(array('seq' => '3_save_and_options'));
    shn_form_submit(_("Upload Features"),  $count, null, null);
    shn_form_fsclose();
    shn_form_fclose();
}

function shn_gps_upload_and_extra()
{
    shn_form_fopen("upload_seq",null,null);
    shn_form_fsopen(_("Extra Options:"));
    shn_form_hidden(array('seq' => '4_confirm'));
    echo '<p>' . _('Now upload has completed click finish to apply extra options and return to main page.') . '</p>';
    echo '<br />';
    shn_form_label(_('Feed Options:'));
    shn_form_checkbox('Check to publish', 'gis_publish', null, array('value'=>'gis_publish'));
    shn_form_text(_('Feed name'),'gis_feed_name','size="20"');
    echo '<br />';
    shn_form_submit(_("Finish"));
    shn_form_fsclose();
    shn_form_fclose();
}
        
function shn_gps_upload_confirm($feed_ = false, $uuids_)
{
    shn_form_fopen("upload_seq",null,null,array('req'=>false));
    shn_form_fsopen(_("Finish"));
    // Create feed
    if(!$feed_ === FALSE){
        $feed_location = shn_gps_create_feed($feed_, $uuids_);
        if($feed_location === FALSE){
            add_error(_("Failed to save feed"));
        } else {
            add_confirmation(_("A feed has been successfully created at:") . '<a href="' . $feed_location . '">' . $feed_location . '</a>');
        }
    }
    echo '<br />';
    shn_form_hidden(array('seq' => '5_home'));
    shn_form_submit(_("Menu"), 'name="step4"');
    shn_form_fsclose();
    shn_form_fclose();
}

function shn_gps_save_points($ids_)
{
    global $global;
    global $conf;
    require_once $global['approot'] . "/mod/gps/geo_file_factory_upload.inc";
    require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
    if(count($ids_) == 0){
        add_warning(_t("You have not selected any Waypoints"));
        return;
    }
    $file_type_ = $_SESSION['gps']['filetype'];
    // Discover and create appropriate file factory
    if ('gpx' == $file_type_){
        $GeoFactory = new GPXFactoryUpload();
    } elseif('gml' == $file_type_){
        $GeoFactory = new GMLFactoryUpload();
    } elseif('kml' === $file_type_){
        $GeoFactory = new KMLFactoryUpload();
    } elseif('georss' == $file_type_){
        $GeoFactory = new GeoRSSFactoryUpload();
    } else {
        add_error(_('File Type Unsuported'));
        return;
    }
    $features = $GeoFactory->shn_sm_geo_get_features();

    $error = false;
    add_confirmation(_("Selected features have been successfully uploaded:"));
    $uuids = array();
    foreach($ids_ as $id){
        $uuid = shn_gis_create_feature($features[$id - 1]);
        if($uuid){
            array_push($uuid, $uuids);
            add_confirmation(_("Feature number '"). $id . _("', name '"). $features[$id]['f_name'] . _("', coords '"). $features[$id]['f_coords'] . _("' was added."));
        } else {
            add_error(_("Feature number '"). $id . _("', name '"). $features[$id]['f_name'] . _("', coords '"). $features[$id]['f_coords'] . _("' could not be added."));
        }
    }
    return $uuids;
}


