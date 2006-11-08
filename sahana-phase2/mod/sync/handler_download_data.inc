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
echo "<h2>"._('Download Data')."</h2>";
//javascript files used in download UI
?>
<script type="text/javascript" src="index.php?stream=text&mod=sync&act=js"></script>
<?php
global $global;

//get all the modules
$modules=shn_get_module_names();
shn_form_fopen('download_file&stream=text',$global['module'],array('req_message'=>false));
echo "<center>";
echo "<a href=\"#\" onclick=\"document.getElementById('down').style.display='block';\">"._('Advance Options')."</a>";
shn_form_submit(_("Download"));
echo "</center>";
//loop through all the modules to find sync.xml
echo "<div id='down' style='display:none;'>";
shn_form_fsopen(_("Select data to download"));
foreach($modules as $module){
    if (file_exists($syncfile=$global['approot']."mod/".$module."/sync.xml"))
    handel_syncfile($syncfile);
}

echo "<br />";
shn_form_submit(_("Select All")," onclick='check(true);return false;'");
shn_form_submit(_("Clear")," onclick='check(false);return false;'");
echo "<br />";
shn_form_fsclose();
echo "<table class='layout'><tr><td>";
shn_form_fsopen(_("Select File Type"));

?>
    <label><?=_('XML File')?></label><input type="radio" name="file_type" value="xml" checked="true" /><br/>
    <label><?=_('CSV File')?></label><input type="radio" name="file_type" value="csv" /><br/>
    <label><?=_('SQL File')?></label><input type="radio" name="file_type" value="sql" /><br/>
    <label><?=_('SQLite File')?></label><input type="radio" name="file_type" value="sqlite" /><br/>
<?php
shn_form_fsclose();
echo "</td><td>";
shn_form_fsopen(_("Select Compression Type"));

?>
    <label><?=_('None')?></label><input type="radio" name="compression" value="none"  /><br/>
    <label><?=_('Gzip')?></label><input type="radio" name="compression" value="gz" /><br/>
    <label><?=_('Bzip2')?></label><input type="radio" name="compression" value="bz2" /><br/>
    <label><?=_('Zip')?></label><input type="radio" name="compression" value="zip" /><br/>
<?php
shn_form_fsclose();
echo "</td></tr></table>";
echo "</div>";
shn_form_fclose();




function handel_syncfile($syncfile)
{
    $scema=simplexml_load_file($syncfile); // loading the sync.xml file

    $html0="<b onclick=\"expandblock('b{$scema['name']}')\" style=\"cursor:pointer\">+</b>";
    $html1.="<label>".$scema->description."</label>";
	$html1.="<input type=\"checkbox\" name=\"modules[]\" checked='true' value=\"{$scema['name']}\" onchange=\"selectAll(this,'{$scema['name']}[]');\" id=\"{$scema['name']}\">";
    $html1.='<br/>';

    //If there is only one data Block dont print the sub sections
    if(isset($scema->data[1]))
    {
    	echo $html1;
        //print the data blocks
        echo "<div id='b".$scema['name']."' style='display:none'>";
        $block=0;
        foreach($scema->data as $key=>$data){
?>
        <label><?=$data->description;?></label><input type="checkbox" name="<?=$scema['name']."[]"?>" value="<?=$block++;?>" onchange="checkHead('<?=$scema['name'];?>')" /><br />
<?php
        }
        echo "</div>";
    }
    else
    	echo $html1;
    //print data
}
?>