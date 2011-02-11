#!/opt/php-5.3.1/sapi/cli/php
<?php
    $now = time();
    print "Running script at ".strftime('%D %T %n',$now);
    $next = $now + 120;
    $cmd = 'at -s -f /home/ccornwell/public_html/hepl/mod/mpr/at_job.sh -t ';
    $cmd .= strftime('%Y%m%d%H%M',$next);

    $return_var = exec($cmd);
    print "exec returns: $return_var \n";
?>