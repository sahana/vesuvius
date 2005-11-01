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

// Open and close a form section

function shn_form_fopen($act, $mod = null)
{
    global $global;
    if ( null == $mod ) $mod = $global['module'];
?>
    <p><b>Key:</b> Fields marked with <b>*</b> are required (entry is compulsory)</p>
    <div id="formcontainer">
    <form method="POST" action="index.php?mod=<?=$mod?>&act=<?=$act?>" id="formset" >
<?php
}

function shn_form_fclose()
{ ?>
    <input type="submit" value="Submit"/>
    </form>
    </div> <!-- /formcontainer -->
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
                        $extra_opts = null)
{
    $value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
?>
    <label><?=$label?></label>
    <input type="text" name="<?=$name?>" value="<?=$value?>" <?=$text_opts?>  />
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

// create a select field based on field options
function shn_form_opt_select($opt_field, $label, 
                                $select_opts = "", $extra_opts = null)
{
    global $global;

    $value = ($_POST[$opt_field])? $_POST[$opt_field] : null;
?>
    <label><?=$label?></label>
    <select name="<?=$opt_field?>" <?=$select_options?> >
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

// function to deal with additional options such as <BR> and is required 
function shn_form_extra_opts($extra_opts)
{
    // output a required flag
    if (true == $extra_opts['req']) echo "\n    <b>*(req)</b>\n"; 
    // output a break - default is true
    if (!isset($extra_opts['br']) || $extra_opts['br'] == true) echo "\n    <br/>\n";
}
