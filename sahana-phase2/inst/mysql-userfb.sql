/*
 * MySql user feedback functinality related tables.
 */

DROP TABLE IF EXISTS user_feedback;
CREATE TABLE `user_feedback` (
`fb_id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`mod` VARCHAR( 10 ) NULL ,
`act` VARCHAR( 250 ) NULL ,
`comment` LONGTEXT NULL ,
`date` DATETIME NULL ,
`email` VARCHAR( 250 ) NULL
);

DROP TABLE IF EXISTS faq;
 CREATE TABLE `faq` (
`qa_id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`mod` VARCHAR( 10 ) NULL ,
`act` VARCHAR( 250 ) NULL ,
`question` LONGTEXT NULL ,
`answer` LONGTEXT NULL
);
