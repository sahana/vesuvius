/*

* Created on Dec 30, 2004

*

* To change the template for this generated file go to

* Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

*/

package org.erms.db;


import org.erms.business.*;

import java.sql.*;
import java.util.*;


/**
 * @author Administrator
 *         <p/>
 *         <p/>
 *         <p/>
 *         To change the template for this generated type comment go to
 *         <p/>
 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

public class DataAccessManager {
    private static Collection allDistricts = null;
    private static Collection allCategories = null;
    private static Collection allPriorities = null;
    private static Collection allFulfillStatuses = null;
    private static Collection allSearchStatuses = null;

    private static Collection allSiteTypes = null;
    private static HashMap  allSiteMap = new HashMap();




    public DataAccessManager() {
    }

    public Collection getAllSiteTypes()throws SQLException,Exception{
        if(allSiteTypes == null){
            allSiteTypes = new ArrayList();
            Connection conn = DBConnection.createConnection();
            Statement s = null;
            ResultSet rs = null;

            try {

                String sql = SQLGenerator.getSQLForAllSites();

                s = conn.createStatement();

                rs = s.executeQuery(sql);


                String itemCode = null;

                String itemName = null;

                KeyValueDTO dto = null;


                while (rs.next()) {

                    itemCode = rs.getString(DBConstants.TableSiteType.SITE_TYPE_CODE);

                    itemName = rs.getString(DBConstants.TableSiteType.SITE_TYPE);
                    allSiteMap.put(itemCode,itemName);

                    dto = new KeyValueDTO();

                    dto.setDbTableCode(itemCode);

                    dto.setDisplayValue(itemName);

                    allSiteTypes.add(dto);

                }

            } finally {

                closeConnections(conn,s,rs);

            }
        }
        return allSiteTypes;
    }


    public Collection getAllCategories() throws SQLException, Exception {
        if (allCategories == null) {
            allCategories = loadAllCategories();
        }
        return allCategories;

    }

    public Collection getAllSearchStatuses() throws SQLException, Exception {
        if (allSearchStatuses == null) {
            allSearchStatuses = loadAllSearchStatuses();
        }
        return allSearchStatuses;

    }

    private static Collection loadAllCategories() throws SQLException, Exception {


        Connection conn = DBConnection.createConnection();

        List categoryDTOs = new ArrayList();
        Statement s = null;
        ResultSet rs = null;

        try {

            String sql = SQLGenerator.getSQLForAllCategories();

            s = conn.createStatement();

            rs = s.executeQuery(sql);


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

            closeConnections(conn,s,rs);

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

        Statement s = null;
        ResultSet rs = null;

        try {

            String sql = SQLGenerator.getSQLForAllPriorities();

            s = conn.createStatement();

            rs = s.executeQuery(sql);

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
            closeConnections(conn,s,rs);
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

            preparedStatement.setString(1, request.getOrgCode());

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

            preparedStatement.setString(12, request.getSiteContact());


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
        return loadAllOrganizationNames();
    }


    private Collection loadAllOrganizationNames() throws SQLException, Exception {

        Connection conn = DBConnection.createConnection();

        Collection orgDTOs = new ArrayList();
        Statement s = null;
        ResultSet rs = null;

        try {

            String sql = SQLGenerator.getSQLForAllOrganizationNames();

            s = conn.createStatement();

            rs = s.executeQuery(sql);

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
            closeConnections(conn,s,rs);
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

        Statement s  = null;
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

            closeConnections(conn,s, rs);

        }


        return districtDTOs;

    }


    public Collection getAllStatuses() throws SQLException, Exception {
        if (allFulfillStatuses == null) {
            allFulfillStatuses = loadAllStatuses();
        }
        return allFulfillStatuses;

    }

    private Collection loadAllSearchStatuses() throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        List statusDTOs = new ArrayList();

        Statement s = null;
        ResultSet rs = null;
        try {
            String sql = SQLGenerator.getSQLForAllSearchStatuses();
            s = conn.createStatement();
            rs = s.executeQuery(sql);
            String itemCode = null;
            String itemName = null;
            KeyValueDTO dto = null;
            while (rs.next()) {
                itemCode = rs.getString(DBConstants.TableColumns.REQUEST_STATUS);
                itemName = rs.getString(DBConstants.TableColumns.REQUEST_STATUS_DESCRIPTION);
                dto = new KeyValueDTO();
                dto.setDbTableCode(itemCode);
                dto.setDisplayValue(itemName);
                statusDTOs.add(dto);
            }
        } finally {
            closeConnections(conn,s,rs);
        }
        return statusDTOs;
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

                itemCode = rs.getString(DBConstants.TableColumns.FULLFILL_STATUS);

                itemName = rs.getString(DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION);

                dto = new KeyValueDTO();

                dto.setDbTableCode(itemCode);

                dto.setDisplayValue(itemName);

                statusDTOs.add(dto);

            }

        } finally {

            closeConnections(conn,s,rs);

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

    public RequestInfo getRequest(String requestDetailID) throws SQLException, Exception {
        if (requestDetailID == null || Integer.parseInt(requestDetailID) == 0)
            throw new Exception("The request detail ID is null");

        Statement statement = null;
        ResultSet resultSet = null;

        RequestInfo reqInfo = new RequestInfo();


        Connection connection = DBConnection.createConnection();
        RequestTO requestTO = new RequestTO();
        RequestDetailTO requestDetailTO = new RequestDetailTO();
//

        try {
            String sql = SQLGenerator.getSQLGetRequestDetail(requestDetailID);

            System.out.print("SQL QUARY       %%%%%%%%%%%%%%%%%%%%%% "+sql);
            statement = connection.createStatement();
            resultSet = statement.executeQuery(sql);

            //Write this code with if rather than the while , thee is no way  the loop cn go to the
            //loop towice unless the MySQL has messed up

            if (resultSet.next()) {
                //fill the request detail TO
                requestDetailTO.setRequestDetailID(resultSet.getString(DBConstants.TableColumns.REQUEST_DETAIL_ID));
                requestDetailTO.setRequestID(resultSet.getString(DBConstants.TableColumns.REQUEST_ID));
                requestDetailTO.setCategory(resultSet.getString(DBConstants.TableColumns.CATEGORY));
                requestDetailTO.setItem(resultSet.getString(DBConstants.TableColumns.ITEM));
                requestDetailTO.setDescription(resultSet.getString(DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION));
                requestDetailTO.setUnit(resultSet.getString(DBConstants.TableColumns.UNIT));
                requestDetailTO.setQuantity(resultSet.getInt(DBConstants.TableColumns.QUANTITY));
                requestDetailTO.setPriority(resultSet.getString(DBConstants.TableColumns.PRIORITY_LEVEL));

                requestDetailTO.setStatus(resultSet.getString(DBConstants.TableColumns.REQUEST_STATUS));


                //set the category name
                //TODO there should be a better way to do that
                Iterator it = allCategories.iterator();
                while (it.hasNext()) {
                    KeyValueDTO keypair = (KeyValueDTO) it.next();
                    if (requestDetailTO.getCategory().equals(keypair.getDbTableCode())) {
                        requestDetailTO.setCategoryName(keypair.getDisplayValue());
                        break;
                    }
                }

                requestTO.setRequestID(resultSet.getString(DBConstants.TableColumns.REQUEST_ID));
                requestTO.setOrgCode(resultSet.getString(DBConstants.TableColumns.ORG_CODE));
                requestTO.setCreateDate(resultSet.getDate(DBConstants.TableColumns.CREATE_DATE));
                requestTO.setRequestedDate(resultSet.getDate(DBConstants.TableColumns.REQUEST_DATE));
                requestTO.setCallerName(resultSet.getString(DBConstants.TableColumns.CALLER_NAME));
                requestTO.setCallerAddress(resultSet.getString(DBConstants.TableColumns.CALLER_ADDRESS));
                requestTO.setCallerContactNumber(resultSet.getString(DBConstants.TableColumns.CALLER_CONTACT_NO));
                requestTO.setDescription(resultSet.getString(DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION));
                requestTO.setSiteType(resultSet.getString(DBConstants.TableColumns.SITE_TYPE));
                requestTO.setSiteDistrict(resultSet.getString(DBConstants.TableColumns.SITE_DISTRICT));
                requestTO.setSiteArea(resultSet.getString(DBConstants.TableColumns.SITE_AREA));
                requestTO.setSiteName(resultSet.getString(DBConstants.TableColumns.SITE_NAME));
                requestTO.setOrgName(resultSet.getString(DBConstants.TableColumns.ORG_NAME));
                requestTO.setOrgContact(resultSet.getString(DBConstants.TableColumns.ORG_CONTACT_NUMBER));
                requestTO.setSiteContact(resultSet.getString(DBConstants.TableColumns.SITE_CONTACT));                


                List requestDetailTOs = new ArrayList();
                requestDetailTOs.add(requestDetailTO);

                requestTO.setRequestDetails(requestDetailTOs);
                reqInfo.setRequest(requestTO);
            }else{
                throw new RuntimeException("A RequetDetailInfo with ID= \'"+requestDetailID + "\' Does not exists ");
            }


            // Now get the services who have serviced this request.
            String sqlFulfillServices = SQLGenerator.getSQLGetServiceDetailsForRequest(requestDetailID);
            statement = connection.createStatement();
            ResultSet resultSet1 = statement.executeQuery(sqlFulfillServices);


            List servicerList = new ArrayList();

            while (resultSet1.next()) {
                RequestFulfillDetailTO requestFulfillDetailTO = new RequestFulfillDetailTO();
                requestFulfillDetailTO = new RequestFulfillDetailTO();
                requestFulfillDetailTO.setOrgCode(resultSet1.getString(DBConstants.TableColumns.ORG_CODE));
                requestFulfillDetailTO.setOrgContact(resultSet1.getString(DBConstants.TableColumns.ORG_ADDRESS));
                requestFulfillDetailTO.setOrgName(resultSet1.getString(DBConstants.TableColumns.ORG_NAME));
                requestFulfillDetailTO.setQuantity(resultSet1.getString(DBConstants.TableColumns.SERVICE_QTY));
                requestFulfillDetailTO.setStatus(resultSet1.getString(DBConstants.TableColumns.FULLFILL_STATUS));
                requestFulfillDetailTO.setFulfillID(resultSet1.getString(DBConstants.TableColumns.FUlFILL_ID));
                requestFulfillDetailTO.setRequestDetailID(requestDetailID);
                servicerList.add(requestFulfillDetailTO);
            }
            reqInfo.setServices(servicerList);
        } finally {
            closeConnections(connection, statement, resultSet);
        }
        return reqInfo;
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

    public void fulfillRequest(RequestFulfillDetailTO fullFillment) throws Exception {

        Connection connection = null;

        PreparedStatement preparedStatement = null;

        ResultSet resultSet = null;


        try {

            connection = DBConnection.createConnection();

            connection.setAutoCommit(false);



            // Setting the Request Header data.

            String sqlAddFulFillRequestString = SQLGenerator.getSQLAddFulFillRequest();


            preparedStatement = connection.prepareStatement(sqlAddFulFillRequestString);


            preparedStatement.setString(1, fullFillment.getOrgCode());

            preparedStatement.setString(2, fullFillment.getRequestDetailID());

            preparedStatement.setString(3, fullFillment.getQuantity());

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

    public void fulfillRequest(RequestFulfillDetailTO fullFillment,
                               Collection oldFullFillment,
                               Collection newFullFillment, String status,String reqDetailID) throws Exception {

        //validate this
        if (fullFillment != null) {
            fulfillRequest(fullFillment);
        }

        if (oldFullFillment.size() != newFullFillment.size()) {
        }

        Connection connection = null;
        PreparedStatement preparedStatement = null;
        connection = null;
        ResultSet resultSet = null;

        if (oldFullFillment != null || newFullFillment != null) {

            try {

                Iterator itrOld = oldFullFillment.iterator();
                Iterator itrNew = newFullFillment.iterator();
                RequestFulfillDetailTO oldReqFTO = null;
                RequestFulfillDetailTO newReqFTO = null;

                connection = DBConnection.createConnection();
                connection.setAutoCommit(false);
                while (itrOld.hasNext()) {
                    oldReqFTO = (RequestFulfillDetailTO) itrOld.next();
                    newReqFTO = (RequestFulfillDetailTO) itrNew.next();
                    if (!oldReqFTO.getFulfillID().equals(newReqFTO.getFulfillID())) {
                        throw new RuntimeException("getFulfillID mismatched.");
                    }

                    if (!oldReqFTO.getStatus().equals(newReqFTO.getStatus())) {

                        String sqlUpdateFulFillRequestString = SQLGenerator.SQLupdateFulFillRequest();
                        String sqlAddFulFillStausChanged = SQLGenerator.getSQLAddFulFillStausChanged();

                        System.out.println(sqlUpdateFulFillRequestString);
                        preparedStatement = connection.prepareStatement(sqlUpdateFulFillRequestString);


                        preparedStatement.setString(1, newReqFTO.getStatus());
                        preparedStatement.setString(2, oldReqFTO.getFulfillID());
                        preparedStatement.executeUpdate();
                        preparedStatement.executeUpdate();


                        PreparedStatement preparedStatement1 = connection.prepareStatement(sqlAddFulFillStausChanged);
                        preparedStatement1.setString(1, oldReqFTO.getFulfillID());
                        preparedStatement1.setTimestamp(2, new Timestamp(System.currentTimeMillis()));
                        preparedStatement1.setString(3, newReqFTO.getStatus());
                        preparedStatement1.executeUpdate();

                        System.out.println("After commit");
                    }
                }
                if (status!= null) {
                    String sqlreqStatusChangeStatement = SQLGenerator.getSQLupdateRequestStatus();
                    System.out.println(sqlreqStatusChangeStatement);
                    PreparedStatement reqStatusChangeStatement = connection.prepareStatement(sqlreqStatusChangeStatement);
                    reqStatusChangeStatement.setString(1, status);
                    reqStatusChangeStatement.setString(2, reqDetailID);
                    reqStatusChangeStatement.executeUpdate();
                    reqStatusChangeStatement.executeUpdate();
                }
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



            // Setting the Request Header data.

            String sqlSearchString = SQLGenerator.getSQLForSearchCriteria();


            preparedStatement = connection.prepareStatement(sqlSearchString);
            preparedStatement.setString(1, searchCriteria.getCategory());
            preparedStatement.setString(2, searchCriteria.getCategory());
            preparedStatement.setString(3, searchCriteria.getOrganization());
            preparedStatement.setString(4, searchCriteria.getOrganization());
            preparedStatement.setString(5, searchCriteria.getSiteName());
            preparedStatement.setString(6, searchCriteria.getSiteName());
            preparedStatement.setString(7, searchCriteria.getSiteDistrict());
            preparedStatement.setString(8, searchCriteria.getSiteDistrict());
            preparedStatement.setString(9, searchCriteria.getItem());
            preparedStatement.setString(10, searchCriteria.getItem());
            preparedStatement.setString(11, searchCriteria.getPriority());
            preparedStatement.setString(12, searchCriteria.getPriority());
            preparedStatement.setString(13, searchCriteria.getStatus());
            preparedStatement.setString(14, searchCriteria.getStatus());

/*          preparedStatement.setDate(15, searchCriteria.getRequestDateFrom());
preparedStatement.setDate(16, searchCriteria.getRequestDateTo());
preparedStatement.setDate(17, searchCriteria.getRequestDateFrom());
preparedStatement.setDate(18, searchCriteria.getRequestDateTo());
*/
            resultSet = preparedStatement.executeQuery();


            List returnSearchTOs = new ArrayList();

            RequestSearchTO requestSearchTo = new RequestSearchTO();


            while (resultSet.next()) {

                requestSearchTo = new RequestSearchTO();

                requestSearchTo.setRequestDetId(resultSet.getString(DBConstants.TableColumns.REQUEST_DETAIL_ID));
                requestSearchTo.setItem(resultSet.getString(DBConstants.TableColumns.ITEM));
                requestSearchTo.setCategory(resultSet.getString(DBConstants.TableColumns.CATEGORY));
                requestSearchTo.setPriority(resultSet.getString(DBConstants.TableColumns.PRIORITY_LEVEL));
                requestSearchTo.setQuantity(Integer.parseInt(resultSet.getString(DBConstants.TableColumns.QUANTITY)));
                requestSearchTo.setSiteName(resultSet.getString(DBConstants.TableColumns.SITE_NAME));
                requestSearchTo.setSiteArea(resultSet.getString(DBConstants.TableColumns.SITE_AREA));
                requestSearchTo.setSiteDistrict(resultSet.getString(DBConstants.TableColumns.SITE_DISTRICT));
                requestSearchTo.setStatus(resultSet.getString(DBConstants.TableColumns.FULLFILL_STATUS));
                requestSearchTo.setUnits(resultSet.getString(DBConstants.TableColumns.UNIT));
                requestSearchTo.setSiteType(resultSet.getString(DBConstants.TableColumns.SITE_TYPE));


                returnSearchTOs.add(requestSearchTo);

            }


            return returnSearchTOs;

        } finally {

            closeConnections(connection, preparedStatement, resultSet);

        }

    }


    public void addOrganization(OrganizationRegistrationTO org) throws SQLException {

        Connection connection = null;

        PreparedStatement preparedStatement = null;


        try {

            try {

                connection = DBConnection.createConnection();

            } catch (Exception e) {

                throw new SQLException(e.getMessage());

            }

            preparedStatement = connection.

                    prepareStatement(SQLGenerator.getSQLForOrganizationRegistration());

            int i = 1;

            preparedStatement.setString(i++, org.getOrgCode());

            preparedStatement.setString(i++, org.getContactPerson());

            preparedStatement.setString(i++, org.getOrgName());

            preparedStatement.setBoolean(i++, Boolean.getBoolean(org.getStatus()));

            preparedStatement.setString(i++, org.getOrgAddress());

            preparedStatement.setString(i++, org.getContactNumber());

            preparedStatement.setString(i++, org.getEmailAddress());

            preparedStatement.setString(i++, org.getCountryOfOrigin());

            preparedStatement.setString(i++, org.getFacilitiesAvailable());

            preparedStatement.setString(i++, org.getWorkingAreas());

            preparedStatement.setString(i++, org.getComments());

            preparedStatement.executeUpdate();

        } finally {

            closeStatement(preparedStatement);

            closeConnection(connection);

        }


    }


//    /**
//     * This method is purely for testing purposes.
//     *
//     * @param args
//     */
//
//    public static void main
//
//            (String[] args) {
//
//        DataAccessManager app = new DataAccessManager();
//
//        try {
//
//
//            Collection newL = new Vector();
//
//            RequestFulfillDetailTO reqfNew = new RequestFulfillDetailTO();
//            reqfNew.setFulfillID("71");
//            reqfNew.setStatus("Delived");
//            reqfNew.setQuantity("44");
//            newL.add(reqfNew);
//
//            reqfNew = new RequestFulfillDetailTO();
//            reqfNew.setFulfillID("72");
//            reqfNew.setStatus("Delived");
//            reqfNew.setQuantity("444");
//            newL.add(reqfNew);
//
//
//            Collection oldL = new Vector();
//
//            RequestFulfillDetailTO reqfOld = new RequestFulfillDetailTO();
//            reqfOld.setFulfillID("71");
//            reqfOld.setOrgCode("000001");
//            oldL.add(reqfOld);
//
//            reqfOld = new RequestFulfillDetailTO();
//            reqfOld.setFulfillID("72");
//            reqfOld.setOrgCode("000001");
//            oldL.add(reqfOld);
//
//
//
//            app.fulfillRequest(null,oldL,newL);
//
//            Collection c1 = app.getAllCategories();
//
//            Collection c2 = app.getAllDistricts();
//
//            Collection c3 = app.getAllOrganizationNames();
//
//            Collection c4 = app.getAllPriorities();
//
//            Collection c5 = app.getAllStatuses();
//
//
//            System.out.println("done");
//
//        } catch (SQLException e) {
//
//            // TODO Auto-generated catch block
//
//            e.printStackTrace();
//
//        } catch (Exception e) {
//
//            // TODO Auto-generated catch block
//
//            e.printStackTrace();
//
//        }
//
//    }


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

                String realpassword = rs.getString(2);
                String orgCode = rs.getString(3);
                String organization = rs.getString(4);
                System.out.println(realpassword);
                System.out.println(organization);

                User user = new User(userName, organization);
                user.setOrgCode(orgCode);

                if (realpassword.equals(password)) {

                    return user;

                }

            }

        } finally {

            closeConnections(conn,s,rs);

        }


        return null;

    }


    public boolean hasOrgAlreadyRegisterd(String orgCode) throws Exception {

        Connection conn = DBConnection.createConnection();

        PreparedStatement ps = null;

        ResultSet rs = null;

        try {

            String sql = SQLGenerator.getSQLForCountOrganizationCode();

            ps = conn.prepareStatement(sql);

            ps.setString(1, orgCode);

            rs = ps.executeQuery();

            if (rs.next()) {

                if (rs.getInt(1) > 0) {

                    return true;

                }

            }

            return false;

        } finally {

            closeConnections(conn,ps,rs);
        }

    }


    public String getSiteTypeName(String siteTypeCode){
         return (String)allSiteMap.get(siteTypeCode);
    }
}


