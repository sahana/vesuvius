#!/usr/bin/perl

require header;
require secure;

if ($ENV{'QUERY_STRING'}eq"F"){
	print "
	<div id=\"main\">
 	<h2>&#187; Cleaning Server</h2>
 	<h3>Cleaned /www/ Directory</h3>
 	<p>
 	Server has been cleaned!
 	</p>
 	</div>";

 	deletex ("/www");
 	coppy("/home/admin/www/favicon.ico","/www/favicon.ico");
 	coppy("/home/admin/www/redirect.html","/www/index.html");
 	coppy("/home/admin/www/.htaccess","/www/.htaccess");
	mkdir("/www/images/");
 	coppy("/home/admin/www/images/logo.jpg","/www/images/logo.jpg");
} 

else {
 	print "
 	<div id=\"main\">
 	<h2>&#187; Clean Server</h2>
 	<h3>Clean /www/ Directory</h3>
 	<p>
 	This will delete contents of \\www\\ folder
 	<br />
 	Are you sure: <a href=\"$ENV{SCRIPT_NAME}?F\">Yes, Continue</a>
 	</p>
 	</div>";
ENDDD
}

require footer;
exit;

# usege deletex (path);
sub deletex {
 	my @names;
 	my $name;
 	my ($path)=$_[0] ;
 	opendir DIR,"$path";
 	$name=readdir DIR;
 	$name=readdir DIR;
 	@names=readdir DIR;
 	closedir DIR;

 	foreach $name (@names){
		if (-d "$path/$name"){deletex ("$path/$name"); rmdir ("$path/$name");};

		@namess=split(/\./, $name);

		if (!(-d "$path/$name")&&(!($skip=~ /@namess[$namess+1]/)||(@namess[$namess+1]eq''))){
			unlink "$path/$name";
   		}
  	}
}

sub coppy {
	open (FILE,"$_[0]");
   	binmode FILE;
   	@lines=<FILE>;
   	close (FILE);
   	open (FILE,">$_[1]");
   	binmode FILE;
   	print FILE @lines;
   	close (FILE);
}

