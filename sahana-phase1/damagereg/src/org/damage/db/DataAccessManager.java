package org.damage.db;

import org.damage.business.DamagedHouseTO;
import org.erms.db.*;
import org.erms.db.DBConstants;
import org.erms.db.SQLGenerator;
import org.erms.business.KeyValueDTO;
import org.sahana.share.db.AbstractDataAccessManager;

import java.util.Collection;
import java.util.List;
import java.util.ArrayList;
import java.sql.*;


public class DataAccessManager extends AbstractDataAccessManager  implements DBConstants {

   public DataAccessManager() throws Exception{}
    
   public boolean addDamagedHouse(DamagedHouseTO  dhTO)throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        boolean status=false;

         try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);
            preparedStatement = connection.prepareStatement(org.damage.db.SQLGenerator.getSQLForAddDamagedHouse());

            preparedStatement.setString(1,dhTO.getDistrictCode());
            preparedStatement.setString(2,dhTO.getDivision());
             preparedStatement.setString(3,dhTO.getGSN());
             preparedStatement.setString(4,dhTO.getOwner());
             preparedStatement.setString(5,dhTO.getDistanceFromSea());
            preparedStatement.setString(6,dhTO.getCity());
             preparedStatement.setString(5,dhTO.getNoAndStreet());
             preparedStatement.setString(5,dhTO.getCurrentAddress());
             preparedStatement.setString(5,dhTO.getFloorArea());
             preparedStatement.setString(5,dhTO.getNoOfStories());
             preparedStatement.setString(5,dhTO.getTypeOfOwnership());
         preparedStatement.setString(5,dhTO.getNoOfResidents());
             preparedStatement.setString(5,dhTO.getTypeOfConstruction());
            preparedStatement.setString(5,dhTO.getPropertyTaxNo());
             preparedStatement.setString(5,dhTO.getTotalDamagedCost());
             preparedStatement.setString(5,dhTO.getLandArea());
             preparedStatement.setString(5,dhTO.getRelocate());
             preparedStatement.setString(5,dhTO.getInsured());
             preparedStatement.setString(5,dhTO.getDamageType());
             preparedStatement.setString(5,dhTO.getDamageType());

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





}
