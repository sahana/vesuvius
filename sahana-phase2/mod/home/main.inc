<?PHP

/**
 * shn_soap_home_default 
 * 
 * @access public
 * @return string
 */
function shn_soap_home_default()
{

}

function shn_text_home_help()
{
    if(empty($_GET['help_id'])){
        echo "var help_arr = new Array(".count($_SESSION['form_help']).");\n";
        if(isset($_SESSION['form_help']))
            foreach($_SESSION['form_help'] as $help_id => $value){
                $clean_value = preg_replace(array('@([\r\n])[\s]+@','@"@'), array(' ',"'"),$value);
                echo "help_arr[".$help_id."] = \"$clean_value\";\n";
            }
    }else{
        echo $_SESSION['form_help'][$_GET['help_id']];
    }
}

function shn_home_default()
{
    global $conf;
    
    ?>

    <div id="home">

    <?=_("<h2>Welcome to the Sahana FOSS Disaster Management System</h2>")?>
<!--        <img src="theme/default/img/home_pic1.png" align="left" /> -->
    <p><?=_("Sahana is an set of web based disaster management applications that provide solutions to large-scale humanitarian coordination and collaboration problems in the aftermath of a disaster. The applications and problems they address are as follows:")?></p>
	<ul>
    
<?php
	_shn_home_module_info('gis','Giving you the current situation awareness on a map');
	_shn_home_module_info('mpr','Helping to reduce trauma by effectively finding missing persons');
	_shn_home_module_info('dvr','Tracing internally displaced people (IDPs) and their needs');
    _shn_home_module_info('or','Listing "Who is doing What, Where" allow relief agencies to self-distribute themselves better to address the gaps in disasters');
    _shn_home_module_info('rms',"Tracking all the requests for aid from the field and matching them against donars who have pledged aid");
    _shn_home_module_info('cr',"Tracking the location, distibution, capacity and breakdown of victims in shelter");
    _shn_home_module_info('ims',"Effectively and efficiently manage relief aid, enables  transfer of inventory items to different inventories and notify when items are required to refill.");
    _shn_home_module_info('msg',"Message through email and mobile phones to groups");
    _shn_home_module_info('vol',"Capturing all volunteers, their skills, availability and allocation");
    _shn_home_module_info('cs',"Captures information on different catalogues and measurement units. Which is used in systems such as Inventory Management System and Request Management System.");
    _shn_home_module_info('sync',"Synchronize of data between instances of Sahana.");
?>

	</ul>
    <p>
    <?php
    	echo _("For more detail on the Sahana system see the ") .
			  '<a href="http://www.sahana.lk">' .
			  _("Sahana Website").'</a><br/>';
        echo _('For live help from the Sahana community on using this application goto the ').
              '<a href="http://www.sahana.lk/chat">'._('Sahana Community Chat').'</a><br/>';

        if ($conf['root_name'] != '') {
            echo '<br/>'._('Administrator: ').$conf['root_name'];
        }
        if ($conf['root_email'] != '') {
            echo '.<br/>Email: '.$conf['root_email'];
        }
        if ($conf['root_tel'] != '') {
            echo '<br/>Telephone: '.$conf['root_tel'];
        }
    ?>
	</p>
    </div>

<?php
}

function _shn_home_module_info($module, $description) 
{
    global $conf;

    if ($conf['mod_'.$module.'_enabled']) {
        echo '<li><b>'.$conf['mod_'.$module.'_name'].'</b> - ';
        echo _($description).'</li>';
    }

}

?>
