<?php

/**
 * Data Export functions 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ishan Liyanage <ishanul@gmail.com>
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
 
 function _shn_rs_export_form($title){
    global $global;
    global $dieconf;
    echo "<h2>Export File Info</h2>";

    /*$recordSet = $global['db']->Execute('select * from export where id='.$_GET['id']);
    $arr=$recordSet->FetchRow();

    $_SESSION['export_sql']=$arr['sql'];
    $_SESSION['export_title']=explode(",", $arr['title']);*/
    shn_form_fopen("export&amp;stream=text",null, array('req_message'=>false));
    shn_form_fsopen(_('Export File Info'));
    shn_form_label("Name :", "<b>".$title."</b>", $extra_opts = null);
    //shn_form_label("Description", "<b>".$arr['desc']."</b>", $extra_opts = null);
    shn_form_select($dieconf['formats'],"Select File Format", "format");
    shn_form_fsclose();
    shn_form_submit(_('Export'));
    shn_form_fclose();
 }
 
function _shn_rs_export_init($sql,$dis_name,$title){
    $_SESSION['export_sql']=$sql;
    $_SESSION['export_title']=$dis_name;
    echo "<br><br>";
    echo "<b><a href='index.php?mod=rs&amp;act=export&amp;title=".$title."'> Export to other formats</a></b>";
         
 }
