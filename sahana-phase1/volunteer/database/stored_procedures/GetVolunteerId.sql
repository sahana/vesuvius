CREATE OR REPLACE FUNCTION GetVolunteerId (varchar(10), varchar(128))
RETURNS INTEGER
AS '

DECLARE -- variables
	uname  ALIAS FOR $1;
	passwd ALIAS FOR $2;
	IID    integer;

BEGIN

	SELECT vp.VolunteerId
          INTO IID
	  FROM Person p
         INNER JOIN relVolunteerPerson vp
	    ON p.PersonId = vp.PersonId
	 WHERE UserName = uname
           AND Password = passwd;

        RETURN IID;

END
' LANGUAGE plpgsql