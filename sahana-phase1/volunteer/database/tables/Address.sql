CREATE SEQUENCE seq_Address
       START 1
       INCREMENT 1;

CREATE TABLE Address
(
	AddressId    integer DEFAULT nextval('seq_Address'::text) NOT NULL,
	AddressLine1 varchar(50) DEFAULT '',
	AddressLine2 varchar(50) DEFAULT '',
	AddressLine3 varchar(50) DEFAULT '',
	Location     varchar(50) DEFAULT '',
        State        varchar(50) DEFAULT '',
	Postcode     varchar(10) DEFAULT '',
	Country      varchar(50) DEFAULT '',
	LocationId   integer NOT NULL,
	CreateUserId varchar(10) DEFAULT 'System',
	CreateDate   date DEFAULT current_date,
	CreateTime   time DEFAULT current_time,
	UpdateUserId varchar(10) DEFAULT 'System',
	UpdateDate   date DEFAULT current_date,
	UpdateTime   time DEFAULT current_time,
	RowVersion   timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_Address_AddressId PRIMARY KEY (AddressId)
);

ALTER TABLE Address
      ADD CONSTRAINT fk_Address_Code_LocationId
      FOREIGN KEY (LocationId)
      REFERENCES Code (CodeId);