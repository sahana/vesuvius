/*Social Network TABLES*/

/** 
 * Social Network mysql-config.sql File
 *
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan@opensource.lk> <rekasandaruwan@gmail.com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    shana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
* Dropping tables if exists
* Modules: sn 
* Last Edited: 02-feb-2009 
*/

DROP TABLE IF EXISTS `sn_groups`;

CREATE TABLE sn_groups 
    (`group_id` varchar(60) NOT NULL, 
    `group_name` varchar(100), 
    `description` TEXT(600),
    `category_id` varchar(100) NULL,
PRIMARY KEY (`group_id`)
);


DROP TABLE IF EXISTS `sn_category`;

CREATE TABLE sn_category 
    (`category_id` varchar(60) NOT NULL, 
    `category_name` varchar(100), 
    `parent_id` varchar(60) NULL,
    `level` varchar(10),
PRIMARY KEY (`category_id`)
);


DROP TABLE IF EXISTS `sn_roles`;

CREATE TABLE sn_roles 
    (`role_id` varchar(60) NOT NULL, 
    `role_name` varchar(100), 
    `description` TEXT(200),
PRIMARY KEY (`role_id`)
);


DROP TABLE IF EXISTS `sn_group_note`;

CREATE TABLE sn_group_note 
    (`note_id` varchar(60) NOT NULL,
     `group_id` varchar(60), 
     `subject` TEXT(200),
     `date` date,
     `note` LONGTEXT,
PRIMARY KEY (`note_id`)
);


DROP TABLE IF EXISTS `sn_roles`;

CREATE TABLE sn_roles 
    (`role_id` varchar(60) NOT NULL, 
    `role_category` varchar(100),
    `role_name` varchar(100), 
    `description` TEXT(600),
PRIMARY KEY (`role_id`)
);


DROP TABLE IF EXISTS `sn_module_role`;

CREATE TABLE sn_module_role 
    (`role_id` varchar(60), 
    `user_id` varchar(60)
);


DROP TABLE IF EXISTS `sn_group_role`;

CREATE TABLE sn_group_role 
    (`role_id` varchar(60), 
    `group_id` varchar(60),
    `user_id` varchar(60)
);


DROP TABLE IF EXISTS `sn_forum_role`;

CREATE TABLE sn_forum_role 
    (`role_id` varchar(60),
    `forum_id` varchar(60),
    `user_id` varchar(60)
);


DROP TABLE IF EXISTS `sn_forums`;

CREATE TABLE sn_forums 
    (`forum_id` varchar(60) NOT NULL, 
    `forum_name` varchar(100), 
    `description` TEXT(600),
    `dis_id` varchar(100) NULL,
PRIMARY KEY (`forum_id`)
);


DROP TABLE IF EXISTS `sn_forum_note`;

CREATE TABLE sn_forum_note 
    (`note_id` varchar(60) NOT NULL,
     `forum_id` varchar(60), 
     `subject` TEXT(200),
     `date` date,
     `note` LONGTEXT,
PRIMARY KEY (`note_id`)
);


DROP TABLE IF EXISTS `sn_public_profile`;
CREATE TABLE `sn_public_profile` (
`p_uuid` VARCHAR( 60 ) NOT NULL ,
`public_profile` TINYINT( 1 ) NOT NULL DEFAULT '0',
PRIMARY KEY ( `p_uuid` )
);

DROP TABLE IF EXISTS `sn_interests`;
CREATE TABLE `sn_interests` (
`interest_id` BIGINT NOT NULL,
`interest` TEXT NOT NULL ,
`description` MEDIUMTEXT NOT NULL ,
PRIMARY KEY ( `interest_id` )
);

DROP TABLE IF EXISTS `sn_user_interest`;
CREATE TABLE `sn_user_interest` (
`p_uuid` VARCHAR( 60 ) NOT NULL ,
`interest_id` BIGINT NOT NULL ,
PRIMARY KEY ( `p_uuid` , `interest_id` )
);

DROP TABLE IF EXISTS `sn_friends`;
CREATE TABLE `sn_friends` (
`p_uuid` VARCHAR( 60 ) NOT NULL ,
`friend_p_uuid` VARCHAR( 60 ) NOT NULL ,
`status` VARCHAR( 60 ),
PRIMARY KEY ( `p_uuid` , `friend_p_uuid` )
);

DROP TABLE IF EXISTS `sn_messages`;
CREATE TABLE `sn_messages` (
`message_id` BIGINT NOT NULL AUTO_INCREMENT,
`from_p_uuid` VARCHAR( 60 ) NOT NULL ,
`to_p_uuid` VARCHAR(60) NOT NULL,
`subject` TEXT NOT NULL ,
`message` LONGTEXT NOT NULL ,
`date` DATETIME NOT NULL ,
`status` VARCHAR( 40 ) NOT NULL ,
`folder` TEXT ,
PRIMARY KEY ( `message_id` )
);


DROP TABLE IF EXISTS `sn_forum_topic`;

CREATE TABLE sn_forum_topic 
    (`forum_id` varchar(60),  
    `user_id` varchar(60),
    `topic_id` varchar(60),
    `topic` varchar(200)
);


DROP TABLE IF EXISTS `sn_forum_post`;

CREATE TABLE sn_forum_post
    (`forum_id` varchar(60),  
    `user_id` varchar(60),
    `topic_id` varchar(60),
    `post_id` varchar(60),
    `date` date,
    `post` LONGTEXT
);

DROP TABLE IF EXISTS `sn_notification`;
CREATE TABLE `sn_notification` (
`notification_id` BIGINT NOT NULL ,
`target_p_uuid` VARCHAR( 60 ) NULL ,
`target_group_id` VARCHAR( 60 ) NULL ,
`target_action` VARCHAR( 200 ) NULL ,
`target_module` VARCHAR( 10 ) NULL ,
`target_func_params` LONGBLOB NULL ,
`added_date` DATETIME NULL ,
`expiry_date` DATETIME NULL ,
`subject` TEXT NULL ,
`message` TEXT NULL ,
`notification_status` VARCHAR( 20 ) NULL,
`related_to` BIGINT NULL,
PRIMARY KEY ( `notification_id` )
);
