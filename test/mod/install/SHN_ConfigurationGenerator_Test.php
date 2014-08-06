<?php

require_once 'mod/install/SHN_ConfigurationGenerator.php';
require_once 'inc/lib_form.inc';

class SHN_ConfigurationGenerator_Test extends PHPUnit_Framework_TestCase
{
    
    private $_instance;


    public function setup()
    {
        
        global $global;
        
        $global['theme'] = 'vesuvius2';
        $global['approot'] = realpath(dirname(__FILE__)) . '/../../../';
        
        $this->_instance = new SHN_ConfigurationGenerator($global['approot']);
        
    }
    
    
    public function test_sd ()
    {
        
        $this->_instance->writeConfInit();
        
        $content = file_get_contents(realpath(dirname(__FILE__)) . "/result_1.txt");
        $result = substr($content, strlen($content)-0);
        
        $this->expectOutputString($result);
    }
    
}

?>

