CREATE SEQUENCE seq_VolunteerLocation
       START 1
       INCREMENT 1;

CREATE TABLE relVolunteerLocation
(
	VolunteerLocationId integer DEFAULT nextval('seq_VolunteerLocation'::text) NOT NULL,
	VolunteerId         integer NOT NULL,
	LocationId            integer NOT NULL,
        CreateUserId          varchar(10) DEFAULT 'System',
	CreateDate            date DEFAULT current_date,
	CreateTime            time DEFAULT current_time,
	UpdateUserId          varchar(10) DEFAULT 'System',
	UpdateDate            date DEFAULT current_date,
	UpdateTime            time DEFAULT current_time,
        RowVersion            timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relVolunteerLocation_VolunteerLocationId PRIMARY KEY (VolunteerLocationId)
);

ALTER TABLE relVolunteerLocation
      ADD CONSTRAINT fk_relVolunteerLocation_Volunteer_VolunteerId
          FOREIGN KEY (VolunteerId)
          REFERENCES Volunteer (VolunteerId);

ALTER TABLE relVolunteerLocation
      ADD CONSTRAINT fk_relVolunteerLocation_Code_CodeId
          FOREIGN KEY (LocationId)
          REFERENCES Code (CodeId);
