CREATE SEQUENCE seq_pk_Match
       START 1
       INCREMENT 1;

CREATE SEQUENCE seq_Match
       START 1
       INCREMENT 1;

CREATE TABLE Match
(
	MatchIdentifier      integer DEFAULT nextval('seq_pk_Match'::text) NOT NULL,
	MatchId              integer NOT NULL,
	MatchType            integer NOT NULL,
	VolunteerSkillId     integer,
	OpportunitySkillId   integer,
	VolunteerAddressId   integer,
	OpportunityAddressId integer,
	ContactVolunteer     boolean DEFAULT false,
	ContactOrganisation  boolean DEFAULT false,
	VolunteerRead	     boolean DEFAULT false,
	OrganisationRead     boolean DEFAULT false,
	CreateUserId         varchar(10) DEFAULT 'System',
	CreateDate           date DEFAULT current_date,
	CreateTime           time DEFAULT current_time,
	UpdateUserId         varchar(10) DEFAULT 'System',
	UpdateDate           date DEFAULT current_date,
	UpdateTime           time DEFAULT current_time,
        RowVersion           timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_Match_MatchIdentifier PRIMARY KEY (MatchIdentifier)
);

ALTER TABLE Match
      ADD CONSTRAINT fk_Match_Code_MatchType
      FOREIGN KEY (MatchType)
      REFERENCES Code (CodeId);

ALTER TABLE Match
      ADD CONSTRAINT fk_Match_relVolunteerSkill_VolunteerSkillId
      FOREIGN KEY (VolunteerSkillId)
      REFERENCES relVolunteerSkill (VolunteerSkillId);

ALTER TABLE Match
      ADD CONSTRAINT fk_Match_relOpportunitySkill_OpportunitySkillId
      FOREIGN KEY (OpportunitySkillId)
      REFERENCES relOpportunitySkill (OpportunitySkillId);

ALTER TABLE Match
      ADD CONSTRAINT fk_Match_relVolunteerAddress_VolunteerAddressId
      FOREIGN KEY (VolunteerAddressId)
      REFERENCES relVolunteerAddress (VolunteerAddressId);

ALTER TABLE Match
      ADD CONSTRAINT fk_Match_relOpportunityAddress_OpportunityAddressId
      FOREIGN KEY (OpportunityAddressId)
      REFERENCES relOpportunityAddress (OpportunityAddressId);
