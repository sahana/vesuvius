# Host: 192.168.101.14
# Database: erms
# Table: 'burial_site_detail'
#
CREATE TABLE `burial_site_detail` (
  `burial_site_code` int(10) NOT NULL auto_increment,
  `province` varchar(5) NOT NULL default '',
  `district` varchar(20) NOT NULL default '',
  `division` int(5) NOT NULL default '0',
  `area` varchar(200) NOT NULL default '',
  `sitedescription` varchar(200) NOT NULL default '',
  `burialdetail` varchar(200) default '',
  `body_count_total` int(5) unsigned default '0',
  `body_count_men` int(5) unsigned default '0',
  `body_count_women` int(5) default '0',
  `body_count_children` int(5) unsigned default '0',
  `gps_lattitude` varchar(20) default '',
  `gps_longitude` varchar(20) default '',
  `authority_person_name` varchar(100) NOT NULL default '',
  `authority_name` varchar(50) NOT NULL default '',
  `authority_person_rank` varchar(100) NOT NULL default '',
  `authority_reference` varchar(100) default '',
  PRIMARY KEY  (`burial_site_code`)
) TYPE=MyISAM COMMENT='Details of burial sites'; 

