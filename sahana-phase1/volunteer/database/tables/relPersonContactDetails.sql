CREATE SEQUENCE seq_PersonContactDetails
       START 1
       INCREMENT 1;

CREATE TABLE relPersonContactDetails
(
	PersonContactDetailsId integer DEFAULT nextval('seq_PersonContactDetails'::text) NOT NULL,
	PersonId               integer NOT NULL,
	ContactDetailsId       integer NOT NULL,
        CreateUserId           varchar(10) DEFAULT 'System',
	CreateDate             date DEFAULT current_date,
	CreateTime             time DEFAULT current_time,
	UpdateUserId           varchar(10) DEFAULT 'System',
	UpdateDate             date DEFAULT current_date,
	UpdateTime             time DEFAULT current_time,
        RowVersion             timestamp DEFAULT current_timestamp,
        CONSTRAINT pk_relPersonContactDetails_PersonContactDetailsId PRIMARY KEY (PersonContactDetailsId)
);

ALTER TABLE relPersonContactDetails
      ADD CONSTRAINT fk_relPersonContactDetails_Person_PersonId
          FOREIGN KEY (PersonId)
          REFERENCES Person (PersonId);

ALTER TABLE relPersonContactDetails
      ADD CONSTRAINT fk_relPersonContactDetails_ContactDetails_ContactDetailsId
          FOREIGN KEY (ContactDetailsId)
          REFERENCES ContactDetails (ContactDetailsId);
