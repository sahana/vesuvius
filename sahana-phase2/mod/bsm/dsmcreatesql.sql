-- phpMyAdmin SQL Dump
-- version 3.0.1.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Feb 17, 2009 at 11:28 AM
-- Server version: 5.1.30
-- PHP Version: 5.2.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `sahana`
--

-- --------------------------------------------------------

--
-- Table structure for table `bsm_address`
--

DROP TABLE IF EXISTS `bsm_address`;
CREATE TABLE IF NOT EXISTS `bsm_address` (
  `addr_uuid` int(10) NOT NULL AUTO_INCREMENT,
  `addr_type` varchar(60) DEFAULT NULL,
  `addr_status` varchar(60) DEFAULT NULL,
  `line_1` varchar(200) DEFAULT NULL,
  `line_2` varchar(200) DEFAULT NULL,
  `cty_twn_vil` varchar(60) DEFAULT NULL,
  `post_code` varchar(20) DEFAULT NULL COMMENT 'zip code',
  `district` varchar(60) DEFAULT NULL,
  `state_prov` varchar(60) DEFAULT NULL,
  `country` varchar(60) DEFAULT NULL,
  `loc_id` int(10) DEFAULT NULL,
  `gis_lat` varchar(20) DEFAULT NULL,
  `gis_long` varchar(20) DEFAULT NULL,
  `create_dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `create_by` varchar(100) NOT NULL DEFAULT 'admin',
  `create_proc` varchar(100) NOT NULL DEFAULT 'http://demo.sahana.lk/bsm',
  `modify_dt` datetime DEFAULT NULL,
  `modify_by` varchar(100) DEFAULT NULL,
  `modify_proc` varchar(100) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`addr_uuid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='Patient, Facility, and Health worker addresses' AUTO_INCREMENT=4 ;

--
-- Dumping data for table `bsm_address`
--

INSERT INTO `bsm_address` (`addr_uuid`, `addr_type`, `addr_status`, `line_1`, `line_2`, `cty_twn_vil`, `post_code`, `district`, `state_prov`, `country`, `loc_id`, `gis_lat`, `gis_long`, `create_dt`, `create_by`, `create_proc`, `modify_dt`, `modify_by`, `modify_proc`, `deactivate_dt`) VALUES
(1, 'Office', 'Active', '12 balcombe place', NULL, 'Colombo 08', '00080', 'Colombo', 'Western', 'Sri Lanka', NULL, NULL, NULL, '2008-12-22 11:38:50', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(2, 'Office', 'Active', '15 De Seram road', NULL, 'Mount Lavinia', '10080', 'Colombo', 'Western', 'Sri Lanka', NULL, NULL, NULL, '2008-12-31 22:21:37', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(3, 'Physical', 'Inactive', '12 Balcombe Place', NULL, 'Colombo 08', '00080', 'Colombo', 'Western', 'Sri Lanka', NULL, NULL, NULL, '2008-12-31 22:22:44', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_addr_lukup_elmnt`
--

DROP TABLE IF EXISTS `bsm_addr_lukup_elmnt`;
CREATE TABLE IF NOT EXISTS `bsm_addr_lukup_elmnt` (
  `elmnt_uuid` int(10) NOT NULL AUTO_INCREMENT COMMENT 'record uuid',
  `elmnt_name` varchar(60) DEFAULT NULL COMMENT 'name of country, prov, or dist, ',
  `elmnt_prnt_uuid` int(10) DEFAULT NULL COMMENT 'id the parent e.g. country of a prov',
  `elmnt_code` varchar(20) DEFAULT NULL COMMENT 'ISO 2 cntry, state, or postal code or other',
  `elmnt_type` varchar(60) NOT NULL COMMENT 'country, province, district, state',
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`elmnt_uuid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COMMENT='Lookup table to hold address country dist prov names' AUTO_INCREMENT=6 ;

--
-- Dumping data for table `bsm_addr_lukup_elmnt`
--

INSERT INTO `bsm_addr_lukup_elmnt` (`elmnt_uuid`, `elmnt_name`, `elmnt_prnt_uuid`, `elmnt_code`, `elmnt_type`, `deactivate_dt`) VALUES
(1, 'Kurunegala', 0, 'KN', 'District', NULL),
(3, 'Wariyapola', 1, NULL, 'Town', NULL),
(4, 'Udubedewa', 1, '35000', 'Town', NULL),
(5, '30050', 1, NULL, 'Postal Code', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_cases`
--

DROP TABLE IF EXISTS `bsm_cases`;
CREATE TABLE IF NOT EXISTS `bsm_cases` (
  `case_uuid` int(10) NOT NULL AUTO_INCREMENT,
  `case_dt` datetime NOT NULL COMMENT 'date time case was identified may differ from record create datetime',
  `pat_p_uuid` int(10) DEFAULT NULL COMMENT 'patient prsn_id where prsn_cate = Patient',
  `pat_full_name` varchar(200) DEFAULT NULL COMMENT 'patient name must be taken from person table this field is an alternate',
  `hwork_p_uuid` int(10) DEFAULT NULL COMMENT 'health care worker identifying case fk prsn id taken from person table',
  `hwork_full_name` varchar(200) DEFAULT NULL COMMENT 'health care worker such as doctor name must be obtained from person table',
  `fclty_uuid` int(10) DEFAULT NULL COMMENT 'indicate the facility the case was reported from',
  `fclty_name` varchar(200) DEFAULT NULL COMMENT 'facility name same as in table facility',
  `loc_uuid` int(10) DEFAULT NULL,
  `loc_name` varchar(200) DEFAULT NULL,
  `disease` varchar(60) DEFAULT NULL COMMENT 'disease name look up from disease table',
  `dis_dia_dt` datetime DEFAULT NULL COMMENT 'disease diagnosed date time',
  `agent` varchar(100) DEFAULT NULL COMMENT 'carrier agent of the disease',
  `gender` varchar(20) DEFAULT NULL COMMENT 'patient gender same as in person table',
  `age` decimal(5,2) DEFAULT NULL COMMENT 'age of patient same as age defined in person table',
  `age_grp` varchar(100) DEFAULT NULL COMMENT 'patient age group same as in person table lookup prsn_age_grp table',
  `notes` varchar(200) DEFAULT NULL COMMENT 'keywords or notes',
  `create_dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `create_by` varchar(100) NOT NULL DEFAULT 'admin',
  `create_proc` varchar(200) NOT NULL DEFAULT 'http://demo.sahana.lk/bsm',
  `modify_dt` datetime DEFAULT NULL,
  `modify_by` varchar(100) DEFAULT NULL,
  `modify_proc` varchar(100) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'set time to deactivate record and not delete for referential integrity',
  PRIMARY KEY (`case_uuid`),
  KEY `case_id` (`case_uuid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='a case is initiated when a patient reports symptoms' AUTO_INCREMENT=4 ;

--
-- Dumping data for table `bsm_cases`
--

INSERT INTO `bsm_cases` (`case_uuid`, `case_dt`, `pat_p_uuid`, `pat_full_name`, `hwork_p_uuid`, `hwork_full_name`, `fclty_uuid`, `fclty_name`, `loc_uuid`, `loc_name`, `disease`, `dis_dia_dt`, `agent`, `gender`, `age`, `age_grp`, `notes`, `create_dt`, `create_by`, `create_proc`, `modify_dt`, `modify_by`, `modify_proc`, `deactivate_dt`) VALUES
(1, '2008-12-19 11:18:07', NULL, 'Waidyanatha', 1, NULL, NULL, NULL, 12, NULL, 'Cholera', NULL, 'Colleague', 'Unknown', '39.00', 'Young Adult (16-21)', NULL, '2008-12-20 18:08:21', 'admin', 'mHcap-gprs', '0000-00-00 00:00:00', 'user', NULL, NULL),
(2, '2008-12-19 11:18:07', NULL, 'Waidyanatha', 1, NULL, NULL, NULL, 12, NULL, 'Cholera', NULL, NULL, 'Male', NULL, 'Adult', NULL, '2008-12-22 11:39:13', 'admin', 'mHcap-gprs', NULL, NULL, NULL, NULL),
(3, '2008-12-19 11:18:07', NULL, 'Waidyanatha', 1, NULL, NULL, NULL, 12, NULL, 'Cholera', NULL, NULL, 'Male', NULL, 'Adult', NULL, '2008-12-22 11:40:26', 'admin', 'mHcap-gprs', NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_case_serv`
--

DROP TABLE IF EXISTS `bsm_case_serv`;
CREATE TABLE IF NOT EXISTS `bsm_case_serv` (
  `case_uuid` int(10) NOT NULL,
  `serv_uuid` varchar(60) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'deactivate and not delete record for referential integrity',
  UNIQUE KEY `bsm_case_serv_idx` (`serv_uuid`,`case_uuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='relate case to services';

--
-- Dumping data for table `bsm_case_serv`
--


-- --------------------------------------------------------

--
-- Table structure for table `bsm_case_sign`
--

DROP TABLE IF EXISTS `bsm_case_sign`;
CREATE TABLE IF NOT EXISTS `bsm_case_sign` (
  `case_uuid` int(10) NOT NULL,
  `sign` varchar(60) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`case_uuid`,`sign`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='relate signs for a given case';

--
-- Dumping data for table `bsm_case_sign`
--

INSERT INTO `bsm_case_sign` (`case_uuid`, `sign`, `deactivate_dt`) VALUES
(1, 'Ache', NULL),
(1, 'Fever', NULL),
(1, 'Stomoch', NULL),
(1, 'Vomitting', NULL),
(3, 'rash', NULL),
(1, 'Coma', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_case_status`
--

DROP TABLE IF EXISTS `bsm_case_status`;
CREATE TABLE IF NOT EXISTS `bsm_case_status` (
  `case_status` varchar(100) NOT NULL,
  `case_status_desc` varchar(200) DEFAULT NULL,
  `case_status_enum` int(11) DEFAULT NULL COMMENT 'give a number to identify the sequence of status in list',
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'to deactivate record insert datetime',
  PRIMARY KEY (`case_status`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `bsm_case_status`
--

INSERT INTO `bsm_case_status` (`case_status`, `case_status_desc`, `case_status_enum`, `deactivate_dt`) VALUES
('Closed', 'case is closed due to other reasons see remarks', 8, NULL),
('Cured', 'case has been treated and is cured', 7, NULL),
('Diagnosed', 'cased diagnosed', 4, NULL),
('Investigating', 'case is being investigated and results will be produced', 2, NULL),
('Open', 'case has been create remains to be investigated', 1, NULL),
('Referred', 'case has been refered to anothe facility or health care worker', 3, NULL),
('Treated', 'treatment has been initiated', 6, NULL),
('Untreated', 'case has been investigated and results produced but remains untreated', 5, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_case_status_log`
--

DROP TABLE IF EXISTS `bsm_case_status_log`;
CREATE TABLE IF NOT EXISTS `bsm_case_status_log` (
  `case_uuid` int(10) NOT NULL,
  `case_status` varchar(60) NOT NULL,
  `case_status_dt` datetime DEFAULT NULL,
  `auth_p_uuid` varchar(60) DEFAULT NULL COMMENT 'person authorizing the status change id from person table',
  `notes` varchar(200) DEFAULT NULL COMMENT 'remarks comments for each status',
  `create_dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `create_by` varchar(100) NOT NULL DEFAULT 'admin',
  `create_proc` varchar(100) NOT NULL DEFAULT 'http://demo.sahana.lk/bsm',
  `modify_dt` datetime DEFAULT NULL,
  `modify_by` varchar(100) DEFAULT NULL,
  `modify_proc` varchar(100) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'deactivate and not delete to maintain referential integrity',
  PRIMARY KEY (`case_uuid`,`case_status`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='history of the status change of a cahse';

--
-- Dumping data for table `bsm_case_status_log`
--


-- --------------------------------------------------------

--
-- Table structure for table `bsm_case_symp`
--

DROP TABLE IF EXISTS `bsm_case_symp`;
CREATE TABLE IF NOT EXISTS `bsm_case_symp` (
  `case_uuid` int(10) NOT NULL,
  `symptom` varchar(60) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`case_uuid`,`symptom`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='set of symptoms for each case';

--
-- Dumping data for table `bsm_case_symp`
--

INSERT INTO `bsm_case_symp` (`case_uuid`, `symptom`, `deactivate_dt`) VALUES
(1, 'Ache', NULL),
(1, 'Fever', NULL),
(1, 'Stomoch', NULL),
(1, 'Vomitting', NULL),
(0, 'Fever', NULL),
(1, 'Abdominal cramp', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_caus_fact`
--

DROP TABLE IF EXISTS `bsm_caus_fact`;
CREATE TABLE IF NOT EXISTS `bsm_caus_fact` (
  `caus_fact` varchar(60) NOT NULL,
  `caus_fact_enum` int(10) DEFAULT NULL,
  `caus_fact_priority` varchar(60) DEFAULT NULL,
  `caus_fact_desc` varchar(200) DEFAULT NULL,
  `caus_fact_code` varchar(60) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`caus_fact`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='source of disease';

--
-- Dumping data for table `bsm_caus_fact`
--

INSERT INTO `bsm_caus_fact` (`caus_fact`, `caus_fact_enum`, `caus_fact_priority`, `caus_fact_desc`, `caus_fact_code`, `deactivate_dt`) VALUES
('heavy rains', 1, NULL, 'heavy rains', NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_contact`
--

DROP TABLE IF EXISTS `bsm_contact`;
CREATE TABLE IF NOT EXISTS `bsm_contact` (
  `cont_uuid` int(10) NOT NULL AUTO_INCREMENT,
  `cont_mode` varchar(60) DEFAULT NULL,
  `cont_val` varchar(200) DEFAULT NULL COMMENT 'corresponding value for particulat type; e.g. cont_type = ''mobile phone'' cont_val = ''5551212'' or cont_type = ''email'' cont_val = ''me@myaddress.domain''',
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`cont_uuid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='contact details of facilities, persons' AUTO_INCREMENT=3 ;

--
-- Dumping data for table `bsm_contact`
--

INSERT INTO `bsm_contact` (`cont_uuid`, `cont_mode`, `cont_val`, `deactivate_dt`) VALUES
(1, 'Email', 'me@mydomain.net', NULL),
(2, 'Mobile Phone', '+99-555-1212', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_cty_twn_vil`
--

DROP TABLE IF EXISTS `bsm_cty_twn_vil`;
CREATE TABLE IF NOT EXISTS `bsm_cty_twn_vil` (
  `cty_twn_vil` varchar(60) NOT NULL,
  `district` varchar(60) NOT NULL,
  `cty_twn_vil_desc` varchar(200) DEFAULT NULL,
  `post_code` varchar(20) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`cty_twn_vil`,`district`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `bsm_cty_twn_vil`
--


-- --------------------------------------------------------

--
-- Table structure for table `bsm_disease`
--

DROP TABLE IF EXISTS `bsm_disease`;
CREATE TABLE IF NOT EXISTS `bsm_disease` (
  `disease` varchar(60) NOT NULL,
  `dis_enum` int(10) DEFAULT NULL,
  `dis_type` varchar(60) DEFAULT NULL,
  `dis_priority` varchar(60) DEFAULT NULL,
  `icd_code` varchar(10) DEFAULT NULL,
  `icd_desc` varchar(200) DEFAULT NULL COMMENT 'ICD code description',
  `notes` varchar(200) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'set datetime to deactivate record not delete for referential integrity',
  PRIMARY KEY (`disease`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='list of diseases';

--
-- Dumping data for table `bsm_disease`
--

INSERT INTO `bsm_disease` (`disease`, `dis_enum`, `dis_type`, `dis_priority`, `icd_code`, `icd_desc`, `notes`, `deactivate_dt`) VALUES
('Enteric Fever', 1, 'ENT', 'Medium', 'A01', 'Isolation of Salmonella typhi from blood, stool or other clinical specimen. Serological tests based on agglutination antibodies (SAT) are of little diagnostic value because of limited sensitivity and ', NULL, NULL),
('Pertussis', 2, 'ENT', 'Medium', '', '', NULL, NULL),
('Dysentery', 3, 'Unknown', 'Medium', '', '', NULL, NULL),
('Diphtheria', 4, 'ENT', 'Medium', '', '', NULL, NULL),
('Polio', 5, 'Unknown', 'Medium', '', '', NULL, NULL),
('Yellow Fever', 6, 'ENT', 'High', '', '', NULL, NULL),
('Plague', 7, 'Dermatological', 'High', '', '', NULL, NULL),
('Cholera', 8, 'ENT', 'High', NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_dis_caus_fact`
--

DROP TABLE IF EXISTS `bsm_dis_caus_fact`;
CREATE TABLE IF NOT EXISTS `bsm_dis_caus_fact` (
  `disease` varchar(60) NOT NULL,
  `caus_fact` varchar(60) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'set date time to deactivate record do not delete for referential integrity',
  PRIMARY KEY (`disease`,`caus_fact`),
  KEY `dis_caus_fact` (`disease`),
  KEY `caus_fact_dis` (`caus_fact`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='relating diseases and causative factors';

--
-- Dumping data for table `bsm_dis_caus_fact`
--

INSERT INTO `bsm_dis_caus_fact` (`disease`, `caus_fact`, `deactivate_dt`) VALUES
('Cholera', 'heavy rains', NULL),
('Enteric Fever', 'heavy rains', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_dis_sign`
--

DROP TABLE IF EXISTS `bsm_dis_sign`;
CREATE TABLE IF NOT EXISTS `bsm_dis_sign` (
  `disease` varchar(60) NOT NULL,
  `sign` varchar(60) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`disease`,`sign`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='relate diseases to signs from lookup tables';

--
-- Dumping data for table `bsm_dis_sign`
--

INSERT INTO `bsm_dis_sign` (`disease`, `sign`, `deactivate_dt`) VALUES
('Enteric Fever', 'Rash', NULL),
('Enteric Fever', 'High fever', NULL),
('Enteric Fever', 'Distended abdomen', NULL),
('Enteric Fever', 'Delirium', NULL),
('Enteric Fever', 'Typhoid state', NULL),
('Pertussis', 'Whooping', NULL),
('Dysentery', 'Abdominal tenderness', NULL),
('Diphtheria', 'Hoarseness', NULL),
('Diphtheria', 'Swollen glands', NULL),
('Diphtheria', 'Grey membrane covering throat', NULL),
('Diphtheria', 'Red infected wound', NULL),
('Diphtheria', 'Wound with gray patchy material', NULL),
('Diphtheria', 'Eye signs', NULL),
('Polio', 'Neck stiffnes', NULL),
('Polio', 'Back stiffness', NULL),
('Polio', 'Muscle spasms', NULL),
('Polio', 'Increase sensitivity to couch', NULL),
('Polio', 'Paralysis of the limbs', NULL),
('Polio', 'Cranial Nerve palsy', NULL),
('Polio', 'Facial muscle paralysis', NULL),
('Polio', 'Features of bulbar palsy', NULL),
('Yellow Fever', 'Red eyes', NULL),
('Yellow Fever', 'Red toungue', NULL),
('Yellow Fever', 'Yellowing of skin', NULL),
('Yellow Fever', 'Yellowing of sclera', NULL),
('Yellow Fever', 'Nose bleed', NULL),
('Yellow Fever', 'Heart arrythmias', NULL),
('Yellow Fever', 'Liver failure', NULL),
('Yellow Fever', 'Kidney failure', NULL),
('Yellow Fever', 'Delirium', NULL),
('Yellow Fever', 'Seizures', NULL),
('Yellow Fever', 'Coma', NULL),
('Plague', 'Buboes', NULL),
('Plague', 'Mucosal tissues bleed', NULL),
('Plague', 'Gangeens', NULL),
('Plague', 'Pneumonia', NULL),
('Plague', 'Coma', NULL),
('Cholera', 'Dehydration', NULL),
('Cholera', 'Tachycardia', NULL),
('Cholera', 'Drowsiness', NULL),
('Cholera', 'Back stiffness', NULL),
('Enteric Fever', 'Buboes', NULL),
('Dysentery', 'Back stiffness', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_dis_symp`
--

DROP TABLE IF EXISTS `bsm_dis_symp`;
CREATE TABLE IF NOT EXISTS `bsm_dis_symp` (
  `disease` varchar(60) NOT NULL,
  `symptom` varchar(60) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`disease`,`symptom`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='relate diseases to symptoms, lookup table';

--
-- Dumping data for table `bsm_dis_symp`
--

INSERT INTO `bsm_dis_symp` (`disease`, `symptom`, `deactivate_dt`) VALUES
('Cholera', 'Watery Diarrhoea', NULL),
('Cholera', 'Nausea', NULL),
('Cholera', 'Vomitting', NULL),
('Cholera', 'Muscle ramps', NULL),
('Cholera', 'Thirst', NULL),
('Plague', 'Fever ', NULL),
('Plague', 'Chills', NULL),
('Plague', 'Headache', NULL),
('Plague', 'Fatigue', NULL),
('Plague', 'Diarrhoea', NULL),
('Plague', 'Chest pain', NULL),
('Plague', 'Vomitting', NULL),
('Plague', 'Muscle aches', NULL),
('Plague', 'Cough Blood', NULL),
('Yellow Fever', 'Fever', NULL),
('Yellow Fever', 'Headache', NULL),
('Yellow Fever', 'Muscle aches', NULL),
('Yellow Fever', 'Nausea', NULL),
('Yellow Fever', 'Loss of appetite', NULL),
('Yellow Fever', 'Dizziness', NULL),
('Yellow Fever', 'Abdominal pain', NULL),
('Polio', 'Fever', NULL),
('Polio', 'Headache', NULL),
('Polio', 'Vomiting', NULL),
('Polio', 'Diarrhea', NULL),
('Polio', 'Fatigue', NULL),
('Polio', 'Constipation', NULL),
('Polio', 'Difficult to swollow', NULL),
('Polio', 'Difficulty in breathing', NULL),
('Diphtheria', 'Sore throat', NULL),
('Diphtheria', 'Painfull swollowing', NULL),
('Diphtheria', 'Difficulty in breathing', NULL),
('Diphtheria', 'Fever', NULL),
('Diphtheria', 'Chills', NULL),
('Diphtheria', 'Malaise', NULL),
('Dysentery', 'Abdominal cramp', NULL),
('Dysentery', 'Nausis', NULL),
('Dysentery', 'Vomitting', NULL),
('Dysentery', 'Fever', NULL),
('Dysentery', 'Diarrhoea', NULL),
('Dysentery', 'Blood stained stools', NULL),
('Dysentery', 'Mocous stained stools', NULL),
('Pertussis', 'Runny nose', NULL),
('Pertussis', 'Sneezing', NULL),
('Pertussis', 'Mild cough', NULL),
('Pertussis', 'Low-grade fever', NULL),
('Pertussis', 'Dry cough', NULL),
('Enteric Fever', 'Fever', NULL),
('Enteric Fever', 'Headache', NULL),
('Enteric Fever', 'Fatigue', NULL),
('Enteric Fever', 'Sore throat', NULL),
('Enteric Fever', 'Abdominal pain', NULL),
('Enteric Fever', 'Diarrhoea', NULL),
('Enteric Fever', 'Constipation', NULL),
('Diphtheria', 'Blood stained stools', NULL),
('Diphtheria', 'Constipation', NULL),
('Cholera', 'Chills', NULL),
('Cholera', 'Abdominal pain', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_dis_type`
--

DROP TABLE IF EXISTS `bsm_dis_type`;
CREATE TABLE IF NOT EXISTS `bsm_dis_type` (
  `dis_type` varchar(60) NOT NULL,
  `dis_type_desc` varchar(200) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`dis_type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='define case types - maternal, perdiatric, cardiac, ent, ';

--
-- Dumping data for table `bsm_dis_type`
--

INSERT INTO `bsm_dis_type` (`dis_type`, `dis_type_desc`, `deactivate_dt`) VALUES
('cardiac', 'heart diseases', NULL),
('Dermatological', 'skin diseases', NULL),
('ENT', 'ear nose and throat diseases', NULL),
('maternal', 'pre and post child birth', NULL),
('pediatric', 'child diseases', NULL),
('SDT', 'sexually transmitted diseases', NULL),
('Unknown', 'type of disease unknown', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_facility`
--

DROP TABLE IF EXISTS `bsm_facility`;
CREATE TABLE IF NOT EXISTS `bsm_facility` (
  `fclty_uuid` int(10) NOT NULL AUTO_INCREMENT,
  `fclty_cate` varchar(60) DEFAULT NULL COMMENT 'storage facility, health facility',
  `fclty_type` varchar(60) DEFAULT NULL,
  `fclty_status` varchar(60) DEFAULT NULL,
  `fclty_desc` varchar(200) DEFAULT NULL,
  `loc_uuid` int(10) DEFAULT NULL,
  `create_dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `create_by` varchar(100) NOT NULL DEFAULT 'admin',
  `create_proc` varchar(100) NOT NULL DEFAULT 'http://demo.sahan.lk/bsm',
  `modify_dt` datetime DEFAULT NULL,
  `modify_by` varchar(100) DEFAULT NULL,
  `modify_proc` varchar(100) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`fclty_uuid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT AUTO_INCREMENT=5 ;

--
-- Dumping data for table `bsm_facility`
--

INSERT INTO `bsm_facility` (`fclty_uuid`, `fclty_cate`, `fclty_type`, `fclty_status`, `fclty_desc`, `loc_uuid`, `create_dt`, `create_by`, `create_proc`, `modify_dt`, `modify_by`, `modify_proc`, `deactivate_dt`) VALUES
(1, 'Medical', 'Base Hospital', 'Operational', 'Kuliyapitiya base hospital', NULL, '2009-01-01 03:47:44', 'admin', 'http://demo.sahan.lk/bsm', NULL, NULL, NULL, NULL),
(2, 'Medical', 'Base Hospital', 'Operational', 'Apollo Hospital', NULL, '2009-01-01 03:48:19', 'admin', 'http://demo.sahan.lk/bsm', NULL, NULL, NULL, NULL),
(3, 'Medical', 'Base Hospital', 'Operational', 'Asiri Hospital', NULL, '2009-01-01 03:49:01', 'admin', 'http://demo.sahan.lk/bsm', NULL, NULL, NULL, NULL),
(4, 'Administrative', 'MOH Office', 'Operational', 'Ganemulla', NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahan.lk/bsm', NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_fclty_addr`
--

DROP TABLE IF EXISTS `bsm_fclty_addr`;
CREATE TABLE IF NOT EXISTS `bsm_fclty_addr` (
  `fclty_uuid` int(10) NOT NULL,
  `addr_uuid` int(10) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'to deactivate record insert datetime',
  PRIMARY KEY (`fclty_uuid`,`addr_uuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `bsm_fclty_addr`
--

INSERT INTO `bsm_fclty_addr` (`fclty_uuid`, `addr_uuid`, `deactivate_dt`) VALUES
(1, 1, NULL),
(1, 3, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_fclty_cate`
--

DROP TABLE IF EXISTS `bsm_fclty_cate`;
CREATE TABLE IF NOT EXISTS `bsm_fclty_cate` (
  `fclty_cate` varchar(60) NOT NULL,
  `fctly_cate_desc` varchar(200) DEFAULT NULL,
  `fclty_cate_enum` int(10) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`fclty_cate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `bsm_fclty_cate`
--

INSERT INTO `bsm_fclty_cate` (`fclty_cate`, `fctly_cate_desc`, `fclty_cate_enum`, `deactivate_dt`) VALUES
('Medical', 'facility that provides medical services', 1, NULL),
('Administrative', 'facility that provides health admin services', 2, NULL),
('Legal', 'facility that provides health legal services', 3, NULL),
('Educational', 'facility that provides health professionals training services', 5, NULL),
('Dental', 'facility that provides dental services', 4, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_fclty_serv`
--

DROP TABLE IF EXISTS `bsm_fclty_serv`;
CREATE TABLE IF NOT EXISTS `bsm_fclty_serv` (
  `fclty_uuid` int(10) NOT NULL,
  `serv_uuid` int(10) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`fclty_uuid`,`serv_uuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `bsm_fclty_serv`
--

INSERT INTO `bsm_fclty_serv` (`fclty_uuid`, `serv_uuid`, `deactivate_dt`) VALUES
(1, 1, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_fclty_type`
--

DROP TABLE IF EXISTS `bsm_fclty_type`;
CREATE TABLE IF NOT EXISTS `bsm_fclty_type` (
  `fclty_type` varchar(100) NOT NULL,
  `fclty_cate` varchar(100) NOT NULL,
  `fclty_type_desc` varchar(200) DEFAULT NULL,
  `fclty_type_enum` int(10) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`fclty_type`,`fclty_cate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `bsm_fclty_type`
--

INSERT INTO `bsm_fclty_type` (`fclty_type`, `fclty_cate`, `fclty_type_desc`, `fclty_type_enum`, `deactivate_dt`) VALUES
('General Hospital', 'Medical', NULL, 1, NULL),
('District Hospital', 'Medical', NULL, 2, NULL),
('Base Hospital', 'Medical', NULL, 3, NULL),
('Peripheral Unit', 'Medical', NULL, 4, NULL),
('Maternity Home', 'Medical', NULL, 5, NULL),
('MOH Officer', 'Administrative', 'Medical Officer of Health Office', 6, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_location`
--

DROP TABLE IF EXISTS `bsm_location`;
CREATE TABLE IF NOT EXISTS `bsm_location` (
  `loc_uuid` int(10) NOT NULL AUTO_INCREMENT,
  `loc_prnt_uuid` int(10) DEFAULT NULL,
  `loc_name` varchar(60) NOT NULL COMMENT 'location name is mandetory',
  `loc_cate` varchar(60) DEFAULT NULL,
  `loc_type` varchar(60) DEFAULT NULL,
  `loc_desc` varchar(200) DEFAULT NULL,
  `loc_iso_code` varchar(20) DEFAULT NULL COMMENT 'iso location definition',
  `coord_sys` varchar(60) DEFAULT NULL COMMENT 'gis lat/lon or gis utm to id the vect coord system',
  `loc_shape` varchar(100) DEFAULT NULL COMMENT 'fk to address table to get details such as town, state, country',
  `loc_x_vect` varchar(200) DEFAULT NULL COMMENT 'all the x axis cartesian coordinates of the location shape separate by coma',
  `loc_y_vect` varchar(200) DEFAULT NULL COMMENT 'all the y axis cartesian coordinates of the location shape separate by coma',
  `loc_z_vect` varchar(200) DEFAULT NULL COMMENT 'all the z axis cartesian coordinates of the location shape separate by coma',
  `create_dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `create_by` varchar(100) NOT NULL DEFAULT 'admin',
  `create_proc` varchar(100) NOT NULL DEFAULT 'http://demo.sahana.lk/bsm',
  `modify_dt` datetime DEFAULT NULL,
  `modify_by` varchar(100) DEFAULT NULL,
  `modify_proc` varchar(100) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`loc_uuid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT AUTO_INCREMENT=21 ;

--
-- Dumping data for table `bsm_location`
--

INSERT INTO `bsm_location` (`loc_uuid`, `loc_prnt_uuid`, `loc_name`, `loc_cate`, `loc_type`, `loc_desc`, `loc_iso_code`, `coord_sys`, `loc_shape`, `loc_x_vect`, `loc_y_vect`, `loc_z_vect`, `create_dt`, `create_by`, `create_proc`, `modify_dt`, `modify_by`, `modify_proc`, `deactivate_dt`) VALUES
(1, 18, 'Kuliyapitiya', 'Health', 'MOH', 'Kuliyapitiya MOH Division', NULL, NULL, 'Polygon', NULL, NULL, NULL, '2008-12-18 23:11:18', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(2, NULL, 'Kurunegala', 'Health', 'DPDHS', 'Kurunegala DPDHS District', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-19 00:36:31', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(3, 4, 'Udugama', 'Health', 'PHI', 'Udugama PHI areas', '1999', NULL, 'Polygon', NULL, NULL, NULL, '2008-12-19 00:51:41', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(4, 18, 'Wariyapola', 'Health', 'MOH', 'Wariyapola', NULL, NULL, 'Polygon', '10.6, 17.5, 16.1,', '21.3, 27.5, 10.4', '0,0,0', '2008-12-19 10:04:15', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(5, 13, 'Udubeddewa', 'Health', 'MOH', 'Udubeddewa MOH Division', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-19 10:08:07', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(6, NULL, 'Sri Lanka', 'Health', 'National', 'Sri Lanka national health care system', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-19 10:50:06', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(7, NULL, '', 'Health', 'Village', 'Chembanur', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-19 12:07:33', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(9, NULL, 'Chembanur', 'Health', 'PHC', 'Chembanur PHC area', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-20 17:05:40', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(10, NULL, 'Chembanur', 'Health', 'Village', 'Chembanur VHN area', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-20 17:06:43', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(11, NULL, 'Kuliyapitiya', 'Health', 'PHI', 'Kuliyapitiya PHI area', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-20 17:10:10', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(12, 4, 'Thambapanni', 'Health', 'PHI', 'Thambapanni', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-20 17:33:05', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(13, 6, 'Nuwara', 'Health', 'District', 'Nuwara', NULL, NULL, NULL, NULL, NULL, NULL, '2008-12-30 23:41:07', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(14, NULL, '', NULL, NULL, 'Colombo', NULL, NULL, 'Circle', NULL, NULL, NULL, '2009-01-09 09:48:33', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(15, NULL, 'Colo', NULL, NULL, NULL, NULL, NULL, 'Circle', NULL, NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(16, 17, 'Colombo', 'Health', 'MOH', NULL, NULL, NULL, 'Polygon', NULL, NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(17, 6, 'Colombo', 'Governance', 'District', NULL, NULL, NULL, 'Circle', NULL, NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(18, NULL, 'Kurunegala', 'Health', 'District', 'Kurunegala DPDHS District', NULL, NULL, 'Polygon', NULL, NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(19, 1, 'Maharagama', 'Health', 'PHI', 'Maharagama PHI division', NULL, NULL, 'Polygon', NULL, NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(20, NULL, 'Mahabalipuram', 'Health', 'District', NULL, NULL, NULL, 'Circle', NULL, NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_loc_cate`
--

DROP TABLE IF EXISTS `bsm_loc_cate`;
CREATE TABLE IF NOT EXISTS `bsm_loc_cate` (
  `loc_cate` varchar(60) NOT NULL,
  `loc_cate_desc` varchar(200) DEFAULT NULL,
  `loc_cate_enum` int(10) DEFAULT NULL COMMENT 'enumeration to pass instead of name',
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`loc_cate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='health system, governance system, etc';

--
-- Dumping data for table `bsm_loc_cate`
--

INSERT INTO `bsm_loc_cate` (`loc_cate`, `loc_cate_desc`, `loc_cate_enum`, `deactivate_dt`) VALUES
('Health', 'location definition of the health system hierarchy', NULL, NULL),
('Governance', NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_loc_type`
--

DROP TABLE IF EXISTS `bsm_loc_type`;
CREATE TABLE IF NOT EXISTS `bsm_loc_type` (
  `loc_type` varchar(60) NOT NULL,
  `loc_cate` varchar(60) NOT NULL,
  `loc_type_prnt` varchar(60) DEFAULT NULL COMMENT 'parent of location type e.g. MOH division is parent of PHI area',
  `type_desc` varchar(200) DEFAULT NULL,
  `loc_type_enum` int(10) NOT NULL,
  `loc_type_shape` varchar(100) DEFAULT NULL COMMENT 'location type shape - point, line, circle, rectangle, polygon',
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'deactivate record and not delete to avoid referential integrity',
  PRIMARY KEY (`loc_type`,`loc_cate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='health or governance locations';

--
-- Dumping data for table `bsm_loc_type`
--

INSERT INTO `bsm_loc_type` (`loc_type`, `loc_cate`, `loc_type_prnt`, `type_desc`, `loc_type_enum`, `loc_type_shape`, `deactivate_dt`) VALUES
('MOH', 'Health', 'District', 'Medical Officer of Health Division', 0, 'polygon', NULL),
('PHI', 'Health', 'MOH', 'Publich Health Inspector Area', 0, 'polygon', NULL),
('District', 'Health', 'Province', 'District health area', 0, 'polygon', NULL),
('Province', 'Health', 'Region', 'Provincial health area', 0, 'polygon', NULL),
('Region', 'Health', 'National', 'Regional Health area', 0, 'polygon', NULL),
('National', 'Health', NULL, 'National health geographic coverage', 0, 'polygon', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_person`
--

DROP TABLE IF EXISTS `bsm_person`;
CREATE TABLE IF NOT EXISTS `bsm_person` (
  `p_uuid` int(10) NOT NULL AUTO_INCREMENT COMMENT 'unique id for indexing db',
  `prsn_role` varchar(60) NOT NULL DEFAULT 'Unknown' COMMENT 'category can be Health Care Worker or Patient',
  `prsn_type` varchar(60) DEFAULT 'Unknown',
  `prsn_state` varchar(60) DEFAULT 'Unknown' COMMENT 'Status for a patient = diseased handicaped',
  `passport` varchar(60) DEFAULT NULL COMMENT 'passport number or NIC',
  `natl_id` varchar(60) DEFAULT NULL,
  `dr_lic` varchar(60) DEFAULT NULL COMMENT 'driver license',
  `last_name` varchar(100) DEFAULT NULL COMMENT 'Surname or family name',
  `first_name` varchar(100) DEFAULT NULL COMMENT 'given first name',
  `mi_name` varchar(100) DEFAULT NULL COMMENT 'middle initial or name',
  `alias` varchar(100) DEFAULT NULL COMMENT 'other names or alias',
  `gender` varchar(20) DEFAULT 'Unknown' COMMENT 'sex = Male, Female, or Unknown',
  `desig` varchar(100) DEFAULT 'Unknown' COMMENT 'person designation',
  `dep_p_uuid` int(10) DEFAULT NULL COMMENT 'dependent person uuid',
  `age` int(11) DEFAULT NULL,
  `age_grp` varchar(60) DEFAULT NULL COMMENT 'Infant Child Teen Adulacent Adult Elderly',
  `dob` date DEFAULT NULL COMMENT 'Date of Birth',
  `height` decimal(6,4) DEFAULT NULL COMMENT 'meters',
  `ht_unit` varchar(100) DEFAULT 'meters' COMMENT 'specify unit of measure',
  `weight` decimal(7,4) DEFAULT NULL COMMENT 'kilograms',
  `wt_unit` varchar(100) DEFAULT 'kilograms' COMMENT 'weight unit of measure',
  `ethicity` varchar(100) DEFAULT 'Unknown' COMMENT 'combination of race and religion',
  `loc_id` int(10) DEFAULT NULL,
  `country` varchar(60) DEFAULT 'Unknown' COMMENT 'country of birth or residence',
  `create_dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `create_by` varchar(100) NOT NULL DEFAULT 'admin',
  `create_proc` varchar(100) NOT NULL DEFAULT 'http://demo.sahana.lk/bsm',
  `modify_dt` timestamp NULL DEFAULT NULL,
  `modify_by` varchar(100) DEFAULT NULL,
  `modify_proc` varchar(100) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`p_uuid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT AUTO_INCREMENT=6 ;

--
-- Dumping data for table `bsm_person`
--

INSERT INTO `bsm_person` (`p_uuid`, `prsn_role`, `prsn_type`, `prsn_state`, `passport`, `natl_id`, `dr_lic`, `last_name`, `first_name`, `mi_name`, `alias`, `gender`, `desig`, `dep_p_uuid`, `age`, `age_grp`, `dob`, `height`, `ht_unit`, `weight`, `wt_unit`, `ethicity`, `loc_id`, `country`, `create_dt`, `create_by`, `create_proc`, `modify_dt`, `modify_by`, `modify_proc`, `deactivate_dt`) VALUES
(1, 'User', 'Unknown', 'Unknown', '69070948v', '69070948v', '', 'Waidyanatha', 'Nuwan', 'T.', NULL, 'Unknown', 'Unknown', NULL, NULL, NULL, NULL, '1.6500', 'meters', '99.9900', 'kilograms', 'Unknown', NULL, 'Unknown', '2008-12-19 11:18:07', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', 'mob-gprs', NULL),
(2, 'Patient', 'Mental', 'Certified', 'L6011156', '76293456v', '', 'Hewapathirana', 'Roshan', 'XXX', 'Doc', 'Unknown', 'Unknown', NULL, 27, NULL, NULL, NULL, 'meters', NULL, 'kilograms', 'Unknown', NULL, 'Unknown', '2008-12-20 00:45:00', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(3, 'Health Care Worker', 'VHN', 'Certified', '690700948v', NULL, '', 'Waidyanatha', 'Nuwan', 'Thejana', 'NUT', 'Male', NULL, NULL, 39, 'Adult', '1969-03-10', NULL, 'meters', NULL, 'kilograms', 'Unknown', 12, 'Sri Lanka', '2008-12-31 01:09:48', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(4, 'Patient', 'Physical', 'In', 'LMNKDD452', NULL, NULL, 'Kerala', 'Uduwala', 'Handuwa', NULL, 'Female', 'Unknown', 1, 23, 'Adult', '1990-01-03', NULL, 'meters', NULL, 'kilograms', 'Unknown', NULL, 'Unknown', '2008-12-31 16:50:48', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(5, 'Unknown', 'Unknown', 'Unknown', NULL, NULL, NULL, 'Samarajiva', 'Rohan', NULL, 'Prof', 'Unknown', 'Unknown', NULL, 55, NULL, NULL, NULL, 'meters', NULL, 'kilograms', 'Unknown', NULL, 'Unknown', '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_prsn_addr`
--

DROP TABLE IF EXISTS `bsm_prsn_addr`;
CREATE TABLE IF NOT EXISTS `bsm_prsn_addr` (
  `p_uuid` varchar(60) NOT NULL,
  `addr_uuid` varchar(60) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`p_uuid`,`addr_uuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='relating table of address and person entities many-to-many';

--
-- Dumping data for table `bsm_prsn_addr`
--

INSERT INTO `bsm_prsn_addr` (`p_uuid`, `addr_uuid`, `deactivate_dt`) VALUES
('1', '1', NULL),
('1', '2', NULL),
('4', '3', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_prsn_cont`
--

DROP TABLE IF EXISTS `bsm_prsn_cont`;
CREATE TABLE IF NOT EXISTS `bsm_prsn_cont` (
  `p_uuid` varchar(60) NOT NULL,
  `cont_uuid` varchar(60) NOT NULL,
  `deactivate-dt` datetime DEFAULT NULL,
  PRIMARY KEY (`p_uuid`,`cont_uuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `bsm_prsn_cont`
--

INSERT INTO `bsm_prsn_cont` (`p_uuid`, `cont_uuid`, `deactivate-dt`) VALUES
('1', '1', NULL),
('1', '2', NULL),
('4', '1', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_prsn_role`
--

DROP TABLE IF EXISTS `bsm_prsn_role`;
CREATE TABLE IF NOT EXISTS `bsm_prsn_role` (
  `prsn_role` varchar(60) NOT NULL,
  `prsn_role_desc` varchar(200) DEFAULT NULL COMMENT 'additional field to describe the catefory',
  `prsn_role_enum` int(10) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`prsn_role`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='person = Healthcare Worker or Patient';

--
-- Dumping data for table `bsm_prsn_role`
--

INSERT INTO `bsm_prsn_role` (`prsn_role`, `prsn_role_desc`, `prsn_role_enum`, `deactivate_dt`) VALUES
('Health Care Worker', 'Medical professional or person working in the health care fielf', 0, NULL),
('Patient', 'A person with a diagnosed or undiagnosed disease', 0, NULL),
('User', 'A person with rights to use the system', 0, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_prsn_state`
--

DROP TABLE IF EXISTS `bsm_prsn_state`;
CREATE TABLE IF NOT EXISTS `bsm_prsn_state` (
  `prsn_state` varchar(60) NOT NULL,
  `prsn_role` varchar(60) NOT NULL,
  `prsn_state_desc` varchar(200) DEFAULT NULL,
  `prsn_state_enum` int(10) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`prsn_role`,`prsn_state`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='defines the status of a person in a particular category';

--
-- Dumping data for table `bsm_prsn_state`
--

INSERT INTO `bsm_prsn_state` (`prsn_state`, `prsn_role`, `prsn_state_desc`, `prsn_state_enum`, `deactivate_dt`) VALUES
('Certified', 'Health Care Worker', NULL, 0, NULL),
('Intern', 'Health Care Worker', NULL, 0, NULL),
('Student', 'Health Care Worker', NULL, 0, NULL),
('In', 'Patient', NULL, 0, NULL),
('Out', 'Patient', NULL, 0, NULL),
('Unknown', 'Health Care Worker', NULL, 0, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_prsn_type`
--

DROP TABLE IF EXISTS `bsm_prsn_type`;
CREATE TABLE IF NOT EXISTS `bsm_prsn_type` (
  `prsn_type` varchar(60) NOT NULL,
  `prsn_role` varchar(60) NOT NULL DEFAULT 'Patient',
  `prsn_type_desc` varchar(200) DEFAULT NULL,
  `prsn_type_enum` int(11) NOT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`prsn_role`,`prsn_type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='Define a subcategory or type for persons in each category.';

--
-- Dumping data for table `bsm_prsn_type`
--

INSERT INTO `bsm_prsn_type` (`prsn_type`, `prsn_role`, `prsn_type_desc`, `prsn_type_enum`, `deactivate_dt`) VALUES
('HI', 'Health Care Worker', 'Health Inspector', 0, NULL),
('DDHS', 'Health Care Worker', 'Deputy Director of Health Services', 0, NULL),
('GP', 'Health Care Worker', 'General Practitioner', 0, NULL),
('MO', 'Health Care Worker', 'Medical Officer', 0, NULL),
('MOH', 'Health Care Worker', 'Medical Officer of Health', 0, NULL),
('PHI', 'Health Care Worker', 'Public Health Inspector', 0, NULL),
('SHN', 'Health Care Worker', '', 0, NULL),
('VHN', 'Health Care Worker', 'Village Health Care Worker', 0, NULL),
('Mental', 'Patient', 'Patient with Mental Disease', 0, NULL),
('Physical', 'Patient', 'Patient with Physical Disease', 0, NULL),
('Unknown', 'Health Care Worker', NULL, 0, NULL),
('Suwacevo', 'Health Care Worker', NULL, 0, NULL),
('Unknown', 'Patient', NULL, 0, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_service`
--

DROP TABLE IF EXISTS `bsm_service`;
CREATE TABLE IF NOT EXISTS `bsm_service` (
  `serv_uuid` int(10) NOT NULL AUTO_INCREMENT,
  `serv_cate` varchar(60) DEFAULT NULL,
  `serv_type` varchar(60) DEFAULT NULL,
  `serv_state` varchar(60) DEFAULT NULL,
  `serv_state_dt` datetime DEFAULT NULL,
  `prov_p_uuid` int(10) DEFAULT NULL,
  `recp_p_uuid` int(10) DEFAULT NULL,
  `serv_start_dt` datetime DEFAULT NULL COMMENT 'date time service was initiated',
  `serv_end_dt` datetime DEFAULT NULL COMMENT 'date time service was terminated',
  `loc_uuid` int(10) DEFAULT NULL COMMENT 'location service is executer',
  `serv_notes` varchar(200) DEFAULT NULL COMMENT 'other notes in relation to service',
  `create_dt` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `create_by` varchar(100) NOT NULL DEFAULT 'admin',
  `create_proc` varchar(100) NOT NULL DEFAULT 'http://demo.sahana.lk',
  `modify_dt` datetime DEFAULT NULL,
  `modify_by` varchar(100) DEFAULT NULL,
  `modify_proc` varchar(100) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'deactivate record and not delete to maintain referential integrity',
  PRIMARY KEY (`serv_uuid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT AUTO_INCREMENT=9 ;

--
-- Dumping data for table `bsm_service`
--

INSERT INTO `bsm_service` (`serv_uuid`, `serv_cate`, `serv_type`, `serv_state`, `serv_state_dt`, `prov_p_uuid`, `recp_p_uuid`, `serv_start_dt`, `serv_end_dt`, `loc_uuid`, `serv_notes`, `create_dt`, `create_by`, `create_proc`, `modify_dt`, `modify_by`, `modify_proc`, `deactivate_dt`) VALUES
(1, 'Health Care Worker', 'Investigate', 'Requested', '2008-11-30 22:39:33', 4, 2, '2008-11-23 22:39:45', '2009-01-08 00:00:00', 13, 'hello world', '2008-12-28 22:40:07', 'admin', 'http://demo.sahana.lk', '0000-00-00 00:00:00', 'user', '_bsm', NULL),
(2, 'Health Care Worker', 'Investigate', 'Completed', '2008-12-25 00:00:00', 3, 5, '2008-12-29 00:00:00', '2008-12-31 00:00:00', NULL, 'update', '2008-12-30 17:27:58', 'admin', 'http://demo.sahana.lk', '0000-00-00 00:00:00', 'user', '_bsm', NULL),
(3, 'Health Care Worker', 'Investigate', 'Requested', '2008-06-05 00:00:00', 3, NULL, '2008-06-22 00:00:00', NULL, NULL, NULL, '0000-00-00 00:00:00', 'NULL', 'http://demo.sahana.lk', '0000-00-00 00:00:00', NULL, 'bsm', NULL),
(7, 'Health Facility', 'Quarantine', 'To Do', '2009-01-10 00:00:00', NULL, NULL, '2009-01-13 00:00:00', '2009-01-16 00:00:00', NULL, 'Critical', '0000-00-00 00:00:00', 'NULL', 'http://demo.sahana.lk', NULL, NULL, 'NULL', NULL),
(8, 'Disease', 'FBC', 'Work in Progress', '2009-01-26 00:00:00', NULL, NULL, '2009-01-10 00:00:00', '2009-02-08 00:00:00', NULL, 'doo doo doo daa daa daa', '0000-00-00 00:00:00', 'NULL', 'http://demo.sahana.lk', NULL, NULL, 'NULL', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_serv_cate`
--

DROP TABLE IF EXISTS `bsm_serv_cate`;
CREATE TABLE IF NOT EXISTS `bsm_serv_cate` (
  `serv_cate` varchar(100) NOT NULL,
  `serv_cate_enum` int(10) NOT NULL,
  `serv_desc` varchar(200) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`serv_cate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='service categories for person, cases, facilities';

--
-- Dumping data for table `bsm_serv_cate`
--

INSERT INTO `bsm_serv_cate` (`serv_cate`, `serv_cate_enum`, `serv_desc`, `deactivate_dt`) VALUES
('Case', 0, 'services to be carried out with respect to cases', NULL),
('Disease', 0, 'services to be carried out with respect to diseases', NULL),
('Health Care Worker', 0, 'services carried out by health care workers - doctors, nurses, etc', NULL),
('Health Facility', 0, 'services to be carried out by health facilities', NULL),
('Patient', 0, 'services to be carried out by patients -', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_serv_item`
--

DROP TABLE IF EXISTS `bsm_serv_item`;
CREATE TABLE IF NOT EXISTS `bsm_serv_item` (
  `serv_uuid` int(10) NOT NULL COMMENT 'uuid from bsm_service table',
  `item_name` varchar(60) NOT NULL COMMENT 'item name from bsm_serv_type_item',
  `item_state` varchar(20) NOT NULL COMMENT 'Input or Output item',
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'remove active status of record but not delete from db'
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COMMENT='service item details related to bsm_service table';

--
-- Dumping data for table `bsm_serv_item`
--

INSERT INTO `bsm_serv_item` (`serv_uuid`, `item_name`, `item_state`, `deactivate_dt`) VALUES
(1, 'Form H-544', 'Process', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_serv_state`
--

DROP TABLE IF EXISTS `bsm_serv_state`;
CREATE TABLE IF NOT EXISTS `bsm_serv_state` (
  `serv_state` varchar(60) NOT NULL COMMENT 'provides the different states the serive transitions',
  `serv_state_seq` int(5) DEFAULT NULL COMMENT 'set a sequence number',
  `serv_cate` varchar(60) NOT NULL,
  `serv_type` varchar(60) NOT NULL,
  `serv_status_enum` int(10) DEFAULT NULL,
  `serv_status_desc` varchar(200) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`serv_state`,`serv_cate`,`serv_type`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

--
-- Dumping data for table `bsm_serv_state`
--

INSERT INTO `bsm_serv_state` (`serv_state`, `serv_state_seq`, `serv_cate`, `serv_type`, `serv_status_enum`, `serv_status_desc`, `deactivate_dt`) VALUES
('To Do', NULL, 'Health Care Worker', 'Investigate', 0, 'service request has been received in to do list', NULL),
('Requested', NULL, 'Health Care Worker', 'Investigate', 0, NULL, NULL),
('Work in Progress', NULL, 'Health Care Worker', 'Investigate', 0, NULL, NULL),
('Canceled', NULL, 'Health Care Worker', 'Investigate', 0, 'Investigation canceled due to a reason, see notes', NULL),
('Completed', NULL, 'Health Care Worker', 'Investigate', 0, 'task completed', NULL),
('Closed', NULL, 'Health Care Worker', 'Investigate', 0, 'Investigation completed and cases is closed', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_serv_type`
--

DROP TABLE IF EXISTS `bsm_serv_type`;
CREATE TABLE IF NOT EXISTS `bsm_serv_type` (
  `serv_type_enum` int(10) NOT NULL,
  `serv_type` varchar(100) NOT NULL,
  `serv_cate` varchar(100) NOT NULL,
  `serv_type_desc` varchar(200) DEFAULT NULL,
  `serv_proc` varchar(200) DEFAULT NULL COMMENT 'description of how service must be carried out',
  `serv_prov_prsn_type` varchar(60) DEFAULT NULL,
  `serv_recp_prsn_type` varchar(60) DEFAULT NULL,
  `serv_exp_rslt` varchar(200) DEFAULT NULL COMMENT 'expected outcome of the service',
  `serv_exp_tm` int(11) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL COMMENT 'deactivate and not delete record for referential integrity',
  PRIMARY KEY (`serv_type`,`serv_cate`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT;

--
-- Dumping data for table `bsm_serv_type`
--

INSERT INTO `bsm_serv_type` (`serv_type_enum`, `serv_type`, `serv_cate`, `serv_type_desc`, `serv_proc`, `serv_prov_prsn_type`, `serv_recp_prsn_type`, `serv_exp_rslt`, `serv_exp_tm`, `deactivate_dt`) VALUES
(0, 'Cardiac', 'Health Facility', 'cardiac intensive care', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'FBC', 'Cases', 'patient should obtain full blood count', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Investigate', 'Health Care Worker', '', 'health care worker to visit patient to verify case', NULL, NULL, NULL, NULL, NULL),
(0, 'Maternity', 'Health Facility', 'pre and post maternity care', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Notify', 'Disease', 'notify specific disease', NULL, NULL, 'MOH', NULL, NULL, NULL),
(0, 'Quarantine', 'Cases', 'patinet must be quarantined', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Report H399', 'Health Care Worker', 'notify weekly notifiable diseases to regional epidemiological unit', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Report H544', 'Health Care Worker', 'notify divisional health care worker of notifiable disease', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Urine Test', 'Cases', 'patient should obtain urine test', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'X-Ray', 'Cases', 'patient should obtain an X-Ray', NULL, NULL, NULL, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_serv_type_item`
--

DROP TABLE IF EXISTS `bsm_serv_type_item`;
CREATE TABLE IF NOT EXISTS `bsm_serv_type_item` (
  `item_name` varchar(60) NOT NULL COMMENT 'given name for item',
  `serv_cate` varchar(60) NOT NULL,
  `serv_type` varchar(60) NOT NULL COMMENT 'service type item is used in',
  `item_desc` varchar(200) DEFAULT NULL COMMENT 'additional descitption',
  `item_state` varchar(20) NOT NULL COMMENT 'Input or Output to or of the service',
  `deactivate_dt` timestamp NULL DEFAULT NULL COMMENT 'to remove record but not delete from db'
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COMMENT='associate input and output items for a service';

--
-- Dumping data for table `bsm_serv_type_item`
--

INSERT INTO `bsm_serv_type_item` (`item_name`, `serv_cate`, `serv_type`, `item_desc`, `item_state`, `deactivate_dt`) VALUES
('Form H-544', 'Health Care Worker', 'Investigate', 'Form to be carried with PHI during house call', 'IN', '2009-01-26 16:15:37'),
('Form H-544', 'Health Care Worker', 'Investigate', 'Completed H-544 form to be sumitted to MOH', 'OUT', '2009-01-26 16:16:21');

-- --------------------------------------------------------

--
-- Table structure for table `bsm_sign`
--

DROP TABLE IF EXISTS `bsm_sign`;
CREATE TABLE IF NOT EXISTS `bsm_sign` (
  `sign` varchar(60) NOT NULL,
  `sign_desc` varchar(200) DEFAULT NULL,
  `sign_code` varchar(60) DEFAULT NULL,
  `sign_priority` varchar(60) DEFAULT NULL,
  `sign_enum` int(10) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`sign`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=COMPACT COMMENT='list of signs';

--
-- Dumping data for table `bsm_sign`
--

INSERT INTO `bsm_sign` (`sign`, `sign_desc`, `sign_code`, `sign_priority`, `sign_enum`, `deactivate_dt`) VALUES
('Back stiffness', 'Back stiffness', NULL, NULL, 0, NULL),
('Buboes', 'Buboes', NULL, NULL, 0, NULL),
('Coma', 'Coma', NULL, NULL, 0, NULL),
('Cranial nerve palsy', 'Cranial Nerve palsy', NULL, NULL, 0, NULL),
('Dehydration', 'Dehydration', NULL, NULL, 0, NULL),
('Delirium', 'Delirium', NULL, NULL, 0, NULL),
('Distended abdomen', 'Distended abdomen', NULL, NULL, 0, NULL),
('Drowsiness', 'Drowsiness', NULL, NULL, 0, NULL),
('Eye signs', 'Eye signs', NULL, NULL, 0, NULL),
('Facial muscle paralysis', 'Facial muscle paralysis', NULL, NULL, 0, NULL),
('Features of bulbar palsy', 'Features of bulbar palsy', NULL, NULL, 0, NULL),
('Gangeens', 'Gangeens', NULL, NULL, 0, NULL),
('Grey membrane covering throat', 'Grey membrane covering throat', NULL, NULL, 0, NULL),
('Heart arrythmias', 'Heart arrythmias', NULL, NULL, 0, NULL),
('High fever', 'High fever', NULL, NULL, 0, NULL),
('Hoarseness', 'Swollen glands', NULL, NULL, 0, NULL),
('Kidney failure', 'Kidney failure', NULL, NULL, 0, NULL),
('Limb paralysis', 'Paralysis of the limbs', NULL, NULL, 0, NULL),
('Liver failure', 'Liver failure', NULL, NULL, 0, NULL),
('Mucosal tissue bleed', 'Bleeding from mucosal tissues', NULL, NULL, 0, NULL),
('Muscle spasms', 'Muscle spasms', NULL, NULL, 0, NULL),
('Neck stiffnes', 'Neck stiffnes', NULL, NULL, 0, NULL),
('Nose bleed', 'Bleeding from nose', NULL, NULL, 0, NULL),
('Pneumonia', 'Pneumonia', NULL, NULL, 0, NULL),
('Rash', 'Rash', NULL, NULL, 0, NULL),
('Red eyes', 'Red eyes', NULL, NULL, 0, NULL),
('Red infected wound', 'Red infected wound', NULL, NULL, 0, NULL),
('Red toungue', 'Red toungue', NULL, NULL, 0, NULL),
('Seizures', 'Seizures', NULL, NULL, 0, NULL),
('Tachycardia', 'Tachycardia', NULL, NULL, 0, NULL),
('Touch sensitive', 'Increase sensitivity to couch', NULL, NULL, 0, NULL),
('Typhoid state', 'Typhoid state', NULL, NULL, 0, NULL),
('Whooping', 'Whooping', NULL, NULL, 0, NULL),
('Wound with gray patchy material', 'Wound with gray patchy material', NULL, NULL, 0, NULL),
('Yellowing of sclera', 'Yellowing of sclera', NULL, NULL, 0, NULL),
('Yellowing of skin', 'Yellowing of skin', NULL, NULL, 0, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `bsm_symptom`
--

DROP TABLE IF EXISTS `bsm_symptom`;
CREATE TABLE IF NOT EXISTS `bsm_symptom` (
  `symptom` varchar(60) NOT NULL,
  `symp_desc` varchar(200) DEFAULT NULL,
  `symp_code` varchar(60) DEFAULT NULL,
  `symp_priority` varchar(60) DEFAULT NULL,
  `symp_enum` int(10) DEFAULT NULL,
  `deactivate_dt` datetime DEFAULT NULL,
  PRIMARY KEY (`symptom`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC COMMENT='list of symptoms';

--
-- Dumping data for table `bsm_symptom`
--

INSERT INTO `bsm_symptom` (`symptom`, `symp_desc`, `symp_code`, `symp_priority`, `symp_enum`, `deactivate_dt`) VALUES
('Watery Diarrhoea', NULL, '', '', 0, NULL),
('Nausea', NULL, '', '', 0, NULL),
('Vomitting', NULL, '', '', 0, NULL),
('Muscle Cramps', NULL, '', '', 0, NULL),
('Thirst', NULL, '', '', 0, NULL),
('Fever', NULL, '', '', 0, NULL),
('Headache', NULL, '', '', 0, NULL),
('Fatigue', NULL, '', '', 0, NULL),
('Diarrhea', NULL, '', '', 0, NULL),
('Chest pain', NULL, '', '', 0, NULL),
('Muscle aches', NULL, '', '', 0, NULL),
('Cough Blood', 'Cough with blood stained sputum', '', '', 0, NULL),
('Loss of appetite', NULL, '', '', 0, NULL),
('Dizziness', NULL, '', '', 0, NULL),
('Abdominal pain', NULL, '', '', 0, NULL),
('Constipation', NULL, '', '', 0, NULL),
('Difficult to swollow', NULL, '', '', 0, NULL),
('Difficulty in breathing', NULL, '', '', 0, NULL),
('Sore throat', NULL, '', '', 0, NULL),
('Painfull swollowing', NULL, '', '', 0, NULL),
('Chills', NULL, '', '', 0, NULL),
('Malaise', NULL, '', '', 0, NULL),
('Abdominal cramp', NULL, '', '', 0, NULL),
('Blood stained stools', NULL, '', '', 0, NULL),
('Mocous stained stools', NULL, '', '', 0, NULL),
('Runny nose', NULL, '', '', 0, NULL),
('Sneezing', NULL, '', '', 0, NULL),
('Mild cough', NULL, '', '', 0, NULL),
('Low-grade fever', NULL, '', '', 0, NULL),
('Dry Cough', NULL, '', '', 0, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `field_options`
--

DROP TABLE IF EXISTS `field_options`;
CREATE TABLE IF NOT EXISTS `field_options` (
  `field_name` varchar(100) DEFAULT NULL,
  `option_code` varchar(20) DEFAULT NULL,
  `option_description` varchar(50) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `field_options`
--

INSERT INTO `field_options` (`field_name`, `option_code`, `option_description`) VALUES
('opt_group_type', 'fam', 'family'),
('opt_group_type', 'com', 'company'),
('opt_group_type', 'soc', 'society'),
('opt_group_type', 'tor', 'tourists'),
('opt_group_type', 'oth', 'other'),
('opt_group_type', '===', '==Select Option=='),
('opt_id_type', 'nic', 'National Identity Card'),
('opt_id_type', 'pas', 'Passport'),
('opt_id_type', 'dln', 'Driving License Number'),
('opt_id_type', 'oth', 'Other'),
('opt_status', 'ali', 'Alive & Well'),
('opt_status', 'mis', 'Missing'),
('opt_status', 'inj', 'Injured'),
('opt_status', 'dec', 'Deceased'),
('opt_gender', 'mal', 'Male'),
('opt_gender', 'fml', 'Female'),
('opt_relationship_type', 'fat', 'Father'),
('opt_relationship_type', 'mot', 'Mother'),
('opt_relationship_type', 'bro', 'Brother'),
('opt_relationship_type', 'sis', 'Sister'),
('opt_relationship_type', 'gft', 'GrandFather'),
('opt_relationship_type', 'gmt', 'GrandMother'),
('opt_relationship_type', 'gfpat', 'GrandFatherPaternal'),
('opt_relationship_type', 'gfmat', 'GrandFatherMaternal'),
('opt_relationship_type', 'gmpat', 'GrandMotherPaternal'),
('opt_relationship_type', 'gmmat', 'GrandMotherMaternal'),
('opt_relationship_type', 'fnd', 'Friend'),
('opt_relationship_type', 'oth', 'Other'),
('opt_contact_type', 'home', 'Home(permanent address)'),
('opt_contact_type', 'name', 'Contact Person'),
('opt_contact_type', 'pmob', 'Personal Mobile'),
('opt_contact_type', 'curr', 'Current Phone'),
('opt_contact_type', 'cmob', 'Current Mobile'),
('opt_contact_type', 'emai', 'Email address'),
('opt_contact_type', 'fax', 'Fax Number'),
('opt_contact_type', 'web', 'Website'),
('opt_contact_type', 'inst', 'Instant Messenger'),
('opt_person_loc_type', 'hom', 'Permanent home address)'),
('opt_person_loc_type', 'imp', 'Impact location'),
('opt_person_loc_type', 'cur', 'Current location'),
('opt_age_group', 'unk', 'Unknown'),
('opt_age_group', 'inf', 'Infant (0-1)'),
('opt_age_group', 'chi', 'Child (1-15)'),
('opt_age_group', 'you', 'Young Adult (16-21)'),
('opt_age_group', 'adu', 'Adult (22-50)'),
('opt_age_group', 'sen', 'Senior Citizen (50+)'),
('opt_country', 'uk', 'United Kingdom'),
('opt_country', 'lanka', 'Sri Lanka'),
('opt_race', 'unk', 'Unknown'),
('opt_race', 'filip', 'Filipino'),
('opt_race', 'other', 'Other'),
('opt_religion', 'unk', 'Unknown'),
('opt_religion', 'bud', 'Buddhist'),
('opt_religion', 'chr', 'Christian'),
('opt_religion', 'mus', 'Muslim'),
('opt_religion', 'oth', 'Other'),
('opt_marital_status', 'unk', 'Unknown'),
('opt_marital_status', 'sin', 'Single'),
('opt_marital_status', 'mar', 'Married'),
('opt_marital_status', 'div', 'Divorced'),
('opt_blood_type', 'unk', 'Unknown'),
('opt_blood_type', 'a+', 'A+'),
('opt_blood_type', 'a-', 'A-'),
('opt_blood_type', 'b+', 'B+'),
('opt_blood_type', 'b-', 'B-'),
('opt_blood_type', 'ab+', 'AB+'),
('opt_blood_type', 'ab-', 'AB-'),
('opt_blood_type', 'o+', 'O+'),
('opt_blood_type', 'o-', 'O-'),
('opt_blood_type', 'oth', 'Other'),
('opt_eye_color', 'unk', 'Unknown'),
('opt_eye_color', 'bla', 'Black'),
('opt_eye_color', 'bro', 'Light Brown'),
('opt_eye_color', 'blu', 'Blue'),
('opt_eye_color', 'oth', 'Other'),
('opt_skin_color', 'unk', 'Unknown'),
('opt_skin_color', 'bla', 'Black'),
('opt_skin_color', 'bro', 'Dark Brown'),
('opt_skin_color', 'fai', 'Fair'),
('opt_skin_color', 'whi', 'White'),
('opt_skin_color', 'oth', 'Other'),
('opt_hair_color', 'unk', 'Unknown'),
('opt_hair_color', 'bla', 'Black'),
('opt_hair_color', 'bro', 'Brown'),
('opt_hair_color', 'red', 'Red'),
('opt_hair_color', 'blo', 'Blond'),
('opt_hair_color', 'oth', 'Other'),
('opt_camp_type', 'ngo', 'NGO Run Camp'),
('opt_camp_type', 'tmp', 'Temporary Shelter'),
('opt_camp_type', 'gov', 'Government Evacuation Center'),
('opt_camp_service', 'adm', 'Administrative Facilities'),
('opt_camp_service', 'snt', 'Sanitation Facilities'),
('opt_camp_service', 'wat', 'Water Facilities'),
('opt_camp_service', 'mdc', 'Medical Facilities'),
('opt_org_type', 'gov', 'Government'),
('opt_org_type', 'priv', 'Private'),
('opt_org_type', 'ngo', 'NGO'),
('opt_org_type', 'ingo', 'International NGO'),
('opt_org_type', 'mngo', 'Multinational NGO'),
('opt_org_sub_type', 'dep', 'Department'),
('opt_org_sub_type', 'subs', 'Subsidiary'),
('opt_org_sub_type', 'bra', 'Branch'),
('opt_sector_type', 'sup', 'Supplier of Goods'),
('opt_sector_type', 'comm', 'Communications'),
('opt_sector_type', 'med', 'Medical Services'),
('opt_sector_type', 'rehab', 'Rehabilitation'),
('opt_sector_type', 'edu', 'Education'),
('opt_location_type', '1', 'Country'),
('opt_location_type', '2', 'State'),
('opt_location_type', '3', 'City'),
('opt_cs_depth', '6', 'depth'),
('opt_cs_page_record', '30', 'number of page records'),
('opt_rs_rep_freq', '30', 'the frequency of report update'),
('opt_rs_cht_freq', '30', 'the frequency of chart update'),
('opt_landmark_type', 'vil', 'Village'),
('opt_landmark_type', 'tem', 'Temple'),
('opt_landmark_type', 'vil', 'School'),
('opt_landmark_contact_type', 'cor', 'Coordinator'),
('opt_landmark_contact_type', 'cof', 'Chief Of Village'),
('opt_landmark_contact_type', 'mon', 'Monk'),
('opt_wikimap_type', 'gen', 'General'),
('opt_wikimap_type', 'per', 'Person Status'),
('opt_wikimap_type', 'dam', 'Damage Status'),
('opt_wikimap_type', 'dis', 'Disaster Status'),
('opt_wikimap_type', 'sos', 'Help Needed'),
('opt_contact_type', 'emphone', 'Emergency Phone Contact'),
('opt_skill_type', 'ANI2', 'General Skills-Animals-Animal Control Vehicles'),
('opt_skill_type', 'ANI1', 'General Skills-Animals-Animal Handling'),
('opt_skill_type', 'ANI3', 'General Skills-Animals-Grief Counseling'),
('opt_skill_type', 'ANI4', 'General Skills-Animals-Horse Trailers'),
('opt_skill_type', 'ANI5', 'General Skills-Animals-Livestock Vehicles'),
('opt_skill_type', 'ANI8', 'General Skills-Animals-Other'),
('opt_skill_type', 'ANI7', 'General Skills-Animals-Veterinarian'),
('opt_skill_type', 'ANI6', 'General Skills-Animals-Veterinary Technician'),
('opt_skill_type', 'AUT2', 'General Skills-Automotive-Body Repair'),
('opt_skill_type', 'AUT1', 'General Skills-Automotive-Engine Repair'),
('opt_skill_type', 'AUT3', 'General Skills-Automotive-Lights, Electrical'),
('opt_skill_type', 'AUT6', 'General Skills-Automotive-Other'),
('opt_skill_type', 'AUT4', 'General Skills-Automotive-Tire Repair'),
('opt_skill_type', 'AUT5', 'General Skills-Automotive-Wheel and Brake Repair'),
('opt_skill_type', 'BAB1', 'General Skills-Baby and Child Care-Aide'),
('opt_skill_type', 'BAB2', 'General Skills-Baby and Child Care-Leader'),
('opt_skill_type', 'BAB3', 'General Skills-Baby and Child Care-Other'),
('opt_skill_type', 'CON1', 'General Skills-Construction Services-Glass Service'),
('opt_skill_type', 'CON2', 'General Skills-Construction Services-House Repair'),
('opt_skill_type', 'CON3', 'General Skills-Construction Services-Inspection, B'),
('opt_skill_type', 'CON6', 'General Skills-Construction Services-Other'),
('opt_skill_type', 'CON4', 'General Skills-Construction Services-Roofing'),
('opt_skill_type', 'CON5', 'General Skills-Construction Services-Window Repair'),
('opt_skill_type', 'ELE1', 'General Skills-Electrical-External Wiring'),
('opt_skill_type', 'ELE2', 'General Skills-Electrical-Internal Wiring'),
('opt_skill_type', 'ELE3', 'General Skills-Electrical-Other'),
('opt_skill_type', 'FOO1', 'General Skills-Food Service-Cooking'),
('opt_skill_type', 'FOO2', 'General Skills-Food Service-Directing'),
('opt_skill_type', 'FOO5', 'General Skills-Food Service-Other'),
('opt_skill_type', 'FOO3', 'General Skills-Food Service-Preparing'),
('opt_skill_type', 'FOO4', 'General Skills-Food Service-Serving'),
('opt_skill_type', 'HAZ1', 'General Skills-Hazardous Materials-Asbestos'),
('opt_skill_type', 'HAZ2', 'General Skills-Hazardous Materials-Chemicals'),
('opt_skill_type', 'HAZ3', 'General Skills-Hazardous Materials-Explosives'),
('opt_skill_type', 'HAZ4', 'General Skills-Hazardous Materials-Flammables'),
('opt_skill_type', 'HAZ5', 'General Skills-Hazardous Materials-Gases'),
('opt_skill_type', 'HAZ6', 'General Skills-Hazardous Materials-Identification'),
('opt_skill_type', 'HAZ8', 'General Skills-Hazardous Materials-Other'),
('opt_skill_type', 'HAZ7', 'General Skills-Hazardous Materials-Radioactive '),
('opt_skill_type', 'INF1', 'General Skills-Information Services-Book Restorati'),
('opt_skill_type', 'INF2', 'General Skills-Information Services-Computer'),
('opt_skill_type', 'INF3', 'General Skills-Information Services-Data Entry'),
('opt_skill_type', 'INF4', 'General Skills-Information Services-Hardware (Comp'),
('opt_skill_type', 'INF7', 'General Skills-Information Services-Other'),
('opt_skill_type', 'INF5', 'General Skills-Information Services-Software (Comp'),
('opt_skill_type', 'INF6', 'General Skills-Information Services-Telephone Repa'),
('opt_skill_type', 'MED1', 'General Skills-Medical-Assist to Physician'),
('opt_skill_type', 'MED2', 'General Skills-Medical-Counseling'),
('opt_skill_type', 'MED3', 'General Skills-Medical-Dentist'),
('opt_skill_type', 'MED4', 'General Skills-Medical-First Aid'),
('opt_skill_type', 'MED5', 'General Skills-Medical-Medical, Ambulance'),
('opt_skill_type', 'MED6', 'General Skills-Medical-Nurse'),
('opt_skill_type', 'MED9', 'General Skills-Medical-Other'),
('opt_skill_type', 'MED7', 'General Skills-Medical-Physician'),
('opt_skill_type', 'MED8', 'General Skills-Medical-Technician'),
('opt_skill_type', 'PLU2', 'General Skills-Plumbing-Other'),
('opt_skill_type', 'PLU1', 'General Skills-Plumbing-Pumping-With Pump'),
('opt_skill_type', 'PLU3', 'General Skills-Plumbing-Pumping-Without Pump'),
('opt_skill_type', 'TRE1', 'General Skills-Tree-Evaluation of Needs'),
('opt_skill_type', 'TRE4', 'General Skills-Tree-Other'),
('opt_skill_type', 'TRE2', 'General Skills-Tree-Removal of Trees'),
('opt_skill_type', 'TRE3', 'General Skills-Tree-Trimming of Trees'),
('opt_skill_type', 'UNS1', 'Unskilled-Other-Baby Care Help'),
('opt_skill_type', 'UNS2', 'Unskilled-Other-Clerical'),
('opt_skill_type', 'UNS3', 'Unskilled-Other-Food Help'),
('opt_skill_type', 'UNS4', 'Unskilled-Other-Heavy Labor (Moving, Erecting Tent'),
('opt_skill_type', 'UNS5', 'Unskilled-Other-Light Labor (Cleanup)'),
('opt_skill_type', 'UNS6', 'Unskilled-Other-Messenger (Local People Preferred)'),
('opt_skill_type', 'UNS7', 'Unskilled-Other-Miscellaneous'),
('opt_skill_type', 'VEH1', 'Resources-Vehicle-Own Aircraft'),
('opt_skill_type', 'VEH5', 'Resources-Building Aide-Own Backhoe'),
('opt_skill_type', 'VEH2', 'Resources-Building Aide-Own Bulldozer'),
('opt_skill_type', 'VEH3', 'Resources-Building Aide-Own Crane'),
('opt_skill_type', 'VEH4', 'Resources-Building Aide-Own Forklift'),
('opt_skill_type', 'VEH7', 'Resources-Building Aide-Own Heavy Equipment'),
('opt_skill_type', 'VEH6', 'Resources-Vehicle-Own Medical; Ambulance'),
('opt_skill_type', 'VEH13', 'Resources-Vehicle-Own Other'),
('opt_skill_type', 'VEH8', 'Resources-Vehicle-Own Refrigerated'),
('opt_skill_type', 'VEH9', 'Resources-Vehicle-Own Steamshovel'),
('opt_skill_type', 'VEH10', 'Resources-Vehicle-Own Truck'),
('opt_skill_type', 'VEH11', 'Resources-Vehicle-Own Van, Car'),
('opt_skill_type', 'VEH12', 'Resources-Vehicle-Own Boat(s)'),
('opt_skill_type', 'WAR1', 'Resources-Warehouse-Forklift'),
('opt_skill_type', 'WAR2', 'Resources-Warehouse-General'),
('opt_skill_type', 'WAR3', 'General Skills-Warehouse-Management'),
('opt_skill_type', 'WIT1', 'Unskilled-With Tools-with Brooms'),
('opt_skill_type', 'WIT2', 'Unskilled-With Tools-with Carpentry Tools'),
('opt_skill_type', 'WIT7', 'Unskilled-With Tools-with Other Tools'),
('opt_skill_type', 'WIT3', 'Unskilled-With Tools-with Pump, Small'),
('opt_skill_type', 'WIT4', 'Unskilled-With Tools-with Saws, Chainsaw'),
('opt_skill_type', 'WIT5', 'Unskilled-With Tools-with Wheelbarrow'),
('opt_skill_type', 'WIT6', 'Unskilled-With Tools-with Yard Tools'),
('opt_skill_type', 'REST1', 'Restriction-No Heavy Lifting'),
('opt_skill_type', 'REST2', 'Restriction-Can not drive'),
('opt_skill_type', 'REST1', 'Restriction-No Heavy Lifting'),
('opt_skill_type', 'REST2', 'Restriction-Can not drive'),
('opt_skill_type', 'REST3', 'Restriction-Can not swim'),
('opt_skill_type', 'REST4', 'Restriction-Handicapped'),
('opt_skill_type', 'MGR', 'Site Manager'),
('opt_addr_type', 'adtyphy', 'Physical'),
('opt_contact_mode', 'email', 'Email'),
('opt_loc_health_type', 'olhtnat', 'National'),
('opt_loc_health_type', 'olhtreg', 'Regional'),
('opt_loc_health_type', 'olhtprov', 'Province'),
('opt_loc_health_type', 'olhtdist', 'District'),
('opt_loc_health_type', 'olhtdiv', 'Division'),
('opt_gender', 'unk', 'Unknown'),
('opt_contact_mode', 'hmp', 'Home Telephone'),
('opt_contact_mode', 'offp', 'Office Telephone'),
('opt_contact_mode', 'fax', 'Fascismile'),
('opt_contact_mode', 'mp', 'Mobile Phone'),
('opt_addr_type', 'adtybill', 'Billing'),
('opt_contact_mode', 'web', 'Website'),
('opt_addr_type', 'adtymail', 'Mailling'),
('opt_contact_mode', 'blog', 'Blog'),
('opt_contact_mode', 'pager', 'Pager'),
('opt_contact_mode', 'im', 'Instant Messenger'),
('opt_addr_type', 'adtytemp', 'Temporary'),
('opt_addr_type', 'adtyoff', 'Office'),
('opt_addr_status', 'adstact', 'Active'),
('opt_addr_status', 'adstina', 'Inactive'),
('opt_addr_status', 'adstfut', 'Future'),
('opt_addr_status', 'adstunk', 'Unknown'),
('opt_fac_status', 'fcstor', 'Operational'),
('opt_fac_status', 'fcstcl', 'Closed'),
('opt_fac_status', 'fcston', 'Opened'),
('opt_fac_status', 'fcstunk', 'Unknown'),
('opt_dis_priority', 'disph', 'High'),
('opt_dis_priority', 'dispm', 'Medium'),
('opt_dis_priority', 'displ', 'Low'),
('opt_shape', 'shpply', 'Polygon'),
('opt_shape', 'shpcir', 'Circle'),
('opt_shape', 'shptri', 'Triangle'),
('opt_shape', 'shprec', 'Rectangle'),
('opt_shape', 'shppt', 'Point'),
('opt_shape', 'shpln', 'Line'),
('opt_addr_elmnt', 'adelcntry', 'Country'),
('opt_addr_elmnt', 'adelprov', 'Province'),
('opt_addr_elmnt', 'adeldist', 'District'),
('opt_addr_elmnt', 'adelvil', 'Village'),
('opt_addr_elmnt', 'adeltwn', 'Town'),
('opt_addr_elmnt', 'adelState', 'State'),
('opt_addr_elmnt', 'adelState', 'State');
