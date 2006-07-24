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
-- Table structure for table gacl_acl
--

CREATE TABLE gacl_acl (
  id INT NOT NULL default '0',
  section_value varchar(230) NOT NULL default 'system',
  allow INT NOT NULL default '0',
  enabled INT NOT NULL default '0',
  return_value text,
  note text,
  updated_date INT NOT NULL default '0',
  PRIMARY KEY (id)
) ;

--
-- Dumping data for table gacl_acl
--


/*!40000 ALTER TABLE `gacl_acl` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_acl` ENABLE KEYS */;

--
-- Table structure for table gacl_acl_sections
--

CREATE TABLE gacl_acl_sections (
  id INT NOT NULL default '0',
  value varchar(230) NOT NULL,
  order_value INT NOT NULL default '0',
  name varchar(230) NOT NULL,
  hidden INT NOT NULL default '0',
  PRIMARY KEY (id)
) ;

--
-- Dumping data for table gacl_acl_sections
--


/*!40000 ALTER TABLE `gacl_acl_sections` DISABLE KEYS */;
INSERT INTO gacl_acl_sections VALUES (1,'system',1,'System',0);
INSERT INTO gacl_acl_sections VALUES (2,'user',2,'User',0);
/*!40000 ALTER TABLE `gacl_acl_sections` ENABLE KEYS */;

--
-- Table structure for table gacl_aco
--

CREATE TABLE gacl_aco (
  id INT NOT NULL default '0',
  section_value varchar(240) NOT NULL default '0',
  value varchar(240) NOT NULL,
  order_value INT NOT NULL default '0',
  name varchar(255) NOT NULL,
  hidden INT NOT NULL default '0',
  PRIMARY KEY (id)
) ;

--
-- Dumping data for table gacl_aco
--


/*!40000 ALTER TABLE `gacl_aco` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_aco` ENABLE KEYS */;

--
-- Table structure for table gacl_aco_map
--

CREATE TABLE gacl_aco_map (
  acl_id INT NOT NULL default '0',
  section_value varchar(230) NOT NULL default '0',
  value varchar(230) NOT NULL,
  PRIMARY KEY (acl_idsection_value,value)
) ;

--
-- Dumping data for table gacl_aco_map
--


/*!40000 ALTER TABLE `gacl_aco_map` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_aco_map` ENABLE KEYS */;

--
-- Table structure for table gacl_aco_sections
--

CREATE TABLE gacl_aco_sections (
  id INT NOT NULL default '0',
  value varchar(230) NOT NULL,
  order_value INT NOT NULL default '0',
  name varchar(230) NOT NULL,
  hidden INT NOT NULL default '0',
  PRIMARY KEY (id)
) ;

--
-- Dumping data for table gacl_aco_sections
--


/*!40000 ALTER TABLE `gacl_aco_sections` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_aco_sections` ENABLE KEYS */;

--
-- Table structure for table gacl_aro
--

CREATE TABLE gacl_aro (
  id INT NOT NULL default '0',
  section_value varchar(240) NOT NULL default '0',
  value varchar(240) NOT NULL,
  order_value INT NOT NULL default '0',
  name varchar(255) NOT NULL,
  hidden INT NOT NULL default '0',
  PRIMARY KEY (id)
) ;

--
-- Dumping data for table gacl_aro
--


/*!40000 ALTER TABLE `gacl_aro` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_aro` ENABLE KEYS */;

--
-- Table structure for table gacl_aro_groups
--

CREATE TABLE gacl_aro_groups (
  id INT NOT NULL default '0',
  parent_id INT NOT NULL default '0',
  lft INT NOT NULL default '0',
  rgt INT NOT NULL default '0',
  name varchar(255) NOT NULL,
  value varchar(255) NOT NULL,
  PRIMARY KEY (idvalue)
) ;

--
-- Dumping data for table gacl_aro_groups
--


/*!40000 ALTER TABLE `gacl_aro_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_aro_groups` ENABLE KEYS */;

--
-- Table structure for table gacl_aro_groups_map
--

CREATE TABLE gacl_aro_groups_map (
  acl_id INT NOT NULL default '0',
  group_id INT NOT NULL default '0',
  PRIMARY KEY (acl_idgroup_id)
) ;

--
-- Dumping data for table gacl_aro_groups_map
--


/*!40000 ALTER TABLE `gacl_aro_groups_map` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_aro_groups_map` ENABLE KEYS */;

--
-- Table structure for table gacl_aro_map
--

CREATE TABLE gacl_aro_map (
  acl_id INT NOT NULL default '0',
  section_value varchar(230) NOT NULL default '0',
  value varchar(230) NOT NULL,
  PRIMARY KEY (acl_idsection_value,value)
) ;

--
-- Dumping data for table gacl_aro_map
--


/*!40000 ALTER TABLE `gacl_aro_map` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_aro_map` ENABLE KEYS */;

--
-- Table structure for table gacl_aro_sections
--

CREATE TABLE gacl_aro_sections (
  id INT NOT NULL default '0',
  value varchar(230) NOT NULL,
  order_value INT NOT NULL default '0',
  name varchar(230) NOT NULL,
  hidden INT NOT NULL default '0',
  PRIMARY KEY (id)
) ;

--
-- Dumping data for table gacl_aro_sections
--


/*!40000 ALTER TABLE `gacl_aro_sections` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_aro_sections` ENABLE KEYS */;

--
-- Table structure for table gacl_axo
--

CREATE TABLE gacl_axo (
  id INT NOT NULL default '0',
  section_value varchar(240) NOT NULL default '0',
  value varchar(240) NOT NULL,
  order_value INT NOT NULL default '0',
  name varchar(255) NOT NULL,
  hidden INT NOT NULL default '0',
  PRIMARY KEY (id)
) ;

--
-- Dumping data for table gacl_axo
--


/*!40000 ALTER TABLE `gacl_axo` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_axo` ENABLE KEYS */;

--
-- Table structure for table gacl_axo_groups
--

CREATE TABLE gacl_axo_groups (
  id INT NOT NULL default '0',
  parent_id INT NOT NULL default '0',
  lft INT NOT NULL default '0',
  rgt INT NOT NULL default '0',
  name varchar(255) NOT NULL,
  value varchar(255) NOT NULL,
  PRIMARY KEY (idvalue)
) ;

--
-- Dumping data for table gacl_axo_groups
--


/*!40000 ALTER TABLE `gacl_axo_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_axo_groups` ENABLE KEYS */;

--
-- Table structure for table gacl_axo_groups_map
--

CREATE TABLE gacl_axo_groups_map (
  acl_id INT NOT NULL default '0',
  group_id INT NOT NULL default '0',
  PRIMARY KEY (acl_idgroup_id)
) ;

--
-- Dumping data for table gacl_axo_groups_map
--


/*!40000 ALTER TABLE `gacl_axo_groups_map` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_axo_groups_map` ENABLE KEYS */;

--
-- Table structure for table gacl_axo_map
--

CREATE TABLE gacl_axo_map (
  acl_id INT NOT NULL default '0',
  section_value varchar(230) NOT NULL default '0',
  value varchar(230) NOT NULL,
  PRIMARY KEY (acl_idsection_value,value)
) ;

--
-- Dumping data for table gacl_axo_map
--


/*!40000 ALTER TABLE `gacl_axo_map` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_axo_map` ENABLE KEYS */;

--
-- Table structure for table gacl_axo_sections
--

CREATE TABLE gacl_axo_sections (
  id INT NOT NULL default '0',
  value varchar(230) NOT NULL,
  order_value INT NOT NULL default '0',
  name varchar(230) NOT NULL,
  hidden INT NOT NULL default '0',
  PRIMARY KEY (id)
) ;

--
-- Dumping data for table gacl_axo_sections
--


/*!40000 ALTER TABLE `gacl_axo_sections` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_axo_sections` ENABLE KEYS */;

--
-- Table structure for table gacl_groups_aro_map
--

CREATE TABLE gacl_groups_aro_map (
  group_id INT NOT NULL default '0',
  aro_id INT NOT NULL default '0',
  PRIMARY KEY (group_idaro_id)
) ;

--
-- Dumping data for table gacl_groups_aro_map
--


/*!40000 ALTER TABLE `gacl_groups_aro_map` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_groups_aro_map` ENABLE KEYS */;

--
-- Table structure for table gacl_groups_axo_map
--

CREATE TABLE gacl_groups_axo_map (
  group_id INT NOT NULL default '0',
  axo_id INT NOT NULL default '0',
  PRIMARY KEY (group_idaxo_id)
) ;

--
-- Dumping data for table gacl_groups_axo_map
--


/*!40000 ALTER TABLE `gacl_groups_axo_map` DISABLE KEYS */;
/*!40000 ALTER TABLE `gacl_groups_axo_map` ENABLE KEYS */;

--
-- Table structure for table gacl_phpgacl
--

CREATE TABLE gacl_phpgacl (
  name varchar(230) NOT NULL,
  value varchar(230) NOT NULL,
  PRIMARY KEY  (name)
) ;

--
-- Dumping data for table gacl_phpgacl
--


/*!40000 ALTER TABLE `gacl_phpgacl` DISABLE KEYS */;
INSERT INTO gacl_phpgacl VALUES ('version','3.3.4'),('schema_version','2.1');
/*!40000 ALTER TABLE `gacl_phpgacl` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;


CREATE INDEX gacl_enabled_acl ON gacl_acl (enabled);

CREATE INDEX gacl_section_value_acl ON gacl_acl (section_value);

CREATE UNIQUE INDEX gacl_value_acl_sections ON gacl_acl_sections (value);

CREATE UNIQUE INDEX gacl_section_value_value_aco ON gacl_aco (section_value,value);

CREATE UNIQUE INDEX gacl_value_aco_sections ON gacl_aco_sections (value);

CREATE UNIQUE INDEX gacl_section_value_value_aro ON gacl_aro (section_value,value);

CREATE UNIQUE INDEX gacl_value_aro_groups ON gacl_aro_groups (value);

CREATE INDEX gacl_parent_id_aro_groups ON gacl_aro_groups (parent_id);

CREATE UNIQUE INDEX gacl_value_aro_sections ON gacl_aro_sections (value);

CREATE UNIQUE INDEX gacl_section_value_value_axo ON gacl_axo (section_value,value);

CREATE UNIQUE INDEX gacl_value_axo_groups ON gacl_axo_groups (value);

CREATE INDEX gacl_parent_id_axo_groups ON gacl_axo_groups (parent_id);

CREATE UNIQUE INDEX gacl_value_axo_sections ON gacl_axo_sections (value);
