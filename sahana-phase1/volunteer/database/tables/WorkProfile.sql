CREATE SEQUENCE seq_WorkProfile
       START 1
       INCREMENT 1;

CREATE TABLE WorkProfile
(
	WorkProfileId integer DEFAULT nextval('seq_WorkProfile'::text) NOT NULL,
	VolunteerId   integer NOT NULL,
	FPC_Flag      integer DEFAULT 15 NOT NULL,
        PermTempFlag  integer DEFAULT 19 NOT NULL,
	CreateUserId  varchar(10) DEFAULT 'System',
	CreateDate    date DEFAULT current_date,
	CreateTime    time DEFAULT current_time,
	UpdateUserId  varchar(10) DEFAULT '',
	UpdateDate    date DEFAULT current_date,
	UpdateTime    time DEFAULT current_time,
	RowVersion    timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_WorkProfile_WorkProfileId PRIMARY KEY (WorkProfileId)
);

ALTER TABLE WorkProfile
      ADD CONSTRAINT fk_WorkProfile_Volunteer_VolunteerId
      FOREIGN KEY (VolunteerId)
      REFERENCES Volunteer (VolunteerId);

ALTER TABLE WorkProfile
      ADD CONSTRAINT fk_WorkProfile_Code_FPC_Flag
      FOREIGN KEY (FPC_Flag)
      REFERENCES Code (CodeId);

ALTER TABLE WorkProfile
      ADD CONSTRAINT fk_WorkProfile_Code_PermTempFlag
      FOREIGN KEY (PermTempFlag)
      REFERENCES Code (CodeId);
