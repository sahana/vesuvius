CREATE OR REPLACE FUNCTION VolunteerAddressAdd
(
	integer,
	integer
)
RETURNS INTEGER
AS '

DECLARE -- variables
        VolId ALIAS FOR $1;
	LocId ALIAS FOR $2;

BEGIN

	INSERT INTO relVolunteerAddress
	(
		VolunteerId,
		AddressId
	)
	SELECT VolId,
	       a.AddressId
	  FROM Address a
         WHERE a.LocationId = LocId
           AND a.AddressLine1 = ''''
           AND a.AddressLine2 = ''''
	   AND a.AddressLine3 = ''''
	   AND a.Location = ''''
	   AND a.State = ''''
	   AND a.Postcode = ''''
	   AND a.Country = ''''
	 LIMIT 1;

	RETURN currval(''seq_VolunteerAddress''::text);

END
' LANGUAGE 'plpgsql'