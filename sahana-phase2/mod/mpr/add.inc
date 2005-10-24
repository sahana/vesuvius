<?php
/* $Id: add.inc,v 1.2 2005-10-24 09:59:44 janakawicks Exp $ */

/**Main home page of the MPR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author	  Janaka Wickramasinghe <janaka@opensource.lk> 
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/* {{{ include files */
//@todo: put thsi some where else later
include_once($global['approot'].'/mod/mpr/errors.inc');
include_once($global['approot'].'/inc/lib_errors.inc');
include_once($global['approot'].'/inc/lib_validate.inc');

//yaml
include_once($global['approot'].'/3rd/spyc/spyc.php');

/* }}} */


/* {{{ Action Layer ;-) */

/* {{{ _shn_mpr_add_default($error=false) : Add From */
function _shn_mpr_add_default($error=false)
{
    global $global;
?>
    <h1 align="center">Report Missing Person</h1>
<?php
    if($error)
        display_errors();

    $frm_open = array('method'=>"POST",'action'=>'');
    shn_from_open($frm_open);

    $sections = Spyc::YAMLLoad($global['approot'].'/mod/mpr/map.yml');
    #$array = Spyc::YAMLLoad($global['approot'].'/mod/mpr/test.yml');
    foreach($sections as $k => $v){
        $array = Spyc::YAMLLoad($global['approot'].'/mod/mpr/'.$v);
        if($error)
            shn_form_add_component_list($array,true,$k,false,true);
        else
            shn_form_add_component_list($array,true,$k);
    }        
    shn_form_close();
}
/* }}} */

/* {{{ _shn_mpr_add_commit($error=false) : Add form commit */
function _shn_mpr_add_commit($error=false)
{
    $error=false;
    //validate
    //date of birth
    $dob=$_POST['dob'];
    $dob=trim($dob);
    if($dob != '' && ! shn_check_date($dob)){
        $error=true;
        add_error(SHN_ERR_MPR_DATEOFBIRTH);
    }
    //if erros send back to the main from with errors
    if($error){
        _shn_mpr_add_default(true);
        return false;
    }
#    var_dump($_POST);
    add_error(SHN_ERR_MPR_DATEOFBIRTH);
    _shn_mpr_add_default(true);
}
/* }}} */

/* }}} */

// vim: set tabstop=4 shiftwidth=4 fdm=marker:
?>
