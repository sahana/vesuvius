CREATE SEQUENCE seq_CategorySkill
       START 1
       INCREMENT 1;

CREATE TABLE relCategorySkill
(
	CategorySkillId integer DEFAULT nextval('seq_CategorySkill'::text) NOT NULL,
	CategoryId      integer NOT NULL,
	SkillId         integer NOT NULL,
        CreateUserId    varchar(10) DEFAULT 'System',
	CreateDate      date DEFAULT current_date,
	CreateTime      time DEFAULT current_time,
	UpdateUserId    varchar(10) DEFAULT 'System',
	UpdateDate      date DEFAULT current_date,
	UpdateTime      time DEFAULT current_time,
        RowVersion      timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relCategorySkill_CategorySkillId PRIMARY KEY (CategorySkillId)
);

ALTER TABLE relCategorySkill
      ADD CONSTRAINT fk_relCategorySkill_Category_CategoryId
          FOREIGN KEY (CategoryId)
          REFERENCES Category (CategoryId);

ALTER TABLE relCategorySkill
      ADD CONSTRAINT fk_relCategorySkill_Skill_SkillId
          FOREIGN KEY (SkillId)
          REFERENCES Skill (SkillId);
