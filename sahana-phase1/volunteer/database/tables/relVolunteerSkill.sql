CREATE SEQUENCE seq_VolunteerSkill
       START 1
       INCREMENT 1;

CREATE TABLE relVolunteerSkill
(
	VolunteerSkillId integer DEFAULT nextval('seq_VolunteerSkill'::text) NOT NULL,
	VolunteerId      integer NOT NULL,
	SkillId          integer NOT NULL,
	SkillType        integer DEFAULT 22 NOT NULL,
        CreateUserId     varchar(10) DEFAULT 'System',
	CreateDate       date DEFAULT current_date,
	CreateTime       time DEFAULT current_time,
	UpdateUserId     varchar(10) DEFAULT 'System',
	UpdateDate       date DEFAULT current_date,
	UpdateTime       time DEFAULT current_time,
        RowVersion       timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relVolunteerSkill_VolunteerSkillId PRIMARY KEY (VolunteerSkillId)
);

ALTER TABLE relVolunteerSkill
      ADD CONSTRAINT fk_relVolunteerSkill_Volunteer_VolunteerId
          FOREIGN KEY (VolunteerId)
          REFERENCES Volunteer (VolunteerId);

ALTER TABLE relVolunteerSkill
      ADD CONSTRAINT fk_relVolunteerSkill_Skill_SkillId
          FOREIGN KEY (SkillId)
          REFERENCES Skill (SkillId);

ALTER TABLE relVolunteerSkill
      ADD CONSTRAINT fk_relVolunteerSkill_Code_SkillType
          FOREIGN KEY (SkillType)
          REFERENCES Code (CodeId);
