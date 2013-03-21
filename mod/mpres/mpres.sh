# setup this script to run with cron to automate the ingesting of email person reports...

cd /opt/pl/mod/mpres/ ;
/usr/bin/php crontask.php > /dev/null 2>&1 ;
