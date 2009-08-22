<?php
/**
 * Data Download Interface Handler 
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

global $global;
echo "<h2>"._t('Export Data')."</h2>";
//javascript files used in download UI
?>
<script type="text/javascript" src="index.php?stream=text&amp;mod=sync&amp;act=js"></script>
<?php
//get all the modules
$modules=shn_get_module_names();

//draw download form
shn_form_fopen('download_file&stream=text',$global['module'],array('req_message'=>false,'tab'=>'float'));
echo "<center>";
shn_form_submit(_t("Export"));
echo "</center>";
//loop through all the modules to find sync.xml

shn_form_fsopen(_t("Select Data"));
?>
<p><?php echo _t("The following list shows the data which are available to export. Use the check boxes to select or deselect data you want to export. If the data you select has dependent data, they would be automatically added to export file.")."</p>";?>
<?php
foreach($modules as $module){
    if (file_exists($syncfile=$global['approot']."mod/".$module."/sync.xml"))
    handel_syncfile($syncfile);
}

echo "<br />";
shn_form_submit(_t("Select All")," onclick='check(true);return false;'");
shn_form_submit(_t("Clear")," onclick='check(false);return false;'");
echo "<br />";
shn_form_fsclose();
shn_form_fsopen(_t("File Type"));
?>
    <p><?php echo _t("The data can be exported in the following formats please select the format you want to export.")?></p>
    <label><?php echo _t('XML File')?></label><input type="radio" name="file_type" value="xml" checked="true" /><br/>
    <label><?php echo _t('CSV File')?></label><input type="radio" name="file_type" value="csv" disabled="true" /><br/>
    <label><?php echo _t('SQL File')?></label><input type="radio" name="file_type" value="sql" disabled="true"/><br/>
    <label><?php echo _t('SQLite File')?></label><input type="radio" name="file_type" value="sqlite" disabled="true"/><br/>
<?php
shn_form_fsclose();
shn_form_fsopen(_t("Compression Type"));


//check the avalable compression functions and enable them
    $bzip2=(function_exists('bzopen'))?'':'disabled="true"';
    $gzip=(function_exists('gzopen'))?'':'disabled="true"';
?>
    <p><?php echo _t("The export file can be compressed using the formats in the list bellow. Select 'None' if you do not want the file to be compressed.")." <strong><em>"._t("Important:")."</em></strong>"._t("Compressing the export file will reduce the download time significantly.")."</p>"?>
    <label><?php echo _t('None')?></label><input type="radio" name="compression" value="none"/><br/>
    <label><?php echo _t('Gzip')?></label><input type="radio" name="compression" value="gz" <?php echo $gzip?> checked="true" /><br/>
    <label><?php echo _t('Bzip2')?></label><input type="radio" name="compression" value="bz2" <?php echo $bzip2?> /><br/>
    <label><?php echo _t('Zip')?></label><input type="radio" name="compression" value="zip" disabled="true"/><br/> 
<?php
shn_form_fsclose();
shn_form_fclose();




function handel_syncfile($syncfile)
{
    $scema=simplexml_load_file($syncfile); // loading the sync.xml file

    $html0="<b onclick=\"expandblock('b{$scema['name']}')\" style=\"cursor:pointer\">+</b>";
    $html1.="<label>".$scema->description."</label>";
	$html1.="<input type=\"checkbox\" name=\"modules[]\" checked='true' value=\"{$scema['name']}\" onchange=\"selectAll(this,'{$scema['name']}[]');\" id=\"{$scema['name']}\" />";
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
        <label><?php echo _lc($data->description);?></label><input type="checkbox" name="<?php echo $scema['name']."[]"?>" value="<?php echo $block++;?>" onchange="checkHead('<?php echo $scema['name'];?>')" /><br />
<?php
        }
        echo "</div>";
    }
    else
    	echo $html1;
    //print data
}
