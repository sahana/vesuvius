CREATE TABLE `organization_district` (
  `OrgCode` varchar(100) NOT NULL default '',
  `DistrictName` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`DistrictName`,`OrgCode`)
) TYPE=MyISAM DEFAULT CHARSET=latin1; 


ALTER TABLE organization ADD COLUMN LastUpdate varchar(100) NOT NULL;

ALTER TABLE organization ADD COLUMN UntilDate varchar(100) NOT NULL;

ALTER TABLE organization ADD COLUMN IsSriLankan tinyint NOT NULL;

# Host: 192.168.101.14
# Database: erms
# Table: 'organization_sector'
# 
CREATE TABLE `organization_sector` (
  `OrgCode` varchar(100) NOT NULL default '',
  `Sector` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`OrgCode`,`Sector`)
) Type=MyISAM DEFAULT CHARSET=latin1; 


