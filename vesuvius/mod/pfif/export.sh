#!/bin/bash
# Export unexported persons and notes.
cd /home/neve/v/mod/pfif
/usr/bin/php cronexport.php 1>> export.out 2>> export.out
