USE sahana;
/* INVENTORY MANAGEMENT SYSTEM TABLES */
/* --------------------------------------------------------------------------*/
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
	PRIMARY KEY(item_id)
);

DROP TABLE IF EXISTS `ims_inventory_records`;
CREATE TABLE ims_inventory_records
(

	inv_uuid BIGINT NOT NULL AUTO_INCREMENT,
	parent_id BIGINT,
	inventory_name VARCHAR(100),
	inventory_type VARCHAR(100),
	reg_no VARCHAR(100),
	man_power VARCHAR(100),
	equipment VARCHAR(100),
	resources TEXT,
	space VARCHAR(100),
	PRIMARY KEY(inv_uuid)	
);

DROP TABLE IF EXISTS `ims_transfer_item`;
CREATE TABLE ims_transfer_item
(
	transit_id BIGINT NOT NULL AUTO_INCREMENT,
	item_id BIGINT,
	amount_send VARCHAR(50),
	unit VARCHAR(20),
	inv_id_to BIGINT,
	person_send VARCHAR(100),
	date_send DATE,
	destribution_method VARCHAR(100),
	requested_person VARCHAR(100),
	received_item_id BIGINT,
	amount_received VARCHAR(20),
	person_received VARCHAR(20),
	date_received DATE,
	PRIMARY KEY(transit_id)
	
);

DROP TABLE IF EXISTS `ims_reorder_level`;
CREATE TABLE ims_reorder_level
(
	catalog_id VARCHAR(100),
	inv_id BIGINT,
	minimum_quantity VARCHAR(50),
	unit VARCHAR(20),
	PRIMARY KEY(catalog_id,inv_id)
);

