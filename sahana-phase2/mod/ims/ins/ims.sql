USE sahana;
/* INVENTORY MANAGEMENT SYSTEM TABLES */
/* --------------------------------------------------------------------------*/
DROP TABLE IF EXISTS `ims_item_records`;
CREATE TABLE ims_item_records
(

	item_id BIGINT NOT NULL AUTO_INCREMENT,
	catalog_id VARCHAR(100),
	category VARCHAR(20),
	inv_id VARCHAR(60),
	item_name VARCHAR(100),
	amount BIGINT,
	unit VARCHAR(20),
	manufactured_date DATE,
	expire_date DATE,
	state VARCHAR(20),
	transit_state VARCHAR(20),
	item_send_to VARCHAR(20),
	item_send_from VARCHAR(20),
	amount_send BIGINT,
	amount_received BIGINT,
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


