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
* @package	  framework
* @subpackage localization
* @tutorial	  localization.pkg
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/

$locale = $_SESSION["locale"];
$lc = $_SESSION["locale"];
if(!function_exists('file_put_contents')) {
    function file_put_contents($file_name, $content)
    {
        $file = fopen($file_name, 'w+');
        fwrite($file, $content);
        return fclose($file);
    }
}
?>
<h3><?=_("Sahana Localization Module") ?></h3>
<h4><?=_("Language Translation") ?></h4>
<h3><?php print _("Current language : ") . _lc($lc) ?></h3>
<table class="layout">
<tr>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'extract'));
	    shn_form_submit('Get New List');
	    shn_form_fclose();
	?>
	</td>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'load'));
	    shn_form_submit('Load Existing List');
	    shn_form_fclose();
	?>
	</td>
	<td>
	<?php
		$file_name = "../res/locale/$locale/LC_MESSAGES/sahana.po";
    	if(file_exists($file_name)) {
    		global $global;
    		print _("You can download the [" .
    				"<a href='".$global['approot']."res/locale/$locale/LC_MESSAGES/sahana.po'> Sahana.po </a>] " .
    				"file and do the translation offline," .
    				"then paste the content of the file in the text area bellow and save it using save button.");
    	}

   	?>
	</td>
</tr>
</table>
<?php

function __text_clean($str)
{
	if(get_magic_quotes_gpc())
    	return stripslashes($str);
}

function _shn_admin_lc_save()
{
	$locale = $_SESSION["locale"];
	$file_name = "../res/locale/$locale/LC_MESSAGES/sahana.po";
	$file_cont = __text_clean($_POST['msgs']);

	if(is_writable("../res/locale/$locale/LC_MESSAGES/"))
		file_put_contents($file_name, utf8_encode($file_cont));
	else
		print "plesae make the path : $file_name writable";

	_shn_admin_lc_load();
}

function _shn_admin_lc_load($file_n = null)
{
	$locale = $_SESSION["locale"];

	if($file_n == null)
    		$file_name = "../res/locale/$locale/LC_MESSAGES/sahana.po";
	else
		$file_name = $file_n;

	if(!file_exists($file_name))
		$value = "Please create the file first";
	else {
		$value = file_get_contents($file_name);
        if(!_shn_lc_is_dbl10n_tbl_empty()) {
            $value .= "\n\n#: DB L10N Starts here\n";
            $value .= _shn_lc_get_dbpo();
        }
    }

	shn_form_fopen("lc_trns",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'save'));
    shn_form_fsopen('Translation');
    shn_form_textarea('','msgs',null,array('value'=>$value,'rows'=>'30', 'cols'=>'100'));
    shn_form_fsclose();
    shn_form_submit('Save');
    shn_form_fclose();
}
?>

<?php
switch($_REQUEST['seq']) {
	case '':
            _shn_admin_lc_load();
            break;
    case 'load':
            _shn_admin_lc_load();
            break;
    case 'save':
            _shn_admin_lc_save();
            break;
    case 'extract':
    		$return = array();
            $cmd = 'xgettext --keyword=__ --keyword=_e ' .
            		'--keyword=_p  --default-domain=sahana ' .
            		'--language=php ../*/*/*.inc ' .
            		'--output=../res/locale/' . $locale. '/LC_MESSAGES/sahana_temp.po';
            _shn_admin_lc_load('../res/locale/' . $locale. '/LC_MESSAGES/sahana_temp.po');
            system($cmd, &$return);
            break;
    case 'compile':
            $return = array();
            $cmd = 'msgfmt ../res/locale/' . $locale . '/LC_MESSAGES/sahana.po --output-file=../res/locale/' . $locale . '/LC_MESSAGES/sahana.mo';            system($cmd, &$return);
            break;
}
?>

<table>
<tr>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'extract'));
	    shn_form_submit('Get New List');
	    shn_form_fclose();
	?>
	</td>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'load'));
	    shn_form_submit('Load Existing List');
	    shn_form_fclose();
	?>
	</td>
	<td>
	<?php
//		shn_form_fopen("lc_trns",null,array('req_message'=>false));
//	    shn_form_hidden(array('seq'=>'save'));
//	    shn_form_submit('Save Messages');
//	    shn_form_fclose();
	?>
	</td>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'compile'));
	    shn_form_submit('Compile Messages');
	    shn_form_fclose();
	?>
	</td>
</tr>
</table>