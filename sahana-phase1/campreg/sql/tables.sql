# Host: 192.168.101.14
# Database: erms
# Table: 'camps_camp'
#
CREATE TABLE `camps_camp` (
  `CAMP_FAMILY` int(5) NOT NULL default '0',
  `CAMP_ID` int(5) NOT NULL auto_increment,
  `AREA_NAME` varchar(50) NOT NULL default '',
  `DIV_ID` int(5) NOT NULL default '0',
  `DIST_CODE` varchar(5) NOT NULL default '',
  `PROV_CODE` varchar(5) NOT NULL default '',
  `CAMP_NAME` varchar(50) NOT NULL default '',
  `CAMP_ACCESABILITY` varchar(255) default NULL,
  `CAMP_MEN` int(5) NOT NULL default '0',
  `CAMP_WOMEN` int(5) NOT NULL default '0',
  `CAMP_CHILDREN` int(5) NOT NULL default '0',
  `CAMP_TOTAL` int(11) default '0',
  `CAMP_CAPABILITY` varchar(255) default NULL,
  `CAMP_CONTACT_PERSON` varchar(100) default NULL,
  `CAMP_CONTACT_NUMBER` varchar(100) default NULL,
  `LAST_UPDATE_DATE` date NOT NULL default '0000-00-00',
  `CAMP_COMMENT` varchar(255) default NULL,
  `LAST_UPDATE_TIME` time NOT NULL default '00:00:00',
  PRIMARY KEY  (`CAMP_ID`)
) TYPE=MyISAM DEFAULT CHARSET=latin1;

# Host: 192.168.101.14
# Database: erms
# Table: 'camp_history'
#
CREATE TABLE `camp_history` (
  `HISTORY_ID` int(10) NOT NULL auto_increment,
  `CAMP_ID` int(5) NOT NULL default '0',
  `CAMP_MEN` int(5) default '0',
  `CAMP_WOMEN` int(5) default '0',
  `CAMP_CHILDREN` int(5) default '0',
  `CAMP_COMMENT` varchar(255) default '',
  `CAMP_FAMILY` int(5) default '0',
  `UPDATED_DATE` date NOT NULL default '0000-00-00',
  PRIMARY KEY  (`HISTORY_ID`)
) TYPE=MyISAM DEFAULT CHARSET=latin1 COMMENT='This includes the historical information for the camps data'; 



