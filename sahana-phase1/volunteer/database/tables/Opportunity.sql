CREATE SEQUENCE seq_Opportunity
       START 1
       INCREMENT 1;

CREATE TABLE Opportunity
(
	OpportunityId       integer DEFAULT nextval('seq_Opportunity'::text) NOT NULL,
	OrganisationId      integer NOT NULL,
	OrganisationContact integer NOT NULL,
	FPC_Flag	    integer DEFAULT 15,
	PermTempFlag	    integer DEFAULT 19,
	CreateUserId        varchar(10) DEFAULT 'System',
	CreateDate          date DEFAULT current_date,
	CreateTime          time DEFAULT current_time,
	UpdateUserId        varchar(10) DEFAULT 'System',
	UpdateDate          date DEFAULT current_date,
	UpdateTime          time DEFAULT current_time,
	RowVersion          timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_Opportunity_OpportunityId PRIMARY KEY (OpportunityId)
);

ALTER TABLE Opportunity
      ADD CONSTRAINT fk_Opportunity_Organisation_OrganisationId
      FOREIGN KEY (OrganisationId)
      REFERENCES  Organisation (OrganisationId);

ALTER TABLE Opportunity
      ADD CONSTRAINT fk_Opportunity_Person_OrganisationContact
      FOREIGN KEY (OrganisationContact)
      REFERENCES  Person (PersonId);