CREATE OR REPLACE FUNCTION WorkProfileDelete
(
	integer
)
RETURNS INTEGER
AS '

DECLARE -- variables
	PrId ALIAS FOR $1;

BEGIN

	DELETE FROM WorkProfile
	 WHERE WorkProfileId = PrId;

	RETURN 0;

END
' LANGUAGE 'plpgsql'