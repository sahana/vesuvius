CREATE SEQUENCE seq_ContactDetails
       START 1
       INCREMENT 1;

CREATE TABLE ContactDetails
(
	ContactDetailsId integer DEFAULT nextval('seq_ContactDetails'::text) NOT NULL,
	Email	         varchar(50) DEFAULT '',
	Phone            varchar(50) DEFAULT '',
	Mobile           varchar(50) DEFAULT '',
	CreateUserId     varchar(10) DEFAULT 'System',
	CreateDate       date DEFAULT current_date,
	CreateTime       time DEFAULT current_time,
	UpdateUserId     varchar(10) DEFAULT 'System',
	UpdateDate       date DEFAULT current_date,
	UpdateTime       time DEFAULT current_time,
	RowVersion       timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_ContactDetails_ContactDetailsId PRIMARY KEY (ContactDetailsId)
);
