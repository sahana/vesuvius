<?php
/* $Id: lib_form.inc,v 1.50 2006-08-03 07:30:19 priyanga Exp $ */
/**
 *
 * Sahana HTML form library
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage presentation
 * @author     Chamindra de Silva (chamindra@opensource.lk>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

$shn_help_id;

/**
 * You can add extra attributes to the given HTML element
 *
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_extra_opts($extra_opts)
{
    global $shn_help_id;
    // output a required flag
    if (true == $extra_opts['req']) echo "\n <b class='req'>*req</b>\n";

    //Help
    if(isset($extra_opts['help'])){
        $shn_help_id++;
        $_SESSION['form_help'][$shn_help_id] = $extra_opts['help'] ."<br /><br />[<a class=closeLink href='#' onclick='hideCurrentPopup(); return false;'>close this tip</a>]";
        #echo "<a href=\"stream.php?stream_type=help&help_id=$shn_help_id\">[Help]</a>\n";
        echo '<a href="" class=popupLink onclick="return !showPopup(\'help_popup\', event,'.$shn_help_id.');">[Help]</a>';
    }

    // output a break - default is true
    if ((!isset($extra_opts['br'])) ||( $extra_opts['br'] == true)) echo "\n    <br />\n";
}

/**
 * This function will open the HTML Form
 *
 * @param mixed $act
 * @param mixed $mod
 * @param string $form_opts
 * @access public
 * @return void
 */
function shn_form_fopen($act, $mod = null, $form_opts = array('req_message'=>true))
{
?>
<div onclick='event.cancelBubble = true;' class="popup" id="help_popup" ></div>
<?php
    global $global;
    if ( null == $mod ) $mod = $global['module'];

    if (!isset($form_opts['style']))
        $form_opts['style'] = "formset";
    
    if (isset($form_opts['anchor']))
        $anchor = '#' . $form_opts['anchor'];
    else
        $anchor = '';
    
    if($form_opts['req_message']){
?>
    <p><b>Key:</b><b class='red'> *req </b> - Fields tagged with this have to be filled to submit the form successfully</p>
<?php
    }
?>
    <div id="formcontainer">
    <form method="POST" action="index.php?mod=<?=$mod?>&act=<?=$act?><?=$anchor?>" id="<?=$form_opts['style']?>" <?=$form_opts['enctype']?>name="<?=$form_opts['name']?>">
<?php
}

/**
 * This function will close the HTML form
 *
 * @access public
 * @return void
 */
function shn_form_fclose()
{ ?>
    </form>
    </div> <!-- /formcontainer -->
<?php
}

/**
 * This will produce a submit button
 *
 * @param mixed $name
 * @access public
 * @return void
 */
function shn_form_submit($name, $submit_opts = null)
{ ?>
    <input type="submit" value="<?=$name?>" <?=$submit_opts?> />
<?php
}


/**
 * Open and close a fieldset, which is a group of field
 *
 * @param mixed $label
 * @access public
 * @return void
 */
function shn_form_fsopen($label = null)
{ ?>
    <fieldset>
    <legend><?=$label?></legend>
<?php
}

/**
 * HTML Form close
 *
 * @access public
 * @return void
 */
function shn_form_fsclose()
{ ?>
    </fieldset>
<?php
}


/**
 * HTML button element
 *
 * @param mixed $name
 * @param mixed $button_opts
 * @access public
 * @return void
 */
function shn_form_button($name, $button_opts = null, $extra_opts = null)

{
?>
    <input type="button" value="<?=$name?>" <?=$button_opts?> />
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * HTML text element
 *
 * @param mixed $label
 * @param mixed $name
 * @param mixed $text_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_text($label, $name, $text_opts = null, $extra_opts = null )
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
    if(get_magic_quotes_gpc())
        $value = stripslashes($value);
?>
    <label><?=$label?></label>
    <input type="text" name="<?=$name?>" value="<?=$value?>" <?=$text_opts?> />
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * HTML hidden element
 *
 * @param mixed $hidden_vars
 * @access public
 * @return void
 */
function shn_form_hidden($hidden_vars)
{
    foreach ($hidden_vars as $name => $value) {
?>
    <input type="hidden" name="<?=$name?>" value="<?=$value?>">
<?php
    }
}

/**
 * HTML checkbox element
 *
 * @param mixed $label
 * @param mixed $name
 * @param mixed $text_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_checkbox($label, $name, $text_opts = null, $extra_opts = null)
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
    $disabled = $extra_opts['disabled']==NULL? false :$extra_opts['disabled'];
 ?>
    <label><?=$label?></label>
    <input type="checkbox" name="<?=$name?>" value="<?=$value?>" <?if ($disabled){ echo "disabled='true'";}?><?=$text_opts?>  />
<?php
    shn_form_extra_opts($extra_opts);
}


/**
 * HTML dropdown list element
 *
 * @param mixed $options
 * @param mixed $label
 * @param mixed $name
 * @param string $select_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_select($options,$label, $name,$select_opts = "", $extra_opts = null)
{
    global $global;

    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
?>
    <label><?=$label?></label>
    <select name="<?=$name?>" <?=$select_opts?> >
<?php
    foreach ($options as $opt_value => $desc )
    {
        $sel = ( $opt_value == $value ) ? "selected" : null ;
?>
        <option value="<?=$opt_value?>" <?=$sel?>><?=$desc?></option>
<?php
    }
?>
    </select>
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * HTML radio button element
 *
 * @param mixed $options
 * @param mixed $label
 * @param mixed $name
 * @param string $select_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_radio($options,$label, $name,$select_opts = "", $extra_opts = null)
{
    global $global;
    $value = ($_POST[$opt_field])? $_POST[$opt_field] : $extra_opts['value'];
?>
    <label><?=$label?></label>
<?php
    foreach ($options as $opt_value => $desc ) 
    {
        if($value == $opt_value)
        {
?>
        <input type="radio" name="<?=$name?>" value="<?=$opt_value?>" checked="true" />
        <?=$desc?>
<?php
        }
        else
        {
?>
        <input type="radio" name="<?=$name?>" value="<?=$opt_value?>"/>
        <?=$desc?>
<?php
        }        
    }
?>
<?php
    shn_form_extra_opts($extra_opts);
}


/**
 * create a select field based on field options
 *
 * @param mixed $opt_field
 * @param mixed $label
 * @param string $select_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_opt_select($opt_field, $label, $select_opts = "", $extra_opts = null)
{
    global $global;
    $sort=$extra_opts['sort'];
    $name=($extra_opts['name'])?$extra_opts['name']:$opt_field;
    $value = ($_POST[$opt_field])? $_POST[$opt_field] : $extra_opts['value'];
?>
    <label><?=$label?></label>
    <select name="<?=$name?>" <?=$select_opts?>
<?php
if($sort==null){
	$q="select * from field_options where field_name='{$opt_field}'";
}else{		    
	$q="select * from field_options where field_name='{$opt_field}' order by $sort ";
}
		    $res = $global['db']->Execute($q);
        
    while(!res==NULL && !$res->EOF) {

        $sel = ( $res->fields[1] == $value ) ? "selected" : null ;
?>
 <option value="<?=$res->fields[1]?>" <?=$sel?>><?=$res->fields[2]?></option>
<?php

        $res->MoveNext();
      }
      if (isset($extra_opts['all']) || $extra_opts['all'] == true) echo "<option value='all'>All</option>";
 ?>
    </select>
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * create a select field based on field option
 *
 * @param mixed $opt_field
 * @param mixed $label
 * @param string $select_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_opt_multi_select($opt_field, $label, $select_opts = "", $extra_opts = null)
{
    global $global;

    $value = ($_POST[$opt_field])? $_POST[$opt_field] : $extra_opts['value'];
	
?>
    <label><?=$label?></label>
    <select name="<?=$opt_field?>[]" <?=$select_opts?>
<?php
		    $res = $global['db']->Execute
        ("select * from field_options where field_name='$opt_field'");
    while(!res==NULL && !$res->EOF) {
        if($value!=NULL){
            $sel = ( (array_search($res->fields[1],$value)==true) || (array_search($res->fields[1],$value)===0) ) ? "selected" : null ;
        }
?>
 <option value="<?=$res->fields[1]?>" <?=$sel?>><?=$res->fields[2]?></option>
<?php

        $res->MoveNext();
      }
      if (isset($extra_opts['all']) || $extra_opts['all'] == true) echo "<option value='all'>All</option>";
 ?>
    </select>
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * create a multi select field
 *
 * @param array $opt_field
 * @param mixed $label
 * @param string $select_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_multi_select($name,$options, $label, $select_opts = "", $extra_opts = null)
{
    global $global;
    
   $value =  $extra_opts['value'];

?>
    <label><?=$label?></label>
    <select name="<?=$name?>[]" <?=$select_opts?>
<?php
		  
    foreach ($options as $opt_value => $desc ) {
        if($value!=NULL){
            $sel = ( (array_search($opt_value,$value)==true) || (array_search($opt_value,$value)===0) ) ? "selected" : null ;
        }
?>
 <option value="<?=$opt_value?>" <?=$sel?>><?=$desc?></option>
<?php

     
      }
      if (isset($extra_opts['all']) || $extra_opts['all'] == true) echo "<option value='all'>All</option>";
 ?>
    </select>
<?php
    shn_form_extra_opts($extra_opts);
}


/**
 * create a checkboxes field based on field option
 *
 * @param mixed $opt_field
 * @access public
 * @return void
 */
function shn_form_opt_checkbox($opt_field,$extra_opts=null){
    global $global;

    $value = ($_POST[$opt_field])? $_POST[$opt_field] : null;
    $resu = $global['db']->Execute("select * from field_options where field_name='$opt_field'");

    while(!resu==NULL && !$resu->EOF) {
        $sel = ( $resu->fields[1] == $value ) ? "checked" : null ;
?>
        <label><?=$resu->fields[2]?></label>
        <input type="checkbox" name="<?=$opt_field?>[]" value="<?=$resu->fields[1]?>" <?=$sel?>></input>
        <br>
<?php
        $resu->MoveNext();
    }
    shn_form_extra_opts($extra_opts);
}

/**
 * HTML textarea element
 *
 * @param mixed $label
 * @param mixed $name
 * @param mixed $text_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_textarea($label, $name, $text_opts = null, $extra_opts = null)
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
    if(get_magic_quotes_gpc())
        $value = stripslashes($value);

?>
    <label><?=$label?></label>
    <textarea name="<?=$name?>" <?=$text_opts?> ><?=$value?></textarea>
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * HTML upload element
 *
 * @param mixed $label
 * @param mixed $name
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_upload($label, $name, $extra_opts = null)
{
?>
    <label><?=$label?></label>
    <input type="file" name="<?=$name?>" />
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * This is a pseudo element, which creats a label
 *
 * @param mixed $label
 * @param mixed $caption
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_label($label, $caption, $extra_opts = null)
{
    if(get_magic_quotes_gpc())
        $caption = stripslashes($caption);
?>
    <label><?=$label?></label>
    <?=$caption?>
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * HTML password text element
 *
 * @param mixed $label
 * @param mixed $name
 * @param mixed $text_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_password($label, $name, $text_opts = null, $extra_opts = null)
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
?>
    <label><?=$label?></label>
    <input type="password" name="<?=$name?>" value="<?=$value?>" <?=$text_opts?> />
<?php
    shn_form_extra_opts($extra_opts);
}

/**
 * This is a pseudo element, contains a date
 *
 * @param mixed $label
 * @param string $name
 * @param mixed $initdate
 * @access public
 * @return void
 */

/* This is the old date picker function
function shn_form_date($label, $name = 'date', $initdate = null )
{
    ($valueM = $_POST[$name.'M']) || ($valueM = ($initdate)? date('m',$initdate) : null);
    ($valueY = $_POST[$name.'Y']) || ($valueY = ($initdate)? date('Y',$initdate) : null);
    ($valueD = $_POST[$name.'D']) || ($valueD = ($initdate)? date('d',$initdate) : null);
    global $global;
?>
    <label><?=$label._(" (dd-mm-yyyy)")?></label>
    <input type="text" name="<?=$name.'D'?>" value="<?=$valueD?>" size="2" maxlength=2>&#175;
   
    <input type="text" name="<?=$name.'M'?>" value="<?=$valueM?>" size="2" maxlength=2>&#175;
   
    <input type="text" name="<?=$name.'Y'?>" value="<?=$valueY?>" size="4" maxlength=4>
<?php
}*/


function shn_form_date($label,$name,$extra_opts = null)
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];

    //including the script file only once
    static $script_include=false;
    if(!$script_include){
        echo "<script type='text/javascript' src='res/js/scw.js'></script>";
        $script_include=true;
    }
    $format=(isset($extra_opts['format']))?$extra_opts['format']:'yyyy-mm-dd';
    $string = strtoupper($format);
    $f=substr($string,  0, 1);
    $l=substr($string, -1, 1);
    $m=($f=='Y'||$l=='Y')?$m:'Y';
    $m=($f=='M'||$l=='M')?$m:'M';
    $m=($f=='D'||$l=='D')?$m:'D';
    $seq=$f.$m.$l;
?>

<label><?=$label?></label>
    <input type="text" name="<?=$name?>" value="<?=$value?>" id="<?=$name?>" onclick="scwDateOutputFormat='<?=$format?>';scwDateInputSequence='<?=$seq?>';scwShow(this,this);" size="12" maxlength="12">
<?php
    shn_form_extra_opts($extra_opts);
}


/* fancy popup calendar, however such systems are eyecandy and not efficient
function shn_form_date($label, $name = 'date')
{
    #$today = date("Y-m-d");
    $today = date("d/m/Y");
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
    global $global;
?>
    <script language="javascript" type="text/javascript" src="res/js/calendar.core.js"></script>
    <label><?=$label?></label>
<?php
    require_once $global['approot']."/3rd/popupcal/cal_class.php";
    $calendario=new Calendar("en");
    $calendario->CreateCalendar($today,$name,"1/1/2000","12/30/2000");
    # @TODO handle localization and remove fixed date range above

    shn_form_extra_opts($extra_opts);
}
*/

// this function enumerates through an array and displays it as elements 
// of a row. You may have many arrays within arrays.
function shn_form_table_row($elements, $text_opts=null) {

    static $depth = 0;

    if ($depth == 0) echo "    <tr $text_opts>\n";

    foreach ( $elements as $value) {

        if (is_array($value)) {
            $depth++;
            // recurse if it is an array
            //shn_form_print_row($value);
            $depth--;
        } else {
           echo "        <td>$value </td>\n";
        }
    }

    if ($depth == 0) echo "    </tr>\n";
}

function shn_form_fopen_alt($act, $mod = null, $form_opts = array('req_message'=>true))
{
    global $global;
    if ( null == $mod ) $mod = $global['module'];

    $form_id = $form_opts['id'];
    if($form_opts['req_message']){
?>
    <p><b>Key:</b> Fields marked with <b>*</b> are required (entry is compulsory)</p>
<?php
    }
?>
    <div id="<?=$form_id?>">
    <form method="POST" action="index.php?mod=<?=$mod?>&act=<?=$act?>" id="formset" <?=$form_opts['enctype']?>name="<?=$form_opts['name']?>">
<?php
}
?>
