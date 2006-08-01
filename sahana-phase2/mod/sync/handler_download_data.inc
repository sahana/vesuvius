<?php
/**
 * Data Dump Interface Handler 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
echo "<h2>Download Data</h2>";
//javascript files used in download UI
?>
<script type="text/javascript">
function selectAll(el,arr){
    var child=document.getElementsByName(arr);
    var st=false;
    if(el.checked == true)
        st=true;
    else
        st=false;
    for (var i=0;i<child.length;i++){
    child[i].checked=st;
    }
}

function checkHead(hname){
    var he=document.getElementById(hname);
    var arr=hname+"[]";
    var child=document.getElementsByName(arr);
    var st=true;
    for (var i=0;i<child.length;i++){
     if(child[i].checked==false){
      st=false;
      break;
     }
    }
    he.checked=st;
}

function check(st){
    var box=document.getElementsByTagName('input');
    for(var i=0;i<box.length;i++){
        if(box[i].type=='checkbox')
            box[i].checked=st;
    }
}

function expand(id){
    var el=document.getElementById(id);
    if(el.style.display=='block')
        el.style.display='none';
    else
        el.style.display='block';
}
</script>
<?php
global $global;

//get all the modules
$modules=shn_get_module_names();
echo "<div id='formcontainer'>";
echo "<form method='POST' action='stream.php?mod=sync&act=download_file' id='formset' name=''>";
echo "<h4>Select data to download</h4>";
//loop through all the modules to find sync.xml
echo "<center><table class='layout'><tr><td rowspan='2'>";
foreach($modules as $module){
    if (file_exists($syncfile=$global['approot']."mod/".$module."/sync.xml"))
    handel_syncfile($syncfile);
}
echo "<br /><center>";
shn_form_submit(_("Select All")," onclick='check(true);return false;'");
shn_form_submit(_("Clear")," onclick='check(false);return false;'");
echo "</center><br /></td>";
echo "<br /><br />";
echo "<td>";
shn_form_fsopen(_("Select File Type"));


?>
    <label>XML File</label><input type="radio" name="file_type" value="xml" checked="true" /><br />
    <label>CSV File</label><input type="radio" name="file_type" value="csv" /><br />
    <label>SQL File</label><input type="radio" name="file_type" value="sql" /><br />
    <label>SQLite File</label><input type="radio" name="file_type" value="sqlite" /><br />
<?php
shn_form_fsclose();
echo "<br /></td></tr></table></center>";
echo "<center><hr />";
shn_form_submit(_("Download"));
echo "</center>";
shn_form_fclose();
echo "</div>";



function handel_syncfile($syncfile)
{
    $scema=simplexml_load_file($syncfile); // loading the sync.xml file
    //print_r($scema);
    //printing the main check box
?>
    <a onclick="expand('b<?=$scema['name'];?>')" href="#">+</a><input type="checkbox" name="modules[]" value="<?=$scema['name'];?>" onchange="selectAll(this,'<?=$scema['name'];?>[]');" id="<?=$scema['name'];?>"><?=$scema->description;?><br />
    
<?php
    //If there is only one data Block dont print the sub sections
    if(isset($scema->data[1]))
    {
        //print the data blocks
        echo "<div id='b".$scema['name']."' style='display:none'>";
        $block=0;
        foreach($scema->data as $key=>$data){
?>
        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="checkbox" name="<?=$scema['name']."[]"?>" value="<?=$block++;?>" onchange="checkHead('<?=$scema['name'];?>')"><?=$data->description;?></input><br />
<?php
        }
        echo "</div>";
    }
    //print data
}
?>