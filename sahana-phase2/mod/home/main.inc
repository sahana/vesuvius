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
	<li><b><?=_("Missing Person Registry</b> <br/>Helping to reduce trauma by effectively finding missing persons")?> </li>
	<li><b><?=_("Organization Registry</b> <br/>Coordinating and balancing the distribution of relief organizations in the affected areas and connecting relief groups allowing them to operate as one")?> </li>
	<li><b><?=_("Request Management System</b> <br/>Registering and Tracking all incoming requests for support and relief up to fulfilment and helping donors connect to relief requirements")?> </li>
	<li><b><?=_("Camp Registry</b><br/>Tracking the location and numbers of victims in the various camps and temporary shelters setup all around the affected area")?> </li>
	<li><b><?=_("Inventory Management System</b><br/> Effectively and efficiently manage relief aid, enables  transfer of inventory items to different inventories and notify when items are required to refill.")?> </li>
	<li><b><?=_("Catalogue System</b><br/> Captures information on different catalogues and messurement units. Which is used in systems such as Inverntory Management System and Request Management System.")?> </li>
	</ul>
    <p>
    <?php
    	echo _("For more detail on the Sahana system see the ") .
			  '<a href="http://www.sahana.lk">' .
			  _("Sahana Website </a><br/>"); 
        if ($conf['root_name'] != '') {
            echo '<br/>'._('Administrator: ').$conf['root_name'].
                   '.<br/>Email: '.$conf['root_email'].'<br/>Telephone: '.$conf['root_tel'];
        }
    ?>
	</p>
    </div>

<?php
}

?>
