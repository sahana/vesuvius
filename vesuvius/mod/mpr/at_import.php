#!/opt/php-5.3.1/sapi/cli/php
<?php
    // TODO: start a fallback job to run in the event cronimport encounteres a fatal error. Cancel it if cronimport completes successfully.
    echo "timezone:".date_default_timezone_get()."\n";
    $now = time();
    print "\nRunning script at ".strftime('%D %T %n',$now)."\n";

    include('pfif_cronimport.php');

    $next = $_SESSION['next_harvest'];
    $now = time();
    if ($next - $now <= 15 ) {
        print "ERROR: next harvest must be later than current time: $next";
        $next = $now + 120;
    }
    $next_str = strftime('%Y%m%d%H%M',$next);
    $cmd = 'at -s -f /home/ccornwell/public_html/pl/trunk/mod/mpr/at_job.sh -t ';
    $cmd .= $next_str;
    $cmd .= " > ../../www/tmp/pfif_cache/logs/import_".$next_str.".log 2>&1";

    print "\nsubmitting:".$cmd."\n";
    $sts = exec($cmd);
    print "exec status = $sts \n";
    ?>
