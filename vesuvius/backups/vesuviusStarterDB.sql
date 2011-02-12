-- phpMyAdmin SQL Dump
-- version 3.3.4
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Feb 11, 2011 at 05:25 PM
-- Server version: 5.0.77
-- PHP Version: 5.3.5

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `vesuvius`
--

-- --------------------------------------------------------

--
-- Table structure for table `adodb_logsql`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `adodb_logsql` (
  `created` datetime NOT NULL,
  `sql0` varchar(250) NOT NULL,
  `sql1` text NOT NULL,
  `params` text NOT NULL,
  `tracer` text NOT NULL,
  `timer` decimal(16,6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `adodb_logsql`
--


-- --------------------------------------------------------

--
-- Table structure for table `alt_logins`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `alt_logins` (
  `p_uuid` varchar(60) NOT NULL,
  `user_name` varchar(100) NOT NULL,
  `type` varchar(60) default 'openid',
  PRIMARY KEY  (`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `alt_logins`
--


-- --------------------------------------------------------

--
-- Table structure for table `audit`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `audit` (
  `audit_id` bigint(20) NOT NULL auto_increment,
  `updated` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `x_uuid` varchar(60) NOT NULL,
  `u_uuid` varchar(60) NOT NULL,
  `change_type` varchar(3) NOT NULL,
  `change_table` varchar(100) NOT NULL,
  `change_field` varchar(100) NOT NULL,
  `prev_val` text,
  `new_val` text,
  PRIMARY KEY  (`audit_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2356735 ;

--
-- Dumping data for table `audit`
--


-- --------------------------------------------------------

--
-- Table structure for table `config`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `config` (
  `config_id` bigint(20) NOT NULL auto_increment,
  `module_id` varchar(20) default NULL,
  `confkey` varchar(50) NOT NULL,
  `value` varchar(100) default NULL,
  PRIMARY KEY  (`config_id`),
  KEY `module_id` (`module_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=2252 ;

--
-- Dumping data for table `config`
--

INSERT INTO `config` (`config_id`, `module_id`, `confkey`, `value`) VALUES
(6, 'admin', 'acl_locking', '1'),
(7, 'admin', 'acl_signup_enabled', '1'),
(2251, 'plus', 'timeout', '864000');

-- --------------------------------------------------------

--
-- Table structure for table `contact`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `contact` (
  `pgoc_uuid` varchar(60) NOT NULL,
  `opt_contact_type` varchar(10) NOT NULL,
  `contact_value` varchar(100) default NULL,
  PRIMARY KEY  (`pgoc_uuid`,`opt_contact_type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `contact`
--

INSERT INTO `contact` (`pgoc_uuid`, `opt_contact_type`, `contact_value`) VALUES
('1', 'email', 'root@localhost');

-- --------------------------------------------------------

--
-- Table structure for table `field_options`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `field_options` (
  `field_name` varchar(100) default NULL,
  `option_code` varchar(20) default NULL,
  `option_description` varchar(50) default NULL,
  `display_order` int(8) default NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `field_options`
--

INSERT INTO `field_options` (`field_name`, `option_code`, `option_description`, `display_order`) VALUES
('opt_id_type', 'nic', 'National Identity Card', NULL),
('opt_id_type', 'pas', 'Passport', NULL),
('opt_id_type', 'dln', 'Driving License Number', NULL),
('opt_id_type', 'oth', 'Other', NULL),
('opt_status', 'ali', 'Alive & Well', NULL),
('opt_status', 'mis', 'Missing', NULL),
('opt_status', 'inj', 'Injured', NULL),
('opt_status', 'dec', 'Deceased', NULL),
('opt_gender', 'mal', 'Male', NULL),
('opt_gender', 'fml', 'Female', NULL),
('opt_relationship_type', 'fat', 'Father', NULL),
('opt_relationship_type', 'mot', 'Mother', NULL),
('opt_relationship_type', 'bro', 'Brown', NULL),
('opt_relationship_type', 'sis', 'Sister', NULL),
('opt_relationship_type', 'gft', 'GrandFather', NULL),
('opt_relationship_type', 'gmt', 'GrandMother', NULL),
('opt_relationship_type', 'gfpat', 'GrandFatherPaternal', NULL),
('opt_relationship_type', 'gfmat', 'GrandFatherMaternal', NULL),
('opt_relationship_type', 'gmpat', 'GrandMotherPaternal', NULL),
('opt_relationship_type', 'gmmat', 'GrandMotherMaternal', NULL),
('opt_relationship_type', 'fnd', 'Friend', NULL),
('opt_relationship_type', 'oth', 'Other', NULL),
('opt_contact_type', 'home', 'Home(permanent address)', NULL),
('opt_contact_type', 'name', 'Contact Person', NULL),
('opt_contact_type', 'pmob', 'Personal Mobile', NULL),
('opt_contact_type', 'curr', 'Current Phone', NULL),
('opt_contact_type', 'cmob', 'Current Mobile', NULL),
('opt_contact_type', 'email', 'Email address', NULL),
('opt_contact_type', 'fax', 'Fax Number', NULL),
('opt_contact_type', 'web', 'Website', NULL),
('opt_contact_type', 'inst', 'Instant Messenger', NULL),
('opt_eye_color', 'GRN', 'Green', NULL),
('opt_eye_color', 'GRY', 'Gray', NULL),
('opt_race', 'R1', 'American Indian or Alaska Native', NULL),
('opt_race', 'U', 'Unknown', NULL),
('opt_marital_status', 'unk', 'Unknown', NULL),
('opt_marital_status', 'sin', 'Single', NULL),
('opt_marital_status', 'mar', 'Married', NULL),
('opt_marital_status', 'div', 'Divorced', NULL),
('opt_blood_type', 'a+', 'A+', NULL),
('opt_blood_type', 'a-', 'A-', NULL),
('opt_blood_type', 'b+', 'B+', NULL),
('opt_blood_type', 'b-', 'B-', NULL),
('opt_blood_type', 'ab+', 'AB+', NULL),
('opt_blood_type', 'ab-', 'AB-', NULL),
('opt_blood_type', 'o+', 'O+', NULL),
('opt_blood_type', 'o-', 'O-', NULL),
('opt_eye_color', 'BRO', 'Brown', NULL),
('opt_eye_color', 'BLU', 'Blue', NULL),
('opt_eye_color', 'BLK', 'Black', NULL),
('opt_skin_color', 'DRK', 'Dark', NULL),
('opt_country', 'AFG', 'Afghanistan', NULL),
('opt_skin_color', 'BLK', 'Black', NULL),
('opt_skin_color', 'ALB', 'Albino', NULL),
('opt_hair_color', 'BLN', 'Blond or Strawberry', NULL),
('opt_country', 'ALA', 'Åland Islands', NULL),
('opt_hair_color', 'BLK', 'Black', NULL),
('opt_hair_color', 'BLD', 'Bald', NULL),
('opt_location_type', '2', 'Town or Neighborhood', NULL),
('opt_location_type', '1', 'County or Equivalent', NULL),
('opt_contact_type', 'zip', 'Zip Code', NULL),
('opt_eye_color', 'UNK', 'Unknown', NULL),
('opt_country', 'ALB', 'Albania', NULL),
('opt_country', 'DZA', 'Algeria', NULL),
('opt_country', 'ASM', 'American Samoa', NULL),
('opt_country', 'AND', 'Andorra', NULL),
('opt_country', 'AGO', 'Angola', NULL),
('opt_country', 'AIA', 'Anguilla', NULL),
('opt_country', 'ATA', 'Antarctica', NULL),
('opt_country', 'ATG', 'Antigua and Barbuda', NULL),
('opt_country', 'ARG', 'Argentina', NULL),
('opt_country', 'ARM', 'Armenia', NULL),
('opt_country', 'ABW', 'Aruba', NULL),
('opt_country', 'AUS', 'Australia', NULL),
('opt_country', 'AUT', 'Austria', NULL),
('opt_country', 'AZE', 'Azerbaijan', NULL),
('opt_country', 'BHS', 'Bahamas', NULL),
('opt_country', 'BHR', 'Bahrain', NULL),
('opt_country', 'BGD', 'Bangladesh', NULL),
('opt_country', 'BRB', 'Barbados', NULL),
('opt_country', 'BLR', 'Belarus', NULL),
('opt_country', 'BEL', 'Belgium', NULL),
('opt_country', 'BLZ', 'Belize', NULL),
('opt_country', 'BEN', 'Benin', NULL),
('opt_country', 'BMU', 'Bermuda', NULL),
('opt_country', 'BTN', 'Bhutan', NULL),
('opt_country', 'BOL', 'Bolivia', NULL),
('opt_country', 'BIH', 'Bosnia and Herzegovina', NULL),
('opt_country', 'BWA', 'Botswana', NULL),
('opt_country', 'BVT', 'Bouvet Island', NULL),
('opt_country', 'BRA', 'Brazil', NULL),
('opt_country', 'IOT', 'British Indian Ocean Territory', NULL),
('opt_country', 'BRN', 'Brunei Darussalam', NULL),
('opt_country', 'BGR', 'Bulgaria', NULL),
('opt_country', 'BFA', 'Burkina Faso', NULL),
('opt_country', 'BDI', 'Burundi', NULL),
('opt_country', 'KHM', 'Cambodia', NULL),
('opt_country', 'CMR', 'Cameroon', NULL),
('opt_country', 'CAN', 'Canada', NULL),
('opt_country', 'CPV', 'Cape Verde', NULL),
('opt_country', 'CYM', 'Cayman Islands', NULL),
('opt_country', 'CAF', 'Central African Republic', NULL),
('opt_country', 'TCD', 'Chad', NULL),
('opt_country', 'CHL', 'Chile', NULL),
('opt_country', 'CHN', 'China', NULL),
('opt_country', 'CXR', 'Christmas Island', NULL),
('opt_country', 'CCK', 'Cocos (Keeling) Islands', NULL),
('opt_country', 'COL', 'Colombia', NULL),
('opt_country', 'COM', 'Comoros', NULL),
('opt_country', 'COG', 'Congo', NULL),
('opt_country', 'AFG', 'Afghanistan', NULL),
('opt_country', 'ALA', 'Åland Islands', NULL),
('opt_country', 'ALB', 'Albania', NULL),
('opt_country', 'DZA', 'Algeria', NULL),
('opt_country', 'ASM', 'American Samoa', NULL),
('opt_country', 'AND', 'Andorra', NULL),
('opt_country', 'AGO', 'Angola', NULL),
('opt_country', 'AIA', 'Anguilla', NULL),
('opt_country', 'ATA', 'Antarctica', NULL),
('opt_country', 'ATG', 'Antigua and Barbuda', NULL),
('opt_country', 'ARG', 'Argentina', NULL),
('opt_country', 'ARM', 'Armenia', NULL),
('opt_country', 'ABW', 'Aruba', NULL),
('opt_country', 'AUS', 'Australia', NULL),
('opt_country', 'AUT', 'Austria', NULL),
('opt_country', 'AZE', 'Azerbaijan', NULL),
('opt_country', 'BHS', 'Bahamas', NULL),
('opt_country', 'BHR', 'Bahrain', NULL),
('opt_country', 'BGD', 'Bangladesh', NULL),
('opt_country', 'BRB', 'Barbados', NULL),
('opt_country', 'BLR', 'Belarus', NULL),
('opt_country', 'BEL', 'Belgium', NULL),
('opt_country', 'BLZ', 'Belize', NULL),
('opt_country', 'BEN', 'Benin', NULL),
('opt_country', 'BMU', 'Bermuda', NULL),
('opt_country', 'BTN', 'Bhutan', NULL),
('opt_country', 'BOL', 'Bolivia', NULL),
('opt_country', 'BIH', 'Bosnia and Herzegovina', NULL),
('opt_country', 'BWA', 'Botswana', NULL),
('opt_country', 'BVT', 'Bouvet Island', NULL),
('opt_country', 'BRA', 'Brazil', NULL),
('opt_country', 'IOT', 'British Indian Ocean Territory', NULL),
('opt_country', 'BRN', 'Brunei Darussalam', NULL),
('opt_country', 'BGR', 'Bulgaria', NULL),
('opt_country', 'BFA', 'Burkina Faso', NULL),
('opt_country', 'BDI', 'Burundi', NULL),
('opt_country', 'KHM', 'Cambodia', NULL),
('opt_country', 'CMR', 'Cameroon', NULL),
('opt_country', 'CAN', 'Canada', NULL),
('opt_country', 'CPV', 'Cape Verde', NULL),
('opt_country', 'CYM', 'Cayman Islands', NULL),
('opt_country', 'CAF', 'Central African Republic', NULL),
('opt_country', 'TCD', 'Chad', NULL),
('opt_country', 'CHL', 'Chile', NULL),
('opt_country', 'CHN', 'China', NULL),
('opt_country', 'CXR', 'Christmas Island', NULL),
('opt_country', 'CCK', 'Cocos (Keeling) Islands', NULL),
('opt_country', 'COL', 'Colombia', NULL),
('opt_country', 'COM', 'Comoros', NULL),
('opt_country', 'COG', 'Congo', NULL),
('opt_country', 'COD', 'Congo, the Democratic Republic of the', NULL),
('opt_country', 'COK', 'Cook Islands', NULL),
('opt_country', 'CRI', 'Costa Rica', NULL),
('opt_country', 'CIV', 'Côte d''Ivoire', NULL),
('opt_country', 'HRV', 'Croatia', NULL),
('opt_country', 'CUB', 'Cuba', NULL),
('opt_country', 'CYP', 'Cyprus', NULL),
('opt_country', 'CZE', 'Czech Republic', NULL),
('opt_country', 'DNK', 'Denmark', NULL),
('opt_country', 'DJI', 'Djibouti', NULL),
('opt_country', 'DMA', 'Dominica', NULL),
('opt_country', 'DOM', 'Dominican Republic', NULL),
('opt_country', 'ECU', 'Ecuador', NULL),
('opt_country', 'EGY', 'Egypt', NULL),
('opt_country', 'SLV', 'El Salvador', NULL),
('opt_country', 'GNQ', 'Equatorial Guinea', NULL),
('opt_country', 'ERI', 'Eritrea', NULL),
('opt_country', 'EST', 'Estonia', NULL),
('opt_country', 'ETH', 'Ethiopia', NULL),
('opt_country', 'FLK', 'Falkland Islands (Malvinas)', NULL),
('opt_country', 'FRO', 'Faroe Islands', NULL),
('opt_country', 'FJI', 'Fiji', NULL),
('opt_country', 'FIN', 'Finland', NULL),
('opt_country', 'FRA', 'France', NULL),
('opt_country', 'GUF', 'French Guiana', NULL),
('opt_country', 'PYF', 'French Polynesia', NULL),
('opt_country', 'ATF', 'French Southern Territories', NULL),
('opt_country', 'GAB', 'Gabon', NULL),
('opt_country', 'GMB', 'Gambia', NULL),
('opt_country', 'GEO', 'Georgia', NULL),
('opt_country', 'DEU', 'Germany', NULL),
('opt_country', 'GHA', 'Ghana', NULL),
('opt_country', 'GIB', 'Gibraltar', NULL),
('opt_country', 'GRC', 'Greece', NULL),
('opt_country', 'GRL', 'Greenland', NULL),
('opt_country', 'GRD', 'Grenada', NULL),
('opt_country', 'GLP', 'Guadeloupe', NULL),
('opt_country', 'GUM', 'Guam', NULL),
('opt_country', 'GTM', 'Guatemala', NULL),
('opt_country', 'GGY', 'Guernsey', NULL),
('opt_country', 'GIN', 'Guinea', NULL),
('opt_country', 'GNB', 'Guinea-Bissau', NULL),
('opt_country', 'GUY', 'Guyana', NULL),
('opt_country', 'HTI', 'Haiti', NULL),
('opt_country', 'HMD', 'Heard Island and McDonald Islands', NULL),
('opt_country', 'VAT', 'Holy See (Vatican City State)', NULL),
('opt_country', 'HND', 'Honduras', NULL),
('opt_country', 'HKG', 'Hong Kong', NULL),
('opt_country', 'HUN', 'Hungary', NULL),
('opt_country', 'ISL', 'Iceland', NULL),
('opt_country', 'IND', 'India', NULL),
('opt_country', 'IDN', 'Indonesia', NULL),
('opt_country', 'IRN', 'Iran, Islamic Republic of', NULL),
('opt_country', 'IRQ', 'Iraq', NULL),
('opt_country', 'IRL', 'Ireland', NULL),
('opt_country', 'IMN', 'Isle of Man', NULL),
('opt_country', 'ISR', 'Israel', NULL),
('opt_country', 'ITA', 'Italy', NULL),
('opt_country', 'JAM', 'Jamaica', NULL),
('opt_country', 'JPN', 'Japan', NULL),
('opt_country', 'JEY', 'Jersey', NULL),
('opt_country', 'JOR', 'Jordan', NULL),
('opt_country', 'KAZ', 'Kazakhstan', NULL),
('opt_country', 'KEN', 'Kenya', NULL),
('opt_country', 'KIR', 'Kiribati', NULL),
('opt_country', 'PRK', 'Korea, Democratic People''s Republic of', NULL),
('opt_country', 'KOR', 'Korea, Republic of', NULL),
('opt_country', 'KWT', 'Kuwait', NULL),
('opt_country', 'KGZ', 'Kyrgyzstan', NULL),
('opt_country', 'LAO', 'Lao People''s Democratic Republic', NULL),
('opt_country', 'LVA', 'Latvia', NULL),
('opt_country', 'LBN', 'Lebanon', NULL),
('opt_country', 'LSO', 'Lesotho', NULL),
('opt_country', 'LBR', 'Liberia', NULL),
('opt_country', 'LBY', 'Libyan Arab Jamahiriya', NULL),
('opt_country', 'LIE', 'Liechtenstein', NULL),
('opt_country', 'LTU', 'Lithuania', NULL),
('opt_country', 'LUX', 'Luxembourg', NULL),
('opt_country', 'MAC', 'Macao', NULL),
('opt_country', 'MKD', 'Macedonia, the former Yugoslav Republic of', NULL),
('opt_country', 'MDG', 'Madagascar', NULL),
('opt_country', 'MWI', 'Malawi', NULL),
('opt_country', 'MYS', 'Malaysia', NULL),
('opt_country', 'MDV', 'Maldives', NULL),
('opt_country', 'MLI', 'Mali', NULL),
('opt_country', 'MLT', 'Malta', NULL),
('opt_country', 'MHL', 'Marshall Islands', NULL),
('opt_country', 'MTQ', 'Martinique', NULL),
('opt_country', 'MRT', 'Mauritania', NULL),
('opt_country', 'MUS', 'Mauritius', NULL),
('opt_country', 'MYT', 'Mayotte', NULL),
('opt_country', 'MEX', 'Mexico', NULL),
('opt_country', 'FSM', 'Micronesia, Federated States of', NULL),
('opt_country', 'MDA', 'Moldova, Republic of', NULL),
('opt_country', 'MCO', 'Monaco', NULL),
('opt_country', 'MNG', 'Mongolia', NULL),
('opt_country', 'MNE', 'Montenegro', NULL),
('opt_country', 'MSR', 'Montserrat', NULL),
('opt_country', 'MAR', 'Maroon', NULL),
('opt_country', 'MOZ', 'Mozambique', NULL),
('opt_country', 'MMR', 'Myanmar', NULL),
('opt_country', 'NAM', 'Namibia', NULL),
('opt_country', 'NRU', 'Nauru', NULL),
('opt_country', 'NPL', 'Nepal', NULL),
('opt_country', 'NLD', 'Netherlands', NULL),
('opt_country', 'ANT', 'Netherlands Antilles', NULL),
('opt_country', 'NCL', 'New Caledonia', NULL),
('opt_country', 'NZL', 'New Zealand', NULL),
('opt_country', 'NIC', 'Nicaragua', NULL),
('opt_country', 'NER', 'Niger', NULL),
('opt_country', 'NGA', 'Nigeria', NULL),
('opt_country', 'NIU', 'Niue', NULL),
('opt_country', 'NFK', 'Norfolk Island', NULL),
('opt_country', 'MNP', 'Northern Mariana Islands', NULL),
('opt_country', 'NOR', 'Norway', NULL),
('opt_country', 'OMN', 'Oman', NULL),
('opt_country', 'PAK', 'Pakistan', NULL),
('opt_country', 'PLW', 'Palau', NULL),
('opt_country', 'PSE', 'Palestinian Territory, Occupied', NULL),
('opt_country', 'PAN', 'Panama', NULL),
('opt_country', 'PNG', 'Papua New Guinea', NULL),
('opt_country', 'PRY', 'Paraguay', NULL),
('opt_country', 'PER', 'Peru', NULL),
('opt_country', 'PHL', 'Philippines', NULL),
('opt_country', 'PCN', 'Pitcairn', NULL),
('opt_country', 'POL', 'Poland', NULL),
('opt_country', 'PRT', 'Portugal', NULL),
('opt_country', 'PRI', 'Puerto Rico', NULL),
('opt_country', 'QAT', 'Qatar', NULL),
('opt_country', 'REU', 'Réunion', NULL),
('opt_country', 'ROU', 'Romania', NULL),
('opt_country', 'RUS', 'Russian Federation', NULL),
('opt_country', 'RWA', 'Rwanda', NULL),
('opt_country', 'BLM', 'Saint Barthélemy', NULL),
('opt_country', 'SHN', 'Saint Helena', NULL),
('opt_country', 'KNA', 'Saint Kitts and Nevis', NULL),
('opt_country', 'LCA', 'Saint Lucia', NULL),
('opt_country', 'MAF', 'Saint Martin (French part)', NULL),
('opt_country', 'SPM', 'Saint Pierre and Miquelon', NULL),
('opt_country', 'VCT', 'Saint Vincent and the Grenadines', NULL),
('opt_country', 'WSM', 'Samoa', NULL),
('opt_country', 'SMR', 'San Marino', NULL),
('opt_country', 'STP', 'Sao Tome and Principe', NULL),
('opt_country', 'SAU', 'Saudi Arabia', NULL),
('opt_country', 'SEN', 'Senegal', NULL),
('opt_country', 'SRB', 'Serbia', NULL),
('opt_country', 'SYC', 'Seychelles', NULL),
('opt_country', 'SLE', 'Sierra Leone', NULL),
('opt_country', 'SGP', 'Singapore', NULL),
('opt_country', 'SVK', 'Slovakia', NULL),
('opt_country', 'SVN', 'Slovenia', NULL),
('opt_country', 'SLB', 'Solomon Islands', NULL),
('opt_country', 'SOM', 'Somalia', NULL),
('opt_country', 'ZAF', 'South Africa', NULL),
('opt_country', 'SGS', 'South Georgia and the South Sandwich Islands', NULL),
('opt_country', 'ESP', 'Spain', NULL),
('opt_country', 'LKA', 'Sri Lanka', NULL),
('opt_country', 'SDN', 'Sudan', NULL),
('opt_country', 'SUR', 'Suriname', NULL),
('opt_country', 'SJM', 'Svalbard and Jan Mayen', NULL),
('opt_country', 'SWZ', 'Swaziland', NULL),
('opt_country', 'SWE', 'Sweden', NULL),
('opt_country', 'CHE', 'Switzerland', NULL),
('opt_country', 'SYR', 'Syrian Arab Republic', NULL),
('opt_country', 'TWN', 'Taiwan, Province of China', NULL),
('opt_country', 'TJK', 'Tajikistan', NULL),
('opt_country', 'TZA', 'Tanzania, United Republic of', NULL),
('opt_country', 'THA', 'Thailand', NULL),
('opt_country', 'TLS', 'Timor-Leste', NULL),
('opt_country', 'TGO', 'Togo', NULL),
('opt_country', 'TKL', 'Tokelau', NULL),
('opt_country', 'TON', 'Tonga', NULL),
('opt_country', 'TTO', 'Trinidad and Tobago', NULL),
('opt_country', 'TUN', 'Tunisia', NULL),
('opt_country', 'TUR', 'Turkey', NULL),
('opt_country', 'TKM', 'Turkmenistan', NULL),
('opt_country', 'TCA', 'Turks and Caicos Islands', NULL),
('opt_country', 'TUV', 'Tuvalu', NULL),
('opt_country', 'UGA', 'Uganda', NULL),
('opt_country', 'UKR', 'Ukraine', NULL),
('opt_country', 'ARE', 'United Arab Emirates', NULL),
('opt_country', 'GBR', 'United Kingdom', NULL),
('opt_country', 'USA', 'United States', NULL),
('opt_country', 'UMI', 'United States Minor Outlying Islands', NULL),
('opt_country', 'URY', 'Uruguay', NULL),
('opt_country', 'UZB', 'Uzbekistan', NULL),
('opt_country', 'VUT', 'Vanuatu', NULL),
('opt_country', 'VEN', 'Venezuela, Bolivarian Republic of', NULL),
('opt_country', 'VNM', 'Viet Nam', NULL),
('opt_country', 'VGB', 'Virgin Islands, British', NULL),
('opt_country', 'VIR', 'Virgin Islands, U.S.', NULL),
('opt_country', 'WLF', 'Wallis and Futuna', NULL),
('opt_country', 'ESH', 'Western Sahara', NULL),
('opt_country', 'YEM', 'Yemen', NULL),
('opt_country', 'ZMB', 'Zambia', NULL),
('opt_country', 'ZWE', 'Zimbabwe', NULL),
('opt_eye_color', 'HAZ', 'Hazel', NULL),
('opt_eye_color', 'MAR', 'Maroon', NULL),
('opt_eye_color', 'MUL', 'Multicolored', NULL),
('opt_eye_color', 'PNK', 'Pink', NULL),
('opt_skin_color', 'DBR', 'Dark Brown', NULL),
('opt_skin_color', 'FAR', 'Fair', NULL),
('opt_skin_color', 'LGT', 'Light', NULL),
('opt_skin_color', 'LBR', 'Light Brown', NULL),
('opt_skin_color', 'MED', 'Medium', NULL),
('opt_skin_color', 'UNK', 'Unknown', NULL),
('opt_skin_color', 'OLV', 'Olive', NULL),
('opt_skin_color', 'RUD', 'Ruddy', NULL),
('opt_skin_color', 'SAL', 'Sallow', NULL),
('opt_skin_color', 'YEL', 'Yellow', NULL),
('opt_hair_color', 'BLU', 'Blue', NULL),
('opt_hair_color', 'BRO', 'Brown', NULL),
('opt_hair_color', 'GRY', 'Gray', NULL),
('opt_hair_color', 'GRN', 'Green', NULL),
('opt_hair_color', 'ONG', 'Orange', NULL),
('opt_hair_color', 'PLE', 'Purple', NULL),
('opt_hair_color', 'PNK', 'Pink', NULL),
('opt_hair_color', 'RED', 'Red or Auburn', NULL),
('opt_hair_color', 'SDY', 'Sandy', NULL),
('opt_hair_color', 'WHI', 'White', NULL),
('opt_race', 'R2', 'Asian', NULL),
('opt_race', 'R3', 'Black or African American', NULL),
('opt_race', 'R4', 'Native Hawaiian or Other Pacific Islander', NULL),
('opt_race', 'R5', 'White', NULL),
('opt_race', 'R9', 'Other Race', NULL),
('opt_religion', 'PEV', 'Protestant, Evangelical', 1),
('opt_religion', 'PML', 'Protestant, Mainline', 2),
('opt_religion', 'PHB', 'Protestant, Historically Black', 3),
('opt_religion', 'CAT', 'Catholic', 4),
('opt_religion', 'MOM', 'Mormon', 5),
('opt_religion', 'JWN', 'Jehovah''s Witness', 6),
('opt_religion', 'ORT', 'Orthodox', 7),
('opt_religion', 'COT', 'Other Christian', 8),
('opt_religion', 'JEW', 'Jewish', 9),
('opt_religion', 'BUD', 'Buddhist', 10),
('opt_religion', 'HIN', 'Hindu', 11),
('opt_religion', 'MOS', 'Muslim', 12),
('opt_religion', 'OTH', 'Other Faiths', 13),
('opt_religion', 'NOE', 'Unaffiliated', 14),
('opt_religion', 'VAR', 'Unknown', 15),
('opt_hair_color', 'UNK', 'Unknown', NULL),
('opt_skin_color', 'MBR', 'Medium Brown', NULL),
('opt_gender', 'unk', 'Unknown', NULL),
('opt_gender', 'cpx', 'Complex', NULL),
('opt_blood_type', 'c++5', 'C++', 0);

-- --------------------------------------------------------

--
-- Table structure for table `hospital`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

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
  `npi` varchar(32) default NULL,
  `patient_id_prefix` varchar(32) NOT NULL,
  `creation_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `icon_url` varchar(128) default NULL,
  PRIMARY KEY  (`hospital_uuid`),
  KEY `hospital_uuid` (`hospital_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=3 ;

--
-- Dumping data for table `hospital`
--

INSERT INTO `hospital` (`hospital_uuid`, `name`, `short_name`, `street1`, `street2`, `city`, `county`, `region`, `postal_code`, `country`, `latitude`, `longitude`, `phone`, `fax`, `email`, `npi`, `patient_id_prefix`, `creation_time`, `icon_url`) VALUES
(-1, ' NOT AT HOSPITAL', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 0, 0, ' ', ' ', ' ', ' ', ' ', '2010-10-04 19:36:01', ' '),
(1, 'Suburban Hospital', 'sh', '8600 Old Georgetown Rd', '', 'Bethesda', 'Montgomery', 'MD', '20817', 'USA', 38.99731, -77.10984, '3018963100', '', '', '', '911-', '2010-01-01 01:01:01', 'theme/lpf3/img/suburban.png'),
(2, 'National Naval Medical Center', 'nnmc', 'National Naval Medical Center', '', 'Bethesda', 'Montgomery', 'MD', '20889', 'US', 39.00204, -77.0945, '3012954611', '', '', '', '', '2010-09-22 18:49:34', 'theme/lpf3/img/nnmc.png');

-- --------------------------------------------------------

--
-- Table structure for table `image`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `image` (
  `image_id` bigint(20) NOT NULL auto_increment,
  `x_uuid` varchar(60) NOT NULL,
  `image` mediumblob,
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
  KEY `image_id` (`image_id`,`x_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=10186 ;

--
-- Dumping data for table `image`
--


-- --------------------------------------------------------

--
-- Table structure for table `image_tag`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

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
  KEY `image_id` (`image_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- RELATIONS FOR TABLE `image_tag`:
--   `image_id`
--       `image` -> `image_id`
--

--
-- Dumping data for table `image_tag`
--


-- --------------------------------------------------------

--
-- Table structure for table `incident`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

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
  `closed` tinyint(1) default NULL,
  `description` varchar(1024) default NULL,
  PRIMARY KEY  (`incident_id`),
  KEY `parent_id` (`parent_id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1028 ;

--
-- Dumping data for table `incident`
--

INSERT INTO `incident` (`incident_id`, `parent_id`, `search_id`, `name`, `shortname`, `date`, `type`, `latitude`, `longitude`, `default`, `private_group`, `closed`, `description`) VALUES
(1, NULL, NULL, 'Test Event', 'test', '2000-01-01', 'TEST', 0, 0, 1, NULL, NULL, '');

-- --------------------------------------------------------

--
-- Table structure for table `lc_fields`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `lc_fields` (
  `id` bigint(20) NOT NULL auto_increment,
  `tablename` varchar(32) NOT NULL,
  `fieldname` varchar(32) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `lc_fields`
--

INSERT INTO `lc_fields` (`id`, `tablename`, `fieldname`) VALUES
(1, 'field_options', 'option_description'),
(2, 'ct_unit', 'name'),
(3, 'ct_unit_type', 'name'),
(4, 'ct_unit_type', 'description');

-- --------------------------------------------------------

--
-- Table structure for table `location`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `location` (
  `loc_uuid` varchar(60) NOT NULL,
  `parent_id` varchar(60) default NULL,
  `opt_location_type` varchar(10) default NULL,
  `name` varchar(100) NOT NULL,
  `iso_code` varchar(20) default NULL,
  `description` text,
  PRIMARY KEY  (`loc_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `location`
--

INSERT INTO `location` (`loc_uuid`, `parent_id`, `opt_location_type`, `name`, `iso_code`, `description`) VALUES
('8y2flc-10', NULL, '1', 'Baltimore (city), MD [TO DO]', '1702381', NULL),
('8y2flc-11', NULL, '1', 'Anne Arundel County, MD [TO DO]', '1710958', NULL),
('8y2flc-12', NULL, '1', 'Alexandria (city), VA [TO DO]', '1498415', NULL),
('8y2flc-13', NULL, '1', 'Arlington County, VA [TO DO]', '1480119', NULL),
('8y2flc-14', NULL, '1', 'Falls Church (city), VA [TO DO]', '1498422', NULL),
('8y2flc-15', NULL, '1', 'Fairfax County, VA [TO DO]', '1480119', NULL),
('8y2flc-16', NULL, '1', 'Fairfax (city), VA [TO DO]', '1789070', NULL),
('8y2flc-17', NULL, '1', 'Loudoun County, VA [TO DO]', '1480141', NULL),
('8y2flc-18', NULL, '1', 'Manassas (city), VA [TO DO]', '1498430', NULL),
('8y2flc-19', NULL, '1', 'Manassas Park (city), VA [TO DO]', '1498431', NULL),
('8y2flc-2', NULL, '1', 'Montgomery County, MD', '1712500', 'n/a'),
('8y2flc-21048', '8y2flc-2', '2', 'Abrams', '2458850', NULL),
('8y2flc-21049', '8y2flc-2', '2', 'Allanwood', '589631', NULL),
('8y2flc-21050', '8y2flc-2', '2', 'Alta Vista', '589637', NULL),
('8y2flc-21051', '8y2flc-2', '2', 'Alta Vista Terrace', '589638', NULL),
('8y2flc-21052', '8y2flc-2', '2', 'Ancient Oak', '1712938', NULL),
('8y2flc-21053', '8y2flc-2', '2', 'Ancient Oak North', '1712939', NULL),
('8y2flc-21054', '8y2flc-2', '2', 'Ancient Oak West', '1712940', NULL),
('8y2flc-21055', '8y2flc-2', '2', 'Anscroft', '1712766', NULL),
('8y2flc-21056', '8y2flc-2', '2', 'Arcola', '589650', NULL),
('8y2flc-21057', '8y2flc-2', '2', 'Ashburton', '589659', NULL),
('8y2flc-21058', '8y2flc-2', '2', 'Ashleigh', '589661', NULL),
('8y2flc-21059', '8y2flc-2', '2', 'Ashley Manor', '1712767', NULL),
('8y2flc-21060', '8y2flc-2', '2', 'Ashmead', '1712768', NULL),
('8y2flc-21061', '8y2flc-2', '2', 'Ashton', '582943', NULL),
('8y2flc-21062', '8y2flc-2', '2', 'Ashton Manor', '1712769', NULL),
('8y2flc-21063', '8y2flc-2', '2', 'Ashton Pond', '1712770', NULL),
('8y2flc-21064', '8y2flc-2', '2', 'Ashton Preserve', '2458866', NULL),
('8y2flc-21065', '8y2flc-2', '2', 'Ashton River Estates', '1712771', NULL),
('8y2flc-21066', '8y2flc-2', '2', 'Aspen Hill', '589663', NULL),
('8y2flc-21067', '8y2flc-2', '2', 'Aspen Hill Park', '589664', NULL),
('8y2flc-21068', '8y2flc-2', '2', 'Aspen Knolls', '589665', NULL),
('8y2flc-21069', '8y2flc-2', '2', 'Avenel', '1729631', NULL),
('8y2flc-21070', '8y2flc-2', '2', 'Avery', '589672', NULL),
('8y2flc-21071', '8y2flc-2', '2', 'Banner Country', '1712676', NULL),
('8y2flc-21072', '8y2flc-2', '2', 'Bannockburn', '589689', NULL),
('8y2flc-21073', '8y2flc-2', '2', 'Bannockburn Estates', '589690', NULL),
('8y2flc-21074', '8y2flc-2', '2', 'Bannockburn Heights', '589691', NULL),
('8y2flc-21075', '8y2flc-2', '2', 'Barnesville', '589696', NULL),
('8y2flc-21076', '8y2flc-2', '2', 'Barton Woods', '1712677', NULL),
('8y2flc-21077', '8y2flc-2', '2', 'Battery Park', '589702', NULL),
('8y2flc-21078', '8y2flc-2', '2', 'Beallmount', '1712868', NULL),
('8y2flc-21079', '8y2flc-2', '2', 'Beallsville', '591624', NULL),
('8y2flc-21080', '8y2flc-2', '2', 'Beantown', '589713', NULL),
('8y2flc-21081', '8y2flc-2', '2', 'Beau Monde Estates', '1712578', NULL),
('8y2flc-21082', '8y2flc-2', '2', 'Bel Pre Farms', '589724', NULL),
('8y2flc-21083', '8y2flc-2', '2', 'Bells Mill', '589728', NULL),
('8y2flc-21084', '8y2flc-2', '2', 'Belvedere', '1712944', NULL),
('8y2flc-21085', '8y2flc-2', '2', 'Bennington', '1712679', NULL),
('8y2flc-21086', '8y2flc-2', '2', 'Bethesda', '583184', NULL),
('8y2flc-21087', '8y2flc-2', '2', 'Beverly Farms', '589751', NULL),
('8y2flc-21088', '8y2flc-2', '2', 'Big Pines', '589752', NULL),
('8y2flc-21089', '8y2flc-2', '2', 'Big Woods Acres', '1712523', NULL),
('8y2flc-21090', '8y2flc-2', '2', 'Black Hill', '1712579', NULL),
('8y2flc-21091', '8y2flc-2', '2', 'Blackburn Village', '2458892', NULL),
('8y2flc-21092', '8y2flc-2', '2', 'Blackrock Estates', '1712580', NULL),
('8y2flc-21093', '8y2flc-2', '2', 'Blackrock Hills', '1712581', NULL),
('8y2flc-21094', '8y2flc-2', '2', 'Blackrock Mill', '589765', NULL),
('8y2flc-21095', '8y2flc-2', '2', 'Blair Portal', '589768', NULL),
('8y2flc-21096', '8y2flc-2', '2', 'Blocktown', '583289', NULL),
('8y2flc-21097', '8y2flc-2', '2', 'Blount Commons', '2458894', NULL),
('8y2flc-21098', '8y2flc-2', '2', 'Bondbrook', '1712948', NULL),
('8y2flc-21099', '8y2flc-2', '2', 'Bonifant Village', '2458896', NULL),
('8y2flc-21100', '8y2flc-2', '2', 'Bootjack', '588621', NULL),
('8y2flc-21101', '8y2flc-2', '2', 'Bowie Mill Estates', '1712680', NULL),
('8y2flc-21102', '8y2flc-2', '2', 'Bowie Mill Park', '1712682', NULL),
('8y2flc-21103', '8y2flc-2', '2', 'Boyds', '583349', NULL),
('8y2flc-21104', '8y2flc-2', '2', 'Bradley Farms', '589795', NULL),
('8y2flc-21105', '8y2flc-2', '2', 'Bradley Hills', '589796', NULL),
('8y2flc-21106', '8y2flc-2', '2', 'Bradley Hills Grove', '589797', NULL),
('8y2flc-21107', '8y2flc-2', '2', 'Bradley Woods', '589798', NULL),
('8y2flc-21108', '8y2flc-2', '2', 'Bradmoor', '589799', NULL),
('8y2flc-21109', '8y2flc-2', '2', 'Brandermill', '1712683', NULL),
('8y2flc-21110', '8y2flc-2', '2', 'Briars Acres', '1712684', NULL),
('8y2flc-21111', '8y2flc-2', '2', 'Bridlewood', '1712582', NULL),
('8y2flc-21112', '8y2flc-2', '2', 'Briggs-Chaney Estates', '2458906', NULL),
('8y2flc-21113', '8y2flc-2', '2', 'Brighton', '589816', NULL),
('8y2flc-21114', '8y2flc-2', '2', 'Brighton Estates', '1712685', NULL),
('8y2flc-21115', '8y2flc-2', '2', 'Brighton Knolls', '1712686', NULL),
('8y2flc-21116', '8y2flc-2', '2', 'Brink', '588623', NULL),
('8y2flc-21117', '8y2flc-2', '2', 'Brink Meadow', '1712687', NULL),
('8y2flc-21118', '8y2flc-2', '2', 'Brinklow', '588624', NULL),
('8y2flc-21119', '8y2flc-2', '2', 'Brinkwood Estates', '1712688', NULL),
('8y2flc-21120', '8y2flc-2', '2', 'Broadwood Manor', '589822', NULL),
('8y2flc-21121', '8y2flc-2', '2', 'Brook Hollow', '1712690', NULL),
('8y2flc-21122', '8y2flc-2', '2', 'Brookdale', '589823', NULL),
('8y2flc-21123', '8y2flc-2', '2', 'Brooke Grove', '1712693', NULL),
('8y2flc-21124', '8y2flc-2', '2', 'Brooke Meadow', '2458907', NULL),
('8y2flc-21125', '8y2flc-2', '2', 'Brookemanor Estates', '1712695', NULL),
('8y2flc-21126', '8y2flc-2', '2', 'Brookeville', '589824', NULL),
('8y2flc-21127', '8y2flc-2', '2', 'Brookeville Heights', '1712697', NULL),
('8y2flc-21128', '8y2flc-2', '2', 'Brookeville Knolls', '1712698', NULL),
('8y2flc-21129', '8y2flc-2', '2', 'Brookmead', '1712872', NULL),
('8y2flc-21130', '8y2flc-2', '2', 'Brookmead North', '1712873', NULL),
('8y2flc-21131', '8y2flc-2', '2', 'Brookmont', '589828', NULL),
('8y2flc-21132', '8y2flc-2', '2', 'Brookside Forest', '589829', NULL),
('8y2flc-21133', '8y2flc-2', '2', 'Brown', '589832', NULL),
('8y2flc-21134', '8y2flc-2', '2', 'Browningsville', '589835', NULL),
('8y2flc-21135', '8y2flc-2', '2', 'Browns Corner', '588625', NULL),
('8y2flc-21136', '8y2flc-2', '2', 'Browns Corner[80]', '1712874', NULL),
('8y2flc-21137', '8y2flc-2', '2', 'Browns Corner[93]', '1713090', NULL),
('8y2flc-21138', '8y2flc-2', '2', 'Brownstown', '583443', NULL),
('8y2flc-21139', '8y2flc-2', '2', 'Brownstown Estates', '1712585', NULL),
('8y2flc-21140', '8y2flc-2', '2', 'Bucklodge', '588626', NULL),
('8y2flc-21141', '8y2flc-2', '2', 'Burdette', '589852', NULL),
('8y2flc-21142', '8y2flc-2', '2', 'Burnham Hills', '1712699', NULL),
('8y2flc-21143', '8y2flc-2', '2', 'Burnham Woods', '1712700', NULL),
('8y2flc-21144', '8y2flc-2', '2', 'Burning Tree Estates', '589856', NULL),
('8y2flc-21145', '8y2flc-2', '2', 'Burnt Mills', '589858', NULL),
('8y2flc-21146', '8y2flc-2', '2', 'Burnt Mills Hills', '589859', NULL),
('8y2flc-21147', '8y2flc-2', '2', 'Burnt Mills Knolls', '589860', NULL),
('8y2flc-21148', '8y2flc-2', '2', 'Burnt Mills Manor', '589861', NULL),
('8y2flc-21149', '8y2flc-2', '2', 'Burnt Mills Village', '583493', NULL),
('8y2flc-21150', '8y2flc-2', '2', 'Burtonsville', '583500', NULL),
('8y2flc-21151', '8y2flc-2', '2', 'Byeforde', '589870', NULL),
('8y2flc-21152', '8y2flc-2', '2', 'Cabin John', '589873', NULL),
('8y2flc-21153', '8y2flc-2', '2', 'Cabin John Park', '589874', NULL),
('8y2flc-21154', '8y2flc-2', '2', 'Camelback Village', '1712702', NULL),
('8y2flc-21155', '8y2flc-2', '2', 'Campbell Corner', '589880', NULL),
('8y2flc-21156', '8y2flc-2', '2', 'Candlewood Park', '2458919', NULL),
('8y2flc-21157', '8y2flc-2', '2', 'Capitol View Park', '589890', NULL),
('8y2flc-21158', '8y2flc-2', '2', 'Carderock', '589893', NULL),
('8y2flc-21159', '8y2flc-2', '2', 'Carderock Springs', '589894', NULL),
('8y2flc-21160', '8y2flc-2', '2', 'Carole Acres', '589901', NULL),
('8y2flc-21161', '8y2flc-2', '2', 'Carroll Knolls', '589902', NULL),
('8y2flc-21162', '8y2flc-2', '2', 'Carroll Manor', '589903', NULL),
('8y2flc-21163', '8y2flc-2', '2', 'Cashell Estates', '2458927', NULL),
('8y2flc-21164', '8y2flc-2', '2', 'Cashell Manor', '1712705', NULL),
('8y2flc-21165', '8y2flc-2', '2', 'Cashell Woods', '1712707', NULL),
('8y2flc-21166', '8y2flc-2', '2', 'Castlegate', '2458928', NULL),
('8y2flc-21167', '8y2flc-2', '2', 'Cedar Creek Estates', '1712587', NULL),
('8y2flc-21168', '8y2flc-2', '2', 'Cedar Grove', '589922', NULL),
('8y2flc-21169', '8y2flc-2', '2', 'Cedar Grove Knolls', '1712525', NULL),
('8y2flc-21170', '8y2flc-2', '2', 'Cedar Heights', '589924', NULL),
('8y2flc-21171', '8y2flc-2', '2', 'Cedar Heights Estates', '1712526', NULL),
('8y2flc-21172', '8y2flc-2', '2', 'Cedar Knoll Farms', '1712709', NULL),
('8y2flc-21173', '8y2flc-2', '2', 'Chadswood', '1712711', NULL),
('8y2flc-21174', '8y2flc-2', '2', 'Charlene', '1712712', NULL),
('8y2flc-21175', '8y2flc-2', '2', 'Charred Oak Estates', '589942', NULL),
('8y2flc-21176', '8y2flc-2', '2', 'Cherry Valley', '1712713', NULL),
('8y2flc-21177', '8y2flc-2', '2', 'Cherrywood', '1712714', NULL),
('8y2flc-21178', '8y2flc-2', '2', 'Chesney', '1712528', NULL),
('8y2flc-21179', '8y2flc-2', '2', 'Chestnut Hills', '589960', NULL),
('8y2flc-21180', '8y2flc-2', '2', 'Chestnut Ridge', '589961', NULL),
('8y2flc-21181', '8y2flc-2', '2', 'Chevy Chase', '589963', NULL),
('8y2flc-21182', '8y2flc-2', '2', 'Chevy Chase Lake', '589964', NULL),
('8y2flc-21183', '8y2flc-2', '2', 'Chevy Chase Manor', '589965', NULL),
('8y2flc-21184', '8y2flc-2', '2', 'Chevy Chase Section 4', '589966', NULL),
('8y2flc-21185', '8y2flc-2', '2', 'Chevy Chase Section Five', '1669432', NULL),
('8y2flc-21186', '8y2flc-2', '2', 'Chevy Chase Section Three', '1669430', NULL),
('8y2flc-21187', '8y2flc-2', '2', 'Chevy Chase Terrace', '589967', NULL),
('8y2flc-21188', '8y2flc-2', '2', 'Chevy Chase View', '589968', NULL),
('8y2flc-21189', '8y2flc-2', '2', 'Chevy Chase Village', '1669429', NULL),
('8y2flc-21190', '8y2flc-2', '2', 'Claggettsville', '589980', NULL),
('8y2flc-21191', '8y2flc-2', '2', 'Clarksbrook Estates', '1712589', NULL),
('8y2flc-21192', '8y2flc-2', '2', 'Clarksburg', '583799', NULL),
('8y2flc-21193', '8y2flc-2', '2', 'Clarksburg Heights', '1712590', NULL),
('8y2flc-21194', '8y2flc-2', '2', 'Claysville', '588634', NULL),
('8y2flc-21195', '8y2flc-2', '2', 'Clearspring Manor', '1712530', NULL),
('8y2flc-21196', '8y2flc-2', '2', 'Clifton Park Village', '589991', NULL),
('8y2flc-21197', '8y2flc-2', '2', 'Cliftonbrook', '1712717', NULL),
('8y2flc-21198', '8y2flc-2', '2', 'Clopper', '589992', NULL),
('8y2flc-21199', '8y2flc-2', '2', 'Cloverly', '583819', NULL),
('8y2flc-21200', '8y2flc-2', '2', 'Cohasset', '589995', NULL),
('8y2flc-21201', '8y2flc-2', '2', 'Colesville', '589998', NULL),
('8y2flc-21202', '8y2flc-2', '2', 'Colesville Heights', '2458953', NULL),
('8y2flc-21203', '8y2flc-2', '2', 'Colesville Manor', '589999', NULL),
('8y2flc-21204', '8y2flc-2', '2', 'Colesville Park', '590000', NULL),
('8y2flc-21205', '8y2flc-2', '2', 'College View', '1713117', NULL),
('8y2flc-21206', '8y2flc-2', '2', 'Columbia Forest', '590004', NULL),
('8y2flc-21207', '8y2flc-2', '2', 'Comus', '588637', NULL),
('8y2flc-21208', '8y2flc-2', '2', 'Comus Sugarloaf', '1712467', NULL),
('8y2flc-21209', '8y2flc-2', '2', 'Congressional Manor', '590007', NULL),
('8y2flc-21210', '8y2flc-2', '2', 'Connecticut Avenue Estates', '590008', NULL),
('8y2flc-21211', '8y2flc-2', '2', 'Connecticut Avenue Hills', '590009', NULL),
('8y2flc-21212', '8y2flc-2', '2', 'Connecticut Avenue Park', '590010', NULL),
('8y2flc-21213', '8y2flc-2', '2', 'Connecticut Gardens', '590011', NULL),
('8y2flc-21214', '8y2flc-2', '2', 'County View', '1712531', NULL),
('8y2flc-21215', '8y2flc-2', '2', 'Coventry', '1712595', NULL),
('8y2flc-21216', '8y2flc-2', '2', 'Cresthaven', '590043', NULL),
('8y2flc-21217', '8y2flc-2', '2', 'Crestview', '590044', NULL),
('8y2flc-21218', '8y2flc-2', '2', 'Cropley', '583978', NULL),
('8y2flc-21219', '8y2flc-2', '2', 'Croydon Park', '590054', NULL),
('8y2flc-21220', '8y2flc-2', '2', 'Damascus', '584009', NULL),
('8y2flc-21221', '8y2flc-2', '2', 'Damascus Gardens', '1712470', NULL),
('8y2flc-21222', '8y2flc-2', '2', 'Damascus Hill', '1712532', NULL),
('8y2flc-21223', '8y2flc-2', '2', 'Damascus Manor', '1712533', NULL),
('8y2flc-21224', '8y2flc-2', '2', 'Damascus Terrace', '1712476', NULL),
('8y2flc-21225', '8y2flc-2', '2', 'Damascus Valley Estates', '1712478', NULL),
('8y2flc-21226', '8y2flc-2', '2', 'Damascus Valley Park', '1712534', NULL),
('8y2flc-21227', '8y2flc-2', '2', 'Damascus View', '1712479', NULL),
('8y2flc-21228', '8y2flc-2', '2', 'Darnestown', '590068', NULL),
('8y2flc-21229', '8y2flc-2', '2', 'Darnestown Hills', '1712953', NULL),
('8y2flc-21230', '8y2flc-2', '2', 'Darnestown Knolls', '1712954', NULL),
('8y2flc-21231', '8y2flc-2', '2', 'Dawsonville', '590071', NULL),
('8y2flc-21232', '8y2flc-2', '2', 'Deakins Range', '1712876', NULL),
('8y2flc-21233', '8y2flc-2', '2', 'Deer Park', '590080', NULL),
('8y2flc-21234', '8y2flc-2', '2', 'Deerfield', '590083', NULL),
('8y2flc-21235', '8y2flc-2', '2', 'Dellabrooke Estates', '1712719', NULL),
('8y2flc-21236', '8y2flc-2', '2', 'Denit Estates', '1712720', NULL),
('8y2flc-21237', '8y2flc-2', '2', 'Derwood', '590089', NULL),
('8y2flc-21238', '8y2flc-2', '2', 'Diamond Farms', '1712600', NULL),
('8y2flc-21239', '8y2flc-2', '2', 'Diamond View', '1712480', NULL),
('8y2flc-21240', '8y2flc-2', '2', 'Dickerson', '584103', NULL),
('8y2flc-21241', '8y2flc-2', '2', 'Dobridge', '1712721', NULL),
('8y2flc-21242', '8y2flc-2', '2', 'Dorsey Estates', '1712722', NULL),
('8y2flc-21243', '8y2flc-2', '2', 'Drumeldra Hills', '590112', NULL),
('8y2flc-21244', '8y2flc-2', '2', 'Drummond', '588551', NULL),
('8y2flc-21245', '8y2flc-2', '2', 'Dunlops Hills', '590119', NULL),
('8y2flc-21246', '8y2flc-2', '2', 'Duvall Manor', '1712539', NULL),
('8y2flc-21247', '8y2flc-2', '2', 'East Springbrook', '590124', NULL),
('8y2flc-21248', '8y2flc-2', '2', 'Edgemoor', '590134', NULL),
('8y2flc-21249', '8y2flc-2', '2', 'Edgewood', '590139', NULL),
('8y2flc-21250', '8y2flc-2', '2', 'Edinburgh', '2458987', NULL),
('8y2flc-21251', '8y2flc-2', '2', 'Ednor', '590142', NULL),
('8y2flc-21252', '8y2flc-2', '2', 'Ednor Acres', '1712724', NULL),
('8y2flc-21253', '8y2flc-2', '2', 'Ednor Farms', '1712726', NULL),
('8y2flc-21254', '8y2flc-2', '2', 'Ednor Highlands', '2458988', NULL),
('8y2flc-21255', '8y2flc-2', '2', 'Ednor View', '1712728', NULL),
('8y2flc-21256', '8y2flc-2', '2', 'Ednor Woods', '1712729', NULL),
('8y2flc-21257', '8y2flc-2', '2', 'Elizabeths Delight', '1712541', NULL),
('8y2flc-21258', '8y2flc-2', '2', 'Elmer', '588652', NULL),
('8y2flc-21259', '8y2flc-2', '2', 'Emery Corners', '590159', NULL),
('8y2flc-21260', '8y2flc-2', '2', 'Emory Grove', '590165', NULL),
('8y2flc-21261', '8y2flc-2', '2', 'English Manor', '590167', NULL),
('8y2flc-21262', '8y2flc-2', '2', 'English Village', '590168', NULL),
('8y2flc-21263', '8y2flc-2', '2', 'Estates at Rivers Edge', '1712880', NULL),
('8y2flc-21264', '8y2flc-2', '2', 'Esworthy Estates', '1712881', NULL),
('8y2flc-21265', '8y2flc-2', '2', 'Esworthy Park', '1712882', NULL),
('8y2flc-21266', '8y2flc-2', '2', 'Etchison', '590524', NULL),
('8y2flc-21267', '8y2flc-2', '2', 'Fairhill', '1712883', NULL),
('8y2flc-21268', '8y2flc-2', '2', 'Fairknoll', '590181', NULL),
('8y2flc-21269', '8y2flc-2', '2', 'Fairland', '590182', NULL),
('8y2flc-21270', '8y2flc-2', '2', 'Fairland Acres', '2458994', NULL),
('8y2flc-21271', '8y2flc-2', '2', 'Fairland Estates', '2458995', NULL),
('8y2flc-21272', '8y2flc-2', '2', 'Fairland Heights', '590183', NULL),
('8y2flc-21273', '8y2flc-2', '2', 'Fairview', '1713129', NULL),
('8y2flc-21274', '8y2flc-2', '2', 'Fairview Estates', '590191', NULL),
('8y2flc-21275', '8y2flc-2', '2', 'Fairway', '590192', NULL),
('8y2flc-21276', '8y2flc-2', '2', 'Fairway Hills', '590193', NULL),
('8y2flc-21277', '8y2flc-2', '2', 'Falls Orchard', '590194', NULL),
('8y2flc-21278', '8y2flc-2', '2', 'Fallsgrove', '2458998', NULL),
('8y2flc-21279', '8y2flc-2', '2', 'Farmingdale Estates', '1712602', NULL),
('8y2flc-21280', '8y2flc-2', '2', 'Farmlands', '1712884', NULL),
('8y2flc-21281', '8y2flc-2', '2', 'Fawsett Farms', '590195', NULL),
('8y2flc-21282', '8y2flc-2', '2', 'Fernshire Farms', '1712603', NULL),
('8y2flc-21283', '8y2flc-2', '2', 'Fernshire Woods', '1712604', NULL),
('8y2flc-21284', '8y2flc-2', '2', 'Fernwood', '590204', NULL),
('8y2flc-21285', '8y2flc-2', '2', 'Fetrows', '1712732', NULL),
('8y2flc-21286', '8y2flc-2', '2', 'Flintridge', '1712733', NULL),
('8y2flc-21287', '8y2flc-2', '2', 'Flower Hill', '1712605', NULL),
('8y2flc-21288', '8y2flc-2', '2', 'Forest Estates', '590214', NULL),
('8y2flc-21289', '8y2flc-2', '2', 'Forest Glen', '584443', NULL),
('8y2flc-21290', '8y2flc-2', '2', 'Forest Glen Park', '590215', NULL),
('8y2flc-21291', '8y2flc-2', '2', 'Forest Grove (historical)', '1713138', NULL),
('8y2flc-21292', '8y2flc-2', '2', 'Fountain View', '1712608', NULL),
('8y2flc-21293', '8y2flc-2', '2', 'Four Corners', '590232', NULL),
('8y2flc-21294', '8y2flc-2', '2', 'Fox Chapel', '1712734', NULL),
('8y2flc-21295', '8y2flc-2', '2', 'Fox Hills', '590238', NULL),
('8y2flc-21296', '8y2flc-2', '2', 'Fox Hills Green', '1712969', NULL),
('8y2flc-21297', '8y2flc-2', '2', 'Fox Hills North', '1712960', NULL),
('8y2flc-21298', '8y2flc-2', '2', 'Fox Ridge Estates', '1712483', NULL),
('8y2flc-21299', '8y2flc-2', '2', 'Foxhall', '590240', NULL),
('8y2flc-21300', '8y2flc-2', '2', 'Foxlair Acres', '1712738', NULL),
('8y2flc-21301', '8y2flc-2', '2', 'Franklin Knolls', '590246', NULL),
('8y2flc-21302', '8y2flc-2', '2', 'Franklin Park', '590247', NULL),
('8y2flc-21303', '8y2flc-2', '2', 'Freedom Forest', '1712739', NULL),
('8y2flc-21304', '8y2flc-2', '2', 'Frenchton Place', '2459010', NULL),
('8y2flc-21305', '8y2flc-2', '2', 'Friendship', '584509', NULL),
('8y2flc-21306', '8y2flc-2', '2', 'Friendship Heights', '590258', NULL),
('8y2flc-21307', '8y2flc-2', '2', 'Friendship Knolls', '1712484', NULL),
('8y2flc-21308', '8y2flc-2', '2', 'Friendship Village', '1852591', NULL),
('8y2flc-21309', '8y2flc-2', '2', 'Gaithersburg', '593389', NULL),
('8y2flc-21310', '8y2flc-2', '2', 'Garfield Manor', '1712740', NULL),
('8y2flc-21311', '8y2flc-2', '2', 'Garrett Park', '584560', NULL),
('8y2flc-21312', '8y2flc-2', '2', 'Garrett Park Estates', '590283', NULL),
('8y2flc-21313', '8y2flc-2', '2', 'Gayfields', '590286', NULL),
('8y2flc-21314', '8y2flc-2', '2', 'Georgetown Village', '590292', NULL),
('8y2flc-21315', '8y2flc-2', '2', 'Georgian Colonies', '2459015', NULL),
('8y2flc-21316', '8y2flc-2', '2', 'Georgian Forest', '590293', NULL),
('8y2flc-21317', '8y2flc-2', '2', 'Germantown', '584579', NULL),
('8y2flc-21318', '8y2flc-2', '2', 'Germantown Estates', '1712614', NULL),
('8y2flc-21319', '8y2flc-2', '2', 'Germantown Park', '1712616', NULL),
('8y2flc-21320', '8y2flc-2', '2', 'Germantown View', '1712618', NULL),
('8y2flc-21321', '8y2flc-2', '2', 'Glemont Forest', '590309', NULL),
('8y2flc-21322', '8y2flc-2', '2', 'Glen', '590310', NULL),
('8y2flc-21323', '8y2flc-2', '2', 'Glen Cameron Estates', '1712485', NULL),
('8y2flc-21324', '8y2flc-2', '2', 'Glen Cove', '590312', NULL),
('8y2flc-21325', '8y2flc-2', '2', 'Glen Echo', '590313', NULL),
('8y2flc-21326', '8y2flc-2', '2', 'Glen Echo Heights', '590314', NULL),
('8y2flc-21327', '8y2flc-2', '2', 'Glen Haven', '1713143', NULL),
('8y2flc-21328', '8y2flc-2', '2', 'Glen Hills', '590317', NULL),
('8y2flc-21329', '8y2flc-2', '2', 'Glen Mar Park', '590318', NULL),
('8y2flc-21330', '8y2flc-2', '2', 'Glen Query', '1712963', NULL),
('8y2flc-21331', '8y2flc-2', '2', 'Glenallen', '590320', NULL),
('8y2flc-21332', '8y2flc-2', '2', 'Glenbrook', '590322', NULL),
('8y2flc-21333', '8y2flc-2', '2', 'Glenbrook Knoll', '590323', NULL),
('8y2flc-21334', '8y2flc-2', '2', 'Glenmont', '590330', NULL),
('8y2flc-21335', '8y2flc-2', '2', 'Glenmont Hills', '590331', NULL),
('8y2flc-21336', '8y2flc-2', '2', 'Glenmont Village', '590332', NULL),
('8y2flc-21337', '8y2flc-2', '2', 'Glenora Hills', '590333', NULL),
('8y2flc-21338', '8y2flc-2', '2', 'Glenview', '590335', NULL),
('8y2flc-21339', '8y2flc-2', '2', 'Glenwood', '590337', NULL),
('8y2flc-21340', '8y2flc-2', '2', 'Gold Mine Crossing', '2459017', NULL),
('8y2flc-21341', '8y2flc-2', '2', 'Golf Estates', '1712742', NULL),
('8y2flc-21342', '8y2flc-2', '2', 'Good Hope', '584637', NULL),
('8y2flc-21343', '8y2flc-2', '2', 'Good Hope Estates', '2459018', NULL),
('8y2flc-21344', '8y2flc-2', '2', 'Goodacre Knolls', '590344', NULL),
('8y2flc-21345', '8y2flc-2', '2', 'Goshen', '590347', NULL),
('8y2flc-21346', '8y2flc-2', '2', 'Goshen Hunt Estates', '1712746', NULL),
('8y2flc-21347', '8y2flc-2', '2', 'Goshen Hunt Hills', '1712747', NULL),
('8y2flc-21348', '8y2flc-2', '2', 'Granby Woods', '1712749', NULL),
('8y2flc-21349', '8y2flc-2', '2', 'Great Falls', '590363', NULL),
('8y2flc-21350', '8y2flc-2', '2', 'Green Acres', '590365', NULL),
('8y2flc-21351', '8y2flc-2', '2', 'Green Castle Woods', '2459024', NULL),
('8y2flc-21352', '8y2flc-2', '2', 'Green Tree Manor', '590373', NULL),
('8y2flc-21353', '8y2flc-2', '2', 'Green Wood Knolls', '590374', NULL),
('8y2flc-21354', '8y2flc-2', '2', 'Greenhills', '1712543', NULL),
('8y2flc-21355', '8y2flc-2', '2', 'Greenridge Acres', '1712751', NULL),
('8y2flc-21356', '8y2flc-2', '2', 'Greenwich Forest', '590383', NULL),
('8y2flc-21357', '8y2flc-2', '2', 'Grey Estates', '590387', NULL),
('8y2flc-21358', '8y2flc-2', '2', 'Griffith Park', '1712754', NULL),
('8y2flc-21359', '8y2flc-2', '2', 'Gum Springs', '2459028', NULL),
('8y2flc-21360', '8y2flc-2', '2', 'Hadley Farms', '1712756', NULL),
('8y2flc-21361', '8y2flc-2', '2', 'Hallowell', '1712757', NULL),
('8y2flc-21362', '8y2flc-2', '2', 'Halpine Village', '590404', NULL),
('8y2flc-21363', '8y2flc-2', '2', 'Hamlet North', '1712622', NULL),
('8y2flc-21364', '8y2flc-2', '2', 'Harlow', '1712885', NULL),
('8y2flc-21365', '8y2flc-2', '2', 'Harmony Hall', '1712486', NULL),
('8y2flc-21366', '8y2flc-2', '2', 'Harmony Hills', '590424', NULL),
('8y2flc-21367', '8y2flc-2', '2', 'Hartley Hall Estates', '1712965', NULL),
('8y2flc-21368', '8y2flc-2', '2', 'Harvest Hunt Farm', '1712966', NULL),
('8y2flc-21369', '8y2flc-2', '2', 'Hawlings Hills', '1712758', NULL),
('8y2flc-21370', '8y2flc-2', '2', 'Hawlings Meadow', '1712887', NULL),
('8y2flc-21371', '8y2flc-2', '2', 'Hawlings River Estates', '1712759', NULL),
('8y2flc-21372', '8y2flc-2', '2', 'Hawlings View', '1712761', NULL),
('8y2flc-21373', '8y2flc-2', '2', 'Henderson Corner', '1712762', NULL),
('8y2flc-21374', '8y2flc-2', '2', 'Heritage Walk', '2459045', NULL),
('8y2flc-21375', '8y2flc-2', '2', 'Hermitage Park', '590450', NULL),
('8y2flc-21376', '8y2flc-2', '2', 'Hickory Grove', '2459046', NULL),
('8y2flc-21377', '8y2flc-2', '2', 'Hickory Hill', '1712488', NULL),
('8y2flc-21378', '8y2flc-2', '2', 'Hickory Ridge', '1712489', NULL),
('8y2flc-21379', '8y2flc-2', '2', 'High Point', '590459', NULL),
('8y2flc-21380', '8y2flc-2', '2', 'Highland View', '590469', NULL),
('8y2flc-21381', '8y2flc-2', '2', 'Highlands of Darnestown', '1712968', NULL),
('8y2flc-21382', '8y2flc-2', '2', 'Highlands of Olney', '1712763', NULL),
('8y2flc-21383', '8y2flc-2', '2', 'Highview', '1712544', NULL),
('8y2flc-21384', '8y2flc-2', '2', 'Hillandale', '590471', NULL),
('8y2flc-21385', '8y2flc-2', '2', 'Hillandale Heights', '590472', NULL),
('8y2flc-21386', '8y2flc-2', '2', 'Hillmead', '590476', NULL),
('8y2flc-21387', '8y2flc-2', '2', 'Holiday Hills', '1712764', NULL),
('8y2flc-21388', '8y2flc-2', '2', 'Holiday Park', '590486', NULL),
('8y2flc-21389', '8y2flc-2', '2', 'Hollinridge', '590487', NULL),
('8y2flc-21390', '8y2flc-2', '2', 'Holly Hill', '590491', NULL),
('8y2flc-21391', '8y2flc-2', '2', 'Hollywood Park', '590494', NULL),
('8y2flc-21392', '8y2flc-2', '2', 'Homecrest', '590495', NULL),
('8y2flc-21393', '8y2flc-2', '2', 'Homestead Estates', '590496', NULL),
('8y2flc-21394', '8y2flc-2', '2', 'Homewood', '590497', NULL),
('8y2flc-21395', '8y2flc-2', '2', 'Hungerford Towne', '590513', NULL),
('8y2flc-21396', '8y2flc-2', '2', 'Hunting Hill', '590516', NULL),
('8y2flc-21397', '8y2flc-2', '2', 'Huntington', '590519', NULL),
('8y2flc-21398', '8y2flc-2', '2', 'Huntington[97]', '590520', NULL),
('8y2flc-21399', '8y2flc-2', '2', 'Huntington Terrace', '590521', NULL),
('8y2flc-21400', '8y2flc-2', '2', 'Hyattstown', '590526', NULL),
('8y2flc-21401', '8y2flc-2', '2', 'Indian Spring Terrace', '590534', NULL),
('8y2flc-21402', '8y2flc-2', '2', 'Indian Spring Village', '590535', NULL),
('8y2flc-21403', '8y2flc-2', '2', 'Inverness Knolls', '2459067', NULL),
('8y2flc-21404', '8y2flc-2', '2', 'Janwood', '1712495', NULL),
('8y2flc-21405', '8y2flc-2', '2', 'Jerusalem', '590558', NULL),
('8y2flc-21406', '8y2flc-2', '2', 'Jonesville', '590570', NULL),
('8y2flc-21407', '8y2flc-2', '2', 'Kemp Mill', '1852594', NULL),
('8y2flc-21408', '8y2flc-2', '2', 'Kemp Mill Estates', '590582', NULL),
('8y2flc-21409', '8y2flc-2', '2', 'Kemp Mill Farms', '2459076', NULL),
('8y2flc-21410', '8y2flc-2', '2', 'Kemp Mill Forest', '2459077', NULL),
('8y2flc-21411', '8y2flc-2', '2', 'Ken Gar', '590586', NULL),
('8y2flc-21412', '8y2flc-2', '2', 'Kensington', '590589', NULL),
('8y2flc-21413', '8y2flc-2', '2', 'Kensington Estates', '590590', NULL),
('8y2flc-21414', '8y2flc-2', '2', 'Kensington Heights', '590591', NULL),
('8y2flc-21415', '8y2flc-2', '2', 'Kensington Knolls', '590592', NULL),
('8y2flc-21416', '8y2flc-2', '2', 'Kensington View', '590593', NULL),
('8y2flc-21417', '8y2flc-2', '2', 'Kenwood', '590595', NULL),
('8y2flc-21418', '8y2flc-2', '2', 'Kenwood Park', '590598', NULL),
('8y2flc-21419', '8y2flc-2', '2', 'Kilmarock', '590601', NULL),
('8y2flc-21420', '8y2flc-2', '2', 'Kimberley', '590602', NULL),
('8y2flc-21421', '8y2flc-2', '2', 'Kings Square', '1712776', NULL),
('8y2flc-21422', '8y2flc-2', '2', 'Kings Valley', '588684', NULL),
('8y2flc-21423', '8y2flc-2', '2', 'Kings Valley Manor', '1712545', NULL),
('8y2flc-21424', '8y2flc-2', '2', 'Kingsley', '590604', NULL),
('8y2flc-21425', '8y2flc-2', '2', 'Kingstead Knolls', '1712546', NULL),
('8y2flc-21426', '8y2flc-2', '2', 'Kingsview Knolls', '1712628', NULL),
('8y2flc-21427', '8y2flc-2', '2', 'Knightsbridge', '2459084', NULL),
('8y2flc-21428', '8y2flc-2', '2', 'Knollwood', '1712972', NULL),
('8y2flc-21429', '8y2flc-2', '2', 'Lake Normandy Estates', '590622', NULL),
('8y2flc-21430', '8y2flc-2', '2', 'Lake Potomac', '1712973', NULL),
('8y2flc-21431', '8y2flc-2', '2', 'Lakewood Estates', '590627', NULL),
('8y2flc-21432', '8y2flc-2', '2', 'Landon Village', '590631', NULL),
('8y2flc-21433', '8y2flc-2', '2', 'Larchmont Knolls', '590638', NULL),
('8y2flc-21434', '8y2flc-2', '2', 'Layhill', '590644', NULL),
('8y2flc-21435', '8y2flc-2', '2', 'Layhill South', '590645', NULL),
('8y2flc-21436', '8y2flc-2', '2', 'Layhill Village', '590646', NULL),
('8y2flc-21437', '8y2flc-2', '2', 'Layton Ridge', '1712778', NULL),
('8y2flc-21438', '8y2flc-2', '2', 'Laytonsville', '585383', NULL),
('8y2flc-21439', '8y2flc-2', '2', 'Laytonsville Knolls', '1712780', NULL),
('8y2flc-21440', '8y2flc-2', '2', 'Lees Corner', '1712629', NULL),
('8y2flc-21441', '8y2flc-2', '2', 'Lelands Corner', '585398', NULL),
('8y2flc-21442', '8y2flc-2', '2', 'Lewisdale', '590661', NULL),
('8y2flc-21443', '8y2flc-2', '2', 'Liberty Heights', '1712630', NULL),
('8y2flc-21444', '8y2flc-2', '2', 'Linden', '590668', NULL),
('8y2flc-21445', '8y2flc-2', '2', 'Locust Hill Estates', '590689', NULL),
('8y2flc-21446', '8y2flc-2', '2', 'Log Town (historical)', '1712575', NULL),
('8y2flc-21447', '8y2flc-2', '2', 'Londonderry', '1712783', NULL),
('8y2flc-21448', '8y2flc-2', '2', 'Lone Oak', '590693', NULL),
('8y2flc-21449', '8y2flc-2', '2', 'Longdraft', '1712632', NULL),
('8y2flc-21450', '8y2flc-2', '2', 'Longview South', '1712784', NULL),
('8y2flc-21451', '8y2flc-2', '2', 'Longwood', '590701', NULL),
('8y2flc-21452', '8y2flc-2', '2', 'Lutes', '590710', NULL),
('8y2flc-21453', '8y2flc-2', '2', 'Luxmanor', '585639', NULL),
('8y2flc-21454', '8y2flc-2', '2', 'Lyttonsville', '1713183', NULL),
('8y2flc-21455', '8y2flc-2', '2', 'Maidens Fancy Manor', '2459106', NULL),
('8y2flc-21456', '8y2flc-2', '2', 'Manor Oaks', '2459108', NULL),
('8y2flc-21457', '8y2flc-2', '2', 'Manor Park', '590730', NULL),
('8y2flc-21458', '8y2flc-2', '2', 'Manor Village', '2459109', NULL),
('8y2flc-21459', '8y2flc-2', '2', 'Maplewood', '590736', NULL),
('8y2flc-21460', '8y2flc-2', '2', 'Martins Addition', '1713187', NULL),
('8y2flc-21461', '8y2flc-2', '2', 'Martins Additions', '1669431', NULL),
('8y2flc-21462', '8y2flc-2', '2', 'Martinsburg', '585719', NULL),
('8y2flc-21463', '8y2flc-2', '2', 'Marymount', '590756', NULL),
('8y2flc-21464', '8y2flc-2', '2', 'Maydale', '2459120', NULL),
('8y2flc-21465', '8y2flc-2', '2', 'McAuley Park', '590768', NULL),
('8y2flc-21466', '8y2flc-2', '2', 'McKenney Hills', '590777', NULL),
('8y2flc-21467', '8y2flc-2', '2', 'Meadowbrook Estates', '1712634', NULL),
('8y2flc-21468', '8y2flc-2', '2', 'Meadowood', '590785', NULL),
('8y2flc-21469', '8y2flc-2', '2', 'Merrimack Park', '590790', NULL),
('8y2flc-21470', '8y2flc-2', '2', 'Metropolitan Grove', '588697', NULL),
('8y2flc-21471', '8y2flc-2', '2', 'Middlebrook', '590795', NULL),
('8y2flc-21472', '8y2flc-2', '2', 'Middlebrook Hills', '1712790', NULL),
('8y2flc-21473', '8y2flc-2', '2', 'Middlebrook Mobile Home Park', '1712791', NULL),
('8y2flc-21474', '8y2flc-2', '2', 'Miles Corner', '1712635', NULL),
('8y2flc-21475', '8y2flc-2', '2', 'Milestone', '1712793', NULL),
('8y2flc-21476', '8y2flc-2', '2', 'Mill Grove Gardens', '1712794', NULL),
('8y2flc-21477', '8y2flc-2', '2', 'Mills Farm', '1712980', NULL),
('8y2flc-21478', '8y2flc-2', '2', 'Mills Farm East', '1712981', NULL),
('8y2flc-21479', '8y2flc-2', '2', 'Mitchells Range', '1712982', NULL),
('8y2flc-21480', '8y2flc-2', '2', 'Mohican Hills', '590811', NULL),
('8y2flc-21481', '8y2flc-2', '2', 'Monocacy (historical)', '1712550', NULL),
('8y2flc-21482', '8y2flc-2', '2', 'Monterrey Village', '590817', NULL),
('8y2flc-21483', '8y2flc-2', '2', 'Montgomery Hills', '590818', NULL),
('8y2flc-21484', '8y2flc-2', '2', 'Montgomery Knolls', '590819', NULL),
('8y2flc-21485', '8y2flc-2', '2', 'Montgomery Meadows', '2459134', NULL),
('8y2flc-21486', '8y2flc-2', '2', 'Montgomery Square', '590820', NULL),
('8y2flc-21487', '8y2flc-2', '2', 'Montgomery Village', '1712797', NULL),
('8y2flc-21488', '8y2flc-2', '2', 'Montrose', '590821', NULL),
('8y2flc-21489', '8y2flc-2', '2', 'Mount Ephraim', '588701', NULL),
('8y2flc-21490', '8y2flc-2', '2', 'Mount Lebanon', '1712502', NULL),
('8y2flc-21491', '8y2flc-2', '2', 'Mount Radnor Heights', '1712503', NULL),
('8y2flc-21492', '8y2flc-2', '2', 'Mount Zion', '590849', NULL),
('8y2flc-21493', '8y2flc-2', '2', 'Mountain View Estates', '1712997', NULL),
('8y2flc-21494', '8y2flc-2', '2', 'Mullinix', '590859', NULL),
('8y2flc-21495', '8y2flc-2', '2', 'Muncaster Manor', '1712800', NULL),
('8y2flc-21496', '8y2flc-2', '2', 'Naples Manor', '2459137', NULL),
('8y2flc-21497', '8y2flc-2', '2', 'Nathans Hill', '1712802', NULL),
('8y2flc-21498', '8y2flc-2', '2', 'Natural Woods', '1712552', NULL),
('8y2flc-21499', '8y2flc-2', '2', 'Needwood Estates', '2459138', NULL),
('8y2flc-21500', '8y2flc-2', '2', 'Neelsville', '590869', NULL),
('8y2flc-21501', '8y2flc-2', '2', 'New Birmingham Manor', '590871', NULL),
('8y2flc-21502', '8y2flc-2', '2', 'New Hampshire Estates', '590873', NULL),
('8y2flc-21503', '8y2flc-2', '2', 'Newport Hills', '590881', NULL),
('8y2flc-21504', '8y2flc-2', '2', 'Norbeck', '586203', NULL),
('8y2flc-21505', '8y2flc-2', '2', 'Norbeck Estates', '1712804', NULL),
('8y2flc-21506', '8y2flc-2', '2', 'Norbrook Village', '1712805', NULL),
('8y2flc-21507', '8y2flc-2', '2', 'North Bethesda', '1867297', NULL),
('8y2flc-21508', '8y2flc-2', '2', 'North Chevy Chase', '590889', NULL),
('8y2flc-21509', '8y2flc-2', '2', 'North Farm', '2459144', NULL),
('8y2flc-21510', '8y2flc-2', '2', 'North Germantown', '1713199', NULL),
('8y2flc-21511', '8y2flc-2', '2', 'North Hills Sligo Park', '590892', NULL),
('8y2flc-21512', '8y2flc-2', '2', 'North Kensington', '590893', NULL),
('8y2flc-21513', '8y2flc-2', '2', 'North Potomac', '1713001', NULL),
('8y2flc-21514', '8y2flc-2', '2', 'North Sherwood Forest', '590898', NULL),
('8y2flc-21515', '8y2flc-2', '2', 'North Springbrook', '590899', NULL),
('8y2flc-21516', '8y2flc-2', '2', 'North Takoma Park', '590900', NULL),
('8y2flc-21517', '8y2flc-2', '2', 'Northbrook Estates', '590902', NULL),
('8y2flc-21518', '8y2flc-2', '2', 'Northwest Park', '590904', NULL),
('8y2flc-21519', '8y2flc-2', '2', 'Northwest Park[77]', '590905', NULL),
('8y2flc-21520', '8y2flc-2', '2', 'Northwood Forest', '590906', NULL),
('8y2flc-21521', '8y2flc-2', '2', 'Northwood Park', '590907', NULL),
('8y2flc-21522', '8y2flc-2', '2', 'Norwood', '590908', NULL),
('8y2flc-21523', '8y2flc-2', '2', 'Norwood Estates', '590909', NULL),
('8y2flc-21524', '8y2flc-2', '2', 'Norwood Knolls', '2459150', NULL),
('8y2flc-21525', '8y2flc-2', '2', 'Norwood Village', '1713201', NULL),
('8y2flc-21526', '8y2flc-2', '2', 'Oak Hill Estates', '1712807', NULL),
('8y2flc-21527', '8y2flc-2', '2', 'Oak Ridge', '1712637', NULL),
('8y2flc-21528', '8y2flc-2', '2', 'Oak Springs', '2459153', NULL),
('8y2flc-21529', '8y2flc-2', '2', 'Oakdale', '590918', NULL),
('8y2flc-21530', '8y2flc-2', '2', 'Oakhurst', '2459156', NULL),
('8y2flc-21531', '8y2flc-2', '2', 'Oakmont', '590928', NULL),
('8y2flc-21532', '8y2flc-2', '2', 'Oakmont Manor', '1712638', NULL),
('8y2flc-21533', '8y2flc-2', '2', 'Oakview', '586281', NULL),
('8y2flc-21534', '8y2flc-2', '2', 'Oakwood Knolls', '590931', NULL),
('8y2flc-21535', '8y2flc-2', '2', 'Observatory Heights', '1712809', NULL),
('8y2flc-21536', '8y2flc-2', '2', 'Old Farm', '590939', NULL),
('8y2flc-21537', '8y2flc-2', '2', 'Old Georgetown Estates', '590940', NULL),
('8y2flc-21538', '8y2flc-2', '2', 'Old Germantown', '588705', NULL),
('8y2flc-21539', '8y2flc-2', '2', 'Old Salem Village', '590943', NULL),
('8y2flc-21540', '8y2flc-2', '2', 'Olney', '590948', NULL),
('8y2flc-21541', '8y2flc-2', '2', 'Olney Acres', '1712810', NULL),
('8y2flc-21542', '8y2flc-2', '2', 'Olney Estates', '1712812', NULL),
('8y2flc-21543', '8y2flc-2', '2', 'Olney Mill', '1712813', NULL),
('8y2flc-21544', '8y2flc-2', '2', 'Olney Oaks', '1712814', NULL),
('8y2flc-21545', '8y2flc-2', '2', 'Olney Square', '1712816', NULL),
('8y2flc-21546', '8y2flc-2', '2', 'Olney Town', '1712818', NULL),
('8y2flc-21547', '8y2flc-2', '2', 'Orchard Place', '1712819', NULL),
('8y2flc-21548', '8y2flc-2', '2', 'Orchard Pond', '1712640', NULL),
('8y2flc-21549', '8y2flc-2', '2', 'Paint Branch Estates', '2459164', NULL),
('8y2flc-21550', '8y2flc-2', '2', 'Paint Branch Farms', '590964', NULL),
('8y2flc-21551', '8y2flc-2', '2', 'Park View Estates', '1712554', NULL),
('8y2flc-21552', '8y2flc-2', '2', 'Parkridge', '1712641', NULL),
('8y2flc-21553', '8y2flc-2', '2', 'Parkridge Estates', '1712642', NULL),
('8y2flc-21554', '8y2flc-2', '2', 'Parkside', '590973', NULL),
('8y2flc-21555', '8y2flc-2', '2', 'Parkview Estates', '590975', NULL),
('8y2flc-21556', '8y2flc-2', '2', 'Parkwood', '590978', NULL),
('8y2flc-21557', '8y2flc-2', '2', 'Parrs Ridge', '1713204', NULL),
('8y2flc-21558', '8y2flc-2', '2', 'Peach Orchard Heights', '590988', NULL),
('8y2flc-21559', '8y2flc-2', '2', 'Perrywood Estates', '586479', NULL),
('8y2flc-21560', '8y2flc-2', '2', 'Pine Hill', '591008', NULL),
('8y2flc-21561', '8y2flc-2', '2', 'Pine Knolls', '591010', NULL),
('8y2flc-21562', '8y2flc-2', '2', 'Pioneer Hills', '1712893', NULL),
('8y2flc-21563', '8y2flc-2', '2', 'Pleasant Fields', '1712643', NULL),
('8y2flc-21564', '8y2flc-2', '2', 'Pleasant Run', '1712644', NULL),
('8y2flc-21565', '8y2flc-2', '2', 'Plumgar', '1712821', NULL),
('8y2flc-21566', '8y2flc-2', '2', 'Plyers Mill Estates', '591030', NULL),
('8y2flc-21567', '8y2flc-2', '2', 'Polo Club Estates', '1713002', NULL),
('8y2flc-21568', '8y2flc-2', '2', 'Pooks Hill', '591043', NULL),
('8y2flc-21569', '8y2flc-2', '2', 'Poolesville', '593418', NULL),
('8y2flc-21570', '8y2flc-2', '2', 'Potomac', '591056', NULL),
('8y2flc-21571', '8y2flc-2', '2', 'Potomac Chase', '1713003', NULL),
('8y2flc-21572', '8y2flc-2', '2', 'Potomac Chase Estates', '1713004', NULL),
('8y2flc-21573', '8y2flc-2', '2', 'Potomac Falls', '591057', NULL),
('8y2flc-21574', '8y2flc-2', '2', 'Potomac Grove', '1713005', NULL),
('8y2flc-21575', '8y2flc-2', '2', 'Potomac Hunt Acres', '591060', NULL),
('8y2flc-21576', '8y2flc-2', '2', 'Potomac Manors', '591061', NULL),
('8y2flc-21577', '8y2flc-2', '2', 'Potomac Park Estate', '1712894', NULL),
('8y2flc-21578', '8y2flc-2', '2', 'Potomac Woods', '591064', NULL),
('8y2flc-21579', '8y2flc-2', '2', 'Prathertown', '591068', NULL),
('8y2flc-21580', '8y2flc-2', '2', 'Purdum', '586728', NULL),
('8y2flc-21581', '8y2flc-2', '2', 'Quail Hill', '1712823', NULL),
('8y2flc-21582', '8y2flc-2', '2', 'Quail Ridge', '1712824', NULL),
('8y2flc-21583', '8y2flc-2', '2', 'Quail Run', '1713010', NULL),
('8y2flc-21584', '8y2flc-2', '2', 'Quail Valley', '1712645', NULL),
('8y2flc-21585', '8y2flc-2', '2', 'Quaint Acres', '591086', NULL),
('8y2flc-21586', '8y2flc-2', '2', 'Quince Orchard', '588718', NULL),
('8y2flc-21587', '8y2flc-2', '2', 'Quince Orchard Knolls', '1713012', NULL),
('8y2flc-21588', '8y2flc-2', '2', 'Quince Orchard Manor', '1712646', NULL),
('8y2flc-21589', '8y2flc-2', '2', 'Quince Orchard Valley', '1712649', NULL),
('8y2flc-21590', '8y2flc-2', '2', 'Randolph Hills', '591097', NULL),
('8y2flc-21591', '8y2flc-2', '2', 'Redland', '586797', NULL),
('8y2flc-21592', '8y2flc-2', '2', 'Regency Estates', '591109', NULL),
('8y2flc-21593', '8y2flc-2', '2', 'Relda Square', '1712653', NULL),
('8y2flc-21594', '8y2flc-2', '2', 'Ridgecrest', '2459193', NULL),
('8y2flc-21595', '8y2flc-2', '2', 'Ridgeland Farm Estates', '1712895', NULL),
('8y2flc-21596', '8y2flc-2', '2', 'Ridges of Stedwick', '2459194', NULL),
('8y2flc-21597', '8y2flc-2', '2', 'Riding Stable Estates', '2459195', NULL),
('8y2flc-21598', '8y2flc-2', '2', 'Rive Gauche Estates', '1712896', NULL),
('8y2flc-21599', '8y2flc-2', '2', 'Riverwood', '1712897', NULL),
('8y2flc-21600', '8y2flc-2', '2', 'Robindale', '591148', NULL),
('8y2flc-21601', '8y2flc-2', '2', 'Rock Creek Forest', '591149', NULL),
('8y2flc-21602', '8y2flc-2', '2', 'Rock Creek Gardens', '591150', NULL),
('8y2flc-21603', '8y2flc-2', '2', 'Rock Creek Hills', '591151', NULL),
('8y2flc-21604', '8y2flc-2', '2', 'Rock Creek Knolls', '591152', NULL),
('8y2flc-21605', '8y2flc-2', '2', 'Rock Creek Palisades', '591153', NULL),
('8y2flc-21606', '8y2flc-2', '2', 'Rock Creek Village', '591154', NULL),
('8y2flc-21607', '8y2flc-2', '2', 'Rockcrest', '591161', NULL),
('8y2flc-21608', '8y2flc-2', '2', 'Rockland', '591166', NULL),
('8y2flc-21609', '8y2flc-2', '2', 'Rockville', '586901', NULL),
('8y2flc-21610', '8y2flc-2', '2', 'Rocky Brook Park', '591168', NULL),
('8y2flc-21611', '8y2flc-2', '2', 'Rocky Gorge Meadows', '1712827', NULL),
('8y2flc-21612', '8y2flc-2', '2', 'Rocky Road Park', '1712828', NULL),
('8y2flc-21613', '8y2flc-2', '2', 'Rolling Acres', '591174', NULL),
('8y2flc-21614', '8y2flc-2', '2', 'Rolling Knolls', '1712829', NULL),
('8y2flc-21615', '8y2flc-2', '2', 'Rollingwood', '591175', NULL),
('8y2flc-21616', '8y2flc-2', '2', 'Rollins Park', '591176', NULL),
('8y2flc-21617', '8y2flc-2', '2', 'Ronalee Hills', '1712510', NULL),
('8y2flc-21618', '8y2flc-2', '2', 'Rose Hill Estates', '591182', NULL),
('8y2flc-21619', '8y2flc-2', '2', 'Rosedale Park', '591184', NULL),
('8y2flc-21620', '8y2flc-2', '2', 'Rosemary Hills', '591185', NULL),
('8y2flc-21621', '8y2flc-2', '2', 'Rosemont', '1712656', NULL),
('8y2flc-21622', '8y2flc-2', '2', 'Rosewood Estates', '1712830', NULL),
('8y2flc-21623', '8y2flc-2', '2', 'Rossmoor', '1867299', NULL),
('8y2flc-21624', '8y2flc-2', '2', 'Running Brook Acres', '1712657', NULL),
('8y2flc-21625', '8y2flc-2', '2', 'Rushville', '588722', NULL),
('8y2flc-21626', '8y2flc-2', '2', 'Rusty Acres', '1713216', NULL),
('8y2flc-21627', '8y2flc-2', '2', 'Saddle Creek', '2459211', NULL),
('8y2flc-21628', '8y2flc-2', '2', 'Sam Rice Manor', '1712832', NULL),
('8y2flc-21629', '8y2flc-2', '2', 'Sandy Spring', '587218', NULL),
('8y2flc-21630', '8y2flc-2', '2', 'Sandy Spring Meadow', '1712834', NULL),
('8y2flc-21631', '8y2flc-2', '2', 'Sanford', '591228', NULL),
('8y2flc-21632', '8y2flc-2', '2', 'Schneiders Trailer Haven', '1712835', NULL),
('8y2flc-21633', '8y2flc-2', '2', 'Scotland', '591240', NULL),
('8y2flc-21634', '8y2flc-2', '2', 'Sellman', '591246', NULL),
('8y2flc-21635', '8y2flc-2', '2', 'Seneca', '587270', NULL),
('8y2flc-21636', '8y2flc-2', '2', 'Seneca Chase', '1712562', NULL),
('8y2flc-21637', '8y2flc-2', '2', 'Seneca Highlands', '1712903', NULL),
('8y2flc-21638', '8y2flc-2', '2', 'Seneca Overlook', '1712512', NULL),
('8y2flc-21639', '8y2flc-2', '2', 'Seneca Park', '1712836', NULL),
('8y2flc-21640', '8y2flc-2', '2', 'Seneca Springs', '2459218', NULL),
('8y2flc-21641', '8y2flc-2', '2', 'Seneca Upland', '1712837', NULL),
('8y2flc-21642', '8y2flc-2', '2', 'Sequoia', '2459219', NULL),
('8y2flc-21643', '8y2flc-2', '2', 'Seven Oaks', '591248', NULL),
('8y2flc-21644', '8y2flc-2', '2', 'Sherwood Forest', '591274', NULL),
('8y2flc-21645', '8y2flc-2', '2', 'Silver Crest', '1712513', NULL),
('8y2flc-21646', '8y2flc-2', '2', 'Silver Rock', '591288', NULL),
('8y2flc-21647', '8y2flc-2', '2', 'Silver Spring', '591290', NULL),
('8y2flc-21648', '8y2flc-2', '2', 'Silver Spring Park', '591291', NULL),
('8y2flc-21649', '8y2flc-2', '2', 'Slidell', '588725', NULL),
('8y2flc-21650', '8y2flc-2', '2', 'Sligo', '1713229', NULL),
('8y2flc-21651', '8y2flc-2', '2', 'Sligo Park Hills', '591303', NULL),
('8y2flc-21652', '8y2flc-2', '2', 'Sligo Woods', '591304', NULL),
('8y2flc-21653', '8y2flc-2', '2', 'Smithville', '1713230', NULL),
('8y2flc-21654', '8y2flc-2', '2', 'Sniders Estates', '591310', NULL),
('8y2flc-21655', '8y2flc-2', '2', 'Somerset', '591314', NULL),
('8y2flc-21656', '8y2flc-2', '2', 'Somerset Heights', '591315', NULL),
('8y2flc-21657', '8y2flc-2', '2', 'Sonoma', '591316', NULL),
('8y2flc-21658', '8y2flc-2', '2', 'South Kensington', '1867302', NULL),
('8y2flc-21659', '8y2flc-2', '2', 'South Woodside Park', '591322', NULL),
('8y2flc-21660', '8y2flc-2', '2', 'Southview', '1712563', NULL),
('8y2flc-21661', '8y2flc-2', '2', 'Spencerville', '591326', NULL),
('8y2flc-21662', '8y2flc-2', '2', 'Spencerville Knolls', '1713233', NULL),
('8y2flc-21663', '8y2flc-2', '2', 'Spring Garden Estates', '1712565', NULL),
('8y2flc-21664', '8y2flc-2', '2', 'Spring Hill', '591331', NULL),
('8y2flc-21665', '8y2flc-2', '2', 'Spring Hill[30]', '595654', NULL),
('8y2flc-21666', '8y2flc-2', '2', 'Spring Lake Park', '591332', NULL),
('8y2flc-21667', '8y2flc-2', '2', 'Spring Meadows', '1712905', NULL),
('8y2flc-21668', '8y2flc-2', '2', 'Springbrook', '591334', NULL),
('8y2flc-21669', '8y2flc-2', '2', 'Springbrook Forest', '591335', NULL),
('8y2flc-21670', '8y2flc-2', '2', 'Springbrook Manor', '591336', NULL),
('8y2flc-21671', '8y2flc-2', '2', 'Springfield', '591337', NULL),
('8y2flc-21672', '8y2flc-2', '2', 'Springwood', '591339', NULL),
('8y2flc-21673', '8y2flc-2', '2', 'Stephen Knolls', '591346', NULL),
('8y2flc-21674', '8y2flc-2', '2', 'Stewart Town', '587553', NULL),
('8y2flc-21675', '8y2flc-2', '2', 'Stonebridge', '2459253', NULL),
('8y2flc-21676', '8y2flc-2', '2', 'Stoneridge', '1712662', NULL),
('8y2flc-21677', '8y2flc-2', '2', 'Stoney Brook', '591355', NULL),
('8y2flc-21678', '8y2flc-2', '2', 'Stoney Brook Estates', '591356', NULL),
('8y2flc-21679', '8y2flc-2', '2', 'Stoney Creek Estates', '1713018', NULL),
('8y2flc-21680', '8y2flc-2', '2', 'Stoney Creek Farm', '1713019', NULL),
('8y2flc-21681', '8y2flc-2', '2', 'Stratton Woods', '591360', NULL),
('8y2flc-21682', '8y2flc-2', '2', 'Sugarland', '591372', NULL),
('8y2flc-21683', '8y2flc-2', '2', 'Sugarloaf Vista', '1712517', NULL),
('8y2flc-21684', '8y2flc-2', '2', 'Sumner', '591377', NULL),
('8y2flc-21685', '8y2flc-2', '2', 'Sunnymeade', '1712844', NULL),
('8y2flc-21686', '8y2flc-2', '2', 'Sunset Terrace', '591382', NULL),
('8y2flc-21687', '8y2flc-2', '2', 'Sunshine', '587637', NULL),
('8y2flc-21688', '8y2flc-2', '2', 'Sunshine Acres', '1712845', NULL),
('8y2flc-21689', '8y2flc-2', '2', 'Sweepstakes', '1712566', NULL),
('8y2flc-21690', '8y2flc-2', '2', 'Sycamore Acres', '591387', NULL),
('8y2flc-21691', '8y2flc-2', '2', 'Sycamore Creek', '591388', NULL),
('8y2flc-21692', '8y2flc-2', '2', 'Takoma Park', '598146', NULL),
('8y2flc-21693', '8y2flc-2', '2', 'Tanterra', '1712846', NULL),
('8y2flc-21694', '8y2flc-2', '2', 'The Colony', '1712666', NULL),
('8y2flc-21695', '8y2flc-2', '2', 'The Hamlet', '591403', NULL),
('8y2flc-21696', '8y2flc-2', '2', 'The Plantations', '1712847', NULL),
('8y2flc-21697', '8y2flc-2', '2', 'The Ponderosa', '1712520', NULL),
('8y2flc-21698', '8y2flc-2', '2', 'Thompsons Corner', '588732', NULL),
('8y2flc-21699', '8y2flc-2', '2', 'Tilden Woods', '591410', NULL),
('8y2flc-21700', '8y2flc-2', '2', 'Timberland Estates', '1712849', NULL),
('8y2flc-21701', '8y2flc-2', '2', 'Tobytown', '1712907', NULL),
('8y2flc-21702', '8y2flc-2', '2', 'Towne Centre Place', '1712850', NULL),
('8y2flc-21703', '8y2flc-2', '2', 'Travilah', '588734', NULL),
('8y2flc-21704', '8y2flc-2', '2', 'Travilah Acres', '1713020', NULL),
('8y2flc-21705', '8y2flc-2', '2', 'Travilah Meadows', '1713021', NULL),
('8y2flc-21706', '8y2flc-2', '2', 'Triadelphia (historical)', '598518', NULL),
('8y2flc-21707', '8y2flc-2', '2', 'Tulip Hill', '591437', NULL),
('8y2flc-21708', '8y2flc-2', '2', 'Twin Brook', '591444', NULL),
('8y2flc-21709', '8y2flc-2', '2', 'Twin Brook Forest', '591445', NULL),
('8y2flc-21710', '8y2flc-2', '2', 'Unity', '593437', NULL),
('8y2flc-21711', '8y2flc-2', '2', 'Upper Seneca Crest', '1712521', NULL),
('8y2flc-21712', '8y2flc-2', '2', 'Valley Stream Estates', '587992', NULL),
('8y2flc-21713', '8y2flc-2', '2', 'Viers Mill Village', '588007', NULL),
('8y2flc-21714', '8y2flc-2', '2', 'Walkers Choice', '1712851', NULL),
('8y2flc-21715', '8y2flc-2', '2', 'Walnut Hill', '1712667', NULL),
('8y2flc-21716', '8y2flc-2', '2', 'Walnut Woods', '591489', NULL),
('8y2flc-21717', '8y2flc-2', '2', 'Ward Farm Estates', '1712853', NULL),
('8y2flc-21718', '8y2flc-2', '2', 'Waring (historical)', '1712576', NULL),
('8y2flc-21719', '8y2flc-2', '2', 'Washington Grove', '591497', NULL),
('8y2flc-21720', '8y2flc-2', '2', 'Washingtonian Woods', '2459307', NULL),
('8y2flc-21721', '8y2flc-2', '2', 'Watkins Mill', '1712854', NULL),
('8y2flc-21722', '8y2flc-2', '2', 'Watkins Overlook', '1712857', NULL),
('8y2flc-21723', '8y2flc-2', '2', 'Wesmond', '1712569', NULL),
('8y2flc-21724', '8y2flc-2', '2', 'West Chevy Chase Heights', '591516', NULL),
('8y2flc-21725', '8y2flc-2', '2', 'West End Park', '591519', NULL),
('8y2flc-21726', '8y2flc-2', '2', 'West Riding', '1712672', NULL),
('8y2flc-21727', '8y2flc-2', '2', 'Westboro', '591530', NULL),
('8y2flc-21728', '8y2flc-2', '2', 'Westerly', '1712570', NULL),
('8y2flc-21729', '8y2flc-2', '2', 'Westgate', '591533', NULL),
('8y2flc-21730', '8y2flc-2', '2', 'Westmore', '591534', NULL),
('8y2flc-21731', '8y2flc-2', '2', 'Westmoreland Hills', '591535', NULL),
('8y2flc-21732', '8y2flc-2', '2', 'Westwood', '591537', NULL),
('8y2flc-21733', '8y2flc-2', '2', 'Wexford', '1712859', NULL),
('8y2flc-21734', '8y2flc-2', '2', 'Wheaton', '588185', NULL),
('8y2flc-21735', '8y2flc-2', '2', 'Wheaton Crest', '593889', NULL),
('8y2flc-21736', '8y2flc-2', '2', 'Wheaton Forest', '591539', NULL),
('8y2flc-21737', '8y2flc-2', '2', 'Wheaton Hills', '588187', NULL),
('8y2flc-21738', '8y2flc-2', '2', 'Wheaton Woods', '591540', NULL),
('8y2flc-21739', '8y2flc-2', '2', 'Whetstone', '1712860', NULL),
('8y2flc-21740', '8y2flc-2', '2', 'White Oak', '591544', NULL),
('8y2flc-21741', '8y2flc-2', '2', 'Whitehall Manor', '591548', NULL),
('8y2flc-21742', '8y2flc-2', '2', 'Wickford', '588230', NULL),
('8y2flc-21743', '8y2flc-2', '2', 'Wilber', '1712673', NULL),
('8y2flc-21744', '8y2flc-2', '2', 'Wildcat Forest', '1712862', NULL),
('8y2flc-21745', '8y2flc-2', '2', 'Wilderness Walk', '1712863', NULL),
('8y2flc-21746', '8y2flc-2', '2', 'Wildwood Hills', '591555', NULL),
('8y2flc-21747', '8y2flc-2', '2', 'Wildwood Manor', '591556', NULL),
('8y2flc-21748', '8y2flc-2', '2', 'Willerburn Acres', '591558', NULL),
('8y2flc-21749', '8y2flc-2', '2', 'Willett Estates', '1712864', NULL),
('8y2flc-21750', '8y2flc-2', '2', 'Williamsburg Estates', '591560', NULL),
('8y2flc-21751', '8y2flc-2', '2', 'Williamsburg Square', '1712674', NULL),
('8y2flc-21752', '8y2flc-2', '2', 'Williamsburg Village', '1712866', NULL),
('8y2flc-21753', '8y2flc-2', '2', 'Willow Ridge', '1713024', NULL),
('8y2flc-21754', '8y2flc-2', '2', 'Willson Hills', '591567', NULL),
('8y2flc-21755', '8y2flc-2', '2', 'Windbrook', '2459325', NULL),
('8y2flc-21756', '8y2flc-2', '2', 'Windham (historical)', '1713258', NULL),
('8y2flc-21757', '8y2flc-2', '2', 'Windham Manor', '591575', NULL),
('8y2flc-21758', '8y2flc-2', '2', 'Windmill Farm', '1713025', NULL),
('8y2flc-21759', '8y2flc-2', '2', 'Winters Run', '2459329', NULL),
('8y2flc-21760', '8y2flc-2', '2', 'Wolf Acres', '591580', NULL),
('8y2flc-21761', '8y2flc-2', '2', 'Wood Acres', '591584', NULL),
('8y2flc-21762', '8y2flc-2', '2', 'Woodburn', '591587', NULL),
('8y2flc-21763', '8y2flc-2', '2', 'Woodbyran Farms', '1712909', NULL),
('8y2flc-21764', '8y2flc-2', '2', 'Woodfield', '591591', NULL),
('8y2flc-21765', '8y2flc-2', '2', 'Woodhaven', '591592', NULL),
('8y2flc-21766', '8y2flc-2', '2', 'Woodley Gardens', '591600', NULL),
('8y2flc-21767', '8y2flc-2', '2', 'Woodmont', '591602', NULL),
('8y2flc-21768', '8y2flc-2', '2', 'Woodmoor', '591603', NULL),
('8y2flc-21769', '8y2flc-2', '2', 'Woodside', '588337', NULL),
('8y2flc-21770', '8y2flc-2', '2', 'Woodside Forest', '591605', NULL),
('8y2flc-21771', '8y2flc-2', '2', 'Woodside Park', '591606', NULL),
('8y2flc-21772', '8y2flc-2', '2', 'Wyngate', '591616', NULL),
('8y2flc-4', NULL, '1', 'District of Columbia [TO DO]', '1702382', '(There is also a City of Washington ''Civic'' code: 2390665)'),
('8y2flc-5', NULL, '1', 'Prince George''s County, MD [TO DO]', '1714670', 'Codes at Level 1 are all ''Civic'' category BGN codes'),
('8y2flc-7', NULL, '1', 'Frederick County, MD [TO DO]', '1711211', 'Codes at Level 2 are all ''Populated Places'' category BGN codes'),
('8y2flc-8', NULL, '1', 'Howard County, MD [TO DO]', '1709077', NULL),
('8y2flc-9', NULL, '1', 'Baltimore County, MD [TO DO]', '1695314', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `location_details`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `location_details` (
  `poc_uuid` varchar(60) NOT NULL,
  `location_id` varchar(60) NOT NULL default '',
  `opt_person_loc_type` varchar(10) default NULL,
  `address` text,
  `postcode` varchar(30) default NULL,
  `long_lat` varchar(20) default NULL,
  PRIMARY KEY  (`poc_uuid`,`location_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `location_details`
--


-- --------------------------------------------------------

--
-- Table structure for table `loc_seq_seq`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `loc_seq_seq` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `loc_seq_seq`
--

INSERT INTO `loc_seq_seq` (`id`) VALUES
(21773);

-- --------------------------------------------------------

--
-- Table structure for table `mpres_log`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `mpres_log` (
  `log_index` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(64) NOT NULL,
  `email_subject` varchar(256) NOT NULL,
  `email_from` varchar(128) NOT NULL,
  `email_date` varchar(64) NOT NULL,
  `update_time` datetime NOT NULL,
  PRIMARY KEY  (`log_index`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=160 ;

--
-- RELATIONS FOR TABLE `mpres_log`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `mpres_log`
--


-- --------------------------------------------------------

--
-- Table structure for table `old_passwords`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `old_passwords` (
  `p_uuid` varchar(60) NOT NULL,
  `password` varchar(100) NOT NULL default '',
  `changed_timestamp` bigint(20) NOT NULL,
  PRIMARY KEY  (`p_uuid`,`password`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `old_passwords`
--


-- --------------------------------------------------------

--
-- Table structure for table `password_event_log`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `password_event_log` (
  `log_id` bigint(20) NOT NULL auto_increment,
  `changed_timestamp` bigint(20) NOT NULL,
  `p_uuid` varchar(60) NOT NULL,
  `user_name` varchar(100) NOT NULL,
  `comment` varchar(100) NOT NULL,
  `event_type` int(11) default '1',
  PRIMARY KEY  (`log_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=114 ;

--
-- RELATIONS FOR TABLE `password_event_log`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `password_event_log`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_deceased`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_deceased` (
  `deceased_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `details` text,
  `date_of_death` date default NULL,
  `location` varchar(20) default NULL,
  `place_of_death` text,
  `comments` text,
  PRIMARY KEY  (`deceased_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- RELATIONS FOR TABLE `person_deceased`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_deceased`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_details`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_details` (
  `details_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `next_kin_uuid` varchar(60) default NULL,
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
  PRIMARY KEY  (`details_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=261 ;

--
-- RELATIONS FOR TABLE `person_details`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_details`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_followers`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_followers` (
  `id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `follower_p_uuid` varchar(60) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `p_uuid` (`p_uuid`),
  KEY `follower_p_uuid` (`follower_p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=7 ;

--
-- RELATIONS FOR TABLE `person_followers`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--   `follower_p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_followers`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_missing`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_missing` (
  `missing_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `last_seen` text,
  `last_clothing` text,
  `comments` text,
  PRIMARY KEY  (`missing_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=92 ;

--
-- RELATIONS FOR TABLE `person_missing`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_missing`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_notes`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_notes` (
  `note_id` int(11) NOT NULL auto_increment,
  `note_about_p_uuid` varchar(60) NOT NULL,
  `note_written_by_p_uuid` varchar(60) NOT NULL,
  `note` varchar(1024) NOT NULL,
  `when` timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (`note_id`),
  KEY `note_about_p_uuid` (`note_about_p_uuid`),
  KEY `note_written_by_p_uuid` (`note_written_by_p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;

--
-- RELATIONS FOR TABLE `person_notes`:
--   `note_about_p_uuid`
--       `person_uuid` -> `p_uuid`
--   `note_written_by_p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_notes`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_physical`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_physical` (
  `physical_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `opt_blood_type` varchar(10) default NULL,
  `height` varchar(10) default NULL,
  `weight` varchar(10) default NULL,
  `opt_eye_color` varchar(50) default NULL,
  `opt_skin_color` varchar(50) default NULL,
  `opt_hair_color` varchar(50) default NULL,
  `injuries` text,
  `comments` text,
  PRIMARY KEY  (`physical_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=75 ;

--
-- RELATIONS FOR TABLE `person_physical`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_physical`
--


-- --------------------------------------------------------

--
-- Stand-in structure for view `person_search`
--
CREATE TABLE `person_search` (
`p_uuid` varchar(60)
,`full_name` varchar(100)
,`given_name` varchar(50)
,`family_name` varchar(50)
,`opt_status` varchar(3)
,`updated` timestamp
,`opt_gender` varchar(10)
,`years_old` int(7)
,`image_height` int(11)
,`image_width` int(11)
,`url_thumb` varchar(512)
,`comments` text
,`last_seen` text
,`icon_url` varchar(128)
,`shortname` varchar(16)
,`hospital` varchar(30)
);
-- --------------------------------------------------------

--
-- Table structure for table `person_seq`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_seq` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `person_seq`
--

INSERT INTO `person_seq` (`id`) VALUES
(10288);

-- --------------------------------------------------------

--
-- Table structure for table `person_status`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_status` (
  `status_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `isReliefWorker` tinyint(4) default NULL,
  `opt_status` varchar(3) default NULL,
  `updated` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `isvictim` tinyint(1) default '1',
  `updated_server` timestamp NULL default NULL,
  PRIMARY KEY  (`status_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=260 ;

--
-- RELATIONS FOR TABLE `person_status`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_status`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_to_hospital`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_to_hospital` (
  `id` int(16) NOT NULL auto_increment,
  `hospital_uuid` int(32) NOT NULL,
  `p_uuid` varchar(60) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `hospital_uuid` (`hospital_uuid`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=161 ;

--
-- RELATIONS FOR TABLE `person_to_hospital`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--   `hospital_uuid`
--       `hospital` -> `hospital_uuid`
--

--
-- Dumping data for table `person_to_hospital`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_to_report`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_to_report` (
  `p_uuid` varchar(60) NOT NULL,
  `rep_uuid` varchar(60) NOT NULL,
  `relation` varchar(100) default NULL,
  PRIMARY KEY  (`p_uuid`,`rep_uuid`),
  KEY `p_uuid` (`p_uuid`,`rep_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `person_to_report`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_to_report`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_updates`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_updates` (
  `update_index` int(32) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `update_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `updated_table` varchar(64) NOT NULL,
  `updated_column` varchar(64) NOT NULL,
  `old_value` varchar(512) NOT NULL,
  `new_value` varchar(512) NOT NULL,
  `updated_by_p_uuid` varchar(60) NOT NULL,
  PRIMARY KEY  (`update_index`),
  KEY `p_uuid` (`p_uuid`),
  KEY `updated_by_p_uuid` (`updated_by_p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=139 ;

--
-- RELATIONS FOR TABLE `person_updates`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--   `updated_by_p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `person_updates`
--


-- --------------------------------------------------------

--
-- Table structure for table `person_uuid`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `person_uuid` (
  `p_uuid` varchar(60) NOT NULL,
  `full_name` varchar(100) default NULL,
  `family_name` varchar(50) default NULL,
  `l10n_name` varchar(100) default NULL,
  `custom_name` varchar(50) default NULL,
  `given_name` varchar(50) default NULL,
  PRIMARY KEY  (`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `person_uuid`
--

INSERT INTO `person_uuid` (`p_uuid`, `full_name`, `family_name`, `l10n_name`, `custom_name`, `given_name`) VALUES
('1', 'Root Admin', 'Admin', NULL, NULL, 'Root');

-- --------------------------------------------------------

--
-- Table structure for table `pfif_export_log`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `pfif_export_log` (
  `log_index` int(11) NOT NULL auto_increment,
  `repository_id` int(11) default '0',
  `status` varchar(10) NOT NULL,
  `start_mode` varchar(6) NOT NULL,
  `start_time` datetime default NULL,
  `end_time` datetime default NULL,
  `first_entry` datetime NOT NULL,
  `last_entry` datetime NOT NULL,
  `person_count` int(11) NOT NULL,
  `note_count` int(11) NOT NULL,
  PRIMARY KEY  (`log_index`),
  KEY `repository_id` (`repository_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- RELATIONS FOR TABLE `pfif_export_log`:
--   `repository_id`
--       `pfif_repository` -> `id`
--

--
-- Dumping data for table `pfif_export_log`
--


-- --------------------------------------------------------

--
-- Table structure for table `pfif_harvest_log`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `pfif_harvest_log` (
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
  `note_count` int(11) default '0',
  `person_updates` int(11) default '0',
  `images_in` int(11) default '0',
  `images_retried` int(11) default '0',
  `images_failed` int(11) default '0',
  PRIMARY KEY  (`log_index`),
  KEY `repository_id` (`repository_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- RELATIONS FOR TABLE `pfif_harvest_log`:
--   `repository_id`
--       `pfif_repository` -> `id`
--

--
-- Dumping data for table `pfif_harvest_log`
--


-- --------------------------------------------------------

--
-- Table structure for table `pfif_note_seq`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `pfif_note_seq` (
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `pfif_note_seq`
--

INSERT INTO `pfif_note_seq` (`id`) VALUES
(1);

-- --------------------------------------------------------

--
-- Table structure for table `pfif_repository`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `pfif_repository` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(100) NOT NULL,
  `base_url` varchar(512) NOT NULL,
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
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `pfif_repository`
--


-- --------------------------------------------------------

--
-- Table structure for table `pfif_xml`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `pfif_xml` (
  `xml_id` int(11) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `type` varchar(6) NOT NULL default 'person',
  `pfif_version` varchar(3) NOT NULL default '1.2',
  `src_repository_id` int(11) NOT NULL,
  `entry_date` datetime NOT NULL,
  `document` mediumtext NOT NULL,
  PRIMARY KEY  (`xml_id`),
  KEY `src_repository_id` (`src_repository_id`,`p_uuid`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- RELATIONS FOR TABLE `pfif_xml`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `pfif_xml`
--


-- --------------------------------------------------------

--
-- Table structure for table `phonetic_word`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `phonetic_word` (
  `encode1` varchar(50) default NULL,
  `encode2` varchar(50) default NULL,
  `pgl_uuid` varchar(60) default NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `phonetic_word`
--


-- --------------------------------------------------------

--
-- Table structure for table `plus_access_log`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `plus_access_log` (
  `access_id` int(16) NOT NULL auto_increment,
  `api_key` varchar(60) NOT NULL,
  `access_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `application` varchar(32) default NULL,
  `version` varchar(16) default NULL,
  `ip` varchar(16) default NULL,
  `call` varchar(64) default NULL,
  PRIMARY KEY  (`access_id`),
  KEY `api_key` (`api_key`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=16 ;

--
-- Dumping data for table `plus_access_log`
--


-- --------------------------------------------------------

--
-- Table structure for table `plus_report_log`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `plus_report_log` (
  `report_id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `report_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (`report_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- RELATIONS FOR TABLE `plus_report_log`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `plus_report_log`
--


-- --------------------------------------------------------

--
-- Table structure for table `pop_outlog`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=108 ;

--
-- Dumping data for table `pop_outlog`
--


-- --------------------------------------------------------

--
-- Table structure for table `rap_log`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `rap_log` (
  `rap_id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `report_time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (`rap_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=58 ;

--
-- RELATIONS FOR TABLE `rap_log`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `rap_log`
--


-- --------------------------------------------------------

--
-- Table structure for table `reg`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `reg` (
  `index` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `domain` varchar(200) NOT NULL,
  `API_KEY` varchar(60) NOT NULL,
  `PASSWORD` varchar(60) NOT NULL,
  `SECRET_CODE` varchar(60) NOT NULL,
  `EMAIL_ADDRESS` varchar(255) NOT NULL,
  `FULL_NAME` varchar(255) NOT NULL,
  `last_attempt` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `is_active` int(8) NOT NULL default '0',
  `confirmation_code` varchar(255) NOT NULL,
  PRIMARY KEY  (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- Dumping data for table `reg`
--


-- --------------------------------------------------------

--
-- Table structure for table `resource_to_incident`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `resource_to_incident` (
  `incident_id` bigint(20) NOT NULL,
  `x_uuid` varchar(60) NOT NULL default '',
  PRIMARY KEY  (`incident_id`,`x_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `resource_to_incident`
--


-- --------------------------------------------------------

--
-- Table structure for table `rez_pages`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

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
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=36 ;

--
-- Dumping data for table `rez_pages`
--

INSERT INTO `rez_pages` (`rez_page_id`, `rez_menu_title`, `rez_page_title`, `rez_menu_order`, `rez_content`, `rez_description`, `rez_timestamp`, `rez_visibility`) VALUES
(-51, 'TriagePic Release Notes', 'TriagePic Release Notes', -51, '<script type="text/javascript" src="res/js/jquery-1.4.4.min.js"></script>\n<script type="text/javascript" src="res/js/animatedcollapse.js"></script>\n<script>\nanimatedcollapse.addDiv(''v116'', ''fade=1,hide=1'');\nanimatedcollapse.addDiv(''v115'', ''fade=1,hide=1'');\nanimatedcollapse.addDiv(''v114'', ''fade=1,hide=1'');\nanimatedcollapse.init();\nanimatedcollapse.ontoggle=function($, divobj, state){}\n</script>\n\n<h2>TriagePic Release Notes</h2>\nFrom January, 2011.  Earlier notes are available off-line.<br><br>\n\n\n<h2>February, 2011</h2>\n<a href="javascript:animatedcollapse.toggle(''v116'')"><h3>Version 1.16 (click to expand)</h3></a>\n<div id="v116" display="none;">\nOverall, this version:\n<ul>\n<li>Fixes two problems when saving email settings and outbox entries.</li>\n<li>Allows local outbox history deletions.</li>\n<li>Aligns disaster event categories better with PL.</li>\n</ul>\n\nSpecifically:<br>\n<ul>\n<li>A recently introduced bug, where email setting changes were not saved, is fixed.</li>\n<li>In the Outbox, the â€œPicâ€ column was earlier converted to counts (instead of Y/N), but this conversion wasnâ€™t getting saved in the outbox.xml file except for new entries.  Now it is.</li>\n<li>Version 1.16 allows the user to go into the Outbox and delete one or more individual items from the outbox history.  These are local deletes for now - they are not reported to the central LPF database.</li>\n<li>There are two ways to delete a particular selected Outbox row:  hit the â€œDeleteâ€ key (or DEL or Backspace) or open the Outbox Details window and hit the new â€œDeleteâ€ button.  The first method also allows multiple rows to be selected and deleted.  To facilitate this functionality, a single click on an Outbox row now selects it, instead of opening Outbox Details (which now takes a double click).</li>\n<li>A delete is persisted by changing the contents of outbox.xml.  The contents removed from outbox.xml is moved to a separate file under the â€œdeletedâ€ directory, e.g., â€œ911-1234 Green [from outbox].xmlâ€.  Also moved are the associated *.lpf, *.pfif, and *.jpg files.</li>\n<li>Deletion of one or more rows normally concludes with a dialog box saying:</li>\n"Deleted patient data moved to the C:/Shared TriagePic Data/deleted/ folder:"<br>\nfollowed by, for each deleted row, patient number, zone, and number of deleted files, e.g.:<br>\n"2045 Green (4 files)"<br>\nAll the filenames will begin, in this case, with â€œ2045 Greenâ€¦â€ . There are typically 4 files, consisting of an outbox fragment .xml, an .lpf file, a .pfif file, and one .jpg file.  If problems arise during the deletion process, additional error dialog boxes may precede the normal one.<br>\n<li>Specifically, when deleting a row, possible error messages are:</li>\n<ol>\n<li>"Could not open file C:/Shared TriagePic Data/sent/<some file="">"</some></li>\n<li>For .lpf and .pfif attachments:</li>\n"More than 1 file was found with the pattern C:/Shared TriagePic Data/sent/*.{some extension}<br>\nAll will be moved to the folder C:/Shared TriagePic Data/deleted/."<br>\n<li>"It was planned to delete the file C:/Shared TriagePic Data/sent/{somefile.ext}<br>\nby moving it to the archive C:/Shared TriagePic Data/deleted/,<br>\nbut a file of that name already exists there, which was renamed to <somefile (1).ext="">"</somefile></li>\n<li>"There were no files to delete."  This might occur after an abnormal termination due to crash or debugging.</li>\n</ol>\n<li>If deleting the last row from history, a dummy blank row is automatically inserted into outbox.xml.  This prevents problems later.  The first real data replaces that row.</li>\n<li>TriagePic previously had a 3-way categorization of events:  â€œTEST or DEMOâ€, â€œDRILLâ€, or â€œREAL â€“ NOT A DRILLâ€.  In the first category, a default instance was â€œUnnamed TEST or DEMOâ€.  PL has adopted a 2-way categorization:  â€œTESTâ€ or â€œREALâ€, which it is exposing through the web service (and cached by TriagePic); the default instance is â€œTest Eventâ€.  To align closer to PL, the TriagePic UI is now showing the two categories â€œTEST/DEMO/DRILLâ€ and â€œREAL â€“ NOT A DRILLâ€.  Additionl cleanups to support this re-categorization are discussed next.</li>\n<li>If it is necessary to distinguish between a test and a drill (for instance, in filling out EDXL headers for the .lpf files), the mapping will be that â€œTest Eventâ€ is considered a test and all other events of PL type TEST are considered a drill.</li>\n<li>Historical outbox entries where Event = â€œUnnamed TEST or DEMOâ€ are changed to Event = â€œTest Eventâ€.  This (and correction of related bugs) will allow the stat boxes for Current Event to show useful results when the current event for TriagePic is Test Event.</li>\n<li>If the cached event list includes event â€œnew eventâ€, which PL once exposed, it is deleted.</li>\n</ul>\n</div>\n\n\n<h2>January, 2011</h2>\n<a href="javascript:animatedcollapse.toggle(''v115'')"><h3>Version 1.15 (click to expand)</h3></a>\n<div id="v115" display="none;">\n<ul>\n<li>Version 1.15 fixes several problems with the newly introduced EmailSettings.xml file.  (And for those who upgraded to v 1.14 and had problems, a workaround replacement EmailSettings.xml file was distributed.)\n</li><li>If migrating from TriagePic v 1.13 or earlier, email settings previously in SharedTriagePic.xml now migrate correctly to EmailSettings.xml.  In 1.14, only the default (new-install) contents for EmailSettings.xml appear.\n</li><li>Related to that, if â€œNLM (Testing)â€ was in the profile in use (rather than Generic, Suburban Hospital, or NNMC), the default contents of the EmailSettings.xml file was incorrect (e.g., first line begins as "<options â€¦â€="" instead="" of="" â€œ=""><emailsettings â€¦â€)=""></emailsettings></options></li>\n<li>The preceding problem caused the app to silently quit during startup, right after the â€œCould not connect to web serviceâ€¦â€ dialog.  Changed to be noisy, identifying the bad xml file.  Similar noisy reads are also now done for HospitalSettings.xml, OtherSettings.xml, and UsersAndVersions.xml.</li>\n</ul>\n</div>\n\n<a href="javascript:animatedcollapse.toggle(''v114'')"><h3>Version 1.14 (click to expand)</h3></a>\n<div id="v114" display="none;">\nOverall, this version\n<ul>\n<li>improves the Outbox, the listing of sent items, particularly the information shown when clicking on a particular entry and seeing the dialog box now called â€œOutbox Detailsâ€.</li>\n<li>has some preliminary work on deletion capabilities (most of which is not exposed in this release).</li>\n</ul>\n\nSpecifically:\n<ul>\n<li>The Outbox â€œSentâ€ column before always showed â€œYâ€, whether the email send was successful or not.  It now should show â€œNâ€ if email send was not 100% successful to all recipients.  (Error cases have not been extensively tested.)  In code, the function myEmail.MySendMail now returns a Boolean value to indicate success, the two values of which (for anonymized and regular sends) determine the Outbox â€œSentâ€ value.  To achieve that, the function body, particularly inside the catch handlers, has been moderately modified.</li>\n<li>The Outbox listing of sent items now includes nicknames/aliases in the â€œFirstâ€ name column, and avoids trailing spaces in the â€œFirstâ€ and â€œLastâ€ columns.  The format is now:</li>\n&nbsp;&nbsp;&nbsp;First: William "Bill" A.<br>\n&nbsp;&nbsp;&nbsp;Last: Stockton Jr.<br>\n<li>The title bar of Outbox Details now includes the form name and an alias if present, and handles a missing patient name specially. Two examples:</li>\n&nbsp;&nbsp;&nbsp;Outbox Details - [No Patient Name Given]<br>\n&nbsp;&nbsp;&nbsp;Outbox Details - William "Bill" A. Stockton Jr.<br>\n<li>Outbox Details is larger.  It now reveals both left and right filmstrip controls.  A new read-only area in the lower-left shows details of the selected record.  This is largely the same information thatâ€™s in the selected Outbox data row.  Since the Outbox data row items are sometimes truncated or scrolled from visibility, this gives a more complete picture at a glance.  Minor differences from Outbox, seen in Outbox Details, are:\n</li><li>The â€œwhen sentâ€ timestamp is in a different format which includes the year, and shows the month as a number.  (There is a separate alternative-format timestamp field that could be shown, but we chose not to.)</li>\n<li>The count of pictures is not needed, given that you can see them.</li>\n<li>The read-only role (primary or secondary) &amp; optional caption for a selected photo is shown.  By default, the primary photo is selected when Outbox Details opens.  The selection can be changed just as under the Main Info tab.\n</li><li>When opening an Outbox Details, you may get the warning message:<br>\n"There is a mismatch between the ''Pic'' count and the number of images found in the folder<br>\nC:\\TriagePicSharedData\\sent<br>\nIf you just sent this email, wait a few seconds for background processing to complete and try again."</li>\n<li>On startup, new folder C:/TriagePic Shared Data/deleted is created if not present.</li>\n<li>The form, class, and .cs file â€œFormSentImagesâ€ has been renamed to â€œFormOutboxDetailsâ€.</li>\n<li>For version 1.13, an â€œAboutâ€ entry is added to the System menu (upper left hand corner).  â€œAboutâ€ content  design is very much like the splash screen, but slightly bigger, with title bar, OK button, and mention of the LPF project.  The wordings on the splash screen and main title bar were slightly revised.\n</li><li>During startup, a missing outbox.xml file is always checked for, not just when a new â€œoutbox queueâ€ directory is created.  If missing, a file defining an empty queue is substituted.</li>\n<li>The file TriagePicSharedSettings.xml is split into 3 files:  EmailSettings.xml, HospitalSettings.xml, and OtherSettings.xml.  Internally, new I/O classes are created for them.  Startup code is added to do migration from the old to new structure, and to use the new structure for fresh installs (with Generic, NLM, NNMC, Suburban internal file resources).  For existing installs, after migration, the old settings file is retained but renamed TriagePicSharedSettings[obsolete].xml.\n</li><li>The PatientID format setting is now retained, specifically in the HospitalSettings.xml file.  The representation is the fixed number of digits (not counting alphanumeric prefix); a variable number of digits is represented by -1.  For new installs, the default patient ID format for Suburban and NNMC is â€œfixed 4 digitâ€; for NLM and Generic, itâ€™s â€œvariableâ€ format.\n</li><li>Under â€œHospitalâ€ tab, the leftover subheading â€œPolicies and Other Settingsâ€ was removedâ€¦ (See the separate â€œPoliciesâ€ tab instead, created in a prior version.)\n</li><li>Edits to any field under the â€œHospitalâ€ tab now takes effect immediately, not just when TriagePic exits.  Likewise the Patient Prefix on the â€œPoliciesâ€ tab.\n</li><li>For programmers, the TriagePic VS project now contains a set of Class Diagrams.</li></ul>\n</div>', 'TriagePic Release Notes', '2011-02-04 16:34:24', 'External Page'),
(-50, 'TriagePic Overview', 'TriagePic Overview', -50, '<h2>Overview</h2>\r\n<br>\r\nTriagePic, a hospital-based Windows application, helps quickly gather photos and minimal information about disaster victims arriving at a perimeter triage station, particularly to assist with family reunification.  Photos can be gathered using a webcam or paired Bluetooth camera.  TriagePic can be used with a hospital''s preprinted triage forms, auto-incrementing mass casualty ID numbers.   As each patient is routed to a color-coded zone for treatment, information about that patient is emailed to designated recipients, such as hospital reunification counselors and emergency managers.  If set up as intended, the information is also sent to and read in by this web site.', 'TriagePic Overview', '2011-02-02 20:21:35', 'External Page'),
(-20, 'Error #20', 'Error #20', -20, 'You do not have permission to access this event. If you believe this is in error, please contact lpfsupport@mail.nih.gov', 'Error #20', '2011-01-10 19:11:39', 'Hidden'),
(-6, 'Password Change Successful', 'Password Change Successful', 11, '<div><br></div><div>Your password has been changed and the new password emailed to you. Please use it for future logins.</div>', 'Password Change Successful', '2010-09-29 11:55:51', 'Hidden'),
(-5, 'Password Change Unsuccessful', 'Password Change Unsuccessful', 7, '<div><br></div><div>Your attempted password change was unsuccessful. It appears you used an invalid confirmation code.</div>', 'Password Change Unsuccessful', '2010-09-29 11:56:09', 'Hidden'),
(-4, 'Account Already Active', 'Account Already Active', 6, '<div><br></div><div>This confirmation link is no longer valid. The account attached to it is already active.</div>', 'Account Already Active', '2010-09-29 11:56:06', 'Hidden'),
(-3, 'Registration Unsuccessful', 'Registration Unsuccessful', 5, '<div><br></div><div>Your attempted registration confirmation was unsuccessful. It appears you attempted to confirm an invalid user. Please re-initiate the registration process from your device to try again.</div>', 'Registration Unsuccessful', '2010-09-29 11:56:05', 'Hidden'),
(-2, 'Registration Unsuccessful', 'Registration Unsuccessful', 2, '<div><br></div><div>Your attempted registration confirmation was unsuccessful. It appears you attempted to confirm a user with an invalid confirmation code. Please re-initiate the registration process from your device to try again.</div>', 'Registration Unsuccessful', '2010-09-29 11:56:04', 'Hidden'),
(-1, 'Registration Successful', 'Registration Successful', 1, '<div><br></div><div>Thank you for confirming your registration.&nbsp;</div><div><br></div><div>The device you registered can now utilize the Person Locator web services. (ie. Searching for and Reporting Persons on ReUnite)</div><div><br></div><div><meta http-equiv="content-type" content="text/html; charset=utf-8"><div>Additionally, your user account is now active and you may log into this site with the login/password that was supplied in the email you received. After logging in, you may change your password by going to User Preferences and navigating to "Change Password".</div></div><div><br></div>', 'Registration Successful', '2010-07-15 15:00:07', 'Hidden'),
(11, 'How do I search for a person?', 'How do I search for a person?', 14, '<h2>Searching</h2>\n1) Enter a name in the search box<br>\n2) Click on the "Search" button, or hit Enter <br>\n<br>\n<i>Examples:</i><br>\n<br>\n Joseph Doe<br>\n Doe, Jane<br>\n Joseph Joe Joey<br>\n<br>\nIt is best to leave off titles (â€œDr.â€, â€œMrs.â€) and suffixes (â€œJrâ€) at this time.<br>\n<br>\n<br>\n<h2>Search Options</h2>\nYou may also specify status, gender, and age to limit your search results.  The default is to search all options.  To access search options, click on the "+ More Options" link.<br>\n<br>\nStatus choices are missing (blue), alive and well (green), injured (red), deceased (black), or unknown (gray)<br>\n<br>\nGender choices are male, female, and other/unknown.<br>\n<br>\nAge choices are 0-17, 18+, or unknown.<br>\n<br>\n<br>\n<h2>Results</h2>\nResults include any of the search terms.<br>\n<br>\nUnder the search box is the number of records found that match your search, and the total number in the database (eg, Found 2 out of 43).<br>\n<br>\nYou may sort your results by Time, Name, Age, or Status.<br>\n<br>\nInteractive mode displays photos by page.  The default is 25 per page.  You may change it to 50 or 100 per page via the pull down menu at the top of the results.<br>\n<br>\nHands Free mode displays photos as three as three scrolling rows of photographs.  The photos always distribute themselves evenly among the rows, starting at the right side and from top row to bottom.  If there are more images than can be shown at once, the rows will become animated to scroll horizontally with wrap-around.  There is no meaning to the ordering of the images at this time.<br>\n<br>\n<br>\n<h2>Getting Details about a Given Photo</h2>\nClick on the photo for more information.<br>\n<br>\n<br>\n<h2>Pause and Play Buttons</h2>\nIf horizontal scrolling is occurring, Pause will stop that, and Play will resume it.  Even while paused, the search will be repeated every minute to look for fresh content.<br>\n<br>\n<br>\n<h2>Other Information</h2>\nWhat Information is being Searched, and How Often Is It Updated?<br>\n<br>\nOnce a set of result images for a search is loaded, the search will be quietly repeated every minute to see if there is new content to include.<br>\n<br>\nInformation is being input via TriagePic and records set to us directly by email (e.g., with our iPhone app).<br>\n<br>\n<br>\n<h2>Data Updates</h2>\nOnce a set of result images for a search is loaded, the search will be quietly repeated every minute to see if there is new content.\nInformation is being input via TriagePic and records sent to us directly by email (e.g., with our iPhone app).\n<br>\n<br><br>', 'Instructions for searching on the site', '2010-12-03 20:36:49', 'Public'),
(14, 'Contact us', 'Contact us', 21, '', 'Contact NLM', '2011-02-11 17:22:02', 'Public'),
(15, 'Landing', '', 31, 'This is an organized online bulletin board to aid in locating someone after a disaster.<br><br>\nAnyone may use the search feature, without logging in or registering for an account to search for people. You may also get basic information about someone missing or found, including photos, as reported by family members, friends, or participating local hospitals.<br>\n<br>\n<span class="styleTehButton" style="" onclick="location.href=''index.php?mod=inw&amp;act=default'';">Click Here to Begin Searching for People</span>\n<br>\n<br>\n<br><br>\nTo do more with the site like reporting people, first <a href="index.php?act=signup">create an account</a> and login. Then you can:<br>\n<br>\n<ul>\n	<li>Report someone as missing, and include photographs of them</li>\n	<li>Update that report, e.g., if the person is found or their status changes</li>\n	<li>Share the ability to update a report with family members and friends</li>\n</ul>\n<br>\nParticipating local hospitals can report basic information about arriving disaster victims.&nbsp; (Suburban Hospitalâ€™s implementation is furthest along.)<br>\n<br>\nThe site does no automatic notification at this time, so check back periodically.&nbsp; But hospital personnel may contact you.<br>\n<br>\n', 'Landing', '2011-02-03 18:55:22', 'External Page'),
(24, 'Links', 'Links', 18, '', 'Disaster related links ', '2011-02-11 17:22:26', 'Public'),
(26, 'About Us', 'About Us', 17, '', 'Description of People Locator', '2011-02-11 17:22:42', 'Public'),
(30, 'ABOUT', 'ABOUT', 22, '', 'ABOUT', '2011-02-11 17:22:51', 'External Page');



UPDATE  `rez_pages` SET  `rez_content` =  '<h2>Links</h2>
To update the content of this page, navigate to Administration -> Resources Pages and then click on the edit icon of the page you wish to edit.' WHERE  `rez_pages`.`rez_page_id` = 24;

UPDATE  `rez_pages` SET  `rez_content` =  '<h2>Contact Us</h2>
To update the content of this page, navigate to Administration -> Resources Pages and then click on the edit icon of the page you wish to edit.' WHERE  `rez_pages`.`rez_page_id` = 14;

UPDATE  `rez_pages` SET  `rez_content` =  '<h2>About Us</h2>
To update the content of this page, navigate to Administration -> Resources Pages and then click on the edit icon of the page you wish to edit.' WHERE  `rez_pages`.`rez_page_id` = 26;

UPDATE  `rez_pages` SET  `rez_content` =  '<h2>ABOUT</h2>
To update the content of this page, navigate to Administration -> Resources Pages and then click on the edit icon of the page you wish to edit.' WHERE  `rez_pages`.`rez_page_id` = 30;


-- --------------------------------------------------------

--
-- Table structure for table `sessions`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `sessions` (
  `session_id` varchar(64) NOT NULL,
  `sess_key` varchar(64) NOT NULL,
  `secret` varchar(64) NOT NULL,
  `inactive_expiry` bigint(20) NOT NULL,
  `expiry` bigint(20) NOT NULL,
  `data` text,
  PRIMARY KEY  (`session_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `sessions`
--


-- --------------------------------------------------------

--
-- Table structure for table `sys_data_classifications`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `sys_data_classifications` (
  `level_id` int(11) NOT NULL,
  `level` varchar(60) NOT NULL,
  PRIMARY KEY  (`level_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `sys_data_classifications`
--

INSERT INTO `sys_data_classifications` (`level_id`, `level`) VALUES
(1, 'Person Sensitive'),
(2, 'Organization Sensitive'),
(3, 'Legally Sensitive'),
(4, 'National Security Sensitive'),
(5, 'Socially Sensitive'),
(6, 'System Sensitive'),
(7, 'Not Sensitive'),
(8, 'Unclassified');

-- --------------------------------------------------------

--
-- Table structure for table `sys_group_to_data_classification`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `sys_group_to_data_classification` (
  `group_id` int(11) NOT NULL,
  `level_id` int(11) NOT NULL,
  `crud` varchar(4) NOT NULL,
  PRIMARY KEY  (`group_id`,`level_id`),
  KEY `level_id` (`level_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `sys_group_to_data_classification`
--

INSERT INTO `sys_group_to_data_classification` (`group_id`, `level_id`, `crud`) VALUES
(1, 1, 'crud'),
(1, 2, 'crud'),
(1, 3, 'crud'),
(1, 4, 'crud'),
(1, 5, 'crud'),
(1, 6, 'crud'),
(1, 7, 'crud'),
(1, 8, 'crud'),
(2, 1, 'crud'),
(2, 2, 'crud'),
(2, 3, 'crud'),
(2, 4, 'crud'),
(2, 5, 'crud'),
(2, 6, 'crud'),
(2, 7, 'crud'),
(2, 8, 'crud'),
(3, 1, 'crud'),
(3, 2, 'crud'),
(3, 3, 'crud'),
(3, 4, 'crud'),
(3, 5, 'crud'),
(3, 6, 'crud'),
(3, 7, 'crud'),
(3, 8, 'crud'),
(4, 1, 'crud'),
(4, 2, 'crud'),
(4, 3, 'crud'),
(4, 4, 'crud'),
(4, 5, 'crud'),
(4, 6, 'crud'),
(4, 7, 'crud'),
(4, 8, 'crud'),
(5, 1, 'crud'),
(5, 2, 'crud'),
(5, 3, 'crud'),
(5, 4, 'crud'),
(5, 5, 'crud'),
(5, 6, 'crud'),
(5, 7, 'crud'),
(5, 8, 'crud'),
(6, 1, 'crud'),
(6, 2, 'crud'),
(6, 3, 'crud'),
(6, 4, 'crud'),
(6, 5, 'crud'),
(6, 6, 'crud'),
(6, 7, 'crud'),
(6, 8, 'crud'),
(7, 1, 'crud'),
(7, 2, 'crud'),
(7, 3, 'crud'),
(7, 4, 'crud'),
(7, 5, 'crud'),
(7, 6, 'crud'),
(7, 7, 'crud'),
(7, 8, 'crud'),
(8, 1, 'crud'),
(8, 2, 'crud'),
(8, 3, 'crud'),
(8, 4, 'crud'),
(8, 5, 'crud'),
(8, 6, 'crud'),
(8, 7, 'crud'),
(8, 8, 'crud');

-- --------------------------------------------------------

--
-- Table structure for table `sys_group_to_module`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `sys_group_to_module` (
  `group_id` int(11) NOT NULL,
  `module` varchar(60) NOT NULL,
  `status` varchar(60) NOT NULL,
  PRIMARY KEY  (`group_id`,`module`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `sys_group_to_module`
--

INSERT INTO `sys_group_to_module` (`group_id`, `module`, `status`) VALUES
(1, 'admin', 'enabled'),
(1, 'cam', 'enabled'),
(1, 'dap', 'enabled'),
(1, 'eap', 'enabled'),
(1, 'em', 'enabled'),
(1, 'ha', 'enabled'),
(1, 'inw', 'enabled'),
(1, 'plus', 'enabled'),
(1, 'pop', 'enabled'),
(1, 'pref', 'enabled'),
(1, 'rap', 'enabled'),
(1, 'reg', 'enabled'),
(1, 'rez', 'enabled'),
(1, 'tp', 'enabled'),
(1, 'xst', 'enabled'),
(2, 'eap', 'enabled'),
(2, 'inw', 'enabled'),
(2, 'plus', 'enabled'),
(2, 'pref', 'enabled'),
(2, 'rap', 'enabled'),
(2, 'rez', 'enabled'),
(2, 'xst', 'enabled'),
(3, 'eap', 'enabled'),
(3, 'inw', 'enabled'),
(3, 'rap', 'enabled'),
(3, 'rez', 'enabled'),
(3, 'xst', 'enabled'),
(5, 'eap', 'enabled'),
(5, 'inw', 'enabled'),
(5, 'plus', 'enabled'),
(5, 'pref', 'enabled'),
(5, 'rap', 'enabled'),
(5, 'rez', 'enabled'),
(5, 'tp', 'enabled'),
(5, 'xst', 'enabled'),
(6, 'dap', 'enabled'),
(6, 'eap', 'enabled'),
(6, 'em', 'enabled'),
(6, 'ha', 'enabled'),
(6, 'inw', 'enabled'),
(6, 'plus', 'enabled'),
(6, 'pref', 'enabled'),
(6, 'rap', 'enabled'),
(6, 'rez', 'enabled'),
(6, 'tp', 'enabled'),
(6, 'xst', 'enabled'),
(7, 'eap', 'enabled'),
(7, 'plus', 'enabled');

-- --------------------------------------------------------

--
-- Table structure for table `sys_tablefields_to_data_classification`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `sys_tablefields_to_data_classification` (
  `table_field` varchar(50) NOT NULL,
  `level_id` int(11) NOT NULL,
  PRIMARY KEY  (`table_field`,`level_id`),
  KEY `level_id` (`level_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `sys_tablefields_to_data_classification`
--

INSERT INTO `sys_tablefields_to_data_classification` (`table_field`, `level_id`) VALUES
('group_details', 1),
('identity_to_person', 1),
('person_deceased', 1),
('person_details', 1),
('person_missing', 1),
('person_physical', 1),
('person_status', 1),
('person_to_pgroup', 1),
('person_to_report', 1),
('person_uuid', 1),
('pgroup', 1),
('org_main', 2),
('sector', 2),
('camp_reg', 5),
('contact', 5),
('location_details', 5),
('audit', 6),
('chronology', 6),
('config', 6),
('ct_catalogue', 6),
('field_options', 6),
('image', 6),
('ims_alternate', 6),
('ims_inventory_records', 6),
('ims_item_records', 6),
('ims_relation', 6),
('ims_reorder_level', 6),
('ims_transfer_item', 6),
('lc_fields', 6),
('lc_tmp_po', 6),
('resource_to_incident', 6),
('rms_fulfil', 6),
('rms_pledge', 6),
('rms_plg_item', 6),
('rms_priority', 6),
('rms_request', 6),
('rms_req_item', 6),
('rms_status', 6),
('sessions', 6),
('sync_instance', 6),
('sys_data_classifications', 6),
('sys_group_to_data_classification', 6),
('sys_tablefields_to_data_classification', 6),
('sys_user_groups', 6),
('sys_user_to_group', 6),
('users', 6),
('camp_services', 7),
('ct_cat_unit', 7),
('ct_unit', 7),
('ct_unit_type', 7),
('ims_optimization', 7),
('incident', 7),
('location', 7),
('rms_tmp_sch', 8);

-- --------------------------------------------------------

--
-- Table structure for table `sys_user_groups`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `sys_user_groups` (
  `group_id` int(11) NOT NULL,
  `group_name` varchar(40) NOT NULL,
  PRIMARY KEY  (`group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `sys_user_groups`
--

INSERT INTO `sys_user_groups` (`group_id`, `group_name`) VALUES
(1, 'Administrator'),
(2, 'Registered User'),
(3, 'Anonymous User'),
(5, 'Hospital Staff'),
(6, 'Hospital Staff Admin'),
(7, 'Researchers');

-- --------------------------------------------------------

--
-- Table structure for table `sys_user_to_group`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `sys_user_to_group` (
  `group_id` int(11) NOT NULL,
  `p_uuid` varchar(60) NOT NULL,
  KEY `p_uuid` (`p_uuid`),
  KEY `group_id` (`group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `sys_user_to_group`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--   `group_id`
--       `sys_user_groups` -> `group_id`
--

--
-- Dumping data for table `sys_user_to_group`
--

INSERT INTO `sys_user_to_group` (`group_id`, `p_uuid`) VALUES
(1, '1');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `users` (
  `user_id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `user_name` varchar(100) NOT NULL,
  `password` varchar(128) default NULL,
  `salt` varchar(100) default NULL,
  `changed_timestamp` bigint(20) NOT NULL,
  `status` varchar(60) default 'active',
  `confirmation` varchar(255) default NULL,
  PRIMARY KEY  (`user_id`),
  UNIQUE KEY `user_name` (`user_name`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=48 ;

--
-- RELATIONS FOR TABLE `users`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`user_id`, `p_uuid`, `user_name`, `password`, `salt`, `changed_timestamp`, `status`, `confirmation`) VALUES
(1, '1', 'root', 'c78cd6254de60e91a402f733d12a0c3f', 'e5cb9f3624f2d81964', 1297450104, '', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `user_preference`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `user_preference` (
  `pref_id` int(16) NOT NULL auto_increment,
  `p_uuid` varchar(60) NOT NULL,
  `module_id` varchar(20) NOT NULL,
  `pref_key` varchar(60) NOT NULL,
  `value` varchar(100) default NULL,
  PRIMARY KEY  (`pref_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- RELATIONS FOR TABLE `user_preference`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `user_preference`
--


-- --------------------------------------------------------

--
-- Table structure for table `voice_note`
--
-- Creation: Feb 11, 2011 at 01:20 PM
--

CREATE TABLE `voice_note` (
  `voicenote_id` bigint(20) NOT NULL auto_increment,
  `p_uuid` varchar(60) default NULL,
  `original_filename` varchar(255) default NULL,
  `data` mediumblob,
  `length` double default NULL,
  `format` varchar(16) default NULL,
  `sample_rate` int(8) default NULL,
  `channels` int(8) default NULL,
  `speaker` varchar(16) default NULL,
  `url` varchar(255) default NULL,
  PRIMARY KEY  (`voicenote_id`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

--
-- RELATIONS FOR TABLE `voice_note`:
--   `p_uuid`
--       `person_uuid` -> `p_uuid`
--

--
-- Dumping data for table `voice_note`
--


-- --------------------------------------------------------

--
-- Structure for view `person_search`
--
DROP TABLE IF EXISTS `person_search`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `person_search` AS select distinct `a`.`p_uuid` AS `p_uuid`,`a`.`full_name` AS `full_name`,`a`.`given_name` AS `given_name`,`a`.`family_name` AS `family_name`,`b`.`opt_status` AS `opt_status`,`b`.`updated` AS `updated`,`c`.`opt_gender` AS `opt_gender`,`c`.`years_old` AS `years_old`,`i`.`image_height` AS `image_height`,`i`.`image_width` AS `image_width`,`i`.`url_thumb` AS `url_thumb`,`e`.`comments` AS `comments`,`e`.`last_seen` AS `last_seen`,(case when (`h`.`hospital_uuid` = -(1)) then NULL else `h`.`icon_url` end) AS `icon_url`,`inc`.`shortname` AS `shortname`,`h`.`short_name` AS `hospital` from ((((((((`person_uuid` `a` join `person_status` `b` on((`a`.`p_uuid` = `b`.`p_uuid`))) left join `image` `i` on((`a`.`p_uuid` = `i`.`x_uuid`))) join `person_details` `c` on((`a`.`p_uuid` = `c`.`p_uuid`))) left join `person_missing` `e` on((`a`.`p_uuid` = `e`.`p_uuid`))) join `resource_to_incident` `rti` on((`a`.`p_uuid` = `rti`.`x_uuid`))) join `incident` `inc` on((`inc`.`incident_id` = `rti`.`incident_id`))) left join `person_to_hospital` `pth` on((`a`.`p_uuid` = `pth`.`p_uuid`))) left join `hospital` `h` on((`pth`.`hospital_uuid` = `h`.`hospital_uuid`))) where (((1 = 0) or (`b`.`opt_status` = _utf8'mis') or (`b`.`opt_status` = _utf8'ali') or (`b`.`opt_status` = _utf8'inj') or (`b`.`opt_status` = _utf8'dec') or (`b`.`opt_status` = _utf8'unk') or isnull(`b`.`opt_status`)) and ((1 = 0) or (`c`.`opt_gender` = _utf8'mal') or (`c`.`opt_gender` = _utf8'fml') or ((`c`.`opt_gender` <> _utf8'mal') and (`c`.`opt_gender` <> _utf8'fml')) or isnull(`c`.`opt_gender`)) and ((1 = 0) or (cast(`c`.`years_old` as unsigned) < 18) or (cast(`c`.`years_old` as unsigned) >= 18) or isnull(cast(`c`.`years_old` as unsigned))) and ((1 = 0) or (`h`.`short_name` = _utf8'sh') or (`h`.`short_name` = _utf8'nnmc') or ((`h`.`short_name` <> _utf8'sh') and (`h`.`short_name` <> _utf8'nnmc')) or isnull(`h`.`short_name`)) and (`b`.`isvictim` = _utf8'1')) group by `a`.`p_uuid`;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `image_tag`
--
ALTER TABLE `image_tag`
  ADD CONSTRAINT `image_tag_ibfk_1` FOREIGN KEY (`image_id`) REFERENCES `image` (`image_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `mpres_log`
--
ALTER TABLE `mpres_log`
  ADD CONSTRAINT `mpres_log_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `password_event_log`
--
ALTER TABLE `password_event_log`
  ADD CONSTRAINT `password_event_log_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_deceased`
--
ALTER TABLE `person_deceased`
  ADD CONSTRAINT `person_deceased_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_details`
--
ALTER TABLE `person_details`
  ADD CONSTRAINT `person_details_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_followers`
--
ALTER TABLE `person_followers`
  ADD CONSTRAINT `person_followers_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `person_followers_ibfk_2` FOREIGN KEY (`follower_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_missing`
--
ALTER TABLE `person_missing`
  ADD CONSTRAINT `person_missing_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_notes`
--
ALTER TABLE `person_notes`
  ADD CONSTRAINT `person_notes_ibfk_1` FOREIGN KEY (`note_about_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `person_notes_ibfk_2` FOREIGN KEY (`note_written_by_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_physical`
--
ALTER TABLE `person_physical`
  ADD CONSTRAINT `person_physical_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_status`
--
ALTER TABLE `person_status`
  ADD CONSTRAINT `person_status_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_to_hospital`
--
ALTER TABLE `person_to_hospital`
  ADD CONSTRAINT `person_to_hospital_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `person_to_hospital_ibfk_2` FOREIGN KEY (`hospital_uuid`) REFERENCES `hospital` (`hospital_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_to_report`
--
ALTER TABLE `person_to_report`
  ADD CONSTRAINT `person_to_report_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `person_updates`
--
ALTER TABLE `person_updates`
  ADD CONSTRAINT `person_updates_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `person_updates_ibfk_2` FOREIGN KEY (`updated_by_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `pfif_export_log`
--
ALTER TABLE `pfif_export_log`
  ADD CONSTRAINT `pfif_export_log_ibfk_1` FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `pfif_harvest_log`
--
ALTER TABLE `pfif_harvest_log`
  ADD CONSTRAINT `pfif_harvest_log_ibfk_1` FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `pfif_xml`
--
ALTER TABLE `pfif_xml`
  ADD CONSTRAINT `pfif_xml_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `plus_report_log`
--
ALTER TABLE `plus_report_log`
  ADD CONSTRAINT `plus_report_log_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `rap_log`
--
ALTER TABLE `rap_log`
  ADD CONSTRAINT `rap_log_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `sys_user_to_group`
--
ALTER TABLE `sys_user_to_group`
  ADD CONSTRAINT `sys_user_to_group_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `sys_user_to_group_ibfk_2` FOREIGN KEY (`group_id`) REFERENCES `sys_user_groups` (`group_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `users`
--
ALTER TABLE `users`
  ADD CONSTRAINT `users_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `user_preference`
--
ALTER TABLE `user_preference`
  ADD CONSTRAINT `user_preference_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `voice_note`
--
ALTER TABLE `voice_note`
  ADD CONSTRAINT `voice_note_ibfk_1` FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE;
