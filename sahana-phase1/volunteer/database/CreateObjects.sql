\t

\o output;

-- get tables
SELECT CASE ObjectType
            WHEN 'Table' THEN '\\i tables/' || ObjectName || '.sql;'
            WHEN 'StoredProcedure' THEN '\\i stored_procedures/' || ObjectName || '.sql;'
            WHEN 'Function' THEN '\\i functions/' || ObjectName || '.sql;'
            WHEN 'Type' THEN '\\i datatypes/' || ObjectName || '.sql;'
            WHEN 'Trigger' THEN '\\i triggers/' || ObjectName || '.sql;'
        END -- CASE
  FROM DBObject
 WHERE DBName = 'skillsregister'
 ORDER BY CreateOrder ASC;