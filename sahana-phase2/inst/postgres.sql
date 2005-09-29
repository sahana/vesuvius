/* Make Sure We are Using ISO-8601 */
set DateStyle to ISO;

/* CORE SCHEMA */
/* prefix : cre_ */

-- SESSIONS
CREATE TABLE cre_sessions(
	sesskey VARCHAR(32) NOT NULL,
	expiry INT NOT NULL,
	expireref VARCHAR(64),
	data TEXT NOT NULL,
	PRIMARY KEY (sesskey)
);

COMMENT ON TABLE cre_sessions IS 'Session Data';


-- PEOPLE
CREATE TABLE cre_people(
	id BIGSERIAL NOT NULL,
	firstname VARCHAR(40),
	lastame VARCHAR(100),
    othernames TEXT,
    email VARCHAR(255),
    address TEXT,
	PRIMARY KEY (id)
);

COMMENT ON TABLE cre_people IS 'People List (will change later as the DVR comes in)';

-- USERS
CREATE TABLE cre_users(
    userid BIGINT NOT NULL,
	username VARCHAR(10) NOT NULL,
	password VARCHAR(40) NOT NULL,
	PRIMARY KEY (userid),
	FOREIGN KEY (userid) REFERENCES cre_people(id)
);

COMMENT ON TABLE cre_users IS 'User Information';

/* CORE LOG SCHEMA */

	-- USER LOGS
	CREATE TABLE cre_userlog(
		user_logid BIGSERIAL NOT NULL,
		userid BIGINT NOT NULL,
		ip inet NOT NULL,
		logintime TIMESTAMP NOT NULL DEFAULT NOW(),
		PRIMARY KEY(user_logid),
		FOREIGN KEY (userid) REFERENCES cre_users (userid)
	);
	
	COMMENT ON TABLE cre_userlog IS 'User login Log';
	
	-- ERROR LOG
	CREATE TABLE cre_errorlog(
		error_logid BIGSERIAL NOT NULL,
		user_logid BIGINT NOT NULL,
		severity VARCHAR(10) NOT NULL,
		file TEXT  NOT NULL,
		time TIMESTAMP NOT NULL DEFAULT NOW(),
		message TEXT NOT NULL,
		line INT NOT NULL,
		PRIMARY KEY (error_logid),
		FOREIGN KEY (user_logid) REFERENCES cre_userlog(user_logid)
	);
	
	COMMENT ON TABLE cre_errorlog IS 'Loggs System Error logs';
	
	-- ACTION LOG 
	CREATE TABLE cre_actionlog(
	    action_logid BIGSERIAL NOT NULL,
	    userid BIGINT NOT NULL,
	    user_logid BIGINT NOT NULL,
	    message TEXT NOT NULL,
	    loglevel VARCHAR(10) NOT NULL,
        module VARCHAR(50) NOT NULL,
	    date timestamp NOT NULL DEFAULT NOW(),
	    PRIMARY KEY (action_logid),
	    FOREIGN KEY (user_logid) REFERENCES cre_userlog(user_logid)
	);
	
	COMMENT ON TABLE cre_actionlog IS 'User Action Log';
	
	-- DEBUG LOG
	CREATE TABLE cre_debuglog(
	    debug_logid BIGSERIAL NOT NULL,
	    userid BIGINT NOT NULL,
	    user_logid BIGINT NOT NULL,
	    action VARCHAR (100) NOT NULL,
	    modulename VARCHAR(50) NOT NULL,
	    date timestamp NOT NULL DEFAULT NOW(),
	    data TEXT,
	    PRIMARY KEY (debug_logid),
	    FOREIGN KEY (user_logid) REFERENCES cre_userlog(user_logid)
	);
	
	COMMENT ON TABLE cre_debuglog IS 'Debug User actions';
	
/**** CORE LOG SCHEMA END *****/

-- MODULES
CREATE TABLE cre_modules(
	moduleid BIGSERIAL NOT NULL,
	name VARCHAR(50) NOT NULL,
	description TEXT,
	version VARCHAR(10) NOT NULL,
	active BOOL NOT NULL DEFAULT FALSE ,
	PRIMARY KEY (moduleid)
);

COMMENT ON TABLE cre_modules IS 'Module Information';

--CUSTOM MODULE CONFIGURATIONS
CREATE TABLE cre_config(
	configid BIGSERIAL NOT NULL,
	config_group VARCHAR(100),
	name VARCHAR(50) NOT NULL,
	value TEXT,
	description TEXT,
	type VARCHAR(10),
	moduleid BIGINT,
	PRIMARY KEY(configid),
	FOREIGN KEY (moduleid) REFERENCES cre_modules (moduleid)
);

COMMENT ON TABLE cre_config IS 'Module Configurations';

--CUSTOM CONFIGURATION LISTS (SELECT)
CREATE TABLE cre_configlist(
	description TEXT NOT NULL,
	value VARCHAR(50),
	configid BIGINT NOT NULL,
	FOREIGN KEY (configid) REFERENCES cre_config (configid)
);

COMMENT ON TABLE cre_configlist IS 'Configuration List';

/* Location Classification */

CREATE TABLE cre_location_type(
    location_typeid BIGSERIAL NOT NULL,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    PRIMARY KEY (location_typeid)
);

COMMENT ON TABLE cre_location_type IS 'Types of Locations';


CREATE TABLE cre_location(
    locationid BIGSERIAL NOT NULL,
    parentid BIGINT DEFAULT 0,
    location_typeid BIGINT NOT NULL,
    name VARCHAR(100) NOT NULL,
    value VARCHAR(50), -- for dropdowns if needed
    decription TEXT,
    PRIMARY KEY (locationid),
    FOREIGN KEY (location_typeid) REFERENCES cre_location_type(location_typeid)
);

COMMENT ON TABLE cre_location IS 'Location Classification Table';


/******************/

-- OPTIMIZATION  (DEVEL)
CREATE TABLE devel_logsql (
		  created timestamp NOT NULL DEFAULT NOW(),
		  sql0 varchar(250) NOT NULL,
		  sql1 text NOT NULL,
		  params text NOT NULL,
		  tracer text NOT NULL,
		  timer decimal(16,6) NOT NULL
);

COMMENT ON TABLE devel_logsql IS 'log sql for optimization';

