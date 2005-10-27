-- MySQL dump 10.10
--
-- Host: localhost    Database: sahana
-- ------------------------------------------------------
-- Server version	5.0.13-rc-Debian_1-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `gacl_acl`
--

DROP TABLE IF EXISTS `gacl_acl`;
CREATE TABLE `gacl_acl` (
  `id` int(11) NOT NULL default '0',
  `section_value` varchar(230) NOT NULL default 'system',
  `allow` int(11) NOT NULL default '0',
  `enabled` int(11) NOT NULL default '0',
  `return_value` text,
  `note` text,
  `updated_date` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `gacl_enabled_acl` (`enabled`),
  KEY `gacl_section_value_acl` (`section_value`),
  KEY `gacl_updated_date_acl` (`updated_date`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_acl`
--


/*!40000 ALTER TABLE `gacl_acl` DISABLE KEYS */;
LOCK TABLES `gacl_acl` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_acl` ENABLE KEYS */;

--
-- Table structure for table `gacl_acl_sections`
--

DROP TABLE IF EXISTS `gacl_acl_sections`;
CREATE TABLE `gacl_acl_sections` (
  `id` int(11) NOT NULL default '0',
  `value` varchar(230) NOT NULL,
  `order_value` int(11) NOT NULL default '0',
  `name` varchar(230) NOT NULL,
  `hidden` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `gacl_value_acl_sections` (`value`),
  KEY `gacl_hidden_acl_sections` (`hidden`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_acl_sections`
--


/*!40000 ALTER TABLE `gacl_acl_sections` DISABLE KEYS */;
LOCK TABLES `gacl_acl_sections` WRITE;
INSERT INTO `gacl_acl_sections` VALUES (1,'system',1,'System',0),(2,'user',2,'User',0);
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_acl_sections` ENABLE KEYS */;

--
-- Table structure for table `gacl_aco`
--

DROP TABLE IF EXISTS `gacl_aco`;
CREATE TABLE `gacl_aco` (
  `id` int(11) NOT NULL default '0',
  `section_value` varchar(240) NOT NULL default '0',
  `value` varchar(240) NOT NULL,
  `order_value` int(11) NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `hidden` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `gacl_section_value_value_aco` (`section_value`,`value`),
  KEY `gacl_hidden_aco` (`hidden`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_aco`
--


/*!40000 ALTER TABLE `gacl_aco` DISABLE KEYS */;
LOCK TABLES `gacl_aco` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_aco` ENABLE KEYS */;

--
-- Table structure for table `gacl_aco_map`
--

DROP TABLE IF EXISTS `gacl_aco_map`;
CREATE TABLE `gacl_aco_map` (
  `acl_id` int(11) NOT NULL default '0',
  `section_value` varchar(230) NOT NULL default '0',
  `value` varchar(230) NOT NULL,
  PRIMARY KEY  (`acl_id`,`section_value`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_aco_map`
--


/*!40000 ALTER TABLE `gacl_aco_map` DISABLE KEYS */;
LOCK TABLES `gacl_aco_map` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_aco_map` ENABLE KEYS */;

--
-- Table structure for table `gacl_aco_sections`
--

DROP TABLE IF EXISTS `gacl_aco_sections`;
CREATE TABLE `gacl_aco_sections` (
  `id` int(11) NOT NULL default '0',
  `value` varchar(230) NOT NULL,
  `order_value` int(11) NOT NULL default '0',
  `name` varchar(230) NOT NULL,
  `hidden` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `gacl_value_aco_sections` (`value`),
  KEY `gacl_hidden_aco_sections` (`hidden`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_aco_sections`
--


/*!40000 ALTER TABLE `gacl_aco_sections` DISABLE KEYS */;
LOCK TABLES `gacl_aco_sections` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_aco_sections` ENABLE KEYS */;

--
-- Table structure for table `gacl_aro`
--

DROP TABLE IF EXISTS `gacl_aro`;
CREATE TABLE `gacl_aro` (
  `id` int(11) NOT NULL default '0',
  `section_value` varchar(240) NOT NULL default '0',
  `value` varchar(240) NOT NULL,
  `order_value` int(11) NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `hidden` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `gacl_section_value_value_aro` (`section_value`,`value`),
  KEY `gacl_hidden_aro` (`hidden`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_aro`
--


/*!40000 ALTER TABLE `gacl_aro` DISABLE KEYS */;
LOCK TABLES `gacl_aro` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_aro` ENABLE KEYS */;

--
-- Table structure for table `gacl_aro_groups`
--

DROP TABLE IF EXISTS `gacl_aro_groups`;
CREATE TABLE `gacl_aro_groups` (
  `id` int(11) NOT NULL default '0',
  `parent_id` int(11) NOT NULL default '0',
  `lft` int(11) NOT NULL default '0',
  `rgt` int(11) NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `value` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`,`value`),
  UNIQUE KEY `gacl_value_aro_groups` (`value`),
  KEY `gacl_parent_id_aro_groups` (`parent_id`),
  KEY `gacl_lft_rgt_aro_groups` (`lft`,`rgt`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_aro_groups`
--


/*!40000 ALTER TABLE `gacl_aro_groups` DISABLE KEYS */;
LOCK TABLES `gacl_aro_groups` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_aro_groups` ENABLE KEYS */;

--
-- Table structure for table `gacl_aro_groups_map`
--

DROP TABLE IF EXISTS `gacl_aro_groups_map`;
CREATE TABLE `gacl_aro_groups_map` (
  `acl_id` int(11) NOT NULL default '0',
  `group_id` int(11) NOT NULL default '0',
  PRIMARY KEY  (`acl_id`,`group_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_aro_groups_map`
--


/*!40000 ALTER TABLE `gacl_aro_groups_map` DISABLE KEYS */;
LOCK TABLES `gacl_aro_groups_map` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_aro_groups_map` ENABLE KEYS */;

--
-- Table structure for table `gacl_aro_map`
--

DROP TABLE IF EXISTS `gacl_aro_map`;
CREATE TABLE `gacl_aro_map` (
  `acl_id` int(11) NOT NULL default '0',
  `section_value` varchar(230) NOT NULL default '0',
  `value` varchar(230) NOT NULL,
  PRIMARY KEY  (`acl_id`,`section_value`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_aro_map`
--


/*!40000 ALTER TABLE `gacl_aro_map` DISABLE KEYS */;
LOCK TABLES `gacl_aro_map` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_aro_map` ENABLE KEYS */;

--
-- Table structure for table `gacl_aro_sections`
--

DROP TABLE IF EXISTS `gacl_aro_sections`;
CREATE TABLE `gacl_aro_sections` (
  `id` int(11) NOT NULL default '0',
  `value` varchar(230) NOT NULL,
  `order_value` int(11) NOT NULL default '0',
  `name` varchar(230) NOT NULL,
  `hidden` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `gacl_value_aro_sections` (`value`),
  KEY `gacl_hidden_aro_sections` (`hidden`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_aro_sections`
--


/*!40000 ALTER TABLE `gacl_aro_sections` DISABLE KEYS */;
LOCK TABLES `gacl_aro_sections` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_aro_sections` ENABLE KEYS */;

--
-- Table structure for table `gacl_axo`
--

DROP TABLE IF EXISTS `gacl_axo`;
CREATE TABLE `gacl_axo` (
  `id` int(11) NOT NULL default '0',
  `section_value` varchar(240) NOT NULL default '0',
  `value` varchar(240) NOT NULL,
  `order_value` int(11) NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `hidden` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `gacl_section_value_value_axo` (`section_value`,`value`),
  KEY `gacl_hidden_axo` (`hidden`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_axo`
--


/*!40000 ALTER TABLE `gacl_axo` DISABLE KEYS */;
LOCK TABLES `gacl_axo` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_axo` ENABLE KEYS */;

--
-- Table structure for table `gacl_axo_groups`
--

DROP TABLE IF EXISTS `gacl_axo_groups`;
CREATE TABLE `gacl_axo_groups` (
  `id` int(11) NOT NULL default '0',
  `parent_id` int(11) NOT NULL default '0',
  `lft` int(11) NOT NULL default '0',
  `rgt` int(11) NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `value` varchar(255) NOT NULL,
  PRIMARY KEY  (`id`,`value`),
  UNIQUE KEY `gacl_value_axo_groups` (`value`),
  KEY `gacl_parent_id_axo_groups` (`parent_id`),
  KEY `gacl_lft_rgt_axo_groups` (`lft`,`rgt`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_axo_groups`
--


/*!40000 ALTER TABLE `gacl_axo_groups` DISABLE KEYS */;
LOCK TABLES `gacl_axo_groups` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_axo_groups` ENABLE KEYS */;

--
-- Table structure for table `gacl_axo_groups_map`
--

DROP TABLE IF EXISTS `gacl_axo_groups_map`;
CREATE TABLE `gacl_axo_groups_map` (
  `acl_id` int(11) NOT NULL default '0',
  `group_id` int(11) NOT NULL default '0',
  PRIMARY KEY  (`acl_id`,`group_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_axo_groups_map`
--


/*!40000 ALTER TABLE `gacl_axo_groups_map` DISABLE KEYS */;
LOCK TABLES `gacl_axo_groups_map` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_axo_groups_map` ENABLE KEYS */;

--
-- Table structure for table `gacl_axo_map`
--

DROP TABLE IF EXISTS `gacl_axo_map`;
CREATE TABLE `gacl_axo_map` (
  `acl_id` int(11) NOT NULL default '0',
  `section_value` varchar(230) NOT NULL default '0',
  `value` varchar(230) NOT NULL,
  PRIMARY KEY  (`acl_id`,`section_value`,`value`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_axo_map`
--


/*!40000 ALTER TABLE `gacl_axo_map` DISABLE KEYS */;
LOCK TABLES `gacl_axo_map` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_axo_map` ENABLE KEYS */;

--
-- Table structure for table `gacl_axo_sections`
--

DROP TABLE IF EXISTS `gacl_axo_sections`;
CREATE TABLE `gacl_axo_sections` (
  `id` int(11) NOT NULL default '0',
  `value` varchar(230) NOT NULL,
  `order_value` int(11) NOT NULL default '0',
  `name` varchar(230) NOT NULL,
  `hidden` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `gacl_value_axo_sections` (`value`),
  KEY `gacl_hidden_axo_sections` (`hidden`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_axo_sections`
--


/*!40000 ALTER TABLE `gacl_axo_sections` DISABLE KEYS */;
LOCK TABLES `gacl_axo_sections` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_axo_sections` ENABLE KEYS */;

--
-- Table structure for table `gacl_groups_aro_map`
--

DROP TABLE IF EXISTS `gacl_groups_aro_map`;
CREATE TABLE `gacl_groups_aro_map` (
  `group_id` int(11) NOT NULL default '0',
  `aro_id` int(11) NOT NULL default '0',
  PRIMARY KEY  (`group_id`,`aro_id`),
  KEY `gacl_aro_id` (`aro_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_groups_aro_map`
--


/*!40000 ALTER TABLE `gacl_groups_aro_map` DISABLE KEYS */;
LOCK TABLES `gacl_groups_aro_map` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_groups_aro_map` ENABLE KEYS */;

--
-- Table structure for table `gacl_groups_axo_map`
--

DROP TABLE IF EXISTS `gacl_groups_axo_map`;
CREATE TABLE `gacl_groups_axo_map` (
  `group_id` int(11) NOT NULL default '0',
  `axo_id` int(11) NOT NULL default '0',
  PRIMARY KEY  (`group_id`,`axo_id`),
  KEY `gacl_axo_id` (`axo_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_groups_axo_map`
--


/*!40000 ALTER TABLE `gacl_groups_axo_map` DISABLE KEYS */;
LOCK TABLES `gacl_groups_axo_map` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_groups_axo_map` ENABLE KEYS */;

--
-- Table structure for table `gacl_phpgacl`
--

DROP TABLE IF EXISTS `gacl_phpgacl`;
CREATE TABLE `gacl_phpgacl` (
  `name` varchar(230) NOT NULL,
  `value` varchar(230) NOT NULL,
  PRIMARY KEY  (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `gacl_phpgacl`
--


/*!40000 ALTER TABLE `gacl_phpgacl` DISABLE KEYS */;
LOCK TABLES `gacl_phpgacl` WRITE;
INSERT INTO `gacl_phpgacl` VALUES ('version','3.3.4'),('schema_version','2.1');
UNLOCK TABLES;
/*!40000 ALTER TABLE `gacl_phpgacl` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

