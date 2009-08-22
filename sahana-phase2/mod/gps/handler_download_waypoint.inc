<?php

/**
* Marker Handling Page of GPS Module
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

/**
 * Generates a form to search for features
 *
 * @todo Add in new class box each time one is filled
 * @param <type> $action
 * @param <type> $seq
 */
function shn_gis_form_feature_search2($fresh_search = true, $action = 'download_seq', $seq = '2_choose_features')
{
    global $global;
    global $conf;

    if($conf['gis']){
        // remove already exiting uuids to be saved
        if($fresh_search){
            if(isset($_SESSION['gis']['feature_uuids'])){
                unset($_SESSION['gis']['feature_uuids']);
            }
        }
        require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
?>
        <h2><?php echo _("Feature Search")?></h2>
        <script type="text/javascript">
            <?php require_once $global['approot'] . '/mod/gps/ajax_form.js' ?>
        </script>
<?php
        shn_form_fopen($action, null, null, array('req' => false));
        shn_form_fsopen(_("Feature Details"));
        // Find all layers in system
        $layers = shn_gis_get_layers_all();
        $options_l = array('all' => 'All');
        foreach($layers as $layer){
            $options_l[$layer['l_uuid']] = $layer['l_name'];
        }
        $select_opts = 'onchange="shn_gis_narrow_feature_classes(this.value)"';
        shn_form_select($options_l, "Layer", "l_uuid", $select_opts, $extra_opts = null);
        // Find all feature classes in system
        $f_classes = shn_gis_get_feature_class_all();
        $options_c = array('all' => 'All');
        foreach($f_classes as $f_class){
            $options_c[$f_class['c_uuid']] = $f_class['c_name'];
        }
        // div used by ajax to reload classes
        echo '<div id="gis_feature_class_select_form">';
        shn_form_select($options_c, "Feature Class", "c_uuid", $select_opts = "", $extra_opts = null);
        echo '</div>';
        shn_form_text(_("Name of Author"), "f_author", 'size="20"', array('req' => false));
        shn_form_date(_("Date of Event (From)"), "f_event_date_from", array('req' => false));
        shn_form_date(_("Date of Event (To)"), "f_event_date_to", array('req' => false));
        shn_form_text(_("Name of Feature"), "f_name", 'size="20"', array('req' => false));
        shn_form_hidden(array('seq' => $seq));
        shn_form_fsclose();
        shn_form_submit(_("Search"));
        shn_form_fclose();
    } else {
        // add error message
    }
}

/**
 * Second Menu screen
 *
 * Displays features available in system from attributes chosen.
 * Displays headers chosen in $keys_ (Make sure keys at least match those being passed !!!).
 * Offers post-download options such as delete points or publish as a feed.
 * 
 * @global <type> $global
 * @global <type> $conf
 * @param <type> $results_
 * @param <type> $keys_
 */
function shn_gps_form_feature_display_download($results_, $keys_)
{
    global $global;
    global $conf;
    // Do we need to check for this? If here then we should safely assume GIS is enabled?
    if($conf['gis']){
        require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";
?>
        <h2><?php echo _("Search Results")?></h2>
<?php
        shn_form_fopen('download_seq', null, null, array('req' => false));
        shn_gis_form_feature_display($results_, $keys_);
        shn_form_fsopen('Options');
        shn_form_hidden(array('seq' => '3_save_and_options'));
        shn_form_submit(_("Search For More Features"), 'name="step3"');
        shn_form_submit(_("Fresh Search"), 'name="step3"');
        shn_form_submit(_("Continue To Download"), 'name="step3"');
        shn_form_fsclose();
        shn_form_fclose();
    }
}

/**
 * Third Menu screen
 */
function shn_gps_download_and_extra()
{
    shn_form_fopen("create_file&stream=text", null, array('req_message' => false, 'name' => 'choose'));
    shn_form_fsopen(_("Download"));
    shn_form_opt_select("opt_geo_file_type", "File Type");
    shn_form_submit(_("Download"));
    shn_form_fsclose();
    shn_form_fclose();
    shn_form_fopen('download_seq', null, null, array('req' => false));
    shn_form_fsopen(_("Extra Options:"));
    shn_form_hidden(array('seq' => '4_confirm'));
    echo '<p>' . _('After download has completed click finish to apply extra options and return to main page.') . '</p>';  
    echo '<br />';
    shn_form_label(_('Feed Options:'));
    shn_form_checkbox('Check to publish', 'gis_publish', null, array('value'=>'gis_publish'));
    shn_form_text(_('Feed name'),'gis_feed_name','size="20"');
    echo '<br />';
    shn_form_label(_('Database Options:'));
    shn_form_checkbox('Remove Features From Database', 'gis_delete', null, array('value'=>'gis_delete'));
    echo '<br />';
    shn_form_submit(_("Finish"));
    shn_form_fsclose();
    shn_form_fclose();
}

/**
 * Fourth Menu screen
 */
function shn_gps_download_confirm($feed_ = false, $delete_ = false, $uuids_)
{         
    shn_form_fopen("download_seq",null,null,array('req'=>false));
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
    // Remove selected features       
    if(!$delete_ === FALSE){
        global $global;
        global $conf;
        if($conf['gis']){
            require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
            add_confirmation(_("Features have been removed from the system"));
            foreach($uuids_ as $uuid){
                if(!shn_gis_remove_feature($uuid)){
                    add_error(_("Feature uuid '"). $uuid . _("' could not be removed from system"));
                }
            } 
        } else {
            add_error(_("GIS not installed"));
        }
    }
    echo '<br />';
    shn_form_hidden(array('seq' => '5_home'));
    shn_form_submit(_("Menu"), 'name="step4"');
    shn_form_fsclose();
    shn_form_fclose();
}

/**
 * Creates a geo file using shn_gps_create_file($file_type, $uuids).
 * Called when download button is pressed
 */
function shn_text_gps_create_file()
{
    global $global;
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    // Save features    
    if(isset($_SESSION['gis']['feature_uuids'])){
        $uuids = $_SESSION['gis']['feature_uuids'];               
        $file_type = $_POST['opt_geo_file_type'];
        print shn_gis_create_file('Sahana-Featuressss', $file_type, $uuids, false);
        //header("Content-type: text/" . $file_type);
        //header("Content-Disposition: attachment; filename=" . "Sahana-Features." . $file_type);
        //header("Cache-Control: no-cache, must-revalidate");
        //print shn_gps_create_file($file_type, $uuids);          
    } else {
        // Error 
    }          
}

/**
 * Takes file format and IDs of features to be saved, creates the aproprate factory
 * then creates the points and offers them to the user.
 *
 * @global <type> $global
 * @global <type> $config
 * @param <type> $file_type_
 * @param <type> $feature_uuids
 * @return <type>
 */
function shn_gps_create_file($file_type_, $feature_uuids_)
{
    global $global;
    global $config;
    $db = $global['db'];
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    require_once $global['approot']."/mod/gps/geo_file_factory.inc";
    
    // Discover and create appropriate file factory
    if ('gpx' == $file_type_){
        $GeoFactory = new GPXFactory();
    } elseif('gml' == $file_type_){
        $GeoFactory = new GMLFactory();
    } elseif('kml' === $file_type_){
        $GeoFactory = new KMLFactory();
    } elseif('georss' == $file_type_){
        $GeoFactory = new GeoRSSFactory();
    } else {
        return false;
    }
    
    foreach($feature_uuids_ as $feature_uuid){
        $keys = array(
            'f_uuid'          => '1',
            'f_class'         => '1',
            'f_type'          => '1',
            'f_projection'    => '1',
            'f_coords'        => '1',
            'f_module_item'   => '1',
            'f_name'          => '1',
            'f_description'   => '1',
            'f_author'        => '1',
            'f_url'           => '1',
            'f_address'       => '1',
            'f_event_date'    => '1',
            'f_extended_data' => '1'
        );
        $results = shn_gis_get_features_uuid($feature_uuid, $keys);
        if($results){
            $f_uuid           = $results[0]['f_uuid'];
            $f_class          = $results[0]['f_class'];
            $f_type           = $results[0]['f_type'];
            $f_projection     = $results[0]['f_projection'];
            $f_coords         = $results[0]['f_coords'];
            $f_module_item    = $results[0]['f_module_item'];
            $f_name           = $results[0]['f_name'];
            $f_description    = $results[0]['f_description'];
            $f_author         = $results[0]['f_author'];
            $f_url            = $results[0]['f_url'];
            $f_address        = $results[0]['f_address'];
            $f_event_date     = $results[0]['f_event_date'];
            $f_extended_data  = $results[0]['f_extended_data'];
            // Decode coords string
            $coords = shn_gis_coord_decode($f_coords);
            // Get icon from class
            $class = shn_gis_get_feature_class_uuid($f_class);
            $icon = $class['c_icon'];
            switch($f_type){
                case 'point':
                    $GeoFactory->shn_sm_Geo_Add_Point($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $icon, $extendedData, $coords);
                    break;
                case 'line':
                    $GeoFactory->shn_sm_Geo_Add_Path($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $extendedData_, $longitude_, $coords);
                    break;
                case 'poly':
                    $GeoFactory->shn_sm_Geo_Add_Polygon($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $extendedData_, $longitude_, $coords);
                    break;
                default:
                    // miss out feature...
                    break;
            }
        }
    }
    return $GeoFactory->shn_sm_geo_print();
}

function shn_gps_create_feed($name_, $feature_uuids_)
{
    global $global;
    global $config;
    $db = $global['db'];
    require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
    require_once $global['approot']."/mod/gps/geo_file_factory.inc";

    $GeoFactory = new GeoRSSFactory();
    foreach($feature_uuids_ as $feature_uuid){
        $keys = array(
            'f_uuid'          => '1',
            'f_class'         => '1',
            'f_type'          => '1',
            'f_projection'    => '1',
            'f_coords'        => '1',
            'f_module_item'   => '1',
            'f_name'          => '1',
            'f_description'   => '1',
            'f_author'        => '1',
            'f_url'           => '1',
            'f_address'       => '1',
            'f_event_date'    => '1',
            'f_extended_data' => '1'
        );
        $results = shn_gis_get_features_uuid($feature_uuid, $keys);
        if($results){
            $f_uuid           = $results[0]['f_uuid'];
            $f_class          = $results[0]['f_class'];
            $f_type           = $results[0]['f_type'];
            $f_projection     = $results[0]['f_projection'];
            $f_coords         = $results[0]['f_coords'];
            $f_module_item    = $results[0]['f_module_item'];
            $f_name           = $results[0]['f_name'];
            $f_description    = $results[0]['f_description'];
            $f_author         = $results[0]['f_author'];
            $f_url            = $results[0]['f_url'];
            $f_address        = $results[0]['f_address'];
            $f_event_date     = $results[0]['f_event_date'];
            $f_extended_data  = $results[0]['f_extended_data'];
            // Decode coords string
            $coords = shn_gis_coord_decode($f_coords);
            // Get icon from class
            $class = shn_gis_get_feature_class_uuid($f_class);
            $icon = $class['c_icon'];
            switch($f_type){
                case 'point':
                    $GeoFactory->shn_sm_Geo_Add_Point($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $icon, $extendedData, $coords);
                    break;
                case 'line':
                    $GeoFactory->shn_sm_Geo_Add_Path($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $extendedData_, $longitude_, $coords);
                    break;
                case 'poly':
                    $GeoFactory->shn_sm_Geo_Add_Polygon($f_uuid, $f_name, $f_author, $f_url, $f_description, $f_event_date, $extendedData_, $longitude_, $coords);
                    break;
                default:
                    // miss out feature...
                    break;
            }
        }
    }
    return $GeoFactory->shn_sm_geo_publish($name_);       
}


