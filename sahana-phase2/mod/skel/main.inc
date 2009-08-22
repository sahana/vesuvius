<?php
/**
 * This is the main file for the Sahana module. Once the module is selected in the 
 * post all actions are passed to this file for processing.
 * <Description of file> 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Chamindra de Silva (http://www.linux.lk/~chamindra) 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage skel
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Place all your dependant libraries below. Given are some typical ones
 * required for the module
 */
include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';


include_once($global['approot'].'inc/lib_log.inc');


/**
 * This function allows you to override the mainmenu. This is often done 
 * to include the modules own menu
 * 
 * @access public
 * @return void
 */
function shn_skel_mainmenu() 
{
    global $global;
    $module = $global['module'];
    
    // Create the module menu
    shn_mod_menuopen(_t('Skeleton Module'));

    shn_mod_menuitem('default',_t('Home'));
    shn_sub_mod_menuopen(_t('Sub Menu'));
    shn_sub_mod_menuitem('mio',_t('Menu Item 1'));
    shn_sub_mod_menuitem('mit',_t('Menu Item 2'));
    shn_sub_mod_menuclose();

    shn_sub_mod_menuopen(_t('Sub Menu 2'));
    shn_mod_menuitem('form',_t('Form'));
    shn_mod_menuitem('report',_t('Report'));
    shn_sub_mod_menuclose();
    shn_mod_menuitem('ajax_demo',_t('xAjax Demo'));
    shn_mod_menuclose();
   
    // include the main menu so that the user can navigate outside the module
    include $global['approot'].'/inc/handler_mainmenu.inc';

} 

/** 
 * Other sections you can override
 */
// function shn_skel_header() {}
// function shn_skel_footer() {}
// function shn_skel_html_head() {}

/**
 * This function displays the default page of the module when it is selected
 * This function has to exist! 
 *
 * @access public
 * @return void
 */
function shn_skel_default()
{

    global $global;

?>
<div id="home">
<h2><?php echo  _t('Skeleton Module'); ?></h2>
<p><?php echo  _t('This is a description of the module that we typically
give on the first page with it\' features listed below')?>
<?php echo  _t('Features include:');?></p>
<ul>
    <li><?php echo _t('Give a description of the features')?></li>
    <li><?php echo _t('Feature 2')?></li>
</ul>
</div>

<?php
}

/**
 * This is the call from menu item one, action mio
 *
 * @access public
 * @return void
 */
function shn_skel_mio()
{
    echo '<p>'._t('You called menu item one action').'</p>';
    add_confirmation('This is a sample confirmation message after a form submit');
}

/**
 * This is the call from menu item two, action mit
 *
 * @access public
 * @return void
 */
function shn_skel_mit()
{
    echo '<p>'._t('You called menu item two action').'</p>';
    add_warning('This is a sample warning message after a form submit');
    add_confirmation('This is a sample confirmation message after a form submit');
}


/**
 * This is the call for the action rpt
 *
 * @access public
 * @return void
 */
function shn_skel_report()
{
    echo '<p>'._t('You called the report action').'</p>';

    global $global;

    //shn_log_event('rr','report','skeleton update');

    //shn_log_display('rr');
     
}

/**
 * test XML stream 
 *
 * @access public
 * @return void
 */
function shn_xml_skel_report()
{
    echo '<p>'._t('You called the report action in XML').'</p>';

    global $global;
}

/**
 * test XSTR any stream functionalty
 * the XSTR functions are the default catch for any stream that is not
 * explicitly defined
 *
 * @access public
 * @return void
 */
function shn_XST_skel_report()
{
    echo '<p>'._t('The XST catch all report function caught this stream').'</p>';

    global $global;
}



/**
 * This is function generate a form
 *
 * @access public
 * @return void
 */
function shn_skel_form()
{
    echo '<h2>'._t('Example Form').'</h2>';
    if(isset($_POST))
        print_r($_POST);
    shn_form_fopen("form", null,array('req_message'=>true));
    shn_form_fsopen("Fieldset One");
    shn_form_text("Text Field 0","tf",null,array("req"=>true, "help"=>"testing help"));
    shn_form_text("Text Field 1","tf2","size='40'");
    shn_form_submit("Clear", $submit_opts = null);
    shn_form_fsclose();
    shn_form_fsopen("Fieldset Two");
    shn_form_button("Button", $button_opts = null, $extra_opts = null);
    shn_form_hidden(array("h1"=>"hidden value"));
    shn_form_checkbox("Check Box", "check", $text_opts = null, $extra_opts = null);
    shn_form_select(array("o1"=>"option1","o2"=>"option2","o3"=>"option3"),"Select", "sel",$select_opts = "", $extra_opts = null);
    shn_form_radio(array("o1"=>"Option1","o2"=>"Option2","o3"=>"Option3"),"Radio",'op[]',$select_opts = "", $extra_opts = null);
    shn_form_opt_select('opt_camp_service', "Opt Select", $select_opts = "", $extra_opts = null);
    shn_form_opt_multi_select('opt_camp_service',"Opt multi Select", $select_opts = "", $extra_opts = null);
    shn_form_multi_select("ms",array("o1"=>"option1","o2"=>"option2","o3"=>"option3"),"Multi Select", $select_opts = "", $extra_opts = null);
    shn_form_opt_checkbox('opt_camp_service',$extra_opts=null);
    shn_form_textarea("Text area", "add", $text_opt, $extra_opts = null);
    shn_form_upload("Upload File", 'file', $extra_opts = null);
    shn_form_label("Label", "cap", $extra_opts = null);
    shn_form_password("Password", "pass", null, $extra_opts = null);
    shn_form_date("Input Date","dob",$extra_opts = null);
    shn_form_fsclose();
    shn_form_fsopen(_t('WYSIWYG Editor Demo'));
    shn_form_wysiwyg('Description','description');
    shn_form_fsclose();
    shn_form_submit("Add", $submit_opts = null);
    shn_form_submit("Delete", $submit_opts = null);
    shn_form_fclose();
}

/**
 * This function will demo xajax support in framework
 *
 */

function shn_skel_ajax_demo(){
    global $global;
    include_once $global['approot'].'/inc/lib_xajax.inc';
    shn_xajax_registerFunction('skel_hello_world');
    shn_xajax_registerFunction('skel_calculate');
?>
    <h2><?php echo _t('xAjax Demo'); ?></h2>
    <h3>Demo 1 :: Changing content of an element</h3><br />
    <a href="#" onclick="skel_hello_world()" id='click_me' >Click here</a>
    <br />
    <br />
    <h3>Demo 2 :: Ajax calculater</h3><br />
    <script language="javascript">
        function cal(){
            var val1=document.getElementById('val1').value;
            var val2=document.getElementById('val2').value;
            skel_calculate( val1 , val2 );
            return false;
        }
    </script>
    <form method="post" onsubmit="return false;">
        <input type="text" size="5" id='val1' onchange="cal();"/> 
        <span> + </span>
        <input type="text" size="5" id='val2' onchange="cal();"/>
        <span> = </span>
        <span id='result'>0</span>
        <br />
        <input type="submit" value="Calculate" onclick="cal();" />
    </form>
    <br />
    <br />
    <h3>Demo 3 :: server side validation</h3><br />
<?php

    // this is xajax function we are goign to use to validate the user_id
    shn_xajax_registerFunction('skel_check_user');
    shn_xajax_registerFunction('skel_add_user');

    shn_form_fopen('ajax_demo');
    shn_form_fsopen('User Info');
    shn_form_text('User Id','user_id',' onchange="skel_check_user(this.value)";',array('br'=>false));
    echo "<span id='check' ></span><br /><br />";
    shn_form_text('Email','email');
    shn_form_fsclose();
    shn_form_submit('Add Me', 'onclick="skel_add_user(xajax.getFormValues(\'form0\'));return false"');
    shn_form_fclose();
    echo "Existing Users : ";
    $users=print_r($_SESSION['demo_users'], true);
    echo "<span id='users'>".$users."</span><br />";
}

