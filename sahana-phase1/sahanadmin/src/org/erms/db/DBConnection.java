package org.erms.db;


import java.sql.Connection;

import java.sql.DriverManager;

import java.sql.SQLException;



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

    public static Connection createConnection() throws SQLException, Exception {

        Connection connection = null;
        String userName = DBConstantLoader.getDbUserName();
        String password = DBConstantLoader.getDbPassword();
        String url = DBConstantLoader.getDbUrl();

        Class.forName(DBConstantLoader.getDbDriver()).newInstance();
        connection = DriverManager.getConnection(url, userName, password);
        return connection;

    }

    public static void closeConnection(Connection connection)
    {
      try
      {
        if (connection != null)
          connection.close();
      }
      catch(Exception e){}
    }


}