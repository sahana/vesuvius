CREATE SEQUENCE seq_RelatedCode
       START 1
       INCREMENT 1;

CREATE TABLE RelatedCode
(
	RelatedCodeId integer DEFAULT nextval('seq_RelatedCode'::text) NOT NULL,
	Relationship  char(4) NOT NULL,
	ParentCodeId  integer NOT NULL,
	ChildCodeId   integer NOT NULL,
	CreateUserId  varchar(10) DEFAULT 'System',
	CreateDate    date DEFAULT current_date,
	CreateTime    time DEFAULT current_time,
	UpdateUserId  varchar(10) DEFAULT 'System',
	UpdateDate    date DEFAULT current_date,
	UpdateTime    time DEFAULT current_time,
	RowVersion    timestamp DEFAULT current_timestamp,
	CONSTRAINT pk_RelatedCode_RelatedCodeId PRIMARY KEY (RelatedCodeId)
);

ALTER TABLE RelatedCode
      ADD CONSTRAINT fk_RelatedCode_Code_ParentCodeId
          FOREIGN KEY (ParentCodeId)
          REFERENCES Code (CodeId);

ALTER TABLE RelatedCode
      ADD CONSTRAINT fk_RelatedCode_Code_ChildCodeId
          FOREIGN KEY (ChildCodeId)
          REFERENCES Code (CodeId);