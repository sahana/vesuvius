#!/bin/bash
# Sync PFIF data with some Sahana tables.
cd /home/neve/public_html/pl/trunk/mod/mpr
/usr/bin/php pfif_sync.php 1>> pfif_sync.out 2>> pfif_sync.out
