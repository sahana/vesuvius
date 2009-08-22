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
 *
 */

    // ==============================
    // Sequences
    // ==============================


    function shn_gis_feed_general_select()
    {
        if(isset($_REQUEST['feed_general'])){
            shn_gis_feed_general_seq($return_action_, $return_module_);
        } elseif(isset($_REQUEST['feed_feature_class'])){
            shn_gis_feed_feature_class_seq($return_action_, $return_module_);
        } elseif(isset($_REQUEST['feed_layer'])){
            shn_gis_feed_layer_seq($return_action_, $return_module_);
        } elseif(isset($_REQUEST['feed_review'])){
            shn_gis_feed_review_seq($return_action_, $return_module_);
        } else {
            _shn_gis_feed_form_select_options();
        }
    }


    function shn_gis_feed_general_seq($return_action_, $return_module_)
    {
        global $steps;
        $steps = array('Feature Search', 'Feature Selection', 'Create Feed');

        // If a user wishs to return to a page other than admin home on cancel or finish
        if(return_module_ != NULL && $return_action_ != NULL){
            $_SESSION['gis']['feeds']['return_action'] = $return_action_;
            $_SESSION['gis']['feeds']['return_module'] = $return_module_;
        }

        // If user cancels sequence
        if(isset($_REQUEST['cancel'])){
            add_warning(_t('Operation Canceled'));
            _shn_gis_feed_general_return();
        }

        // if user is in sequence
        elseif(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                //
                case 'seq_2':
                _shn_gis_feed_general_seq_2();
                break;
                //
                case 'seq_3':
                if(isset($_REQUEST['addmoresearch'])){
                    _shn_gis_feed_general_seq_1(false);
                } elseif(isset($_REQUEST['continue'])){
                    _shn_gis_feed_general_seq_3();
                } else {
                    add_error(_("Something went wrong"));
                    _shn_gis_feed_general_return();
                }
                break;
                //
                case 'seq_4':
                if(isset($_REQUEST['back'])){
                    _shn_gis_feed_general_seq_2();
                } else {
                    _shn_gis_feed_general_seq_4();
                }
                break;
                // error
                default:
                add_error(_t('Something went wrong'));
                _shn_gis_feed_general_return();
                break;
            }
        }

        // if user is starting sequence
        else {
            // enter detail page
            unset($_SESSION['gis']['feeds']);
            _shn_gis_feed_general_seq_1();
        }
    }



    function shn_gis_feed_feature_class_seq($return_action_, $return_module_)
    {
        global $steps;
        $steps = array('Feature Search', 'Feature Selection', 'Create Feed');

        // If a user wishs to return to a page other than admin home on cancel or finish
        if(return_module_ != NULL && $return_action_ != NULL){
            $_SESSION['gis']['feeds']['return_action'] = $return_action_;
            $_SESSION['gis']['feeds']['return_module'] = $return_module_;
        }

        // If user cancels sequence
        if(isset($_REQUEST['cancel'])){
            add_warning(_t('Operation Canceled'));
            _shn_gis_feed_feature_class_return();
        }

        // if user is in sequence
        elseif(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                //
                case 'seq_2':
                _shn_gis_feed_feature_class_seq_2();
                break;
                //
                case 'seq_3':
                if(isset($_REQUEST['back'])){
                    _shn_gis_feed_feature_class_seq_1();
                } else {
                    _shn_gis_feed_feature_class_seq_3();
                }
                break;
                //
                case 'seq_4':
                if(isset($_REQUEST['back'])){
                    _shn_gis_feed_feature_class_seq_2();
                } else {
                    _shn_gis_feed_feature_class_seq_4();
                }
                break;
                // error
                default:
                add_error(_t('Something went wrong'));
                _shn_gis_feed_feature_class_return();
                break;
            }
        }

        // if user is starting sequence
        else {
            // enter detail page
            unset($_SESSION['gis']['feeds']);
            _shn_gis_feed_feature_class_seq_1();
        }
    }


    function shn_gis_feed_layer_seq($return_action_, $return_module_)
    {
        global $steps;
        $steps = array('Feature Search', 'Feature Selection', 'Create Feed');

        // If a user wishs to return to a page other than admin home on cancel or finish
        if(return_module_ != NULL && $return_action_ != NULL){
            $_SESSION['gis']['feeds']['return_action'] = $return_action_;
            $_SESSION['gis']['feeds']['return_module'] = $return_module_;
        }

        // If user cancels sequence
        if(isset($_REQUEST['cancel'])){
            add_warning(_t('Operation Canceled'));
            _shn_gis_feed_layer_return();
        }

        // if user is in sequence
        elseif(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                //
                case 'seq_2':
                _shn_gis_feed_layer_seq_2();
                break;
                //
                case 'seq_3':
                if(isset($_REQUEST['back'])){
                    _shn_gis_feed_layer_seq_1();
                } else {
                    _shn_gis_feed_layer_seq_3();
                }
                break;
                //
                case 'seq_4':
                if(isset($_REQUEST['back'])){
                    _shn_gis_feed_layer_seq_2();
                } else {
                    _shn_gis_feed_layer_seq_4();
                }
                break;
                // error
                default:
                add_error(_t('Something went wrong'));
                _shn_gis_feed_layer_return();
                break;
            }
        }

        // if user is starting sequence
        else {
            // enter detail page
            unset($_SESSION['gis']['feeds']);
            _shn_gis_feed_layer_seq_1();
        }
    }

    
    
    function _shn_gis_feed_general_seq_1($fresh = true)
    {
        global $global;
        global $steps;
        require_once $global['approot'] . '/inc/lib_gis/lib_gis_forms.inc';
        
        // Catch uuids
        if(isset($_REQUEST['count']) && !$fresh){
            echo 'IN';
            $uuids = array();
            $limit = $_REQUEST['count'];
            for($i = 1; $i <= $limit; $i++){
                if(isset($_POST[$i])){
                    array_push($uuids, $_POST[$i]);
                }
            }
            $_SESSION['gis']['feeds']['feature_uuids'] = $uuids;
        }
        
        shn_form_progress_bar($steps, 1);
        $act = 'gis_feed_general';
        $button_set = array('cancel' => true, 'next' => true);
        $form_opts = array('seq' => 'seq_2');
        shn_gis_form_feature_search($act, $button_set, $form_opts);

    }

    function _shn_gis_feed_general_seq_2()
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
        if(isset($_SESSION['gis']['feeds']['feature_uuids'])){
            $uuids = $_SESSION['gis']['feeds']['feature_uuids'];
            foreach($uuids as $uuid){
                $feature = shn_gis_get_features_uuid($uuid, $keys);
                // set existing features to extended data to 'selected_' to set them allready checked.
                $feature[0]['checked'] = 'checked_';
                $new_features = array_merge($new_features, $feature);
            }
        }

        $act = 'gis_feed_general';
        $seq = 'seq_3';
        $button_set = array('cancel' => true, 'custom' => array(
                array('value' => _t('Add More Features'), 'submit_opts' => 'name = "addmoresearch"'),
                array('value' => _t('Continue To Create feed'), 'submit_opts' => 'name = "continue"')));
        $keys2 = array('f_class'=>'1','f_coords'=>'1','f_name'=>'1','f_description'=>'1','f_author'=>'1','f_event_date'=>'1','select'=>'1');
        _shn_gis_feed_form_feature_display($act, $seq, $button_set, $new_features, $keys2);
    }

    function _shn_gis_feed_general_seq_3()
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
            $_SESSION['gis']['feeds']['feature_uuids'] = $uuids;
        }
        $act = 'gis_feed_general';
        $seq = 'seq_4';
        $button_set = array('cancel' => true, 'back' => true, 'finish' => true);
        _shn_gis_feed_form_general_extra($act, $seq, $button_set);
    }

    function _shn_gis_feed_general_seq_4()
    {
        global $global;
        require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

        $type = 
        $uuids = $_SESSION['gis']['feeds']['feature_uuids'];
        // Create a feed.
            $feed = $_POST['gis_feed_name'];
            echo 'type' . $type = $_POST['opt_geo_file_type'];
            if('' == $feed){
                add_warning(_("Please enter a name for the feed"));
                _shn_gis_feed_general_seq_3();
                return;
            } else {
                $feed_location = shn_gis_create_feed($feed, $uuids, $type);
                if($feed_location === FALSE){
                    add_error(_("Failed to save feed"));
                } else {
                    add_confirmation(_("A feed has been successfully created at:") . '<a href="' . $feed_location . '">' . $feed_location . '</a>');
                }
            }
        _shn_gis_feed_general_return();
    }


    function _shn_gis_feed_general_return()
    {
        if(isset($_SESSION['gis']['feeds']['return_action']) && isset($_SESSION['gis']['feeds']['return_module'])){
            $return_action = $_SESSION['gis']['feeds']['return_action'];
            $return_module = $_SESSION['gis']['feeds']['return_module'];
        } else {
            $return_action = 'gis_feeds';
            $return_module = 'admin';
        }
        unset($_SESSION['gis']['feeds']);
        _shn_gis_feed_form_return($return_action, $return_module);
    }



    function _shn_gis_feed_feature_class_seq_1()
    {
        global $global;
        global $conf;
        require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
        $feature_classes = shn_gis_get_feature_class_all();
        foreach($feature_classes as $feature_class){
            array_push($_SESSION['gis']['feeds']['feature_uuids'], $feature_class['f_uuid']);
            foreach($conf['gis_feed_feature_classes'] as $class){
                if($feature_class['f_uuid'] == $class){
                    $feature_class['checked'] = 'checked_';
                    break;
                }
            }
        }
        $act = 'gis_form_feature_class';
        $seq = 'seq_2';
        $button_set = array('cancel' => true, 'next' => true);
        _shn_gis_feed_form_feature_class_display($act, $seq, $button_set, $feature_classes);
    }

    function _shn_gis_feed_feature_class_seq_2()
    {
        foreach($_SESSION['gis']['feeds']['feature_uuids'] as $feature_uuid){
            if(isset($_POST[$feature_uuid])){
                array_push($conf['gis_feed_feature_classes'], $feature_uuid);
            } else {
                array_pull($conf['gis_feed_feature_classes'], $feature_uuid);
            }
        }
    }

    function _shn_gis_feed_feature_class_seq_3()
    {

    }


    
    function _shn_gis_feed_layer_seq_1()
    {
        
    }
    
    
    
    
    
    
    
    

    function _shn_gis_feed_form_feature_class_display($act, $seq, $button_set, $feature_classes)
    {
        global $shn_tabindex;
        
        shn_form_fopen($act, null, null);
        shn_form_fsopen(_("Select Feature Classes:"));
        shn_form_hidden(array('seq' => $seq));
        echo '<p>' . _t('Select Feature Classes to display as feeds') . '</p>';
        echo '<table>';
        echo '<thead>';
        echo '<td>' . _t('Name') . '</td>';
        echo '<td>' . _t('Description') . '</td>';
        echo '<td>' . _t('Icon') . '</td>';
        echo '<td>' . _t('Select') . '</td>';
        echo '</thead>';
        $count = 0;
        foreach($feature_classes as $feature_class){
            $count++;
            echo '<tr>';
            echo '<td>' . $feature_class['c_name'] . '</td>';
            echo '<td>' . $feature_class['c_description'] . '</td>';
            echo '<td>' . $feature_class['c_icon'] . '</td>';
            $checked = '';
            if('checked_' == $feature_class['checked']){
                $checked = 'checked = "checked"';
            }
            echo '<td><input type="checkbox" name="' . $feature_class['c_uuid'] . '" id="' . $count . '" value="' . $feature_class['c_uuid'] . '" ' . $checked . ' tabindex="' . ++$shn_tabindex . '" /></td>';
            echo '</tr>';
        }
        echo '</table>';
        shn_form_fsclose();
        shn_form_fclose();
    }


    function _shn_gis_feed_form_feature_display($act, $seq, $button_set, $results_, $keys_)
    {
        global $global;
        require_once $global['approot']."/inc/lib_gis/lib_gis_forms.inc";

        echo '<h2>' . _t("Select Features") . '</h2>';
        shn_form_fopen($act, null, null, array('req' => false));
        shn_form_hidden(array('seq' => $seq));
        shn_gis_form_feature_display($results_, $keys_);
        shn_form_fsopen('Options');
        shn_form_hidden(array('seq' => $seq));
        shn_form_submit_set($button_set);
        shn_form_fsclose();
        shn_form_fclose();
    }

    function _shn_gis_feed_form_general_extra($act, $seq, $button_set)
    {
        shn_form_fopen($act, null, null, array('req' => false));
        shn_form_hidden(array('seq' => $seq));
        shn_form_fsopen(_t("Feed Options:"));
        echo '<p>' . _t('Feeds will be created in the default feed folder which is "/export/feed type/feed name"') . '</p><br />';
        shn_form_opt_select("opt_geo_file_type", "Feed Type");
        shn_form_text(_t('Feed name'),'gis_feed_name','size="20"');
        // shn_form_checkbox('Dynamic', 'gis_feed_dynamic', null, array('value'=>'gis_feed_dynamic' ));
        shn_form_fsclose();
        shn_form_submit_set($button_set);
        shn_form_fclose();
    }


    
    function _shn_gis_feed_form_return($return_action_, $return_module_)
    {
        shn_form_fopen($return_action_, $return_module_, array());
        shn_form_fsopen(_t('Return to Original Menu'));
        shn_form_submit(_t('Return'), 'name="return"');
        shn_form_fsclose();
        shn_form_fclose();
    }

    /**
     * Displays Feed options.
     */
    function _shn_gis_feed_form_select_options()
    {
        shn_form_fopen('gis_feeds', null, array());
        shn_form_fsopen(_t('Feeds'));
        echo '<p>' . _t('Selection an operation to perform on internal features.') . '</p><br />';
        shn_form_fsopen(_t('Review Feeds.'));
        echo '<p>' . _t('Review all currently available feeds.') . '</p><br />';
        shn_form_submit(_t('Review Feeds'), 'name="feed_"');
        shn_form_fsclose();
        shn_form_fsopen(_t('General Feeds'));
        echo '<p>' . _t('Create a feed from a selection of Features.') . '</p><br />';
        shn_form_submit(_t('General Feeds'), 'name="feed_general"');
        shn_form_fsclose();
                shn_form_fsopen(_t('Layer Feeds.'));
        echo '<p>' . _t('Choose which layers to display as feeds.') . '</p><br />';
        shn_form_submit(_t('Layer Feeds'), 'name="feed_layer"');
        shn_form_fsclose();
        shn_form_fsopen(_t('Feature Class Feeds.'));
        echo '<p>' . _t('Choose which feature classes to display as feeds.') . '</p><br />';
        shn_form_submit(_t('Feature Class Feeds'), 'name="feed_feature_class"');
        shn_form_fsclose();
        shn_form_fsclose();
        shn_form_fclose();
    }










