CREATE OR REPLACE FUNCTION StateAdd
(
	integer,
	varchar(50)
)
RETURNS INTEGER
AS '

DECLARE -- variables
	Con ALIAS FOR $1;
	Stt ALIAS FOR $2;
BEGIN

	IF NOT EXISTS (SELECT *
			 FROM Code
			WHERE CodeType = ''STAT''
			  AND CodeDescription = Stt)
           THEN
		INSERT INTO Code
		(
			CodeType,
			Code,
			CodeDescription
		)
		VALUES
		(
			''STAT'',
			'''',
			Stt
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
			''CNST'',
			Con,
			currval(''seq_Code''::text)
		);

	END IF;

		RETURN currval(''seq_Code''::text);

END
' LANGUAGE 'plpgsql'