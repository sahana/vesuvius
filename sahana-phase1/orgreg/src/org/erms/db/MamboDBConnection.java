package org.erms.db;





import org.erms.business.RequestSearchCriteriaTO;

import org.erms.util.ERMSConstants;



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

public class MamboDBConnection {

    /**

     * This method creates the Connection.

     *

     * @return The created Connection

     * @throws Exception

     */

    public static Connection createConnection() throws SQLException, Exception {

        Connection connection = null;
        String userName = ERMSConstants.IMamboDataBaseConstants.dbUserName;
        String password = ERMSConstants.IMamboDataBaseConstants.dbPassword;
        String url = ERMSConstants.IMamboDataBaseConstants.dbURLConnectionString;

        Class.forName(ERMSConstants.IMamboDataBaseConstants.dbDriver).newInstance();
        connection = DriverManager.getConnection(url, userName, password);
        return connection;
    }



    /**

     * This method is purely for testing purposes.

     *

     * @param args

     */

    public static void main(String[] args) {
     DataAccessManager dataAccessManager = new DataAccessManager();
     RequestSearchCriteriaTO rqs = new RequestSearchCriteriaTO();
     rqs.setCategory("");
       try {
            dataAccessManager.searchRequests(rqs);
        }
        catch (SQLException e) {
            e.printStackTrace();
        }

        catch (Exception e) {
            e.printStackTrace();
        }
    }
}

