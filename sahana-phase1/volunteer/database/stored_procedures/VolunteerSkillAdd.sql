CREATE OR REPLACE FUNCTION VolunteerSkillAdd
(
	integer,
	integer
)
RETURNS INTEGER
AS '

DECLARE -- variables
	VolId ALIAS FOR $1;
        SkId  ALIAS FOR $2;

BEGIN

	INSERT INTO relVolunteerSkill
	(
		VolunteerId,
		SkillId
	)
	VALUES
	(
		VolId,
		SkId
	);

	RETURN currval(''seq_VolunteerSkill''::text);

END
' LANGUAGE 'plpgsql'