CREATE OR REPLACE FUNCTION VolunteerAddressDelete
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

	DELETE FROM relVolunteerAddress
         WHERE VolunteerAddressId = (SELECT VolunteerAddressId
				       FROM Address a
				      INNER JOIN relVolunteerAddress va
					 ON a.AddressId = va.AddressId
				      WHERE a.LocationId = LocId
					AND a.AddressLine1 = ''''
					AND a.AddressLine2 = ''''
					AND a.AddressLine3 = ''''
					AND a.Location = ''''
					AND a.State = ''''
					AND a.Postcode = ''''
					AND a.Country = ''''
				      LIMIT 1);

	RETURN 0;

END
' LANGUAGE 'plpgsql'