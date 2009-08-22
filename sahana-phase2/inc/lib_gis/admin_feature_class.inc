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
 * @author     Richard Smith <s0459387@sms.ed.ac.uk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * 
 * Contains page sequences for creating, editing and removing Feature Classes.
 * 
 * All sequences are self contained and can be instigated by calling one of
 * the following functions:
 * 
 * shn_gis_internal_class_add_seq($return_action_, $return_module_)
 * shn_gis_internal_class_edit_seq($return_action_, $return_module_, $class_uuid_)
 * shn_gis_internal_class_remove_seq($return_action_, $return_module_, $class_uuid_)
 * 
 * Where $return_module_ is the module acronym to return to after completing the seq
 * and $return_action_ is the action to perform on returning.
 * 
 * $class_uuid_ is the Feature Class uuid to perfom the action on (if already known).
 *  
 */

// ==============================
// Sequences
// ==============================

/**
 * Select Option depending on action wanted, Options:
 * Add new Feature Class.
 * Edit existing Feature Class.
 * Delete Feature Class.
 * 
 * @param <type> $return_action_
 * @param <type> $return_module_
 * @param <type> $class_uuid_
 */
function shn_gis_internal_class_general_select($return_action_ = null, $return_module_ = null, $class_uuid_ = null)
{
    if(isset($_REQUEST['add'])){
        shn_gis_internal_class_add_seq($return_action_, $return_module_);
    } elseif(isset($_REQUEST['edit'])){
        shn_gis_internal_class_edit_seq($return_action_, $return_moduleL, $class_uuid_);
    } elseif(isset($_REQUEST['remove'])){
        shn_gis_internal_class_remove_seq($return_action_ = null, $return_module_ = null, $class_uuid_ = null);
    } else {    
        _shn_gis_internal_class_form_select_options();
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
function shn_gis_internal_class_add_seq($return_action_ = null, $return_module_ = null)
{
    global $steps;
    $steps = array('General Details', 'Layer Details', 'Confim');

    // If a user wishs to return to a page other than admin home on cancel or finish
    if(return_module_ != null && $return_action_ != null){
        $_SESSION['gis']['feature_class']['return_action'] = $return_action_;
        $_SESSION['gis']['feature_class']['return_module'] = $return_module_;
    }

    // If user cancels sequence
    if(isset($_REQUEST['cancel'])){
        add_warning(_t('Operation Canceled'));
        _shn_gis_internal_class_add_return();
    }

    // if user is in sequence
    elseif(isset($_REQUEST['seq'])){
        switch($_REQUEST['seq']){
            // add layers
            case 'seq_2':
            if(isset($_REQUEST['back'])){
                _shn_gis_internal_class_add_seq_1();
            } else {
                _shn_gis_internal_class_add_seq_2();
            }
            break;
            // confirm page
            case 'seq_3':
            if(isset($_REQUEST['back'])){
                _shn_gis_internal_class_add_seq_1();
            } else {
                _shn_gis_internal_class_add_seq_3();
            }
            break;
            // creating new class
            case 'seq_4':
            if(isset($_REQUEST['back'])){
                _shn_gis_internal_class_add_seq_2();
            } else {
                _shn_gis_internal_class_add_seq_4();
            }
            break;
            // error
            default:
            add_error(_t('Something went wrong'));
            _shn_gis_internal_class_add_return();
            break;
        }
    }

    // if user is starting sequence
    else {
        // enter detail page
        unset($_SESSION['gis']['feature_class']);
        _shn_gis_internal_class_add_seq_1();
    }
}

/**
 * Edit a Feature Class.
 * vars specifiy where to return to after completing sequence.
 *
 * If user knows classid allready can drop straight into editing form by
 * setting $class_uuid_ to the class to edit.
 *
 * @global <type> $steps
 * @param <type> $return_action_
 * @param <type> $return_module_
 * @param <type> $class_uuid_
 */
function shn_gis_internal_class_edit_seq($return_action_ = null, $return_module_ = null, $class_uuid_ = null)
{
    global $steps;
    $steps = array('Search', 'General Details', 'Layer Details', 'Confim');

    // If a user wishs to return to a page other than admin home on cancel or finish
    if(return_module_ != null && $return_action_ != null){
        $_SESSION['gis']['feature_class']['return_action'] = $return_action_;
        $_SESSION['gis']['feature_class']['return_module'] = $return_module_;
    }

    // If user wishes to drop straight into editing a pre known class
    if($class_uuid_ != null){
        $_REQUEST['c_uuid'] = $class_uuid_;
        $_REQUEST['seq'] = 'seq_2';
    }

    // If user cancels sequence
    if(isset($_REQUEST['cancel'])){
        add_warning(_t('Operation Canceled'));
        _shn_gis_internal_class_edit_return();
    }

    // if user is in sequence
    elseif(isset($_REQUEST['seq'])){
        switch($_REQUEST['seq']){
            //
            case 'seq_2':
            _shn_gis_internal_class_edit_seq_2();
            break;
            //
            case 'seq_3':
            if(isset($_REQUEST['back'])){
                _shn_gis_internal_class_edit_seq_1();
            } else {
                _shn_gis_internal_class_edit_seq_3();
            }
            break;
            //
            case 'seq_4':
            if(isset($_REQUEST['back'])){
                _shn_gis_internal_class_edit_seq_2();
            } else{
                _shn_gis_internal_class_edit_seq_4();
            }
            break;
            //
            case 'seq_5':
            if(isset($_REQUEST['back'])){
                _shn_gis_internal_class_edit_seq_3();
            } else{
                _shn_gis_internal_class_edit_seq_5();
            }
            break;
            // error
            default:
            add_error(_t('Something went wrong'));
            _shn_gis_internal_class_edit_return();
            break;
        }
    }

    // if user is starting sequence
    else {
        // enter detail page
        unset($_SESSION['gis']['feature_class']);
        _shn_gis_internal_class_edit_seq_1();
    }
}

/**
 * Remove a Feature Class.
 * vars specifiy where to return to after completing sequence.
 *
 * If user knows classid allready can drop straight into editing form by
 * setting $class_uuid_ to the class to edit.
 * 
 * @global <type> $steps
 * @param <type> $return_action_
 * @param <type> $return_module_
 * @param <type> $class_uuid_
 */
function shn_gis_internal_class_remove_seq($return_action_ = null, $return_module_ = null, $class_uuid_ = null)
{
    global $steps;
    $steps = array('Search', 'Features', 'Confim');

    // If a user wishs to return to a page other than admin home on cancel or finish
    if(return_module_ != null && $return_action_ != null){
        $_SESSION['gis']['feature_class']['return_action'] = $return_action_;
        $_SESSION['gis']['feature_class']['return_module'] = $return_module_;
    }

    // If user wishes to drop straight into removeing a pre known class
    if($class_uuid_ != null){
        $_REQUEST['c_uuid'] = $class_uuid_;
        $_REQUEST['seq'] = 'seq_2';
    }

    // If user cancels sequence
    if(isset($_REQUEST['cancel'])){
        add_warning(_t('Operation Canceled'));
        _shn_gis_internal_class_remove_return();

    }

    // if user is in sequence
    elseif(isset($_REQUEST['seq'])){
        switch($_REQUEST['seq']){
            //
            case 'seq_2':
            _shn_gis_internal_class_remove_seq_2();
            break;
            //
            case 'seq_3':
            if(isset($_REQUEST['back'])){
                _shn_gis_internal_class_remove_seq_1();
            } else {
                _shn_gis_internal_class_remove_seq_3();
            }
            break;
            //
            case 'seq_4':
            if(isset($_REQUEST['back'])){
                _shn_gis_internal_class_remove_seq_2();
            } else {
                _shn_gis_internal_class_remove_seq_4();
            }
            break;
            // error
            default:
            add_error(_t('Something went wrong'));
            _shn_gis_internal_class_remove_return();
            break;
        }
    }

    // if user is starting sequence
    else {
        // enter detail page
        unset($_SESSION['gis']['feature_class']);
        _shn_gis_internal_class_remove_seq_1();
    }
}



// ==============================
// Sequences Actions
// ==============================

// ==============
// Add a Feature Class
// ==============

/**
 * Displays page on which to enter new feature class details.
 * 
 * @global <type> $global
 */
function _shn_gis_internal_class_add_seq_1()
{
    global $global;
    global $steps;
    require_once $global['approot'].'/inc/lib_gis/list_markers.inc';
    
    // Display progress bar.
    shn_form_progress_bar($steps, 1);
    
    // Set forms if allready entered.
    $button_set = array('cancel' => true, 'next' => true);
    if(isset($_REQUEST['back'])){
        $name = $_SESSION['gis']['feature_class']['name'];
        $marker = $_SESSION['gis']['feature_class']['icon'];
        $desc = $_SESSION['gis']['feature_class']['description'];
        _shn_gis_internal_class_form_general_options('gis_database_classes_add', 'seq_2', $button_set, $name, $marker, $desc);
    } else {       
        _shn_gis_internal_class_form_general_options('gis_database_classes_add', 'seq_2', $button_set);
    }
     
    // List existing markers.
    _shn_gis_list_markers();

}

/**
 * Checks values from enter details page.
 * Prints layers page.
 * 
 * @global <type> $global
 * @global <type> $steps
 * @return <type>
 */
function _shn_gis_internal_class_add_seq_2()
{
    global $global;
    global $steps;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

    // Run checks on values entered on general details form
    if(isset($_REQUEST['next'])){
        $error = false;

        // check class name
        if(isset($_REQUEST['gis_feature_class_name']) && trim($_REQUEST['gis_feature_class_name']) != ''){
            $_SESSION['gis']['feature_class']['name'] = trim($_REQUEST['gis_feature_class_name']);
        } else {
            add_error(_t('Enter Feature Class Name'));
            $error = true;
        }

        // check marker url
        if(isset($_REQUEST['gis_feature_class_marker']) && FALSE != getimagesize($_REQUEST['gis_feature_class_marker'])){
            $_SESSION['gis']['feature_class']['icon'] =  trim($_REQUEST['gis_feature_class_marker']);
        } else {
            add_error(_t('Enter a vaid Marker Link'));
            $error = true;
        }

        $_SESSION['gis']['feature_class']['description'] = $_REQUEST['gis_feature_class_description'];

        // If error return to general details form.
        if($error){
            _shn_gis_internal_class_add_seq_1();
            return;
        }
    }
    
    // Show progress bar
    shn_form_progress_bar($steps, 2);
    
    // Finds all layers checks any that have allready been checked.
    $layers = shn_gis_get_layers_all();
    if(isset($_SESSION['gis']['feature_class']['layer_uuids'])){
        $uuids = $_SESSION['gis']['feature_class']['layer_uuids'];
        for($i = 0; $i < count($layers); $i++){
            foreach($uuids as $uuid){
                if($layers[$i]['l_uuid'] == $uuid){
                    $layers[$i]['checked'] = '1';
                }
            }
        }
    }
    $button_set = array('cancel' => true, 'back' => true, 'next' => true);
    _shn_gis_internal_class_form_layer_options('gis_database_classes_add', 'seq_3', $button_set, $layers);
}

/**
 * Shows confirm page.
 * 
 * @global <type> $global
 * @global <type> $steps
 */
function _shn_gis_internal_class_add_seq_3()
{
    global $global;
    global $steps;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
    
    // Show progress bar
    shn_form_progress_bar($steps, 3);
    echo '<h2>' . _t("Confirm New Feature Class Details") . '</h2>';
    
    if(isset($_REQUEST['next'])){
        // Catch layer uuids from previous form.
        $uuids = array();
        $limit = $_REQUEST['count'];
        for($i = 1; $i <= $limit; $i++){
            if(isset($_POST[$i])){
                array_push($uuids, $_POST[$i]);
            }
        }
        $_SESSION['gis']['feature_class']['layer_uuids'] = $uuids;
    } else {
        $uuids = $_SESSION['gis']['feature_class']['layer_uuids'];
    }

    // Get layers from uuids to display
    $layers = array();
    foreach($uuids as $uuid){
        array_push($layers, shn_gis_get_layers_uuid($uuid));
    }
    
    $button_set = array('cancel' => true, 'back' => true, 'finish' => true);
    _shn_gis_internal_class_form_confim('gis_database_classes_add', 'seq_4', $button_set, $_SESSION['gis']['feature_class']['name'], $_SESSION['gis']['feature_class']['icon'], $_SESSION['gis']['feature_class']['description'], $layers);
}

/**
 * Adds Feature Class and shows return page.
 * 
 * @global <type> $global
 */
function _shn_gis_internal_class_add_seq_4()
{
    global $global;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

    if(isset($_REQUEST['finish'])){
        
        $error = false;
        // set new feature class vars.
        $module_ref = '';
        $name = $_SESSION['gis']['feature_class']['name'];
        $description = $_SESSION['gis']['feature_class']['description'];
        $icon = $_SESSION['gis']['feature_class']['icon'];
        $color = '';

        if($name != null && $name != '' && $icon != null && $icon != ''){
            
            // Create new feature class.
            $uuid = shn_gis_create_feature_class($module_ref, $name, $description, $icon, $color);
        
            // Show confimation if successfull or error if not.
            if($uuid){
                add_confirmation(_t('Added New Feature Class.'));
                $layer_uuids = $_SESSION['gis']['feature_class']['layer_uuids'];
                foreach($layer_uuids as $layer_uuid){
                    shn_gis_insert_layer_feature_class($layer_uuid, array($uuid));
                }
                add_confirmation(_t('Added Feature Class to Layers.'));
            } else{
                add_error(_t('Feature Class could not be created.'));
            }
        } else {
            add_error(_t('Feature Class could not be created. Insufficient details'));  
        }

        // Show return page.
        _shn_gis_internal_class_add_return();
    }
}

/**
 * Displays button to return to location prior to starting sequence
 */
function _shn_gis_internal_class_add_return()
{
    if(isset($_SESSION['gis']['feature_class']['return_action']) && isset($_SESSION['gis']['feature_class']['return_module'])){
        $return_action = $_SESSION['gis']['feature_class']['return_action'];
        $return_module = $_SESSION['gis']['feature_class']['return_module'];
    } else {
        $return_action = 'gis_database_classes';
        $return_module = 'admin';
    }
    
    // Unset all session values.
    unset($_SESSION['gis']['feature_class']);
    _shn_gis_internal_class_form_return($return_action, $return_module);
}


// ==============
// Edit a Feature Class
// ==============

/**
 * Shows form to select a Feature Class.
 * 
 * @global <type> $steps
 */
function _shn_gis_internal_class_edit_seq_1()
{
    global $steps;
    shn_form_progress_bar($steps, 1);
    
    $button_set = array('cancel' => true, 'next' => true);
    _shn_gis_internal_class_form_search('gis_database_classes_edit', 'seq_2', $button_set);
}

/**
 * Show form to edit the general details of a Feature Class.
 * 
 * @global <type> $global
 * @global <type> $steps
 */
function _shn_gis_internal_class_edit_seq_2()
{
    global $global;
    global $steps;
    require_once $global['approot'].'/inc/lib_gis/list_markers.inc';
    
    // Show progress bar
    shn_form_progress_bar($steps, 2);
    
    // If details aready entered show in forms
    if(isset($_REQUEST['back'])){
        $name = $_SESSION['gis']['feature_class']['name'];
        $marker = $_SESSION['gis']['feature_class']['icon'];
        $desc = $_SESSION['gis']['feature_class']['description'];
    } else{
        require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
        $feature_class = shn_gis_get_feature_class_uuid($_REQUEST['c_uuid']);
        $name = $feature_class['c_name'];
        $marker = $feature_class['c_icon'];
        $desc = $feature_class['c_description'];
        $_SESSION['gis']['feature_class']['uuid'] = $feature_class['c_uuid'];
    }
    
    // Show general options
    $button_set = array('cancel' => true, 'back' => true, 'next' => true);
    _shn_gis_internal_class_form_general_options('gis_database_classes_edit', 'seq_3', $button_set, $name, $marker, $desc);
    
    // Show markers available in system
    _shn_gis_list_markers();
}

/**
 * Check General details
 * Edit layers feature class belongs to.
 * 
 * @global <type> $global
 * @global <type> $steps
 * @return <type>
 */
function _shn_gis_internal_class_edit_seq_3()
{
    global $global;
    global $steps;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

    if(isset($_REQUEST['next'])){
        $error = false;
        
        // check class name
        if(isset($_REQUEST['gis_feature_class_name']) && trim($_REQUEST['gis_feature_class_name']) != ''){
            $name = trim($_REQUEST['gis_feature_class_name']);
        } else {
            add_error(_t('Enter Feature Class Name'));
            $error = true;
        }
        
        // check marker url
        if(isset($_REQUEST['gis_feature_class_marker']) && FALSE != getimagesize($_REQUEST['gis_feature_class_marker'])){
            $marker = trim($_REQUEST['gis_feature_class_marker']);
        } else {
            add_error(_t('Enter a Valid Marker Link'));
            $error = true;
        }

        $desc = $_REQUEST['gis_feature_class_description'];
        if($error){
            _shn_gis_internal_class_edit_seq_2();
            return;
        } else {
            $_SESSION['gis']['feature_class']['name'] = $name;
            $_SESSION['gis']['feature_class']['icon'] = $marker;
            $_SESSION['gis']['feature_class']['description'] = $desc;
        }
    }
    // Show progress bar.
    shn_form_progress_bar($steps, 3);
    
    // find layers class allready belongs to.
    $layers = shn_gis_get_layers_all();
    $uuids = array();
    if(isset($_SESSION['gis']['feature_class']['layer_uuids'])){
        $uuids = $_SESSION['gis']['feature_class']['layer_uuids'];
    } elseif(isset($_SESSION['gis']['feature_class']['uuid'])){
        $lyrs = shn_gis_get_layers_feature_class($_SESSION['gis']['feature_class']['uuid']);
        foreach($lyrs as $lyr){
            array_push($uuids, $lyr['l_uuid']);
        }
    }
    
    // Check layers that feature class allready belongs to.
    for($i = 0; $i < count($layers); $i++){
        foreach($uuids as $uuid){
            if($layers[$i]['l_uuid'] == $uuid){
                $layers[$i]['checked'] = '1';
            }
        }
    }

    // Show edit layers form
    $button_set = array('cancel' => true, 'back' => true, 'next' => true);
    _shn_gis_internal_class_form_layer_options('gis_database_classes_edit', 'seq_4', $button_set, $layers);

}

/**
 * Show confimation page
 * 
 * @global <type> $global
 * @global <type> $steps
 */
function _shn_gis_internal_class_edit_seq_4()
{
    global $global;
    global $steps;
    shn_form_progress_bar($steps, 4);
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

    // Catch layer uuids
    $uuids = array();
    $limit = $_REQUEST['count'];
    for($i = 1; $i <= $limit; $i++){
        if(isset($_POST[$i])){
            array_push($uuids, $_POST[$i]);
        }
    }
    $_SESSION['gis']['feature_class']['layer_uuids'] = $uuids;

    $layers_new = array();
    foreach($uuids as $uuid){
        array_push($layers_new, shn_gis_get_layers_uuid($uuid));
    }

    $feature_class = shn_gis_get_feature_class_uuid($_SESSION['gis']['feature_class']['uuid']);
    $name_old = $feature_class['c_name'];
    $marke_old = $feature_class['c_icon'];
    $desc_old = $feature_class['c_description'];
    $layers_old = shn_gis_get_layers_feature_class($_SESSION['gis']['feature_class']['uuid']);
    
    $name_new = $_SESSION['gis']['feature_class']['name'];
    $desc_new = $_SESSION['gis']['feature_class']['description'];
    $icon_new = $_SESSION['gis']['feature_class']['icon'];

    echo '<h2>' . _t('Confirm') . '</h2>';
    echo '<h2>' . _t('Original Feature Class Details') . '</h2>';
    _shn_gis_internal_class_form_confim('gis_database_classes_edit', 'seq_5', array(), $name_old, $marke_old, $desc_old, $layers_old);
    $button_set = array('cancel' => true, 'back' => true, 'finish' => true);
    echo '<h2>' . _t('New Feature Class Details') . '</h2>';
    _shn_gis_internal_class_form_confim('gis_database_classes_edit', 'seq_5', $button_set, $name_new, $icon_new, $desc_new, $layers_new);
}

/**
 * Edits class and returns confimation error depending on success.
 * 
 * @global <type> $global
 */
function _shn_gis_internal_class_edit_seq_5()
{
    global $global;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';

    $c_uuid = $_SESSION['gis']['feature_class']['uuid'];
    $name = $_SESSION['gis']['feature_class']['name'];
    $desc = $_SESSION['gis']['feature_class']['description'];
    $icon = $_SESSION['gis']['feature_class']['icon'];
    
    if($c_uuid != '' && $c_uuid != null && $name != '' && $name != null && $icon != '' && $icon != null){
    
        $keys_ = array(
         'c_name'       => $name,
         'c_description'=> $desc,
         'c_icon'       => $icon
        );
    
        // modify feature class
        $ok = shn_gis_modify_feature_class($c_uuid, $keys_);
        if($ok){
            add_confirmation(_t('Edited Feature Class.'));
            $layer_uuids = $_SESSION['gis']['feature_class']['layer_uuids'];
            $all_layers = shn_gis_get_layers_all();
        
            // remove feature class from all layers.
            foreach($all_layers as $layer){
                shn_gis_remove_layer_feature_class($layer['l_uuid'], array($c_uuid));
            }
        
            // add feature class to selected layers.
            foreach($layer_uuids as $layer_uuid){
                shn_gis_insert_layer_feature_class($layer_uuid, array($c_uuid));
            }
            add_confirmation(_t('Added Feature Class to Layers.'));
        } else{
            add_error(_t('Feature Class could not be edited.'));
        }
    } else{
        add_error(_t('Feature Class could not be edited. Insufficient details'));
    }
    // Display return options.
    _shn_gis_internal_class_add_return();
}

/**
 * Return options for edit Feature Class.
 */
function _shn_gis_internal_class_edit_return()
{
    if(isset($_SESSION['gis']['feature_class']['return_action']) && isset($_SESSION['gis']['feature_class']['return_module'])){
        $return_action = $_SESSION['gis']['feature_class']['return_action'];
        $return_module = $_SESSION['gis']['feature_class']['return_module'];
    } else {
        $return_action = 'gis_database_classes';
        $return_module = 'admin';
    }
    unset($_SESSION['gis']['feature_class']);
    _shn_gis_internal_class_form_return($return_action, $return_module);
}


// ==============
// Remove a Feature Class
// ==============

/**
 * Displays Feature Class Available for Deletion.
 * 
 * @global <type> $steps
 */
function _shn_gis_internal_class_remove_seq_1()
{
    global $steps;
    shn_form_progress_bar($steps, 1);
    $button_set = array('cancel' => true, 'next' => true);
    _shn_gis_internal_class_form_search('gis_database_classes_remove', 'seq_2', $button_set);
}

/**
 * Displays options detailing what to do with features belonging to the 
 * Feature Class marked for deletion.
 * 
 * @global <type> $global
 * @global <type> $steps
 */
function _shn_gis_internal_class_remove_seq_2()
{
    global $global;
    global $steps;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
    shn_form_progress_bar($steps, 2);

    if(isset($_REQUEST['next']) && null != $_REQUEST['c_uuid']){
        $_SESSION['gis']['feature_class']['uuid'] = $_REQUEST['c_uuid'];
    }

    if(isset($_SESSION['gis']['feature_class']['uuid'])){
        $c_uuid = $_SESSION['gis']['feature_class']['uuid'];
    }

    $options = $_SESSION['gis']['feature_class']['gis_feature_class_options'];
    $button_set = array('cancel' => true, 'back' => true, 'next' => true);
    _shn_gis_internal_class_form_features_class_options('gis_database_classes_remove', 'seq_3', $button_set, $options);
    
    $keys_ = array(
    'f_class'         => '1',
    'f_coords'        => '1',
    'f_name'          => '1',
    'f_description'   => '1',
    'f_author'        => '1',
    'f_event_date'    => '1',
    );
    $results = shn_gis_get_features_feature_class($c_uuid, $keys_);
    _shn_gis_internal_class_form_features_class_existing($results, $keys_);
}

/**
 * Displays Confirm page.
 * 
 * @global <type> $global
 * @global <type> $steps
 */
function _shn_gis_internal_class_remove_seq_3()
{
    global $global;
    global $steps;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
    
     $options = $_REQUEST['feature_options'];
    if(!isset($options) || trim($options) == ''){
        add_error(_t('Select an Option from "Feature Options"'));
        _shn_gis_internal_class_remove_seq_2();
    } else{  
        
        $c_uuid = $_SESSION['gis']['feature_class']['uuid'];
        $fc = shn_gis_get_feature_class_uuid($c_uuid);
        $name = $fc['c_name'];
        $marker = $fc['c_icon'];
        $desc = $fc['c_description'];
        $layers = shn_gis_get_layers_feature_class($c_uuid);
        
        $_SESSION['gis']['feature_class']['options'] = $options;
        
        shn_form_progress_bar($steps, 3);
        $button_set = array('cancel' => true, 'back' => true, 'finish' => true);
        echo '<h2>' . _t('Feature Class to Delete Details') . '</h2>';
        _shn_gis_internal_class_form_confim('gis_database_classes_remove', 'seq_4', $button_set, $name, $marker, $desc, $layers);
    }
}

/**
 * Deletes Feature Class and applies options to Features belonging to class.
 * 
 * @global <type> $global
 * @global <type> $conf
 * @global <type> $steps
 */
function _shn_gis_internal_class_remove_seq_4()
{        
    global $global;
    global $conf;
    global $steps;
    require_once $global['approot'] . '/inc/lib_gis/gis_fns.inc';
    
    if(isset($_REQUEST['finish'])){
        $options = $_SESSION['gis']['feature_class']['options'];
        $c_uuid = $_SESSION['gis']['feature_class']['uuid'];
        $feature_class = shn_gis_get_feature_class_uuid($c_uuid);

        if($c_uuid != null && $c_uuid != '' && ($options == 'default' || $options == 'delete')){
            
        
            if($_SESSION['gis']['feature_class']['uuid'] != $conf['gis_feature_type_default'] && $feature_class['c_module_ref'] == null && trim($feature_class['c_module_ref']) == ''){
                $keys_ = array(
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
                $features = shn_gis_get_features_feature_class($c_uuid, $keys_);
        
                if('default' == $options){
                    foreach($features as $feature){
                        $keys_ = array('f_class' => $conf['gis_feature_type_default']);
                        if(shn_gis_modify_feature($feature['f_uuid'], $keys_)){
                            add_confirmation(_t('Feature: ') . $feature['f_name'] . _t(' was removed.'));
                        } else{
                            add_error(_t('Feature: ') . $feature['f_name'] . _t(' could not be removed.'));
                        }
                    }
                }
        
        
                if('delete' == $options){
                    foreach($features as $feature){
                        if(shn_gis_remove_feature($feature['f_uuid'])){
                            add_confirmation(_t('Feature: ') . $feature['f_name'] . _t(' was removed.'));
                        } else{
                            add_error(_t('Feature: ') . $feature['f_name'] . _t(' could NOT be removed.'));
                        }
                    }
                }
                if(shn_gis_remove_feature_class($c_uuid, 1)){
                    add_confirmation(_t('Feature Clas was removed.'));
                } else {
                    add_error(_t('Feature Class could not be removed.'));
                }
            } else{
                add_error(_t('Cannot remove the Default Feature Class or a Feature Class that is Associated with another module within Sahana. Please contact your Administrator for more details.'));
            }
        } else {
            add_error(_t('Cannot remove Feature Class. Insufficient details'));
        }
    }
    _shn_gis_internal_class_add_return();
}

/**
 * Displays Feature Class deletion options.
 */
function _shn_gis_internal_class_remove_return()
{
    if(isset($_SESSION['gis']['feature_class']['return_action']) && isset($_SESSION['gis']['feature_class']['return_module'])){
        $return_action = $_SESSION['gis']['feature_class']['return_action'];
        $return_module = $_SESSION['gis']['feature_class']['return_module'];
    } else {
        $return_action = 'gis_database_classes';
        $return_module = 'admin';
    }
    unset($_SESSION['gis']['feature_class']);
    _shn_gis_internal_class_form_return($return_action, $return_module);
}

// ==============================
// Sequences Action Forms
// ==============================

/**
 * Form displaying available feature classes
 * 
 * @global <type> $global
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 */
function _shn_gis_internal_class_form_search($act, $seq, $button_set)
{
    global $global;
    require_once $global['approot'] . '/inc/lib_gis/lib_gis_forms.inc';

    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    echo '<h2>' . _t('Search for Feature Class') . '</h2>';
    shn_form_fsopen(_t('Select Feature Class'));
    shn_gis_form_layer_to_feature_narrow(false);
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Shows form asking for name, marker and description of a feature class
 * 
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 * @param <type> $name
 * @param <type> $marker
 * @param <type> $desc
 */
function _shn_gis_internal_class_form_general_options($act, $seq, $button_set, $name = '', $marker = '', $desc = '')
{
    $class_name_help = _t('Enter a name for Feature Class eg. Small Camp');
    $marker_help = _t('Find required marker below. Right click icon and select "copy image location". Paste into this box');

    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    echo '<h2>' . _t('Feature Class') . '</h2>';
    shn_form_fsopen(_t('General Details'));
    
    shn_form_text(_t('Class Name'),'gis_feature_class_name','size="20"', array('req' => true, 'help' => $class_name_help, 'value' => $name));
    //TODO change for select box menu
    shn_form_text(_t('Marker Link'), 'gis_feature_class_marker', 'size="20"', array('req' => true, 'help' => $marker_help, 'value' => $marker));
    shn_form_textarea(_t('Description'), 'gis_feature_class_description', null, array('value' => $desc));
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Shows form showing all existing layers a Feature Class belongs to as checkboxes.
 * 
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 * @param <type> $layers
 */
function _shn_gis_internal_class_form_layer_options($act, $seq, $button_set, $layers)
{
    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    echo '<h2>' . _t('Extra Options') . '</h2>';
    shn_form_fsopen(_t('Layer Options'));
    shn_form_label(_t('Add Feature Class to Layers:'));
    echo '<br />';
    $count = 0;
    foreach($layers as $layer){
        $count++;
        $checked = '';
        if(isset($layer['checked'])){
            $checked = 'checked = "checked"';
        }
        shn_form_checkbox($layer['l_name'], $count, $checked, array('value' => $layer['l_uuid']));
    }
    shn_form_hidden(array('count' => $count));
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Show form confiming all previously entered feature class details.
 * 
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 * @param <type> $name
 * @param <type> $marker
 * @param <type> $desc
 * @param <type> $layers_
 */
function _shn_gis_internal_class_form_confim($act, $seq, $button_set, $name = '', $marker = '', $desc = '', $layers_ = array())
{
    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    shn_form_fsopen(_t('General Details'));
    shn_form_label(_t('Feature Class Name'), $name);
    if($marker == ''){
        shn_form_label(_t('Feature Class Marker'), '(' . $marker . ')');
    } else {
        shn_form_label(_t('Feature Class Marker'), '<img src="'. $marker . '" style="width:25px; height:25px;" /> (' . $marker . ')');    
    }
    echo '<br />';
    shn_form_label(_t('Feature Class Description'), $desc);
    shn_form_fsclose();
    shn_form_fsopen(_t('Layer Details'));
    shn_form_label(_t('Belongs to Layers:'));
    foreach($layers_ as $layer){
        shn_form_label('', $layer['l_name']);
    }
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Shows options for features belonging to a feature class.
 * 
 * @param <type> $act
 * @param <type> $seq
 * @param <type> $button_set
 */
function _shn_gis_internal_class_form_features_class_options($act, $seq, $button_set, $options)
{
    shn_form_fopen($act, null, array());
    shn_form_hidden(array('seq' => $seq));
    echo '<h2>' . _t('Existing Feature Class') . '</h2>';
    shn_form_fsopen(_t('Feature Options'));
    shn_form_radio(array('default' => 'Set to Default Class','delete'=>'Delete'), 'Options for Features belonging to this Feature Class', 'feature_options', null, array('value' => $options));
    shn_form_fsclose();
    shn_form_submit_set($button_set);
    shn_form_fclose();
}

/**
 * Displays Features belonging to a Feature Class.
 * 
 * @global <type> $global
 * @param <type> $results_
 * @param <type> $keys_display_
 */
function _shn_gis_internal_class_form_features_class_existing($results_, $keys_display_)
{
    global $global;
    require_once $global['approot'] . '/inc/lib_gis/lib_gis_forms.inc';
    shn_form_fopen('seq_3', null, array());
    echo '<h2>' . _t('Feature in this Class') . '</h2>';
    shn_gis_form_feature_display($results_, $keys_display_);
    shn_form_fclose();
}

/**
 * Displays return options.
 * 
 * @param <type> $return_action_
 * @param <type> $return_module_
 */
function _shn_gis_internal_class_form_return($return_action_, $return_module_)
{
    shn_form_fopen($return_action_, $return_module_, array());
    shn_form_fsopen(_t('Return to Original Menu'));
    shn_form_submit(_t('Return'), 'name="return"');
    shn_form_fsclose();
    shn_form_fclose();
}

/**
 * Displays Feature Class options.
 */
function _shn_gis_internal_class_form_select_options()
{
    shn_form_fopen('gis_database_classes', null, array());
    shn_form_fsopen(_t('Feature Class'));
    echo '<p>' . _t('Selection an operation to perform on a Feature Class.') . '</p><br />';
    shn_form_fsopen(_t('Add Feature Class'));
    echo '<p>' . _t('Add a new Feature Class to the system.') . '</p><br />';
    shn_form_submit(_t('Add'), 'name="add"');
    shn_form_fsclose();
    shn_form_fsopen(_t('Edit Feature Class'));
    echo '<p>' . _t('Edit an existing Feature Class within the system.') . '</p><br />';
    shn_form_submit(_t('Edit'), 'name="edit"');
    shn_form_fsclose();
    shn_form_fsopen(_t('Remove Feature Class'));
    echo '<p>' . _t('Remove a Feature Class from the system.') . '</p><br />';
    shn_form_submit(_t('Remove'), 'name="remove"');
    shn_form_fsclose();
    shn_form_fsclose();
    shn_form_fclose();
}

