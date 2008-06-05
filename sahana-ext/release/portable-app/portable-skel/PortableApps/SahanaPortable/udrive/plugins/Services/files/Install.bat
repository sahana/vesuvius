@echo off
echo
copy usr\local\mysql\bin\my-small.cnf c:\my.cnf
echo Installing Apache2 Service ...
rem C:/UniServX.X/usr/local/apache2/bin/Apache.exe -f C:/UniServX.X/usr/local/apache2/conf/httpd.conf -d C:/UniServerX.X/usr/local/apache2/bin/Apache.exe -f C:/UniServerX.X/usr/local/apache2/conf/httpd.conf -d

rem C:/UniServX.X/usr/local/apache2/. -k install -n "Apache2"
C:/UniServerX.X/usr/local/apache2/bin/Apache.exe -k install -n "Apache2"

echo Installing MySQL Service ...

rem C:/UniServX.X/usr/local/mysql/bin/mysqld-opt.exe --install
C:/UniServerX.X/usr/local/mysql/bin/mysqld-opt.exe --install

net start Apache2
net start MySQL
rem start udrive/home/admin/www/redirect.html
start C:/UniServerX.X/redirect.html
echo Now you can copy important data and use the server!
pause