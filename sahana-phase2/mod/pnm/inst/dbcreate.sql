CREATE TABLE `pnm_media_org` (
`m_uuid` VARCHAR( 60 ) NOT NULL ,
`name` VARCHAR( 100 ) NOT NULL ,
`conact` VARCHAR( 100 ) NOT NULL ,
PRIMARY KEY ( `m_uuid` )
);

CREATE TABLE `pnm_headlines` (
`headline` VARCHAR( 60 ) NOT NULL ,
`description` VARCHAR( 100 ) NOT NULL ,
PRIMARY KEY ( `headline` )
);

/**
 * The media table which stores images and videos
 */
DROP TABLE IF EXISTS `pnm_media`;

CREATE TABLE `pnm_media` (
`media_id` VARCHAR( 32 ) NOT NULL ,
`media_title` TEXT NULL ,
`media_description` TEXT NULL ,
`media_type` VARCHAR( 32 ) NULL ,
`mime_type` VARCHAR( 32 ) NULL ,
`media_data` LONGBLOB NULL ,
`date` DATETIME NULL ,
PRIMARY KEY ( `media_id` )
)
