CREATE OR REPLACE FUNCTION SkillAdd
(
	varchar(50)
)
RETURNS INTEGER
AS '

DECLARE -- variables
	SkName  ALIAS FOR $1;

BEGIN

	INSERT INTO Skill
	(
		SkillName
	)
	VALUES
	(
		SkName
	);

	RETURN currval(''seq_Skill''::text);

END
' LANGUAGE 'plpgsql'