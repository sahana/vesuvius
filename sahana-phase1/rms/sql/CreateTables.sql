DROP TABLE `requestfulfill`;
DROP TABLE `requestdetail`;
DROP TABLE `requestheader`;

DROP TABLE `category`;
DROP TABLE `district`;
DROP TABLE `organization`;
DROP TABLE `orgtype`;
DROP TABLE `orgsubtype`;
DROP TABLE `fulfillstatus`;
DROP TABLE `priority`;
DROP TABLE `requeststatus`;
DROP TABLE `requestunit`;

DROP TABLE `user`;
DROP TABLE `sitetype`;

drop table CAMPS_CAMP;
drop table CAMPS_AREA;
drop table CAMPS_DISTRICT;
drop table CAMPS_DIVISION;

drop table CAMPS_PROVINCE;


CREATE TABLE `category` (
  `CatCode` varchar(20) NOT NULL default '',
  `CatDescription` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`CatCode`)
) TYPE=MyISAM;


CREATE TABLE `district` (
  `DistrictCode` varchar(20) NOT NULL default '',
  `Name` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`DistrictCode`)
) TYPE=MyISAM;



CREATE TABLE `orgtype` (
  `OrgType` varchar(20) NOT NULL default '',
  `Name` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`OrgType`)
) TYPE=MyISAM;


CREATE TABLE `orgsubtype` (
  `OrgSubType` varchar(20) NOT NULL default '',
  `Name` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`OrgSubType`)
) TYPE=MyISAM;

CREATE TABLE `organization` (
  `OrgType` varchar(20) NOT NULL default '',
  `OrgSubType` varchar(20) default '',
  `OrgCode` varchar(10) NOT NULL default '0',
  `ContactPerson` varchar(100) NOT NULL default '',
  `OrgName` varchar(100) NOT NULL default '',
  `Status` tinyint(1) NOT NULL default '0',
  `OrgAddress` varchar(200) NOT NULL default '',
  `ContactNumber` varchar(255) NOT NULL default '',
  `EmailAddress` varchar(100) NOT NULL default '',
  `CountryOfOrigin` varchar(100) NOT NULL default '',
  `FacilitiesAvailable` varchar(255) default '',
  `WorkingAreas` varchar(255) default '',
  `Comments` varchar(255) default '',
  PRIMARY KEY  (`OrgCode`)
) TYPE=InnoDb;



CREATE TABLE `fulfillstatus` (
  `status` varchar(20) NOT NULL default '0',
  `Description` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`status`)
) TYPE=MyISAM;


CREATE TABLE `priority` (
  `Priority` varchar(10) NOT NULL default '0',
  `Description` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`Priority`)
) TYPE=MyISAM;



CREATE TABLE `requestheader` (
  `RequestId` int(11) NOT NULL auto_increment,
  `OrgCode` varchar(10) NOT NULL default '',
  `CreateDate` date NOT NULL default '0000-00-00',
  `RequestDate` date NOT NULL default '0000-00-00',
  `CallerName` varchar(50) NOT NULL default '',
  `CallerAddress` varchar(100) NOT NULL default '',
  `CallerContactNo` varchar(50) default '',
  `Description` varchar(200) default '',
  `SiteType` varchar(20) NOT NULL default '',
  `SiteDistrict` varchar(5) NOT NULL default '',
  `SiteArea` varchar(50) default '',
  `SiteName` varchar(50) default '',
  PRIMARY KEY  (`RequestId`)
) TYPE=InnoDb;


CREATE TABLE `requestdetail` (
  `RequestDetailId` int(11) NOT NULL auto_increment,
  `RequestId` int(11) NOT NULL default '0',
  `Category` varchar(5) NOT NULL default '',
  `Item` varchar(100) NOT NULL default '',
  `Description` varchar(100) default '',
  `Unit` varchar(10) NOT NULL default '',
  `Quantity` int(11) NOT NULL default '0',
  `Priority` varchar(20) NOT NULL default '0',
  `Status` varchar(10) NOT NULL default '',
  PRIMARY KEY  (`RequestDetailId`),
  FOREIGN KEY (RequestId) REFERENCES requestheader(RequestId)
) TYPE=InnoDb;


CREATE TABLE `requestfulfill` (
  `FulfullId` int(11) NOT NULL auto_increment,
  `OrgCode` varchar(10) NOT NULL default '',
  `RequestDetailId` int(11) NOT NULL default '0',
  `ServiceQty` int(11) NOT NULL default '0',
  `Status` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`FulfullId`),
  FOREIGN KEY (RequestDetailId) REFERENCES requestdetail(RequestDetailId)
) TYPE=InnoDb;


CREATE TABLE `requeststatus` (
  `Status` varchar(10) NOT NULL default '',
  `Description` varchar(10) NOT NULL default ''
) TYPE=MyISAM;


CREATE TABLE `requestunit` (
  `Unit` varchar(10) NOT NULL default '0',
  PRIMARY KEY  (`Unit`)
) TYPE=MyISAM;


CREATE TABLE `sitetype` (
  `SiteTypeCode` varchar(10) NOT NULL default '',
  `SiteType` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`SiteTypeCode`)
) TYPE=MyISAM;


CREATE TABLE `user` (
  `UserName` varchar(20) NOT NULL default '',
  `Password` varchar(100) NOT NULL default '0',
  `OrgCode` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`UserName`),
  FOREIGN KEY (OrgCode) REFERENCES Organization(OrgCode)
) TYPE=MyISAM;

create table camps_province (
 PROV_CODE varchar (5) not null,
 PROV_NAME varchar (50) not null,
 primary key (PROV_CODE)
) type=InnoDB;

-- ============================================
-- [02] Create Table: 
-- ============================================
create table camps_district (
 DIST_CODE varchar (5) not null,
 DIST_NAME varchar (50) not null,
 PROV_CODE varchar (5) not null,
 foreign key (PROV_CODE) references CAMPS_PROVINCE (PROV_CODE),
 primary key (DIST_CODE)
) type=InnoDB;

-- ============================================
-- [03] Create Table:  
-- ============================================
create table camps_division (
 DIV_ID int (5) not null,
 DIV_NAME varchar (50) not null,
 DIST_CODE varchar (5) not null,
 foreign key (DIST_CODE) references CAMPS_DISTRICT (DIST_CODE),
 primary key (DIV_ID)
) type=InnoDB;

-- ============================================
-- [04] Create Table: 
-- ============================================
create table camps_area (
 AREA_ID int (10) not null,
 AREA_NAME varchar (50) not null,
 DIV_ID int (5) not null,
 foreign key (DIV_ID) references CAMPS_DIVISION (DIV_ID),
 primary key (AREA_ID)
) type=InnoDB;

-- ============================================
-- [05] Create Table: 
-- big varchar value given for contact 
-- person/number to facilitate to enter more details
-- ============================================
CREATE TABLE `camps_camp` (
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
  `CAMP_CAPABILITY` varchar(255) default NULL,
  `CAMP_CONTACT_PERSON` varchar(100) default NULL,
  `CAMP_CONTACT_NUMBER` varchar(100) default NULL,
  `CAMP_COMMENT` varchar(255) default NULL,
  PRIMARY KEY  (`CAMP_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1; 


