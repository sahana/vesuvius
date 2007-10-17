#!/usr/bin/perl

$argIndx = 1;

$arg = $ARGV[$argIndx];

#get module short code.
$modSC = $ARGV[0];

# create file in place.
open(OUTPUT,">","sec_policy.xml");
print OUTPUT "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?> \n
	<!-- 
	##################################################################################################################### 
	# IMPORTANT.													    # 
	# This is a generated file which contains all functions in a single usercase. Add additional usercases / functions # 
	# to match the module architecture. Also you will need to add the table permissions manually.			    # 
	# 														    # 
	#####################################################################################################################  
	-->	
			
<sec_policy 
	xmlns=\"http://www.sahana.lk/security/policy\"
	xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
	xsi:schemaLocation=\"http://www.sahana.lk/security/policy sec_policy.xsd\">  
	<usercase name=\"$modSC\">";

# Iterate through the files passed in as args if not null.
while($arg =~ /(\W|\D)+/){
	# print("ARG $arg\n");
	# open file
	open(INPUT,"<",$arg);
	while($record = <INPUT>){

		if($record =~ /shn_$modSC_.*\(\)/){
			$funcName = substr($&,0,(length($&)) -2);
			print OUTPUT "
		<funct id=\"$funcName\">
			<!-- TODO : Add tables accessed by this function -->
			<!--<tables>
				<table perm=\"crud\">tableName</table>
			</tables>-->
		</funct>";
					
		}				
	}	
	# close file
	close(INPUT);
		
	# next file
	$argIndx=$argIndx+1;
	$arg = $ARGV[$argIndx];
}
print OUTPUT "\n	</usercase>";
print OUTPUT "\n</sec_policy>";
close(OUTPUT);
print("DONE \n");

