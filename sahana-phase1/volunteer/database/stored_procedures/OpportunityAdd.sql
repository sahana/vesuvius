CREATE OR REPLACE FUNCTION OpportunityAdd
(
	integer,
	integer,
	integer,
	integer,
	integer
)
RETURNS INTEGER
AS '

DECLARE -- variables
	FPC      ALIAS FOR $1;
	PermTemp ALIAS FOR $2;
        SkId     ALIAS FOR $3;
	LocId    ALIAS FOR $4;
	Contact  ALIAS FOR $5;

BEGIN

	INSERT INTO Opportunity
	(
		OrganisationId,
		OrganisationContact,
		FPC_Flag,
		PermTempFlag
	)
	SELECT o.OrganisationId,
	       Contact,
	       FPC,
	       PermTemp
	  FROM Person p
	 INNER JOIN Opportunity o
	    ON p.PersonId = o.OrganisationContact
	 WHERE p.PersonId = Contact
	 LIMIT 1;

	INSERT INTO relOpportunitySkill
	(
		OpportunityId,
		SkillId
	)
	VALUES
	(
		currval(''seq_Opportunity''::text),
		SkId
	);

	INSERT INTO relOpportunityAddress
	(
		OpportunityId,
		AddressId
	)
	SELECT currval(''seq_Opportunity''::text),
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

	RETURN currval(''seq_Opportunity''::text);

END
' LANGUAGE 'plpgsql'