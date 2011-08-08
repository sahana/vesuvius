-- phpMyAdmin SQL Dump
-- version 3.3.8
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Jun 23, 2011 at 04:26 PM
-- Server version: 5.0.91
-- PHP Version: 5.3.6

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;


-- --------------------------------------------------------

--
-- Table structure for table `edxl_co_header`
--
-- Creation: Apr 18, 2011 at 11:08 AM
--

CREATE TABLE `edxl_co_header` (
  `de_id` int(11) NOT NULL,
  `co_id` int(11) NOT NULL,
  `content_descr` varchar(255) default NULL COMMENT 'Content description',
  `incident_id` varchar(255) default NULL,
  `incident_descr` varchar(255) default NULL COMMENT 'Incident description',
  `confidentiality` varchar(255) default NULL,
  PRIMARY KEY  (`co_id`),
  UNIQUE KEY `de_id` (`de_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_co_header`:
--   `de_id`
--       `edxl_de_header` -> `de_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_co_keywords`
--
-- Creation: Apr 15, 2011 at 04:54 PM
--

CREATE TABLE `edxl_co_keywords` (
  `co_id` int(11) NOT NULL,
  `keyword_num` int(11) NOT NULL,
  `keyword_urn` varchar(255) NOT NULL,
  `keyword` varchar(255) NOT NULL,
  PRIMARY KEY  (`co_id`,`keyword_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_co_keywords`:
--   `co_id`
--       `edxl_co_header` -> `co_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_co_lpf`
--
-- Creation: Apr 15, 2011 at 05:23 PM
--

CREATE TABLE `edxl_co_lpf` (
  `co_id` int(11) NOT NULL,
  `p_uuid` varchar(255) NOT NULL COMMENT 'Sahana person ID',
  `schema_version` varchar(255) NOT NULL,
  `login_machine` varchar(255) NOT NULL,
  `login_account` varchar(255) NOT NULL,
  `person_id` varchar(255) NOT NULL COMMENT 'Mass casualty patient ID',
  `event_name` varchar(255) NOT NULL,
  `event_long_name` varchar(255) NOT NULL,
  `org_name` varchar(255) NOT NULL,
  `org_id` varchar(255) NOT NULL,
  `last_name` varchar(255) NOT NULL,
  `first_name` varchar(255) NOT NULL,
  `gender` enum('M','F','U','C') NOT NULL,
  `peds` tinyint(1) NOT NULL,
  `triage_category` enum('Green','BH Green','Yellow','Red','Gray','Black') NOT NULL,
  PRIMARY KEY  (`co_id`,`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='LPF is an example of an "other xml" content object, e.g., ot';

--
-- RELATIONS FOR TABLE `edxl_co_lpf`:
--   `co_id`
--       `edxl_co_header` -> `co_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_co_photos`
--
-- Creation: Jun 22, 2011 at 06:04 PM
--

CREATE TABLE `edxl_co_photos` (
  `co_id` int(11) NOT NULL,
  `p_uuid` varchar(255) NOT NULL COMMENT 'Sahana person ID',
  `mimeType` varchar(255) NOT NULL COMMENT 'As in ''image/jpeg''',
  `uri` varchar(255) NOT NULL COMMENT 'Photo filename = Mass casualty patient ID + zone + ''s#'' if secondary + optional caption after hypen',
  `contentData` mediumtext character set ascii NOT NULL COMMENT 'Base-64 encoded image',
  PRIMARY KEY  (`co_id`,`p_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='LPF is an example of an "other xml" content object, e.g., ot';

-- --------------------------------------------------------

--
-- Table structure for table `edxl_co_roles`
--
-- Creation: Apr 15, 2011 at 05:00 PM
--

CREATE TABLE `edxl_co_roles` (
  `co_id` int(11) NOT NULL,
  `role_num` int(11) NOT NULL default '0',
  `of_originator` tinyint(1) NOT NULL COMMENT '0 = false = of consumer',
  `role_urn` varchar(255) NOT NULL,
  `role` varchar(255) NOT NULL,
  PRIMARY KEY  (`co_id`,`role_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_co_roles`:
--   `co_id`
--       `edxl_co_header` -> `co_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_de_header`
--
-- Creation: Jun 07, 2011 at 06:12 PM
--

CREATE TABLE `edxl_de_header` (
  `de_id` int(11) NOT NULL,
  `when_sent` datetime NOT NULL,
  `sender_id` varchar(255) NOT NULL COMMENT 'Email, phone num, etc.  Not always URI, URN, URL',
  `distr_id` varchar(255) NOT NULL COMMENT 'Distribution ID.  Sender may or may not choose to vary.',
  `distr_status` enum('Actual','Exercise','System','Test') NOT NULL,
  `distr_type` enum('Ack','Cancel','Dispatch','Error','Report','Request','Response','Update') NOT NULL COMMENT 'Not included: types for sensor grids',
  `combined_conf` varchar(255) NOT NULL COMMENT 'Combined confidentiality of all content objects',
  `language` varchar(255) default NULL,
  `when_here` datetime NOT NULL COMMENT 'Received or sent from here.  [local]',
  `inbound` tinyint(1) NOT NULL default '1' COMMENT 'BOOLEAN [local]',
  PRIMARY KEY  (`de_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Overall message base, defined by EDXL Distribution Element';

-- --------------------------------------------------------

--
-- Table structure for table `edxl_de_keywords`
--
-- Creation: Apr 15, 2011 at 04:29 PM
--

CREATE TABLE `edxl_de_keywords` (
  `de_id` int(11) NOT NULL,
  `keyword_num` int(11) NOT NULL default '0',
  `keyword_urn` varchar(255) NOT NULL,
  `keyword` varchar(255) character set latin1 NOT NULL,
  PRIMARY KEY  (`de_id`,`keyword_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_de_keywords`:
--   `de_id`
--       `edxl_de_header` -> `de_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_de_prior_messages`
--
-- Creation: Apr 15, 2011 at 04:01 PM
--

CREATE TABLE `edxl_de_prior_messages` (
  `de_id` int(11) NOT NULL,
  `prior_msg_num` int(11) NOT NULL default '0',
  `when_sent` datetime NOT NULL COMMENT 'external time',
  `sender_id` varchar(255) NOT NULL COMMENT 'external ID',
  `distr_id` varchar(255) NOT NULL COMMENT 'external distribution ID',
  PRIMARY KEY  (`de_id`,`prior_msg_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_de_prior_messages`:
--   `de_id`
--       `edxl_de_header` -> `de_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_de_roles`
--
-- Creation: Apr 15, 2011 at 04:28 PM
--

CREATE TABLE `edxl_de_roles` (
  `de_id` int(11) NOT NULL,
  `role_num` int(11) NOT NULL default '0',
  `of_sender` tinyint(1) NOT NULL,
  `role_urn` varchar(255) NOT NULL,
  `role` varchar(255) NOT NULL,
  PRIMARY KEY  (`de_id`,`role_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_de_roles`:
--   `de_id`
--       `edxl_de_header` -> `de_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_de_target_addresses`
--
-- Creation: Apr 15, 2011 at 04:03 PM
--

CREATE TABLE `edxl_de_target_addresses` (
  `de_id` int(11) NOT NULL,
  `address_num` int(11) NOT NULL default '0',
  `scheme` varchar(255) NOT NULL COMMENT 'Like "e-mail"',
  `value` varchar(255) NOT NULL,
  PRIMARY KEY  (`de_id`,`address_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_de_target_addresses`:
--   `de_id`
--       `edxl_de_header` -> `de_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_de_target_circles`
--
-- Creation: Apr 15, 2011 at 04:23 PM
--

CREATE TABLE `edxl_de_target_circles` (
  `de_id` int(11) NOT NULL,
  `circle_num` int(11) NOT NULL default '0',
  `latitude` float NOT NULL,
  `longitude` float NOT NULL,
  `radius_km` float NOT NULL,
  PRIMARY KEY  (`de_id`,`circle_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_de_target_circles`:
--   `de_id`
--       `edxl_de_header` -> `de_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_de_target_codes`
--
-- Creation: Apr 19, 2011 at 01:58 PM
--

CREATE TABLE `edxl_de_target_codes` (
  `de_id` int(11) NOT NULL,
  `codes_num` int(11) NOT NULL default '0',
  `code_type` enum('country','subdivision','locCodeUN') default NULL COMMENT 'Respectively (1) ISO 3166-1 2-letter country code (2) ISO 3166-2 code: country + "-" + per-country 2-3 char code like state, e.g., "US-MD". (3) UN transport hub code: country + "-" + 2-3 char code (cap ASCII or 2-9), e.g., "US-BWI"',
  `code` varchar(6) default NULL COMMENT 'See format examples for code_type field',
  PRIMARY KEY  (`de_id`,`codes_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_de_target_codes`:
--   `de_id`
--       `edxl_de_header` -> `de_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `edxl_de_target_polygons`
--
-- Creation: Jun 07, 2011 at 05:51 PM
--

CREATE TABLE `edxl_de_target_polygons` (
  `de_id` int(11) NOT NULL,
  `poly_num` int(11) NOT NULL default '0',
  `point_num` int(11) NOT NULL default '0' COMMENT 'Point within this polygon',
  `latitude` float NOT NULL,
  `longitude` float NOT NULL,
  PRIMARY KEY  (`de_id`,`poly_num`,`point_num`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- RELATIONS FOR TABLE `edxl_de_target_polygons`:
--   `de_id`
--       `edxl_de_header` -> `de_id`
--

--
-- Constraints for dumped tables
--

--
-- Constraints for table `edxl_co_header`
--
ALTER TABLE `edxl_co_header`
  ADD CONSTRAINT `edxl_co_header_ibfk_1` FOREIGN KEY (`de_id`) REFERENCES `edxl_de_header` (`de_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_co_keywords`
--
ALTER TABLE `edxl_co_keywords`
  ADD CONSTRAINT `edxl_co_keywords_ibfk_1` FOREIGN KEY (`co_id`) REFERENCES `edxl_co_header` (`co_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_co_lpf`
--
ALTER TABLE `edxl_co_lpf`
  ADD CONSTRAINT `edxl_co_lpf_ibfk_1` FOREIGN KEY (`co_id`) REFERENCES `edxl_co_header` (`co_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_co_roles`
--
ALTER TABLE `edxl_co_roles`
  ADD CONSTRAINT `edxl_co_roles_ibfk_1` FOREIGN KEY (`co_id`) REFERENCES `edxl_co_header` (`co_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_de_keywords`
--
ALTER TABLE `edxl_de_keywords`
  ADD CONSTRAINT `edxl_de_keywords_ibfk_1` FOREIGN KEY (`de_id`) REFERENCES `edxl_de_header` (`de_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_de_prior_messages`
--
ALTER TABLE `edxl_de_prior_messages`
  ADD CONSTRAINT `edxl_de_prior_messages_ibfk_1` FOREIGN KEY (`de_id`) REFERENCES `edxl_de_header` (`de_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_de_roles`
--
ALTER TABLE `edxl_de_roles`
  ADD CONSTRAINT `edxl_de_roles_ibfk_1` FOREIGN KEY (`de_id`) REFERENCES `edxl_de_header` (`de_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_de_target_addresses`
--
ALTER TABLE `edxl_de_target_addresses`
  ADD CONSTRAINT `edxl_de_target_addresses_ibfk_1` FOREIGN KEY (`de_id`) REFERENCES `edxl_de_header` (`de_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_de_target_circles`
--
ALTER TABLE `edxl_de_target_circles`
  ADD CONSTRAINT `edxl_de_target_circles_ibfk_1` FOREIGN KEY (`de_id`) REFERENCES `edxl_de_header` (`de_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_de_target_codes`
--
ALTER TABLE `edxl_de_target_codes`
  ADD CONSTRAINT `edxl_de_target_codes_ibfk_1` FOREIGN KEY (`de_id`) REFERENCES `edxl_de_header` (`de_id`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `edxl_de_target_polygons`
--
ALTER TABLE `edxl_de_target_polygons`
  ADD CONSTRAINT `edxl_de_target_polygons_ibfk_1` FOREIGN KEY (`de_id`) REFERENCES `edxl_de_header` (`de_id`) ON DELETE CASCADE ON UPDATE CASCADE;
