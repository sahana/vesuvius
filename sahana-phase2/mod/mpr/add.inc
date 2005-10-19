<?php
/* $Id: add.inc,v 1.1 2005-10-19 12:32:06 janakawicks Exp $ */

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

//@todo: put thsi some where else later
include_once($global['approot'].'/mod/mpr/errors.inc');
include_once($global['approot'].'/inc/lib_errors.inc');
include_once($global['approot'].'/inc/lib_validate.inc');

function _shn_mpr_add_default($error=false)
{
    global $global;
?>
    <h1 align="center">Report Missing Person</h1>
<?php
    if($error)
        display_errors();

    $header = array (array('method'=>"POST",'action'=>'')); // end of header
    shn_show_form($header);
?>
    <div id="add_opt">
<?php
    _shn_mpr_form();
    $tail = array (
        array('type'=>"submit",'value'=>"submit")
    ); // end of tail
    //@todo remove later
?>
    <input type="hidden" name="add_sequence" value="commit" />
<?php
    shn_show_form($tail);
?>
    </div>
<?php
   
}
function _shn_mpr_form($section_seperator="<hr><h2>%s</h2>",$return=false)
{

	//Personal Details
	echo sprintf($section_seperator,_("Personal Details"));

	$body = array (
				array ('type' => 'text', 'desc' => _('First name'), 'name' => 'fname' ,'value'=> $_POST['fname'], 'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Last name'), 'name' => 'lname' ,'value'=> $_POST['lname'], 'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Other names'), 'name' => 'oname' ,'value'=> $_POST['oname'], 'br' => 1 ),
				array ('type' => 'dropdown', 'desc' => _('Gender'), 'name' => 'gender' ,'br' => 1 , 'options' => array ( 
					array('drop_desc' => _('Unknown'), 'value' => 'U'),
					array('drop_desc' => _('Male'), 'value' => 'M'),
					array('drop_desc' => _('Female'), 'value' => 'f')
					)
),
				array ('type' => 'text', 'desc' => _('Date Of Birth(YYYY-MM-DD)'), 'name' => 'dob' ,'value'=> $_POST['dob'], 'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Age'), 'name' => 'age' ,'br' => 1 ),
				array ('type' => 'dropdown', 'desc' => _('Marital Status'), 'name' => 'marital_status' ,'br' => 1 , 'options' => array ( 
					array('drop_desc' => _('Unknown'), 'value' => 'U'),
					array('drop_desc' => _('Single'), 'value' => 'S'),
					array('drop_desc' => _('Married'), 'value' => 'M'),
					array('drop_desc' => _('Divorced'), 'value' => 'D'),
					array('drop_desc' => _('Widowed'), 'value' => 'W')
					)
),
				array ('type' => 'text', 'desc' => _('Religion'), 'name' => 'religion' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Race'), 'name' => 'race' ,'br' => 1 ),
				);
shn_show_form($body);

	//Contact detail
	echo sprintf($section_seperator,_("Contact detail"));

	$body = array (
				array ('type' => 'text', 'desc' => _('Address'), 'name' => 'address' ,'br' => 1 ),
				array ('type' => 'location', 'desc' => _('Location'), 'name' => 'location' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Phone Number'), 'name' => 'phone' ,'br' => 1 ),
				);
shn_show_form($body);

	//Indentification
	echo sprintf($section_seperator,_("Indentification"));

	$body = array (
				array ('type' => 'text', 'desc' => _('Old Id'), 'name' => 'id1' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('New Id'), 'name' => 'id2' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Family Id'), 'name' => 'id3' ,'br' => 1 ),
				);
shn_show_form($body);

	//Physical Appearance
	echo sprintf($section_seperator,_("Physical Appearance"));

	$body = array (
				array ('type' => 'dropdown', 'desc' => _('Skin Color'), 'name' => 'skin_color' ,'br' => 1 , 'options' => array ( 
					array('drop_desc' => _('Unknown'), 'value' => 'unknown'),
					array('drop_desc' => _('Dark or Black'), 'value' => 'dark'),
					array('drop_desc' => _('Brown'), 'value' => 'brown'),
					array('drop_desc' => _('Fair'), 'value' => 'fair'),
					array('drop_desc' => _('White'), 'value' => 'white')
					)
),
				array ('type' => 'dropdown', 'desc' => _('Hair Color'), 'name' => 'hair_color' ,'br' => 1 , 'options' => array ( 
					array('drop_desc' => _('Unknown'), 'value' => 'unknown'),
					array('drop_desc' => _('Black'), 'value' => 'black'),
					array('drop_desc' => _('Dark Brown'), 'value' => 'dark_brown'),
					array('drop_desc' => _('Grey'), 'value' => 'grey'),
					array('drop_desc' => _('Black going grey'), 'value' => 'grey_black'),
					array('drop_desc' => _('Tinted'), 'value' => 'tinted'),
					array('drop_desc' => _('Blonde'), 'value' => 'blonde'),
					array('drop_desc' => _('Brunette'), 'value' => 'brunette'),
					array('drop_desc' => _('Red'), 'value' => 'red'),
					array('drop_desc' => _('Bald'), 'value' => 'bald'),
					array('drop_desc' => _('Other'), 'value' => 'other')
					)
),
				array ('type' => 'dropdown', 'desc' => _('Eye Color'), 'name' => 'eye_color' ,'br' => 1 , 'options' => array ( 
					array('drop_desc' => _('Unknown'), 'value' => 'unknown'),
					array('drop_desc' => _('Black'), 'value' => 'black'),
					array('drop_desc' => _('Dark brown'), 'value' => 'dark_brown'),
					array('drop_desc' => _('Light brown'), 'value' => 'light_brown'),
					array('drop_desc' => _('Blue'), 'value' => 'blue'),
					array('drop_desc' => _('Grey'), 'value' => 'grey'),
					array('drop_desc' => _('Green'), 'value' => 'green'),
					array('drop_desc' => _('other'), 'value' => 'other')
					)
),
				array ('type' => 'text', 'desc' => _('Height'), 'name' => 'height' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Weight'), 'name' => 'weight' ,'br' => 1 ),
				array ('type' => 'txtarea', 'desc' => _('Distinctive features'), 'name' => 'comments' ,'br' => 1 ),
				array ('type' => 'txtarea', 'desc' => _('Last clothing'), 'name' => 'last_seen' ,'br' => 1 ),
				array ('type' => 'txtarea', 'desc' => _('Last clothing'), 'name' => 'last_clothing' ,'br' => 1 )
				);
shn_show_form($body);
	//Reported By
	echo sprintf($section_seperator,_("Reported By"));

	$body = array (
				array ('type' => 'text', 'desc' => _('First Name'), 'name' => 'report_fname' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Last Name'), 'name' => 'report_lname' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Address'), 'name' => 'report_address' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Phone'), 'name' => 'report_phone' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Relationship'), 'name' => 'report_relation' ,'br' => 1 ),
				array ('type' => 'text', 'desc' => _('Organization'), 'name' => 'report_organization' ,'br' => 1 ),
				array ('type' => '', 'desc' => _(''), 'name' => '' ,'br' => 1 )
				);
shn_show_form($body);

}

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

    echo "COMMIT";
}
?>
