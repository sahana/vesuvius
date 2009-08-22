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
    
    function shn_gis_internal_layer_general_select()
    {
        
    }
    
    function shn_gis_internal_layer_add_seq()
    {
        global $steps;
        $steps = array('General Details', 'Confim');

        // If a user wishs to return to a page other than admin home on cancel or finish
        if(return_module_ != NULL && $return_action_ != NULL){
            $_SESSION['gis']['feature_layer']['return_action'] = $return_action_;
            $_SESSION['gis']['feature_layer']['return_module'] = $return_module_;
        }

        // If user cancels sequence
        if(isset($_REQUEST['cancel'])){
            add_warning(_t("Operation Canceled"));
            _shn_gis_internal_layer_add_return();
        }

        // if user is in sequence
        elseif(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                // add layers
                case 'seq_2':
                if(isset($_REQUEST['back'])){
                    _shn_gis_internal_layer_add_seq_1();
                } else {
                    _shn_gis_internal_layer_add_seq_2();
                }
                break;
                // confirm page
                case 'seq_3':
                if(isset($_REQUEST['back'])){
                    _shn_gis_internal_layer_add_seq_1();
                } else {
                    _shn_gis_internal_layer_add_seq_3();
                }
                break;
                // error
                default:
                add_error(_("Something went wrong"));
                _shn_gis_internal_layer_add_return();
                break;
            }
        }

        // if user is starting sequence
        else {
            // enter detail page
            unset($_SESSION['gis']['feature_layer']);
            _shn_gis_internal_layer_add_seq_1();
        }
    }
    
    function shn_gis_internal_layer_edit_seq()
    {
        global $steps;
        $steps = array('General Details', 'Confim');

        // If a user wishs to return to a page other than admin home on cancel or finish
        if(return_module_ != NULL && $return_action_ != NULL){
            $_SESSION['gis']['feature_layer']['return_action'] = $return_action_;
            $_SESSION['gis']['feature_layer']['return_module'] = $return_module_;
        }

        // If user cancels sequence
        if(isset($_REQUEST['cancel'])){
            edit_warning(_t("Operation Canceled"));
            _shn_gis_internal_layer_edit_return();
        }

        // if user is in sequence
        elseif(isset($_REQUEST['seq'])){
            switch($_REQUEST['seq']){
                // edit layers
                case 'seq_2':
                if(isset($_REQUEST['back'])){
                    _shn_gis_internal_layer_edit_seq_1();
                } else {
                    _shn_gis_internal_layer_edit_seq_2();
                }
                break;
                // confirm page
                case 'seq_3':
                if(isset($_REQUEST['back'])){
                    _shn_gis_internal_layer_edit_seq_1();
                } else {
                    _shn_gis_internal_layer_edit_seq_3();
                }
                break;
                // error
                default:
                add_error(_("Something went wrong"));
                _shn_gis_internal_layer_edit_return();
                break;
            }
        }

        // if user is starting sequence
        else {
            // enter detail page
            unset($_SESSION['gis']['feature_layer']);
            _shn_gis_internal_layer_edit_seq_1();
        }
    }
    
    
    /**
     * 
     * @global <type> $global
     * @global <type> $steps
     */
    function _shn_gis_internal_layer_add_seq_1()
    {
        global $steps;

        $name = '';
        $desc = '';
        if($_REQUEST['back']){
            $name = $_SESSION['gis']['feature_layer']['name'];
            $desc = $_SESSION['gis']['feature_layer']['description'];
        }
        
        shn_form_progress_bar($steps, 1);
        $button_set = array('cancel' => true, 'next' => true);
        _shn_gis_internal_layer_form_general_options('gis_database_layer_add', 'seq_2', $button_set, $name, $desc);
    }
    
    /**
     * 
     * @return <type>
     */
    function _shn_gis_internal_layer_add_seq_2()
    {
        global $steps;
       
        if(isset($_REQUEST['next'])){
            $error = false;

            // check class name
            if(isset($_REQUEST['gis_feature_layer_name']) && trim($_REQUEST['gis_feature_layer_name']) != ''){
                $_SESSION['gis']['feature_layer']['name'] = trim($_REQUEST['gis_feature_layer_name']);
            } else {
                add_error(_("Enter Feature Class Name"));
                $error = true;
            }

            $_SESSION['gis']['feature_layer']['description'] = $_REQUEST['gis_feature_layer_description'];

            // If error return to general details form.
            if($error){
                _shn_gis_internal_layer_add_seq_1();
                return;
            }
        }
        
        shn_form_progress_bar($steps, 2);
        $button_set = array('cancel' => true, 'back' => true, 'finish' => true);
        _shn_gis_internal_layer_form_confim('gis_database_layer_add', 'seq_3', $button_set, $_SESSION['gis']['feature_layer']['name'], $_SESSION['gis']['feature_layer']['description']);

        
    }
    
    /**
     * 
     */
    function _shn_gis_internal_layer_add_seq_3()
    {
        global $global;
        if(isset($_REQUEST['finish'])){
            require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
            if(shn_gis_create_layer($_SESSION['gis']['feature_layer']['name'], $_SESSION['gis']['feature_layer']['description']) === false){
                add_error(_("Layer could not be created."));
            } else {
                add_confirmation(_t('Layer was created'));
            }
        }
        _shn_gis_internal_layer_add_return();
    }
    
    /**
     * 
     */
    function _shn_gis_internal_layer_add_return()
    {
        if(isset($_SESSION['gis']['feature_layer']['return_action']) && isset($_SESSION['gis']['feature_layer']['return_module'])){
            $return_action = $_SESSION['gis']['feature_layer']['return_action'];
            $return_module = $_SESSION['gis']['feature_layer']['return_module'];
        } else {
            $return_action = 'gis_database_layers';
            $return_module = 'admin';
        }
        unset($_SESSION['gis']['feature_layer']);
        _shn_gis_internal_layer_form_return($return_action, $return_module);
    }
    
    /**
     * 
     * @global <type> $steps
     */
    function _shn_gis_internal_layer_edit_seq_2()
    {
        global $steps;

        $name = '';
        $desc = '';
        if($_REQUEST['back']){
            $name = $_SESSION['gis']['feature_layer']['name'];
            $desc = $_SESSION['gis']['feature_layer']['description'];
        }
        
        shn_form_progress_bar($steps, 1);
        $button_set = array('cancel' => true, 'next' => true);
        _shn_gis_internal_layer_form_general_options('gis_database_layer_add', 'seq_2', $button_set, $name, $desc);
    }
    
    
    
    
    
    
    
    
    
    function _shn_gis_internal_layer_form_general_options($act, $seq, $button_set, $name = '', $desc = '')
    {
        $class_name_help = _t('Enter a name for a Layer eg. Houses');
        shn_form_fopen($act, null, array());
        shn_form_hidden(array('seq' => $seq));
        echo '<h2>' . _("Feature Class") . '</h2>';
        shn_form_fsopen(_("General Details"));

        shn_form_text(_('Layer Name'), 'gis_feature_layer_name','size="20"', array('req' => true, 'help' => $class_name_help, 'value' => $name));
        shn_form_textarea(_('Description'), 'gis_feature_layer_description', null, array('value' => $desc));
        shn_form_fsclose();
        shn_form_submit_set($button_set);
        shn_form_fclose();
    }
    
    function _shn_gis_internal_layer_form_confim($act, $seq, $button_set, $name = '', $desc = '')
    {
        shn_form_fopen($act, null, array());
        shn_form_hidden(array('seq' => $seq));
        shn_form_fsopen(_t("General Details"));
        shn_form_label(_t('Feature Class Name'), $name);
        shn_form_label(_t('Feature Class Description'), $desc);
        shn_form_fsclose();
        shn_form_submit_set($button_set);
        shn_form_fclose();
    }
    
    function _shn_gis_internal_layer_form_return($return_action_, $return_module_)
    {
        shn_form_fopen($return_action_, $return_module_, array());
        shn_form_fsopen(_("Return to Original Menu"));
        shn_form_submit(_t('Return'), 'name="return"');
        shn_form_fsclose();
        shn_form_fclose();
    }
