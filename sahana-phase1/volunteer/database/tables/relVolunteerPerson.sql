CREATE SEQUENCE seq_VolunteerPerson
       START 1
       INCREMENT 1;

CREATE TABLE relVolunteerPerson
(
	VolunteerPersonId integer DEFAULT nextval('seq_VolunteerPerson'::text) NOT NULL,
	VolunteerId       integer NOT NULL,
	PersonId          integer NOT NULL,
        CreateUserId      varchar(10) DEFAULT 'System',
	CreateDate        date DEFAULT current_date,
	CreateTime        time DEFAULT current_time,
	UpdateUserId      varchar(10) DEFAULT 'System',
	UpdateDate        date DEFAULT current_date,
	UpdateTime        time DEFAULT current_time,
        RowVersion        timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relVolunteerPerson_VolunteerPersonId PRIMARY KEY (VolunteerPersonId)
);

ALTER TABLE relVolunteerPerson
      ADD CONSTRAINT fk_relVolunteerPerson_Volunteer_VolunteerId
          FOREIGN KEY (VolunteerId)
          REFERENCES Volunteer (VolunteerId);

ALTER TABLE relVolunteerPerson
      ADD CONSTRAINT fk_relVolunteerPerson_Person_PersonId
          FOREIGN KEY (PersonId)
          REFERENCES Person (PersonId);
