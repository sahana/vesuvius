CREATE OR REPLACE FUNCTION RegionAdd
(
	integer,
	varchar(50)
)
RETURNS INTEGER
AS '

DECLARE -- variables
	Stt ALIAS FOR $1;
	Reg ALIAS FOR $2;
BEGIN

	IF NOT EXISTS (SELECT *
			 FROM Code
			WHERE CodeType = ''LOCT''
			  AND CodeDescription = Reg)
           THEN
		INSERT INTO Code
		(
			CodeType,
			Code,
			CodeDescription
		)
		VALUES
		(
			''LOCT'',
			'''',
			Reg
		);

		INSERT INTO Address
		(
			LocationId
		)
		VALUES
		(
			currval(''seq_Code''::text)
		);

		INSERT INTO RelatedCode
		(
			Relationship,
			ParentCodeId,
			ChildCodeId
		)
		VALUES
		(
			''STRG'',
			Stt,
			currval(''seq_Code''::text)
		);

	END IF;

		RETURN currval(''seq_Code''::text);

END
' LANGUAGE 'plpgsql'