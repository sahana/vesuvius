#!/bin/bash
# Export unexported persons and notes.
this_dir=`dirname $0`
log_dir=/opt/pl/www/tmp/pfif_logs

cd $this_dir
/usr/bin/php cronexport.php 1>> $log_dir/export.out 2>> $log_dir/export.err
