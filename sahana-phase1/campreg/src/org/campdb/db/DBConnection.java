package org.campdb.db;


import org.campdb.util.CAMPDBConstants;
import org.campdb.util.DBConnectionConstants;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

//import java.util.Properties;
//import java.io.InputStream;
//import java.io.IOException;
//import java.io.FileInputStream;
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
     */
    static String userName;
    static String password;
    static String dbDriver;
    static String dbUrl;
    static Connection connection;
    public static Connection createConnection() throws SQLException, Exception {

        initFromPropertyFile();
        Class.forName(dbDriver).newInstance();
        connection = DriverManager.getConnection(dbUrl, userName, password);

        return connection;
    }
 
    /*static private void initFromPropertyFile()
    {
        //final String PROPFILE= "/home/damitha/programs/jakarta-tomcat-4.1.27/webapps/campdb/conf/Application.properties";
        final String PROPFILE= "webapps/campdb/conf/Application.properties";
        InputStream propsFile;
        Properties dbProp = new Properties();

        try {
            //System.out.println("PROPFILE:" + PROPFILE + "\n");
            propsFile = new FileInputStream(PROPFILE);
            dbProp.load(propsFile);
            propsFile.close();
            userName = dbProp.getProperty("user");
            password = dbProp.getProperty("password");
            
        } catch (IOException ioe) {
            System.out.println("I/O Exception.");
            ioe.printStackTrace();
        }
       
    }*/

    static private void initFromPropertyFile()
    {
        ResourceBundle dbParamBundle = ResourceBundle.getBundle("org.campdb.db.db");
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
