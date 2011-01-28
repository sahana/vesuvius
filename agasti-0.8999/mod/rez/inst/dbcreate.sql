/**
* modRez: The table structure to pages and their content for the resources tab.
* Last changed: 20090806
*/

DROP TABLE IF EXISTS `rez_pages`;

CREATE table rez_pages (
	rez_page_id		int 		AUTO_INCREMENT	NOT NULL,
	rez_menu_title		varchar(64) 			NOT NULL,
	rez_page_title		varchar(64)			NOT NULL,
	rez_menu_order 		int 				NOT NULL,
	rez_content		mediumtext 			NOT NULL,
	rez_description		varchar(128)			NOT NULL,
	rez_timestamp		timestamp			NOT NULL,
	rez_visibility		varchar(16)			NOT NULL,
	PRIMARY KEY(rez_page_id)
) ENGINE=INNODB;
