CREATE OR REPLACE FUNCTION CountryAdd
(
	varchar(50)
)
RETURNS INTEGER
AS '

DECLARE -- variables
	Con   ALIAS FOR $1;
BEGIN

	IF NOT EXISTS (SELECT *
			 FROM Code
			WHERE CodeType = ''CTRY''
			  AND CodeDescription = Con)
           THEN
		INSERT INTO Code
		(
			CodeType,
			Code,
			CodeDescription
		)
		VALUES
		(
			''CTRY'',
			'''',
			Con
		);

		INSERT INTO Address
		(
			LocationId
		)
		VALUES
		(
			currval(''seq_Code''::text)
		);

	END IF;

		RETURN currval(''seq_Code''::text);

END
' LANGUAGE 'plpgsql'