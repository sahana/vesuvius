/* CUSTOM THEME TABLES */
/* --------------------------------------------------------------------------*/
/*
*theme_custom_values table stores various CSS values for this Sahana instance
*/
DROP TABLE IF EXISTS `theme_custom_values`;
CREATE TABLE theme_custom_values
(
	id BIGINT NOT NULL AUTO_INCREMENT,
	css1 VARCHAR(7),
	css2 VARCHAR(7),
	css3 VARCHAR(7),
	css4 VARCHAR(7),
	css5 VARCHAR(7),
	css6 VARCHAR(7),
	css7 VARCHAR(7),
	css8 VARCHAR(7),
	css9 VARCHAR(7),
	logo BOOLEAN,
	parent VARCHAR (20),
	username VARCHAR (50),
	PRIMARY KEY(id)
);
