/*

* Created on Dec 30, 2004

*

* To change the template for this generated file go to

* Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

*/

package org.erms.db;


import org.erms.business.*;


import java.sql.*;

import java.util.ArrayList;

import java.util.Collection;

import java.util.Iterator;

import java.util.List;


/**
 * @author Administrator
 *         <p/>
 *         <p/>
 *         <p/>
 *         To change the template for this generated type comment go to
 *         <p/>
 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

public class MamboDataAccessManager implements DBConstants {
    public MamboDataAccessManager() {
    }

    public void addUserToMamboDatabase(String fullName,String userName, String password, String email) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;


        try {
            connection = MamboDBConnection.createConnection();
            connection.setAutoCommit(false);
            String sql1 = "insert into mos_users(name,userName,email,password,registerDate,gid) values(?,?,?,?,?,18)";
            String sql2 = "insert into mos_core_acl_aro  (section_value, value, order_value, name, hidden)" +
                        " values ('users', last_insert_id(), 0, ?, 0)";
            preparedStatement =  connection.prepareStatement(sql1);
            preparedStatement.setString(1,fullName);
            preparedStatement.setString(2,userName);
            preparedStatement.setString(3,email);
            preparedStatement.setString(4,MD5toHexConverter.md5(password));
            preparedStatement.setDate(5,new Date(new java.util.Date().getTime()));

            preparedStatement.executeUpdate();

            preparedStatement =  connection.prepareStatement(sql2);
            preparedStatement.setString(1,fullName);
            preparedStatement.executeUpdate();

            // If all is ok then commit.
            connection.commit();
            connection.setAutoCommit(true);

        } catch (Exception e) {
            try {
                if (connection != null) {
                    connection.rollback();
                    connection.setAutoCommit(true);
                }

            } catch (SQLException e1) {
                e1.printStackTrace();
                throw e1;

            }

            throw e;

        } finally {

            closeConnections(connection, preparedStatement, resultSet);

        }
    }

    private static void closeConnection(Connection connection) {
        if (connection != null) {
            try {
                connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }

        }

    }

    private static void closeStatement(Statement statement) {
        if (statement != null) {
            try {
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    private static void closeResultSet(ResultSet resultSet) {
        if (resultSet != null) {
            try {
                resultSet.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * Closes the open connections
     *
     * @param connection
     * @param resultSet
     */

    private static void closeConnections(Connection connection, Statement statement, ResultSet resultSet) {
        closeConnection(connection);
        closeStatement(statement);
        closeResultSet(resultSet);


    }
}

