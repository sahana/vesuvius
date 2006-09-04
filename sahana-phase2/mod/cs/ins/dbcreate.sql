/*CATALOGUE SYSTEM TABLES*/
/*-----------------------*/

DROP TABLE IF EXISTS `ct_catalogue`;
DROP TABLE IF EXISTS `ct_unit`;
DROP TABLE IF EXISTS `ct_cat_unit`;
DROP TABLE IF EXISTS `ct_unit_type`;
CREATE TABLE ct_catalogue 
	(ct_uuid varchar(60) NOT NULL PRIMARY KEY, 
	parentid varchar(60),
	name varchar(100),
	description varchar(200),
	final_flag varchar(1) DEFAULT '0',
	keyword varchar(100));

CREATE TABLE ct_unit
	(unit_type_uuid varchar(60),
	unit_uuid varchar(60) NOT NULL PRIMARY KEY,
	name varchar(100),
	base_flag varchar(1) DEFAULT '0',
	multiplier DOUBLE);

CREATE TABLE ct_cat_unit
	(ct_uuid varchar(60),
	unit_uuid varchar(60));

CREATE TABLE ct_unit_type
	(unit_type_uuid varchar(60) NOT NULL PRIMARY KEY,
	name varchar(100),
	description varchar(100));

CREATE TABLE ct_suppliers
	(
	ct_uuid varchar(60),
	supplier varchar(100)
	);
