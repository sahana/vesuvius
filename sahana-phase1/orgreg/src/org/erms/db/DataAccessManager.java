/*

* Created on Dec 30, 2004

*

* To change the template for this generated file go to

* Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

*/

package org.erms.db;


import org.erms.business.*;
import org.sahana.share.db.DBConnection;

import java.sql.*;
import java.util.*;
import java.util.Date;


/**
 * @author Administrator
 *         <p/>
 *         <p/>
 *         <p/>
 *         To change the template for this generated type comment go to
 *         <p/>
 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

public class DataAccessManager implements DBConstants {


    private static Collection allOrganizationNames = null;
    private static Collection allDistricts = null;
    private static Collection allCategories = null;
    private static Collection allPriorities = null;
    private static Collection allStatuses = null;


    public DataAccessManager() {
    }


    public Collection getAllCategories() throws SQLException, Exception {
        if (allCategories == null) {
            allCategories = loadAllCategories();
        }
        return allCategories;
    }


    private static Collection loadAllCategories() throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        List categoryDTOs = new ArrayList();
        try {
            String sql = SQLGenerator.getSQLForAllCategories();
            Statement s = conn.createStatement();
            ResultSet rs = s.executeQuery(sql);

            String itemCode = null;
            String itemName = null;
            KeyValueDTO dto = null;

            while (rs.next()) {

                itemCode = rs.getString(DBConstants.TableColumns.CAT_CODE);

                itemName = rs.getString(DBConstants.TableColumns.CAT_DESCRIPTION);

                dto = new KeyValueDTO();

                dto.setDbTableCode(itemCode);

                dto.setDisplayValue(itemName);

                categoryDTOs.add(dto);

            }

        } finally {

            conn.close();

        }


        return categoryDTOs;

    }


    public Collection getAllPriorities() throws SQLException, Exception {

        if (allPriorities == null) {

            allPriorities = loadAllPriorities();

        }


        return allPriorities;

    }


    private Collection loadAllPriorities() throws SQLException, Exception {

        Connection conn = DBConnection.createConnection();

        List priorityDTOs = new ArrayList();


        try {

            String sql = SQLGenerator.getSQLForAllPriorities();

            Statement s = conn.createStatement();

            ResultSet rs = s.executeQuery(sql);

            String itemCode = null;

            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.TableColumns.PRIORITY_LEVEL);

                itemName = rs.getString(DBConstants.TableColumns.PRIORITY_DESCRIPTION);

                dto = new KeyValueDTO();

                dto.setDbTableCode(itemCode);

                dto.setDisplayValue(itemName);

                priorityDTOs.add(dto);

            }

        } finally {

            conn.close();

        }


        return priorityDTOs;

    }


    /**
     * Method to add a request.
     *
     * @param request The Request value object which will contain the data that needs to be saved.
     * @throws Exception
     */

    public void addRequest(RequestTO request) throws Exception {

        Connection connection = null;

        PreparedStatement preparedStatement = null;

        ResultSet resultSet = null;


        try {

            connection = DBConnection.createConnection();

            connection.setAutoCommit(false);



            // Setting the Request Header data.

            String sqlAddRequestHeaderString = SQLGenerator.getSQLAddRequestHeader();


            preparedStatement = connection.prepareStatement(sqlAddRequestHeaderString);

            preparedStatement.setString(1, request.getOrganization());

            preparedStatement.setDate(2, request.getCreateDate());

            preparedStatement.setDate(3, request.getRequestedDate());

            preparedStatement.setString(4, request.getCallerName());

            preparedStatement.setString(5, request.getCallerAddress());

            preparedStatement.setString(6, request.getCallerContactNumber());

            preparedStatement.setString(7, request.getDescription());

            preparedStatement.setString(8, request.getSiteType());

            preparedStatement.setString(9, request.getSiteDistrict());

            preparedStatement.setString(10, request.getSiteArea());

            preparedStatement.setString(11, request.getSiteName());


            preparedStatement.executeUpdate();



            // Getting the generated Key from the above statement

            ResultSet generatedKeys = preparedStatement.getGeneratedKeys();


            String generatedKey = new String();


            if (generatedKeys.next()) // We're expecting just one auto genrated key
            {

                generatedKey = generatedKeys.getObject(1).toString();

            }


            String sqlAddRequestDetailString = SQLGenerator.getSQLAddRequestDetail();



            // Now we're going to add the detail records.

            Collection requestDetails = request.getRequestDetails();


            for (Iterator iterator = requestDetails.iterator(); iterator.hasNext();) {

                RequestDetailTO requestDetailTO = (RequestDetailTO) iterator.next();


                preparedStatement = connection.prepareStatement(sqlAddRequestDetailString);

                preparedStatement.setString(1, generatedKey);

                preparedStatement.setString(2, requestDetailTO.getCategory());

                preparedStatement.setString(3, requestDetailTO.getItem());

                preparedStatement.setString(4, requestDetailTO.getDescription());

                preparedStatement.setString(5, requestDetailTO.getUnit());

                preparedStatement.setInt(6, requestDetailTO.getQuantity());

                preparedStatement.setString(7, requestDetailTO.getPriority());


                preparedStatement.executeUpdate();


            }



            // If all is ok then commit.

            connection.commit();

            connection.setAutoCommit(true);

        } catch (Exception e) {

            System.out.println("Exception!!!");

            try {

                if (connection != null)

                // Since an exception has occured lets roll back the partially inserted record.
                {

                    System.out.println("About to rollback");

                    connection.rollback();

                    connection.setAutoCommit(true);

                    System.out.println("After roll back");

                }

            } catch (SQLException e1) {

                System.out.println("rollback exception");

                e1.printStackTrace();

                throw e1;

            }

            e.printStackTrace();

            throw e;

        } finally {

            closeConnections(connection, preparedStatement, resultSet);

        }

    }


    public Collection getAllOrganizationNames() throws SQLException, Exception {

        if (allOrganizationNames == null) {

            allOrganizationNames = loadAllOrganizationNames();

        }


        return allOrganizationNames;

    }


    private Collection loadAllOrganizationNames() throws SQLException, Exception {

        Connection conn = DBConnection.createConnection();

        Collection orgDTOs = new ArrayList();


        try {

            String sql = SQLGenerator.getSQLForAllOrganizationNames();

            Statement s = conn.createStatement();

            ResultSet rs = s.executeQuery(sql);

            String itemCode = null;

            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.TableColumns.ORG_CODE);

                itemName = rs.getString(DBConstants.TableColumns.ORG_NAME);

                dto = new KeyValueDTO();

                dto.setDbTableCode(itemCode);

                dto.setDisplayValue(itemName);

                orgDTOs.add(dto);

            }

        } finally {

            conn.close();

        }


        return orgDTOs;

    }


    public Collection getAllDistricts() throws SQLException, Exception {

        if (allDistricts == null) {

            allDistricts = loadAllDistricts();

        }


        return allDistricts;

    }


    private Collection loadAllDistricts() throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        List districtDTOs = new ArrayList();
        Statement s = null;
        ResultSet rs = null;
        try {

            String sql = SQLGenerator.getSQLForAllDistricts();
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

    public Collection getAllDistrictNames() throws Exception {
        Iterator districtDTOIter = getAllDistricts().iterator();
        ArrayList districtNames = new ArrayList(25);
        while (districtDTOIter.hasNext()) {
            KeyValueDTO keyValueDTO = (KeyValueDTO) districtDTOIter.next();
            districtNames.add(keyValueDTO.getDisplayValue());
        }

        return districtNames;
    }


    public Collection getAllStatuses() throws SQLException, Exception {
        if (allStatuses == null) {
            allStatuses = loadAllStatuses();
        }
        return allStatuses;
    }


    private Collection loadAllStatuses() throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        List statusDTOs = new ArrayList();
        Statement s = null;
        ResultSet rs = null;
        try {
            String sql = SQLGenerator.getSQLForAllStatuses();
            s = conn.createStatement();
            rs = s.executeQuery(sql);
            String itemCode = null;
            String itemName = null;

            KeyValueDTO dto = null;


            while (rs.next()) {

                itemCode = rs.getString(DBConstants.TableColumns.STATUS);

                itemName = rs.getString(DBConstants.TableColumns.DESCRIPTION);

                dto = new KeyValueDTO();

                dto.setDbTableCode(itemCode);

                dto.setDisplayValue(itemName);

                statusDTOs.add(dto);

            }

        } finally {

            closeConnections(conn, s, rs);

        }


        return statusDTOs;

    }


    /**
     * This method returns the Request which matches the passed requestdetailID.
     *
     * @param requestDetailID
     * @return An Arraylist, where the first object would be the RequestTO value object and the second object would be
     *         <p/>
     *         the services (if any) who are fulfilling the request.
     */

    public List getRequest(String requestDetailID) throws SQLException, Exception {


        if (requestDetailID == null || Integer.parseInt(requestDetailID) == 0)

            throw new Exception("The request detail ID is null");


        Connection connection = DBConnection.createConnection();

        Statement statement = null;

        ResultSet resultSet = null;

        RequestTO requestTO = new RequestTO();

        RequestDetailTO requestDetailTO = new RequestDetailTO();

        RequestFulfillDetailTO requestFulfillDetailTO = new RequestFulfillDetailTO();

        List returnTOList = new ArrayList();


        try {

            String sql = SQLGenerator.getSQLGetRequestDetail(requestDetailID);

            statement = connection.createStatement();

            resultSet = statement.executeQuery(sql);


            while (resultSet.next()) {

                requestDetailTO.setRequestDetailID(resultSet.getString(DBConstants.TableColumns.REQUEST_DETAIL_ID));

                requestDetailTO.setRequestID(resultSet.getString(DBConstants.TableColumns.REQUEST_ID));

                requestDetailTO.setCategory(resultSet.getString(DBConstants.TableColumns.CATEGORY));

                requestDetailTO.setItem(resultSet.getString(DBConstants.TableColumns.ITEM));

                requestDetailTO.setDescription(resultSet.getString(DBConstants.TableColumns.DESCRIPTION));

                requestDetailTO.setUnit(resultSet.getString(DBConstants.TableColumns.UNIT));

                requestDetailTO.setQuantity(resultSet.getInt(DBConstants.TableColumns.QUANTITY));

                requestDetailTO.setPriority(resultSet.getString(DBConstants.TableColumns.PRIORITY_DESCRIPTION));


                requestTO.setRequestID(resultSet.getString(DBConstants.TableColumns.REQUEST_ID));

                requestTO.setOrganization(resultSet.getString(DBConstants.TableColumns.ORG_CODE));

                requestTO.setCreateDate(resultSet.getDate(DBConstants.TableColumns.CREATE_DATE));

                requestTO.setRequestedDate(resultSet.getDate(DBConstants.TableColumns.REQUEST_DATE));

                requestTO.setCallerName(resultSet.getString(DBConstants.TableColumns.CALLER_NAME));

                requestTO.setCallerAddress(resultSet.getString(DBConstants.TableColumns.CALLER_ADDRESS));

                requestTO.setCallerContactNumber(resultSet.getString(DBConstants.TableColumns.CALLER_CONTACT_NO));

                requestTO.setDescription(resultSet.getString(DBConstants.TableColumns.DESCRIPTION));

                requestTO.setSiteType(resultSet.getString(DBConstants.TableColumns.SITE_TYPE));

                requestTO.setSiteDistrict(resultSet.getString(DBConstants.TableColumns.SITE_DISTRICT));

                requestTO.setSiteArea(resultSet.getString(DBConstants.TableColumns.SITE_AREA));

                requestTO.setSiteName(resultSet.getString(DBConstants.TableColumns.SITE_NAME));


                List requestDetailTOs = new ArrayList();

                requestDetailTOs.add(requestDetailTO);


                requestTO.setRequestDetails(requestDetailTOs);


                returnTOList.add(requestTO);



                // Now get the services who have serviced this request.

                String sqlFulfillServices = SQLGenerator.getSQLGetServiceDetailsForRequest(requestDetailID);

                statement = connection.createStatement();

                resultSet = statement.executeQuery(sqlFulfillServices);


                List servicerList = new ArrayList();


                while (resultSet.next()) {

                    requestFulfillDetailTO = new RequestFulfillDetailTO();

                    requestFulfillDetailTO.setOrgCode(resultSet.getString(DBConstants.TableColumns.ORG_CODE));

                    requestFulfillDetailTO.setOrgContact(resultSet.getString(DBConstants.TableColumns.ORG_ADDRESS));

                    requestFulfillDetailTO.setOrgName(resultSet.getString(DBConstants.TableColumns.ORG_NAME));

                    requestFulfillDetailTO.setQuantity(resultSet.getString(DBConstants.TableColumns.SERVICE_QTY));

                    requestFulfillDetailTO.setStatus(resultSet.getString(DBConstants.TableColumns.STATUS));


                    servicerList.add(requestFulfillDetailTO);

                }


                returnTOList.add(servicerList);

            }

        } finally {

            closeConnections(connection, statement, resultSet);

        }


        return returnTOList;

    }


    public Collection getFullFillDetails(String id) {

        return null;

    }


    /**
     * This method will save the fullfilled request.
     *
     * @param fullFillment The Fulfillment value object which has the data which needs to be saved.
     * @throws Exception
     */

    public void fulfillRequest(RequestFulfillTO fullFillment) throws Exception {

        Connection connection = null;

        PreparedStatement preparedStatement = null;

        ResultSet resultSet = null;


        try {

            connection = DBConnection.createConnection();

            connection.setAutoCommit(false);



            // Setting the Request Header data.

            String sqlAddFulFillRequestString = SQLGenerator.getSQLAddFulFillRequest();


            preparedStatement = connection.prepareStatement(sqlAddFulFillRequestString);


            preparedStatement.setString(1, fullFillment.getOrganization());

            preparedStatement.setString(2, fullFillment.getRequestDetailID());

            preparedStatement.setString(3, fullFillment.getServiceQuantity());

            preparedStatement.setString(4, fullFillment.getStatus());


            preparedStatement.executeUpdate();



            // If all is ok then commit.

            System.out.println("Before commit");

            connection.commit();

            connection.setAutoCommit(true);

            System.out.println("After commit");

        } catch (Exception e) {

            System.out.println("Exception!!!");

            try {

                if (connection != null)

                // Since an exception has occured lets roll back the partially inserted record.
                {

                    System.out.println("About to rollback");

                    connection.rollback();

                    connection.setAutoCommit(true);

                    System.out.println("After roll back");

                }

            } catch (SQLException e1) {

                System.out.println("rollback exception");

                e1.printStackTrace();

                throw e1;

            }

            e.printStackTrace();

            throw e;

        } finally {

            closeConnections(connection, preparedStatement, resultSet);

        }

    }


    /**
     * This class is still in progress... The SQL statement in the SQLgenerator has to be completed with the appropriate search fields and select fields.
     * <p/>
     * Similarly this method woudl have to be updated with the correct set statements.
     *
     * @param searchCriteria
     * @return
     * @throws SQLException
     * @throws Exception
     */

    public List searchRequests(RequestSearchCriteriaTO searchCriteria) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);
            String sqlSearchString = SQLGenerator.getSQLForSearchCriteria();
            preparedStatement = connection.prepareStatement(sqlSearchString);
            preparedStatement.setString(1, searchCriteria.getCategory());
            preparedStatement.setString(2, searchCriteria.getCategory());
            resultSet = preparedStatement.executeQuery();
            List returnSearchTOs = new ArrayList();
            RequestSearchTO requestSearchTo = new RequestSearchTO();

            while (resultSet.next()) {
                requestSearchTo = new RequestSearchTO();
                requestSearchTo.setItem(resultSet.getString(DBConstants.TableColumns.ITEM));
                returnSearchTOs.add(requestSearchTo);
            }
            return returnSearchTOs;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);

        }

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

    public boolean isUserExisting(String userName) throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        Statement s = null;
        ResultSet rs = null;
        boolean returnValue = false;
        try {
            String sql = SQLGenerator.getSQLForUserCheck(userName);
            s = conn.createStatement();
            rs = s.executeQuery(sql);
            if (rs.next()) {
                returnValue = true;
            }
        } finally {
            closeConnections(conn, s, rs);

        }
        return returnValue;

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


    public boolean hasOrgAlreadyRegisterd(String orgName) throws Exception {
        Connection conn = DBConnection.createConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;

        try {
            String sql = SQLGenerator.getSQLForCountOrganizationName();
            ps = conn.prepareStatement(sql);
            ps.setString(1, orgName);
            rs = ps.executeQuery();

            if (rs.next()) {
                if (rs.getInt(1) > 0) {
                    return true;
                }
            }

            return false;

        } finally {
            closeConnections(conn, ps, rs);
        }

    }

    public String getOrgCode() throws Exception {
        Connection conn = DBConnection.createConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;
        String code = null;
        try {
            String sql = SQLGenerator.getLastOrgCode();
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            if (rs.next()) {
                code = rs.getString(1);

                try {
                    int count = Integer.parseInt(code);
                    count = count + 1;
                    String zeroStr = String.valueOf(count);
                    int len = zeroStr.length();
                    zeroStr = "";
                    for (int i = 0; i < 6 - len; i++) {
                        zeroStr = zeroStr + "0";
                    }

                    code = zeroStr + count;
                } catch (NumberFormatException e) {
                    //the number could not be set. use the default
                    code = "000001";
                }
            } else {
                //just use the default
                code = "000001";
            }
        } finally {
            closeConnections(conn, ps, rs);
        }
        return code;

    }

    public OrganizationRegistrationTO getOrgTO(String orgCode) throws Exception {
        Connection conn = DBConnection.createConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;
        OrganizationRegistrationTO orgTo = new OrganizationRegistrationTO();
        try {

            // get info from Organization table
            String sql = SQLGenerator.getSQLForAllOrganizations(orgCode);
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();

            if (rs.next()) {
                orgTo = new OrganizationRegistrationTO();
                orgTo.setOrgType(rs.getString(TableColumns.ORG_TYPE));
                orgTo.setNgoType(rs.getString(TableColumns.ORG_SUBTYPE));
                orgTo.setOrgCode(rs.getString(TableColumns.ORG_CODE));
                orgTo.setContactPerson(rs.getString(TableColumns.ORG_CONTACT_PERSON));
                orgTo.setOrgName(rs.getString(TableColumns.ORG_NAME));
                orgTo.setStatus(new Integer(rs.getInt(TableColumns.ORG_STATUS)).toString());
                orgTo.setOrgAddress(rs.getString(TableColumns.ORG_ADDRESS));
                orgTo.setContactNumber(rs.getString(TableColumns.ORG_CONTACT_NUMBER));
                orgTo.setEmailAddress(rs.getString(TableColumns.ORG_EMAIL_ADDRESS));
                orgTo.setCountryOfOrigin(rs.getString(TableColumns.ORG_COUNTRY_OF_ORIGIN));
                orgTo.setFacilitiesAvailable(rs.getString(TableColumns.ORG_FACILITIES_AVAILABLE));
                orgTo.setComments(rs.getString(TableColumns.ORG_COMMENTS));
                orgTo.setLastUpdate(rs.getString(TableColumns.ORG_LAST_UPDATE));
                orgTo.setPeriodEndDate(rs.getDate(TableColumns.ORG_UNTILDATE));
                int temp = rs.getInt(TableColumns.ORG_IS_SRILANKAN);
                if (temp == 0) {
                    orgTo.setIsSriLankan(false);
                } else {
                    orgTo.setIsSriLankan(true);
                }

            }

            // get information from organization_district table
            sql = SQLGenerator.getSQLForOrganizationDistrictRelationshipInfoRetrieval(orgCode);
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();

            while(rs.next()){
                orgTo.addWorkingArea(rs.getString(TableColumns.ORGANIZATION_DISTRICT_DISTRICT_NAME));
            }

            // get information from organization_sectors table
            sql = SQLGenerator.getSQLForOrganizationSectorsRelationshipInfoRetrieval(orgCode);
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();

            while(rs.next()){
                orgTo.addSectors(rs.getString(TableColumns.ORGANIZATION_SECTOR_SECTOR));
            }

            // get information from users table
            sql = SQLGenerator.getSQLForOrganizationUsersInfoRetrieval(orgCode);
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();

            while(rs.next()){
                orgTo.setUsername(rs.getString(TableColumns.USER_NAME));
            }

            closeConnections(conn, ps, rs);
            return orgTo;
        } finally {
            closeConnections(conn, ps, rs);
        }

    }

    public List getAllOrganizations() throws Exception {
        Connection conn = DBConnection.createConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;
        ArrayList returnList = new ArrayList();
        OrganizationTO orgTo;

        try {
            String sql = SQLGenerator.getSQLForAllOrganizations();
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();

            while (rs.next()) {
                orgTo = new OrganizationTO();
                orgTo.setOrgName(rs.getString(TableColumns.ORG_NAME));
                orgTo.setOrgAddress(rs.getString(TableColumns.ORG_ADDRESS));
                orgTo.setContactNumber(rs.getString(TableColumns.ORG_CONTACT_NUMBER));
                orgTo.setEmailAddress(rs.getString(TableColumns.ORG_EMAIL_ADDRESS));
                orgTo.setCountryOfOrigin(rs.getString(TableColumns.ORG_COUNTRY_OF_ORIGIN));
                orgTo.setFacilitiesAvailable(rs.getString(TableColumns.ORG_FACILITIES_AVAILABLE));
                orgTo.setWorkingAreas(rs.getString(TableColumns.ORG_WORKING_AREAS));
                orgTo.setOrgCode(rs.getString(TableColumns.ORG_CODE));
                orgTo.setComments(rs.getString(TableColumns.ORG_COMMENTS));
                returnList.add(orgTo);
            }
        } finally {
            closeConnections(conn, ps, rs);
        }
        return returnList;
    }


    public boolean updateOrganization(OrganizationRegistrationTO org) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        boolean status = false;

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);
            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLEditOrganization());

            int i = 1;

            String orgType = org.getOrgType();
            String ngoType = org.getNgoType();

            if (!orgType.equals("NGO")) {
                ngoType = "";
            } else {
                ngoType = "NGO-" + ngoType;
            }
            preparedStatement.setString(1, orgType);
            preparedStatement.setString(2, ngoType);

            preparedStatement.setString(3, org.getContactPerson());
            preparedStatement.setString(4, org.getOrgName());
            preparedStatement.setBoolean(5, Boolean.getBoolean(org.getStatus()));
            preparedStatement.setString(6, org.getOrgAddress());
            preparedStatement.setString(7, org.getContactNumber());
            preparedStatement.setString(8, org.getEmailAddress());
            preparedStatement.setString(9, org.getCountryOfOrigin());
            preparedStatement.setString(10, org.getFacilitiesAvailable());
            preparedStatement.setString(11, org.getComments());
            preparedStatement.setDate(12, new java.sql.Date(new java.util.Date().getTime()));
            preparedStatement.setBoolean(13, org.isSriLankan());
            preparedStatement.setDate(14, org.getPeriodEndDate());
            preparedStatement.setString(15, org.getOrgCode());
            preparedStatement.execute();


//
//            String userName = org.getUsername();
//            String password = org.getPassword();
//
//            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationRegistrationUserUpdate(org.getOrgCode()));
//            preparedStatement.setString(1, userName);
//            preparedStatement.setString(2, password);
//            preparedStatement.executeUpdate();

            // before adding, delete existing relationships
            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationWorkingAreaInfoDeletion(org.getOrgCode()));
            preparedStatement.execute();

            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationDistrictInsertion());
            Iterator workingAreasIter = org.getWorkingAreas().iterator();
            while (workingAreasIter.hasNext()) {
                String workingArea = (String) workingAreasIter.next();
                // set the organization code
                preparedStatement.setString(1, org.getOrgCode());
                preparedStatement.setString(2, workingArea);
                preparedStatement.executeUpdate();
            }

            // before adding, delete existing relationships
            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationSectorsInfoDeletion(org.getOrgCode()));
            preparedStatement.execute();

            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationSectors());
            Iterator sectorIter = org.getSectors().iterator();
            while (sectorIter.hasNext()) {
                String sector = (String) sectorIter.next();
                // set the organization code
                preparedStatement.setString(1, org.getOrgCode());
                preparedStatement.setString(2, sector);
                preparedStatement.executeUpdate();
            }

            connection.commit();
            connection.setAutoCommit(true);

            status = true;

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


    public boolean addOrganization(OrganizationRegistrationTO org) throws SQLException, Exception {

        Connection connection = null;
        PreparedStatement preparedStatement = null;

        boolean status = false;

        //first check for the user
        if (isUserExisting(org.getUsername())) {
            throw new Exception("The user name is already taken. Please put in a new user name. click <a href='Registration.jsp?action=add'>here</a> to register again ");
        }

        if (hasOrgAlreadyRegisterd(org.getOrgName())) {
            throw new Exception("The organization name is already registered.  click <a href='Registration.jsp?action=add'>here</a> to go back to registration ");
        }

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);
            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationRegistration());
            String code = getOrgCode();
            int i = 1;

            String orgType = org.getOrgType();
            String ngoType = org.getNgoType();

            if (!orgType.equals("NGO")) {
                ngoType = "";
            } else {
                ngoType = "NGO-" + ngoType;
            }
            preparedStatement.setString(1, orgType);
            preparedStatement.setString(2, ngoType);
            preparedStatement.setString(3, code);
            preparedStatement.setString(4, org.getContactPerson());
            preparedStatement.setString(5, org.getOrgName());
            preparedStatement.setBoolean(6, Boolean.getBoolean(org.getStatus()));
            preparedStatement.setString(7, org.getOrgAddress());
            preparedStatement.setString(8, org.getContactNumber());
            preparedStatement.setString(9, org.getEmailAddress());
            preparedStatement.setString(10, org.getCountryOfOrigin());
            preparedStatement.setString(11, org.getFacilitiesAvailable());
            preparedStatement.setString(12, org.getComments());
            preparedStatement.setDate(13, new java.sql.Date(new java.util.Date().getTime()));
            preparedStatement.setBoolean(14, org.isSriLankan());
            preparedStatement.setDate(15, org.getPeriodEndDate());
            preparedStatement.executeUpdate();


            String userName = org.getUsername();
            String password = org.getPassword();

            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationRegistrationUser());
            preparedStatement.setString(1, userName);
            preparedStatement.setString(2, password);
            preparedStatement.setString(3, code);
            preparedStatement.executeUpdate();

            /**
             * adding user Role to user role table
             */
            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationUserRole());
            preparedStatement.setString(1, userName);
            preparedStatement.setString(2, "2");
            preparedStatement.executeUpdate();
            //just try to put a record to the mambo database. even If it fails move on
            try {
                MamboDataAccessManager mamboDAM = new MamboDataAccessManager();
                mamboDAM.addUserToMamboDatabase(org.getContactPerson(),
                        userName,
                        password,
                        org.getEmailAddress());
            } catch (Exception e) {
                //eat up the exception and move on
                e.printStackTrace();
            }

            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationDistrictInsertion());

            Iterator workingAreasIter = org.getWorkingAreas().iterator();
            while (workingAreasIter.hasNext()) {
                String workingArea = (String) workingAreasIter.next();
                // set the organization code
                preparedStatement.setString(1, code);
                preparedStatement.setString(2, workingArea);
                preparedStatement.executeUpdate();
            }

            preparedStatement = connection.prepareStatement(SQLGenerator.getSQLForOrganizationSectors());

            Iterator sectorIter = org.getSectors().iterator();
            while (sectorIter.hasNext()) {
                String sector = (String) sectorIter.next();
                // set the organization code
                preparedStatement.setString(1, code);
                preparedStatement.setString(2, sector);
                preparedStatement.executeUpdate();
            }

            connection.commit();
            connection.setAutoCommit(true);

            status = true;

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

    public User getUser(String userName) throws Exception {
        Connection conn = DBConnection.createConnection();
        PreparedStatement ps = null;
        ResultSet rs = null;
        User user = new User();
        try {
            SQLGenerator sqlGen = new SQLGenerator();
            String sql = sqlGen.getSQLForGetUser(userName);
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();

            while (rs.next()) {
                user.setUserName(rs.getString(TableColumns.USER_NAME));
                user.setPassword(rs.getString(TableColumns.PASSWORD));
                user.setOrganization(rs.getString(TableColumns.ORG_CODE));
            }
        } finally {
            closeConnections(conn, ps, rs);
        }
        return user;

    }

}

