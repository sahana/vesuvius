CREATE SEQUENCE seq_Volunteer
       START 1
       INCREMENT 1;


CREATE TABLE Volunteer
(
	VolunteerId  integer DEFAULT nextval('seq_Volunteer'::text) NOT NULL,
	CreateUserId varchar(10) DEFAULT 'System',
	CreateDate   date DEFAULT current_date,
	CreateTime   time DEFAULT current_time,
	UpdateUserId varchar(10) DEFAULT 'System',
	UpdateDate   date DEFAULT current_date,
	UpdateTime   time DEFAULT current_time,
	RowVersion   timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_Volunteer_VolunteerId PRIMARY KEY (VolunteerId)
);
