-- MySQL dump 9.11
--
-- Host: localhost    Database: erms
-- ------------------------------------------------------
-- Server version	4.0.23_Debian-1-log

--
-- Table structure for table `tblaccesslevels`
--

DROP TABLE IF EXISTS `tblaccesslevels`;
CREATE TABLE `tblaccesslevels` (
  `AccessLevels` varchar(20) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblaccesslevels`
--


/*!40000 ALTER TABLE `tblaccesslevels` DISABLE KEYS */;
LOCK TABLES `tblaccesslevels` WRITE;
INSERT INTO `tblaccesslevels` VALUES ('PAGE'),('ADD'),('EDIT'),('DELETE'),('SEARCH'),('VIEW');
UNLOCK TABLES;
/*!40000 ALTER TABLE `tblaccesslevels` ENABLE KEYS */;

--
-- Table structure for table `tblaccessmodules`
--

DROP TABLE IF EXISTS `tblaccessmodules`;
CREATE TABLE `tblaccessmodules` (
  `ModuleId` int(11) default NULL,
  `ModuleName` varchar(50) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblaccessmodules`
--


/*!40000 ALTER TABLE `tblaccessmodules` DISABLE KEYS */;
LOCK TABLES `tblaccessmodules` WRITE;
INSERT INTO `tblaccessmodules` VALUES (1,'Assistance Database'),(2,'Camp Registry'),(3,'People Registry');
UNLOCK TABLES;
/*!40000 ALTER TABLE `tblaccessmodules` ENABLE KEYS */;

--
-- Table structure for table `tblaccesspermissions`
--

DROP TABLE IF EXISTS `tblaccesspermissions`;
CREATE TABLE `tblaccesspermissions` (
  `ModuleId` int(11) default NULL,
  `AccessLevel` varchar(20) default NULL,
  `Permission` char(1) default NULL,
  `RoleId` int(11) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblaccesspermissions`
--


/*!40000 ALTER TABLE `tblaccesspermissions` DISABLE KEYS */;
LOCK TABLES `tblaccesspermissions` WRITE;
INSERT INTO `tblaccesspermissions` VALUES (3,'ADD','Y',1),(1,'EDIT','Y',1),(3,'VIEW','Y',1);
UNLOCK TABLES;
/*!40000 ALTER TABLE `tblaccesspermissions` ENABLE KEYS */;

--
-- Table structure for table `tblmoduleaccesslevels`
--

DROP TABLE IF EXISTS `tblmoduleaccesslevels`;
CREATE TABLE `tblmoduleaccesslevels` (
  `ModuleId` int(11) default NULL,
  `AccessLevel` varchar(20) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblmoduleaccesslevels`
--


/*!40000 ALTER TABLE `tblmoduleaccesslevels` DISABLE KEYS */;
LOCK TABLES `tblmoduleaccesslevels` WRITE;
INSERT INTO `tblmoduleaccesslevels` VALUES (1,'PAGE'),(1,'ADD'),(1,'SEARCH');
UNLOCK TABLES;
/*!40000 ALTER TABLE `tblmoduleaccesslevels` ENABLE KEYS */;

--
-- Table structure for table `tblroles`
--

DROP TABLE IF EXISTS `tblroles`;
CREATE TABLE `tblroles` (
  `RoleId` int(11) default NULL,
  `RoleName` varchar(30) default NULL,
  `Description` varchar(100) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblroles`
--


/*!40000 ALTER TABLE `tblroles` DISABLE KEYS */;
LOCK TABLES `tblroles` WRITE;
INSERT INTO `tblroles` VALUES (1,'Administrator','Administration role'),(2,'Normal user','Normal user');
UNLOCK TABLES;
/*!40000 ALTER TABLE `tblroles` ENABLE KEYS */;

--
-- Table structure for table `tbluserroles`
--

DROP TABLE IF EXISTS `tbluserroles`;
CREATE TABLE `tbluserroles` (
  `RoleId` int(11) default NULL,
  `UserName` varchar(30) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tbluserroles`
--


/*!40000 ALTER TABLE `tbluserroles` DISABLE KEYS */;
LOCK TABLES `tbluserroles` WRITE;
INSERT INTO `tbluserroles` VALUES (1,'sanjiva');
UNLOCK TABLES;
/*!40000 ALTER TABLE `tbluserroles` ENABLE KEYS */;

