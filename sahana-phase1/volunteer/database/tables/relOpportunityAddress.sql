CREATE SEQUENCE seq_OpportunityAddress
       START 1
       INCREMENT 1;

CREATE TABLE relOpportunityAddress
(
	OpportunityAddressId integer DEFAULT nextval('seq_OpportunityAddress'::text) NOT NULL,
	OpportunityId        integer NOT NULL,
	AddressId            integer NOT NULL,
	AddressType          integer DEFAULT 12 NOT NULL,
        CreateUserId         varchar(10) DEFAULT 'System',
	CreateDate           date DEFAULT current_date,
	CreateTime           time DEFAULT current_time,
	UpdateUserId         varchar(10) DEFAULT 'System',
	UpdateDate           date DEFAULT current_date,
	UpdateTime           time DEFAULT current_time,
        RowVersion           timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relOpportunityAddress_OpportunityAddressId PRIMARY KEY (OpportunityAddressId)
);

ALTER TABLE relOpportunityAddress
      ADD CONSTRAINT fk_relOpportunityAddress_Opportunity_OpportunityId
          FOREIGN KEY (OpportunityId)
          REFERENCES Opportunity (OpportunityId);

ALTER TABLE relOpportunityAddress
      ADD CONSTRAINT fk_relOpportunityAddress_Address_AddressId
          FOREIGN KEY (AddressId)
          REFERENCES Address (AddressId);

ALTER TABLE relOpportunityAddress
      ADD CONSTRAINT fk_relOpportunityAddress_Code_AddressType
          FOREIGN KEY (AddressType)
          REFERENCES Code (CodeId);
