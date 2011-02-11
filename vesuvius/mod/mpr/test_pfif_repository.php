<?php
error_reporting(E_ALL ^ E_NOTICE);
// print "Configuring error display  ...\n";
ini_set("display_errors", "stdout");


// cron job task for for mpr_pfif import

// set approot since we don't know it yet
$global['approot'] = getcwd()."/../../";
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
    log_test();
    assert($condition);
    print "passed ...\n";
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
                                 'find_by_id',
                                 'find_source',
                                 'find_source_all',
                                 'find_sink',
                                 'find_sink_all');

    private $valid_results = array('1'=>array('name'=>'Person Finder: Haiti Earthquake','role'=>'source'),
                          '2'=>array('name'=>'Person Finder: Haiti Earthquake','role'=>'sink'),
                          '3'=>array('name'=>'Person Finder: Chile Earthquake','role'=>'source'),
                          '4'=>array('name'=>'Person Finder: Chile Earthquake','role'=>'sink'));

    private $import_suite = array('is_ready_for_import',
                                  'start_harvest',
                                  'end_harvest',
                                  'start_harvest_multi_log');
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
        if ($_SESSION['suite']=='basic') {        
            // $this->test_repository = new Pfif_Repository(); // Is this needed?
            $this->clean_db();
        } else if ($_SESSION['suite']=='import') {
        } else if ($_SESSION['suite']=='export') {
        }
        print "\n---\nsetup ".$SESSION['suite']." completed!\n";
    }

    protected static function createValidImportRepository($name = 'test_import') {
        $valid_fields = array('name'=> $name,
                                'base_url'=>'http://localhost/my_repos',
                                'role'=>'source',
                                'granularity'=>'YYYY-MM-DDThh:mm:ssZ',
                                'deleted_record'=>'no',
                                'params'=>'<config/>',
                                'sched_interval_minutes'=>'1',
                                'log_granularity'=>'00:01:00');
        return Pfif_Repository::create($valid_fields);
    }
    public function tear_down() {
        if (!empty($this->test_repository) ) {
            // TODO: make this a command line option: $this->test_repository = null;
            $this->test_repository->first_entry = null;
            $this->test_repository->last_entry = null;
            $this->test_repository->get_log()->end_time = null;
        } 
        // TODO: make this a command line option: $this->clean_db();
        print "tear_down completed ...\n";
    }

    private function clean_db() {
        global $global;
        // TODO: Until foreign key is changed to use DELETE CASCADE have to
        //       delete log records first.
        $query = "DELETE from `pfif_harvest_log` where 1";
        $global['db']->Execute($query);
        $query = "SELECT ROW_COUNT()";
        $rs = $global['db']->GetAll($query);
        print "clean_db deleted ".$rs[0]['ROW_COUNT()']." rows from pfif_harvest_log\n";

        $query = "SELECT COUNT(*) from `pfif_repository` where `id` > 4";
        $rs = $global['db']->GetAll($query);
        $repos_count = $rs[0][0];
        print "clean_db deleting ".$repos_count." rows from pfif_repository\n";

        $query = "DELETE from `pfif_repository` WHERE `id` > 4";
        $rs = $global['db']->Execute($query);

        $query = "SELECT ROW_COUNT()";
        $rs = $global['db']->GetAll($query);
        $repos_delete_count = $rs[0]['ROW_COUNT()'];
        print "clean_db deleted ".$repos_delete_count." rows\n";

        if ($repos_delete_count != $repos_count) {
            throw new RuntimeException("repository cleanup failed!");
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
        // var_dump('run_tests:suite=',$suite);
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
        $test = $_SESSION['test'];

        $_SESSION['test']=$test.'.invalid fields';
        // FIXME: This should test validation for duplicate name, url syntax and role value
        //        For now, use a missing role to trigger failure.
        $invalid_fields = array('name'=>'Person Finder: Haiti Earthquake',
                                'baste_url'=>'http://haiticrisis.appspot.com',
                                'source'=>'stink');
        try {
            $this->test_repository = Pfif_Repository::create($invalid_fields);
            var_dump('ERROR! create returned:',$this->test_repository);
            test_assertion(false);
        } catch (Exception $e) {
            var_dump($e->getMessage());
            test_assertion($this->test_repository == null);
        }
        $this->test_repository = null;

        $_SESSION['test']=$test.'.missing required field';
        $missing_fields = array('name'=>'test_import',
                                'base_url'=>'http://localhost/my_repos');
        $this->test_repository = Pfif_Repository::create($missing_fields);
        test_assertion($this->test_repository->is_new() &&
                       empty($this->test_repository->id)); // Can we also check that db affected rows is 0??
        $this->test_repository = null;

        $_SESSION['test']=$test.'.valid fields';
        $this->test_repository = self::createValidImportRepository();
        // var_dump($this->test_repository);
        test_assertion(!($this->test_repository->is_new()) &&
                       !empty($this->test_repository->id)); // Can we also check that db affected rows is > 0??
        $_SESSION['test']=$test;
    }

    public function test_find() {
        $r = Pfif_Repository::find(); // TODO: finds all 5 repos, but log for #1 is empty
        // var_dump('Dumping result for test_'.$_SESSION['test'],$r);
        $rr = array_reverse($r);
        test_assertion( count($r)==5 && $rr[0]->name=='test_import');
    }

    public function test_find_by_id() {
        global $global,$conf;
        
        $test = $_SESSION['test'];

        $_SESSION['test']=$test.".test key valid";
        $key = $global['db']->Insert_ID('pfif_repository','id');
        test_assertion($key > 4);

        for ($ii=0;$ii <5;$ii++) {// find first 4 static repos
            $_SESSION['test']=$test.".id=".$ii;
            $r = Pfif_Repository::find_by_id($ii);
            // var_dump('Dumping result for test_'.$_SESSION['test'],$r[$ii],'valid ref:\n',$this->valid_results[$ii]);
            $assertion_test = ($ii == 0) ? ($r == false) :
                              ($r[$ii]->name==$this->valid_results[$ii]['name'] &&
                               $r[$ii]->role==$this->valid_results[$ii]['role']);
            test_assertion($assertion_test);
        }

        // Find last entry added
        $_SESSION['test']=$test.".id=".$key;
        $r = Pfif_Repository::find_by_id($key);
        // var_dump('Dumping result for test_'.$_SESSION['test'],$r);
        test_assertion($r && $r[$key]->name=='test_import');

        $_SESSION['test']=$test;
    }

    public function test_find_source() {
        $r = Pfif_Repository::find_source('test_import');
        $repos = array_pop($r);
        test_assertion((count($r) == 0) && $repos->name == 'test_import');
    }

    public function test_find_source_all() {
        $test = $_SESSION['test'];
        $r = Pfif_Repository::find_source();
        // var_dump('Dumping result for test_'.$_SESSION['test'],$r);
        $_SESSION['test']=$test.".count";
        test_assertion(count($r)==3);

        $_SESSION['test']=$test.".role";
        $test_token = true;
        foreach ($r as $row) {
            $test_token &= $row->role=='source';
        }
        test_assertion($test_token);
        $_SESSION['test']=$test;
    }

    public function test_find_sink() {
        $rname = $this->valid_results[2]['name'];
        $r = Pfif_Repository::find_sink($rname);
        // var_dump('Dumping result for test_'.$_SESSION['test'],$r);
        $repos = array_pop($r);
        test_assertion((count($r) == 0) && $repos->name==$rname && $repos->role=='sink');
    }

    public function test_find_sink_all() {
        $test = $_SESSION['test'];
        $r = Pfif_Repository::find_sink();
        // var_dump('Dumping result for test '.$_SESSION['test'],$r);
        $_SESSION['test']=$test.".count";
        test_assertion(count($r)==2);

        $_SESSION['test']=$test.".role";
        $test_token = true;
        foreach ($r as $row) {
            $test_token &= $row->role=='sink';
        }
        test_assertion($test_token);
        $_SESSION['test']=$test;
    }
/*
 *  TODO: Prinitive find() and find_<role>('all') replace this functionality
    public function test_find_all() {
        $r = Pfif_Repository::find_all();
        var_dump('Dumping result for test '.$_SESSION['test'],$r);
        test_assertion(true);
    }
*/
    /**
     *  test_save is used to test any save conditions not tested implicitly by create()
    */
    public function test_save() {
        test_assertion(false);
    }

    /**
     *  test_save is used to test any update conditions not tested implicitly by create() or save()
    */
    public function test_update() {
        test_assertion(false);
    }

    /*  Import Tests */
    /*
     * Using a test repository created by the setup() and configure_*() methods,
     * set the repository params and associated log params to create the required
     * pre-conditions for each test. USe assertions to test post_conditions for each
     * sub_test.
     */
    public function test_is_ready_for_import() {
        if ($this->test_repository == null ||
           stripos($this->test_repository->name,'test_import') === FALSE) 
        {
           $this->test_repository = self::createValidImportRepository();
        }

        $test = $_SESSION['test'];
        $_SESSION['test']=$test.".not ready(interval)";
        /* Subtest 1a: not ready (sched interval not elapsed)
         * - pre: repos.first_entry != NULL AND
         *        repos.last_entry + repos.sched_interval_minutes < now()
         * - post: returned false
        */
        $now = time();
        $interval = $this->test_repository->sched_interval_minutes * 60;
        $this->test_repository->first_entry = $now - $interval;
        $this->test_repository->last_entry = $now;
        $date = date(LOG_DATE_FORMAT,$now);
        $this->test_repository->get_log()->end_time = $date;
        test_assertion(!$this->test_repository->is_ready_for_import());

        $_SESSION['test']=$test.".not ready(busy)";
        /* Subtest 1b: not ready (harvest in progress)
         * - pre: repos.first_entry != NULL AND
         *        repos.log.start != NULL AND repos.log.end == NULL
         * - post: returned false
        */
        $now = time();
        $interval = $this->test_repository->sched_interval_minutes * 60;
        $this->test_repository->first_entry = $now - $interval;
        $this->test_repository->last_entry = $now;
        $date = date(LOG_DATE_FORMAT,$now);
        $this->test_repository->get_log()->end_time = $date;
        test_assertion(!$this->test_repository->is_ready_for_import());

        /* Subtest 2: ready
         * - pre:  repos.first_entry == NULL OR
         *         repos.last_entry + repos.sched_interval_minutes >= now()
         * - post: returned true
        */
        $_SESSION['test']=$test.".ready(NULL)";
        $this->test_repository->first_entry = null;
        $this->test_repository->last_entry = null;
        $this->test_repository->get_log()->end_time = null;
        test_assertion($this->test_repository->is_ready_for_import());

        $_SESSION['test']=$test.".ready(interval elapsed)";
        $this->test_repository->first_entry = $now - 60;
        $this->test_repository->last_entry = $now;
        $this->test_repository->get_log()->end_time = $date;

        test_assertion($this->test_repository->is_ready_for_import($now+$interval));

        $_SESSION['test']=$test;
    }

    /**
     * start_harvest takes a mode ('in' or 'out' and and array of import counts
     * Need to test each completion status and essential import counts
     */
    public function test_start_harvest() {
//        var_dump('start_harvest started with',$this->test_repository);
        if ($this->test_repository == null ||
           stripos($this->test_repository->name,'test_import') === FALSE)
        {
           $this->test_repository = self::createValidImportRepository();
        }

        $test = $_SESSION['test'];
        $_SESSION['test']=$test.".first harvest";
        /* Subtest 1: First harvest for repository
         * - pre: repos is ready (null case)
         * - post: repos.harvest_log record opened and saved to DB
        */
        $this->test_repository->first_entry = null;
        $this->test_repository->last_entry = null;
        $this->test_repository->get_log()->end_time = null;
        try {
            $this->test_repository->start_harvest('test','in');
            // TODO: a more robust test would also verify log entry in database
            test_assertion($this->test_repository->get_log()->status == 'started');
        } catch (Exception $e) {
            error_log("Unexpected exception: ".$e->getMessage());
            test_assertion(false);
        }

        $_SESSION['test']=$test.".start before end";
        /* Subtest 2: ERROR: Start called before end
         * - pre: repos is ready (elapsed interval case)
         *        import is already started
         * - post: TBD: what return or exception should be emitted?
        */
        try {
            $this->test_repository->start_harvest('test','in');
            test_assertion(false);
        } catch (RuntimeException $rte) {
            test_assertion(stripos($rte->getMessage(),'Invalid start request')===0);
        } catch (Exception $e){
            test_assertion(false);
        }
        $_SESSION['test']=$test;
    }

    /**
     * end_harvest takes a status and and array of import counts
     * Need to test each completion status and essential import counts
     */
    private function start_harvest($mode,$dir) {
            try {
                error_log("...starting harvest...");
                $this->test_repository->start_harvest($mode,$dir);
                // TODO: a more robust test would also verify log entry in database
                if (!$this->test_repository->get_log()->status == 'started') {
                    throw new Exception('invalid log status');
                }
            } catch (Exception $e) {
                error_log("start failed: ".$e->getMessage()."\n");
                test_assertion(false);
            }
    }

    private function increment_firstlast_by_secs(&$counts,$secs=1) {
        $first = strtotime($counts['first_entry']) + $secs;
        $last = strtotime($counts['last_entry']) + $secs;
        $counts['first_entry'] = gmdate(UTC_DATE_FORMAT,$first);
        $counts['last_entry'] = gmdate(UTC_DATE_FORMAT,$last);
    }
    
    public function test_end_harvest() {
        $counts = array(
                    'st2'=>array( 'pfif_person_count'=>0,
                                  'pfif_note_count'=>0),
                    'st3'=>array('pfif_person_count'=>300,
                                 'pfif_note_count'=>300,
                                 'first_entry'=>'2010-01-01T00:03:00Z',
                                 'last_entry'=>'2010-01-01T00:03:01Z',
                                 'last_entry_count'=>1,
                                 'images_in'=>300,
                                 'images_retried'=>300,
                                 'images_failed'=>0),
                    'st4.1'=>array('pfif_person_count'=>1,
                                 'pfif_note_count'=>1,
                                 'first_entry'=>'2010-01-01T00:04:01Z',
                                 'last_entry'=>'2010-01-01T00:04:02Z',
                                 'last_entry_count'=>1,
                                 'images_in'=>1,
                                 'images_retried'=>0,
                                 'images_failed'=>0),
                    'st4.2'=>array('pfif_person_count'=>2,
                                 'pfif_note_count'=>1,
                                 'first_entry'=>'2010-01-01T00:04:02Z',
                                 'last_entry'=>'2010-01-01T00:04:03Z',
                                 'last_entry_count'=>1,
                                 'images_in'=>2,
                                 'images_retried'=>1,
                                 'images_failed'=>0),
                    'st4.3'=>array('pfif_person_count'=>3,
                                 'pfif_note_count'=>1,
                                 'first_entry'=>'2010-01-01T00:04:03Z',
                                 'last_entry'=>'2010-01-01T00:04:04Z',
                                 'last_entry_count'=>1,
                                 'images_in'=>2,
                                 'images_retried'=>1,
                                 'images_failed'=>1),
                    'st4.4'=>array('pfif_person_count'=>4,
                                 'pfif_note_count'=>1,
                                 'first_entry'=>'2010-01-01T00:04:04Z',
                                 'last_entry'=>'2010-01-01T00:04:05Z',
                                 'last_entry_count'=>3,
                                 'images_in'=>2,
                                 'images_retried'=>1,
                                 'images_failed'=>2)
                  );

        $this->test_repository = null;
        $this->test_repository = self::createValidImportRepository('test_import_end1');
        // var_dump('test_import_end1',$this->test_repository);

        $test = $_SESSION['test'];
        $_SESSION['test']=$test.".invalid";
        /* Subtest 1: end called before start
         * - pre: repos idle
         * - post: Invalid end request exception thrown
        */
        try {
            $this->test_repository->end_harvest(true);
            test_assertion(false);
        } catch (RuntimeException $rte) {
            test_assertion(stripos($rte->getMessage(),'Invalid end request')===0);
        } catch (Exception $e){
            error_log("Unexpected exception: ".$e->getMessage()."\n");
            test_assertion(false);
        }

        $_SESSION['test']=$test.".error";
        /* Subtest 2: end with status 'error' + counts
         * - pre: harvest started
         * - post: harvest ended with error status
         *         repository record updated in DB
         *         log record updated eith 'error' status and time in DB
        */
        $this->start_harvest('test','in');

        try {
            error_log("...ending harvest...");
            $this->test_repository->end_harvest(false,$counts['st2']);
            // TODO: a more robust test would also verify log entry in database
            test_assertion($this->test_repository->get_log()->status == 'error');
        } catch (Exception $rte) {
            error_log("Unexpected exception: ".$e->getMessage()."\n");
            test_assertion(false);
        }

        $_SESSION['test']=$test.".paused/completed";
        /* Subtest 3: end with status 'paused' + counts
         * - pre: harvest started
         *        time remaining before log_granularity reached
         * - post: harvest ended
         *         repository record updated in DB
         *         log record updated with 'paused' status and time in DB
        */
        $this->test_repository = null;
        $this->test_repository = self::createValidImportRepository('test_import_end2');
        $this->test_repository->sched_interval_minutes = 1;
        $this->test_repository->log_granularity = '00:01:00';
//        var_dump('test_import_end2',$this->test_repository);

        for ($ii = 0; $ii < 2; $ii++) {
          $this->start_harvest('test','in');
          sleep(1);
          try {
            error_log("...ending harvest...");
            $this->test_repository->end_harvest(true,$counts['st3']);
            // TODO: a more robust test would also verify log entry and counts in database
                if ($ii%2 == 0) {
                    test_assertion($this->test_repository->get_log()->status == 'paused');
                    error_log("...waiting 1 minute for next harvest...");
                    $this->increment_firstlast_by_secs($counts['st3'],1);
//                    var_dump('first',$counts['st3']['first'],'last',$counts['st3']['last']);
                    sleep(60);
                } else {
                    test_assertion($this->test_repository->get_log()->status == 'completed');
                }
           } catch (Exception $rte) {
            error_log("Unexpected exception: ".$e->getMessage()."\n");
            test_assertion(false);
          }
        }

        $_SESSION['test']=$test.".completed.1";
        /* Subtest 4: end with status 'completed' + counts
         * - pre: harvest started
         *        time remaining before log_granularity reached
         * - post: harvest ended
         *         repository record updated in DB
         *         log record updated eith 'paused' status and time in DB
        */
        $this->test_repository->log_granularity = '00:02:00';
        for ($ii = 1; $ii < 5; $ii++) {
            error_log("...waiting 1 minute for next harvest...");
            sleep(60);
            $this->start_harvest('test','in');
            sleep(1);
            try {
                error_log("...ending harvest...\n");
                $this->test_repository->end_harvest(true,$counts['st4.'.($ii)]);
                // TODO: a more robust test would also verify multiple log entries and counts in database
                if ($ii%3 == 0) {
                    test_assertion($this->test_repository->get_log()->status == 'completed');
                } else {
                    test_assertion($this->test_repository->get_log()->status == 'paused');
                }
            } catch (Exception $rte) {
                error_log("Unexpected exception: ".$e->getMessage()."\n");
                test_assertion(false);
            }
            $_SESSION['test']=$test.".completed.".($ii);
        }
        $_SESSION['test']=$test;
    }

    public function test_start_harvest_multi_log() {
        $test = $_SESSION['test'];
        $_SESSION['test']=$test.".first harvest (open log)";
        /* Subtest 1: First harvest for repository
         * - pre: repos is ready (null case)
         * - post: repos.harvest_log entry opened and saved in DB?
        */
        // $this->test_repository->start_harvest('scheduled','in');
        test_assertion(false);

        $_SESSION['test']=$test.".ERROR: second harvest before ready";
        /* Subtest 2: start called before schedule interval elapsed
         * - pre: first harvest ended with status 'paused'
         *        repos sched_interval has not elapsed since first harvest
         * - post: RuntimeException thrown with Invalid request message
        */
        // $this->test_repository->end_harvest('started');
        try {
            $this->test_repository->start_harvest('test','in');
        } catch (RuntimeException $rte) {
            test_assertion(stripos($e->getMessage(),'Invalid start request')===0);
        } catch (Exception $e){
            test_assertion(false);
        }


        $_SESSION['test']=$test.".second harvest (update log)";
        /* Subtest 3: Second harvest for repository: : log granularity not reached
         * - pre: first harvest ended with status 'paused'
         *        repos is ready (elapsed interval case)
         * - post: repos.harvest_log updated and saved in DB?
        */
        sleep(60*$this->test_repository->sched_interval_minutes);
        // $this->test_repository->start_harvest('scheduled','in');
        test_assertion(false);

        $_SESSION['test']=$test.".third harvest (flush log)";
        /* Subtest 4: Third harvest for repository: log granularity reached
         * - pre: Second harvest ended with status 'paused'
         *        repos is ready (elapsed interval case)
         * - post: repos.harvest_log closed and saved in DB?
        */
        // $this->test_repository->end_harvest('started');
        sleep(60*$this->test_repository->sched_interval_minutes);
        // $this->test_repository->start_harvest('scheduled','in');
        // $this->test_repository->end_harvest('completed');
        test_assertion(false);
    }
    /*  Export Tests */

    public function test_is_ready_for_export() {
        $test = $_SESSION['test'];
        $_SESSION['test']=$test.".not ready";
        /* Subtest 1: not ready
         * - pre:
         * - post:
        */
        test_assertion(false);

        $_SESSION['test']=$test.".ready";
        /* Subtest 2: ready
         * - pre:
         * - post:
        */
        test_assertion(false);

        $_SESSION['test']=$test;
    }

    public function test_start_export() {
        $test = $_SESSION['test'];
        $_SESSION['test']=$test.".subtest 1";
        /* Subtest 1: TBD
         * - pre:
         * - post:
        */
        test_assertion(false);

        $_SESSION['test']=$test.".subtest 2";
        /* Subtest 2: TBD
         * - pre:
         * - post:
        */
        test_assertion(false);

        $_SESSION['test']=$test;
    }

    public function test_end_export() {
        $test = $_SESSION['test'];
        $_SESSION['test']=$test.".subtest 1";
        /* Subtest 1: TBD
         * - pre:
         * - post:
        */
        test_assertion(false);

        $_SESSION['test']=$test.".subtest 2";
        /* Subtest 2: TBD
         * - pre:
         * - post:
        */
        test_assertion(false);

        $_SESSION['test']=$test;
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