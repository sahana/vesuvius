CREATE OR REPLACE FUNCTION OpportunityDelete
(
	integer
)
RETURNS INTEGER
AS '

DECLARE -- variables
	OppId ALIAS FOR $1;

BEGIN

	DELETE FROM relOpportunitySkill
	 WHERE OpportunityId = OppId;

	DELETE FROM relOpportunityAddress
	 WHERE OpportunityId = OppId;

	DELETE FROM Opportunity
	 WHERE OpportunityId = OppId;

	RETURN 0;

END
' LANGUAGE 'plpgsql'
