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
