/*

* Created on Dec 30, 2004

*

* To change the template for this generated file go to

* Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

*/

package org.sahana.share.db;


import org.sahana.share.utils.OrderedMap;
import org.sahana.share.utils.KeyValueDTO;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Collection;


/**
 * @author Administrator
 *         <p/>
 *         <p/>
 *         <p/>
 *         To change the template for this generated type comment go to
 *         <p/>
 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

public class AbstractDataAccessManager {
    protected static OrderedMap allDistricts = null;
    protected static OrderedMap allCategories = null;
    protected static OrderedMap allPriorities = null;
    protected static OrderedMap allFulfillStatuses = null;
    protected static OrderedMap allSearchStatuses = null;

    protected static OrderedMap allSiteMap = null;


    public AbstractDataAccessManager() throws Exception {
        this.allSiteMap = loadAllSiteTypes();
        allCategories = loadAllCategories();
        allSearchStatuses = loadAllSearchStatuses();
        allPriorities = loadAllPriorities();
        allDistricts = loadAllDistricts();
        allFulfillStatuses = loadAllStatuses();
    }

    protected OrderedMap loadAllSiteTypes() throws SQLException, Exception {
        allSiteMap = new OrderedMap();
        Connection conn = DBConnection.createConnection();
        Statement s = null;
        ResultSet rs = null;

        try {

            String sql = AbstractSQLGenerator.getSQLForAllSites();

            s = conn.createStatement();

            rs = s.executeQuery(sql);


            String itemCode = null;

            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.Sitetype.SITE_TYPE_CODE);

                itemName = rs.getString(DBConstants.Sitetype.SITE_TYPE);
                allSiteMap.put(itemCode, itemName);
            }

        } finally {

            closeConnections(conn, s, rs);

        }
        return allSiteMap;
    }


    public Collection getAllSiteTypes() throws SQLException, Exception {
        return allSiteMap.getValuesInOrder();
    }


    public Collection getAllCategories() throws SQLException, Exception {
        return allCategories.getValuesInOrder();

    }

    public Collection getAllSearchStatuses() throws SQLException, Exception {
        return allSearchStatuses.getValuesInOrder();

    }

    protected static OrderedMap loadAllCategories() throws SQLException, Exception {


        Connection conn = DBConnection.createConnection();

        OrderedMap categoryDTOs = new OrderedMap();
        Statement s = null;
        ResultSet rs = null;

        try {

            String sql = AbstractSQLGenerator.getSQLForAllCategories();

            s = conn.createStatement();

            rs = s.executeQuery(sql);


            String itemCode = null;

            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.Category.CAT_CODE);

                itemName = rs.getString(DBConstants.Category.CAT_DESCRIPTION);

                categoryDTOs.put(itemCode, itemName);
            }

        } finally {
            closeConnections(conn, s, rs);
        }

        return categoryDTOs;

    }


    public Collection getAllPriorities() throws SQLException, Exception {
        return allPriorities.getValuesInOrder();

    }


    protected OrderedMap loadAllPriorities() throws SQLException, Exception {

        Connection conn = DBConnection.createConnection();

        OrderedMap priorityDTOs = new OrderedMap();

        Statement s = null;
        ResultSet rs = null;

        try {

            String sql = AbstractSQLGenerator.getSQLForAllPriorities();

            s = conn.createStatement();

            rs = s.executeQuery(sql);

            String itemCode = null;

            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.Priority.PRIORITY_LEVEL);

                itemName = rs.getString(DBConstants.Priority.PRIORITY_DESCRIPTION);

                priorityDTOs.put(itemCode, itemName);

            }

        } finally {
            closeConnections(conn, s, rs);
        }

        return priorityDTOs;

    }


    public Collection getAllOrganizationNames() throws SQLException, Exception {
        return loadAllOrganizationNames();
    }


    protected Collection loadAllOrganizationNames() throws SQLException, Exception {

        Connection conn = DBConnection.createConnection();

        Collection orgDTOs = new ArrayList();
        Statement s = null;
        ResultSet rs = null;

        try {

            String sql = AbstractSQLGenerator.getSQLForAllOrganizationNames();

            s = conn.createStatement();

            rs = s.executeQuery(sql);

            String itemCode = null;

            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.Organization.ORG_CODE);

                itemName = rs.getString(DBConstants.Organization.ORG_NAME);

                dto = new KeyValueDTO();

                dto.setDbTableCode(itemCode);

                dto.setDisplayValue(itemName);

                orgDTOs.add(dto);

            }

        } finally {
            closeConnections(conn, s, rs);
        }


        return orgDTOs;

    }


    public Collection getAllDistricts() throws SQLException, Exception {
        return allDistricts.getValuesInOrder();

    }


    protected OrderedMap loadAllDistricts() throws SQLException, Exception {

        Connection conn = DBConnection.createConnection();

        OrderedMap districtDTOs = new OrderedMap();

        Statement s = null;
        ResultSet rs = null;

        try {

            String sql = AbstractSQLGenerator.getSQLForAllDistricts();

            s = conn.createStatement();

            rs = s.executeQuery(sql);

            String itemCode = null;

            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.District.DISTRICT_CODE);

                itemName = rs.getString(DBConstants.District.DISTRICT_NAME);

                districtDTOs.put(itemCode, itemName);

            }

        } finally {

            closeConnections(conn, s, rs);

        }


        return districtDTOs;

    }


    public Collection getAllStatuses() throws SQLException, Exception {
        return allFulfillStatuses.getValuesInOrder();

    }

    protected OrderedMap loadAllSearchStatuses() throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        OrderedMap statusDTOs = new OrderedMap();

        Statement s = null;
        ResultSet rs = null;
        try {
            String sql = AbstractSQLGenerator.getSQLForAllSearchStatuses();
            s = conn.createStatement();
            rs = s.executeQuery(sql);
            String itemCode = null;
            String itemName = null;
            KeyValueDTO dto = null;
            while (rs.next()) {
                itemCode = rs.getString(DBConstants.Requeststatus.REQUEST_STATUS);
                itemName = rs.getString(DBConstants.Requeststatus.REQUEST_STATUS_DESCRIPTION);
                statusDTOs.put(itemCode, itemName);
            }
        } finally {
            closeConnections(conn, s, rs);
        }
        return statusDTOs;
    }


    protected OrderedMap loadAllStatuses() throws SQLException, Exception {

        Connection conn = DBConnection.createConnection();

        OrderedMap statusDTOs = new OrderedMap();

        Statement s = null;
        ResultSet rs = null;


        try {

            String sql = AbstractSQLGenerator.getSQLForAllStatuses();

            s = conn.createStatement();

            rs = s.executeQuery(sql);

            String itemCode = null;

            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.Fulfillstatus.FULLFILL_STATUS);

                itemName = rs.getString(DBConstants.Fulfillstatus.FULLFILL_STATUS_DESCRIPTION);

                dto = new KeyValueDTO();

                dto.setDbTableCode(itemCode);

                dto.setDisplayValue(itemName);

                statusDTOs.put(itemCode, itemName);

            }

        } finally {

            closeConnections(conn, s, rs);

        }


        return statusDTOs;

    }


    protected String ususalWildcard2SQLWildCard(String whildCard) {
        if (whildCard == null) {
            return null;
        }
        whildCard = whildCard.replace('*', '%');
        whildCard = whildCard.replace('?', '_');
        return whildCard;
    }


    protected static void closeResultSet

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


    protected static void closeConnection

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

    protected static void closeConnections

            (Connection

            connection, Statement

            statement, ResultSet

            resultSet) {

        closeStatement(statement);

        closeResultSet(resultSet);

        closeConnection(connection);
    }


    protected static void closeStatement

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

    public String getPriorityName(String key) {
        return (String) allPriorities.get(key);

    }

    public String getCategoryName(String code) {
        return (String) allCategories.get(code);

    }


    public String getSiteTypeName(String siteTypeCode) {
        return (String) allSiteMap.get(siteTypeCode);
    }
}


