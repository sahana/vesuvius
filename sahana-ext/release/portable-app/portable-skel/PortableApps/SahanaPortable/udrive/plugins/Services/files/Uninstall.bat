@echo off
echo
net stop MySQL
net stop Apache2
usr\local\apache2\bin\Apache.exe -k uninstall -n "Apache2"
echo Uninstalling MySQL Service ...
usr\local\mysql\bin\mysqld-opt.exe --remove
del C:\my.cnf
echo Now you can copy important data and delete the server root directory
pause