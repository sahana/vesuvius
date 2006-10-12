<?php
/**Admin controller of the Catalogue system 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sanjeewa Jayasinghe <sditfac@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage cs
*/

include_once($global['approot'].'/inc/lib_form.inc');


function shn_cs_adm_default()
{
    global $global;
    $db=$global['db'];

    $query="select option_code from field_options where field_name='opt_cs_depth'";
    $res=$db->Execute($query);
    $current_depth=$res->fields["option_code"];
    
    $options=array('1'=>'1','2'=>'2','3'=>'3','4'=>'4','5'=>'5','6'=>'6','7'=>'7','8'=>'8','9'=>'9','10'=>'10','11'=>'11','12'=>'12','13'=>'13','14'=>'14','15'=>'15');
    shn_form_fopen("adm_max_depth_form_submit");
    shn_form_fsopen(_("Current Value of Maximum Depth"));

    $extra_opts['value'] = $current_depth;
    shn_form_text('','base_unit','size="5" readonly=true',$extra_opts);
    shn_form_fsclose();

    shn_form_fsopen(_("Select the New value of Maximum Depth"));
    shn_form_select($options,'','max_depth',$select_opts,array('req'=>true));
    shn_form_fsclose();
    shn_form_submit(_("Save"));
    shn_form_fclose();

}


function shn_cs_adm_max_depth_form_submit()
{
    global $global;
    $db=$global['db'];
    $depth = trim($_POST['max_depth']);

    $query="update field_options set option_code='$depth' where field_name='opt_cs_depth' ";
    $res=$db->Execute($query); 
    
    ?>
	<div id="result_msg">
	<?php echo "Maximum Depth ".$depth."  was successfully saved";?>
	</div>
    <?php
    shn_cs_adm_max_depth_form();
}

?>
