/*
MySQL Backup
Source Host:           192.168.101.14
Source Server Version: 4.1.8-nt
Source Database:       erms
Date:                  2005/01/17 18:21:17
*/

SET FOREIGN_KEY_CHECKS=0;
use erms;
#----------------------------
# Table structure for camp_history
#----------------------------
CREATE TABLE `camp_history` (
  `CAMP_TOTAL` int(5) NOT NULL default '0',
  `HISTORY_ID` int(10) NOT NULL auto_increment,
  `CAMP_ID` int(5) NOT NULL default '0',
  `CAMP_MEN` int(5) default '0',
  `CAMP_WOMEN` int(5) default '0',
  `CAMP_CHILDREN` int(5) default '0',
  `CAMP_COMMENT` varchar(255) default '',
  `CAMP_FAMILY` int(5) default '0',
  `UPDATED_TIME` time NOT NULL default '00:00:00',
  `UPDATED_DATE` date NOT NULL default '0000-00-00',
  PRIMARY KEY  (`HISTORY_ID`)
) TYPE=MyISAM COMMENT='This includes the historical informattion for the camps data';
#----------------------------

ALTER TABLE CAMPS_CAMP ADD CAMP_FAMILY int(5) NOT NULL;
ALTER TABLE CAMPS_CAMP ADD LAST_UPDATE_DATE date NOT NULL;
ALTER TABLE CAMPS_CAMP ADD LAST_UPDATE_TIME time NOT NULL;