/*
* Created on Dec 30, 2004
*
* To change the template for this generated file go to
* Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
*/
package org.campdb.db;

import org.campdb.business.*;
import org.campdb.util.LabelValue;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Collection;

/**
 * @author Administrator
 *         <p/>
 *         To change the template for this generated type comment go to
 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class DataAccessManager {

    //todo: load @ startup - & reload when ever edit/add/modify

    public DataAccessManager() {
    }

    private String getDistrictCode(CampTO campTO) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement pstmt = null;
        ResultSet resultSet = null;
        try {
            connection = DBConnection.createConnection();
            String sqlString = SQLGenerator.getSQLForDistrictCode(campTO.getDivisionId());
            pstmt = connection.prepareStatement(sqlString);
            resultSet = pstmt.executeQuery();
            if (resultSet.next()) {
                return resultSet.getString("DIST_CODE");
            }

        } finally {
            closeConnections(connection, pstmt, resultSet);
        }
        return null;
    }

    private String getProvinceCode(CampTO campTO) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement pstmt = null;
        ResultSet resultSet = null;
        try {
            connection = DBConnection.createConnection();
            String sqlString = SQLGenerator.getSQLForProvinceCode(campTO.getDistrictCode());
            pstmt = connection.prepareStatement(sqlString);
            resultSet = pstmt.executeQuery();
            if (resultSet.next()) {
                return resultSet.getString("PROV_CODE");
            }

        } finally {
            closeConnections(connection, pstmt, resultSet);
        }
        return null;
    }


    //campdb
    public boolean addCamp(CampTO campTO) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement pstmt = null;
        boolean returnValue = false;

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);

            String sqlString = SQLGenerator.getSQLAddCamp();
            pstmt = connection.prepareStatement(sqlString);

            pstmt.setString(1, campTO.getAreaName());
            pstmt.setString(2, campTO.getDivisionId());
            pstmt.setString(3, getDistrictCode(campTO));
            campTO.setDistrictCode(getDistrictCode(campTO));
            pstmt.setString(4, getProvinceCode(campTO));
            campTO.setProvienceCode(getProvinceCode(campTO));
            pstmt.setString(5, campTO.getCampName());
            pstmt.setString(6, campTO.getCampAccesability());
            pstmt.setString(7, campTO.getCampMen());
            pstmt.setString(8, campTO.getCampWomen());
            pstmt.setString(9, campTO.getCampChildren());
            pstmt.setString(10, campTO.getCampTotal());
            pstmt.setString(11, campTO.getCampCapability());
            pstmt.setString(12, campTO.getCampContactPerson());
            pstmt.setString(13, campTO.getCampContactNumber());
            pstmt.setString(14, campTO.getCampComment());
            pstmt.setDate(15,new java.sql.Date(campTO.getUpdateDate().getTime()));
            pstmt.setDate(16,new java.sql.Date(new java.util.Date().getTime()));
            pstmt.setString(17,campTO.getCampFamily());

            pstmt.execute();
            returnValue = true;
        }catch(Exception e){
            returnValue = false;
            e.printStackTrace();
            connection.rollback();
        } finally {
            connection.setAutoCommit(true);
            closeConnections(connection, pstmt, null);
        }

        return returnValue;
    }

     public boolean editCamp(CampTO campTO) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement pstmt = null;
        boolean returnValue = false;

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);

            String sqlString = SQLGenerator.getSQLEditCamp();
            System.out.println("sqlString = " + sqlString);
            pstmt = connection.prepareStatement(sqlString);
//
//             DBConstants.TableColumns.CAMP_AREANAME + "=?, "+
//                     DBConstants.TableColumns.CAMP_DIV_ID + "=?, "+
//                     DBConstants.TableColumns.CAMP_DIST_CODE + "=?, "+
//                     DBConstants.TableColumns.CAMP_PROV_CODE + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_NAME + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_ACCESABILITY + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_MEN + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_WOMEN + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_CHILDREN + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_TOTAL + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_CAPABILITY + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_CONTACT_PERSON + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_CONTACT_NUMBER + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_COMMENT + "=?, "+
//                     DBConstants.TableColumns.CAMP_LAST_UPDATE_DATE + "=?, "+
//                     DBConstants.TableColumns.CAMP_LAST_UPDATE_TIME + "=?, "+
//                     DBConstants.TableColumns.CAMP_CAMP_FAMILY  + "=?" +
//                     " where (" + DBConstants.TableColumns.CAMP_CAMP_ID + "=?";

            pstmt.setString(1, campTO.getAreaName());
            pstmt.setString(2, campTO.getDivisionId());
            pstmt.setString(3, getDistrictCode(campTO));
            campTO.setDistrictCode(getDistrictCode(campTO));
            pstmt.setString(4, getProvinceCode(campTO));
            campTO.setProvienceCode(getProvinceCode(campTO));
            pstmt.setString(5, campTO.getCampName());
            pstmt.setString(6, campTO.getCampAccesability());
            pstmt.setString(7, campTO.getCampMen());
            pstmt.setString(8, campTO.getCampWomen());
            pstmt.setString(9, campTO.getCampChildren());
            pstmt.setString(10, campTO.getCampTotal());
            pstmt.setString(11, campTO.getCampCapability());
            pstmt.setString(12, campTO.getCampContactPerson());
            pstmt.setString(13, campTO.getCampContactNumber());
            pstmt.setString(14, campTO.getCampComment());
            pstmt.setDate(15,new java.sql.Date(campTO.getUpdateDate().getTime()));
            pstmt.setDate(16,new java.sql.Date(new java.util.Date().getTime()));
            pstmt.setString(17,campTO.getCampFamily());
            pstmt.setString(18,campTO.getCampId());

            pstmt.execute();
            returnValue = true;
        }catch(Exception e){
            returnValue = false;
            e.printStackTrace();
            connection.rollback();
        } finally {
            connection.setAutoCommit(true);
            closeConnections(connection, pstmt, null);
        }

        return returnValue;
    }

    public boolean editCamp1(CampTO campTO) throws SQLException, Exception {
        Connection connection = null;
        Statement stmt = null;

        try {
            connection = DBConnection.createConnection();
            campTO.setDistrictCode(getDistrictCode(campTO));
            campTO.setProvienceCode(getProvinceCode(campTO));

            String sqlString = SQLGenerator.getSQLEditCamp(campTO);
            stmt = connection.createStatement();
            return stmt.execute(sqlString);
        } finally {
            closeConnections(connection, stmt, null);
        }
    }

    public boolean deleteCamp(int campId) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement pstmt = null;

        try {
            connection = DBConnection.createConnection();
            String sqlString = SQLGenerator.getSQLDeleteCamp();
            pstmt = connection.prepareStatement(sqlString);
            pstmt.setInt(1, campId);
            return pstmt.execute();
        } finally {
            closeConnections(connection, pstmt, null);
        }
    }



    public List searchCamps(String campName, String provinceCode,
                            String districtCode, int divisionId)
            throws SQLException, Exception {
        Connection connection = null;
        Connection connection2 = null;
        Statement stmt = null;
        Statement stmt2 = null;
        ResultSet resultSet = null;
        ResultSet tempRS = null;

        try {
            connection = DBConnection.createConnection();
            connection2 = DBConnection.createConnection();
            //connection.setAutoCommit(false);
            connection2.setAutoCommit(false);

            // Setting the Request Header data.
            String sqlSearchString = SQLGenerator.getSQLForSearchCriteria(campName,
                    provinceCode, districtCode, divisionId);

            stmt = connection.createStatement();
            stmt2 = connection2.createStatement();

            resultSet = stmt.executeQuery(sqlSearchString);

            List returnSearchTOs = new ArrayList();
            CampTO campTo;

            while (resultSet.next()) {
                campTo = new CampTO();
//                campTo = new CampTO();
//                campTo.setAreadId(resultSet.getString("AREA_ID"));
                campTo.setAreaName(resultSet.getString("AREA_NAME"));
                campTo.setCampAccesability(resultSet.getString("CAMP_ACCESABILITY"));
                campTo.setCampCapability(resultSet.getString("CAMP_CAPABILITY"));
                campTo.setCampChildren(resultSet.getString("CAMP_CHILDREN"));
                campTo.setCampComment(resultSet.getString("CAMP_COMMENT"));
                campTo.setCampContactNumber(resultSet.getString("CAMP_CONTACT_NUMBER"));
                campTo.setCampContactPerson(resultSet.getString("CAMP_CONTACT_PERSON"));
                campTo.setCampId(resultSet.getString("CAMP_ID"));
                campTo.setCampMen(resultSet.getString("CAMP_MEN"));
                campTo.setCampTotal(resultSet.getString("CAMP_TOTAL"));
                campTo.setCampName(resultSet.getString("CAMP_NAME"));
                campTo.setCampWomen(resultSet.getString("CAMP_WOMEN"));
                campTo.setDistrictCode(resultSet.getString("DIST_CODE"));
                campTo.setDivisionId(resultSet.getString("DIV_ID"));
                campTo.setProvienceCode(resultSet.getString("PROV_CODE"));

//                sqlSearchString = SQLGenerator.getSQLForAreaName(Integer.parseInt(campTo.getAreadId()));
//                tempRS = stmt2.executeQuery(sqlSearchString);
//                if (tempRS.next()) {
//                    campTo.setAreaName(tempRS.getString("AREA_NAME"));
//                }

                sqlSearchString = SQLGenerator.getSQLForDivisionName(Integer.parseInt(campTo.getDivisionId()));
                tempRS = stmt2.executeQuery(sqlSearchString);
                if (tempRS.next()) campTo.setDivionName(tempRS.getString("DIV_NAME"));

                sqlSearchString = SQLGenerator.getSQLForDistrictName(campTo.getDistrictCode());
                tempRS = stmt2.executeQuery(sqlSearchString);
                if (tempRS.next()) campTo.setDistrictName(tempRS.getString("DIST_NAME"));

                sqlSearchString = SQLGenerator.getSQLForProvienceName(campTo.getProvienceCode());
                tempRS = stmt2.executeQuery(sqlSearchString);
                if (tempRS.next()) campTo.setProvienceName(tempRS.getString("PROV_NAME"));

                returnSearchTOs.add(campTo);
            }
            return returnSearchTOs;
        } finally {
            closeConnections(connection, stmt, resultSet);
            closeConnections(connection2, stmt2, tempRS);
        }
    }

    public CampTO searchCamp(int campId)
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForSearchCriteria(campId);
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            CampTO campTo = null;

            if (resultSet.next()) {
                campTo = new CampTO();
//                campTo.setAreadId(resultSet.getString("AREA_ID"));
                campTo.setAreaName(resultSet.getString("AREA_NAME"));
                campTo.setCampAccesability(resultSet.getString("CAMP_ACCESABILITY"));
                campTo.setCampCapability(resultSet.getString("CAMP_CAPABILITY"));
                campTo.setCampChildren(resultSet.getString("CAMP_CHILDREN"));
                campTo.setCampComment(resultSet.getString("CAMP_COMMENT"));
                campTo.setCampContactNumber(resultSet.getString("CAMP_CONTACT_NUMBER"));
                campTo.setCampContactPerson(resultSet.getString("CAMP_CONTACT_PERSON"));
                campTo.setCampId(resultSet.getString("CAMP_ID"));
                campTo.setCampMen(resultSet.getString("CAMP_MEN"));
                campTo.setCampName(resultSet.getString("CAMP_NAME"));
                campTo.setCampWomen(resultSet.getString("CAMP_WOMEN"));
                campTo.setCampTotal(resultSet.getString("CAMP_TOTAL"));
                campTo.setDistrictCode(resultSet.getString("DIST_CODE"));
                campTo.setDivisionId(resultSet.getString("DIV_ID"));
                campTo.setProvienceCode(resultSet.getString("PROV_CODE"));
            } else {
                return null;
            }
            //todo: should use outer joint
            sqlString = SQLGenerator.getSQLForProvienceName(campTo.getProvienceCode());
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                campTo.setProvienceName(resultSet.getString("PROV_NAME"));
            }

            sqlString = SQLGenerator.getSQLForDistrictName(campTo.getDistrictCode());
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                campTo.setDistrictName(resultSet.getString("DIST_NAME"));
            }

            sqlString = SQLGenerator.getSQLForDivisionName(Integer.parseInt(campTo.getDivisionId()));
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                campTo.setDivionName(resultSet.getString("DIV_NAME"));
            }


            return campTo;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    public List listProvicences()
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForProvienceList();
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("PROV_NAME");
                String value = resultSet.getString("PROV_CODE");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    public List listDistricts()
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

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("DIST_NAME");
                String value = resultSet.getString("DIST_CODE");
                list.add(new LabelValue(label, value));
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
            sqlString = sqlString + " order by PROV_CODE";
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("DIST_NAME");
                String value = resultSet.getString("DIST_CODE");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }


    public List listDistrictwithProvince(String provinceID)
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForDistrictListWithProvince(provinceID);
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("DIST_NAME");
                String value = resultSet.getString("DIST_CODE");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    public List listDivisions()
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            // Setting the Request Header data.
            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForDivisionList();
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("DIV_NAME");
                String value = resultSet.getString("DIV_ID");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    public List listDivisionsforDistrcit(String disstrictName)
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            // Setting the Request Header data.
            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForDivisionListforDistrict(disstrictName);
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("DIV_NAME");
                String value = resultSet.getString("DIV_ID");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }


    public List listAreas()
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            // Setting the Request Header data.
            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForAreaList();
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("AREA_NAME");
                String value = resultSet.getString("AREA_ID");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    private static void closeResultSet
            (ResultSet
            resultSet) {
        // close the result set
        if (resultSet != null) {
            try {
                resultSet.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    private static void closeConnection
            (Connection
            connection) {
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
    private static void closeConnections
            (Connection
            connection, Statement
            statement, ResultSet
            resultSet) {

        closeStatement(statement);
        closeResultSet(resultSet);
        closeConnection(connection);


    }

    private static void closeStatement
            (Statement
            statement) {
        // close the statement
        if (statement != null) {
            try {
                statement.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }

    public User loginSuccess(String userName, String password) throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        Statement s = null;
        ResultSet rs = null;
        try {
            String sql = SQLGenerator.getSQLForLogin(userName);
            s = conn.createStatement();
            rs = s.executeQuery(sql);
            if (rs.next()) {
                String realpassword = rs.getString(DBConstants.TableColumns.PASSWORD);
                String organization = rs.getString(DBConstants.TableColumns.ORGANIZATION);

                User user = new User(userName, organization);
                if (realpassword.equals(password)) {
                    return user;
                }
            }
        } finally {
            closeConnections(conn, s, rs);
        }

        return null;
    }


    public List validateCampTOforInsert(CampTO campTO) throws SQLException, Exception {
        List result = campTO.validate();

        if (!result.isEmpty()) {
            return result;
        }

        Connection connection = null;
        Statement stmt = null;
        ResultSet rs = null;
        String sqlString;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);
            stmt = connection.createStatement();

            String areaId, divisionId, districtCode, provCode;

            if (campTO.getAreadId() != null) {
                areaId = campTO.getAreadId();
                sqlString = SQLGenerator.getSQLForAreaDivision(areaId);
                rs = stmt.executeQuery(sqlString);

                if (rs.next()) {
                    divisionId = rs.getString("DIV_ID");

                    if (campTO.getDivisionId() != null) {
                        if (!divisionId.equals(campTO.getAreadId())) {
                            result.add("Area doesn't exist in the Division");
                            return result;
                        }
                    }

                    sqlString = SQLGenerator.getSQLForDivisionDistrict(divisionId);
                    rs = stmt.executeQuery(sqlString);

                    if (!rs.next()) {
                        result.add("Division doesn't exist ");
                        return result;
                    }
                    districtCode = rs.getString("DIST_CODE");

                    if (campTO.getDistrictCode() != null) {
                        if (!districtCode.equals(campTO.getDistrictCode())) {
                            result.add("Division doesn't exist in the District");
                            return result;
                        }
                    }

                    sqlString = SQLGenerator.getSQLForDistrictProvince(districtCode);
                    rs = stmt.executeQuery(sqlString);

                    if (!rs.next()) {
                        result.add("District doesn't exist ");
                        return result;
                    }
                    provCode = rs.getString("PROV_CODE");

                    if (campTO.getProvienceCode() != null) {
                        if (!provCode.equals(campTO.getProvienceCode())) {
                            result.add("Division doesn't exist in the District ");
                            return result;
                        }
                    }
                } else {
                    result.add("Area doesn't exist");
                    return result;
                }
            } else if (campTO.getDivisionId() != null) {
                divisionId = campTO.getDivisionId();
                sqlString = SQLGenerator.getSQLForDivisionDistrict(divisionId);
                rs = stmt.executeQuery(sqlString);

                if (rs.next()) {
                    districtCode = rs.getString("DIST_CODE");

                    if (campTO.getDistrictCode() != null) {
                        if (!districtCode.equals(campTO.getDistrictCode())) {
                            result.add("Division doesn't exist in the District");
                            return result;
                        }
                    }

                    sqlString = SQLGenerator.getSQLForDistrictProvince(districtCode);
                    rs = stmt.executeQuery(sqlString);

                    if (!rs.next()) {
                        result.add("District doesn't exist ");
                        return result;
                    }
                    provCode = rs.getString("PROV_CODE");

                    if (campTO.getProvienceCode() != null) {
                        if (!provCode.equals(campTO.getProvienceCode())) {
                            result.add("District doesn't exist in the Division");
                            return result;
                        }
                    }
                } else {
                    result.add("Division doesn't exist");
                    return result;
                }

            } else {
                districtCode = campTO.getDistrictCode();
                sqlString = SQLGenerator.getSQLForDistrictProvince(districtCode);
                rs = stmt.executeQuery(sqlString);

                if (rs.next()) {
                    provCode = rs.getString("PROV_CODE");

                    if (campTO.getProvienceCode() != null) {
                        if (!provCode.equals(campTO.getProvienceCode())) {
                            result.add("District doesn't exist in the Division");
                            return result;
                        }
                    }
                } else {
                    result.add("District doesn't exist");
                    return result;
                }
            }

        } //end try
        finally {
            closeConnections(connection, stmt, rs);
        }

        return result;
    }


    public List validateCampTOforEdit(CampTO campTO) throws SQLException, Exception {
        List result = campTO.validate();

        if (!result.isEmpty()) {
            return result;
        }

        Connection connection = null;
        Statement stmt = null;
        ResultSet rs = null;
        String sqlString;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);
            stmt = connection.createStatement();

            String campId = campTO.getCampId();
            sqlString = SQLGenerator.getSQLForEditCamp(campId);
            rs = stmt.executeQuery(sqlString);

            if (!rs.next()) {
                result.add("Camp Id doesn't exist in the table");
                return result;
            }

            String areaId, divisionId, districtCode, provCode;

            if (campTO.getAreadId() != null) {
                areaId = campTO.getAreadId();
                sqlString = SQLGenerator.getSQLForAreaDivision(areaId);
                rs = stmt.executeQuery(sqlString);

                if (rs.next()) {
                    divisionId = rs.getString("DIV_ID");

                    if (campTO.getDivisionId() != null) {
                        if (!divisionId.equals(campTO.getAreadId())) {
                            result.add("Area doesn't exist in the Division");
                            return result;
                        }
                    }

                    sqlString = SQLGenerator.getSQLForDivisionDistrict(divisionId);
                    rs = stmt.executeQuery(sqlString);
                    districtCode = rs.getString("DIST_CODE");

                    if (campTO.getDistrictCode() != null) {
                        if (!districtCode.equals(campTO.getDistrictCode())) {
                            result.add("Division doesn't exist in the District");
                            return result;
                        }
                    }

                    sqlString = SQLGenerator.getSQLForDistrictProvince(districtCode);
                    rs = stmt.executeQuery(sqlString);
                    provCode = rs.getString("PROV_CODE");

                    if (campTO.getProvienceCode() != null) {
                        if (!provCode.equals(campTO.getProvienceCode())) {
                            result.add("District doesn't exist in the Division");
                            return result;
                        }
                    }
                } else {
                    result.add("Area doesn't exist");
                    return result;
                }
            } else if (campTO.getDivisionId() != null) {
                divisionId = campTO.getDivisionId();
                sqlString = SQLGenerator.getSQLForDivisionDistrict(divisionId);
                rs = stmt.executeQuery(sqlString);

                if (rs.next()) {
                    districtCode = rs.getString("DIST_CODE");

                    if (campTO.getDistrictCode() != null) {
                        if (!districtCode.equals(campTO.getDistrictCode())) {
                            result.add("Division doesn't exist in the District");
                            return result;
                        }
                    }

                    sqlString = SQLGenerator.getSQLForDistrictProvince(districtCode);
                    rs = stmt.executeQuery(sqlString);
                    provCode = rs.getString("PROV_CODE");

                    if (campTO.getProvienceCode() != null) {
                        if (!provCode.equals(campTO.getProvienceCode())) {
                            result.add("District doesn't exist in the Division");
                            return result;
                        }
                    }
                } else {
                    result.add("Division doesn't exist");
                    return result;
                }

            } else {
                districtCode = campTO.getDistrictCode();
                sqlString = SQLGenerator.getSQLForDistrictProvince(districtCode);
                rs = stmt.executeQuery(sqlString);

                if (rs.next()) {
                    provCode = rs.getString("PROV_CODE");

                    if (campTO.getProvienceCode() != null) {
                        if (!provCode.equals(campTO.getProvienceCode())) {
                            result.add("District doesn't exist in the Division");
                            return result;
                        }
                    }
                } else {
                    result.add("District doesn't exist");
                    return result;
                }
            }

        } //end try
        finally {
            closeConnections(connection, stmt, rs);
        }

        return result;
    }

    public ArrayList getDivisionRelatedInfo() throws Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForDivisionInfo();
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            ArrayList arrayList = new ArrayList(100);

            while (resultSet.next()) {
                String id = resultSet.getString("DIV_ID");
                String districtName = resultSet.getString("DIST_NAME");
                String provName = resultSet.getString("PROV_NAME");
                arrayList.add(" District : " + districtName + "   Province : " + provName);
            }

            return arrayList;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }

    }



}
