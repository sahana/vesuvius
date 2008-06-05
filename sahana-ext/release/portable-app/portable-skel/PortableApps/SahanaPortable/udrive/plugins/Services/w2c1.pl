# The Uniform Server Service Install Tool
# By The Uniform Server Development Team
# Version 1.5

print "This script will install Uniform Server as a Windows service!\n";

#$pathc="C:/UniServerX.X";
$pathc="c:/UniServerX.X";

#$skip=(" gif jpg bmp pcx tif zip gz rar tar cab ha exe com dll hlp xls doc pdf ps dbf png log MYD frm MYI pm so var ");
$paterns="\/www|\/home|\/cgi-bin|\/usr|\/tmp|\/htpasswd|\/scgi-bin|\/plugins";
$use=".conf|.cgi|.pl|.bat|.cnf|.ini|Config.pm";

mkdir ("$pathc");

convert ("../../","$pathc");
#coppy ("./files/Uninstall.bat", "$pathc/Uninstall.bat");
convert ("./files","$pathc");
coppy ("../../home/admin/www/redirect.html", "$pathc/redirect.html");
#coppy ("./files/index.html","$pathc/home/admin/www/index.html");
coppy ("$pathc/usr/local/PHP/php.ini", "$pathc/usr/local/Apache2/bin/php.ini");
coppy ("$pathc/usr/local/PHP/libmysql.dll", "$pathc/usr/local/Apache2/bin/libmysql.dll");
coppy ("$pathc/usr/local/mysql/bin/my-small.cnf", "c:/my.cnf");
print "Installing Apache2 as service ...";
$res=`$pathc/usr/local/apache2/bin/Apache.exe -f $pathc/usr/local/apache2/conf/httpd.conf -d $pathc/usr/local/apache2/. -k install -n "Apache2"`;
print " done!\n";
print "Installing MySQL as service ...";
$res=`$pathc/usr/local/mysql/bin/mysqld-opt.exe  --install`;
print " done!\n";
print "Starting Apache2 ...";
#$res=`$pathc/USR/LOCAL/APACHE2/BIN/APACHE.EXE -n Apache2 -k start`;
$res=`net start Apache2`;
print " done!\n";
print "starting MySQL ...";
$res=`net start mysql`;
print " done!\n";
print "Have a fun\n";

$res=`start $pathc/home/admin/www/redirect.html`;

exit;

# usage convert (path,path1);
sub convert {
 my @names;
 my $name;
 my ($path)=$_[0] ;
 my ($path1)=$_[1] ;
 opendir DIR,"$path";
 $name=readdir DIR;
 $name=readdir DIR;

 @names=readdir DIR;
 closedir DIR;
 foreach $name (@names){
  if (-d "$path/$name"){mkdir ("$path1/$name"); convert ("$path/$name","$path1/$name")};
  if (!(-d "$path/$name")&&($name=~ /($use)$/)){
   print "$path/$name - converting ...";
   open (FILE,"$path/$name");
   binmode FILE;
   read FILE,$lines,100000;
   close (FILE);
   $lines=~ s/(\W)($paterns)/$1$pathc$2/g;
   open (FILE,">$path1/$name");
   binmode FILE;
   print FILE $lines;
   close (FILE);
   print " done!\n";
   } else {
   print "$path/$name - transferring ...";
   coppy ("$path/$name", "$path1/$name");
   print " done!\n";
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
