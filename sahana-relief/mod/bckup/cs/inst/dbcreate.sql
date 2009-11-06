/*CATALOGUE SYSTEM TABLES*/

/**
* Dropping tables if exists
* Modules: cs 
* Last Edited: 26-OCT-2006 sditfac@opensource.lk
*/

DROP TABLE IF EXISTS `ct_catalogue`;
DROP TABLE IF EXISTS `ct_unit`;
DROP TABLE IF EXISTS `ct_cat_unit`;
DROP TABLE IF EXISTS `ct_unit_type`;
DROP TABLE IF EXISTS `ct_suppliers`;

/**
* Table to store catalogs and items
* Modules: cs,rms,ims
* Last Edited: 1-MARCH-2007 sditfac@opensource.lk
*/

CREATE TABLE ct_catalogue 
	(ct_uuid varchar(60) NOT NULL PRIMARY KEY, 
	parentid varchar(60), 
	name varchar(100), 
	description varchar(200), 
	final_flag varchar(1) DEFAULT '0',
	serial varchar(100) DEFAULT '1.',
	keyword varchar(100)); 

/**
* Table to store measurement units
* Modules: cs,rms,ims
* Last Edited: 26-OCT-2006 sditfac@opensource.lk
*/

CREATE TABLE ct_unit
	(unit_type_uuid varchar(60), 
	unit_uuid varchar(60) NOT NULL PRIMARY KEY, 
	name varchar(100), 
	base_flag varchar(1) DEFAULT '0', 
	multiplier DOUBLE); 

/**
* Table to store many to many relationship of ct_catalogue and ct_unit tables
* Modules: cs 
* Last Edited: 26-OCT-2006 sditfac@opensource.lk
*/

CREATE TABLE ct_cat_unit
	(ct_uuid varchar(60), 
	unit_uuid varchar(60)); 

/**
* Table to store measurement unit types
* Modules: cs,rms,ims
* Last Edited: 26-OCT-2006 sditfac@opensource.lk
*/

CREATE TABLE ct_unit_type
	(unit_type_uuid varchar(60) NOT NULL PRIMARY KEY, 
	name varchar(100), 
	description varchar(100)); 

/**
* Table to store suppliers
* Modules: cs 
* Last Edited: 26-OCT-2006 sditfac@opensource.lk
*/

CREATE TABLE ct_suppliers
	(
	ct_uuid varchar(60), 
	supplier varchar(100) 
	);
