: Name: Start Server File
: Created By: The Uniform Server Development Team
: Edited Last By: Olajide Olaolorun (empirex)
: Edited By: Chamindra de Silva for Sahana installation
: Comment: After start, go to apanel directly.
: To Developers: Implemented %www%, and %apanel% :)

@echo off

rem use: start mysql console - to start mysql at server start and display console
rem use: start mysql - to start mysql at server start
rem use: start nomysql console - to display console

rem udrive\home\admin\program\pskill.exe Apache.exe c
rem ADDED
rem udrive\home\admin\program\pskill.exe mysqld-opt.exe c
subst w: /d


rem REMOVED: if errorlevel 2 goto :PAUSE
rem if not errorlevel 1 goto :STARTED

set Disk=%1

if "%Disk%"=="" set Disk=w

rem create the disk
subst %Disk%: "udrive"

if errorlevel 1 goto :HINT
set apachepath=\usr\local\apache2\
set apacheit=%Disk%:%apachepath%bin\Apache.exe -f %apachepath%conf\httpd.conf -d %apachepath%.
set programit=%Disk%:\home\admin\program\
set closeit=%programit%close.bat %Disk%

%Disk%:
cd \usr\local\php
start \usr\local\mysql\bin\mysqld-opt.exe --defaults-file=/usr/local/mysql/bin/my-small.cnf
CLS
echo The server is working on the disk %Disk%:\ [http/127.0.0.1/apanel/]
set www=\www\
set apanel=\home\admin\www\
rem REMOVED 
rem start %apanel%\redirect.html

if "%3"=="console" goto :CONSOLE
start %programit%uniserv.exe "%apacheit%" "%closeit%"
goto :END

:CONSOLE
%apacheit%
%closeit%
goto :END

:HINT
CLS
echo The disk %Disk% is busy. Use start.bat [disk letter]
goto :PAUSE

:STARTED
CLS
echo ERROR!!! 
echo One of the instances of Apache server is started. Use stop.bat

:PAUSE
echo .
rem pause

:END
rem pause
