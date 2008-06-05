@echo off
set Disk=%1
IF "%Disk%"=="" set Disk=w
%Disk%:\home\admin\program\pskill.exe mysqld-opt.exe
IF ERRORLEVEL 1 goto nomysql
%Disk%:\usr\local\mysql\bin\mysqladmin.exe --character-sets-dir="/usr/local/mysql/share/charsets/" --user=root --password=root shutdown
:nomysql
subst %Disk%: /D