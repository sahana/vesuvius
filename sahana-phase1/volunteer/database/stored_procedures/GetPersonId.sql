CREATE OR REPLACE FUNCTION GetPersonId (varchar(10), varchar(128))
RETURNS INTEGER
AS '

DECLARE -- variables
	uname  ALIAS FOR $1;
	passwd ALIAS FOR $2;
	IID    integer;

BEGIN

	SELECT PersonId
          INTO IID
	  FROM Person
	 WHERE UserName = uname
           AND Password = passwd;

        RETURN IID;

END
' LANGUAGE plpgsql