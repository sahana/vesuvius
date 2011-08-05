#!/bin/bash
# Import the next batch (default is 200) of persons and notes.
cd /home/neve/v/mod/pfif
/usr/bin/php cronimport.php person 1>> import.out 2>> import.out
/usr/bin/php cronimport.php note 1>> import.out 2>> import.out
