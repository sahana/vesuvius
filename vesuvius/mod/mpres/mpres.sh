# See Jira ticket PL-59 for why the "Kerberos" kludge below is necessary.
cd /opt/pl/mod/mpres/ ;
/usr/bin/php crontask.php | grep -v Kerberos >> ~/mpres.log 2>> ~/mpres.err ;
