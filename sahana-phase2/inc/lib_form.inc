<?php
/*
*
* Sahana HTML form library
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     http://www.linux.lk/~chamindra
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

// function to deal with additional options such as <BR> and is required 
function shn_form_extra_opts($extra_opts)
{
    // output a required flag
    if (true == $extra_opts['req']) echo "\n    <b>*(req)</b>\n"; 
    // output a break - default is true
    if (!isset($extra_opts['br']) || $extra_opts['br'] == true) echo "\n    <br/>\n";
}
// Open and close a form section

function shn_form_fopen($act, $mod = null, $form_opts = null)
{
    global $global;
    if ( null == $mod ) $mod = $global['module'];
?>
    <p><b>Key:</b> Fields marked with <b>*</b> are required (entry is compulsory)</p>
    <div id="formcontainer">
    <form method="POST" action="index.php?mod=<?=$mod?>&act=<?=$act?>" id="formset" <?=$form_opts['enctype']?>>
<?php
}

function shn_form_fclose()
{ ?>
    </form>
    </div> <!-- /formcontainer -->
<?php
}

function shn_form_submit($name)
{ ?>
    <input type="submit" value="<?=$name?>"/>
<?php
}

// Open and close a fieldset, which is a group of fields

function shn_form_fsopen($label = null)
{ ?>
    <fieldset>
    <legend><?=$label?></legend>
<?php
}

function shn_form_fsclose()
{ ?>
    </fieldset>
<?php
}

// enter the fields

function shn_form_text($label, $name, $text_opts = null, 
                        $extra_opts = null, $readonly = false, $disabled = false)
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
?>
    <label><?=$label?></label>
    <input type="text" name="<?=$name?>" value="<?=$value?>" <?=$text_opts?> <?php $readonly?print"readonly":print" "?> <?php $disabled?print"disabled":print" "?> />
<?php
    shn_form_extra_opts($extra_opts);
}


function shn_form_hidden($hidden_vars) 
{
    foreach ($hidden_vars as $name => $value) {
?>
    <input type="hidden" name="<?=$name?>" value="<?=$value?>">
<?php   
    }
}

function shn_form_checkbox($label, $name, $text_opts = null, 
                        $extra_opts = null)
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
?>
    <label><?=$label?></label>
    <input type="checkbox" name="<?=$name?>" value="<?=$value?>" <?=$text_opts?>  />
<?php
    shn_form_extra_opts($extra_opts);
}


function shn_form_select($options,$label, $name,$select_opts = "", $extra_opts = null)
{
    global $global;

    $value = ($_POST[$opt_field])? $_POST[$opt_field] : null;
?>
    <label><?=$label?></label>
    <select name="<?=$name?>" <?=$select_opts?> >
<?php
    foreach ($options as $opt_value => $desc ) {
    
        $sel = ( $res->fields[1] == $value ) ? "selected" : null ;
?>
        <option value="<?=$opt_value?>" <?=$sel?>><?=$desc?></option>
<?php
    }
?>
    </select> 
<?php
    shn_form_extra_opts($extra_opts);
} 



// create a select field based on field options
function shn_form_opt_select($opt_field, $label, 
                                $select_opts = "", $extra_opts = null)
{
    global $global;

    $value = ($_POST[$opt_field])? $_POST[$opt_field] : null;
?>
    <label><?=$label?></label>
    <select name="<?=$opt_field?>" <?=$select_opts?> >
<?php

    $res = $global['db']->Execute
        ("select * from field_options where field_name='$opt_field'");
    while(!res==NULL && !$res->EOF) {
        
        $sel = ( $res->fields[1] == $value ) ? "selected" : null ;
?>
        <option value="<?=$res->fields[1]?>" <?=$sel?>><?=$res->fields[2]?></option>
<?php
        $res->MoveNext();
    }
?>
    </select> 
<?php
    shn_form_extra_opts($extra_opts);
} 


function shn_form_opt_checkbox($opt_field){
    global $global;
		$value = ($_POST[$opt_field])? $_POST[$opt_field] : null;
		$resu = $global['db']->Execute
		       ("select * from field_options where field_name='$opt_field'");
			     while(!resu==NULL && !$resu->EOF) {
		            $sel = ( $resu->fields[1] == $value ) ? "checked" : null ;
?>
				       <label><?=$resu->fields[2]?></label>
				       <input type="checkbox" name="<?=$opt_field?>[]" value="<?=$resu->fields[1]?>" <?=$sel?>></input>
     		       <br>
<?php
				       $resu->MoveNext();
   		     }
}

function shn_form_textarea($label, $name, $text_opts = null, 
                        $extra_opts = null)
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
?>
    <label><?=$label?></label>
    <textarea name="<?=$name?>" <?=$text_opts?> ><?=$value?></textarea>
<?php
    shn_form_extra_opts($extra_opts);
}

function shn_form_upload($label, $name,
                        $extra_opts = null)
{
?>
    <label><?=$label?></label>
    <input type="file" name="<?=$name?>" />
<?php
    shn_form_extra_opts($extra_opts);
}

function shn_form_label($label, $caption,
                        $extra_opts = null)
{
?>
    <label><?=$label?></label>
    <?=$caption?>
<?php
    shn_form_extra_opts($extra_opts);
}

?>
