DROP TABLE IF EXISTS `messaging_group`;
CREATE TABLE messaging_group
(

	group_uuid VARCHAR(20),
	group_name VARCHAR(100),
	address VARCHAR(500),
	mobile VARCHAR(500),
	PRIMARY KEY(group_uuid)
);