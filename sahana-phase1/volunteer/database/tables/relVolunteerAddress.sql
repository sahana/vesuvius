CREATE SEQUENCE seq_VolunteerAddress
       START 1
       INCREMENT 1;

CREATE TABLE relVolunteerAddress
(
	VolunteerAddressId integer DEFAULT nextval('seq_VolunteerAddress'::text) NOT NULL,
	VolunteerId        integer NOT NULL,
	AddressId          integer NOT NULL,
        CreateUserId       varchar(10) DEFAULT 'System',
	CreateDate         date DEFAULT current_date,
	CreateTime         time DEFAULT current_time,
	UpdateUserId       varchar(10) DEFAULT 'System',
	UpdateDate         date DEFAULT current_date,
	UpdateTime         time DEFAULT current_time,
        RowVersion         timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relVolunteerAddress_VolunteerAddressId PRIMARY KEY (VolunteerAddressId)
);

ALTER TABLE relVolunteerAddress
      ADD CONSTRAINT fk_relVolunteerAddress_Volunteer_VolunteerId
          FOREIGN KEY (VolunteerId)
          REFERENCES Volunteer (VolunteerId);

ALTER TABLE relVolunteerAddress
      ADD CONSTRAINT fk_relVolunteerAddress_Address_AddressId
          FOREIGN KEY (AddressId)
          REFERENCES Address (AddressId);
