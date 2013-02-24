<?
/**
 * @name         Form Library
 * @version      11
 * @package      framework
 * @author       Chamindra de Silva (chamindra@opensource.lk>
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
 * @author       Richard Smith <s0459387@sms.ed.ac.uk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 *
 * @see http://www.php.net/manual/en/features.file-upload.php#74692 regarding alternate solution for large file upload
 *
 * @edited Carl Cornwell <ccornwell@mail.nih.gov> Fix typos - change res to $res in shn_form_opt_select
 *                                                          - add php to <?if in shn_form_checkbox
 * @edited Leif Neve <lneve@mail.nih.gov> Added optional stream param to shn_form_fopen
 */


$shn_help_id;
$shn_form_id; //this variable is used by the tab functions
$shn_tab_enabled=false; //this variable is used by the tab functions
$shn_tabindex=0; //used to prioritize form data entry fields when navigating with the [TAB] key



/**
 * You can add extra attributes to the given HTML element
 *
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_extra_opts($extra_opts) {
	global $shn_help_id;

	// show public or private info bubbles
	if (isset($extra_opts['public'])) {
		echo "\n<span class=\"publicText\">Public</span>\n";
	}
	if (isset($extra_opts['private'])) {
		echo "\n<span class=\"privateText\">Private</span>\n";
	}
	// Help
	if(isset($extra_opts['help'])) {
		$shn_help_id++;
		$_SESSION['form_help'][$shn_help_id] = "<div style=\"text-align: right;\"><a class=\"closeLink\" href=\"#\" onclick='hideCurrentPopup(); return false;'>X</a></div><br>".$extra_opts['help'];
		echo '<span class="helpIcon" onclick="return !showPopup(\'help_popup\', event,'.$shn_help_id.');">?</span>';
	}
	// output a required flag
	if (isset($extra_opts['req']) && true == $extra_opts['req']) {
		echo "\n <span class='req'>*</span>\n";
	}
	// show notes
	if (isset($extra_opts['note'])) {
		echo "<p class=\"note\">{$extra_opts['note']}</p>";
	}
	// output a break - default is true
	if ((!isset($extra_opts['br'])) ||( $extra_opts['br'] == true)) {
		echo "<br />\n    <div class='brake'></div>\n";
	}
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
function shn_form_fopen($act, $mod = null, $form_opts = array('req_message'=>true), $stream=null, $style="") {

	global $global;
	global $shn_form_id;
	global $shn_tab_enabled;

	if(null == $mod) {
		$mod = $global['module'];
	}

	if ($stream != null) {
		$stream_param = "&stream=$stream";
	} else {
		$stream_param = "";
        }

	static $idno=0; // generate a form id if the id is not set
	if(!isset($form_opts['id'])) {
		if (isset($form_opts['name'])) {// name and the id should be same XHTML
			$form_opts['id'] = $form_opts['name']; // use the name value for id also
		} else {
			$form_opts['id'] = "form".$idno++;
		}
	}
	$shn_form_id=$form_opts['id'];

	if(isset($form_opts['tab'])) {  //check to see if the tabing is enable
		global $shn_tab_enabled;
		$shn_tab_enabled=true;
	}

	if(isset($form_opts['anchor'])) {
		$anchor = '#' . $form_opts['anchor'];
	} else {
		$anchor = '';
	}


	// default some values that occassionally never get set
	if(!isset($form_opts['enctype'])) {
		$form_opts['enctype'] = "";
	}
	if(!isset($form_opts['tab'])) {
		$form_opts['tab'] = "";
	}

	//if the class is not given set it to default
	if(!isset($form_opts['class'])) {
		$form_opts['class']='form-container';
	}

	echo "
		<div onclick='event.cancelBubble = true;' class=\"popup\" id=\"help_popup\"></div><div class=\"".$form_opts['class']."\">
	";

	if(isset($form_opts['req_message']) && $form_opts['req_message'] == true) {
		echo "
			<br>
			<p><b>Key:</b><b class='red'> * </b> - Fields tagged with a red asterisk&#040;<span class='red'> * </span>&#041; are mandatory and must be filled in.</p><br>
		";
	}

	echo "
		<form method=\"post\" action=\"index.php?mod=".$mod."&amp;act=".$act.$stream_param.$anchor."\" id=\"".$form_opts['id']."\" ".$form_opts['enctype']." name=\"".$form_opts['id']."\" style=\"".$style."\">
	";

	//print the tab position div
	if ($shn_tab_enabled & !($form_opts['tab']=='float')) {
		shn_form_drawtab();
	}
}


/**
 * This function will open the HTML Form with custom url
 *
 * @param mixed $act
 * @param mixed $mod
 * @param string $form_opts
 * @access public
 * @return void
 */
function shn_form_fopen2($act, $mod = null, $form_opts = array('req_message'=>true), $stream=null, $style="") {

	global $global;
	global $shn_form_id;
	global $shn_tab_enabled;

	if(null == $mod) {
		$mod = $global['module'];
	}

	if ($stream != null) {
		$stream_param = "&stream=$stream";
	} else {
		$stream_param = "";
        }

	static $idno=0; // generate a form id if the id is not set
	if(!isset($form_opts['id'])) {
		if (isset($form_opts['name'])) {// name and the id should be same XHTML
			$form_opts['id'] = $form_opts['name']; // use the name value for id also
		} else {
			$form_opts['id'] = "form".$idno++;
		}
	}
	$shn_form_id=$form_opts['id'];

	if(isset($form_opts['tab'])) {  //check to see if the tabing is enable
		global $shn_tab_enabled;
		$shn_tab_enabled=true;
	}

	if(isset($form_opts['anchor'])) {
		$anchor = '#' . $form_opts['anchor'];
	} else {
		$anchor = '';
	}


	// default some values that occassionally never get set
	if(!isset($form_opts['enctype'])) {
		$form_opts['enctype'] = "";
	}
	if(!isset($form_opts['tab'])) {
		$form_opts['tab'] = "";
	}

	//if the class is not given set it to default
	if(!isset($form_opts['class'])) {
		$form_opts['class']='form-container';
	}

	echo "
		<div onclick='event.cancelBubble = true;' class=\"popup\" id=\"help_popup\"></div><div class=\"".$form_opts['class']."\">
	";

	if(isset($form_opts['req_message']) && $form_opts['req_message'] == true) {
		echo "
			<br>
			<p><b>Key:</b><b class='red'> * </b> - Fields tagged with a red asterisk&#040;<span class='red'> * </span>&#041; are mandatory and must be filled in.</p><br>
		";
	}

	echo "
		<form method=\"post\" action=\"".$act."\" id=\"".$form_opts['id']."\" ".$form_opts['enctype']." name=\"".$form_opts['id']."\" style=\"".$style."\">
	";

	//print the tab position div
	if ($shn_tab_enabled & !($form_opts['tab']=='float')) {
		shn_form_drawtab();
	}
}



/**
 * This function will close the HTML form
 *
 * @access public
 * @return void
 */
function shn_form_fclose() {
	global $shn_form_id;
	global $shn_tab_enabled;

	//print the tabscript and the tabposition div tag
	if($shn_tab_enabled){
		shn_form_drawtab();
		echo "<script language=\"JavaScript\">tabFieldset(\"$shn_form_id\");</script>";
	}
	echo "</form></div><!-- /formcontainer -->";
}



/**
 * This will produce a submit button
 *
 * @param mixed $name
 * @access public
 * @return void
 */
function shn_form_submit($name, $submit_opts = null) {
	global $shn_tabindex;
	echo "<input type=\"submit\" value=\"".$name."\" ".$submit_opts." tabindex=\"". ++$shn_tabindex ."\" />";
}



/**
 * This will produce a reset button
 *
 * @param mixed $name
 * @access public
 * @return void
 */
function shn_form_reset($name, $submit_opts = null) {
	global $shn_tabindex;

	echo "<input type=\"reset\" value=\"".$name."\" ".$submit_opts." tabindex=\"".++$shn_tabindex."\" />";
}



/**
 * Open and close a fieldset, which is a group of field
 *
 * @param mixed $label
 * @param string $id
 * @access public
 * @return void
 */
function shn_form_fsopen($label = null, $id = "noIdDefined") {
	echo '<fieldset id="'.$id.'"><legend>'.$label.'</legend>';
}



/**
 * HTML Form close
 *
 * @access public
 * @return void
 */
function shn_form_fsclose() {
	echo "</fieldset>";
}



/**
 * HTML button element
 *
 * @param mixed $name
 * @param mixed $button_opts
 * @access public
 * @return void
 */
function shn_form_button($name, $button_opts = null, $extra_opts = null) {
	global $shn_tabindex;
	echo "<input type=\"button\" value=\"".$name."\" ".$button_opts." tabindex=\"". ++$shn_tabindex ."\" />";
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
function shn_form_text($label, $name, $text_opts = null, $extra_opts = null) {
	global $shn_tabindex;

	$value = isset($_POST[$name]) ? $_POST[$name] : (isset($extra_opts['value']) ? $extra_opts['value'] : "");
	if(get_magic_quotes_gpc()) {
		$value = stripslashes($value);
	}

	if(!isset($extra_opts['no_label']) || (isset($extra_opts['no_label']) && $extra_opts['no_label'] !== true)) {
		echo "<label for=\"".$name."\">".$label."</label>";
	}
	echo "<input type=\"text\" name=\"".$name."\" id=\"".$name."\" value=\"".$value."\" ".$text_opts." tabindex=\"". ++$shn_tabindex ."\"";
	if (isset($extra_opts['has_error']) && $extra_opts['has_error'] == true) {
		echo 'class="err"';
	}
	if(isset($extra_opts['public']) && $extra_opts['public'] == true) {
		echo 'class="public"';
	}
	if(isset($extra_opts['private']) && $extra_opts['private'] == true) {
		echo 'class="private"';
	}
	echo " />";
	shn_form_extra_opts($extra_opts);
}



/**
 * HTML hidden element
 *
 * @param mixed $hidden_vars
 * @access public
 * @return void
 */
function shn_form_hidden($hidden_vars) {
	foreach ($hidden_vars as $name => $value) {

		// added support for multivalued hidden fields
		if(is_array($value) == true){
			foreach($value as $v){
				echo "<input type=\"hidden\" name=\"".$name."[]\" value=\"".$v."\" />";
			}
		} else {
			echo "<input type=\"hidden\" name=\"".$name."\" value=\"".$value."\" />";
		}
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
function shn_form_checkbox($label, $name, $text_opts = null, $extra_opts = null) {
	global $shn_tabindex;

	$value = isset($_POST[$name]) ? $_POST[$name] : $extra_opts['value'];
	$disabled = $extra_opts['disabled'] == NULL ? false : $extra_opts['disabled'];

	if(strlen(trim($label))>0) {
		echo "<label for=\"".$name."\">".$label."</label>";
	}
	echo "<input type=\"checkbox\" name=\"".$name."\" id=\"".$name."\" value=\"".$value."\" ";
	if($disabled){
		echo "disabled='true'";
	}
	echo " ".$text_opts." tabindex=\"".++$shn_tabindex."\" />";
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
function shn_form_select($options, $label, $name, $select_opts = "", $extra_opts = null) {
	global $global;
	global $shn_tabindex;

	$value = isset($_POST[$name]) ? $_POST[$name] : (isset($extra_opts['value']) ? $extra_opts['value'] : "");

	//to prevent warnings set $options to array() if it is null
	$options = ($options == null) ? array() : $options;

	echo "
		<label for=\"".$name."\">".$label."</label>
		<select name=\"".$name."\" id=\"".$name."\" ".$select_opts." tabindex=\"". ++$shn_tabindex ."\">
	";
	foreach ($options as $opt_value => $desc ) {
		$sel = ( $opt_value == $value ) ? 'selected="selected"' : null ;
		echo "
			<option value=\"".$opt_value."\" ".$sel.">".$desc."</option>
		";
	}
	echo "</select>";
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
function shn_form_radio($options, $label, $name, $select_opts = "", $extra_opts = null) {
	global $global;
	global $shn_tabindex;

	$value = isset($_POST[$name]) ? $_POST[$name] : $extra_opts['value'];

	if(!isset($extra_opts['no_label']) || (isset($extra_opts['no_label']) && $extra_opts['no_label'] !== true)) {
		echo "<label>".$label."</label>";
	}

	$checked='';
	foreach ($options as $opt_value => $desc ) {
		if($value == $opt_value) {
			$checked='checked';
		} else {
			$checked='';
		}
		echo "<input type=\"radio\" name=\"".$name."\" value=\"".$opt_value."\" tabindex=\"".++$shn_tabindex."\" ".$select_opts." ".$checked." /> ".$desc;
	}
	echo " ";
	shn_form_extra_opts($extra_opts);
}



/**
 * HTML radio button element v2
 * Notes: This function is provides the same functionality of the above function in a more simplified and elegant manner. -gmiernicki
 *
 * @param mixed $options
 * @param mixed $label
 * @param mixed $name
 * @param string $select_opts
 * @param mixed $extra_opts
 * @access public
 * @return void
 */
function shn_form_radio2($options, $label, $name, $checked, $extra_opts = null) {
	global $global;
	global $shn_tabindex;
	if(!isset($extra_opts['no_label']) || (isset($extra_opts['no_label']) && $extra_opts['no_label'] !== true)) {
		echo "<label>".$label."</label>";
	}
	foreach ($options as $option => $description ) {
		$checkedText = ($checked == $option) ? "checked" : "";
		echo "<input type=\"radio\" name=\"".$name."\" value=\"".$option."\" tabindex=\"".++$shn_tabindex."\" ".$checkedText."/> ".$description;
	}
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
function shn_form_opt_select($opt_field, $label, $select_opts = "", $extra_opts = null) {
	global $global;
	global $shn_tabindex;

	$sort  = isset($extra_opts['sort']) ? $extra_opts['sort'] : null;
	$name  = isset($extra_opts['name']) ? $extra_opts['name'] : $opt_field;
	$value = isset($_POST[$opt_field])  ? $_POST[$opt_field]  : $extra_opts['value'];
	if (isset($extra_opts['public']) && $extra_opts['public'] == true) {
		$class = 'class="public"';
	}
	if (isset($extra_opts['private']) && $extra_opts['private'] == true) {
		$class = 'class="private"';
	} else {
		$class = "";
	}
	echo "<label>".$label."</label> <select name=\"".$name."\" ".$select_opts." tabindex=\"".++$shn_tabindex."\" ".$class." \>";
/*
	?><label><?php echo $label?></label> <select name="<?php echo $name?>" <?php echo $select_opts?> tabindex="<?php echo ++$shn_tabindex?>" > <?php
*/
	if ($sort == null) {
		$q="select * from field_options where field_name='{$opt_field}'";
	} else {
		$q="select * from field_options where field_name='{$opt_field}' order by $sort ";
	}
	$res = $global['db']->Execute($q);
	if (isset($extra_opts['select']) && $extra_opts['select'] == true) {
		echo "<option value='select'>- Select -</option>";
	}
	while(!$res==NULL && !$res->EOF) {
		$sel = ($res->fields[1] == $value) ? 'selected="selected"' : null;
		echo "<option value=\"".$res->fields[1]."\" ".$sel.">"._lc($res->fields[2])."</option> ";
		$res->MoveNext();
	}
	if (isset($extra_opts['all']) && $extra_opts['all'] == true){
		$sel = (strtolower($value) == 'all')?"selected=\"selected\"":"";
		echo "<option value='all' $sel>[ALL]</option>";
	}
	echo "</select>";
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
function shn_form_opt_multi_select($opt_field, $label, $select_opts = "", $extra_opts = null) {
	global $global;
	global $shn_tabindex;
	$value = ($_POST[$opt_field])? $_POST[$opt_field] : $extra_opts['value'];

	?><label><?php echo $label?></label><select name="<?php echo $opt_field?>[]" <?php echo $select_opts?> tabindex="<?php echo ++$shn_tabindex?>"><?php
	if($extra_opts["sort"]==true){
		$q="select * from field_options where field_name='$opt_field' order by option_code";
	} else{
		$q="select * from field_options where field_name='$opt_field'";
	}
	$res = $global['db']->Execute($q);
	while(!res==NULL && !$res->EOF) {
		if($value!=NULL) {
			$sel = ( (array_search($res->fields["option_code"],$value)==true) || (array_search($res->fields["option_code"],$value)===0) ) ? 'selected="selected"' : null ;
		}
		?><option value="<?php echo $res->fields["option_code"]?>" <?php echo $sel?>><?php echo $res->fields["option_description"]?></option><?php
		$res->MoveNext();
	}
	if (isset($extra_opts['all']) || $extra_opts['all'] == true) {
		echo "<option value='all'>All</option>";
	}
	?></select><?php
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
function shn_form_multi_select($name, $options, $label, $select_opts = "", $extra_opts = null) {
	global $global;
	global $shn_tabindex;
	$value = isset($extra_opts['value']) ? $extra_opts['value'] : "";
	$size  = count($options);

	if($size > 31) {
		$size = 31; // 31 is a good number :)
	}

	echo "
		<label>".$label."</label>
		<select multiple size=\"".$size."\" id=\"".$name."\" name=\"".$name."[]\" ".$select_opts." tabindex=\"".++$shn_tabindex."\">
	";

	foreach ($options as $opt_value => $desc ) {
		if($value != NULL) {
			$sel = ((array_search($opt_value,$value) == true) || (array_search($opt_value,$value) === 0)) ? 'selected="selected"' : null;
		} else {
			$sel = "";
		}
		echo "<option value=\"".$opt_value."\" ".$sel.">".$desc."</option>";
	}

	if(isset($extra_opts['all']) && $extra_opts['all'] == true) {
		echo "<option value='all'>All</option>";
	}

	echo "</select>";
	shn_form_extra_opts($extra_opts);
}



/**
 * create a checkboxes field based on field option
 *
 * @param mixed $opt_field
 * @access public
 * @return void
 */
function shn_form_opt_checkbox($opt_field, $extra_opts = null) {
	global $global;
	global $shn_tabindex;

	$value = isset($_POST[$opt_field]) ? $_POST[$opt_field] : "";
	$resu = $global['db']->Execute("select * from field_options where field_name='$opt_field'");

	$selected=$extra_opts['selected'];
	while(!resu==NULL && !$resu->EOF) {
		$sel=null;
		for($i=0;$i<count($selected);$i++) {
			if($selected[$i]==$resu->fields[1]) {
				$sel='checked';
			}
		}
		// $sel = ( $resu->fields[1] == $value ) ? "checked" : null ;
		?><label><?php echo _lc($resu->fields[2])?></label><input type="checkbox" name="<?php echo $opt_field?>[]" value="<?php echo $resu->fields[1]?>" tabindex="<?php echo ++$shn_tabindex?>" <?php echo $sel?>></input><br><?php
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
function shn_form_textarea($label, $name, $text_opts=null, $extra_opts = null) {
	global $shn_tabindex;

	$cols  = isset($extra_opts['cols']) ? $extra_opts['cols'] : '30';
	$rows  = isset($extra_opts['rows']) ? $extra_opts['rows'] : '4';
	$value = isset($_POST[$name]) ? $_POST[$name] : isset($extra_opts['value']) ? $extra_opts['value'] : "";

	if(isset($extra_opts['has_error']) && $extra_opts['has_error'] == true) {
		$class = 'class="err"';
	}
	if(isset($extra_opts['public']) && $extra_opts['public'] == true) {
		$class = 'class="public"';
	}
	if(isset($extra_opts['private']) && $extra_opts['private'] == true) {
		$class = 'class="private"';
	} else {
		$class = "";
	}
	if(!isset($extra_opts['no_label']) || (isset($extra_opts['no_label']) && $extra_opts['no_label'] !== true)) {
		echo "<label for=\"".$name."\">".$label."</label>";
	}
	echo "<textarea name=\"".$name."\" id=\"".$name."\" cols=\"".$cols."\" rows=\"".$rows."\" ".$text_opts." tabindex=\"".++$shn_tabindex."\" ".$class." >".$value."</textarea>";
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
function shn_form_upload($label, $name, $extra_opts = null) {
	global $shn_tabindex;
	if (isset($extra_opts['public'])) {
		$class = 'class="public"';
	} else if (isset($extra_opts['private'])) {
		$class = 'class="private"';
	} else {
		$class = "";
	}

	// Added 1/23/10 (c.cornwell) to allow upload of Google daily PFIF snapshot
	$max_size = " ";
	if (isset($extra_opts['max_file_size'])) {
		$max_size = " max_file_size = \"".$extra_opts['max_file_size']."\" ";
	}
	echo "<label>".$label."</label><input type=\"file\" id=\"".$name."\" name=\"".$name."\" tabindex=\"".++$shn_tabindex."\" ".$class.$max_size." />";
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
function shn_form_label($label, $caption, $extra_opts = null) {
	if (get_magic_quotes_gpc()) {
		$caption = stripslashes($caption);
	}
	?><label><?php echo $label?></label><label class="value"><?php echo $caption?></label>	<?php
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
function shn_form_password($label, $name, $text_opts = null, $extra_opts = null) {
	global $shn_tabindex;
	$value = isset($_POST[$name]) ? $_POST[$name] : (isset($extra_opts['value']) ? $extra_opts['value'] : "");
	echo "<label for=\"".$name."\">".$label."</label><input type=\"password\" name=\"".$name."\" id=\"".$name."\" value=\"".$value."\" ".$text_opts." tabindex=\"".++$shn_tabindex."\" />";
	echo shn_form_extra_opts($extra_opts);
}



// this function enumerates through an array and displays it as elements
// of a row. You may have many arrays within arrays.
function shn_form_table_row($elements, $text_opts=null) {
	static $depth = 0;
	if ($depth == 0) {
		echo "    <tr $text_opts>\n";
	}
	foreach ($elements as $value) {
		if (is_array($value)) {
			$depth++;
			// recurse if it is an array
			//shn_form_print_row($value);
			$depth--;
		} else {
			echo "        <td>$value </td>\n";
		}
	}
	if ($depth == 0) {
		echo "    </tr>\n";
	}
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
function shn_form_date($label, $name, $extra_opts=null) {
	global $shn_tabindex;
	$value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];

	//including the script file only once
	static $script_include=false;
	if(!$script_include){
		echo "<script type='text/javascript' src='res/js/scw.js'></script>";
		$script_include=true;
	}
	$format = (isset($extra_opts['format']))?$extra_opts['format']:'yyyy-mm-dd';
	$string = strtoupper($format);
	$f      = substr($string,  0, 1);
	$l      = substr($string, -1, 1);
	$m      = ($f=='Y' || $l=='Y') ? $m : 'Y';
	$m      = ($f=='M' || $l=='M') ? $m : 'M';
	$m      = ($f=='D' || $l=='D') ? $m : 'D';
	$seq    = $f.$m.$l;
	if ($extra_opts['public'] == true) {
		$class = 'class="public"';
	}
	if ($extra_opts['private'] == true) {
		$class = 'class="private"';
	}
	echo "<label>".$label."</label><input type=\"text\" name=\"".$name."\" value=\"".$value."\" id=\"".$name."\" size=\"12\" maxlength=\"12\" tabindex=\"".++$shn_tabindex."\" ".$class." />";
	echo "<span> <img src=\"res/img/x-office-calendar.png\" onclick=\"scwDateOutputFormat='".$format."';scwDateInputSequence='".$seq."';scwShow(document.getElementById('".$name."'), this);\" alt=\"Click Here\" /><span>";
	shn_form_extra_opts($extra_opts);
}



/**
 * This function can be used to set the tab place.
 * To use this function you have set the 'tab'=>'float' in the fopen function.
 *
 * @param mixed $label
 * @param string $name
 * @param mixed $initdate
 * @access public
 * @return void
 */
function shn_form_drawtab() {
	static $draw=true;
	if($draw){
		echo "<br/><div id='tabPosition'></div>";
		$draw=false;
	}
}



function shn_form_fopen_alt($act, $mod = null, $form_opts = array('req_message'=>true), $style="") {
	global $global;
	if(null == $mod) {
		$mod = $global['module'];
	}
	$form_id = $form_opts['id'];
	if($form_opts['req_message']) {
		echo "
			<p><b>Key:</b> Fields marked with <b>*</b> are required (entry is compulsory)</p>
		";
	}
	echo '
		<div id='.$form_id.'><form method="POST" action="index.php?mod='.$mod.'&amp;act='.$act.'" id="formset" '.$form_opts['enctype'].' name="'.$form_opts['name'].'" style="'.$style.'">
	';
}



/**
 * This will render a flash still image capture interface.
 * It will also generate a unique image_id and put it under the key
 * $_SESSION['online_cam']['image_id'].
 * The security key will be stored under
 * $_SESSION['online_cam']['seckey']
 *
 * @param String $act The action of the current page
 * @param String $mod The module of the current page.
 */
function shn_form_still_camera($act = null, $mod = null) {
	global $global;
	include_once($global['approot']."inc/online_cam/online_cam.inc");
	$session_id = session_id();
	$time = time();
	$rand1 = rand(0,9999);
	$rand2 = rand(0,9999);
	$image_id = (($mod!=null)?$mod:"home")."_".(($act!=null)?$act:"default")."_".$rand1.$time.$rand2;
	shn_online_cam($image_id);
}



/**
 * Prints button sets at bottom of a page in the order of
 * cancel(0..1), back(0..1), next(0..1) | finish(0..1) | confirm(0..1), custom_button(0..*)
 *
 * Example Input:
 *  $button_set = array('cancel' => true, 'back' => true, 'next' => true,
 *                  'custom' => array(
 *                    array('value' => 'button text1', 'submit_opts' => 'name = "post value1"'),
 *                    array('value' => 'button text2', 'submit_opts' => 'name = "post value2"')))
 *
 * @param <type> $button_set
 */
function shn_form_submit_set($button_set = array('cancel' => true, 'back' => true, 'next' => true)) {
	if(isset($button_set['cancel'])) {
		shn_form_submit(_t('Form-Submit-Button|Cancel'), 'name="cancel"');
	}
	if(isset($button_set['back'])) {
		shn_form_submit(_t('Form-Submit-Button|Back'), 'name="back"');
	}
	if(isset($button_set['next'])) {
		shn_form_submit(_t('Form-Submit-Button|Next'), 'name="next"');
	} elseif(isset($button_set['finish'])) {
		shn_form_submit(_t('Form-Submit-Button|Finish'), 'name="finish"');
	} elseif(isset($button_set['confim'])) {
		shn_form_submit(_t('Form-Submit-Button|Confirm'), 'name="confirm"');
	}
	if(isset($button_set['custom'])) {
		$custom_buttons = $button_set['custom'];
		for($i = 0; $i < count($custom_buttons); $i++) {
			shn_form_submit($custom_buttons[$i]['value'], $custom_buttons[$i]['submit_opts']);
		}
	}
}



/**
 * Progress Bar
 *
 * Add this to a page to create a progress bar detailing the user's progress
 * through a task.
 *
 * @param <type> $steps - Array(str): All steps.
 * @param <type> $current_step - Int: The current step the user is on.
 */
function shn_form_progress_bar($steps, $current_step) {
	$total_step = count($steps);
	echo '<div id="progress_bar"><table><tr>';
	for($i = 1; $i <= $total_step; $i++){
		echo '<td ';
		if($i == $current_step){
			echo 'id="progress_bar_tab_current"';
		} elseif($i < $current_step){
			echo 'class="progress_bar_tab_before"';
		} else{
			echo 'class="progress_bar_tab_after"';
		}
		echo ' width="' . (100 / $total_step) . '%">';;
		echo $i . '. ' . $steps[$i - 1];
		echo '</td>';
		if($i != $total_step){
			echo '<td class="progress_bar_tab_spacer"><img src="theme/default/img/bullet_go.png"></td>';
		}
		next($steps);
	}
	echo '</tr></table></div><br />';
}



/**
 * This function will draw a wysiwyg editor on the form
 *
 */
function shn_form_wysiwyg($label, $name, $extra_opts = array()) {
	global $shn_tabindex;
	global $global;
	global $conf;
	$value = ($_POST[$name])? $_POST[$name] : $extra_opts['value'];
	if(get_magic_quotes_gpc()) {
		$value = stripslashes($value);
	}
	?><h4><?php echo $label?></h4><?php
	if(isset($conf['wysiwyg'])==false || strlen(trim($conf['wysiwyg']))==0){
		echo "<div class='error message'>"._t("Form-Wysiwyg-Text|Wysiwyg editor not configured correctly. Using Textarea instead.")."<br/><br/></div>";
		shn_form_textarea($label,$name,null,$extra_opts);
	}
	switch($conf['wysiwyg']){
		case 'tiny_mce':
			static $mceinit = true;
			if($mceinit){
				?>
				<!-- TinyMCE -->
					<script type="text/javascript" src="res/tiny_mce/tiny_mce.js"></script>
					<script type="text/javascript">
						tinyMCE.init({
							mode : "specific_textareas",
							editor_selector : "mceEditor"
						});
					</script>
				<!-- /TinyMCE -->
				<?php
				$mceinit = false;
			}
			echo "<textarea id='$name' name='$name' rows='15' cols='80' style='width:100%' class='mceEditor'>".htmlspecialchars($value)."</textarea>";
		break;

		case 'fckeditor':
			if(file_exists($global['approot'].'www/res/fckeditor/fckeditor.php')){
				include_once $global['approot'].'www/res/fckeditor/fckeditor.php';
				$sBasePath = 'res/fckeditor/' ;
				$oFCKeditor = new FCKeditor($name) ;
				$toolbar = (isset($extra_opts['tool_bar']))?$extra_opts['tool_bar']:'Basic';
				$oFCKeditor->ToolbarSet = htmlspecialchars($toolbar);
				$oFCKeditor->BasePath	= $sBasePath ;
				$oFCKeditor->Value		= $value ;
				$oFCKeditor->Create() ;
			}else{
				// show normal text area
				echo "<div class='error message'>"._t("Form-Wysiwyg-Text|A required file was not found. Failed to initialize Wysiwig Editor. Using Textarea instead.")."<br/><br/></div>";
				shn_form_textarea($label,$name,null,$extra_opts);
			}
		break;

		default:
		//currently print a text area when EXTjs is included use it's wysiwyg
	}
	shn_form_extra_opts($extra_opts);
}
