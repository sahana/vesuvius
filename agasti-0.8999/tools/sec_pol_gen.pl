#!/usr/bin/perl

$argIndx = 1;

$arg = $ARGV[$argIndx];

if($arg =~ /(\W|\D)+/){

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
	<usercase name=\"$modSC\">
		<functions>
";

# Iterate through the files passed in as args if not null.
while($arg =~ /(\W|\D)+/){
	# print("ARG $arg\n");
	# open file
	open(INPUT,"<",$arg);
	while($record = <INPUT>){

		if($record =~ /shn_$modSC_.*\(\)/){
			$funcName = substr($&,0,(length($&)) -2);
			print OUTPUT "
			<function>$funcName</function>";
					
		}				
	}	
	# close file
	close(INPUT);
		
	# next file
	$argIndx=$argIndx+1;
	$arg = $ARGV[$argIndx];
}
print OUTPUT "	</functions>
		<!-- TODO : Add tables accessed by the above function -->
		<!--<tables>
				<table perm=\"crud\">tableName</table>
		</tables>-->";
		
print OUTPUT "\n	</usercase>";
print OUTPUT "\n</sec_policy>";
close(OUTPUT);
}else{
print("Usage is as follows.\n
sec_pol_gen.pl <module_short_code> <file1> [file2] [file3]\n
Where file1, file2, file3 are files to be scanned for functions.
");
}
