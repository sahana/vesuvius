/*

* Created on Dec 30, 2004

*

* To change the template for this generated file go to

* Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

*/

package org.erms.db;


import org.erms.business.*;
import org.sahana.share.db.AbstractDataAccessManager;
import org.sahana.share.db.DBConstants;
import org.sahana.share.db.DBConnection;
import org.sahana.share.utils.KeyValueDTO;

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

public class DataAccessManager extends AbstractDataAccessManager{
    public DataAccessManager() throws Exception {
        super();
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

            System.out.print("SQL QUARY       %%%%%%%%%%%%%%%%%%%%%% " + sql);
            statement = connection.createStatement();
            resultSet = statement.executeQuery(sql);

            //Write this code with if rather than the while , thee is no way  the loop cn go to the
            //loop towice unless the MySQL has messed up

            if (resultSet.next()) {
                //fill the request detail TO
                requestDetailTO.setRequestDetailID(resultSet.getString(DBConstants.Requestdetail.REQUEST_DETAIL_ID));
                requestDetailTO.setRequestID(resultSet.getString(DBConstants.Requestdetail.REQUEST_ID));
                requestDetailTO.setCategory(resultSet.getString(DBConstants.Requestdetail.CATEGORY));
                requestDetailTO.setItem(resultSet.getString(DBConstants.Requestdetail.ITEM));
                requestDetailTO.setDescription(resultSet.getString(DBConstants.Requestdetail.FULLFILL_STATUS_DESCRIPTION));
                requestDetailTO.setUnit(resultSet.getString(DBConstants.Requestdetail.UNIT));
                requestDetailTO.setQuantity(resultSet.getInt(DBConstants.Requestdetail.QUANTITY));
                requestDetailTO.setPriority(resultSet.getString(DBConstants.Requestdetail.PRIORITY_LEVEL));

                requestDetailTO.setStatus(resultSet.getString(DBConstants.Requestdetail.REQUEST_STATUS));


                //set the category name
                //TODO there should be a better way to do that
                Iterator it = allCategories.getValuesInOrder().iterator();
                while (it.hasNext()) {
                    KeyValueDTO keypair = (KeyValueDTO) it.next();
                    if (requestDetailTO.getCategory().equals(keypair.getDbTableCode())) {
                        requestDetailTO.setCategoryName(keypair.getDisplayValue());
                        break;
                    }
                }

                requestTO.setRequestID(resultSet.getString(DBConstants.Requestheader.REQUEST_ID));
                requestTO.setOrgCode(resultSet.getString(DBConstants.Requestheader.ORG_CODE));
                requestTO.setCreateDate(resultSet.getDate(DBConstants.Requestheader.CREATE_DATE));
                requestTO.setRequestedDate(resultSet.getDate(DBConstants.Requestheader.REQUEST_DATE));
                requestTO.setCallerName(resultSet.getString(DBConstants.Requestheader.CALLER_NAME));
                requestTO.setCallerAddress(resultSet.getString(DBConstants.Requestheader.CALLER_ADDRESS));
                requestTO.setCallerContactNumber(resultSet.getString(DBConstants.Requestheader.CALLER_CONTACT_NO));
                requestTO.setDescription(resultSet.getString(DBConstants.Requestheader.FULLFILL_STATUS_DESCRIPTION));
                requestTO.setSiteType(resultSet.getString(DBConstants.Requestheader.SITE_TYPE));
                requestTO.setSiteDistrict(resultSet.getString(DBConstants.Requestheader.SITE_DISTRICT));
                requestTO.setSiteArea(resultSet.getString(DBConstants.Requestheader.SITE_AREA));
                requestTO.setSiteName(resultSet.getString(DBConstants.Requestheader.SITE_NAME));
                requestTO.setOrgName(resultSet.getString(DBConstants.Organization.ORG_NAME));
                requestTO.setOrgContact(resultSet.getString(DBConstants.Organization.ORG_CONTACT_NUMBER));
                requestTO.setSiteContact(resultSet.getString(DBConstants.Requestheader.SITE_CONTACT));


                Vector requestDetailTOs = new Vector();
                requestDetailTOs.add(requestDetailTO);

                requestTO.setRequestDetails(requestDetailTOs);
                reqInfo.setRequest(requestTO);
            } else {
                throw new RuntimeException("A RequetDetailInfo with ID= \'" + requestDetailID + "\' Does not exists ");
            }


            // Now get the services who have serviced this request.
            String sqlFulfillServices = SQLGenerator.getSQLGetServiceDetailsForRequest(requestDetailID);
            statement = connection.createStatement();
            ResultSet resultSet1 = statement.executeQuery(sqlFulfillServices);


            List servicerList = new ArrayList();

            while (resultSet1.next()) {
                RequestFulfillDetailTO requestFulfillDetailTO = new RequestFulfillDetailTO();
                requestFulfillDetailTO = new RequestFulfillDetailTO();
                requestFulfillDetailTO.setOrgCode(resultSet1.getString(DBConstants.Requestfulfill.ORG_CODE));
                requestFulfillDetailTO.setOrgContact(resultSet1.getString(DBConstants.Organization.ORG_ADDRESS));
                requestFulfillDetailTO.setOrgName(resultSet1.getString(DBConstants.Organization.ORG_NAME));
                requestFulfillDetailTO.setQuantity(resultSet1.getString(DBConstants.Requestfulfill.SERVICE_QTY));
                requestFulfillDetailTO.setStatus(resultSet1.getString(DBConstants.Requestfulfill.FULLFILL_STATUS));
                requestFulfillDetailTO.setFulfillID(resultSet1.getString(DBConstants.Requestfulfill.FUlFILL_ID));
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
                               Collection newFullFillment, String status, String reqDetailID) throws Exception {

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
                if (status != null) {
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
            preparedStatement.setString(6, ususalWildcard2SQLWildCard(searchCriteria.getSiteName()));
            preparedStatement.setString(7, searchCriteria.getSiteDistrict());
            preparedStatement.setString(8, searchCriteria.getSiteDistrict());
            preparedStatement.setString(9, searchCriteria.getItem());
            preparedStatement.setString(10, ususalWildcard2SQLWildCard(searchCriteria.getItem()));
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

                requestSearchTo.setRequestDetId(resultSet.getString(DBConstants.Requestdetail.REQUEST_DETAIL_ID));
                requestSearchTo.setItem(resultSet.getString(DBConstants.Requestdetail.ITEM));
                requestSearchTo.setCategory(resultSet.getString(DBConstants.Requestdetail.CATEGORY));
                requestSearchTo.setPriority(resultSet.getString(DBConstants.Requestdetail.PRIORITY_LEVEL));
                requestSearchTo.setQuantity(Integer.parseInt(resultSet.getString(DBConstants.Requestdetail.QUANTITY)));
                requestSearchTo.setSiteName(resultSet.getString(DBConstants.Requestheader.SITE_NAME));
                requestSearchTo.setSiteArea(resultSet.getString(DBConstants.Requestheader.SITE_AREA));
                requestSearchTo.setSiteDistrict(resultSet.getString(DBConstants.Requestheader.SITE_DISTRICT));
                requestSearchTo.setStatus(resultSet.getString(DBConstants.Requestdetail.REQUEST_STATUS));
                requestSearchTo.setUnits(resultSet.getString(DBConstants.Requestdetail.UNIT));
                requestSearchTo.setSiteType(resultSet.getString(DBConstants.Requestheader.SITE_TYPE));


                returnSearchTOs.add(requestSearchTo);

            }


            return returnSearchTOs;

        } finally {

            closeConnections(connection, preparedStatement, resultSet);

        }

    }

    public User loginSuccess(String userName, String password) throws SQLException, Exception {
           Connection conn = null;
            Statement s = null;
            ResultSet rs = null;

           try {
               conn = DBConnection.createConnection();

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

            } catch (Exception e){
                  e.printStackTrace();
            }finally {

                closeConnections(conn,s,rs);

            }


            return null;

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

            closeConnections(conn, ps, rs);
        }

    }



}


