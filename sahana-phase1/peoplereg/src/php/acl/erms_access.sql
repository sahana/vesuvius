-- MySQL dump 9.11
--
-- Host: localhost    Database: erms
-- ------------------------------------------------------
-- Server version	4.0.23_Debian-1-log

--
-- Table structure for table `TBLACCESSLEVELS`
--

DROP TABLE IF EXISTS `TBLACCESSLEVELS`;
CREATE TABLE `TBLACCESSLEVELS` (
  `AccessLevels` varchar(20) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `TBLACCESSLEVELS`
--


/*!40000 ALTER TABLE `TBLACCESSLEVELS` DISABLE KEYS */;
LOCK TABLES `TBLACCESSLEVELS` WRITE;
INSERT INTO `TBLACCESSLEVELS` VALUES ('PAGE'),('ADD'),('EDIT'),('DELETE'),('SEARCH'),('VIEW');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TBLACCESSLEVELS` ENABLE KEYS */;

--
-- Table structure for table `TBLACCESSMODULES`
--

DROP TABLE IF EXISTS `TBLACCESSMODULES`;
CREATE TABLE `TBLACCESSMODULES` (
  `ModuleId` int(11) default NULL,
  `ModuleName` varchar(50) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `TBLACCESSMODULES`
--


/*!40000 ALTER TABLE `TBLACCESSMODULES` DISABLE KEYS */;
LOCK TABLES `TBLACCESSMODULES` WRITE;
INSERT INTO `TBLACCESSMODULES` VALUES (1,'Assistance Database'),(2,'Camp Registry'),(3,'People Registry');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TBLACCESSMODULES` ENABLE KEYS */;

--
-- Table structure for table `TBLACCESSPERMISSIONS`
--

DROP TABLE IF EXISTS `TBLACCESSPERMISSIONS`;
CREATE TABLE `TBLACCESSPERMISSIONS` (
  `ModuleId` int(11) default NULL,
  `AccessLevel` varchar(20) default NULL,
  `Permission` char(1) default NULL,
  `RoleId` int(11) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `TBLACCESSPERMISSIONS`
--


/*!40000 ALTER TABLE `TBLACCESSPERMISSIONS` DISABLE KEYS */;
LOCK TABLES `TBLACCESSPERMISSIONS` WRITE;
INSERT INTO `TBLACCESSPERMISSIONS` VALUES (3,'ADD','Y',1),(1,'EDIT','Y',1),(3,'VIEW','Y',1);
UNLOCK TABLES;
/*!40000 ALTER TABLE `TBLACCESSPERMISSIONS` ENABLE KEYS */;

--
-- Table structure for table `TBLMODULEACCESSLEVELS`
--

DROP TABLE IF EXISTS `TBLMODULEACCESSLEVELS`;
CREATE TABLE `TBLMODULEACCESSLEVELS` (
  `ModuleId` int(11) default NULL,
  `AccessLevel` varchar(20) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblmoduleaccesslevels`
--


/*!40000 ALTER TABLE `TBLMODULEACCESSLEVELS` DISABLE KEYS */;
LOCK TABLES `TBLMODULEACCESSLEVELS` WRITE;
INSERT INTO `TBLMODULEACCESSLEVELS` VALUES (1,'PAGE'),(1,'ADD'),(1,'SEARCH');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TBLMODULEACCESSLEVELS` ENABLE KEYS */;

--
-- Table structure for table `TBLROLES`
--

DROP TABLE IF EXISTS `TBLROLES`;
CREATE TABLE `TBLROLES` (
  `RoleId` int(11) default NULL,
  `RoleName` varchar(30) default NULL,
  `Description` varchar(100) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblroles`
--


/*!40000 ALTER TABLE `TBLROLES` DISABLE KEYS */;
LOCK TABLES `TBLROLES` WRITE;
INSERT INTO `TBLROLES` VALUES (1,'Administrator','Administration role'),(2,'Normal user','Normal user');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TBLROLES` ENABLE KEYS */;

--
-- Table structure for table `TBLUSERROLES`
--

DROP TABLE IF EXISTS `TBLUSERROLES`;
CREATE TABLE `tbluserroles` (
  `RoleId` int(11) default NULL,
  `UserName` varchar(30) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tbluserroles`
--


/*!40000 ALTER TABLE `TBLUSERROLES` DISABLE KEYS */;
LOCK TABLES `TBLUSERROLES` WRITE;
INSERT INTO `TBLUSERROLES` VALUES (1,'sanjiva');
UNLOCK TABLES;
/*!40000 ALTER TABLE `TBLUSERROLES` ENABLE KEYS */;

