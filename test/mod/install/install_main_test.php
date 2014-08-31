<?php

require_once 'mod/install/main.inc';
require_once 'mod/plus/unitTestLib.php';

/**
 * This class test the functions of mod/install/main.inc file
 */
class INSTALL_MAIN_TEST extends PHPUnit_Framework_TestCase
{
    
    /**
     * This method runs, before any test method.
     * 
     * @global type $global
     */
    public function setup()
    {
        
        global $global;
        
        $global['theme'] = 'vesuvius2';
        $global['approot'] = realpath(dirname(__FILE__)) . '/../../../';
        
    }
    
    /**
     * Test the standard output of shn_install_stream_init() method.
     */
    public function test_shn_install_stream_init()
    {
        shn_install_stream_init();
        ob_end_flush();
        $this->expectOutputString('<body><div id="container"><div id="header" class="clearfix"><div id="leftHeaderLogo"><a href="">
<img id="leftHeaderLogoImg" src="theme/vesuvius2/img/vesuvius.png" alt="Vesuvius Logo"></a>
</div><div id="rightHeaderLogo">
<a href="http://www.nlm.nih.gov/"><img src="theme/vesuvius2/img/sahana_vesuvius.png" alt="Sahana Vesuvius Logo">
</a></div></div>
		<div id="headerText">
			<h1><sup>™</sup></h1>
			<h3>&nbsp;</h3>
			<h4></h4>
			<h4><a href="">http://sahanafoundation.org</a></h4>
		</div>
	<div id="wrapper" class="clearfix"><div id="wrapper_menu"><div id="menuwrap"><ul id="menu"></ul></div></div><div id="content"><div style="padding: 20px 0px 0px 36px; font-size: 16px;">');
        
    }
    
    
}

?>
