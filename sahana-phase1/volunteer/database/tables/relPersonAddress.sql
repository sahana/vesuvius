CREATE SEQUENCE seq_PersonAddress
       START 1
       INCREMENT 1;

CREATE TABLE relPersonAddress
(
	PersonAddressId integer DEFAULT nextval('seq_PersonAddress'::text) NOT NULL,
	PersonId        integer NOT NULL,
	AddressId       integer NOT NULL,
	AddressType     integer NOT NULL,
        CreateUserId    varchar(10) DEFAULT 'System',
	CreateDate      date DEFAULT current_date,
	CreateTime      time DEFAULT current_time,
	UpdateUserId    varchar(10) DEFAULT 'System',
	UpdateDate      date DEFAULT current_date,
	UpdateTime      time DEFAULT current_time,
        RowVersion      timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relPersonAddress_PersonAddressId PRIMARY KEY (PersonAddressId)
);

ALTER TABLE relPersonAddress
      ADD CONSTRAINT fk_relPersonAddress_Person_PersonId
          FOREIGN KEY (PersonId)
          REFERENCES Person (PersonId);

ALTER TABLE relPersonAddress
      ADD CONSTRAINT fk_relPersonAddress_Address_AddressId
          FOREIGN KEY (AddressId)
          REFERENCES Address (AddressId);

ALTER TABLE relPersonAddress
      ADD CONSTRAINT fk_relPersonAddress_Code_AddressType
          FOREIGN KEY (AddressType)
          REFERENCES Code (CodeId);
