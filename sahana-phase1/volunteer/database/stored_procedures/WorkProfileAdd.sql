CREATE OR REPLACE FUNCTION WorkProfileAdd
(
	integer,
	integer,
	integer
)
RETURNS INTEGER
AS '

DECLARE -- variables
	VolId    ALIAS FOR $1;
	FPC 	 ALIAS FOR $2;
	PermTemp ALIAS FOR $3;
BEGIN

	IF NOT EXISTS (SELECT *
			 FROM WorkProfile
			WHERE VolunteerId = VolId
			  AND FPC_Flag = FPC
			  AND PermTempFlag = PermTemp)
           THEN
		INSERT INTO WorkProfile
		(
			VolunteerId,
			FPC_Flag,
			PermTempFlag
		)
		VALUES
		(
			VolId,
			FPC,
			PermTemp
		);

	END IF;

		RETURN currval(''seq_WorkProfile''::text);

END
' LANGUAGE 'plpgsql'