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

function shn_rs_search_main_form()
{
    $option_array=array('none' => '--- Select ---','file_name' => 'Report Name','report_chart_owner' => 'Report Owner','keyword' => 'Keyword', 'file_type' => 'File Type','all' =>'All Reports');
    shn_form_fopen('search_submit_one');
    shn_form_fsopen(_('Select Details'));
    shn_form_select($option_array,'Search By :','search_type',null);
    shn_form_text('','search_for','size="50"',$extra_opts);
    $extra_opts['value'] = 'exact';
    shn_form_checkbox("Do Exact Search ", 'exact_relative','',$extra_opts);
    shn_form_fsclose();
    shn_form_submit(_("Search"));
    shn_form_fclose();
}

function shn_rs_search_submit_one_result()
{
    global $global;
    $db=$global["db"];
    $search_type = trim($_POST['search_type']);
    $search_for = trim($_POST['search_for']);
    $exact_relative = $_POST['exact_relative'];

	if($exact_relative == 'exact' && $search_type != 'all')
	{
	$query = "select file_name , date_of_created ,time_of_created,report_chart_owner,file_type,file_size_kb,keyword,title from report_files where $search_type = '$search_for'";
	}
	elseif($search_type == 'all')
	{
	$query = "select file_name , date_of_created ,time_of_created,report_chart_owner,file_type,file_size_kb,keyword,title from report_files";
	}
	else
	{
	$first_3_letters=substr($search_for, 0, 3);
	$query = "select file_name , date_of_created ,time_of_created,report_chart_owner,file_type,file_size_kb,keyword,title from report_files where $search_type like '$first_3_letters%' ";
	}
	
    $res=$db->Execute($query);

?>
<br>
<div id="result">
<table>
    <thead>
        <td><strong><?=_("File Name")?></strong></td>
        <td><strong><?=_("Title")?></strong></td>
        <td><strong><?=_("Keyword")?></strong></td>
	<td><strong><?=_("Date of Created")?></strong></td>
	<td><strong><?=_("Time of Created")?></strong></td>
	<td><strong><?=_("Report Owner")?></strong></td>
	<td><strong><?=_("File Type")?></strong></td>
	<td><strong><?=_("File Size (kb) ")?></strong></td>
    </thead>
    <tbody>
<?php
    while(!$res==NULL && !$res->EOF)
    {
    $file_name =$res->fields["file_name"];
    $file_type = $res->fields["file_type"];
    $date_of_created = $res->fields["date_of_created"];
    $time_of_created = $res->fields["time_of_created"];
    $report_chart_owner = $res->fields["report_chart_owner"];
    $file_size_kb = $res->fields["file_size_kb"];
    $keyword = $res->fields["keyword"];
    $title = $res->fields["title"];
    ?>
    <tr>
        <td><?php print $file_name ;?></td>
        <td><?php print $title ;?></td>
	<td><?php print $keyword ;?></td>
	<td><?php print $date_of_created ;?></td>
	<td><?php print $time_of_created ;?></td>
	<td><?php print $report_chart_owner ;?></td>
	<td><?php print $file_type ;?></td>
	<td><?php print $file_size_kb ;?></td>
    </tr>
    <?php  

     $res->MoveNext();
	}


?>
    </tbody>    
</table>
</div>
<?php


}

?>