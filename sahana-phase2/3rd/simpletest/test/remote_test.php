<?php
    // $Id: remote_test.php,v 1.1 2005-10-11 06:37:17 saumya Exp $
    require_once('../remote.php');
    require_once('../reporter.php');
    
    // The following URL will depend on your own installation.
    $base_url = 'http://uno/simple/';
    
    $test = &new GroupTest('Remote tests');
    $test->addTestCase(new RemoteTestCase(
            $base_url . 'test/visual_test.php?xml=yes',
            $base_url . 'test/visual_test.php?xml=yes&dry=yes'));
    if (SimpleReporter::inCli()) {
        exit ($test->run(new XmlReporter()) ? 0 : 1);
    }
    $test->run(new HtmlReporter());
?>