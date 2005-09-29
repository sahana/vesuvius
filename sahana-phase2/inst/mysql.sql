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


-- PEOPLE
CREATE TABLE cre_people(
	id BIGINT NOT NULL AUTO_INCREMENT,
	firstname VARCHAR(40),
	lastame VARCHAR(100),
    othernames TEXT,
    email VARCHAR(255),
    address TEXT,
	PRIMARY KEY (id)
);

-- USERS
CREATE TABLE cre_users(
    userid BIGINT NOT NULL,
	username VARCHAR(10) NOT NULL,
	password VARCHAR(40) NOT NULL,
	PRIMARY KEY (userid),
	FOREIGN KEY (userid) REFERENCES cre_people(id)
);

/* CORE LOG SCHEMA */

	-- USER LOGS
	CREATE TABLE cre_userlog(
		user_logid BIGINT NOT NULL AUTO_INCREMENT,
		userid BIGINT NOT NULL,
		ip VARCHAR( 15 ) NOT NULL,
		logintime TIMESTAMP NOT NULL DEFAULT NOW(),
		PRIMARY KEY(user_logid),
		FOREIGN KEY (userid) REFERENCES cre_users (userid)
	);
	
	-- ERROR LOG
	CREATE TABLE cre_errorlog(
		error_logid BIGINT NOT NULL AUTO_INCREMENT,
		user_logid BIGINT NOT NULL,
		severity VARCHAR(10) NOT NULL,
		file TEXT  NOT NULL,
		time TIMESTAMP NOT NULL DEFAULT NOW(),
		message TEXT NOT NULL,
		line INT NOT NULL,
		PRIMARY KEY (error_logid),
		FOREIGN KEY (user_logid) REFERENCES cre_userlog(user_logid)
	);
	
	-- ACTION LOG 
	CREATE TABLE cre_actionlog(
	    action_logid BIGINT NOT NULL AUTO_INCREMENT,
	    userid BIGINT NOT NULL,
	    user_logid BIGINT NOT NULL,
	    message TEXT NOT NULL,
	    loglevel VARCHAR(10) NOT NULL,
        module VARCHAR(50) NOT NULL,
	    date timestamp NOT NULL DEFAULT NOW(),
	    PRIMARY KEY (action_logid),
	    FOREIGN KEY (user_logid) REFERENCES cre_userlog(user_logid)
	);
	
	-- DEBUG LOG
	CREATE TABLE cre_debuglog(
	    debug_logid BIGINT NOT NULL AUTO_INCREMENT,
	    userid BIGINT NOT NULL,
	    user_logid BIGINT NOT NULL,
	    action VARCHAR (100) NOT NULL,
	    modulename VARCHAR(50) NOT NULL,
	    date timestamp NOT NULL DEFAULT NOW(),
	    data TEXT,
	    PRIMARY KEY (debug_logid),
	    FOREIGN KEY (user_logid) REFERENCES cre_userlog(user_logid)
	);
	
/**** CORE LOG SCHEMA END *****/

-- MODULES
CREATE TABLE cre_modules(
	moduleid BIGINT NOT NULL AUTO_INCREMENT,
	name VARCHAR(50) NOT NULL,
	description TEXT,
	version VARCHAR(10) NOT NULL,
	active BOOL NOT NULL DEFAULT 0 ,
	PRIMARY KEY (moduleid)
);

--CUSTOM MODULE CONFIGURATIONS
CREATE TABLE cre_config(
	configid BIGINT NOT NULL AUTO_INCREMENT,
	config_group VARCHAR(100),
	name VARCHAR(50) NOT NULL,
	value TEXT,
	description TEXT,
	type VARCHAR(10),
	moduleid BIGINT,
	PRIMARY KEY(configid),
	FOREIGN KEY (moduleid) REFERENCES cre_modules (moduleid)
);

--CUSTOM CONFIGURATION LISTS (SELECT)
CREATE TABLE cre_configlist(
	description TEXT NOT NULL,
	value VARCHAR(50),
	configid BIGINT NOT NULL,
	FOREIGN KEY (configid) REFERENCES cre_config (configid)
);

/* Location Classification */

CREATE TABLE cre_location_type(
    location_typeid BIGINT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    PRIMARY KEY (location_typeid)
);

CREATE TABLE cre_location(
    locationid BIGINT NOT NULL AUTO_INCREMENT,
    parentid BIGINT DEFAULT 0,
    location_typeid BIGINT NOT NULL,
    name VARCHAR(100) NOT NULL,
    value VARCHAR(50), -- for dropdowns if needed
    decription TEXT,
    PRIMARY KEY (locationid),
    FOREIGN KEY (location_typeid) REFERENCES cre_location_type(location_typeid)
);


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

