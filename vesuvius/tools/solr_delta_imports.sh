#!/bin/sh
# Perform SOLR delta updates forever. No logging (check /opt/solr/logs).
while :
do
	/usr/bin/curl "http://localhost:8983/solr/dataimport?command=delta-import" > /dev/null 2>&1
	sleep 5
done
