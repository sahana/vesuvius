-- MySQL dump 10.9
--
-- Host: localhost    Database: erms
-- ------------------------------------------------------
-- Server version	4.1.9-nt

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE="NO_AUTO_VALUE_ON_ZERO" */;

--
-- Table structure for table `dmg_case`
--

DROP TABLE IF EXISTS `dmg_case`;
CREATE TABLE `dmg_case` (
  `CaseId` int(11) NOT NULL default '0',
  `ReportedPersonId` varchar(30) default NULL,
  `ReportedDate` datetime default NULL,
  `DamageDate` datetime default NULL,
  `CauseOfDamage` varchar(20) default NULL,
  `ReporterNicPassportId` varchar(30) default NULL,
  `ReporterName` varchar(60) default NULL,
  `ReporterTelNo` varchar(30) default NULL,
  `ReporterAddress` varchar(100) default NULL,
  `ReporterLocation` varchar(20) default NULL,
  `AuthOfficerId` varchar(20) default NULL,
  `InstitutionId` varchar(20) default NULL,
  `ReferenceNumber` varchar(20) default NULL,
  PRIMARY KEY  (`CaseId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


--
-- Table structure for table `dmg_detail_hospital`
--

DROP TABLE IF EXISTS `dmg_detail_hospital`;
CREATE TABLE `dmg_detail_hospital` (
  `DamageReportId` int(10) unsigned NOT NULL default '0',
  `PropertyId` int(10) unsigned default '0',
  `PropertyTypeCode` varchar(200) default NULL,
  `SummaryStatus` text,
  `SummaryFacility` text,
  `DamageDetailHospitalId` int(10) unsigned NOT NULL default '0',
  `HospitalName` varchar(200) default NULL,
  PRIMARY KEY  (`DamageDetailHospitalId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dmg_detail_hospital`
--


--
-- Table structure for table `dmg_detail_hospital_est_cost`
--

DROP TABLE IF EXISTS `dmg_detail_hospital_est_cost`;
CREATE TABLE `dmg_detail_hospital_est_cost` (
  `DmgDetailEstimatedCostId` int(10) unsigned NOT NULL default '0',
  `DamageReportId` int(10) unsigned NOT NULL default '0',
  `PropertyId` int(10) unsigned default NULL,
  `BudgetDescription` varchar(200) default NULL,
  `EstimatedValue` double default NULL,
  PRIMARY KEY  (`DmgDetailEstimatedCostId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dmg_detail_hospital_est_cost`
--


--
-- Table structure for table `dmg_report`
--

DROP TABLE IF EXISTS `dmg_report`;
CREATE TABLE `dmg_report` (
  `DamageReportId` int(11) NOT NULL default '0',
  `CaseId` int(11) NOT NULL default '0',
  `NumberPersonsAffected` int(11) default '0',
  `PropertyTypeCode` varchar(30) default '',
  `ContactPersonName` varchar(30) default '',
  `ContactPersonId` varchar(30) default '',
  `DamageTypeCode` varchar(30) NOT NULL default '',
  `EstimatedDamageValue` double default '0',
  `PropertyId` int(11) default '0',
  `IsRelocate` tinyint(1) default '0',
  PRIMARY KEY  (`DamageReportId`),
  KEY `FKC328D39577E1648B` (`CaseId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


--
-- Table structure for table `dmg_type`
--

DROP TABLE IF EXISTS `dmg_type`;
CREATE TABLE `dmg_type` (
  `damageTypeCode` int(10) unsigned NOT NULL auto_increment,
  `damageDescription` varchar(45) default NULL,
  PRIMARY KEY  (`damageTypeCode`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dmg_type`
--


/*!40000 ALTER TABLE `dmg_type` DISABLE KEYS */;
LOCK TABLES `dmg_type` WRITE;
INSERT INTO `dmg_type` VALUES (1,'Completely Damaged'),(2,'Partly Damaged - Unusable'),(3,'Partly Damaged - Usable'),(4,'Not Damaged');
UNLOCK TABLES;
/*!40000 ALTER TABLE `dmg_type` ENABLE KEYS */;



--
-- Table structure for table `institution`
--

DROP TABLE IF EXISTS `institution`;
CREATE TABLE `institution` (
  `institutionCode` int(10) unsigned NOT NULL auto_increment,
  `institutionName` varchar(45) NOT NULL default '',
  PRIMARY KEY  (`institutionCode`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `institution`
--


/*!40000 ALTER TABLE `institution` DISABLE KEYS */;
LOCK TABLES `institution` WRITE;
INSERT INTO `institution` VALUES (1,'Police Station'),(2,'GN Office'),(3,'Social Service Dept');
UNLOCK TABLES;
/*!40000 ALTER TABLE `institution` ENABLE KEYS */;

--
-- Table structure for table `insurancecompany`
--

DROP TABLE IF EXISTS `insurancecompany`;
CREATE TABLE `insurancecompany` (
  `InsuranceCompanyCode` int(10) unsigned NOT NULL auto_increment,
  `InsuranceCompanyName` varchar(45) NOT NULL default '',
  PRIMARY KEY  (`InsuranceCompanyCode`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `insurancecompany`
--


/*!40000 ALTER TABLE `insurancecompany` DISABLE KEYS */;
LOCK TABLES `insurancecompany` WRITE;
INSERT INTO `insurancecompany` VALUES (1,'Sri Lanka Insurance Company'),(2,'National Insurance Company'),(3,'Jana Shakthi Insurance'),(4,'Egals Insurance');
UNLOCK TABLES;
/*!40000 ALTER TABLE `insurancecompany` ENABLE KEYS */;


--
-- Table structure for table `property`
--

DROP TABLE IF EXISTS `property`;
CREATE TABLE `property` (
  `PropertyId` int(11) NOT NULL default '0',
  `PropertyTypeCode` varchar(100) default NULL,
  `LocationCode` varchar(30) default NULL,
  `OwnerName` varchar(50) default NULL,
  `OwnerPersonRef` varchar(30) default NULL,
  `OwnerAddress` varchar(100) default NULL,
  `PropertyAddress` varchar(100) default NULL,
  `IsInsured` tinyint(1) default '0',
  `InsuranceCompany` varchar(50) default NULL,
  `InsurencePolicy` varchar(50) default NULL,
  `InsurenceValue` double(15,0) default '0',
  PRIMARY KEY  (`PropertyId`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

