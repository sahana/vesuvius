#!/usr/bin/perl

use strict;
use warnings;

die ('Usage: mysql2pgsql <mysql schema file>') unless (@ARGV == 1);

open MYSQL, $ARGV[0] or die ("can not open ". $ARGV[0]);

#flags
my $comment_block = 0;
my $tablename = "";
my $constraints = "";
while (<MYSQL>){
    # Comments
    $comment_block = 1 if /\/\*/;
    print $_ if($comment_block == 1) ;

    if($comment_block == 0){
        s/BIGINT NOT NULL AUTO_INCREMENT/BIGSERIAL/i;
        s/TINYINT/INT/i;
        s/DOUBLE/DECIMAL/i;
        s/INT\(1\)/BOOLEAN/i;
        s/BOOL(.*)DEFAULT 1/BOOL$1DEFAULT TRUE/i;
        s/BOOL(.*)DEFAULT 0/BOOL$1DEFAULT FALSE/i;
        s/BLOB/BYTEA/i;
        s/ENGINE=.*;/;/i;
        s/`//g;
        s/INT\(.*\)/INT/i; #thoes ugly int (11) etc
        #s/KEY
        $tablename = $1 if /CREATE TABLE (.*?) /;
        $constraints .= "\nCREATE INDEX $1 ON $tablename \($2\);\n" if /^\s+KEY (.*?)\s+\((.*?)\)\s*,/;
        $constraints .= "\nCREATE UNIQUE INDEX $1 ON $tablename \($2\);\n" if /^\s+UNIQUE KEY (.*?)\s+\((.*?)\)\s*,/;

        #sahana specific 
        s/PRIMARY KEY\s+(.*?)\,/PRIMARY KEY $1/i;
        
        print $_ unless (/DROP TABLE IF EXISTS|LOCK TABLE|UNLOCK TABLE|UNIQUE KEY|^\s+KEY/);
    }

    $comment_block = 0 if /\*\//;
}
print $constraints;

close (MYSQL);
