\t

\o output;

-- get table permissions
SELECT /* CASE ObjectName
            WHEN 'Match' THEN 'GRANT SELECT, INSERT ON ' || ObjectName || ' TO "www-data";'
            ELSE 'GRANT SELECT, INSERT, UPDATE ON ' || ObjectName || ' TO "www-data";'
        END -- CASE */
       'GRANT SELECT, INSERT, UPDATE, DELETE ON ' || ObjectName || ' TO "www-data";'
  FROM DBObject
 WHERE DBName = 'skillsregister'
   AND ObjectType = 'Table'
 ORDER BY CreateOrder ASC;

-- get sequence permissions
SELECT CASE substring(ObjectName FROM 1 FOR 3)
            WHEN 'rel' THEN 'GRANT SELECT, UPDATE ON seq_' || substring(ObjectName FROM 4 FOR (char_length(ObjectName)-3)) || ' TO "www-data";'
            ELSE 'GRANT SELECT, UPDATE ON seq_' || ObjectName || ' TO "www-data";'
        END -- CASE
  FROM DBObject
 WHERE DBName = 'skillsregister'
   AND ObjectType = 'Table'
 ORDER BY CreateOrder ASC;

SELECT 'GRANT SELECT, UPDATE ON seq_pk_Match TO "www-data";';