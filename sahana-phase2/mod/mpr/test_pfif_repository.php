<?php
error_reporting(E_ALL ^ E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");


// cron job task for for mpr_pfif import

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";
require_once("../../conf/sysconf.inc.php");
require_once("../../conf/sysconf.inc.php");
require_once("../../3rd/adodb/adodb.inc.php");
require_once("../../inc/handler_db.inc");
require_once "pfif_repository.inc";

/* 
  * Set up assertion options and test reporting functions
*/
assert_options(ASSERT_ACTIVE,   true);
assert_options(ASSERT_BAIL,     true);
assert_options(ASSERT_WARNING,  false);
assert_options(ASSERT_CALLBACK, 'assert_failure');

function log_test() {
    print $_SESSION['suite'].".".$_SESSION['test'].":";
}

function test_assertion($condition) {
    assert($condition);
    print " passed ...\n";
}

function assert_failure() {
global $global, $test_runner;
    print "failed ...\n";
    print $global['db']->ErrorMsg()."\n";
    $test_runner->tear_down();
}

/* 
 * Define the test runner class 
*/
class TestRunner {
    private $basic_suite = array('create',
                                 'find',
                                 'find_source',
                                 'find_sink',
                                 'find_all');
    private $import_suite = array('is_ready_for_import',
                                  'start_import',
                                  'end_import');
    private $export_suite = array('is_ready_for_export',
                                  'start_export',
                                  'end_export');

    private $test_delay = 0;
    private $test_suite = array();
    private $test_repository = null;
    
    public function __construct() {}
    
    public function setup() {
        // TBD: what, if any, setup is necessary for running repository tests?
        // Check session for which test suite
        if (!($__SESSION['suite']=='basic')) {        
            $this->test_repository = new Pfif_Repository();
        }
    }

    public function tear_down() {
        // TBD: what, if any, setup is necessary for running repository tests?
        if (!empty($test_repository) ) {
            $test_repository->__destruct();
            $test_repository = null;
            print "tear_down completed ...\n";
        } else {
            print "nothing to tear_down ...\n";
        }
    }

    public function configure_basic_tests($delay=0) {
       $_SESSION['suite'] = "basic";
       $this->test_suite = $this->basic_suite;
       $this->test_delay = $delay;
        // Use sys exec to run sql pfif_repository/pfif_log init  script
    }
    
    public function configure_import_tests($delay=0) {
        $_SESSION['suite'] = "import";
       $this->test_suite = $this->import_suite;
       $this->test_delay = $delay;
        // Populate pfif_repository/pfif_log init with repos & logs to support import scenarios
    }
    
    public function configure_export_tests($delay=0) {
       $_SESSION['suite'] = "export";
       $this->test_suite = $this->export_suite;
       $this->test_delay = $delay;
        // Populate pfif_repository/pfif_log init with repos & logs to support export scenarios
    }
    
    public function run_tests($test_list = array()) {
        // Allow caller to override configured test list
        $suite = !empty($test_list) ? $test_list : $this->test_suite;

        // Iterate through test list invoking tests in sequence
        foreach ($suite as $test) {
            $_SESSION['test'] = $test;
            $func = 'test_'.$test;
            $this->$func();
            sleep($this->test_delay);
        }
    }

    /*  Basic Tests */

    /**
            * Create a repository in the database
            *
            * Pre-conditions: test_repository instance created
            *                           no repository exists with same name and role
            * Post-conditions: test_responsitory instance initialized
            */
    public function test_create() {
        log_test();
        $test = $__SESSION['test'];

        $__SESSION['test']=$test.".invalid fields";
        $invalid_fields = array('name'=>'Person Finder: Haiti Earthquake',
                                'base_url'=>'http://haiticrisis.appspot.com',
                                'role'=>'source');
        $this->test_repository = Pfif_Repository::create($invalid_fields);
        //var_dump($this->test_repository);
        test_assertion(!($this->test_repository->is_new()));
        $this->test_repository = null;

        $__SESSION['test']=$test.".missing required field";
        $missing_fields = array('name'=>'test_import',
                                'base_url'=>'http://localhost/my_repos');
        $this->test_repository = Pfif_Repository::create($missing_fields);
        //var_dump($this->test_repository);
        test_assertion(!($this->test_repository->is_new()));
        $this->test_repository = null;

        $__SESSION['test']=$test.".valid fields";
        $valid_fields = array('name'=>'test_import',
                                'base_url'=>'http://localhost/my_repos',
                                'role'=>'source');
        $this->test_repository = Pfif_Repository::create($valid_fields);
        //var_dump($this->test_repository);
        test_assertion(!($this->test_repository->is_new()) &&
                       !empty($this->test_repository->id));
        $__SESSION['test']=$test;
    }

    public function test_find() {
        log_test();
        
        test_assertion(true);
    }

    public function test_find_source() {
        log_test();
        test_assertion(true);
    }

    public function test_find_sink() {
        log_test();
        test_assertion(true);
    }

    public function test_find_all() {
        log_test();
        test_assertion(true);
    }

    public function test_save() {
        log_test();
        test_assertion(true);
    }

    public function test_update() {
        log_test();
        test_assertion(true);
    }

    /*  Import Tests */

    public function test_is_ready_for_import() {
        log_test();
        test_assertion(true);
    }

    public function test_start_import() {
        log_test();
        test_assertion(true);
    }

    public function test_end_import() {
        log_test();
        test_assertion(true);
    }

    /*  Export Tests */

    public function test_is_ready_for_export() {
        log_test();
        test_assertion(true);
    }

    public function test_start_export() {
        log_test();
        test_assertion(true);
    }

    public function test_end_export() {
        log_test();
        test_assertion(true);
    }
}

/*
  * ================   CONFIGURE AND RUN TESTS ==================
  */
$test_interval = 0; // Set to N seconds to insert delay between tests.
$test_runner = new TestRunner();
$test_runner->configure_basic_tests($test_interval);
$test_runner->setup();
$test_runner->run_tests();
$test_runner->tear_down();
$test_runner->configure_import_tests($test_interval);
$test_runner->setup();
$test_runner->run_tests();
$test_runner->tear_down();
$test_runner->configure_export_tests($test_interval);
$test_runner->setup();
$test_runner->run_tests();
$test_runner->tear_down();

?>