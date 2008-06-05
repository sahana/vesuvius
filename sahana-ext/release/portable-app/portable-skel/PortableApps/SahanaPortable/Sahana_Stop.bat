: Name: Stop Server File
: Created By: The Uniform Server Development Team
: Edited Last By: Olajide Olaolorun (empirex)
: Comment: Tara's new syetm of shutting down the server
: To Developers: Implemented a new system of server shutdown

@echo off
udrive\home\admin\program\pskill.exe Apache.exe c

rem ADDED
udrive\home\admin\program\pskill.exe mysqld-opt.exe c

subst w: /d

