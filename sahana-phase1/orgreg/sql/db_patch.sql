CREATE TABLE `organization_district` (
  `OrgCode` varchar(100) NOT NULL default '',
  `DistrictName` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`DistrictName`,`OrgCode`)
) TYPE=MyISAM; 


ALTER TABLE organization ADD COLUMN LastUpdate date NOT NULL default '0000-00-00';
ALTER TABLE organization ADD COLUMN UntilDate date NOT NULL default '0000-00-00';
ALTER TABLE organization ADD COLUMN IsSriLankan tinyint NOT NULL;


UPDATE organization SET LastUpdate='2005-01-19';
UPDATE organization SET UntilDate ='2005-12-31';


# Host: 192.168.101.14
# Database: erms
# Table: 'organization_sector'
# 
CREATE TABLE `organization_sector` (
  `OrgCode` varchar(100) NOT NULL default '',
  `Sector` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`OrgCode`,`Sector`)
) TYPE=MyISAM; 


