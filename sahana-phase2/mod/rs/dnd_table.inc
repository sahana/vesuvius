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
global $global;
include_once $global['approot']."/inc/handler_db.inc";
include $global['approot']."/mod/rs/lib_table.inc";
include_once($global['approot']."/inc/browser_caps.inc");
include_once $global['approot']."/inc/reporting/lib_reporting.inc";
include_once("table.inc");
//var_dump($global['db']->MetaTables('TABLES'));
//var_dump($global['db']->ServerInfo());
?>

<!-- next line is for drag and drop events -->
<script type="text/javascript" src="res/js/dojo/dojo.js"></script>

<?php


$table_name = $_POST['table'];
$chosen_fields = $_POST['fields'];

// Next two three lines for check browser compatibility
//var_dump($global['bcaps']->getBrowser());

$javascript=$global['bcaps']->getBrowser()->JavaScript;
if($javascript==1){
//calling Dynamic reporting javascript functions
_shn_rs_dnd_table();
_shn_rs_lib_dnd();
//check weather a fields names or table name was submitted
if(isset($chosen_fields) && ($chosen_fields != "")){
	// if so then show result
	_shn_dr_show_table($table_name, $chosen_fields);
}
else{
	if(isset($table_name)){
			//Print the error message If an error occured 
			display_errors($return=false,$clean_errors=true,$exit=false);
// 			if table name is set then show fields dnd table 
			_shn_dr_dnd_fields($table_name);
	}
	else{
		//Print the error message If an error occured 
		display_errors($return=false,$clean_errors=true,$exit=false);
// 			if nothing is set then show dnd table 
	_shn_dr_dnd_table();
	}
}
}
else{
	shn_rs_get_dynamic_report_form();
}


// drag and drop containers for choosing table name
function _shn_dr_dnd_table(){
	$tables = _shn_dr_tables();

	echo "<h2>"._('Selecting data from a table')."</h2>";
	shn_form_fopen("dnd_table",null,array('enctype'=>'enctype="multipart/form-data"', 'id'=>'myForm'));

?>
<table id="dnd">
	<thead><td><strong>Tables to choose<strong></td><td><strong>Chosen table<strong></td></thead>
	<tbody>
	<tr><td id="kontener1">
			<ul>
			<?php
				foreach($tables as $tab => $name )
print "\t<li id=".$tab.">".$name."</li>\n";
			?>
			</ul>
	</td><td id="kontener2"><ul></ul>
	</td></tr>
	</tbody>
</table>
<?php
// passing data with POST method
	$hidden_vars['table'] = "none";
	shn_form_hidden($hidden_vars);
	shn_form_fclose();
}



// drag and drop containers for choosing fields
function _shn_dr_dnd_fields($table_name){
	$fields = _shn_dr_fields($table_name);
	echo "<h2>"._('Selecting data from a table')."</h2>";
	shn_form_fopen("dnd_table",null,array('enctype'=>'enctype="multipart/form-data"', 'id'=>'myForm'));
?>

<table id="dnd">
	<thead><td><strong>Fields to choose<strong></td><td><strong>Chosen fields<strong></td></thead>
	<tbody>
	<tr><td id="kontener3">
			<ul>
			<?php
				foreach($fields as $field => $name )
print "\t<li id=".$field.">".$name."</li>\n";
			?>
			</ul>
	</td><td id="kontener4">
	</td></tr>
	</tbody>
</table>

<?php
	print "<button onclick=\"submitFields()\" type=button>Create report</button>";
// passing data with POST method
	$hidden_vars['fields'] = "none";
	$hidden_vars['table'] = $table_name;
	shn_form_hidden($hidden_vars);
	shn_form_fclose();

}




// show table that user wanted to be shown
function _shn_dr_show_table($table_name, $chosen_fields){
	
	global $global;

	// getting user-friendly table_name
	$tables = _shn_dr_tables();
	$fields = _shn_dr_fields($table_name);

	$cond = "";
	$chosen_fields_array = split(",", $chosen_fields);
	foreach($chosen_fields_array as $key)
		$cond = $cond."OR field_name = '".$key."' ";
	$cond = ereg_replace("^OR", "", $cond);

// 	getting data from choosen table
	$sql = "SELECT DISTINCT $chosen_fields FROM $table_name";
	$res = $global['db']->Execute($sql); 
    
	
// 	printing out result
?>
		<h2><?php echo 'Results for: '.$tables[$table_name]; ?></h2>
    <div id="result">
    <table>
    <thead>
<?php
		foreach($chosen_fields_array as $field){
    	echo '<td><strong>'.$fields[$field].'</strong></td>';
    	$table_header[$field]=$fields[$field];
		}
?>
    </thead>
		<tboby>
<?php
        $table_data_display=array();
      	while($res->fields){
			echo '<tr>';
			foreach($chosen_fields_array as $field){
				echo '<td>'.$res->fields[$field].'</td>';
				$table_data[$field]=$res->fields[$field];
			}	
			echo '</tr>';
			$res->MoveNext();
			array_push($table_data_display,$table_data);
		}
?>
		</tbody>
		</table>
		</div>

<?php
//print_r($table_data_display);
//print_r($table_header);

    $rep_name=split(' ',$tables[$table_name]);
//This is for generata nice file name    
    foreach($rep_name as $rn){
        $dis_name=$dis_name.'_'.$rn;	
    }
//This is for download pdf version of the report    
    shn_report_fopen('pdf',$dis_name,$ims_report_keyword_arr,false,$table_name.'_pdf');
	shn_report_add_title($tables[$table_name]);
    shn_report_add_table($table_header,$table_data_display);
	shn_report_close(true);
	
//This is for download ods version of the report

    shn_report_fopen('ods',$dis_name,$ims_report_keyword_arr,false,$table_name.'_ods');
    shn_report_add_title($tables[$table_name]);
    shn_report_add_table($table_header,$table_data_display);
    shn_report_close(true);
//This is for download M$ excel version of the report   
    /*shn_report_fopen('xls',$dis_name,$ims_report_keyword_arr,false,$table_name.'_xls');
    shn_report_add_title($tables[$table_name]);
    shn_report_add_table($table_header,$table_data_display);
    shn_report_close(true);  */
    
//This is for export
    _shn_rs_export_init($sql,$dis_name,$tables[$table_name]);
}


