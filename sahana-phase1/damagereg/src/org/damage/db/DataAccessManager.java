package org.damage.db;

import org.sahana.share.db.AbstractDataAccessManager;
import org.sahana.share.db.DBConnection;
import org.damage.business.DamagedHouseTO;
import org.damage.business.DamagedHouseMoreInfoTO;
import org.damage.business.HouseFacilityInfoTO;
import org.damage.business.SearchHouseTO;

import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.sql.*;


public class DataAccessManager extends AbstractDataAccessManager implements DBConstants {

    public DataAccessManager() throws Exception {
    }

    public boolean addDamagedHouse(DamagedHouseTO dhTO) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        boolean status = false;

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);
            preparedStatement = connection.prepareStatement(org.damage.db.SQLGenerator.getSQLForAddDamagedHouse());

            //preparedStatement.setString(1, dhTO.getDistrictCode());
            preparedStatement.setString(1, dhTO.getDistrictCode());
            preparedStatement.setString(2, dhTO.getDivision());
            preparedStatement.setString(3, dhTO.getGSN());
            preparedStatement.setString(4, dhTO.getOwner());
            preparedStatement.setDouble(5, dhTO.getDistanceFromSea());
            preparedStatement.setString(6, dhTO.getCity());
            preparedStatement.setString(7, dhTO.getNoAndStreet());
            preparedStatement.setString(8, dhTO.getCurrentAddress());
            preparedStatement.setDouble(9, dhTO.getFloorArea());
            preparedStatement.setInt(10, dhTO.getNoOfStories());
            preparedStatement.setString(11, dhTO.getTypeOfOwnership());
            preparedStatement.setInt(12, dhTO.getNoOfResidents());
            preparedStatement.setString(13, dhTO.getTypeOfConstruction());
            preparedStatement.setString(14, dhTO.getPropertyTaxNo());
            preparedStatement.setDouble(15, dhTO.getTotalDamagedCost());
            preparedStatement.setDouble(16, dhTO.getLandArea());
            preparedStatement.setBoolean(17, dhTO.getRelocate());
            preparedStatement.setBoolean(18, dhTO.getInsured());
            preparedStatement.setString(19, dhTO.getDamageType());
            preparedStatement.setString(20, dhTO.getComments());
            preparedStatement.executeUpdate();


            Iterator ite1 = dhTO.getDamagedHouseMoreInfoList().iterator();
            preparedStatement = connection.prepareStatement(org.damage.db.SQLGenerator.getSQLForAddDamagedHouse_Damage_Moreinfo());
            while(ite1.hasNext()) {
                DamagedHouseMoreInfoTO dhmInfoTO = (DamagedHouseMoreInfoTO) ite1.next();
                preparedStatement.setInt(1, dhmInfoTO.getHouseID());
                preparedStatement.setString(2, dhmInfoTO.getDamageInfo());

                preparedStatement.executeUpdate();
            }

            Iterator ite2 = dhTO.getHouseFacilityInfoList().iterator();
            preparedStatement = connection.prepareStatement(org.damage.db.SQLGenerator.getSQLForAddDamagedHouse_Facility_Info());
            while (ite2.hasNext()) {
                HouseFacilityInfoTO hfInfoTO = (HouseFacilityInfoTO) ite2.next();
                preparedStatement.setInt(1, hfInfoTO.getHouseID());
                preparedStatement.setString(2, hfInfoTO.getFacilityName());
                preparedStatement.setString(3, hfInfoTO.getDescription());
                preparedStatement.executeUpdate();
            }

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

    public List searchRequests(SearchHouseTO searchCriteria) throws SQLException, Exception {

        Connection connection = null;

        PreparedStatement preparedStatement = null;

        ResultSet resultSet = null;


        try {

            connection = DBConnection.createConnection();

            connection.setAutoCommit(false);



            // Setting the Request Header data.

            String sqlSearchString = SQLGenerator.getSQLForSearchCriteria();


            preparedStatement = connection.prepareStatement(sqlSearchString);
            preparedStatement.setString(1, searchCriteria.getDistrictCode());
            preparedStatement.setString(2, searchCriteria.getDistrictCode());
            preparedStatement.setString(3, searchCriteria.getDivision());
            preparedStatement.setString(4, searchCriteria.getDivision());
            preparedStatement.setString(5, searchCriteria.getGsn());
            preparedStatement.setString(6, ususalWildcard2SQLWildCard(searchCriteria.getGsn()));
            preparedStatement.setString(7, searchCriteria.getOwner());
            preparedStatement.setString(8, searchCriteria.getOwner());
            resultSet = preparedStatement.executeQuery();


            List returnSearchTOs = new ArrayList();
            while (resultSet.next()) {
               DamagedHouseTO requestSearchTo = new DamagedHouseTO();
                requestSearchTo.setDistrictCode(resultSet.getString(DBConstants.TableColumns.DISTRICT_CODE));
                requestSearchTo.setDivision(resultSet.getString(DBConstants.TableColumns.DIVISION ));
                requestSearchTo.setGsn(resultSet.getString(DBConstants.TableColumns.GSN ));
                requestSearchTo.setOwner(resultSet.getString(DBConstants.TableColumns.OWNER ));
                requestSearchTo.setDistanceFromSea(resultSet.getDouble(DBConstants.TableColumns.DISTANCE_FROM_SEA));
                requestSearchTo.setFloorArea(resultSet.getDouble(DBConstants.TableColumns.FLOOR_AREA));
                requestSearchTo.setNoOfStories(resultSet.getInt(DBConstants.TableColumns.NO_OF_STORIES ));
                requestSearchTo.setDamagedType(resultSet.getString(DBConstants.TableColumns.DAMAGE_TYPE ));
                requestSearchTo.setTypeOfOwnership(resultSet.getString(DBConstants.TableColumns.TYPE_OF_OWNERSHIP));
                requestSearchTo.setTypeOfConstruction(resultSet.getString(DBConstants.TableColumns.TYPE_OF_CONSTRUCTION ));
                requestSearchTo.setPropertyTaxNo(resultSet.getString(DBConstants.TableColumns.PROPERTY_TAX_NO));
                requestSearchTo.setTotalDamagedCost(resultSet.getDouble(DBConstants.TableColumns.TOTAL_DAMAGED_COST ));
                requestSearchTo.setLandArea(resultSet.getDouble(DBConstants.TableColumns.LAND_AREA ));
                requestSearchTo.setRelocate(resultSet.getBoolean(DBConstants.TableColumns.INSURED ));
                requestSearchTo.setDamagedType(resultSet.getString(DBConstants.TableColumns.DAMAGE_TYPE));
                requestSearchTo.setComments(resultSet.getString(DBConstants.TableColumns.COMMENTS ));
            }


            return returnSearchTOs;

        } finally {

            closeConnections(connection, preparedStatement, resultSet);

        }

    }

}
