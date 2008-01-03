<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    framework
* @subpackage localization
* @tutorial   localization.pkg
* @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

//global $global;
//
//$list = $global['db']->MetaTables();
//print_r($list);

function __show_basic_form()
{
    shn_form_fopen("lc_db",null,array('req_message'=>false));

    shn_form_hidden(array('seq'=>'add_entry'));

    shn_form_text(_("Table / Field Names"),'table',null,array('br'=>false));
    shn_form_text("",'field',null,array('br'=>false));

    shn_form_submit(_("Add Entry"));
    shn_form_fclose();
}

function __add_entry($table, $field)
{
	global $global;

    $sql = "SELECT * FROM lc_fields " .
            "WHERE tablename = '$table' " .
            "AND fieldname = '$field'";

    $rs = $global['db']->Execute($sql);

    if(trim($table)=='') {
    	add_error(_("The Table name cannot be blank, please enter a valid Table name"));
	$error = true;
    }

    if(trim($field)=='') {
		add_error(_("The Field name cannot be blank, please enter a valid Field name"));
		$error = true;
    }
    
    // check for table availability
    $tables = $global['db']->MetaTables("TABLES");
    $table_error = false;
    if(array_search($table,$tables)===FALSE){
    	add_error(_("The is no table named ").$table);
    	$table_error = true;
    	$error = true;
    }
    
    // check for field availability
    if(!$table_error){
    	$fields = $global['db']->MetaColumnNames($table,true);
    	if(array_search($field,$fields)===FALSE){
    		add_error(_("There is no field named ").$field._(" in the table ").$table);
    		$error = true;	
    	}
    }    

    if($error) {
        display_errors();
    }elseif(1 > $rs->RecordCount()) {
        $sql = "INSERT INTO lc_fields (tablename, fieldname) " .
                "VALUES('$table','$field')";
        $global['db']->Execute($sql);

        add_confirmation(_("Database localization entry added successfully!"));
    }else {
        add_error( _("The database localization entry already exists"));
    }
}


function __show_entries()
{
    global $global;
    $rec_count = 0;
    $sql = "SELECT * FROM lc_fields";

    $rs = $global['db']->Execute($sql);

?>
	<div id ="result">
    <table>
    <thead>
    	<td><?php print _("ID") ?></td>
    	<td width="150"><?php print _("Table Name") ?></td>
    	<td width=""><?php print _("Field Name") ?></td>
    	<td width="">&nbsp;</td>
   	</thead>
	<tbody>
<?php
	foreach($rs as $r) {
		$rec_count++;
		$url = "index.php?mod=admin&amp;act=lc_db&amp;seq=del&amp;id=" . $r[0];
?>
		<tr>
        <td><?php print  $r[0] ?></td>
        <td><?php print  $r[1] ?></td>
        <td><?php print  $r[2] ?></td>
        <td><a href="<?php print $url?>"><?php echo _("Remove") ?></a></td>
    	</tr>
<?php
	}

	if(1 > $rec_count) {
?>
    	<tr>
        <td colspan="4"><?php echo _("There are no DB L10N entries at the moment") ?></td>
    	</tr>
<?php
	}
?>
    </table>
</div>
<?php
}



function __del_entry($id)
{
    global $global;

    $sql = "DELETE FROM lc_fields WHERE id = '$id'";

    if($global['db']->Execute($sql)) {
        add_confirmation(_("DB L10N entry removed successfully"));
    }else {
        add_confirmation(_("Error occurred while removing DB L10N entry"));
    }
}

switch($_REQUEST['seq']) {

    case '' : 
    	__show_basic_form();
		__show_entries();
        break;

    case 'add_entry':
		$table = $_POST['table'];
		$field = $_POST['field'];
		__add_entry($table, $field);
		__show_basic_form();
		__show_entries();
		break;
		
    case 'del':
    	$id = $_GET['id'];
		__del_entry($id);
		__show_basic_form();
		__show_entries();
		break;
}
?>
