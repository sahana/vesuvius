CREATE TABLE `organization_district` (
  `OrgCode` varchar(100) NOT NULL default '',
  `DistrictName` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`DistrictName`,`OrgCode`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1; 


ALTER TABLE organization ADD COLUMN LastUpdate varchar(100) NOT NULL;
