/* A Sample database creation script from inventory management module */
/* Remeber to follow the schema conventions */ 
/* --------------------------------------------------------------------------*/
/*

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
	added_date DATE,
	PRIMARY KEY(inv_uuid)	
);
*/
