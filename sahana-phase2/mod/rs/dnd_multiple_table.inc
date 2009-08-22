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
include $global['approot']."/mod/rs/lib_table.inc";

?>

<!-- next lines are for drag and drop events -->
<script type="text/javascript" src="res/js/dojo/dojo.js"></script>

<?php

$tables_name = $_POST['table'];
$chosen_fields = $_POST['fields'];
$create_table = $_POST['crt'];
$keys = $_POST['keys'];
$topic=$_POST['rep_name'];
if(!isset($topic)){
	$topic=NULL;
}
//calling dynamic reporting javascript functions
_shn_rs_lib_dnd();
_shn_rs_dnd_multiple_table();

if(($create_table == "true")&&($chosen_fields != "")){
	if(isset($keys))
		_shn_dr_show_table($tables_name, $chosen_fields, $keys,$topic);
	else
		_shn_dr_show_table($tables_name, $chosen_fields, null,$topic);
}
else{
	if(isset($tables_name)&&($tables_name != "")){
			//Print the error message If an error occured 
			display_errors($return=false,$clean_errors=true,$exit=false);
// 			if table name is set then show fields dnd form 
		_shn_dr_dnd_table(split(",", $tables_name), split(",", $chosen_fields));
	}
	else{
		//Print the error message If an error occured 
		display_errors($return=false,$clean_errors=true,$exit=false);
// 			if nothing is set then show table dnd form 
	_shn_dr_dnd_table(null, null);
	}
}





// drag and drop containers for choosing table name and fields name
function _shn_dr_dnd_table($tables_name, $chosen_fields){

	$tables = _shn_dr_tables();

	echo "<h2>"._('Selecting data from several tables')."</h2>";
	shn_form_fopen("dnd_multiple_table",null,array('enctype'=>'enctype="multipart/form-data"', 'id'=>'myForm'));
    shn_form_fsopen();
	?>
	<table id="dnd">
		<thead><td><strong>Tables to choose<strong></td><td><strong>Chosen tables<strong></td></thead>
		<tbody>
		<tr><td id="kontener1">
				<ul>
				<?php	
// filling tables list if none was chosen
	if($tables_name == ""){
		foreach($tables as $tab => $name )
			print "\t<li class=table id=".$tab.">".$name."</li>\n";
				?>
				</ul>
		</td><td id="kontener2"><ul></ul>
		</td></tr>
		</tbody>
	</table>
	<?php
// filling tables list if some was chosen
	}
	else{
		$foreign = _shn_dr_get_foreign_tables($tables_name);
		foreach($foreign as $tab)
			if(array_key_exists($tab, $tables) && !in_array($tab, $tables_name))
				print "\t<li id=".$tab.">".$tables[$tab]."</li>\n";	
				?>
				</ul>
		</td><td id="kontener2">
			<ul>
				<?php
// filling chosen tables list 
					$i = 0;
					foreach($tables_name as $tab )
						print "\t<li class=table".$i++." id=".$tab.">".$tables[$tab]."</li>\n";
				?></ul>
		</td></tr>
		</tbody>
		<thead><td><strong>Fields to choose<strong></td><td><strong>Chosen fields<strong></td></thead>
		<tbody>
		<tr><td id="kontener3"><ul>
			<?php				
// filling fields list
					$i = 0;
					foreach($tables_name as $tab ){
						$fields[$tab] = _shn_dr_fields($tab);
						foreach($fields[$tab] as $name => $usr_fr_name )
							if(!in_array($tab.".".$name, $chosen_fields))
								print "\t<li class=table".$i." id=".$tab.".".$name.">".$usr_fr_name."</li>\n";
							else{
								$fl[$name] = $usr_fr_name;
								$class[$name] = $i;
								}
						$i++;
					}
			?>
			</ul></td><td id="kontener4"><ul>
			<?php
// filling chosen fields list
					foreach($chosen_fields as $two){
						if(($two != "none")&&($two != "")){
							$new = split("\.", $two);
							print "\t<li class=table".$class[$new[1]]." id=".$two.">".$fl[$new[1]]."</li>\n";	
						}
					}
			?>
			</ul></td></tr>
		</tbody>
	</table>
	<br>
	<br>
	
	<?php
	    $extra_opts['help']='Type a specific name for the report, If you need your own name';
		shn_form_text('Report Name', 'rep_name', 'size="50"',$extra_opts);
		echo '<br><br>';
	    print "<button onclick=\"submitFields()\" type=button>Create report</button>";
	}
// passing data with POST method
	$hidden_vars['table'] = "none";
	$hidden_vars['fields'] = "none";
	$hidden_vars['crt'] = "false";
	shn_form_hidden($hidden_vars);
	shn_form_fsclose();
	shn_form_fclose();
}





// creating condition for sql query
function _shn_dr_create_condition1($tables){
	$len = count($tables)-1;

	$cond = "";
	for($k = 0; $k<$len; $k++){
		$cond = $cond." ( dr_fields.table_name = '$tables[$k]' AND ( ";
		for	($i = 0; $i<$len; $i++)
			if($tables[$i] != $tables[$k])
				$cond = $cond." dr_fields.tab_for_key = '$tables[$i]' OR ";
		if($tables[$i] != $tables[$k])
			$cond = $cond." dr_fields.tab_for_key = '$tables[$i]'";
		$cond = $cond.")) OR ";
	}

	$cond = $cond." ( dr_fields.table_name = '$tables[$k]' AND ( ";
	for	($i = 0; $i<$len-1; $i++)
		$cond = $cond." dr_fields.tab_for_key = '$tables[$i]' OR ";
	$cond = $cond." dr_fields.tab_for_key = '$tables[$i]' ))";

	return $cond;
}



// creating condition for sql query
function _shn_dr_create_condition2($test){
	$cond = "";
	foreach($test as $key=>$name)
		$cond = $cond." OR ".str_replace(":", "=", $key).".".$name;
	$cond = ereg_replace("^ OR", "", $cond);

	return $cond;
}




function _shn_dr_create_form($table_name, $chosen_fields, $keys){
	$tables = _shn_dr_tables();

	$check = array();
	foreach($keys as $key){
		$tmp1 = split(":", $key);
		$tmp2 = split("\.", $tmp1[1]);
		$val = $tmp1[0].":".$tmp2[0];
		if(!array_key_exists($val, $check))
			$check[$val] = array();
		array_push($check[$val], $tmp2[1]);
	}


	foreach($check as $key=>$value){
		shn_form_fopen("dnd_multiple_table",null,array('enctype'=>'enctype="multipart/form-data"', 'id'=>'myForm'));
		if(count($check[$key]) > 1){
			$tmp = split(":", $key);
			$tab1 = split("\.", $tmp[0]);
			$fields[$tab1[0]] = _shn_dr_fields($tab1[0]);
			$fields[$tmp[1]] = _shn_dr_fields($tmp[1]);
	// 		print "<p> ".$key."</p>";
			print "<h3>Please choose to which field from table \"".$tables[$tmp[1]]."\" should be equal field \"".$fields[$tab1[0]][$tab1[1]]."\" from table \"".$tables[$tab1[0]]."\": </h3>";
	
	
			foreach($check[$key] as $sth)
				$options[$key.".".$sth] = $fields[$tmp[1]][$sth];
			shn_form_radio($options, null, "keys");
		}
	}
		$hidden_vars['table'] = $table_name;
		$hidden_vars['fields'] = $chosen_fields;
		$hidden_vars['crt'] = "true";
		shn_form_hidden($hidden_vars);
		shn_form_submit(_('Create report'));
		shn_form_fclose();

}



function _shn_dr_get_db_data($tab){
	global $global;
	// creating sql condition
	$cond = _shn_dr_create_condition1($tab);
	
	// 	getting data about relations between tables
	$sql = "SELECT tab_for_key, field_for_key, table_name, field_name FROM dr_fields WHERE (".$cond." )";
	
	$res = $global['db']->Execute($sql); 
		
	return $res;
}



// show table that user wanted to be shown
function _shn_dr_show_table($table_name, $chosen_fields, $keys_sub,$rep_name=null){
	global $global;
	$table_data_display=array();
	$tab = split(",", $table_name);
	//echo $table_name;
// 	getting user friendly names for all fields from chosen tables and for chosen tables
	$tables = _shn_dr_tables();
	foreach($tab as $key=>$name)
		$fields[$name] = _shn_dr_fields($name);

// 	if only one table has been chosen there is no need to check for foreign keys
	if((count($tab) == 1) || (!$keys_sub)){
		$res = _shn_dr_get_db_data($tab);

		$test = array();
		$keys = array();
		while(!$res->EOF ){
			$key =  $res->fields['tab_for_key'].".".$res->fields['field_for_key'].":".$res->fields['table_name'];
			array_push($keys, $key.".".$res->fields['field_name']);
			if(!array_key_exists($key, $test))
				$test[$key] = $res->fields['field_name'];

			$res->MoveNext();
		}
	}
	else if ($keys_sub){
		$tmp1 = split(":", $keys_sub);
		$tmp2 = split("\.", $tmp1[1]);

		$res = _shn_dr_get_db_data($tab);

		$test = array();
		$keys = array();
		while(!$res->EOF){
			$key =  $res->fields['tab_for_key'].".".$res->fields['field_for_key'].":".$res->fields['table_name'];

			if($key == $tmp1[0].":".$tmp2[0]){
				if(!in_array($key, $keys))
					array_push($keys, $key);
			}
			else
				array_push($keys, $key);

			if(!array_key_exists($key, $test))
				$test[$key] = $res->fields['field_name'];
			else
				$test[$key] = $tmp2[1];

			$res->MoveNext();
		}
	}


// if there are no double keys 
	if(count($test) == count($keys)){
// 		getting tables names from chosen_fields (only tables which has been chosen)
// 			fli - array of tables
// 			tab - string for sql query
		$con = " ";
		$fl = split(",", $chosen_fields);
		$fli = array();
		foreach($fl as $key){
			$temp = split("\.", $key);
			array_push($fli, $temp[1]);
			if(!ereg(" ".$temp[0].",", $con))
				$con = $con.$temp[0].",";
		}
		$con = ereg_replace(",$", "", $con);

	// 	getting data from chosen table
		if( count($tab) != 1 ){
			//var_dump($test);
			$cond = _shn_dr_create_condition2($test);
			$sql = "SELECT DISTINCT $chosen_fields FROM $table_name WHERE (".$cond." )";
		}
		else
			$sql = "SELECT DISTINCT $chosen_fields FROM $con ";

		$res = $global['db']->Execute($sql); 
	    if(NULL==$rep_name){
	    	$rep_name='Results for selecting data from several tables';
	    }
		// 	printing out result
		?>
				<h2><?php echo $rep_name?></h2>
				<div id="result">
				<table>
				<thead>
		<?php
			foreach($fl as $key=>$name){
				$var = split("\.", $name);
				print "<td><strong>".$fields[$var[0]][$var[1]]."</strong></td>";
				$table_header[$var[0].$var[1]]=$fields[$var[0]][$var[1]];
			}
		?>
				</thead>
				<tboby>
		<?php
				$len = count($fl);
				while(!$res->EOF){
					echo '<tr>';
					foreach($fli as $key=>$name){
						echo '<td>'.$res->fields[$name].'</td>';
						$table_data[$name]=$res->fields[$name];
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
		$nice_name=$rep_name;
		$rep_name=split(' ',$rep_name);
		//This is for generata nice file name    
        foreach($rep_name as $rn){
           $dis_name=$dis_name.'_'.$rn;	
        }
        
        //This is for generate pdf format of the report
		shn_report_fopen('pdf',$dis_name,$ims_report_keyword_arr,false,$table_name.'_pdf');
	    shn_report_add_title('Results from several tables');
        shn_report_add_table($table_header,$table_data_display);
	    shn_report_close(true);
	    //for ods format
	    shn_report_fopen('ods',$dis_name,$ims_report_keyword_arr,false,$table_name.'_ods');
	    shn_report_add_title('Results from several tables');
        shn_report_add_table($table_header,$table_data_display);
	    shn_report_close(true);
	    /*//for M$ excel format
	    shn_report_fopen('xls',$dis_name,$ims_report_keyword_arr,false,$table_name.'_xls');
	    shn_report_add_title('Results from several tables');
        shn_report_add_table($table_header,$table_data_display);
	    shn_report_close(true);*/
	    
	    //This is for export
        _shn_rs_export_init($sql,$dis_name,$nice_name);
        
	}// 	if for some tables have two keys:
	else
		_shn_dr_create_form($table_name, $chosen_fields, $keys);
}
