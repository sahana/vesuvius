CREATE SEQUENCE seq_Skill
       START 1
       INCREMENT 1;

CREATE TABLE Skill
(
	SkillId integer DEFAULT nextval('seq_Skill'::text) NOT NULL,
	SkillName varchar(50) NOT NULL,
	CreateUserId varchar(10) DEFAULT 'System',
	CreateDate   date DEFAULT current_date,
	CreateTime   time DEFAULT current_time,
	UpdateUserId varchar(10) DEFAULT 'System',
	UpdateDate   date DEFAULT current_date,
	UpdateTime   time DEFAULT current_time,
	RowVersion   timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_Skill_SkillId PRIMARY KEY (SkillId)
);