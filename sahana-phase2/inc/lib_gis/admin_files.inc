<?php
    
/**
 * Marker Handling Page of GPS Module
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @author     Richard Smith <s0459387@sms.ed.ac.uk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * 
 * Functions for up/downloading gis database features to file formats such as
 * kml gml and gpx
 * 
 */

    function shn_gis_internal_class_general_select()
    {
        if(isset($_REQUEST['download'])){
            shn_gis_file_download_seq($return_action_, $return_module_);
        } elseif(isset($_REQUEST['upload'])){
            shn_gis_file_upload_seq($return_action_, $return_moduleL, $class_uuid_);
        } elseif(isset($_REQUEST['upload2'])){
            shn_gis_file_upload2_seq($return_action_ = NULL, $return_module_ = NULL, $class_uuid_ = NULL);
        } else {
            _shn_gis_file_form_select_options();
        }
    }


    /**
     * Add a new Feature Class.
     * vars specifiy where to return to after completing sequence.
     *
     * @global <type> $steps
     * @param <type> $return_action_
     * @param <type> $return_module_
     */
    function shn_gis_file_download_seq($return_action_ = NULL, $return_module_ = NULL)
    {
        global $steps;
        $steps = array('Feature Search', 'Feature Selection', 'Download & Extra Options');

        // If a user wishs to return to a page other than admin home on cancel or finish
        if(return_module_ != NULL && $return_action_ != NULL){
            $_SESSION['gis']['files']['return_action'] = $return_action_;
            $_SESSION['gis']['files']['return_module'] = $return_module_;
        }

        // If user cancels sequence
        if(isset($_REQUEST['cancel'])){
            add_warning(_t('Operation Canceled'));
            _shn_gis_file_download_return();
        }

        // if user is in sequence
        elseif(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                //
                case 'seq_2':
                    _shn_gis_file_download_seq_2();
                break;
                // 
                case 'seq_3':
                if(isset($_REQUEST['addmoresearch'])){
                    _shn_gis_file_download_seq_1(false);
                } elseif(isset($_REQUEST['download'])){
                    _shn_gis_file_download_seq_3();
                } else {
                    add_error(_("Something went wrong"));
                    _shn_gis_file_download_return();
                }
                break;
                // 
                case 'seq_4':
                if(isset($_REQUEST['back'])){
                    _shn_gis_file_download_seq_2();
                } else {
                    _shn_gis_file_download_seq_4();
                }
                break;
                // error
                default:
                add_error(_t('Something went wrong'));
                _shn_gis_file_download_return();
                break;
            }
        }

        // if user is starting sequence
        else {
            // enter detail page
            unset($_SESSION['gis']['files']);
            _shn_gis_file_download_seq_1();
        }
    }

    function shn_gis_file_upload_seq($return_action_ = NULL, $return_module_ = NULL)
    {
        global $steps;
        $steps = array('File Selection', 'Feature Selection', 'Upload & Extra Options');

        // If a user wishs to return to a page other than admin home on cancel or finish
        if(return_module_ != NULL && $return_action_ != NULL){
            $_SESSION['gis']['files']['return_action'] = $return_action_;
            $_SESSION['gis']['files']['return_module'] = $return_module_;
        }

        // If user cancels sequence
        if(isset($_REQUEST['cancel'])){
            add_warning(_t('Operation Canceled'));
            _shn_gis_file_upload_return();
        }

        // if user is in sequence
        elseif(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                // 
                case 'seq_2':
                _shn_gis_file_upload_seq_2();
                break;
                // 
                case 'seq_3':
                if(isset($_REQUEST['back'])){
                    _shn_gis_file_upload_seq_1();
                } else {
                    _shn_gis_file_upload_seq_3();
                }
                break;
                // 
                case 'seq_4':
                if(isset($_REQUEST['back'])){
                    _shn_gis_file_upload_seq_2();
                } else {
                    _shn_gis_file_upload_seq_4();
                }
                break;
                // error
                default:
                add_error(_t('Something went wrong'));
                _shn_gis_file_upload_return();
                break;
            }
        }

        // if user is starting sequence
        else {
            // enter detail page
            unset($_SESSION['gis']['files']);
            _shn_gis_file_upload_seq_1();
        }
    }


    // ==============================
    // Sequences Actions
    // ==============================


    function _shn_gis_file_download_seq_1($fresh = true)
    {
        global $global;
        global $steps;
        require_once $global['approot'] . '/inc/lib_gis/lib_gis_forms.inc';

        // Catch uuids
        if(isset($_REQUEST['count']) && !$fresh){
            $uuids = array();
            $limit = $_REQUEST['count'];
            for($i = 1; $i <= $limit; $i++){
                if(isset($_POST[$i])){
                    array_push($uuids, $_POST[$i]);
                }
            }
            $_SESSION['gis']['files']['feature_uuids'] = $uuids;
        }

        shn_form_progress_bar($steps, 1);
        $act = 'gis_file_download';
        $button_set = array('cancel' => true, 'next' => true);
        $form_opts = array('seq' => 'seq_2');
        shn_gis_form_feature_search($act, $button_set, $form_opts);
    }


    function _shn_gis_file_download_seq_2()
    {
        global $global;
        global $steps;
        require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
        shn_form_progress_bar($steps, 2);

        $keys = array('f_uuid'=>'1','f_class'=>'1','f_type'=>'1','f_projection'=>'1',
                    'f_coords'=>'1','f_module_item'=>'1','f_name'=>'1','f_description'=>'1',
                    'f_author'=>'1','f_url'=>'1','f_address'=>'1','f_event_date'=>'1','f_extended_data'=>'1');

        // Add features from new search.
        $new_features = shn_gis_get_features_other($keys, $_POST['l_uuid'], $_POST['c_uuid'], trim($_POST['f_author']), trim($_POST['f_event_date_from']), trim($_POST['f_event_date_to']), trim($_POST['f_name']));

        // Add pre-searched features.
        if(isset($_SESSION['gis']['files']['feature_uuids'])){
            $uuids = $_SESSION['gis']['files']['feature_uuids'];
            foreach($uuids as $uuid){
                $feature = shn_gis_get_features_uuid($uuid, $keys);
                // set existing features to extended data to 'selected_' to set them allready checked.
                $feature[0]['checked'] = 'checked_';
                $new_features = array_merge($new_features, $feature);
            }
        }

        $act = 'gis_file_download';
        $seq = 'seq_3';
        $button_set = array('cancel' => true, 'custom' => array(
                array('value' => _t('Add More Features'), 'submit_opts' => 'name = "addmoresearch"'),
                array('value' => _t('Continue To Download'), 'submit_opts' => 'name = "download"')));
        $keys2 = array('f_class'=>'1','f_coords'=>'1','f_name'=>'1','f_description'=>'1','f_author'=>'1','f_event_date'=>'1','select'=>'1');
        _shn_gis_file_form_feature_display($act, $seq, $button_set, $new_features, $keys2);
    }


    function _shn_gis_file_download_seq_3()
    {
        global $steps;
        shn_form_progress_bar($steps, 3);

        // Catch uuids
        if(isset($_REQUEST['count'])){
            $uuids = array();
            $limit = $_REQUEST['count'];
            for($i = 1; $i <= $limit; $i++){
                if(isset($_POST[$i])){
                    array_push($uuids, $_POST[$i]);
                }
            }
            $_SESSION['gis']['files']['feature_uuids'] = $uuids;
        }

        $act = 'gis_file_download';
        $seq = 'seq_4';
        $button_set = array('cancel' => true, 'back' => true, 'finish' => true);
        _shn_gis_file_form_download();
        _shn_gis_file_form_extra($act, $seq, $button_set);

    }


    function _shn_gis_file_download_seq_4()
    {
        global $global;
        require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

        $feed = false;
        $delete = false;
        $uuids = $_SESSION['gis']['files']['feature_uuids'];

        // Create a feed.
        if(isset($_POST['gis_publish'])){
            $feed = $_POST['gis_feed_name'];
            if('' == $feed){
                add_warning(_("Please enter a name for the feed"));
                _shn_gis_file_download_seq_3();
                return;
            } else {
                $feed_location = shn_gis_create_feed($feed, $uuids);
                if($feed_location === FALSE){
                    add_error(_("Failed to save feed"));
                } else {
                    add_confirmation(_("A feed has been successfully created at:") . '<a href="' . $feed_location . '">' . $feed_location . '</a>');
                }
            }
        }

        // remove selected features.
        if(isset($_POST['gis_delete'])){
            global $global;
            require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
            foreach($uuids as $uuid){
                if(shn_gis_remove_feature($uuid)){
                    add_confirmation(_("Feature uuid '"). $uuid . _("' have been removed from the system."));
                } else {
                    add_error(_("Feature uuid '"). $uuid . _("' could not be removed from the system."));
                }
            }
        }
        _shn_gis_file_download_return();
    }


    function _shn_gis_file_download_return()
    {
        if(isset($_SESSION['gis']['files']['return_action']) && isset($_SESSION['gis']['files']['return_module'])){
            $return_action = $_SESSION['gis']['files']['return_action'];
            $return_module = $_SESSION['gis']['files']['return_module'];
        } else {
            $return_action = 'gis_files';
            $return_module = 'admin';
        }
        unset($_SESSION['gis']['files']);
        _shn_gis_file_form_return($return_action, $return_module);
    }



    function shn_text_admin_gis_create_file2()
    {
        if(isset($_POST['opt_geo_file_type']) && isset($_SESSION['gis']['feature_uuids'])){
            global $global;
            require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
            
            $file_name = 'Sahana-Features';             
            $file_type = $_POST['opt_geo_file_type'];
            $feature_uuids = $_SESSION['gis']['feature_uuids'];
            $echo = false;
            print shn_gis_create_file($file_name, $file_type, $feature_uuids, $echo);
        }
    }









    function _shn_gis_file_upload_seq_1()
    {
        global $steps;
        global $conf;
        shn_form_progress_bar($steps, 1);
        $act = 'gis_file_upload';
        $seq = 'seq_2';
        $button_set = array('cancel' => true, 'next' => true);
        $extensions = $conf['gis_file_extensions'];
        unset($extensions[array_search('georss', $conf['gis_file_extensions'])]);
        $extension_str = ' .' . implode(', .', $extensions);
        _shn_gis_file_form_upload($act, $seq, $button_set, $extension_str);
    }

    function _shn_gis_file_upload_seq_2()
    {
        global $global;
        global $steps;
        require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
        require_once $global['approot'] . "/inc/lib_gis/lib_gis_file_factory_upload.inc";
        $path = '../www/tmp/dom.txt';

        // If returning to page no need to create tmp file.
        if(!isset($_REQUEST['back'])){

            $file = $_FILES['load'];

            // Print the error message if an error occurred with the Upload File
            display_errors($return=false, $clean_errors=true, $exit=false);

            // Check whether a file was uploaded
            if(!isset($file) || !shn_sm_check_file_upload()){
                _shn_gis_file_upload_seq_1();
                return;
            }

            // Sort points
            if(isset($_SESSION['gis']['files']['file'])) {
                $current_file = $_SESSION['gis']['files']['file'];
                $handle1 = fopen($current_file, "r");
                $contents = fread($handle1, filesize($current_file));
                fclose($handle1);
                $handle2 = fopen($path, 'w+');
                fwrite($handle2,$contents);
                fclose($handle2);
            }
        }

        // Discover and create aproprate file factory
        $file_type_ = $_SESSION['gis']['files']['filetype'];
        if ('gpx' == $file_type_){
            $GeoFactory = new GPXFactoryUpload($path);
        } elseif('gml' == $file_type_){
            $GeoFactory = new GMLFactoryUpload($path);
        } elseif('kml' === $file_type_){
            $GeoFactory = new KMLFactoryUpload($path);
        } elseif('georss' == $file_type_){
            $GeoFactory = new GeoRSSFactoryUpload($path);
        } else {
            add_error(_('File Type Unsuported'));
            return;
        }
        $features = $GeoFactory->shn_sm_geo_get_features();
        
        if(isset($_REQUEST['back']) && isset($_SESSION['gis']['files']['feature_ids_upload'])){
            foreach($_SESSION['gis']['files']['feature_ids_upload'] as $id){
                $features[$id - 1]['checked'] = 'checked_';
            } 
        }
        
        // Start page.
        shn_form_progress_bar($steps, 2);

        $act = 'gis_file_upload';
        $seq = 'seq_3';
        $button_set = array('cancel' => true, 'back' => true, 'next' => true);
        $keys = array('f_class'=>'1','f_coords'=>'1','f_name'=>'1','f_description'=>'1','f_author'=>'1','f_event_date'=>'1','select'=>'1');
        _shn_gis_file_form_feature_display($act, $seq, $button_set, $features, $keys);
    }

    function _shn_gis_file_upload_seq_3()
    {
        global $steps;
        shn_form_progress_bar($steps, 3);

        // Get selected features id to upload, save to session.
        if(isset($_REQUEST['count'])){
            $ids = array();
            $limit = $_REQUEST['count'];
            for($i = 1; $i <= $limit; $i++){
                if(isset($_POST[$i])){
                    array_push($ids, $_POST[$i]);
                }
            }
            $_SESSION['gis']['files']['feature_ids_upload'] = $ids;
        }


        // show form for extra options
        $act = 'gis_file_upload';
        $seq = 'seq_4';
        $button_set = array('cancel' => true, 'back' => true, 'finish' => true);
        _shn_gis_file_form_upload_extra($act, $seq, $button_set);
    }

    function _shn_gis_file_upload_seq_4()
    {
        global $global;
        require_once $global['approot'] . "/inc/lib_gis/lib_gis_file_factory_upload.inc";
        require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";

        // If Creating a feed check name.
        if(isset($_POST['gis_publish'])){
            $feed = $_POST['gis_feed_name'];
            if('' == $feed){
                add_error(_("Please enter a name for the feed"));
                _shn_gis_file_upload_seq_3();
                return;
            }
        }
        
        
        $ids = $_SESSION['gis']['files']['feature_ids_upload'];

        // discover and create aproprate file factory
        $path = '../www/tmp/dom.txt';
        $file_type_ = $_SESSION['gis']['files']['filetype'];
        if ('gpx' == $file_type_){
            $GeoFactory = new GPXFactoryUpload($path);
        } elseif('gml' == $file_type_){
            $GeoFactory = new GMLFactoryUpload($path);
        } elseif('kml' === $file_type_){
            $GeoFactory = new KMLFactoryUpload($path);
        } elseif('georss' == $file_type_){
            $GeoFactory = new GeoRSSFactoryUpload($path);
        } else {
            add_error(_('File Type Unsuported'));
            return;
        }

        // Get all features then add selected features to database.
        $uuids = array();
        $features = $GeoFactory->shn_sm_geo_get_features();
        if(count($ids) == 0){
            add_warning('You did not select any Waypoints.');
        } else{
            add_confirmation(_("The following Features have been successfully uploaded to Sahana internal database:"));
            foreach($ids as $id){
                $uuid = shn_gis_create_feature($features[$id - 1]);
                if($uuid){
                    add_confirmation(_("Feature number '"). $id . _("', name '"). $features[$id - 1]['f_name'] . _("', coords '"). $features[$id - 1]['f_coords'] . _("' was added."));
                    array_push($uuids, $uuid);
                } else {
                    add_error(_("Feature number '"). $id . _("', name '"). $features[$id - 1]['f_name'] . _("', coords '"). $features[$id - 1]['f_coords'] . _("' could not be added."));
                }
            }
        }

        if(isset($_POST['gis_publish'])){
            $feed_location = shn_gis_create_feed($feed, $uuids);
            if($feed_location === FALSE){
                add_error(_("Failed to save feed"));
            } else {
                add_confirmation(_("A feed has been successfully created at:") . '<a href="' . $feed_location . '">' . $feed_location . '</a>');
            }
        }

        _shn_gis_file_upload_return();
    }

    function _shn_gis_file_upload_return()
    {
        if(isset($_SESSION['gis']['files']['return_action']) && isset($_SESSION['gis']['files']['return_module'])){
            $return_action = $_SESSION['gis']['files']['return_action'];
            $return_module = $_SESSION['gis']['files']['return_module'];
        } else {
            $return_action = 'gis_files';
            $return_module = 'admin';
        }
        unset($_SESSION['gis']['files']);
        _shn_gis_file_form_return($return_action, $return_module);
    }





    // ==============================
    // Sequences Action Forms
    // ==============================

    function _shn_gis_file_form_feature_display($act, $seq, $button_set, $results_, $keys_)
    {
        global $global;
        require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";

        echo '<h2>' . _t("Select Features") . '</h2>';
        shn_form_fopen($act, null, null, array('req' => false));
        shn_gis_form_feature_display($results_, $keys_);
        shn_form_fsopen('Options');
        shn_form_hidden(array('seq' => $seq));
        shn_form_submit_set($button_set);
        shn_form_fsclose();
        shn_form_fclose();
    }

    function _shn_gis_file_form_download()
    {        
        shn_form_fopen("gis_create_file&stream=text", null, array('req_message' => false, 'name' => 'choose'));
        shn_form_fsopen(_t("Download"));
        shn_form_opt_select("opt_geo_file_type", "File Type");
        shn_form_submit(_t("Download"));
        shn_form_fsclose();
        shn_form_fclose();
    }

    function _shn_gis_file_form_extra($act, $seq, $button_set)
    {
        shn_form_fopen($act, null, null, array('req' => false));
        shn_form_fsopen(_t("Extra Options:"));
        shn_form_hidden(array('seq' => $seq));
        echo '<p>' . _('After download has completed click finish to apply extra options and return to main page.') . '</p>';
        echo '<br />';
        shn_form_label(_t('Feed Options:'));
        shn_form_checkbox('Check to publish', 'gis_publish', null, array('value'=>'gis_publish'));
        shn_form_text(_t('Feed name'),'gis_feed_name','size="20"');
        echo '<br />';
        shn_form_label(_t('Database Options:'));
        shn_form_checkbox('Remove Features From Database', 'gis_delete', null, array('value'=>'gis_delete'));
        echo '<br />';
        shn_form_fsclose();
        shn_form_submit_set($button_set);
        shn_form_fclose();
    }

    function _shn_gis_file_form_upload_extra($act, $seq, $button_set)
    {
        shn_form_fopen($act, null, null);
        shn_form_fsopen(_("Extra Options:"));
        shn_form_hidden(array('seq' => $seq));
        echo '<p>' . _('Click Finish to upload features to Sahanas internal database and apply extra options.') . '</p>';
        echo '<br />';
        shn_form_label(_('Feed Options:'));
        shn_form_checkbox('Check to publish', 'gis_publish', null, array('value'=>'gis_publish'));
        shn_form_text(_('Feed name'),'gis_feed_name','size="20"', array('req' => true));
        echo '<br />';
        shn_form_fsclose();
        shn_form_submit_set($button_set);
        shn_form_fclose();
    }


    function _shn_gis_file_form_upload($act, $seq, $button_set, $extension_str)
    {
        global $global;
        require_once $global['approot']."/inc/lib_form.inc";
        echo '<h2>' . _('Upload Waypoints') . '</h2>';
        shn_form_fopen($act, null, array('enctype'=>'enctype="multipart/form-data"', 'req_message'=>false));
        shn_form_hidden(array('seq' => $seq));
        shn_form_fsopen(_("Upload File"));
        echo "<p>" . _t('Upload a waypoint file with one of following extensions:') . $extension_str . "</p>";
        echo "<p><em><strong>"._('important: ')."</strong></em>"._('This system will only accept files which are well-formed and valid.')."</p>";
        shn_form_upload(_('Upload File'),"load");
        shn_form_fsclose();
        shn_form_submit_set($button_set);
        shn_form_fclose();
    }












    /**
     * Displays return options.
     *
     * @param <type> $return_action_
     * @param <type> $return_module_
     */
    function _shn_gis_file_form_return($return_action_, $return_module_)
    {
        shn_form_fopen($return_action_, $return_module_, array());
        shn_form_fsopen(_t('Return to Original Menu'));
        shn_form_submit(_t('Return'), 'name="return"');
        shn_form_fsclose();
        shn_form_fclose();
    }

    /**
     * Displays File options.
     */
    function _shn_gis_file_form_select_options()
    {
        shn_form_fopen('gis_files', null, array());
        shn_form_fsopen(_t('Feature Up/Download'));
        echo '<p>' . _t('Selection an operation to perform on internal features.') . '</p><br />';
        shn_form_fsopen(_t('Download Features'));
        echo '<p>' . _t('Download Features to a file.') . '</p><br />';
        shn_form_submit(_t('Download'), 'name="download"');
        shn_form_fsclose();
        shn_form_fsopen(_t('Internal - Upload Features.'));
        echo '<p>' . _t('Upload features from a file to Sahanas internal GIS database.') . '</p><br />';
        shn_form_submit(_t('Upload'), 'name="upload"');
        shn_form_fsclose();
        shn_form_fsopen(_t('External - Upload Features.'));
        echo '<p>' . _t('Upload features to an external overlay layer.') . '</p><br />';
        shn_form_submit(_t('Upload'), 'name="upload2"');
        shn_form_fsclose();
        shn_form_fsclose();
        shn_form_fclose();
    }








    function shn_gis_file_upload2_seq($return_action_ = NULL, $return_module_ = NULL)
    {

        global $global;
        global $conf;
        global $file;

        $file=$_FILES['load'];
        $extensions=array('kml','kmz','osm','xml');

        //check whether a file was uploaded
        if(isset($file)){
            //get the extension and the tmp name of the file
            $ext=end(explode('.',$_FILES['load']['name']));
            unset($_SESSION['gis']['file']);
            $_SESSION['gis']['file']="./res/OpenLayers/files/".basename($_FILES['load']['name']);
            //check for  directory write permission
            if(!is_writable('./res/OpenLayers/files')){
                add_error(_t('Make sure the files folder is writable'));
            }
            //check whether an error occurred
            else if($file['error']!= 0){
                //give error information
                switch ($file['error']){
                    case 1:
                    case 2:
                    add_error(_('The uploaded file exceeds the Max upload size'));
                    break;
                    case 3:
                    add_error(_('The uploaded file was only partially uploaded.'));
                    break;
                    case 4:
                    add_error(_('No file was uploaded :  Please press the browse button and select a file to upload before you press the next button'));
                    break;
                }
            }
            //check for correct extension
            else if(!in_array($ext,$extensions)){
                add_error("<b>".strtoupper($ext)."</b> : "._t("Please upload a file with one of these extensions:").'".kml", ".kmz", ".osm", ".xml"');
            }
            //check for file write permission
            else if(file_exists($_SESSION['gis']['file']) && !is_writable($_SESSION['gis']['file'])){
                add_error(_t('File already exists & is not writable'));
            }
            //move the uploaded file to the files directory, with the correct name
            else {
                move_uploaded_file($_FILES['load']['tmp_name'],$_SESSION['gis']['file']);
                add_confirmation(_t("File was uploaded"));
                if ("kmz"==$ext) {
                    // UNIX-specific:
                    //$execute = "unzip -u ".$global['approot']."www/".$_SESSION['gis']['file']." -d ".$global['approot']."www/res/OpenLayers/files";
                    //`$execute`;
                    // PHP 5.2.0+ or PECL:
                    if(function_exists("zip_open")) {
                        $dir = $global['approot'].'www/res/OpenLayers/files/';
                        $zipped = $global['approot']."www/".$_SESSION['gis']['file'];
                        $zip = zip_open($zipped);
                        while($zip_entry = zip_read($zip)) {
                            $entry = zip_entry_open($zip,$zip_entry);
                            $filename = zip_entry_name($zip_entry);
                            $target_dir = $dir.substr($filename,0,strrpos($filename,'/'));
                            $filesize = zip_entry_filesize($zip_entry);
                            if (is_dir($target_dir) || mkdir($target_dir)) {
                                if ($filesize > 0) {
                                    $contents = zip_entry_read($zip_entry, $filesize);
                                    file_put_contents($dir.$filename,$contents);
                                    $ext_contents=end(explode('.',$filename));
                                    if ("kml"==$ext_contents) {
                                        $input=$dir.$filename;
                                        $output=$dir.$filename.".w";
                                        $lines=file($input);
                                        $handle = fopen($output, 'w');
                                        foreach ($lines as $line_num => $line) {
                                            // Rewrite file to use correct path
                                            $search="<img src='";
                                            $replace="<img src='res/OpenLayers/files/";
                                            $line_out=str_replace($search,$replace,$line);
                                            $search="<href>";
                                            $replace="<href>res/OpenLayers/files/";
                                            $line=str_replace($search,$replace,$line_out);
                                            // If the URL was remote not local, then put it back!
                                            $search="<href>res/OpenLayers/files/http://";
                                            $replace="<href>http://";
                                            $line_out=str_replace($search,$replace,$line);
                                            fwrite($handle, $line_out);
                                        }
                                        fclose($handle);
                                        // All KMZ files seem to have just 'doc.kml' inside so make them more identifable & support multiple simultaneous uploads
                                        // (Multiple files in the normal 'files' folder are less likely to collide, but could be fixed by more rewriting)
                                        $basename=reset(explode('.',$_FILES['load']['name']));
                                        $newname = $dir.$basename.".kml";
                                        rename($output, $newname);
                                        // remove non-rewritten file:
                                        unlink ($input);
                                    }
                                }
                            }
                        }
                        add_confirmation(_t("File was decompressed"));
                        // remove zipped file:
                        unlink ($zipped);
                        add_confirmation(_t("File was deleted"));
                    } else {
                        if(version_compare(phpversion(), "5.2.0", "<"))
                        $infoVersion="(use PHP 5.2.0+ or <a href=\"http://pecl.php.net/package/zip\" target=_blank>PECL</a>)";

                        add_error(_t("You need to install/enable the php_zip extension")." $infoVersion "._t("to decompress KMZ files."));
                    }
                }
            }
        }

        //Print the error message if an error occurred with the Upload File
        display_errors($return=false,$clean_errors=true,$exit=false);
        //draw upload form
        _shn_gis_file_upload2_upload_files_form();

    }

    function _shn_gis_file_upload2_upload_files_form()
    {
        print '<h2>'._t("Upload Files").'</h2>';
        print '<p>'._t("This form allows uploading of files in").' <a href="http://en.wikipedia.org/wiki/Keyhole_Markup_Language" target=_blank>KML</a>, <a href="http://wiki.openstreetmap.org/index.php/Protocol" target=_blank>OSM</a> '._t("or").' <a href="http://en.wikipedia.org/wiki/Geography_Markup_Language" target=_blank>GML</a> '._t("format to").' www/res/OpenLayers/files</p>';
        print '<p>KMZ '._t("files will be unzipped upon upload").'.</p>';
        print '<p>'._t("NB Be sure that the file contains the actual data you want & isn't simply a 'Network Link'").'.</p>';
        print '<p>'._t("File should have one of the following extensions:").'.kml, .kmz, .osm '._t("or").' .xml</p>';

        global $global;
        include_once $global['approot']."/inc/lib_form.inc";

        $upload_help=_t("KML files should have the extension .kml or .kmz, OSM files should have the extension .osm, GML files should have the extension .xml.");
        shn_form_fopen("gis_files",null,array('enctype'=>'enctype="multipart/form-data"','req_message'=>false));
        shn_form_fsopen(_t("Upload File"));
        shn_form_upload(_t('Upload KML, OSM or GML'),"load",array('req'=>false,"help"=>$upload_help));
        shn_form_fsclose();
        shn_form_submit(_t("Upload"));
        shn_form_fclose();
        print "<br />";
        // List current directory contents
        _shn_gis_file_upload2_list_files();
    }

    function _shn_gis_file_upload2_list_files()
    // ToDo: Separate lists for the 3 different sorts
    {
        print '<h2>'._t("Current Files").'</h2>';
        print '<p>'._t("These are the files currently available on this server").':</p>';
        global $global;
        $dir=$global['approot'].'/www/res/OpenLayers/files';
        //Read into Arrays ready for sorting
        $kml = array();
        $osm = array();
        $gml = array();
        if ($handle = opendir($dir)) {
            while (false !== ($file = readdir($handle))) {
                if ($file != "." && $file != ".." && !is_dir($dir."/".$file)) {
                    $ext=end(explode('.',$file));
                    if ("kml"==$ext){
                        $kml[$file]="<a href=\"res/OpenLayers/files/".$file."\" target=_blank>".$file."</a><br />\n";
                    } else if ("osm"==$ext){
                        $osm[$file]="<a href=\"res/OpenLayers/files/".$file."\" target=_blank>".$file."</a><br />\n";
                    } else if ("xml"==$ext){
                        $gml[$file]="<a href=\"res/OpenLayers/files/".$file."\" target=_blank>".$file."</a><br />\n";
                    }
                }
            }
            // Sort arrays
            asort ($kml);
            asort ($osm);
            asort ($gml);
            // Print out to screen
            echo "<table><thead><td>KML</td><td>OSM</td><td>GML</td></thead>\n";
            echo "<tbody><tr><td valign='top'><table>\n";
            foreach ($kml as $key => $val) {
                echo "<tr><td style=\"border: 0px;\">$val</td></tr>\n";
            }
            echo "</table><td valign='top'><table>\n";
            foreach ($osm as $key => $val) {
                echo "<tr><td style=\"border: 0px;\">$val</td></tr>\n";
            }
            echo "</table><td valign='top'><table>\n";
            foreach ($gml as $key => $val) {
                echo "<tr><td style=\"border: 0px;\">$val</td></tr>\n";
            }
            echo "</table></td></tr></tbody></table>\n";
            closedir($handle);
        }
    }


