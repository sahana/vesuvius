#!/bin/bash
# Import the next batch (default is max 200) of persons and notes.
this_dir=`dirname $0`
log_dir=$this_dir/../../www/tmp/pfif_logs

cd $this_dir
while :
do
	/usr/bin/php cronimport.php person 1>> $log_dir/import.out 2>> $log_dir/import.err
	/usr/bin/php cronimport.php note 1>> $log_dir/import.out 2>> $log_dir/import.err
	sleep 5
done
