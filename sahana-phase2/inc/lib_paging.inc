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



/**
 * @param mixed
 * @access public
 * @return void
 */
function shn_paging_get_report($query,$rpp=20,$headers=NULL,$action=null,$returnflag=false)
{
    global $global;
    //$db = $global['db'];
    //$results = $db->Execute($query);
    //$number=$results->RecordCount();

    $res=_shn_page_get_rs($query,$rpp);
    if(!$res)return false;

    _shn_page_draw_navi($res);
    if($returnflag)
        return $res;

    _shn_page_draw_table($res,$headers);
    return 0;
}

function _shn_page_get_rs($query,$rpp){
    global $global;
    if(isset($_GET['page']))
        $page=$_GET['page'];
    else
        $page=1;

    define('ADODB_FETCH_ASSOC',2);
    $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
    $res=$global['db']->PageExecute($query, $rpp, $page);
    if (!$res){add_error($global['db']->ErrorMsg());}
    return $res;
}

function _shn_page_draw_navi(&$res){
    global $global;
    if(isset($_GET['page']))
        $page=$_GET['page'];
    else
        $page=1;

    //calculate start and end
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
        echo "<strong>"._("No Search Results ")."</strong>";
        return;
    }
    //if there is only one page don't print the navigation links
    if($last==1)
        return;

    //print the amount of pages
    echo "Page $page/$last : ";

    //draw the First and prev links
    if($page!=1)
    {
?>
    <b><a href="index.php?mod=<?php echo $global['module'];?>&amp;act=<?php echo $global['action']?>&amp;page=1"><?php echo _('First')?></a></b> 
    <b><a href="index.php?mod=<?php echo $global['module'];?>&amp;act=<?php echo $global['action']?>&amp;page=<?php echo $page-1;?>"><?php echo _('Previous')?></a></b> 
<?php
    }

    //draw the page links
    if($start>1){
?>
        <a href="index.php?mod=<?php echo $global['module'];?>&amp;act=<?php echo $global['action']?>&amp;page=<?php echo $i-1?>">&#8230;</a>
<?php
    }
    for($i=$start;$i<=$end;$i++)
    {
        if($i==$page)
        {
            echo "<span class='red'>".$i."</span>";
        }
        else
        {
?>
        <a href="index.php?mod=<?php echo $global['module'];?>&amp;act=<?php echo $global['action']?>&amp;page=<?php echo $i?>"><?php echo $i?></a> 
<?php
        }
    }
    if($end<$last){
?>
        <a href="index.php?mod=<?php echo $global['module'];?>&amp;act=<?php echo $global['action']?>&amp;page=<?php echo $i+1?>">&#8230;</a>
<?php
    }

   //draw the next and the last link
    if($page!=$last)
    {
    ?>
    <b><a href="index.php?mod=<?php echo $global['module'];?>&amp;act=<?php echo $global['action']?>&amp;page=<?php echo $page+1?>"><?php echo _('Next')?></a></b> 
    <b><a href="index.php?mod=<?php echo $global['module'];?>&amp;act=<?php echo  $global['action']?>&amp;page=<?php echo $last ?>"><?php echo _('Last')?></a></b> 
<?php
    }
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
?>