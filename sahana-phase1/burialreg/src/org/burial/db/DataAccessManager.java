package org.burial.db;

import org.burial.business.KeyValueDTO;
import org.burial.business.UserTO;
import org.burial.business.BurialSiteDetailTO;
import org.sahana.share.db.DBConnection;

import java.sql.*;
import java.util.*;

/*
* Created on Jan 2, 2005
*
*/

public class DataAccessManager {


    protected static DataAccessManager instance = null;

    protected final HashMap districtMap = new HashMap();
    protected final HashMap divisionMap = new HashMap();
    protected final HashMap provinceMap = new HashMap();

    protected final ArrayList districts = new ArrayList();
    protected final ArrayList divsions = new ArrayList();
    protected final ArrayList provinces = new ArrayList();


    private DataAccessManager() {
    }


    public static DataAccessManager getInstance() {
        if (instance == null)
            instance = new DataAccessManager();
        return instance;

    }



    private Connection createConnection() throws SQLException {
        try {
            return DBConnection.createConnection();
        } catch (SQLException e) {
            throw e;
        }catch (Exception e) {
            throw new SQLException(e.getMessage());
        }

    }



//    protected int executeUpdate(String sql) throws SQLException {
//        Statement stmt = null;
//        try {
//            stmt = createConnection().createStatement();
//            return stmt.executeUpdate(sql);
//            close(stmt);
//        }catch(Exception e){}
//
//    }


    public boolean insertSite(BurialSiteDetailTO site) throws SQLException {
        Connection connection = null;
        PreparedStatement   preparedStatement = null;
        try {

            connection = createConnection();
            String sqlAddRequestHeaderString = SQLGenerator.getSQLForInsertSiteDTO();
            System.out.println(sqlAddRequestHeaderString);

            preparedStatement = connection.prepareStatement(sqlAddRequestHeaderString);

            preparedStatement.setString(1, site.getProvinceCode());
            preparedStatement.setString(2, site.getDistrictCode());
            preparedStatement.setString(3, site.getDivisionCode());
            preparedStatement.setString(4, site.getArea());
            preparedStatement.setString(5, site.getSitedescription());
            preparedStatement.setString(6, site.getBurialdetail());
            preparedStatement.setInt(7, site.getBodyCountTotal());
            preparedStatement.setInt(8, site.getBodyCountMmen());
            preparedStatement.setInt(9, site.getBodyCountWomen());
            preparedStatement.setInt(10, site.getBodyCountChildren());
            preparedStatement.setString(11, site.getGpsLattitude());
            preparedStatement.setString(12, site.getGpsLongitude());
            preparedStatement.setString(13, site.getAuthorityPersonName());
            preparedStatement.setString(14, site.getAuthorityName());
            preparedStatement.setString(15, site.getAuthorityPersonRank());
            preparedStatement.setString(16, site.getAuthorityReference());

            preparedStatement.executeUpdate();
        } finally{
            closeStatement(preparedStatement);
            closeConnection(connection);
        }
        return true;
    }


    public Collection getAllSites() throws SQLException {
        Connection connection = null;
        Statement   statement = null;
        ArrayList sites = new ArrayList();
        ResultSet resultset=null;
        try {
            connection = createConnection();
            String sqlGetAllSites = SQLGenerator.getSQLForAllSites();

            statement = connection.createStatement();
            resultset = statement.executeQuery(sqlGetAllSites);

            while(resultset.next()){
                BurialSiteDetailTO burialSiteDetailTO = new BurialSiteDetailTO();
                burialSiteDetailTO.setBurialSiteCode(resultset.getInt(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_CODE));
                burialSiteDetailTO.setProvinceCode(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_PROVINCE));
                burialSiteDetailTO.setDistrictCode(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_DISTRICT));
                burialSiteDetailTO.setDivisionCode(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_DEVISION));
                burialSiteDetailTO.setArea(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AREA));
                burialSiteDetailTO.setSitedescription(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_SITE_DESCRIPTION));

                burialSiteDetailTO.setBurialdetail(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BURIAL_DETAIL));
                burialSiteDetailTO.setBodyCountTotal(resultset.getInt(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODY_COUNT_TOTEL));
                burialSiteDetailTO.setBodyCountMmen(resultset.getInt(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_MEN ));
                burialSiteDetailTO.setBodyCountWomen(resultset.getInt(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_WOMEN));
                burialSiteDetailTO.setBodyCountChildren(resultset.getInt(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_CHILDREAN ));

                burialSiteDetailTO.setGpsLattitude(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_GPRS_LATTATUDE));
                burialSiteDetailTO.setGpsLongitude(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_GPRS_LONGATIUDE ));
                burialSiteDetailTO.setAuthorityPersonName(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_PERSON_NAME));
                burialSiteDetailTO.setAuthorityName(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_NAME));

                burialSiteDetailTO.setAuthorityPersonRank(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_PERSON_RANK));
                burialSiteDetailTO.setAuthorityReference(resultset.getString(DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_REFERANCE ));
                sites.add(burialSiteDetailTO);
            }


        }finally{
            closeConnections(connection,statement,resultset);
        }
        return sites;
    }


    public UserTO loginSuccess(String userName, String password) throws SQLException, Exception {
        Connection conn = createConnection();
        Statement s =  null;
        ResultSet rs = null;
        try {
            String sql = SQLGenerator.getSQLForLogin(userName);
            s = conn.createStatement();
            rs = s.executeQuery(sql);

            if (rs.next()) {
                String realpassword = rs.getString(2);
                String orgCode = rs.getString(3);
                String organization = rs.getString(4);
                UserTO user = new UserTO(userName, organization);
                user.setOrgCode(orgCode);
                if (realpassword.equals(password)) {
                    return user;
                }
            }
        } finally {
            conn.close();
        }
        return null;
    }


    public Collection getAllDistricts() throws SQLException {
        if (districts.isEmpty()) {
            Connection connection = null;
            PreparedStatement pstmt = null;
            ResultSet resultSet = null;
            try {
                connection = createConnection();
                String sqlString = SQLGenerator.getSQLForDistrictList();
                pstmt = connection.prepareStatement(sqlString);
                resultSet = pstmt.executeQuery();

                while (resultSet.next()) {
                    KeyValueDTO keyDTO = new KeyValueDTO();
                    keyDTO.setDbTableCode(resultSet.getString("DIST_CODE"));
                    keyDTO.setDisplayValue(resultSet.getString("DIST_NAME"));
                    districts.add(keyDTO);
                    districtMap.put(keyDTO.getDbTableCode(),keyDTO.getDisplayValue());
                }
            } finally {

                closeConnections(connection,pstmt,resultSet);
            }
        }
        return districts;
    }

    public Collection getAllDivisions() throws SQLException {
        if (divsions.isEmpty()) {
            Connection connection = null;
            PreparedStatement pstmt = null;
            ResultSet resultSet = null;
            try {
                connection = createConnection();
                String sqlString = SQLGenerator.getSQLForAllDevisions();
                pstmt = connection.prepareStatement(sqlString);
                resultSet = pstmt.executeQuery();

                while (resultSet.next()) {
                    KeyValueDTO keyDTO = new KeyValueDTO();
                    keyDTO.setDbTableCode(resultSet.getString(DataBaseConstants.TableColumans.DIVISION_CODE));
                    keyDTO.setDisplayValue(resultSet.getString(DataBaseConstants.TableColumans.DIVISION_NAME));
                    divsions.add(keyDTO);
                    divisionMap.put(keyDTO.getDbTableCode(),keyDTO.getDisplayValue());
                }
            } finally {
                closeConnections(connection,pstmt,resultSet);
            }
        }
        return divsions;
    }

    public Collection getAllProvinces() throws SQLException {
        if (provinces.isEmpty()) {
            Connection connection = null;
            PreparedStatement pstmt = null;
            ResultSet resultSet = null;
            try {
                connection = createConnection();
                String sqlString = SQLGenerator.getSQLForAllProivnces();
                pstmt = connection.prepareStatement(sqlString);
                resultSet = pstmt.executeQuery();

                while (resultSet.next()) {
                    KeyValueDTO keyDTO = new KeyValueDTO();
                    keyDTO.setDbTableCode(resultSet.getString(DataBaseConstants.TableColumans.PROVINCE_CODE));
                    keyDTO.setDisplayValue(resultSet.getString(DataBaseConstants.TableColumans.PROVINCE_NAME));
                    provinces.add(keyDTO);
                    provinceMap.put(keyDTO.getDbTableCode(),keyDTO.getDisplayValue());
                }
            } finally {
                closeConnections(connection,pstmt,resultSet);
            }
        }
        return provinces;
    }

    public List listDivisionsforDistrict(String districtName)
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            String sqlString = SQLGenerator.getSQLForDivisionListforDistrict(districtName);
            preparedStatement = connection.prepareStatement(sqlString);
            KeyValueDTO valDTO = null;
            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                valDTO = new KeyValueDTO();
                valDTO.setDisplayValue(resultSet.getString("DIV_NAME"));
                valDTO.setDbTableCode(resultSet.getString("DIV_ID"));
                list.add(valDTO);
            }
            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    public List listDistrictwithProvince(String provinceID)  throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();

            String sqlString = SQLGenerator.getSQLForDistrictListWithProvince(provinceID);
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();
            KeyValueDTO valueDTO = null;
            List list = new ArrayList();

            while (resultSet.next()) {
                valueDTO = new KeyValueDTO();
                valueDTO.setDbTableCode(resultSet.getString("DIST_CODE"));
                valueDTO.setDisplayValue(resultSet.getString("DIST_NAME"));
                list.add(valueDTO);
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    public List listDistrictsOrderbyProvince()
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForDistrictList();
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();
            KeyValueDTO valueDTO = null;
            List list = new ArrayList();

            while (resultSet.next()) {
                valueDTO = new KeyValueDTO();
                valueDTO.setDbTableCode(resultSet.getString("DIST_CODE"));
                valueDTO.setDisplayValue(resultSet.getString("DIST_NAME"));
                list.add(valueDTO);
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }


    public String getDistrict(String districtCode){
        return (String)districtMap.get(districtCode);
    }

    public String getDiviosion(String devisionCode){
        return (String)divisionMap.get(devisionCode);
    }

    public String getProvince(String provinceCode){
        return (String)provinceMap.get(provinceCode);

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


    private static void closeConnection (Connection  connection) {
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

    private static void closeConnections (Connection connection, Statement  statement, ResultSet  resultSet) {
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

