CREATE SEQUENCE seq_OpportunityLocation
       START 1
       INCREMENT 1;

CREATE TABLE relOpportunityLocation
(
	OpportunityLocationId integer DEFAULT nextval('seq_OpportunityLocation'::text) NOT NULL,
	OpportunityId         integer NOT NULL,
	LocationId            integer NOT NULL,
        CreateUserId          varchar(10) DEFAULT 'System',
	CreateDate            date DEFAULT current_date,
	CreateTime            time DEFAULT current_time,
	UpdateUserId          varchar(10) DEFAULT 'System',
	UpdateDate            date DEFAULT current_date,
	UpdateTime            time DEFAULT current_time,
        RowVersion            timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relOpportunityLocation_OpportunityLocationId PRIMARY KEY (OpportunityLocationId)
);

ALTER TABLE relOpportunityLocation
      ADD CONSTRAINT fk_relOpportunityLocation_Opportunity_OpportunityId
          FOREIGN KEY (OpportunityId)
          REFERENCES Opportunity (OpportunityId);

ALTER TABLE relOpportunityLocation
      ADD CONSTRAINT fk_relOpportunityLocation_Code_CodeId
          FOREIGN KEY (LocationId)
          REFERENCES Code (CodeId);
