<?php
/**
 * Dump File Upload Handler 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Agnieszka Kulikowska <agnieszka.kulikowska@gmail.com>
 * @author     Ishan Liyanage <ishanul@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot']."/inc/handler_db.inc";
include_once ("lib_table.inc");

function shn_rs_get_dynamic_report_form(){
	$table_name = $_POST['tableName'];
    $chosen_fields = $_POST['fieldsNames'];
//check weather a fields names or table name was submitted
if(isset($chosen_fields)){
	// if so then show table
	_shn_dr_show_table_form($table_name, $chosen_fields);
}
else{
	if(isset($table_name) && ($table_name != "0")){
		//Print the error message If an error occured 
		display_errors($return=false,$clean_errors=true,$exit=false);
// 		if table name is set then show fields form 
		_shn_dr_fields_form($table_name);
	}
	else{
		if($table_name == "0"){
			add_error("Please select a table name.");
			_shn_dr_table_form();
		}
		else{
		//Print the error message If an error occured 
		display_errors($return=false,$clean_errors=true,$exit=false);
// 		if nothing is set then show table form 
		_shn_dr_table_form();
		}
	}
}
}

// form for fields names
function _shn_dr_fields_form($table_name){
	$tables = _shn_dr_tables();
	$usrfr_table_name = $tables[$table_name];

	$fields = _shn_dr_fields_form_second($table_name);
	$table['tableName'] = $table_name;

	echo "<h2>"._('Viewing any part of database table')."</h2>";
	//functions from lib_form.inc
    shn_form_fopen("table&amp",null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_('Names of fields of the table: '.$usrfr_table_name));
    echo '<p>'._('Choose which fields would you like to view. ')."<em><strong>"."</p>";
	shn_form_multi_select('fieldsNames', $fields, 'Names of fields:', 'multiple="multiple"');
	shn_form_hidden($table);
    shn_form_fsclose();
    shn_form_submit(_('Create report'));
    shn_form_fclose();


}


// function returns array where key is field name and value is fields user-friendly name
function _shn_dr_fields_form_second($table_name){
	global $global;

	// getting user-friendly tables names
	$sql = "SELECT dr_fields.usrfr_field_name,dr_fields.field_name FROM dr_fields 
					WHERE dr_fields.table_name='$table_name'";
	$res = $global['db']->Execute($sql); 

// 	$fields[0] = 'Select all';
	while($res->fields['usrfr_field_name'] != NULL){
		$fields[$res->fields['field_name']] = $res->fields['usrfr_field_name'];
		$res->MoveNext();
	}
	return $fields;
}



// function returns array where key is table name and value is tables user-friendly name
function _shn_dr_tables_form(){
	global $global;

	// getting user-friendly tables names
	$sql = "SELECT dr_tables.usrfr_table_name,dr_tables.table_name FROM dr_tables";
	$res = $global['db']->Execute($sql); 

	$tables[0] = '--Choose the table--';
	while($res->fields['usrfr_table_name'] != NULL){
		$tables[$res->fields['table_name']] = $res->fields['usrfr_table_name'];
		$res->MoveNext();
	}

	return $tables;
}




// form for choosing table
function _shn_dr_table_form(){
	$tables = _shn_dr_tables_form();

	echo "<h2>"._('Viewing any part of database table')."</h2>";
	//functions from lib_form.inc
    shn_form_fopen("table&amp",null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_('Name of a table'));
    echo "<p>"._('Choose which table would you like to view.')."</p>";
		shn_form_select($tables, 'Table Names', 'tableName');
    shn_form_fsclose();
    shn_form_submit(_('Submit'));
    shn_form_fclose();
}




// show table that user wanted to be shown
function _shn_dr_show_table_form($table_name, $chosen_fields){
	global $global;
    //print_r($chosen_fields);
	// getting user-friendly table_name
	$tables = _shn_dr_tables();
	$usrfr_table_name = $tables[$table_name];


	$i = 0;
	while($i < count($chosen_fields)-1){
		$tmp1 = $tmp1."field_name='$chosen_fields[$i]' OR ";
		$tmp2 = $tmp2." $chosen_fields[$i] , ";
		$i++;
	}
	
	$tmp1 = $tmp1."field_name='$chosen_fields[$i]'";
	$tmp2 = $tmp2."$chosen_fields[$i] ";
    //echo $tmp1;
	//echo $tmp2;
	// getting user-friendly fields names of the choosen table and selected fields
	$sql = "SELECT dr_fields.usrfr_field_name,dr_fields.field_name FROM dr_fields
					WHERE table_name='$table_name' AND ($tmp1)";	

	$res = $global['db']->Execute($sql); 

	$i = 0;
	
	while($res->fields['field_name'] != NULL){
		$usrfr_field_name[$i] = $res->fields['usrfr_field_name']; 
		$field_name[$i++] = $res->fields['field_name']; 
		$res->MoveNext();
	}

// 	getting data from choosen table
	$sql = "SELECT DISTINCT $tmp2 FROM `$table_name`";
	//echo $sql;
	$res = $global['db']->Execute($sql); 


// 	printing out result
?>
	<h2><?php echo 'Results for: '.$usrfr_table_name; ?></h2>
    <div id="result">
    <table>
    <thead>
<?php
	$i = 0;
	while($usrfr_field_name[$i] != NULL && $usrfr_field_name[$i] != EOF){
        echo '<td><strong>'.$usrfr_field_name[$i++].'</strong></td>';
	}
?>
    </thead>
	<tboby>
<?php

		while(!$res->EOF){
			echo '<tr>';
			$k = 0;
			//print_r($field_name);
			while($k < count($field_name))
				echo '<td>'.$res->fields[$field_name[$k++]].'</td>';
			echo '</tr>';
			$res->MoveNext();
		}
?>
    </tbody>
	</table>
	</div>

<?php
}


