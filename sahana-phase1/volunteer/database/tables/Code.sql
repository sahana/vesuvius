CREATE SEQUENCE seq_Code
       START 1
       INCREMENT 1;

CREATE TABLE Code
(
	CodeId          integer DEFAULT nextval('seq_Code'::text) NOT NULL,
	CodeType        char(4) NOT NULL,
	Code            varchar(10) NOT NULL,
	CodeDescription varchar(128) DEFAULT '',
	CreateUserId    varchar(10) DEFAULT 'System',
	CreateDate      date DEFAULT current_date,
	CreateTime      time DEFAULT current_time,
	UpdateUserId    varchar(10) DEFAULT 'System',
	UpdateDate      date DEFAULT current_date,
	UpdateTime	time DEFAULT current_time,
	RowVersion      timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_Code_CodeId PRIMARY KEY (CodeId)
);
