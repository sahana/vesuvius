<?php
/**
 * Report Search
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
 * This is the search type selection form
 * @access public
 * @return void
 */
function shn_rs_search_type_select()
{
    print "<h1>"._t("Search")."</h1>";
    ?>
    <p><?php echo  _t('Here you can search for reports and charts. Select the category that you need to search for.'); ?></p> 
    <?php

    $form_opts['id']="rep_search";
    $search_type_array=array('none'=>'---select---','report'=>'Report','chart'=>'Chart');
    shn_form_fopen('search',null,$form_opts);
    shn_form_fsopen(_t('Select the Search category'));
    $select_opts='onChange="changeform()"';
    shn_form_select($search_type_array,_t('Search By :'),'search_rep_chart',$select_opts,null);
    shn_form_fsclose();
    shn_form_fclose();
    print "<br>";
    shn_rs_search_cat_js();
}

/**
 * This is the search form
 * @access public
 * @return void
 */
function shn_rs_search_main_form()
{
    $search_rep_chart = trim($_POST['search_rep_chart']);
    shn_form_fopen('search_submit_one',null,'');
    shn_form_fsopen(_t('Select Details'));

    if($search_rep_chart == 'report')
     {
     $option_array=array('none' => '--- Select ---','file_name' => 'File Name','rep_id'=>'Report ID','file_type' => 'File Type','file_size_kb'=>'File Size','title'=>'Report Title','all' =>'All Reports');
     }
    elseif($search_rep_chart == 'chart')
     {
    $option_array=array('none' => '--- Select ---','file_name' => 'Chart Name','rep_id'=>'Chart ID','file_size_kb'=>'File Size','all' =>'All Charts');
     }
    else
     {
    $option_array=array('none' => '--- Select Category First---');
     }

    shn_form_select($option_array,'Search By :','search_type');
    shn_form_text('Phrase : ','search_for','size="50"');
    $extra_opts['value'] = 'exact';
    shn_form_checkbox("Do Exact Search :", 'exact_relative','',$extra_opts);
    shn_form_fsclose();
    print "<b>OR</b>"._t("Do a keyword search")."<br><br>";
    shn_form_fsopen(_t('Keyword Search'));
    shn_form_text('Keyword : ','keyword','size="50"');
    shn_form_fsclose();
    shn_form_hidden(array('search_cat' => $search_rep_chart));
    shn_form_submit(_t("Search"));
    shn_form_fclose();
}

/**
 * This is the search submit result table.
 * @access public
 * @return void
 */
function shn_rs_search_submit_one_result()
{
    global $global;
    $db=$global["db"];
    $search_type = trim($_POST['search_type']);
    $search_for = trim($_POST['search_for']);
    $keyword =  trim($_POST['keyword']);
    $search_cat =  trim($_POST['search_cat']);
    $exact_relative = $_POST['exact_relative'];

    if($keyword !='')
    {
	switch($search_cat)
	{
	case 'report':
	$keyword_query = "SELECT report_files.rep_id,report_files.file_name,report_files.t_stamp,report_files.file_type,report_files.file_size_kb,report_files.title FROM report_files,report_keywords WHERE report_keywords.rep_id = report_files.rep_id AND report_keywords.keyword = '$keyword' and report_files.file_type != 'png' ";
	break;
	case 'chart':
	$keyword_query = "SELECT report_files.rep_id,report_files.file_name,report_files.t_stamp,report_files.file_type,report_files.file_size_kb,report_files.title FROM report_files,report_keywords WHERE report_keywords.rep_id = report_files.rep_id and report_keywords.keyword = '$keyword' and report_files.file_type = 'png'";
	break;
	}
	$keyword_result=$db->Execute($keyword_query);
	_printTable($keyword_result);
	}
    else
    {
	if($exact_relative == 'exact' && $search_type != 'all' && $search_cat == 'report')
	{
	$query = "SELECT rep_id,file_name,t_stamp,file_type,file_size_kb,title FROM report_files WHERE $search_type = '$search_for' and file_type != 'png' ";
	$res=$db->Execute($query);
	_printTable($res);
	}
	elseif($exact_relative == 'exact' && $search_type != 'all' && $search_cat == 'chart')
	{
	$query = "SELECT rep_id,file_name,t_stamp,file_type,file_size_kb,title FROM report_files WHERE $search_type = '$search_for' and file_type = 'png' ";
	$res=$db->Execute($query);
	_printTable($res);		
	}
	elseif($exact_relative != 'exact' && $search_type != 'all' && $search_cat == 'report')
	{
	$first_3_letters=substr($search_for, 0, 3);
	$query = "SELECT rep_id,file_name,t_stamp,file_type,file_size_kb,title FROM report_files WHERE $search_type like '$first_3_letters%' and file_type != 'png' ";
	$res=$db->Execute($query);
	_printTable($res);
	}
	elseif($exact_relative != 'exact' && $search_type != 'all' && $search_cat == 'chart')
	{
	$first_3_letters=substr($search_for, 0, 3);
	$query = "SELECT rep_id,file_name,t_stamp,file_type,file_size_kb,title FROM report_files WHERE $search_type like '$first_3_letters%' and file_type = 'png' ";
	$res=$db->Execute($query);
	_printTable($res);
	}
	elseif($search_type == 'all' && $search_cat == 'report')
	{
	$query = "SELECT rep_id,file_name,t_stamp,file_type,file_size_kb,title FROM report_files WHERE file_type != 'png'";
	$res=$db->Execute($query);
	_printTable($res);
	}
	elseif($search_type == 'all' && $search_cat == 'chart')
	{
	$query = "SELECT rep_id,file_name,t_stamp,file_type,file_size_kb,title FROM report_files WHERE file_type = 'png'";
	$res=$db->Execute($query);
	_printTable($res);
	}
	else
	{
	$query = "SELECT rep_id,file_name,t_stamp,file_type,file_size_kb,title FROM report_files";
	$res=$db->Execute($query);
	_printTable($res);
	}
    }
}

/**
 * This is the search submit result table content.
 * @access public
 * @return void
 */
function _printTable($res)
{
    ?>
    <br>
    <div id="result">
    <table>
    <thead>
    <td><strong><?php echo _t("Report ID")?></strong></td>
    <td><strong><?php echo _t("File Name")?></strong></td>
    <td><strong><?php echo _t("Title")?></strong></td>
    <td><strong><?php echo _t("Date/Time")?></strong></td>
    <td><strong><?php echo _t("File Type")?></strong></td>
    <td><strong><?php echo _t("File Size (kb) ")?></strong></td>
    </thead>
    <tbody>
    <?php
    $record_counter = 0;
    while(!$res==NULL && !$res->EOF)
    {
    $rep_id =$res->fields["rep_id"];
    $file_name =$res->fields["file_name"];
    $file_type = $res->fields["file_type"];
    $date_time= $res->fields["t_stamp"];
    $file_size_kb = $res->fields["file_size_kb"];
    $title = $res->fields["title"];
    ?>
    <tr>
    <td><?php print $rep_id ;?></td>
    <td><?php shn_report_download($rep_id,$file_name); ?></td>
    <td><?php print $title ;?></td>
    <td><center><?php print $date_time ;?></center></td>
    <td><?php print $file_type ;?></td>
    <td><?php print $file_size_kb ;?></td>
    </tr>
    <?php
    $res->MoveNext();
    $record_counter++;
    }
    ?>
    </tbody>    
    </table>
    </div>
    <?php
    print "<b>".$record_counter._t(" reports found")."</b>";
}
