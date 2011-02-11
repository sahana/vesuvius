<?php
/**
 *
 * This is the Sahana paging library
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @author     Ishan Liyanage <ishanul@gmail.com>
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

//require_once("lib_export.inc");
/**
 * The main paging function
 *
 * @param string $query
 * @param integer $rpp
 * @param array $headers
 * @param mixed $extra_opts
 * @access public
 * @return void
 */

function shn_paging_get_report($query,$rpp=20,$headers=NULL,$extra_opt)
{
	global $global;
	if(isset($_REQUEST['rpp'])){
		if('none'!=$_REQUEST['rpp'])
		{
			$rpp=$_REQUEST['rpp'];
		}

	}
	$global["paging_rpp"]=$rpp;
	$res=_shn_page_get_rs($query,$rpp);
	if(!$res)return false;
	$url = null;
	if(isset($extra_opt['paging_url'])){
		$url = $extra_opt['paging_url'];
	}else{
		$url=_shn_paging_url();
		if(isset($extra_opt['post'])&&$extra_opt['post']==true){
			_shn_page_draw_navi_post($res,$url);
		}
		else{
			_shn_page_draw_navi($res,$url,$rpp);
		}

		if(!isset($headers)||$extra_opt['return']==true)
		return $res;
		//shn_export($query,$headers);
		_shn_page_draw_table($res,$headers);
		return 0;
	}
}

function _shn_page_get_rs($query,$rpp){
	global $global;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];
	}
	else
	$page=1;

	//if the page is next or Previous
	if('Next'==$page){
		$page=$_REQUEST['c_page']+1;
	}
	if('Previous'==$page){
		$page=$_REQUEST['c_page']-1;
	}

	define('ADODB_FETCH_ASSOC',2);
	define('ADODB_FETCH_BOTH',3);
	$fetchmode=$global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
	if('all'==$rpp){
		$res=$global['db']->Execute($query);
	}else{
		$res=$global['db']->PageExecute($query, $rpp, $page);
	}

	//revert the fetch mode
	$global['db']->SetFetchMode($fetchmode);

	if (!$res){add_error($global['db']->ErrorMsg());}
	return $res;
}

//navigation with links
function _shn_page_draw_navi(&$res,$url,$rpp){
	_shn_paging_set_rpp();
	global $global;
	if(isset($_REQUEST['page']))
	$page=$_REQUEST['page'];
	else
	$page=1;

	//calculate start and end
	$global["page_no"]=$page;
	$start=$page-5;
	$end=$page+5;
	$last=$res->LastPageNo();

	if($start<1){
		$end=$end-$start+1;
		$start=1;
	}
	if($end>$last){
		$start=$start-($end-$last);
		$end=$last;
		if($start<1){
			$start=1;
		}
	}

	//if no records are found print No results
	if($res->RecordCount()==0){
		add_information(_t("No Records found "));
		//echo "<strong>"._t("No Records found ")."</strong>";
		return;
	}
	//if there is only one page don't print the navigation links
	//if($last==1)
	//return;
	//to add dynamic records per page
	?>
<div>
<form name='paging_form' class='paging_form' action='<?php echo $url?>'
	method='POST'><?php

	//shn_form_hidden(array('rpp'=>''));

	//print the amount of pages
	echo _t("Page "). "$page/$last" . " : ";

	//draw the First and prev links
	if($page!=1)
	{
		?> <b><a
	href="<?php echo $url?>&amp;page=<?php echo $page-1;?>&amp;rpp=<?php echo $rpp;?>"
	title="<?php echo _t('Go to Previous Page')?>"><?php echo _t('Previous')?></a></b>
<b><a href="<?php echo $url?>&amp;page=1&amp;rpp=<?php echo $rpp;?>"
	title="<?php echo _t('Go to First Page')?>"><?php echo _t('1')?></a></b>

		<?php
	}

	//draw the page links
	if($start>1)
	echo "&#8230;";
	for($i=$start;$i<=$end;$i++)
	{
		if($i==$page)
		echo "<span class='red'>".$i."</span>";
		elseif($i==$start||$i==$end)
		continue;
		else
		{
			?> <a
	href="<?php echo $url?>&amp;page=<?php echo $i?>&amp;rpp=<?php echo $rpp;?>"
	title="<?php echo _t('Go to Page No ').$i?>"><?php echo $i?></a> <?php
		}
	}
	if($end<$last)
	echo "&#8230;";

	//draw the next and the last link
	if($page!=$last)
	{
		?> <b><a
	href="<?php echo $url?>&amp;page=<?php echo $last ?>&amp;rpp=<?php echo $rpp;?>"
	title="<?php echo _t('Go to Last Page')?>"><?php echo $last?></a></b> <b><a
	href="<?php echo $url?>&amp;page=<?php echo $page+1?>&amp;rpp=<?php echo $rpp;?>"
	title="<?php echo _t('Go to Next Page')?>"><?php echo _t('Next')?></a></b>

		<?php
	}

	$options=array('none'=>'Default','1000000'=>'All','10'=>'10','20'=>'20','30'=>'30','40'=>'40','50'=>'50','100'=>'100');
	?> &nbsp;&nbsp; <?php
	shn_form_select($options,_t("Records per page"), "rpp","onchange='set_rpp(this.value);'", $extra_opts = null);
	?>

</div>
	<?php
}


//navigation with posts
function _shn_page_draw_navi_post(&$res,$url){
	_shn_paging_set_rpp();
	global $global;
	if(isset($_REQUEST['page']))
	$page=$_REQUEST['page'];
	else
	$page=1;

	//if the page is next or Previous
	if('Next'==$page){
		$page=$_REQUEST['c_page']+1;
	}
	if('Previous'==$page){
		$page=$_REQUEST['c_page']-1;
	}

	//calculate start and end
	$global["page_no"]=$page;
	$start=$page-5;
	$end=$page+5;
	$last=$res->LastPageNo();

	if($start<1){
		$end=$end-$start+1;
		$start=1;
	}
	if($end>$last){
		$start=$start-($end-$last);
		$end=$last;
		if($start<1){
			$start=1;
		}
	}

	//if no records are found print No results
	if($res->RecordCount()==0){
		add_information(_t("No Records found "));
		//echo "<strong>"._t("No Records found ")."</strong>";
		return;
	}
	//if there is only one page don't print the navigation links
	//if($last==1)
	//  return;

	?>
<form name='paging_form' class='paging_form' action='<?php echo $url?>'
	method='POST'><?php
	foreach($_POST as $name=>$post){
		//if a post values came in and array create a hidden array.
		if(is_array($post)){
			foreach($post as $val){
				shn_form_hidden(array($name.'[]'=>$val));
			}
			continue;
		}
		if('c_page'!=$name && 'page'!=$name){
			shn_form_hidden(array($name=>$post));
		}
	}

	//$options=array('none'=>'default','all'=>'All','10'=>'10','20'=>'20','30'=>'30','40'=>'40','50'=>'50','100'=>'100');
	$options=array('none'=>'Default','1000000'=>'All','10'=>'10','20'=>'20','30'=>'30','40'=>'40','50'=>'50','100'=>'100');
	?>
<div><?php 
//shn_form_hidden(array('rpp'=>''));

//print the amount of pages
echo _t("Page "). "$page/$last" . " : ";

//draw the First and prev links
if($page!=1)
{
	shn_form_submit(_t('Previous'),"id ='page' name='page'");
	shn_form_submit('1',"id ='page' name='page'");

}

//draw the page links
if($start>1)
echo "&#8230;";
for($i=$start;$i<=($end);$i++)
{
	if($i==$page)
	echo "<span class='red'>".$i."</span>";
	elseif($i==$start||$i==$end)
	continue;
	else
	shn_form_submit($i,"id ='page' name='page'");
}
if($end<$last)
echo "&#8230;";


//draw the next and the last link
if($page!=$last)
{
	shn_form_submit($last,"id ='page' name='page'");
	shn_form_submit(_t('Next'),"id ='page' name='page'");
}
?> &nbsp;&nbsp; <?php
shn_form_select($options,_t("Records per page"), "rpp","onchange='set_rpp(this.value);'", $extra_opts = null);

?> <input type="hidden" id="c_page" name="c_page"
	value=<?php echo $page?> /></div>
</form>
<?php
}


function _shn_page_draw_table(&$res,&$headers){
	?>
<div id='result'>
<table>
<?php
if(isset($headers))
_shn_page_table_header($headers);

_shn_page_table_body($res);
?>
</table>
</div>
<?php
}



function _shn_page_table_body(&$res){
	foreach($res as $record){
		?>
<tr>
<?php
foreach($record as $field){
	?>
	<td><?php echo $field?></td>
	<?php
}
?>
</tr>
<?php
	}
}


function _shn_page_table_header($headers)
{
	?>
<thead>
<?php
foreach($headers as $heads)
{
	?>
	<td><?php echo $heads;?></td>
	<?php
}
?>
</thead>
<?php
}


//this function generate the url used for navigation links and the forms
function _shn_paging_url(){
	global $global;
	$url="index.php?mod={$global['module']}&amp;act={$global['action']}";
	unset($_GET['act']);
	unset($_GET['mod']);
	unset($_GET['page']);
	foreach($_GET as $key=>$val){
		$url.="&amp;{$key}={$val}";
	}
	return $url;
}

function get_record_no(){
	global $global;
	static $no;
	if(!isset($no)){
		$no=$global["paging_rpp"]*(intval($global["page_no"])-1);
		$no++;
	}
	return $no++;
}
function _shn_paging_set_rpp(){
	?>
<script language="JavaScript" type="text/javascript">
function set_rpp(rpp_val){
	//alert(rpp_val);
	//document.getElementById('page').value="1";
	document.getElementById('rpp').value=rpp_val;
	document.paging_form.submit();
}
</script>
	<?php
}
