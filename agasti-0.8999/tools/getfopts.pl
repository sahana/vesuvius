#!/usr/bin/perl
#
# Perl Helper Script to extract field_options descriptions
# from Sahana SQL files, useful to create the PO template
#
# This creates PHP code using _("") as gettext-Alias for each
# field_options description, and writes it to stdout
#
# author: dominic

print "<?php\n";

while( <STDIN> ) {
  if ( /.*INSERT\s*INTO\s*field_options.*VALUES\s*\(.*,\s*\'([^']*)\'\s*\)\s*;/ ) {
    print "print(_(\"$1\"));\n";
  }
}

print "?>\n";
