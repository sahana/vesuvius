Trinity Volunteer Management and Volunteer Registration Installation Notes
Developed by Trinity College Computer Science Department.
Developers: Jonathan Damon, Ralph Morelli, Trishan de Lanerolle, Jonathan Raye, Kalin Gochev
Contributors: Antonio Alcorn, Heidi Ellis, Alex Lanstein, Candyce Young-Fields,Turner Hayes, Bach Dao 

Run the db_setup.sql script (from the ins folder) to create vm_ tables and deployment data in your sahana database. 
(must add a statement specifying which database to add to at beginning of file, ie. use sahana_dev;)
(we use this command to run the script.  $mysql -u sahana_admin -p < db_setup.sql)
text
~ After executing the script change the config value found in Sahana's administration->config values menu called mod_vm_hack to 1, if you do not have ACL enabled. 

COMMIT LOG:
17/04/2007: Added revised admin.inc file to cvs 
