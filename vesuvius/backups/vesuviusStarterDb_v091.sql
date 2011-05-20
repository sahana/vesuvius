-- MySQL dump 10.11
--
-- Host: localhost    Database: vesuvius091
-- ------------------------------------------------------
-- Server version	5.0.77-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `adodb_logsql`
--

DROP TABLE IF EXISTS `adodb_logsql`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `adodb_logsql` (
  `created` datetime NOT NULL,
  `sql0` varchar(250) NOT NULL,
  `sql1` text NOT NULL,
  `params` text NOT NULL,
  `tracer` text NOT NULL,
  `timer` decimal(16,6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `adodb_logsql`
--

LOCK TABLES `adodb_logsql` WRITE;
/*!40000 ALTER TABLE `adodb_logsql` DISABLE KEYS */;
/*!40000 ALTER TABLE `adodb_logsql` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `alt_logins`
--

DROP TABLE IF EXISTS `alt_logins`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `alt_logins` (
  `p_uuid` varchar(128) NOT NULL,
  `user_name` varchar(100) NOT NULL,
  `type` varchar(60) default 'openid',
  PRIMARY KEY  (`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `alt_logins`
--

LOCK TABLES `alt_logins` WRITE;
/*!40000 ALTER TABLE `alt_logins` DISABLE KEYS */;
/*!40000 ALTER TABLE `alt_logins` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `audit`
--

DROP TABLE IF EXISTS `audit`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `audit` (
  `audit_id` bigint(20) NOT NULL auto_increment,
  `updated` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `x_uuid` varchar(128) NOT NULL,
  `u_uuid` varchar(128) NOT NULL,
  `change_type` varchar(3) NOT NULL,
  `change_table` varchar(100) NOT NULL,
  `change_field` varchar(100) NOT NULL,
  `prev_val` text,
  `new_val` text,
  PRIMARY KEY  (`audit_id`)
) ENGINE=InnoDB AUTO_INCREMENT=187 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `audit`
--

LOCK TABLES `audit` WRITE;
/*!40000 ALTER TABLE `audit` DISABLE KEYS */;
/*!40000 ALTER TABLE `audit` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `config`
--

DROP TABLE IF EXISTS `config`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `config` (
  `config_id` bigint(20) NOT NULL auto_increment,
  `module_id` varchar(20) default NULL,
  `confkey` varchar(50) NOT NULL,
  `value` varchar(100) default NULL,
  PRIMARY KEY  (`config_id`),
  KEY `module_id` (`module_id`)
) ENGINE=InnoDB AUTO_INCREMENT=1996 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `config`
--

LOCK TABLES `config` WRITE;
/*!40000 ALTER TABLE `config` DISABLE KEYS */;
INSERT INTO `config` (`config_id`, `module_id`, `confkey`, `value`) VALUES (3,'admin','acl_base','installed'),(5,'admin','acl_enabled','1');
/*!40000 ALTER TABLE `config` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contact`
--

DROP TABLE IF EXISTS `contact`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `contact` (
  `pgoc_uuid` varchar(128) NOT NULL,
  `opt_contact_type` varchar(10) NOT NULL,
  `contact_value` varchar(100) default NULL,
  PRIMARY KEY  (`pgoc_uuid`,`opt_contact_type`),
  KEY `contact_value` (`contact_value`),
  KEY `opt_contact_type` (`opt_contact_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `contact`
--

LOCK TABLES `contact` WRITE;
/*!40000 ALTER TABLE `contact` DISABLE KEYS */;
/*!40000 ALTER TABLE `contact` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `field_options`
--

DROP TABLE IF EXISTS `field_options`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `field_options` (
  `field_name` varchar(100) default NULL,
  `option_code` varchar(20) default NULL,
  `option_description` varchar(50) default NULL,
  `display_order` int(8) default NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `field_options`
--

LOCK TABLES `field_options` WRITE;
/*!40000 ALTER TABLE `field_options` DISABLE KEYS */;
INSERT INTO `field_options` (`field_name`, `option_code`, `option_description`, `display_order`) VALUES ('opt_status','ali','Alive & Well',NULL),('opt_status','mis','Missing',NULL),('opt_status','inj','Injured',NULL),('opt_status','dec','Deceased',NULL),('opt_gender','mal','Male',NULL),('opt_gender','fml','Female',NULL),('opt_contact_type','home','Home(permanent address)',NULL),('opt_contact_type','name','Contact Person',NULL),('opt_contact_type','pmob','Personal Mobile',NULL),('opt_contact_type','curr','Current Phone',NULL),('opt_contact_type','cmob','Current Mobile',NULL),('opt_contact_type','email','Email address',NULL),('opt_contact_type','fax','Fax Number',NULL),('opt_contact_type','web','Website',NULL),('opt_contact_type','inst','Instant Messenger',NULL),('opt_eye_color','GRN','Green',NULL),('opt_eye_color','GRY','Gray',NULL),('opt_race','R1','American Indian or Alaska Native',NULL),('opt_race',NULL,'Unknown',NULL),('opt_eye_color','BRO','Brown',NULL),('opt_eye_color','BLU','Blue',NULL),('opt_eye_color','BLK','Black',NULL),('opt_skin_color','DRK','Dark',NULL),('opt_country','AFG','Afghanistan',NULL),('opt_skin_color','BLK','Black',NULL),('opt_skin_color','ALB','Albino',NULL),('opt_hair_color','BLN','Blond or Strawberry',NULL),('opt_country','ALA','Åland Islands',NULL),('opt_hair_color','BLK','Black',NULL),('opt_hair_color','BLD','Bald',NULL),('opt_location_type','2','Town or Neighborhood',NULL),('opt_location_type','1','County or Equivalent',NULL),('opt_contact_type','zip','Zip Code',NULL),('opt_eye_color',NULL,'Unknown',NULL),('opt_country','ALB','Albania',NULL),('opt_country','DZA','Algeria',NULL),('opt_country','ASM','American Samoa',NULL),('opt_country','AND','Andorra',NULL),('opt_country','AGO','Angola',NULL),('opt_country','AIA','Anguilla',NULL),('opt_country','ATA','Antarctica',NULL),('opt_country','ATG','Antigua and Barbuda',NULL),('opt_country','ARG','Argentina',NULL),('opt_country','ARM','Armenia',NULL),('opt_country','ABW','Aruba',NULL),('opt_country','AUS','Australia',NULL),('opt_country','AUT','Austria',NULL),('opt_country','AZE','Azerbaijan',NULL),('opt_country','BHS','Bahamas',NULL),('opt_country','BHR','Bahrain',NULL),('opt_country','BGD','Bangladesh',NULL),('opt_country','BRB','Barbados',NULL),('opt_country','BLR','Belarus',NULL),('opt_country','BEL','Belgium',NULL),('opt_country','BLZ','Belize',NULL),('opt_country','BEN','Benin',NULL),('opt_country','BMU','Bermuda',NULL),('opt_country','BTN','Bhutan',NULL),('opt_country','BOL','Bolivia',NULL),('opt_country','BIH','Bosnia and Herzegovina',NULL),('opt_country','BWA','Botswana',NULL),('opt_country','BVT','Bouvet Island',NULL),('opt_country','BRA','Brazil',NULL),('opt_country','IOT','British Indian Ocean Territory',NULL),('opt_country','BRN','Brunei Darussalam',NULL),('opt_country','BGR','Bulgaria',NULL),('opt_country','BFA','Burkina Faso',NULL),('opt_country','BDI','Burundi',NULL),('opt_country','KHM','Cambodia',NULL),('opt_country','CMR','Cameroon',NULL),('opt_country','CAN','Canada',NULL),('opt_country','CPV','Cape Verde',NULL),('opt_country','CYM','Cayman Islands',NULL),('opt_country','CAF','Central African Republic',NULL),('opt_country','TCD','Chad',NULL),('opt_country','CHL','Chile',NULL),('opt_country','CHN','China',NULL),('opt_country','CXR','Christmas Island',NULL),('opt_country','CCK','Cocos (Keeling) Islands',NULL),('opt_country','COL','Colombia',NULL),('opt_country','COM','Comoros',NULL),('opt_country','COG','Congo',NULL),('opt_country','AFG','Afghanistan',NULL),('opt_country','ALA','Åland Islands',NULL),('opt_country','ALB','Albania',NULL),('opt_country','DZA','Algeria',NULL),('opt_country','ASM','American Samoa',NULL),('opt_country','AND','Andorra',NULL),('opt_country','AGO','Angola',NULL),('opt_country','AIA','Anguilla',NULL),('opt_country','ATA','Antarctica',NULL),('opt_country','ATG','Antigua and Barbuda',NULL),('opt_country','ARG','Argentina',NULL),('opt_country','ARM','Armenia',NULL),('opt_country','ABW','Aruba',NULL),('opt_country','AUS','Australia',NULL),('opt_country','AUT','Austria',NULL),('opt_country','AZE','Azerbaijan',NULL),('opt_country','BHS','Bahamas',NULL),('opt_country','BHR','Bahrain',NULL),('opt_country','BGD','Bangladesh',NULL),('opt_country','BRB','Barbados',NULL),('opt_country','BLR','Belarus',NULL),('opt_country','BEL','Belgium',NULL),('opt_country','BLZ','Belize',NULL),('opt_country','BEN','Benin',NULL),('opt_country','BMU','Bermuda',NULL),('opt_country','BTN','Bhutan',NULL),('opt_country','BOL','Bolivia',NULL),('opt_country','BIH','Bosnia and Herzegovina',NULL),('opt_country','BWA','Botswana',NULL),('opt_country','BVT','Bouvet Island',NULL),('opt_country','BRA','Brazil',NULL),('opt_country','IOT','British Indian Ocean Territory',NULL),('opt_country','BRN','Brunei Darussalam',NULL),('opt_country','BGR','Bulgaria',NULL),('opt_country','BFA','Burkina Faso',NULL),('opt_country','BDI','Burundi',NULL),('opt_country','KHM','Cambodia',NULL),('opt_country','CMR','Cameroon',NULL),('opt_country','CAN','Canada',NULL),('opt_country','CPV','Cape Verde',NULL),('opt_country','CYM','Cayman Islands',NULL),('opt_country','CAF','Central African Republic',NULL),('opt_country','TCD','Chad',NULL),('opt_country','CHL','Chile',NULL),('opt_country','CHN','China',NULL),('opt_country','CXR','Christmas Island',NULL),('opt_country','CCK','Cocos (Keeling) Islands',NULL),('opt_country','COL','Colombia',NULL),('opt_country','COM','Comoros',NULL),('opt_country','COG','Congo',NULL),('opt_country','COD','Congo, the Democratic Republic of the',NULL),('opt_country','COK','Cook Islands',NULL),('opt_country','CRI','Costa Rica',NULL),('opt_country','CIV','Côte d\'Ivoire',NULL),('opt_country','HRV','Croatia',NULL),('opt_country','CUB','Cuba',NULL),('opt_country','CYP','Cyprus',NULL),('opt_country','CZE','Czech Republic',NULL),('opt_country','DNK','Denmark',NULL),('opt_country','DJI','Djibouti',NULL),('opt_country','DMA','Dominica',NULL),('opt_country','DOM','Dominican Republic',NULL),('opt_country','ECU','Ecuador',NULL),('opt_country','EGY','Egypt',NULL),('opt_country','SLV','El Salvador',NULL),('opt_country','GNQ','Equatorial Guinea',NULL),('opt_country','ERI','Eritrea',NULL),('opt_country','EST','Estonia',NULL),('opt_country','ETH','Ethiopia',NULL),('opt_country','FLK','Falkland Islands (Malvinas)',NULL),('opt_country','FRO','Faroe Islands',NULL),('opt_country','FJI','Fiji',NULL),('opt_country','FIN','Finland',NULL),('opt_country','FRA','France',NULL),('opt_country','GUF','French Guiana',NULL),('opt_country','PYF','French Polynesia',NULL),('opt_country','ATF','French Southern Territories',NULL),('opt_country','GAB','Gabon',NULL),('opt_country','GMB','Gambia',NULL),('opt_country','GEO','Georgia',NULL),('opt_country','DEU','Germany',NULL),('opt_country','GHA','Ghana',NULL),('opt_country','GIB','Gibraltar',NULL),('opt_country','GRC','Greece',NULL),('opt_country','GRL','Greenland',NULL),('opt_country','GRD','Grenada',NULL),('opt_country','GLP','Guadeloupe',NULL),('opt_country','GUM','Guam',NULL),('opt_country','GTM','Guatemala',NULL),('opt_country','GGY','Guernsey',NULL),('opt_country','GIN','Guinea',NULL),('opt_country','GNB','Guinea-Bissau',NULL),('opt_country','GUY','Guyana',NULL),('opt_country','HTI','Haiti',NULL),('opt_country','HMD','Heard Island and McDonald Islands',NULL),('opt_country','VAT','Holy See (Vatican City State)',NULL),('opt_country','HND','Honduras',NULL),('opt_country','HKG','Hong Kong',NULL),('opt_country','HUN','Hungary',NULL),('opt_country','ISL','Iceland',NULL),('opt_country','IND','India',NULL),('opt_country','IDN','Indonesia',NULL),('opt_country','IRN','Iran, Islamic Republic of',NULL),('opt_country','IRQ','Iraq',NULL),('opt_country','IRL','Ireland',NULL),('opt_country','IMN','Isle of Man',NULL),('opt_country','ISR','Israel',NULL),('opt_country','ITA','Italy',NULL),('opt_country','JAM','Jamaica',NULL),('opt_country','JPN','Japan',NULL),('opt_country','JEY','Jersey',NULL),('opt_country','JOR','Jordan',NULL),('opt_country','KAZ','Kazakhstan',NULL),('opt_country','KEN','Kenya',NULL),('opt_country','KIR','Kiribati',NULL),('opt_country','PRK','Korea, Democratic People\'s Republic of',NULL),('opt_country','KOR','Korea, Republic of',NULL),('opt_country','KWT','Kuwait',NULL),('opt_country','KGZ','Kyrgyzstan',NULL),('opt_country','LAO','Lao People\'s Democratic Republic',NULL),('opt_country','LVA','Latvia',NULL),('opt_country','LBN','Lebanon',NULL),('opt_country','LSO','Lesotho',NULL),('opt_country','LBR','Liberia',NULL),('opt_country','LBY','Libyan Arab Jamahiriya',NULL),('opt_country','LIE','Liechtenstein',NULL),('opt_country','LTU','Lithuania',NULL),('opt_country','LUX','Luxembourg',NULL),('opt_country','MAC','Macao',NULL),('opt_country','MKD','Macedonia, the former Yugoslav Republic of',NULL),('opt_country','MDG','Madagascar',NULL),('opt_country','MWI','Malawi',NULL),('opt_country','MYS','Malaysia',NULL),('opt_country','MDV','Maldives',NULL),('opt_country','MLI','Mali',NULL),('opt_country','MLT','Malta',NULL),('opt_country','MHL','Marshall Islands',NULL),('opt_country','MTQ','Martinique',NULL),('opt_country','MRT','Mauritania',NULL),('opt_country','MUS','Mauritius',NULL),('opt_country','MYT','Mayotte',NULL),('opt_country','MEX','Mexico',NULL),('opt_country','FSM','Micronesia, Federated States of',NULL),('opt_country','MDA','Moldova, Republic of',NULL),('opt_country','MCO','Monaco',NULL),('opt_country','MNG','Mongolia',NULL),('opt_country','MNE','Montenegro',NULL),('opt_country','MSR','Montserrat',NULL),('opt_country','MAR','Maroon',NULL),('opt_country','MOZ','Mozambique',NULL),('opt_country','MMR','Myanmar',NULL),('opt_country','NAM','Namibia',NULL),('opt_country','NRU','Nauru',NULL),('opt_country','NPL','Nepal',NULL),('opt_country','NLD','Netherlands',NULL),('opt_country','ANT','Netherlands Antilles',NULL),('opt_country','NCL','New Caledonia',NULL),('opt_country','NZL','New Zealand',NULL),('opt_country','NIC','Nicaragua',NULL),('opt_country','NER','Niger',NULL),('opt_country','NGA','Nigeria',NULL),('opt_country','NIU','Niue',NULL),('opt_country','NFK','Norfolk Island',NULL),('opt_country','MNP','Northern Mariana Islands',NULL),('opt_country','NOR','Norway',NULL),('opt_country','OMN','Oman',NULL),('opt_country','PAK','Pakistan',NULL),('opt_country','PLW','Palau',NULL),('opt_country','PSE','Palestinian Territory, Occupied',NULL),('opt_country','PAN','Panama',NULL),('opt_country','PNG','Papua New Guinea',NULL),('opt_country','PRY','Paraguay',NULL),('opt_country','PER','Peru',NULL),('opt_country','PHL','Philippines',NULL),('opt_country','PCN','Pitcairn',NULL),('opt_country','POL','Poland',NULL),('opt_country','PRT','Portugal',NULL),('opt_country','PRI','Puerto Rico',NULL),('opt_country','QAT','Qatar',NULL),('opt_country','REU','Réunion',NULL),('opt_country','ROU','Romania',NULL),('opt_country','RUS','Russian Federation',NULL),('opt_country','RWA','Rwanda',NULL),('opt_country','BLM','Saint Barthélemy',NULL),('opt_country','SHN','Saint Helena',NULL),('opt_country','KNA','Saint Kitts and Nevis',NULL),('opt_country','LCA','Saint Lucia',NULL),('opt_country','MAF','Saint Martin (French part)',NULL),('opt_country','SPM','Saint Pierre and Miquelon',NULL),('opt_country','VCT','Saint Vincent and the Grenadines',NULL),('opt_country','WSM','Samoa',NULL),('opt_country','SMR','San Marino',NULL),('opt_country','STP','Sao Tome and Principe',NULL),('opt_country','SAU','Saudi Arabia',NULL),('opt_country','SEN','Senegal',NULL),('opt_country','SRB','Serbia',NULL),('opt_country','SYC','Seychelles',NULL),('opt_country','SLE','Sierra Leone',NULL),('opt_country','SGP','Singapore',NULL),('opt_country','SVK','Slovakia',NULL),('opt_country','SVN','Slovenia',NULL),('opt_country','SLB','Solomon Islands',NULL),('opt_country','SOM','Somalia',NULL),('opt_country','ZAF','South Africa',NULL),('opt_country','SGS','South Georgia and the South Sandwich Islands',NULL),('opt_country','ESP','Spain',NULL),('opt_country','LKA','Sri Lanka',NULL),('opt_country','SDN','Sudan',NULL),('opt_country','SUR','Suriname',NULL),('opt_country','SJM','Svalbard and Jan Mayen',NULL),('opt_country','SWZ','Swaziland',NULL),('opt_country','SWE','Sweden',NULL),('opt_country','CHE','Switzerland',NULL),('opt_country','SYR','Syrian Arab Republic',NULL),('opt_country','TWN','Taiwan, Province of China',NULL),('opt_country','TJK','Tajikistan',NULL),('opt_country','TZA','Tanzania, United Republic of',NULL),('opt_country','THA','Thailand',NULL),('opt_country','TLS','Timor-Leste',NULL),('opt_country','TGO','Togo',NULL),('opt_country','TKL','Tokelau',NULL),('opt_country','TON','Tonga',NULL),('opt_country','TTO','Trinidad and Tobago',NULL),('opt_country','TUN','Tunisia',NULL),('opt_country','TUR','Turkey',NULL),('opt_country','TKM','Turkmenistan',NULL),('opt_country','TCA','Turks and Caicos Islands',NULL),('opt_country','TUV','Tuvalu',NULL),('opt_country','UGA','Uganda',NULL),('opt_country','UKR','Ukraine',NULL),('opt_country','ARE','United Arab Emirates',NULL),('opt_country','GBR','United Kingdom',NULL),('opt_country','USA','United States',NULL),('opt_country','UMI','United States Minor Outlying Islands',NULL),('opt_country','URY','Uruguay',NULL),('opt_country','UZB','Uzbekistan',NULL),('opt_country','VUT','Vanuatu',NULL),('opt_country','VEN','Venezuela, Bolivarian Republic of',NULL),('opt_country','VNM','Viet Nam',NULL),('opt_country','VGB','Virgin Islands, British',NULL),('opt_country','VIR','Virgin Islands, U.S.',NULL),('opt_country','WLF','Wallis and Futuna',NULL),('opt_country','ESH','Western Sahara',NULL),('opt_country','YEM','Yemen',NULL),('opt_country','ZMB','Zambia',NULL),('opt_country','ZWE','Zimbabwe',NULL),('opt_eye_color','HAZ','Hazel',NULL),('opt_eye_color','MAR','Maroon',NULL),('opt_eye_color','MUL','Multicolored',NULL),('opt_eye_color','PNK','Pink',NULL),('opt_skin_color','DBR','Dark Brown',NULL),('opt_skin_color','FAR','Fair',NULL),('opt_skin_color','LGT','Light',NULL),('opt_skin_color','LBR','Light Brown',NULL),('opt_skin_color','MED','Medium',NULL),('opt_skin_color',NULL,'Unknown',NULL),('opt_skin_color','OLV','Olive',NULL),('opt_skin_color','RUD','Ruddy',NULL),('opt_skin_color','SAL','Sallow',NULL),('opt_skin_color','YEL','Yellow',NULL),('opt_hair_color','BLU','Blue',NULL),('opt_hair_color','BRO','Brown',NULL),('opt_hair_color','GRY','Gray',NULL),('opt_hair_color','GRN','Green',NULL),('opt_hair_color','ONG','Orange',NULL),('opt_hair_color','PLE','Purple',NULL),('opt_hair_color','PNK','Pink',NULL),('opt_hair_color','RED','Red or Auburn',NULL),('opt_hair_color','SDY','Sandy',NULL),('opt_hair_color','WHI','White',NULL),('opt_race','R2','Asian',NULL),('opt_race','R3','Black or African American',NULL),('opt_race','R4','Native Hawaiian or Other Pacific Islander',NULL),('opt_race','R5','White',NULL),('opt_race','R9','Other Race',NULL),('opt_religion','PEV','Protestant, Evangelical',1),('opt_religion','PML','Protestant, Mainline',2),('opt_religion','PHB','Protestant, Historically Black',3),('opt_religion','CAT','Catholic',4),('opt_religion','MOM','Mormon',5),('opt_religion','JWN','Jehovah\'s Witness',6),('opt_religion','ORT','Orthodox',7),('opt_religion','COT','Other Christian',8),('opt_religion','JEW','Jewish',9),('opt_religion','BUD','Buddhist',10),('opt_religion','HIN','Hindu',11),('opt_religion','MOS','Muslim',12),('opt_religion','OTH','Other Faiths',13),('opt_religion','NOE','Unaffiliated',14),('opt_religion',NULL,'Unknown',15),('opt_hair_color',NULL,'Unknown',NULL),('opt_skin_color','MBR','Medium Brown',NULL),('opt_gender',NULL,'Unknown',NULL),('opt_gender','cpx','Complex',NULL),('opt_status','unk','Unknown',NULL),('opt_status','fnd','Found',NULL),('opt_country',NULL,'Unknown',NULL);
/*!40000 ALTER TABLE `field_options` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `hospital`
--

DROP TABLE IF EXISTS `hospital`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `hospital` (
  `hospital_uuid` int(32) NOT NULL auto_increment,
  `name` varchar(60) NOT NULL,
  `short_name` varchar(30) NOT NULL,
  `street1` varchar(120) NOT NULL,
  `street2` varchar(120) default NULL,
  `city` varchar(60) NOT NULL,
  `county` varchar(60) NOT NULL,
  `region` varchar(60) NOT NULL,
  `postal_code` varchar(16) NOT NULL,
  `country` varchar(32) NOT NULL,
  `latitude` double NOT NULL,
  `longitude` double NOT NULL,
  `phone` varchar(16) default NULL,
  `fax` varchar(16) default NULL,
  `email` varchar(64) default NULL,
  `www` varchar(256) default NULL,
  `npi` varchar(32) default NULL,
  `patient_id_prefix` varchar(32) NOT NULL,
  `patient_id_suffix_variable` int(11) NOT NULL default '1',
  `patient_id_suffix_fixed_length` int(11) NOT NULL default '0',
  `creation_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `icon_url` varchar(128) default NULL,
  PRIMARY KEY  (`hospital_uuid`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `hospital`
--

LOCK TABLES `hospital` WRITE;
/*!40000 ALTER TABLE `hospital` DISABLE KEYS */;
INSERT INTO `hospital` (`hospital_uuid`, `name`, `short_name`, `street1`, `street2`, `city`, `county`, `region`, `postal_code`, `country`, `latitude`, `longitude`, `phone`, `fax`, `email`, `www`, `npi`, `patient_id_prefix`, `patient_id_suffix_variable`, `patient_id_suffix_fixed_length`, `creation_time`, `icon_url`) VALUES (1,'Suburban Hospital','sh','8600 Old Georgetown Rd',NULL,'Bethesda','Montgomery','MD','20817','USA',38.99731,-77.10984,'3018963100',NULL,NULL,NULL,NULL,'911-',1,0,'2010-01-01 06:01:01','theme/lpf3/img/suburban.png'),(2,'National Naval Medical Center','nnmc','National Naval Medical Center',NULL,'Bethesda','Montgomery','MD','20889','US',39.00204,-77.0945,'3012954611',NULL,NULL,NULL,NULL,'000-',1,0,'2010-09-22 22:49:34','theme/lpf3/img/nnmc.png');
/*!40000 ALTER TABLE `hospital` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `image`
--

DROP TABLE IF EXISTS `image`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `image` (
  `image_id` bigint(20) NOT NULL auto_increment,
  `x_uuid` varchar(128) NOT NULL,
  `image_type` varchar(100) NOT NULL,
  `image_height` int(11) default NULL,
  `image_width` int(11) default NULL,
  `created` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `category` varchar(32) default NULL,
  `url` varchar(512) default NULL,
  `url_thumb` varchar(512) default NULL,
  `original_filename` varchar(64) default NULL,
  `crop_x` int(16) default NULL,
  `crop_y` int(16) default NULL,
  `crop_w` int(16) default NULL,
  `crop_h` int(16) default NULL,
  `full_path` varchar(512) default NULL,
  PRIMARY KEY  (`image_id`),
  UNIQUE KEY `image_id` (`x_uuid`)
) ENGINE=InnoDB AUTO_INCREMENT=57125 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `image`
--

LOCK TABLES `image` WRITE;
/*!40000 ALTER TABLE `image` DISABLE KEYS */;
/*!40000 ALTER TABLE `image` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `image_tag`
--

DROP TABLE IF EXISTS `image_tag`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `image_tag` (
  `tag_id` int(12) NOT NULL auto_increment,
  `image_id` bigint(20) NOT NULL,
  `tag_x` int(12) NOT NULL,
  `tag_y` int(12) NOT NULL,
  `tag_w` int(12) NOT NULL,
  `tag_h` int(12) NOT NULL,
  `tag_text` varchar(128) NOT NULL,
  PRIMARY KEY  (`tag_id`),
  KEY `tag_id` (`tag_id`,`image_id`),
  KEY `image_id` (`image_id`),
  CONSTRAINT `image_tag_ibfk_1` FOREIGN KEY (`image_id`) REFERENCES `image` (`image_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `image_tag_ibfk_2` FOREIGN KEY (`image_id`) REFERENCES `image` (`image_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `image_tag`
--

LOCK TABLES `image_tag` WRITE;
/*!40000 ALTER TABLE `image_tag` DISABLE KEYS */;
/*!40000 ALTER TABLE `image_tag` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `incident`
--

DROP TABLE IF EXISTS `incident`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `incident` (
  `incident_id` bigint(20) NOT NULL auto_increment,
  `parent_id` bigint(20) default NULL,
  `search_id` varchar(60) default NULL,
  `name` varchar(60) default NULL,
  `shortname` varchar(16) default NULL,
  `date` date default NULL,
  `type` varchar(32) default NULL,
  `latitude` double default NULL,
  `longitude` double default NULL,
  `default` tinyint(1) default NULL,
  `private_group` int(16) default NULL,
  `closed` tinyint(1) NOT NULL default '0',
  `description` varchar(1024) default NULL,
  `street` varchar(256) default NULL,
  `external_report` varchar(8192) default NULL,
  PRIMARY KEY  (`incident_id`),
  UNIQUE KEY `shortname_idx` (`shortname`),
  KEY `parent_id` (`parent_id`)
) ENGINE=InnoDB AUTO_INCREMENT=28 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `incident`
--

LOCK TABLES `incident` WRITE;
/*!40000 ALTER TABLE `incident` DISABLE KEYS */;
INSERT INTO `incident` (`incident_id`, `parent_id`, `search_id`, `name`, `shortname`, `date`, `type`, `latitude`, `longitude`, `default`, `private_group`, `closed`, `description`, `street`, `external_report`) VALUES (1,NULL,NULL,'Test Exercise','test','2000-01-01','TEST',0,0,1,NULL,0,'','','');
/*!40000 ALTER TABLE `incident` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `lc_fields`
--

DROP TABLE IF EXISTS `lc_fields`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `lc_fields` (
  `id` bigint(20) NOT NULL auto_increment,
  `tablename` varchar(32) NOT NULL,
  `fieldname` varchar(32) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `lc_fields`
--

LOCK TABLES `lc_fields` WRITE;
/*!40000 ALTER TABLE `lc_fields` DISABLE KEYS */;
INSERT INTO `lc_fields` (`id`, `tablename`, `fieldname`) VALUES (1,'field_options','option_description'),(2,'ct_unit','name'),(3,'ct_unit_type','name'),(4,'ct_unit_type','description');
/*!40000 ALTER TABLE `lc_fields` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `loc_seq_seq`
--

DROP TABLE IF EXISTS `loc_seq_seq`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `loc_seq_seq` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `loc_seq_seq`
--

LOCK TABLES `loc_seq_seq` WRITE;
/*!40000 ALTER TABLE `loc_seq_seq` DISABLE KEYS */;
INSERT INTO `loc_seq_seq` (`id`) VALUES (0);
/*!40000 ALTER TABLE `loc_seq_seq` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `location`
--

DROP TABLE IF EXISTS `location`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `location` (
  `loc_uuid` varchar(60) NOT NULL,
  `parent_id` varchar(60) default NULL,
  `opt_location_type` varchar(10) default NULL,
  `name` varchar(100) NOT NULL,
  `iso_code` varchar(20) default NULL,
  `description` text,
  PRIMARY KEY  (`loc_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `location`
--

LOCK TABLES `location` WRITE;
/*!40000 ALTER TABLE `location` DISABLE KEYS */;
/*!40000 ALTER TABLE `location` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `location_details`
--

DROP TABLE IF EXISTS `location_details`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `location_details` (
  `poc_uuid` varchar(128) NOT NULL,
  `location_id` varchar(60) NOT NULL default '',
  `opt_person_loc_type` varchar(10) default NULL,
  `address` text,
  `postcode` varchar(30) default NULL,
  `long_lat` varchar(20) default NULL,
  PRIMARY KEY  (`poc_uuid`,`location_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `location_details`
--

LOCK TABLES `location_details` WRITE;
/*!40000 ALTER TABLE `location_details` DISABLE KEYS */;
/*!40000 ALTER TABLE `location_details` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `mpres_log`
--

DROP TABLE IF EXISTS `mpres_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `mpres_log` (
  `log_index` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `email_subject` varchar(256) NOT NULL,
  `email_from` varchar(128) NOT NULL,
  `email_date` varchar(64) NOT NULL,
  `update_time` datetime NOT NULL,
  PRIMARY KEY  (`log_index`),
  KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `mpres_log_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `mpres_log_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=382 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `mpres_log`
--

LOCK TABLES `mpres_log` WRITE;
/*!40000 ALTER TABLE `mpres_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `mpres_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `old_passwords`
--

DROP TABLE IF EXISTS `old_passwords`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `old_passwords` (
  `p_uuid` varchar(60) NOT NULL,
  `password` varchar(100) NOT NULL default '',
  `changed_timestamp` bigint(20) NOT NULL,
  PRIMARY KEY  (`p_uuid`,`password`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `old_passwords`
--

LOCK TABLES `old_passwords` WRITE;
/*!40000 ALTER TABLE `old_passwords` DISABLE KEYS */;
/*!40000 ALTER TABLE `old_passwords` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `password_event_log`
--

DROP TABLE IF EXISTS `password_event_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `password_event_log` (
  `log_id` bigint(20) NOT NULL auto_increment,
  `changed_timestamp` bigint(20) NOT NULL,
  `p_uuid` varchar(128) NOT NULL,
  `user_name` varchar(100) NOT NULL,
  `comment` varchar(100) NOT NULL,
  `event_type` int(11) default '1',
  PRIMARY KEY  (`log_id`),
  KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `password_event_log_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `password_event_log_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=245 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `password_event_log`
--

LOCK TABLES `password_event_log` WRITE;
/*!40000 ALTER TABLE `password_event_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `password_event_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_deceased`
--

DROP TABLE IF EXISTS `person_deceased`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_deceased` (
  `deceased_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `details` text,
  `date_of_death` date default NULL,
  `location` varchar(20) default NULL,
  `place_of_death` text,
  `comments` text,
  PRIMARY KEY  (`deceased_id`),
  UNIQUE KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `person_deceased_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_deceased_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_deceased`
--

LOCK TABLES `person_deceased` WRITE;
/*!40000 ALTER TABLE `person_deceased` DISABLE KEYS */;
/*!40000 ALTER TABLE `person_deceased` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_details`
--

DROP TABLE IF EXISTS `person_details`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_details` (
  `details_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `next_kin_uuid` varchar(128) default NULL,
  `birth_date` date default NULL,
  `opt_age_group` varchar(10) default NULL,
  `relation` varchar(50) default NULL,
  `opt_country` varchar(10) default NULL,
  `opt_race` varchar(10) default NULL,
  `opt_religion` varchar(10) default NULL,
  `opt_marital_status` varchar(10) default NULL,
  `opt_gender` varchar(10) default NULL,
  `occupation` varchar(100) default NULL,
  `years_old` int(7) default NULL,
  `minAge` int(7) default NULL,
  `maxAge` int(7) default NULL,
  `last_seen` text,
  `last_clothing` text,
  `other_comments` text,
  PRIMARY KEY  (`details_id`),
  UNIQUE KEY `p_uuid` (`p_uuid`),
  UNIQUE KEY `search_index` (`p_uuid`,`opt_age_group`,`opt_gender`,`years_old`),
  CONSTRAINT `person_details_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_details_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1657795 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_details`
--

LOCK TABLES `person_details` WRITE;
/*!40000 ALTER TABLE `person_details` DISABLE KEYS */;
/*!40000 ALTER TABLE `person_details` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_followers`
--

DROP TABLE IF EXISTS `person_followers`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_followers` (
  `id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `follower_p_uuid` varchar(128) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `p_uuid` (`p_uuid`),
  KEY `follower_p_uuid` (`follower_p_uuid`),
  CONSTRAINT `person_followers_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_followers_ibfk_2` FOREIGN KEY (`follower_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_followers_ibfk_3` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_followers_ibfk_4` FOREIGN KEY (`follower_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_followers`
--

LOCK TABLES `person_followers` WRITE;
/*!40000 ALTER TABLE `person_followers` DISABLE KEYS */;
/*!40000 ALTER TABLE `person_followers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_notes`
--

DROP TABLE IF EXISTS `person_notes`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_notes` (
  `note_id` int(11) NOT NULL auto_increment,
  `note_about_p_uuid` varchar(60) NOT NULL,
  `note_written_by_p_uuid` varchar(60) NOT NULL,
  `note` varchar(1024) NOT NULL,
  `when` timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (`note_id`),
  KEY `note_about_p_uuid` (`note_about_p_uuid`),
  KEY `note_written_by_p_uuid` (`note_written_by_p_uuid`),
  CONSTRAINT `person_notes_ibfk_1` FOREIGN KEY (`note_about_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_notes_ibfk_2` FOREIGN KEY (`note_written_by_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_notes_ibfk_3` FOREIGN KEY (`note_about_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_notes_ibfk_4` FOREIGN KEY (`note_written_by_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_notes`
--

LOCK TABLES `person_notes` WRITE;
/*!40000 ALTER TABLE `person_notes` DISABLE KEYS */;
/*!40000 ALTER TABLE `person_notes` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_physical`
--

DROP TABLE IF EXISTS `person_physical`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_physical` (
  `physical_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `opt_blood_type` varchar(10) default NULL,
  `height` varchar(10) default NULL,
  `weight` varchar(10) default NULL,
  `opt_eye_color` varchar(50) default NULL,
  `opt_skin_color` varchar(50) default NULL,
  `opt_hair_color` varchar(50) default NULL,
  `injuries` text,
  `comments` text,
  PRIMARY KEY  (`physical_id`),
  UNIQUE KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `person_physical_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_physical_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1664419 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_physical`
--

LOCK TABLES `person_physical` WRITE;
/*!40000 ALTER TABLE `person_physical` DISABLE KEYS */;
/*!40000 ALTER TABLE `person_physical` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary table structure for view `person_search`
--

DROP TABLE IF EXISTS `person_search`;
/*!50001 DROP VIEW IF EXISTS `person_search`*/;
/*!50001 CREATE TABLE `person_search` (
  `p_uuid` varchar(128),
  `full_name` varchar(100),
  `given_name` varchar(50),
  `family_name` varchar(50),
  `opt_status` varchar(3),
  `updated` datetime,
  `opt_gender` varchar(10),
  `years_old` bigint(11),
  `image_height` int(11),
  `image_width` int(11),
  `url_thumb` varchar(512),
  `icon_url` varchar(128),
  `shortname` varchar(16),
  `hospital` varchar(30),
  `comments` text,
  `last_seen` text
) ENGINE=MyISAM */;

--
-- Table structure for table `person_seq`
--

DROP TABLE IF EXISTS `person_seq`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_seq` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_seq`
--

LOCK TABLES `person_seq` WRITE;
/*!40000 ALTER TABLE `person_seq` DISABLE KEYS */;
INSERT INTO `person_seq` (`id`) VALUES (4);
/*!40000 ALTER TABLE `person_seq` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_status`
--

DROP TABLE IF EXISTS `person_status`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_status` (
  `status_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `isReliefWorker` tinyint(4) default NULL,
  `opt_status` varchar(3) default NULL,
  `last_updated` datetime default NULL,
  `isvictim` tinyint(1) default '1',
  `creation_time` datetime default NULL,
  PRIMARY KEY  (`status_id`),
  UNIQUE KEY `p_uuid` (`p_uuid`),
  KEY `search_index` (`opt_status`,`last_updated`,`isvictim`),
  CONSTRAINT `person_status_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_status_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3320034 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_status`
--

LOCK TABLES `person_status` WRITE;
/*!40000 ALTER TABLE `person_status` DISABLE KEYS */;
/*!40000 ALTER TABLE `person_status` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_to_report`
--

DROP TABLE IF EXISTS `person_to_report`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_to_report` (
  `p_uuid` varchar(128) NOT NULL,
  `rep_uuid` varchar(128) NOT NULL,
  `relation` varchar(100) default NULL,
  PRIMARY KEY  (`p_uuid`,`rep_uuid`),
  CONSTRAINT `person_to_report_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_to_report_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_to_report`
--

LOCK TABLES `person_to_report` WRITE;
/*!40000 ALTER TABLE `person_to_report` DISABLE KEYS */;
/*!40000 ALTER TABLE `person_to_report` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_updates`
--

DROP TABLE IF EXISTS `person_updates`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_updates` (
  `update_index` int(32) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `update_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `updated_table` varchar(64) NOT NULL,
  `updated_column` varchar(64) NOT NULL,
  `old_value` varchar(512) NOT NULL,
  `new_value` varchar(512) NOT NULL,
  `updated_by_p_uuid` varchar(128) NOT NULL,
  PRIMARY KEY  (`update_index`),
  KEY `p_uuid` (`p_uuid`),
  KEY `updated_by_p_uuid` (`updated_by_p_uuid`),
  CONSTRAINT `person_updates_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_updates_ibfk_2` FOREIGN KEY (`updated_by_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_updates_ibfk_3` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `person_updates_ibfk_4` FOREIGN KEY (`updated_by_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=124 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_updates`
--

LOCK TABLES `person_updates` WRITE;
/*!40000 ALTER TABLE `person_updates` DISABLE KEYS */;
/*!40000 ALTER TABLE `person_updates` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `person_uuid`
--

DROP TABLE IF EXISTS `person_uuid`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `person_uuid` (
  `p_uuid` varchar(128) NOT NULL,
  `full_name` varchar(100) default NULL,
  `family_name` varchar(50) default NULL,
  `l10n_name` varchar(100) default NULL,
  `custom_name` varchar(50) default NULL,
  `given_name` varchar(50) default NULL,
  `incident_id` bigint(20) NOT NULL,
  `hospital_uuid` varchar(60) default NULL,
  `expiry_date` datetime default NULL,
  PRIMARY KEY  (`p_uuid`),
  UNIQUE KEY `search_index` (`p_uuid`,`full_name`,`incident_id`,`hospital_uuid`),
  KEY `full_name_idx` (`full_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `person_uuid`
--

LOCK TABLES `person_uuid` WRITE;
/*!40000 ALTER TABLE `person_uuid` DISABLE KEYS */;
INSERT INTO `person_uuid` (`p_uuid`, `full_name`, `family_name`, `l10n_name`, `custom_name`, `given_name`, `incident_id`, `hospital_uuid`, `expiry_date`) VALUES ('1','Root /','/',NULL,NULL,'Root',0,NULL,NULL),('3','Anonymous User','User',NULL,NULL,'Anonymous',0,NULL,NULL);
/*!40000 ALTER TABLE `person_uuid` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pfif_export_log`
--

DROP TABLE IF EXISTS `pfif_export_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pfif_export_log` (
  `log_index` int(11) NOT NULL auto_increment,
  `repository_id` int(11) default '0',
  `direction` varchar(3) NOT NULL default 'in',
  `status` varchar(10) NOT NULL,
  `start_mode` varchar(10) NOT NULL,
  `start_time` datetime default NULL,
  `end_time` datetime default NULL,
  `first_entry` datetime NOT NULL,
  `last_entry` datetime NOT NULL,
  `last_count` int(11) default '0',
  `person_count` int(11) default '0',
  PRIMARY KEY  (`log_index`),
  KEY `repository_id` (`repository_id`),
  CONSTRAINT `pfif_export_log_ibfk_1` FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `pfif_export_log_ibfk_2` FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `pfif_export_log`
--

LOCK TABLES `pfif_export_log` WRITE;
/*!40000 ALTER TABLE `pfif_export_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `pfif_export_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pfif_harvest_note_log`
--

DROP TABLE IF EXISTS `pfif_harvest_note_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pfif_harvest_note_log` (
  `log_index` int(11) NOT NULL auto_increment,
  `repository_id` int(11) default '0',
  `direction` varchar(3) NOT NULL default 'in',
  `status` varchar(10) NOT NULL,
  `start_mode` varchar(10) NOT NULL,
  `start_time` datetime default NULL,
  `end_time` datetime default NULL,
  `first_entry` datetime NOT NULL,
  `last_entry` datetime NOT NULL,
  `last_count` int(11) default '0',
  `note_count` int(11) default '0',
  PRIMARY KEY  (`log_index`),
  KEY `repository_id` (`repository_id`),
  CONSTRAINT `pfif_harvest_note_log_ibfk_1` FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `pfif_harvest_note_log_ibfk_2` FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `pfif_harvest_note_log`
--

LOCK TABLES `pfif_harvest_note_log` WRITE;
/*!40000 ALTER TABLE `pfif_harvest_note_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `pfif_harvest_note_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pfif_harvest_person_log`
--

DROP TABLE IF EXISTS `pfif_harvest_person_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pfif_harvest_person_log` (
  `log_index` int(11) NOT NULL auto_increment,
  `repository_id` int(11) default '0',
  `direction` varchar(3) NOT NULL default 'in',
  `status` varchar(10) NOT NULL,
  `start_mode` varchar(10) NOT NULL,
  `start_time` datetime default NULL,
  `end_time` datetime default NULL,
  `first_entry` datetime NOT NULL,
  `last_entry` datetime NOT NULL,
  `last_count` int(11) default '0',
  `person_count` int(11) default '0',
  `images_in` int(11) default '0',
  `images_retried` int(11) default '0',
  `images_failed` int(11) default '0',
  PRIMARY KEY  (`log_index`),
  KEY `repository_id` (`repository_id`),
  CONSTRAINT `pfif_harvest_person_log_ibfk_1` FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `pfif_harvest_person_log_ibfk_2` FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `pfif_harvest_person_log`
--

LOCK TABLES `pfif_harvest_person_log` WRITE;
/*!40000 ALTER TABLE `pfif_harvest_person_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `pfif_harvest_person_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pfif_note`
--

DROP TABLE IF EXISTS `pfif_note`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pfif_note` (
  `note_record_id` varchar(128) NOT NULL,
  `p_uuid` varchar(128) NOT NULL,
  `source_version` varchar(10) NOT NULL,
  `source_repository_id` int(11) NOT NULL,
  `linked_person_record_id` varchar(128) default NULL,
  `entry_date` datetime NOT NULL,
  `author_name` varchar(100) default NULL,
  `author_email` varchar(100) default NULL,
  `author_phone` varchar(100) default NULL,
  `source_date` datetime NOT NULL,
  `found` varchar(5) default NULL,
  `status` varchar(20) default NULL,
  `email_of_found_person` varchar(100) default NULL,
  `phone_of_found_person` varchar(100) default NULL,
  `last_known_location` text,
  `text` text,
  PRIMARY KEY  (`note_record_id`),
  KEY `p_uuid` (`p_uuid`),
  KEY `source_repository_id` (`source_repository_id`),
  KEY `linked_person_record_id` (`linked_person_record_id`),
  CONSTRAINT `pfif_note_ibfk_2` FOREIGN KEY (`source_repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='IMPORT WILL FAIL if you add foreign key constraints.';
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `pfif_note`
--

LOCK TABLES `pfif_note` WRITE;
/*!40000 ALTER TABLE `pfif_note` DISABLE KEYS */;
/*!40000 ALTER TABLE `pfif_note` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pfif_note_seq`
--

DROP TABLE IF EXISTS `pfif_note_seq`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pfif_note_seq` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `pfif_note_seq`
--

LOCK TABLES `pfif_note_seq` WRITE;
/*!40000 ALTER TABLE `pfif_note_seq` DISABLE KEYS */;
INSERT INTO `pfif_note_seq` (`id`) VALUES (1);
/*!40000 ALTER TABLE `pfif_note_seq` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pfif_person`
--

DROP TABLE IF EXISTS `pfif_person`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pfif_person` (
  `p_uuid` varchar(128) NOT NULL,
  `source_version` varchar(10) NOT NULL,
  `source_repository_id` int(11) NOT NULL,
  `entry_date` datetime NOT NULL,
  `expiry_date` datetime default NULL,
  `author_name` varchar(100) default NULL,
  `author_email` varchar(100) default NULL,
  `author_phone` varchar(100) default NULL,
  `source_name` varchar(100) default NULL,
  `source_date` datetime default NULL,
  `source_url` varchar(512) default NULL,
  `full_name` varchar(128) default NULL,
  `first_name` varchar(100) default NULL,
  `last_name` varchar(100) default NULL,
  `home_city` varchar(100) default NULL,
  `home_state` varchar(15) default NULL,
  `home_country` varchar(2) default NULL,
  `home_neighborhood` varchar(100) default NULL,
  `home_street` varchar(100) default NULL,
  `home_postal_code` varchar(16) default NULL,
  `photo_url` varchar(512) default NULL,
  `sex` varchar(10) default NULL,
  `date_of_birth` date default NULL,
  `age` varchar(10) default NULL,
  `other` text,
  PRIMARY KEY  (`p_uuid`),
  KEY `source_repository_id` (`source_repository_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `pfif_person`
--

LOCK TABLES `pfif_person` WRITE;
/*!40000 ALTER TABLE `pfif_person` DISABLE KEYS */;
/*!40000 ALTER TABLE `pfif_person` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pfif_repository`
--

DROP TABLE IF EXISTS `pfif_repository`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pfif_repository` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(100) NOT NULL,
  `base_url` varchar(512) NOT NULL,
  `resource_type` varchar(6) NOT NULL default 'person',
  `role` varchar(6) NOT NULL,
  `granularity` varchar(20) default NULL,
  `deleted_record` varchar(10) default NULL,
  `params` varchar(1000) default NULL,
  `sched_interval_minutes` int(11) default '60',
  `log_granularity` varchar(20) default NULL,
  `first_entry` datetime default NULL,
  `last_entry` datetime default NULL,
  `total_persons` int(11) default '0',
  `total_notes` int(11) default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `pfif_repository`
--

LOCK TABLES `pfif_repository` WRITE;
/*!40000 ALTER TABLE `pfif_repository` DISABLE KEYS */;
/*!40000 ALTER TABLE `pfif_repository` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `phonetic_word`
--

DROP TABLE IF EXISTS `phonetic_word`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `phonetic_word` (
  `encode1` varchar(50) default NULL,
  `encode2` varchar(50) default NULL,
  `pgl_uuid` varchar(128) default NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `phonetic_word`
--

LOCK TABLES `phonetic_word` WRITE;
/*!40000 ALTER TABLE `phonetic_word` DISABLE KEYS */;
/*!40000 ALTER TABLE `phonetic_word` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `plus_access_log`
--

DROP TABLE IF EXISTS `plus_access_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `plus_access_log` (
  `access_id` int(16) NOT NULL auto_increment,
  `access_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `application` varchar(32) default NULL,
  `version` varchar(16) default NULL,
  `ip` varchar(16) default NULL,
  `call` varchar(64) default NULL,
  `api_version` varchar(8) default NULL,
  PRIMARY KEY  (`access_id`)
) ENGINE=InnoDB AUTO_INCREMENT=454 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `plus_access_log`
--

LOCK TABLES `plus_access_log` WRITE;
/*!40000 ALTER TABLE `plus_access_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `plus_access_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `plus_report_log`
--

DROP TABLE IF EXISTS `plus_report_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `plus_report_log` (
  `report_id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `report_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (`report_id`),
  KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `plus_report_log_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `plus_report_log_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `plus_report_log`
--

LOCK TABLES `plus_report_log` WRITE;
/*!40000 ALTER TABLE `plus_report_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `plus_report_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pop_outlog`
--

DROP TABLE IF EXISTS `pop_outlog`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pop_outlog` (
  `outlog_index` int(11) NOT NULL auto_increment,
  `mod_accessed` varchar(8) NOT NULL,
  `time_sent` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `send_status` varchar(8) NOT NULL,
  `error_message` varchar(512) NOT NULL,
  `email_subject` varchar(256) NOT NULL,
  `email_from` varchar(128) NOT NULL,
  `email_recipients` varchar(256) NOT NULL,
  PRIMARY KEY  (`outlog_index`)
) ENGINE=InnoDB AUTO_INCREMENT=153 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `pop_outlog`
--

LOCK TABLES `pop_outlog` WRITE;
/*!40000 ALTER TABLE `pop_outlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `pop_outlog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rap_log`
--

DROP TABLE IF EXISTS `rap_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `rap_log` (
  `rap_id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `report_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (`rap_id`),
  KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `rap_log_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `rap_log_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=102 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `rap_log`
--

LOCK TABLES `rap_log` WRITE;
/*!40000 ALTER TABLE `rap_log` DISABLE KEYS */;
/*!40000 ALTER TABLE `rap_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rez_pages`
--

DROP TABLE IF EXISTS `rez_pages`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `rez_pages` (
  `rez_page_id` int(11) NOT NULL auto_increment,
  `rez_menu_title` varchar(64) NOT NULL,
  `rez_page_title` varchar(64) NOT NULL,
  `rez_menu_order` int(11) NOT NULL,
  `rez_content` mediumtext NOT NULL,
  `rez_description` varchar(128) NOT NULL,
  `rez_timestamp` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `rez_visibility` varchar(16) NOT NULL,
  PRIMARY KEY  (`rez_page_id`)
) ENGINE=InnoDB AUTO_INCREMENT=30 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `rez_pages`
--

LOCK TABLES `rez_pages` WRITE;
/*!40000 ALTER TABLE `rez_pages` DISABLE KEYS */;
INSERT INTO `rez_pages` (`rez_page_id`, `rez_menu_title`, `rez_page_title`, `rez_menu_order`, `rez_content`, `rez_description`, `rez_timestamp`, `rez_visibility`) VALUES (-45,'PLUS Web Service API','PLUS Web Service API',35,'<a href=\"https://pl.nlm.nih.gov/index.php?mod=rez&amp;act=default&amp;page_id=plus\" title=\"\" target=\"\">PL User Service API</a>','PLUS Web Service API','2011-03-10 23:29:45','Hidden'),(-30,'ABOUT','ABOUT',31,'<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\"><span class=\"Apple-style-span\" style=\"font-family: \'Times New Roman\'; font-size: medium; \"><pre style=\"word-wrap: break-word; white-space: pre-wrap; \">Some of the Sahana Agasti modules are being actively developed, maintained, or customized by the U.S. National Library of Medicine (NLM), located on the National Institutes of Health (NIH) campus in Bethesda, Maryland. NLM is in a community partnership with 3 nearby hospitals (National Naval Medical Center, NIH Clinical Center, Suburban Hospital) to improve emergency responses to a mass disaster impacting those hospitals. The partnership, called the Bethesda Hospitals\' Emergency Preparedness Partnership (BHEPP), received initial federal funding for LPF and other NLM IT projects in 2008-9. The LPF project is currently supported by the Intramural Research Program of the NIH, through NLMâ€™s Lister Hill National Center for Biomedical Communications (LHNCBC). Software development is headed by LHNCBC\'s Communication Engineering Branch (CEB), with additional content from LHNCBC\'s Computer Science Branch (CSB) and the Disaster Information Management Research Center (DIMRC), part of NLM\'s Specialized Information Services.</pre></span>','ABOUT','2011-03-17 23:13:25','Hidden'),(-20,'Error #20 :: Access Denied','Error #20 :: Access Denied',-20,'You do not have permission to access this event. If you believe this is in error, please contact lpfsupport@mail.nih.gov','Error #20 :: Access Denied','2011-02-04 00:01:42','Hidden'),(-6,'Password Change Successful','Password Change Successful',11,'<div><br></div><div>Your password has been changed and the new password emailed to you. Please use it for future logins.</div>','Password Change Successful','2010-09-29 15:55:51','Hidden'),(-5,'Password Change Unsuccessful','Password Change Unsuccessful',7,'<div><br></div><div>Your attempted password change was unsuccessful. It appears you used an invalid confirmation code.</div>','Password Change Unsuccessful','2010-09-29 15:56:09','Hidden'),(-4,'Account Already Active','Account Already Active',6,'<div><br></div><div>This confirmation link is no longer valid. The account attached to it is already active.</div>','Account Already Active','2010-09-29 15:56:06','Hidden'),(-3,'Registration Unsuccessful','Registration Unsuccessful',5,'<div><br></div><div>Your attempted registration confirmation was unsuccessful. It appears you attempted to confirm an invalid user. Please re-initiate the registration process from your device to try again.</div>','Registration Unsuccessful','2010-09-29 15:56:05','Hidden'),(-2,'Registration Unsuccessful','Registration Unsuccessful',2,'<div><br></div><div>Your attempted registration confirmation was unsuccessful. It appears you attempted to confirm a user with an invalid confirmation code. Please re-initiate the registration process from your device to try again.</div>','Registration Unsuccessful','2010-09-29 15:56:04','Hidden'),(-1,'Registration Successful','Registration Successful',1,'<div><br></div><div>Thank you for confirming your registration.&nbsp;</div><div><br></div><div>The device you registered can now utilize the Person Locator web services. (ie. Searching for and Reporting Persons on ReUnite)</div><div><br></div><div><meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\"><div>Additionally, your user account is now active and you may log into this site with the login/password that was supplied in the email you received. After logging in, you may change your password by going to User Preferences and navigating to \"Change Password\".</div></div><div><br></div>','Registration Successful','2010-07-15 19:00:07','Hidden'),(11,'How do I search for a person?','How do I search for a person?',14,'<h2>Searching</h2>\n1) Enter a name in the search box<br>\n2) Click on the \"Search\" button, or hit Enter <br>\n<br>\n<i>Examples:</i><br>\n<br>\n Joseph Doe<br>\n Doe, Jane<br>\n Joseph Joe Joey<br>\n<br>\nIt is best to leave off titles (â€œDr.â€, â€œMrs.â€) and suffixes (â€œJrâ€) at this time.<br>\n<br>\n<br>\n<h2>Search Options</h2>\nYou may also specify status, gender, and age to limit your search results.  The default is to search all options.  To access search options, click on the \"+ More Options\" link.<br>\n<br>\nStatus choices are missing (blue), alive and well (green), injured (red), deceased (black), or unknown (gray)<br>\n<br>\nGender choices are male, female, and other/unknown.<br>\n<br>\nAge choices are 0-17, 18+, or unknown.<br>\n<br>\n<br>\n<h2>Results</h2>\nResults include any of the search terms.<br>\n<br>\nUnder the search box is the number of records found that match your search, and the total number in the database (eg, Found 2 out of 43).<br>\n<br>\nYou may sort your results by Time, Name, Age, or Status.<br>\n<br>\nInteractive mode displays photos by page.  The default is 25 per page.  You may change it to 50 or 100 per page via the pull down menu at the top of the results.<br>\n<br>\nHands Free mode displays photos as three as three scrolling rows of photographs.  The photos always distribute themselves evenly among the rows, starting at the right side and from top row to bottom.  If there are more images than can be shown at once, the rows will become animated to scroll horizontally with wrap-around.  There is no meaning to the ordering of the images at this time.<br>\n<br>\n<br>\n<h2>Getting Details about a Given Photo</h2>\nClick on the photo for more information.<br>\n<br>\n<br>\n<h2>Pause and Play Buttons</h2>\nIf horizontal scrolling is occurring, Pause will stop that, and Play will resume it.  Even while paused, the search will be repeated every minute to look for fresh content.<br>\n<br>\n<br>\n<h2>Other Information</h2>\nWhat Information is being Searched, and How Often Is It Updated?<br>\n<br>\nOnce a set of result images for a search is loaded, the search will be quietly repeated every minute to see if there is new content to include.<br>\n<br>\nInformation is being input via TriagePic and records set to us directly by email (e.g., with our iPhone app).<br>\n<br>\n<br>\n<h2>Data Updates</h2>\nOnce a set of result images for a search is loaded, the search will be quietly repeated every minute to see if there is new content.\nInformation is being input via TriagePic and records sent to us directly by email (e.g., with our iPhone app).\n<br>\n<br><br>','Instructions for searching on the site','2010-12-04 01:44:15','Public'),(29,'General Resources','General Resources',38,'<br>','Resources for a disaster','2011-05-11 22:48:31','Hidden');
/*!40000 ALTER TABLE `rez_pages` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sessions`
--

DROP TABLE IF EXISTS `sessions`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `sessions` (
  `session_id` varchar(64) NOT NULL,
  `sess_key` varchar(64) NOT NULL,
  `secret` varchar(64) NOT NULL,
  `inactive_expiry` bigint(20) NOT NULL,
  `expiry` bigint(20) NOT NULL,
  `data` text,
  PRIMARY KEY  (`session_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `sessions`
--

LOCK TABLES `sessions` WRITE;
/*!40000 ALTER TABLE `sessions` DISABLE KEYS */;
/*!40000 ALTER TABLE `sessions` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sys_group_to_module`
--

DROP TABLE IF EXISTS `sys_group_to_module`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `sys_group_to_module` (
  `group_id` int(11) NOT NULL,
  `module` varchar(60) NOT NULL,
  `status` varchar(60) NOT NULL,
  PRIMARY KEY  (`group_id`,`module`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `sys_group_to_module`
--

LOCK TABLES `sys_group_to_module` WRITE;
/*!40000 ALTER TABLE `sys_group_to_module` DISABLE KEYS */;
INSERT INTO `sys_group_to_module` (`group_id`, `module`, `status`) VALUES (1,'admin','enabled'),(1,'eap','enabled'),(1,'em','enabled'),(1,'ha','enabled'),(1,'home','enabled'),(1,'int','enabled'),(1,'inw','enabled'),(1,'plus','enabled'),(1,'pop','enabled'),(1,'pref','enabled'),(1,'rap','enabled'),(1,'rez','enabled'),(1,'tp','enabled'),(1,'xst','enabled'),(2,'eap','enabled'),(2,'home','enabled'),(2,'inw','enabled'),(2,'pref','enabled'),(2,'rap','enabled'),(2,'rez','enabled'),(2,'xst','enabled'),(3,'eap','enabled'),(3,'home','enabled'),(3,'inw','enabled'),(3,'rap','enabled'),(3,'rez','enabled'),(3,'xst','enabled'),(5,'eap','enabled'),(5,'home','enabled'),(5,'inw','enabled'),(5,'pref','enabled'),(5,'rap','enabled'),(5,'rez','enabled'),(5,'tp','enabled'),(5,'xst','enabled'),(6,'eap','enabled'),(6,'em','enabled'),(6,'ha','enabled'),(6,'home','enabled'),(6,'inw','enabled'),(6,'pref','enabled'),(6,'rap','enabled'),(6,'rez','enabled'),(6,'tp','enabled'),(6,'xst','enabled'),(7,'eap','enabled'),(7,'home','enabled'),(7,'inw','enabled'),(7,'pref','enabled'),(7,'rap','enabled'),(7,'rez','enabled'),(7,'xst','enabled');
/*!40000 ALTER TABLE `sys_group_to_module` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sys_user_groups`
--

DROP TABLE IF EXISTS `sys_user_groups`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `sys_user_groups` (
  `group_id` int(11) NOT NULL,
  `group_name` varchar(40) NOT NULL,
  PRIMARY KEY  (`group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `sys_user_groups`
--

LOCK TABLES `sys_user_groups` WRITE;
/*!40000 ALTER TABLE `sys_user_groups` DISABLE KEYS */;
INSERT INTO `sys_user_groups` (`group_id`, `group_name`) VALUES (1,'Administrator'),(2,'Registered User'),(3,'Anonymous User'),(5,'Hospital Staff'),(6,'Hospital Staff Admin'),(7,'Researchers');
/*!40000 ALTER TABLE `sys_user_groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sys_user_to_group`
--

DROP TABLE IF EXISTS `sys_user_to_group`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `sys_user_to_group` (
  `group_id` int(11) NOT NULL,
  `p_uuid` varchar(128) NOT NULL,
  KEY `p_uuid` (`p_uuid`),
  KEY `group_id` (`group_id`),
  CONSTRAINT `sys_user_to_group_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `sys_user_to_group_ibfk_2` FOREIGN KEY (`group_id`) REFERENCES `sys_user_groups` (`group_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `sys_user_to_group_ibfk_3` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `sys_user_to_group_ibfk_4` FOREIGN KEY (`group_id`) REFERENCES `sys_user_groups` (`group_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `sys_user_to_group`
--

LOCK TABLES `sys_user_to_group` WRITE;
/*!40000 ALTER TABLE `sys_user_to_group` DISABLE KEYS */;
INSERT INTO `sys_user_to_group` (`group_id`, `p_uuid`) VALUES (3,'3'),(1,'1');
/*!40000 ALTER TABLE `sys_user_to_group` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user_preference`
--

DROP TABLE IF EXISTS `user_preference`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `user_preference` (
  `pref_id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `module_id` varchar(20) NOT NULL,
  `pref_key` varchar(60) NOT NULL,
  `value` varchar(100) default NULL,
  PRIMARY KEY  (`pref_id`),
  KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `user_preference_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `user_preference_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `user_preference`
--

LOCK TABLES `user_preference` WRITE;
/*!40000 ALTER TABLE `user_preference` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_preference` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `users` (
  `user_id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(128) NOT NULL,
  `user_name` varchar(100) NOT NULL,
  `password` varchar(128) default NULL,
  `salt` varchar(100) default NULL,
  `changed_timestamp` bigint(20) NOT NULL default '0',
  `status` varchar(60) default 'active',
  `confirmation` varchar(255) default NULL,
  PRIMARY KEY  (`user_id`),
  UNIQUE KEY `user_name` (`user_name`),
  KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `users_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `users_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=122 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` (`user_id`, `p_uuid`, `user_name`, `password`, `salt`, `changed_timestamp`, `status`, `confirmation`) VALUES (1,'1','root','c78cd6254de60e91a402f733d12a0c3f','e5cb9f3624f2d81964',1297450104,'active',NULL),(3,'3','anonymous',NULL,NULL,0,'active',NULL);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `voice_note`
--

DROP TABLE IF EXISTS `voice_note`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `voice_note` (
  `voicenote_id` bigint(20) NOT NULL auto_increment,
  `p_uuid` varchar(128) default NULL,
  `original_filename` varchar(255) default NULL,
  `data` mediumblob,
  `length` double default NULL,
  `format` varchar(16) default NULL,
  `sample_rate` int(8) default NULL,
  `channels` int(8) default NULL,
  `speaker` varchar(16) default NULL,
  `url` varchar(255) default NULL,
  PRIMARY KEY  (`voicenote_id`),
  KEY `p_uuid` (`p_uuid`),
  CONSTRAINT `voice_note_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `voice_note_ibfk_2` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Dumping data for table `voice_note`
--

LOCK TABLES `voice_note` WRITE;
/*!40000 ALTER TABLE `voice_note` DISABLE KEYS */;
/*!40000 ALTER TABLE `voice_note` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'vesuvius091'
--
DELIMITER ;;
/*!50003 DROP PROCEDURE IF EXISTS `delete_person` */;;
/*!50003 SET SESSION SQL_MODE=""*/;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `delete_person`(IN id VARCHAR(128))
BEGIN


DELETE c.* FROM contact c, person_to_report pr WHERE pr.rep_uuid = c.pgoc_uuid AND pr.p_uuid = id;


DELETE ld.* FROM location_details ld, person_to_report pr WHERE pr.rep_uuid = ld.poc_uuid AND pr.p_uuid = id;


DELETE p.* FROM person_uuid p, person_to_report pr WHERE pr.rep_uuid = p.p_uuid AND pr.p_uuid = id AND pr.rep_uuid NOT IN (SELECT p_uuid FROM users);


DELETE person_uuid.* FROM person_uuid WHERE p_uuid = id;


DELETE pfif_person.* FROM pfif_person WHERE p_uuid = id;


DELETE pfif_note.* FROM pfif_note WHERE p_uuid = id;


UPDATE pfif_note SET linked_person_record_id = NULL WHERE p_uuid = id;


DELETE contact.* FROM contact WHERE pgoc_uuid = id;


DELETE image.* from image where x_uuid = id;

END */;;
/*!50003 SET SESSION SQL_MODE=@OLD_SQL_MODE*/;;
/*!50003 DROP PROCEDURE IF EXISTS `PLSearch` */;;
/*!50003 SET SESSION SQL_MODE=""*/;;
/*!50003 CREATE*/ /*!50020 DEFINER=`mrodriguez`@`localhost`*/ /*!50003 PROCEDURE `PLSearch`(
     IN searchTerms CHAR(255),
	 IN statusFilter VARCHAR(100),
	 IN genderFilter VARCHAR(100),
	 IN ageFilter VARCHAR(100),
	 IN hospitalFilter VARCHAR(100),
	 IN incidentName VARCHAR(100),
	 IN sortBy VARCHAR(100),
	 IN pageStart INT,
	 IN perPage INT,
    OUT totalRows INT

)
BEGIN

	DROP TABLE IF EXISTS tmp_names; 
    IF searchTerms = '' THEN 
            CREATE TEMPORARY TABLE tmp_names AS (
            SELECT SQL_NO_CACHE pu.*
                FROM person_uuid pu
                   JOIN incident i  ON (pu.incident_id = i.incident_id AND i.shortname = incidentName)
                  LIMIT 2000
         );
    
    ELSE
            CREATE TEMPORARY TABLE  tmp_names AS (
            SELECT SQL_NO_CACHE pu.*
                FROM person_uuid pu
                   JOIN incident i  ON (pu.incident_id = i.incident_id AND i.shortname = incidentName)
            WHERE full_name like CONCAT(searchTerms , '%') 
            LIMIT 2000
            );
     END IF;
    
    SET @sqlString = CONCAT("SELECT  SQL_NO_CACHE `tn`.`p_uuid`       AS `p_uuid`,
				`tn`.`full_name`    AS `full_name`,
				`tn`.`given_name`   AS `given_name`,
				`tn`.`family_name`  AS `family_name`,
				(CASE WHEN `ps`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'fnd') OR `ps`.`opt_status` IS NULL THEN 'unk' ELSE `ps`.`opt_status` END) AS `opt_status`,
				  DATE_FORMAT(ps.last_updated, '%Y-%m-%d %k:%i:%s') as updated,
                  
				(CASE WHEN `pd`.`opt_gender` NOT IN ('mal', 'fml') OR `pd`.`opt_gender` IS NULL THEN 'unk' ELSE `pd`.`opt_gender` END) AS `opt_gender`,
				(CASE WHEN `pd`.`years_old` < 18 THEN 'child' WHEN `pd`.`years_old` >= 18 THEN 'adult' ELSE 'unknown' END) as `age_group`,
                                `pd`.`years_old` as `years_old`,
				`i`.`image_height` AS `image_height`,
				`i`.`image_width`  AS `image_width`,
				`i`.`url_thumb`    AS `url_thumb`,
				(CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END)  AS `hospital`,
				(CASE WHEN (`h`.`hospital_uuid` = -(1)) THEN NULL ELSE `h`.`icon_url` END) AS `icon_url`,
				`pd`.last_seen,
				`pd`.other_comments as comments
			 FROM tmp_names tn
             JOIN person_status ps  ON (tn.p_uuid = ps.p_uuid AND ps.isVictim = 1 AND INSTR(?, 	(CASE WHEN ps.opt_status NOT IN ('ali', 'mis', 'inj', 'dec', 'fnd') OR ps.opt_status IS NULL THEN 'unk' ELSE  ps.opt_status END)))
             JOIN person_details pd ON (tn.p_uuid = pd.p_uuid AND INSTR(?, (CASE WHEN `opt_gender` NOT IN ('mal', 'fml') OR `opt_gender` IS NULL THEN 'unk' ELSE `opt_gender` END))
															  AND INSTR(?, (CASE WHEN CAST(`years_old` AS UNSIGNED) < 18 THEN 'child' WHEN CAST(`years_old` AS UNSIGNED) >= 18 THEN 'adult' ELSE 'unknown' END)))
			 LEFT 
			 JOIN hospital h        ON (tn.hospital_uuid = h.hospital_uuid AND INSTR(?, (CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END)))
             LEFT 
			 JOIN image i			ON (tn.p_uuid = i.x_uuid)
           ORDER BY ", sortBy, " LIMIT ?, ?;");

      PREPARE stmt FROM @sqlString;

      SET @statusFilter = statusFilter;
      SET @genderFilter = genderFilter;
      SET @ageFilter = ageFilter;
      SET @hospitalFilter = hospitalFilter;

      SET @pageStart = pageStart;
      SET @perPage = perPage;

      SET NAMES utf8;
      EXECUTE stmt USING @statusFilter, @genderFilter, @ageFilter, @hospitalFilter, 
                                                        @pageStart, @perPage;

      DEALLOCATE PREPARE stmt;

      
			 
	DROP TABLE tmp_names;
    
    
      SELECT COUNT(p.p_uuid) INTO totalRows
          FROM person_uuid p
             JOIN incident i ON p.incident_id = i.incident_id
      WHERE i.shortname = incidentName;
   
   
END */;;
/*!50003 SET SESSION SQL_MODE=@OLD_SQL_MODE*/;;
/*!50003 DROP PROCEDURE IF EXISTS `PLSearch2` */;;
/*!50003 SET SESSION SQL_MODE=""*/;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `PLSearch2`(IN searchTerms CHAR(255),
	 IN statusFilter VARCHAR(100),
	 IN genderFilter VARCHAR(100),
	 IN ageFilter VARCHAR(100),
	 IN hospitalFilter VARCHAR(100),
	 IN incident VARCHAR(100),
	 IN sortBy VARCHAR(100),
	 IN pageStart INT,
	 IN perPage INT,
   OUT totalRows INT)
BEGIN


  

  SET @sqlString = "
		SELECT STRAIGHT_JOIN SQL_NO_CACHE
				`a`.`p_uuid`       AS `p_uuid`,
				`a`.`full_name`    AS `full_name`,
				`a`.`given_name`   AS `given_name`,
				`a`.`family_name`  AS `family_name`,
				(CASE WHEN `b`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk') OR `b`.`opt_status` IS NULL THEN 'unk' ELSE `b`.`opt_status` END) AS `opt_status`,
        DATE_FORMAT(b.updated, '%m/%e/%y @ %l:%i:%s %p') as updated,
				(CASE WHEN `c`.`opt_gender` NOT IN ('mal', 'fml') OR `c`.`opt_gender` IS NULL THEN 'unk' ELSE `c`.`opt_gender` END) AS `opt_gender`,
				(CASE WHEN CAST(`c`.`years_old` AS UNSIGNED) < 18 THEN 'child' WHEN CAST(`c`.`years_old` AS UNSIGNED) >= 18 THEN 'adult' ELSE 'unknown' END) as `age_group`,
				`i`.`image_height` AS `image_height`,
				`i`.`image_width`  AS `image_width`,
				`i`.`url_thumb`    AS `url_thumb`,
				(CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END)  AS `hospital`,
				(CASE WHEN (`h`.`hospital_uuid` = -(1)) THEN NULL ELSE `h`.`icon_url` END) AS `icon_url`,
				`inc`.`shortname`  AS `shortname`,
        `pm`.last_seen, `pm`.comments

		   FROM `person_uuid` `a`
		   JOIN `person_status` `b`     ON (`a`.`p_uuid` = `b`.`p_uuid` AND `b`.`isVictim` = 1 )
	  LEFT JOIN `image` `i`           ON `a`.`p_uuid` = `i`.`x_uuid`
		   JOIN `person_details` `c`    ON `a`.`p_uuid` = `c`.`p_uuid`
		   JOIN `incident` `inc`        ON (`inc`.`incident_id` = `a`.`incident_id` AND `a`.`incident_id` <> 0 )
	  LEFT JOIN `hospital` `h`        ON `h`.`hospital_uuid` = `a`.`hospital_uuid`
    LEFT JOIN `person_missing` `pm` ON pm.p_uuid = a.p_uuid
	  WHERE INSTR(?, 	(CASE WHEN `b`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk') OR `b`.`opt_status` IS NULL THEN 'unk' ELSE `b`.`opt_status` END))
	    AND INSTR(?, (CASE WHEN `c`.`opt_gender` NOT IN ('mal', 'fml') OR `c`.`opt_gender` IS NULL THEN 'unk' ELSE `c`.`opt_gender` END))
		  AND INSTR(?, (CASE WHEN CAST(`c`.`years_old` AS UNSIGNED) < 18 THEN 'child' WHEN CAST(`c`.`years_old` AS UNSIGNED) >= 18 THEN 'adult' ELSE 'unknown' END))
		  AND INSTR(?, (CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END))
	    AND `shortname` = ?
      AND (full_name like CONCAT('%', ?, '%'))
    ORDER BY ?
    LIMIT ?, ?";

  PREPARE stmt FROM @sqlString;

  SET @searchTerms = searchTerms;
  SET @statusFilter = statusFilter;
  SET @genderFilter = genderFilter;
  SET @ageFilter = ageFilter;
  SET @hospitalFilter = hospitalFilter;
  SET @incident = incident;
  SET @sortBy = sortBy;
  SET @pageStart = pageStart;
  SET @perPage = perPage;

  EXECUTE stmt USING @statusFilter, @genderFilter, @ageFilter, @hospitalFilter, @incident,
                     @searchTerms,@sortBy, @pageStart, @perPage;

  DEALLOCATE PREPARE stmt;

  SELECT COUNT(p.p_uuid) INTO totalRows
    FROM person_uuid p
    JOIN incident i
      ON p.incident_id = i.incident_id
   WHERE i.shortname = incident;


END */;;
/*!50003 SET SESSION SQL_MODE=@OLD_SQL_MODE*/;;
/*!50003 DROP PROCEDURE IF EXISTS `PLSearch_Count` */;;
/*!50003 SET SESSION SQL_MODE=""*/;;
/*!50003 CREATE*/ /*!50020 DEFINER=`root`@`localhost`*/ /*!50003 PROCEDURE `PLSearch_Count`(IN searchTerms CHAR(255),
	 IN statusFilter VARCHAR(100),
	 IN genderFilter VARCHAR(100),
	 IN ageFilter VARCHAR(100),
	 IN hospitalFilter VARCHAR(100),
	 IN incident VARCHAR(100))
BEGIN




		SELECT STRAIGHT_JOIN COUNT(a.p_uuid)
		   FROM `person_uuid` `a`
		   JOIN `person_status` `b`          ON (`a`.`p_uuid` = `b`.`p_uuid` AND `b`.`isVictim` = 1 )
		   JOIN `person_details` `c`         ON `a`.`p_uuid` = `c`.`p_uuid`
		   JOIN `incident` `inc`             ON (`inc`.`incident_id` = `a`.`incident_id` AND `a`.`incident_id` <> 0 )
	  LEFT JOIN `hospital` `h`               ON `h`.`hospital_uuid` = `a`.`hospital_uuid`
	  WHERE INSTR(statusFilter, 	(CASE WHEN `b`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk') OR `b`.`opt_status` IS NULL THEN 'unk' ELSE `b`.`opt_status` END))
	    AND INSTR(genderFilter, (CASE WHEN `c`.`opt_gender` NOT IN ('mal', 'fml') OR `c`.`opt_gender` IS NULL THEN 'unk' ELSE `c`.`opt_gender` END))
		  AND INSTR(ageFilter, (CASE WHEN CAST(`c`.`years_old` AS UNSIGNED) < 18 THEN 'child' WHEN CAST(`c`.`years_old` AS UNSIGNED) >= 18 THEN 'adult' ELSE 'unknown' END))
		  AND INSTR(hospitalFilter, (CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END))
	    AND `shortname` = incident
      AND (full_name like CONCAT('%', searchTerms, '%') OR given_name SOUNDS LIKE searchTerms OR family_name SOUNDS LIKE searchTerms);



END */;;
/*!50003 SET SESSION SQL_MODE=@OLD_SQL_MODE*/;;
DELIMITER ;

--
-- Final view structure for view `person_search`
--

/*!50001 DROP TABLE `person_search`*/;
/*!50001 DROP VIEW IF EXISTS `person_search`*/;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `person_search` AS select `a`.`p_uuid` AS `p_uuid`,`a`.`full_name` AS `full_name`,`a`.`given_name` AS `given_name`,`a`.`family_name` AS `family_name`,(case when ((`b`.`opt_status` not in (_utf8'ali',_utf8'mis',_utf8'inj',_utf8'dec',_utf8'unk',_utf8'fnd')) or isnull(`b`.`opt_status`)) then _utf8'unk' else `b`.`opt_status` end) AS `opt_status`,`b`.`last_updated` AS `updated`,(case when ((`c`.`opt_gender` not in (_utf8'mal',_utf8'fml')) or isnull(`c`.`opt_gender`)) then _utf8'unk' else `c`.`opt_gender` end) AS `opt_gender`,(case when isnull(cast(`c`.`years_old` as unsigned)) then -(1) else `c`.`years_old` end) AS `years_old`,`i`.`image_height` AS `image_height`,`i`.`image_width` AS `image_width`,`i`.`url_thumb` AS `url_thumb`,(case when (`h`.`hospital_uuid` = -(1)) then NULL else `h`.`icon_url` end) AS `icon_url`,`inc`.`shortname` AS `shortname`,(case when ((`h`.`short_name` not in (_utf8'sh',_utf8'nnmc')) or isnull(`h`.`short_name`)) then _utf8'public' else `h`.`short_name` end) AS `hospital`,`c`.`other_comments` AS `comments`,`c`.`last_seen` AS `last_seen` from ((((((`person_uuid` `a` join `person_status` `b` on(((`a`.`p_uuid` = `b`.`p_uuid`) and (`b`.`isvictim` = 1)))) left join `image` `i` on((`a`.`p_uuid` = `i`.`x_uuid`))) join `person_details` `c` on((`a`.`p_uuid` = `c`.`p_uuid`))) join `incident` `inc` on((`inc`.`incident_id` = `a`.`incident_id`))) left join `hospital` `h` on((`h`.`hospital_uuid` = `a`.`hospital_uuid`))) left join `person_updates` `f` on((`a`.`p_uuid` = `f`.`p_uuid`))) */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2011-05-20 18:40:01
