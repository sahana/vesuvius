CREATE SEQUENCE seq_Organisation
       START 1
       INCREMENT 1;

CREATE TABLE Organisation
(
	OrganisationId   integer DEFAULT nextval('seq_Organisation'::text) NOT NULL,
	OrganisationName varchar(128) DEFAULT '',
	CreateUserId     varchar(10) DEFAULT 'System',
	CreateDate       date DEFAULT current_date,
	CreateTime       time DEFAULT current_time,
	UpdateUserId     varchar(10) DEFAULT 'System',
	UpdateDate       date DEFAULT current_date,
	UpdateTime       time DEFAULT current_time,
	RowVersion       timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_Organisation_OrganisationId PRIMARY KEY (OrganisationId)
);