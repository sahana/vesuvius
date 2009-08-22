<?php

include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot']."/inc/lib_xml.inc";
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');

//require_once "libamp.inc";
require_once "locatews.inc";


function shn_amp_mainmenu() 
{
    global $global;
    $module = $global['module'];
    
    // Create the module menu
    shn_mod_menuopen(_('Aggregator Mashup Portal'));
    shn_mod_menuitem('default',_('Home'));
    shn_mod_menuitem('locate_ws',_('Locate Web Services'));
    shn_mod_menuitem('select_mashup',_('Saved Mashup'));
  
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
   
    // include the main menu so that the user can navigate outside the module
    include $global['approot'].'/inc/handler_mainmenu.inc';

} 

function shn_amp_default(){
	global $conf;
	
//?>
<div id="home">
    <h2><?php echo _lc($conf['mod_amp_name'])?></h2>
    <div><b><i><?php echo _t("\"SAHANA AAggregator Mashup Portal\"")?></i></b></div>
        <br />
        <div><?php echo _t("Aggregator Mashup Portal of the SAHANA Disaster Management System is used to fetch data from different SAHANA instances and make user views on that. When a disaster occurs, it is a general situation that many SAHANA instances may deploy by different authorities. Fetching data from these different instances is crucial since we can use them to make decisions. The Aggregator Mashup Portal provides users to fetch data from different instances by locating them using instance’s URL..")?>
    </div>
    <br />
   
</div>
<br />
<h2><?php echo _t('Saved Mashup')?></h2>
<?php
shn_amp_view_mashup();	
}

