/* INVENTORY MANAGEMENT SYSTEM TABLES */
/* --------------------------------------------------------------------------*/
/*
*ims_item_records table keeps the track of particular items
*/
DROP TABLE IF EXISTS `ims_item_records`;
CREATE TABLE ims_item_records
(

	item_id BIGINT NOT NULL AUTO_INCREMENT,
	catalog_id VARCHAR(100),
	inv_id VARCHAR(60),
	transit_id BIGINT,
	suplier_id VARCHAR(60),
	item_name VARCHAR(100),
	amount VARCHAR(50),
	unit VARCHAR(20),
	manufactured_date DATE,
	expire_date DATE,
	cost_per_unit VARCHAR(100),
	state VARCHAR(20),
        inserted_date DATE,
	total_amount VARCHAR(50),
	predict_amount VARCHAR(50),
	PRIMARY KEY(item_id)
);

/*
*ims_inventory records table keeps the track of inventories
*/
DROP TABLE IF EXISTS `ims_inventory_records`;
CREATE TABLE ims_inventory_records
(

	inv_uuid VARCHAR(15),
	parent_id BIGINT,
	inventory_name VARCHAR(100),
	inventory_type VARCHAR(100),
	reg_no VARCHAR(100),
	man_power VARCHAR(100),
	equipment VARCHAR(100),
	resources TEXT,
	space VARCHAR(100),
	added_date DATE,
	PRIMARY KEY(inv_uuid)	
);

/*
*ims_transfer_item table keeps the track of items that are transfered to other inventries. Mean while this table keeps the records about the inventories which transfered items and which received items
*/

DROP TABLE IF EXISTS `ims_transfer_item`;
CREATE TABLE ims_transfer_item
(
	transit_id BIGINT NOT NULL AUTO_INCREMENT,
	item_id BIGINT,
	catalog_id VARCHAR(100),
	amount_send VARCHAR(50),
	unit VARCHAR(20),
	inv_id_from VARCHAR(15),
	inv_id_to VARCHAR(15),
	destination_type VARCHAR(20),
	person_send VARCHAR(100),
	date_send DATE,
	destribution_method VARCHAR(100),
	requested_person VARCHAR(100),
	received_item_id BIGINT,
	amount_received VARCHAR(20),
	person_received VARCHAR(20),
	date_received DATE,
	cause VARCHAR(500),
	vehicle_number VARCHAR(50),
	driver_name VARCHAR(100),
	driver_mobile VARCHAR(50),
	driver_address VARCHAR(200),
	driving_licence VARCHAR(50),
	PRIMARY KEY(transit_id)
	
);

/*
*ims_reorder_level table keeps the track of re-order level for particular item in particular inventories
*/
DROP TABLE IF EXISTS `ims_reorder_level`;
CREATE TABLE ims_reorder_level
(
	catalog_id VARCHAR(100),
	inv_id VARCHAR(15),
	minimum_quantity VARCHAR(50),
	unit VARCHAR(20),
	PRIMARY KEY(catalog_id,inv_id)
);

/*
*ims_optimization table is a tempory table which stores the predicted amount of a particular item with in a given time period 
*/
DROP TABLE IF EXISTS `ims_optimization`;
CREATE TABLE ims_optimization
(
/*	optim_id BIGINT NOT NULL AUTO_INCREMENT,*/

	catalog_id VARCHAR(100),
	inv_id VARCHAR(15),
	week BIGINT,
	actual_value VARCHAR(50),
	forecasted_value VARCHAR(50),
	unit VARCHAR(20),
	double_forecasted_value VARCHAR(50),
	PRIMARY KEY(catalog_id,inv_id,week)
);

/*
*ims_alternate table keeps the track of items which can be used as an alternate for another type of items
*/

DROP TABLE IF EXISTS `ims_alternate`;
CREATE TABLE ims_alternate
(
	alternate_id BIGINT NOT NULL AUTO_INCREMENT,
	catalog_id VARCHAR(100),
	inv_id VARCHAR(15),
	alternate VARCHAR(100),
	PRIMARY KEY(alternate_id)
);

/*
*ims_relation table keeps the track of items which are related to other items
*/

DROP TABLE IF EXISTS `ims_relation`;
CREATE TABLE ims_relation
(
	relation_id BIGINT NOT NULL AUTO_INCREMENT,
	catalog_id VARCHAR(100),
	inv_id VARCHAR(15),
	relation VARCHAR(100),
	PRIMARY KEY(relation_id)
);

/**
To be removed
**/

/*
*ims_item_amount_history
*/
DROP TABLE IF EXISTS `ims_item_amount_history`;
CREATE TABLE ims_item_amount_history
(

	item_id BIGINT NOT NULL,
	first_amount VARCHAR(60),
	unit VARCHAR(60),
	PRIMARY KEY(item_id)
);

/*
*ims_item_inventory_relation table
*/

DROP TABLE IF EXISTS `ims_inventory_relation`;
CREATE TABLE ims_inventory_relation
(
	inv_uuid VARCHAR(60),
	shel_org_id VARCHAR(60),
	shel_org_flag VARCHAR(10),
	PRIMARY KEY(inv_uuid, shel_org_id)
);

/**
* remove End
*/

/*
*ims_consolidated_kits table
*/

DROP TABLE IF EXISTS `ims_consolidated_kits`;
CREATE TABLE ims_consolidated_kits
(
	kit_item_id BIGINT NOT NULL,
	item_id BIGINT NOT NULL,
	amount VARCHAR(60),
	unit VARCHAR(60),
	PRIMARY KEY(kit_item_id, item_id)
);



