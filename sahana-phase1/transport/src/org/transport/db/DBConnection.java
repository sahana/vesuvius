package org.transport.db;


import org.transport.util.TRANSPORTConstants;
import org.transport.util.DBConnectionConstants;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

import java.util.ResourceBundle;
 


/**
 * 
 * User: Administrator
 * Date: Dec 30, 2004
 * Time: 8:57:36 PM
 * <p/>
 * This class is responsible for the creation and closure of data base connections.
 */
public class DBConnection {
    /**
     * This method creates the Connection.
     *
     * @return The created Connection
     * @throws Exception
     */
    static String userName;
    static String password;
    static String dbDriver;
    static String dbUrl;
    public static Connection createConnection() throws SQLException, Exception {


        Connection connection = null;
        System.out.println("userName:"+ userName + "\n");
        System.out.println("password:"+ password + "\n");
        System.out.println("dbUrl:"+ dbUrl + "\n");
        System.out.println("dbDriver:"+ dbDriver + "\n");

        initFromPropertyFile();


        Class.forName(dbDriver).newInstance();
        connection = DriverManager.getConnection(dbUrl, userName, password);

        System.out.println("Database connection established");

        return connection;
    }
 
    static private void initFromPropertyFile()
    {
        ResourceBundle dbParamBundle = ResourceBundle.getBundle("org.transport.db.db");
        userName = dbParamBundle.getString("db.username");
        password = dbParamBundle.getString("db.password");
        dbUrl= dbParamBundle.getString("db.url");
        dbDriver= dbParamBundle.getString("db.driver");

    }

    /**
     * This method is purely for testing purposes.
     *
     * @param args
     */
//    public static void main(String[] args) {
//
//        DataAccessManager dataAccessManager = new DataAccessManager();
//
//        RequestSearchCriteriaTO rqs = new RequestSearchCriteriaTO();
//
//        rqs.setCategory("");
//
//        try {
//            dataAccessManager.searchRequests(rqs);
//        }
//        catch (SQLException e) {
//
//            e.printStackTrace();
//        }
//        catch (Exception e) {
//
//            e.printStackTrace();
//        }
//    }
}
