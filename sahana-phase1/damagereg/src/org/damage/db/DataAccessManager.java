package org.damage.db;

import org.damage.business.DamagedHouseTO;
import org.erms.db.*;
import org.erms.db.DBConstants;
import org.erms.db.SQLGenerator;
import org.erms.business.KeyValueDTO;

import java.util.Collection;
import java.util.List;
import java.util.ArrayList;
import java.sql.*;


public class DataAccessManager implements DBConstants{

     public DataAccessManager() {
    }
   public boolean addDamagedHouse(DamagedHouseTO  dhTO)throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        boolean status=false;

         try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);
            preparedStatement = connection.prepareStatement(org.damage.db.SQLGenerator.getSQLForAddDamagedHouse());

          } catch (Exception e) {
            try {
                if (connection != null) {
                    connection.rollback();
                    connection.setAutoCommit(true);
                    status = false;

                }

            } catch (SQLException e1) {
                e1.printStackTrace();
                status = false;
                throw e1;

            }
            status = false;
            e.printStackTrace();

        } finally {
            closeStatement(preparedStatement);
            closeConnection(connection);
        }
        return status;
    }
    //list oif house dtos
    //public List searchHouses(SearchHouseTO);


     private Collection loadAllDistricts() throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        List districtDTOs = new ArrayList();
        Statement s = null;
        ResultSet rs = null;
        try {

            String sql = org.erms.db.SQLGenerator.getSQLForAllDistricts();
            s = conn.createStatement();
            rs = s.executeQuery(sql);
            String itemCode = null;
            String itemName = null;
            KeyValueDTO dto = null;


            while (rs.next()) {
                itemCode = rs.getString(DBConstants.TableColumns.DISTRICT_CODE);
                itemName = rs.getString(DBConstants.TableColumns.DISTRICT_NAME);
                dto = new KeyValueDTO();
                dto.setDbTableCode(itemCode);
                dto.setDisplayValue(itemName);
                districtDTOs.add(dto);
            }
        } finally {
            closeConnections(conn, s, rs);
        }


        return districtDTOs;

    }


    private static void closeResultSet(ResultSet resultSet) {
        // close the result set
        if (resultSet != null) {
            try {
                resultSet.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }


    private static void closeConnection(Connection connection) {
        // close the connection
        if (connection != null) {
            try {
                connection.close();
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
        closeResultSet(resultSet);
        closeStatement(statement);
        closeConnection(connection);
    }


    private static void closeStatement(Statement statement) {
        // close the statement
        if (statement != null) {
            try {
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }


}
