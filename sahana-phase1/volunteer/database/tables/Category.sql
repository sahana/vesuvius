CREATE SEQUENCE seq_Category
       START 1
       INCREMENT 1;


CREATE TABLE Category
(
	CategoryId   integer DEFAULT nextval('seq_Category'::text) NOT NULL,
	CategoryName varchar(50) NOT NULL,
	CreateUserId varchar(10) DEFAULT 'System',
	CreateDate   date DEFAULT current_date,
	CreateTime   time DEFAULT current_time,
	UpdateUserId varchar(10) DEFAULT 'System',
	UpdateDate   date DEFAULT current_date,
	UpdateTime   time DEFAULT current_time,
	RowVersion   timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_Category_CategoryId PRIMARY KEY (CategoryId)
);
