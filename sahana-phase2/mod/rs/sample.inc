<?php
/**
 * Sample Report
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/**
 * This is the sample report main form which is used to enter the report Details..
 * @access public
 * @return void
 */
function shn_rs_sample_report()
{
    print "<h1>"._t("Sample Reports Generation")."</h1>";
    ?>
    <p><?php echo  _t('Here you can generate reports based on sahana database or custom reports.'); ?></p> 
    <?php
    $extra_opts['req']=true;
    shn_form_fopen('sample_submit_one','',array('req_message' => true,'enctype'=>'enctype="multipart/form-data"','name'=>'sample_rep_form'));
    shn_form_fsopen(_t('Report Details'));
    shn_form_text(_t("Report File Name   : "),'rep_file_name','size="50"',$extra_opts);
    shn_form_text(_t("Report Title   : "),'rep_title','size="50"','');
    shn_form_textarea(_t("Content :"),'rep_summary' , '', '');
    shn_form_upload(_t("Image :"), 'image', '');
    shn_form_fsclose();
    shn_form_fsopen(_t('Meta Data'));
    shn_form_text(_t("Keyword / Keywords :"),'keyword','size="50"', array('help'=>_t('Here you can enter keywords for your report which will help you to search the report later. If you have more than one keyword enter them in the text box by separating coma.')));
    shn_form_textarea(_t("Description :"),'description' , '', '');
    shn_form_fsclose();

    shn_form_fsopen(_t('Report Type'));
    $option_array=array('none' => '-----Select -----','mod' => 'Module','custom' => 'Custom');
    shn_form_select($option_array,'','report_type','',$extra_opts);
    shn_form_fsclose();

    shn_form_fsopen(_t('Report File Format'));
    $option_array=array('none' => '-----Select -----','ods' => 'SpreadSheet','pdf' => 'PDF','xhtml'=>'XHTML');
    shn_form_select($option_array,'','file_type','',$extra_opts);
    shn_form_fsclose();

    $extra_opts['br']=false;
    $extra_opts['req']=false;
    
    shn_form_button(_t("Create Report"),"onClick='change_action(\"create_rep\")'",$extra_opts);
    shn_form_button(_t("Continue to add more content"),"onClick='change_action(\"continue\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));

    shn_form_fclose();

    shn_sample_change_action_js();
}

/**
 * This function processes the POST values that are passed from the shn_rs_sample_report() in sample.inc
 * @access public
 * @return void
 */
function shn_rs_sample_submit_one_result()
{
    global $global;
    $img_upload_ok = false;

    $rep_file_name =  trim($_POST['rep_file_name']);
    $report_title = trim($_POST['rep_title']);
    $report_summary = trim($_POST['rep_summary']);
    $keyword = trim($_POST['keyword']);
    $selected_report_type = trim($_POST['report_type']);
    $selected_file_type = trim($_POST['file_type']);

    $upload_dir = $global['approot'].'www/tmp/Pictures/';
    $upload_dir = $upload_dir.basename( $_FILES['image']['name']);
	if(move_uploaded_file($_FILES['image']['tmp_name'], $upload_dir)) 
	{
	chmod($upload_dir, 0777);
	$img_upload_ok = true;
	$img_name = basename( $_FILES['image']['name']);
	} 
	else
	{
	$img_upload_ok = false;
	}

    $report_data_arr = array('file_name' => $rep_file_name , 'title' => $report_title , 'summary' => $report_summary, 'meta' => $keyword , 'report_type' => $selected_report_type , 'file_type' => $selected_file_type,'img_name' => $img_name);

	session_start();
	$_SESSION['report_data'] = $report_data_arr;
	$action=trim($_POST['action']);

	if(($selected_report_type == 'custom' && $action == 'create_rep'))
	{
	_shn_rs_report_creator();
	}
	elseif(($selected_report_type == 'custom' && $action == 'continue'))
	{
	_show_custom_report_form();
	}
	else
	{
	_show_mod_select_form();
	}
}

/**
 * This function displays the module selection form.
 * @access public
 * @return void
 */
function _show_mod_select_form()
{
    $option_array=array('none' => '-----Select -----','cs' => 'Catalogue System');
    $form_opts['name']="mod_select";
    shn_form_fopen('sample_submit_two',null,$form_opts);
    shn_form_fsopen(_t('Select Module'));
    $select_opts='onChange="changeform()"';
    shn_form_select($option_array,'','mod_name',$select_opts,null);
    shn_form_fsclose();
    shn_form_fclose();
    shn_sample_change_form_js();
}

/**
 * This function displays the custom report form.
 * @access public
 * @return void
 */
function _show_custom_report_form()
{
    print "<h1>"._t("Add More content to the Custom Report")."</h1>";
    shn_form_fopen('sample_submit_four',null,'');
    shn_form_fsopen(_t('Report Content'));
    shn_form_textarea("",'content' , '', '');
    shn_form_fsclose();
    shn_form_submit(_t("Create Report"));
    shn_form_fclose();
}

/**
 * This function shows the form to search data from the catalogue system module tables
 * @access public
 * @return void
 */
function shn_rs_sample_submit_two_result()
{
    print "<b>"._t("Search data from Database and include them in the Report")."</b>";
    $option_array=array('none' => '-----Select -----','item' => 'Item/Catalogue','unit' => 'Unit','unit_types'=>'Unit Types');
    shn_form_fopen('sample_submit_three',null,'');
    shn_form_fsopen(_t('Select Table'));
    shn_form_select($option_array,'','tab_name','',null);
    shn_form_fsclose();
    shn_form_fsopen(_t('Search'));
    shn_form_text('','keyword','size="50"', array('help'=>_t('')));
    $extra_opts['value'] = 'exact';
    shn_form_checkbox(_t("Do Exact Search "), 'exact_relative','',$extra_opts);
    shn_form_fsclose();
    shn_form_submit(_t("Search"));
    shn_form_fclose();
}

function shn_rs_sample_submit_three_result()
{
    $tab_name =  trim($_POST['tab_name']);
    $keyword =  trim($_POST['keyword']);
    $exact_relative = $_POST['exact_relative'];

    if($tab_name == 'item')
    {
	_show_item_table($keyword,$exact_relative);
    }

    elseif($tab_name == 'unit')
    {
	_show_unit_table($keyword,$exact_relative);
    }

    elseif($tab_name == 'unit_types')
    {
	_show_unit_type_table($keyword,$exact_relative);
     }
}

/**
 * This function shows the Item table.
 * @access private
 * @return void
 */
function _show_item_table($keyword_in = '',$exact_in = true)
{
    global $global;
    $db=$global["db"];

    shn_form_fopen('sample_submit_four',null,'');

    ?>
    <br>
    <div id="result">
    <table>
    <thead>
        <td><strong><?php echo _t("Name")?></strong></td>
        <td><strong><?php echo _t("Description")?></strong></td>
	<td><strong><?php echo _t("Keyword")?></strong></td>
    </thead>
    <tbody>
    <?php

    if($exact_in)
    {
    $query="SELECT * FROM ct_catalogue WHERE name = '$keyword_in' ";
    }
    else
    {
    $first_letters=substr($keyword_in, 0, 1);
    $query= "SELECT * FROM ct_catalogue WHERE name LIKE '$first_letters%' " ;
    }

    $res=$db->Execute($query);
    $data_arr = array();
    $row_coount = 0;
    while(!$res==NULL && !$res->EOF)
    {
    $table_row = "row".$row_coount++;
    $table_row = array();

    $name=$res->fields["name"];
    $description=$res->fields["description"];
    $keyword=$res->fields["keyword"];
    ?>
    <tr>
        <td><?php print $name ;?></td>
        <td><?php print $description ;?></td>
        <td><?php print $keyword ;?></td>
    </tr>
    <?php 

    $table_row ["name"]= $res->fields["name"];
    $table_row ["description"]= $res->fields["description"];
    $table_row ["keyword"]= $res->fields["keyword"];
    array_push($data_arr, $table_row);
    $res->MoveNext();
    }
	$table_headers = array('name' => 'Name' , 'description' => 'Description' , 'keyword' => 'Keyword');
	$_SESSION['table_headers'] = $table_headers; 
	$_SESSION['table_data'] = $data_arr;
	?>
    </tbody>
    </table>
    </div>
    <?php
    shn_form_submit(_t("Add Table & Create Report"));
    shn_form_fclose();
}

/**
 * This function shows the Unit table.
 * @access private
 * @return void
 */
function _show_unit_table($keyword_in = '',$exact_in = true)
{
    global $global;
    $db=$global["db"];
    shn_form_fopen('sample_submit_four',null,'');
    ?>
    <br>
    <div id="result">
    <table>
    <thead>
    <td><strong><?php echo _t("Name")?></strong></td>
    <td><strong><?php echo _t("Multiplier")?></strong></td>
    </thead>
    <tbody>
    <?php
    if($exact_in)
    {
    $query="SELECT * FROM ct_unit WHERE name = '$keyword_in' ";
    }
    else
    {
    $first_letters=substr($keyword_in, 0, 1);
    $query="SELECT * FROM ct_unit WHERE name like '$first_letters%' ";
    } 
    $res=$db->Execute($query);
    $data_arr = array();
    $row_coount = 0;
    while(!$res==NULL && !$res->EOF)
    {
    $table_row = "row".$row_coount++;
    $table_row = array();
    $name=$res->fields["name"];
    $multiplier=$res->fields["multiplier"];
    ?>
    <tr>
    <td><?php print $name ;?></td>
    <td><?php print $multiplier ;?></td>
    </tr>
    <?php  

    $table_row ["name"]= $res->fields["name"];
    $table_row ["multiplier"]= $res->fields["multiplier"];
    array_push($data_arr, $table_row);
    $res->MoveNext();
    }//end of while loop

    $table_headers = array('name' => 'Name' , 'multiplier' => 'Multiplier');
    $_SESSION['table_headers'] = $table_headers; 
    $_SESSION['table_data'] = $data_arr;
    ?>
    </tbody>
    </table>
    </div>
    <?php
    shn_form_submit(_t("Add Table & Create Report"));
    shn_form_fclose();
}

/**
 * This function shows the Unit Type table.
 * @access private
 * @return void
 */
function _show_unit_type_table($keyword_in = '',$exact_in = true)
{
    global $global;
    $db=$global["db"];
    shn_form_fopen('sample_submit_four',null,'');
    ?>
    <br>
    <div id="result">
    <table>
    <thead>
    <td><strong><?php echo _t("Name")?></strong></td>
    <td><strong><?php echo _t("Description")?></strong></td>
    </thead>
    <tbody>
    <?php
    if($exact_in)
    {
    $query="SELECT * FROM ct_unit_type WHERE name = '$keyword_in' ";
    }
    else
    {
    $first_letters=substr($keyword_in, 0, 2);
    $query="SELECT * FROM ct_unit_type WHERE name LIKE '$first_letters%' ";
    } 
    $res=$db->Execute($query);
    $data_arr = array();
    $row_coount = 0;
    while(!$res==NULL && !$res->EOF)
    {
    $table_row = "row".$row_coount++;
    $table_row = array();
    $name=$res->fields["name"];
    $description=$res->fields["description"];
    ?>
    <tr>
    <td><?php print $name ;?></td>
    <td><?php print $description ;?></td>
    </tr>
    <?php
    $table_row ["name"]= $res->fields["name"];
    $table_row ["description"]= $res->fields["description"];
    array_push($data_arr, $table_row);
    $res->MoveNext();
    }//end of while loop
    $table_headers = array('name' => 'Name' , 'description' => 'Description');
    $_SESSION['table_headers'] = $table_headers; 
    $_SESSION['table_data'] = $data_arr;
    ?>
    </tbody>
    </table>
    </div>
    <?php
    shn_form_submit(_t("Add Table & Create Report"));
    shn_form_fclose();
}

/**
 * This function creates reports.
 * @access public
 * @return void
 */
function _shn_rs_report_creator()
{
    $report_data_array = $_SESSION['report_data'];
    $table_headers = $_SESSION['table_headers'];
    $table_data = $_SESSION['table_data'];
    $content =  trim($_POST['content']);
    $keyword_arr = explode(",", $report_data_array['meta']);

    if($report_data_array['file_type'] == 'ods')
    {
    shn_ods_report_fopen($report_data_array['file_name'],$keyword_arr);
    shn_ods_report_add_sheet('sheet1');
    shn_ods_report_add_title($report_data_array['title']);
    shn_ods_report_add_summery($report_data_array['summary']);
        if($content != null)
	{
	shn_ods_report_add_summery($content);
	}
	if($table_headers != null && $table_data != null)
	{
	shn_ods_report_add_table($table_headers,$table_data);
	}
	if($report_data_array['img_name'] != null)
	{
	shn_ods_report_add_image($report_data_array['img_name']);
	}
	shn_ods_report_close();
    }
    elseif($report_data_array['file_type'] == 'pdf')
    {
    shn_pdf_report_fopen($report_data_array['file_name'],$keyword_arr);
    shn_pdf_report_add_title($report_data_array['title']);
    shn_pdf_report_add_summery($report_data_array['summary']);
	if($content != null)
	{
	shn_pdf_report_add_summery($content);
	}
	if($table_headers != null && $table_data != null)
	{
	shn_pdf_report_add_table($table_headers,$table_data);
	}
	if($report_data_array['img_name'] != null)
	{
	shn_pdf_report_add_image($report_data_array['img_name']);
	}
	shn_pdf_report_close();
    }
    else
    {
    shn_xhtml_report_fopen($report_data_array['file_name'],$keyword_arr);
    shn_xhtml_report_add_title($report_data_array['title']);
    shn_xhtml_report_add_summary($report_data_array['summary']);
	if($content != null)
	{
	shn_xhtml_report_add_summary($content);
	}
	if($table_headers != null && $table_data != null)
	{
	shn_xhtml_report_add_table($table_headers,$table_data);
	}
	if($report_data_array['img_name'] != null)
	{
	shn_xhtml_report_add_image($report_data_array['img_name']);
	}
	shn_xhtml_report_close();
    }
}
