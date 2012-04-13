#!/bin/bash
# Import the next batch (default is 200) of persons and notes.
this_dir=`dirname $0`
log_dir=/opt/pl/www/tmp/pfif_logs

cd $this_dir
/usr/bin/php cronimport.php person 1>> $log_dir/import.out 2>> $log_dir/import.err
/usr/bin/php cronimport.php note 1>> $log_dir/import.out 2>> $log_dir/import.err
