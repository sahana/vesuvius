CREATE OR REPLACE FUNCTION VolunteerSkillDelete
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

	DELETE FROM relVolunteerSkill
	 WHERE VolunteerId = VolId
	   AND SkillId = SkId;

	RETURN 0;

END
' LANGUAGE 'plpgsql'
