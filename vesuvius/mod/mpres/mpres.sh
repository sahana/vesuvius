# See Jira ticket PL-59 for why the "Kerberos" kludge below is necessary.
cd /opt/pl/mod/mpres/ ;
/usr/bin/php crontask.php | grep -v Kerberos >> /pl/tmp/mpres.log 2>> /pl/tmp/mpres.err ;
