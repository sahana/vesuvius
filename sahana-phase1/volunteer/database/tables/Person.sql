CREATE SEQUENCE seq_Person
       START 1
       INCREMENT 1;

CREATE TABLE Person
(
	PersonId      integer DEFAULT nextval('seq_Person'::text) NOT NULL,
	Title         integer NOT NULL,
	FirstName     varchar(50) NOT NULL,
	Surname       varchar(50) NOT NULL,
	DateOfBirth   date DEFAULT current_date NOT NULL,
	UserName      varchar(10) NOT NULL,
	Password      varchar(128) NOT NULL,
	ContactMethod integer NOT NULL,
	CreateUserId  varchar(10) DEFAULT 'System' NOT NULL,
	CreateDate    date DEFAULT current_date NOT NULL,
	CreateTime    time DEFAULT current_time NOT NULL,
	UpdateUserId  varchar(10) DEFAULT 'System' NOT NULL,
	UpdateDate    date DEFAULT current_date NOT NULL,
	UpdateTime    time DEFAULT current_time NOT NULL,
	RowVersion    timestamp DEFAULT current_timestamp NOT NULL,
	CONSTRAINT pk_Person PRIMARY KEY (PersonId)
);

ALTER TABLE Person
      ADD CONSTRAINT fk_Person_Code_Title
      FOREIGN KEY (Title)
      REFERENCES Code (CodeId);

ALTER TABLE Person
      ADD CONSTRAINT fk_Person_Code_ContactMethod
      FOREIGN KEY (ContactMethod)
      REFERENCES Code (CodeId);

CREATE UNIQUE INDEX ix_Person_UserName
    ON Person (UserName);

CREATE INDEX ix_Person_Password
    ON Person (Password);
