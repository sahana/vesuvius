CREATE SEQUENCE seq_OpportunitySkill
       START 1
       INCREMENT 1;

CREATE TABLE relOpportunitySkill
(
	OpportunitySkillId integer DEFAULT nextval('seq_OpportunitySkill'::text) NOT NULL,
	OpportunityId      integer NOT NULL,
	SkillId            integer NOT NULL,
	SkillType          integer DEFAULT 23 NOT NULL,
        CreateUserId       varchar(10) DEFAULT 'System',
	CreateDate         date DEFAULT current_date,
	CreateTime         time DEFAULT current_time,
	UpdateUserId       varchar(10) DEFAULT 'System',
	UpdateDate         date DEFAULT current_date,
	UpdateTime         time DEFAULT current_time,
        RowVersion         timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relOpportunitySkill_OpportunitySkillId PRIMARY KEY (OpportunitySkillId)
);

ALTER TABLE relOpportunitySkill
      ADD CONSTRAINT fk_relOpportunitySkill_Opportunity_OpportunityId
          FOREIGN KEY (OpportunityId)
          REFERENCES Opportunity (OpportunityId);

ALTER TABLE relOpportunitySkill
      ADD CONSTRAINT fk_relOpportunitySkill_Skill_SkillId
          FOREIGN KEY (SkillId)
          REFERENCES Skill (SkillId);

ALTER TABLE relOpportunitySkill
      ADD CONSTRAINT fk_relOpportunitySkill_Code_SkillType
          FOREIGN KEY (SkillType)
          REFERENCES Code (CodeId);
