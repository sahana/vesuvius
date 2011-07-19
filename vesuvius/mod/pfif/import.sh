#!/bin/bash
# Import the next batch (default is 200) of persons and notes.
cd /home/neve/public_html/pl/trunk/mod/mpr
/usr/bin/php pfif_cronimport.php person 1>> pfif_import.out 2>> pfif_import.out
/usr/bin/php pfif_cronimport.php note 1>> pfif_import.out 2>> pfif_import.out
