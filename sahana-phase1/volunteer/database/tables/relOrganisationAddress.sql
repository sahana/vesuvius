CREATE SEQUENCE seq_OrganisationAddress
       START 1
       INCREMENT 1;

CREATE TABLE relOrganisationAddress
(
	OrganisationAddressId integer DEFAULT nextval('seq_OrganisationAddress'::text) NOT NULL,
	OrganisationId        integer NOT NULL,
	AddressId            integer NOT NULL,
	AddressType          integer NOT NULL,
        CreateUserId         varchar(10) DEFAULT 'System',
	CreateDate           date DEFAULT current_date,
	CreateTime           time DEFAULT current_time,
	UpdateUserId         varchar(10) DEFAULT 'System',
	UpdateDate           date DEFAULT current_date,
	UpdateTime           time DEFAULT current_time,
        RowVersion           timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relOrganisationAddress_OrganisationAddressId PRIMARY KEY (OrganisationAddressId)
);

ALTER TABLE relOrganisationAddress
      ADD CONSTRAINT fk_relOrganisationAddress_Organisation_OrganisationId
          FOREIGN KEY (OrganisationId)
          REFERENCES Organisation (OrganisationId);

ALTER TABLE relOrganisationAddress
      ADD CONSTRAINT fk_relOrganisationAddress_Address_AddressId
          FOREIGN KEY (AddressId)
          REFERENCES Address (AddressId);

ALTER TABLE relOrganisationAddress
      ADD CONSTRAINT fk_relOrganisationAddress_Code_AddressType
          FOREIGN KEY (AddressType)
          REFERENCES Code (CodeId);
