package org.sahana.share.db;

import java.sql.Connection;

import java.sql.DriverManager;

import java.sql.SQLException;




public class DBConnection {

    public static Connection createConnection() throws SQLException, Exception {
        Connection connection = null;
        String userName = DBConstantLoader.getDbUserName();
        String password = DBConstantLoader.getDbPassword();
        String url = DBConstantLoader.getDbUrl();
        Class.forName(DBConstantLoader.getDbDriver()).newInstance();
        connection = DriverManager.getConnection(url, userName, password);
        return connection;

    }
}

