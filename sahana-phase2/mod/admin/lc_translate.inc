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
<h5><?php echo _t("Sahana Localization Module") ?></h5>
<h5><?php echo _t("Language Translation") ?></h5>
<h5><?php print _t("Current language : ") . _lc($lc) ?></h5>
<table class="layout">
<tr>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'extract'));
	    shn_form_submit(_t('Get New List'));
	    shn_form_fclose();
	?>
	</td>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'load'));
	    shn_form_submit(_t('Load Existing List'));
	    shn_form_fclose();
	?>
	</td>
	<td>
	<?php
			shn_form_fopen("lc_trns",null,array('req_message'=>false));
			shn_form_hidden(array('seq'=>'merge'));
			shn_form_submit(_t('Merge New Strings'));
		   	shn_form_fclose();
	?>
	</td>
	<td>
	<?php
		$file_name = "../res/locale/$locale/LC_MESSAGES/sahana.po";
    	if(file_exists($file_name)) {
    		global $global;
    		print _t("You can download the " ).
    				"[<a href='".$global['approot']."res/locale/$locale/LC_MESSAGES/sahana.po'> Sahana.po </a>] " .
    				_t("file and do the translation offline, then paste the content of the file in the text area bellow and save it using save button.");
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
	//$file_cont = __text_clean($_POST['msgs']);

	$file_cont = html_entity_decode($_POST['msgs'],ENT_QUOTES,"UTF-8");
	/*$file_cont = str_replace("\\\"","\"",$file_cont);
	$file_cont = str_replace("\\\n","\\n");*/
	$file_cont = stripcslashes($file_cont);
//	file_put_contents("/tmp/testfile.po",$file_cont);

	//echo "<pre>".$file_cont."</pre>";

	if(is_writable("../res/locale/$locale/LC_MESSAGES/")){
		$result = file_put_contents($file_name, $file_cont);
		chmod($file_name,0666);
		if($result===FALSE){
			add_error(_t("Failed to write to file ").$file_name);
		}else{
			add_confirmation(_t("File saved successfully."));
		}
	}else{
		echo "<div class=\"message info\">";
		print _t("Please make the path : ").$file_name ._t(" writable");
		echo "</div>";
	}

	_shn_admin_lc_load();
}

function _shn_admin_lc_merge()
{
	$locale = $_SESSION["locale"];
	$file_name = "../res/locale/$locale/LC_MESSAGES/sahana.po";
	$file_name1 = "../res/locale/$locale/LC_MESSAGES/sahana_temp.po";


	if(is_writable("../res/locale/$locale/LC_MESSAGES/"))
	{
		if(file_exists($file_name)){
				$return = array();
            	$cmd = 'xgettext --keyword=__ --keyword=_e ' .
        		'--keyword=_t  --default-domain=sahana ' .
        		'--language=php ../*/*/*.inc ../*/*.inc ../*/*/*/*/*.inc ' .
        		'--output=../res/locale/' . $locale. '/LC_MESSAGES/sahana_temp.po';
        		system($cmd, &$return);

        		/*$_SESSION['admin']['locale']['charset'] = implode('', file("../res/locale/$locale/LC_MESSAGES/sahana_temp.po"));
        		$string = 'charset=CHARSET';
        		$position = strpos($_SESSION['admin']['locale']['charset'],$string);
        		$quatationposition = strpos($_SESSION['admin']['locale']['charset'],"\"",$position);
        		$var = 'charset=UTF-8  ';
				$_SESSION['admin']['locale']['charset'] = substr_replace($_SESSION['admin']['locale']['charset'],$var,$position,strlen($var));



				$somecontent = $_SESSION['admin']['locale']['charset'];

*/
        		$filename = "../res/locale/$locale/LC_MESSAGES/sahana_temp.po";
        		$po_file = file_get_contents("../res/locale/$locale/LC_MESSAGES/sahana_temp.po");
        		$rep_po_file = _shn_replace_charset($po_file,"UTF-8");

        		if(is_writable($filename)) {
    				if(!$handle = fopen($filename, 'w+')) {
         				add_error(_t("Cannot open file ").$filename);
         				exit;
    				}
					if(fwrite($handle, $rep_po_file) === FALSE) {
        				add_error(_t("Cannot write to file ").$filename) ;
        				exit;
    				}
    				//echo "Success, wrote to file ($filename) .$msgstr"."MSGID = ".$msgid;
    				fclose($handle);
    				//unset($_SESSION['admin']['locale']['charset']);
    				_shn_admin_lc_merge_over();

				}else {
    				add_error(_t("Cannot write to file ").$filename) ;
				}
		}
		else
			print _t("Please make the path : ").$file_name ._t(" writable");

	}else
		print _t("Please make the path : ").$file_name ._t(" writable");

	_shn_admin_lc_load();


}

function _shn_admin_lc_merge_over()
{
		$locale = $_SESSION["locale"];
		$file_name = "../res/locale/$locale/LC_MESSAGES/sahana_temp.po";
		$tmpfilename = tempnam('/tmp/','shn');

		if(file_exists($file_name)){
			$cmd = 'msgcat ../res/locale/' . $locale. '/LC_MESSAGES/sahana_temp.po ../res/locale/' . $locale. '/LC_MESSAGES/sahana.po > '.$tmpfilename;
       		system($cmd, &$return);

       		$fp_src = fopen($tmpfilename,'r');
       		$fp_dest = fopen('../res/locale/' . $locale. '/LC_MESSAGES/sahana.po',"w+");
       		while($tmp = fread($fp_src,1024)){
       			fwrite($fp_dest,$tmp);
       		}
       		fclose($fp_src);
       		fclose($fp_dest);

       		add_confirmation(_t("New strings merge sucessfully, please press 'Load Existing List' button"));
		}else{
			add_error(_t("Please make the path : ").$file_name ._t(" writable"));
		}
		//_shn_admin_lc_load();
}


function _shn_admin_lc_load($file_n = null)
{
	$locale = $_SESSION["locale"];

	if($file_n == null)
    		$file_name = "../res/locale/$locale/LC_MESSAGES/sahana.po";
	else
		$file_name = $file_n;

	if(!file_exists($file_name))
		$value = _t("Please create the file first");
	else {
		//$value = file_get_contents($file_name);
        if(!_shn_lc_is_dbl10n_tbl_empty()) {
            $t_value .= "\n\n#: "._t("DB L10N Starts here")."\n";
            $t_value .= _shn_lc_get_dbpo();
            $tmp_ids = tempnam("/tmp/","shn_");
            chmod($tmp_ids,0666);
            $tmpfilename = tempnam("/tmp/","shn_");
            chmod($tmpfilename,0666);
            file_put_contents($tmp_ids,$t_value);
            $cmd = 'msgcat '.$file_name.' '.$tmp_ids.' > '.$tmpfilename;//
            $output= array();
       		exec($cmd,&$output, &$return);

       		if($return==0){
       			 $value = file_get_contents($tmpfilename);
       		}else{
       			add_error(_t("Failed to merge database localization values."));
				echo $cmd;
       			$value = file_get_contents($file_name);
       		}
        }
    }

	//echo "<pre>".$value."</pre>";

	shn_form_fopen("lc_trns",null,array('req_message'=>false));
    shn_form_hidden(array('seq'=>'save'));
    shn_form_fsopen(_t('Translation'));
    shn_form_textarea('','msgs',null,array('value'=>$value,'rows'=>'30', 'cols'=>'100'));
    shn_form_fsclose();
    shn_form_submit(_t('Save'));
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
    case 'merge':
    		_shn_admin_lc_merge();
    		break;
    case 'extract':
    		$return = array();
            $cmd = 'xgettext --keyword=__ --keyword=_e ' .
            		'--keyword=_p  --default-domain=sahana ' .
            		'--language=php ../*/*/*.inc ../*/*.inc ../*/*/*/*/*.inc ../*/*/*/*/*.inc ' .
            		'--output=../res/locale/' . $locale. '/LC_MESSAGES/sahana_temp.po';
            system($cmd, &$return);
            $po_file = file_get_contents("../res/locale/" . $locale. "/LC_MESSAGES/sahana_temp.po");
            $new_po_file = _shn_replace_charset($po_file,"UTF-8");
            file_put_contents("../res/locale/" . $locale. "/LC_MESSAGES/sahana_temp.po",$new_po_file);
            chmod("../res/locale/" . $locale. "/LC_MESSAGES/sahana_temp.po",0666);
            _shn_admin_lc_load('../res/locale/' . $locale. '/LC_MESSAGES/sahana_temp.po');

            break;
    case 'compile':
            $return = array();
            $cmd = 'msgfmt ../res/locale/' . $locale . '/LC_MESSAGES/sahana.po --output-file=../res/locale/' . $locale . '/LC_MESSAGES/sahana.mo';
            system($cmd, &$return);
            break;
}
?>

<table>
<tr>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'extract'));
	    shn_form_submit(_t('Get New List'));
	    shn_form_fclose();
	?>
	</td>
	<td>
	<?php
		shn_form_fopen("lc_trns",null,array('req_message'=>false));
	    shn_form_hidden(array('seq'=>'load'));
	    shn_form_submit(_t('Load Existing List'));
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
	    shn_form_submit(_t('Compile Messages'));
	    shn_form_fclose();
	?>
	</td>
</tr>
</table>

