/*

 * Created on Dec 30, 2004

 *

 * To change the template for this generated file go to

 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

 */

package org.erms.db;

import org.sahana.share.db.AbstractDataAccessManager;
import org.sahana.share.db.DBConstants;


/**

 * @author Administrator

 * <p/>

 * To change the template for this generated type comment go to

 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

 */

public class SQLGenerator extends AbstractDataAccessManager{

    public SQLGenerator() throws Exception {
    }


     public static String getSQLForAllSearchStatuses() {
        return "SELECT "
            + DBConstants.Requeststatus.REQUEST_STATUS + ","
            + DBConstants.Requeststatus.REQUEST_STATUS_DESCRIPTION
            + " FROM "
            + DBConstants.Requeststatus.TABLENAME;

    }


    /**

     * returns the sql statement for inserting records into the request header

     *

     * @return

     */

    public static String getSQLAddRequestHeader() {

        return "INSERT into "

            + DBConstants.Requestheader.TABLENAME

            + " ("

            + DBConstants.Requestheader.ORG_CODE + ", "

            + DBConstants.Requestheader.CREATE_DATE + ", "

            + DBConstants.Requestheader.REQUEST_DATE + ", "

            + DBConstants.Requestheader.CALLER_NAME + ", "

            + DBConstants.Requestheader.CALLER_ADDRESS + ", "

            + DBConstants.Requestheader.CALLER_CONTACT_NO + ", "

            + DBConstants.Requestheader.FULLFILL_STATUS_DESCRIPTION + ", "

            + DBConstants.Requestheader.SITE_TYPE + ", "

            + DBConstants.Requestheader.SITE_DISTRICT + ", "

            + DBConstants.Requestheader.SITE_AREA + ", "

            + DBConstants.Requestheader.SITE_NAME + ", "

            + DBConstants.Requestheader.SITE_CONTACT

            + ") "

            + " VALUES "

            + "(?,?,?,?,?,?,?,?,?,?,?,?)";

    }



    /**

     * returns the sql statement for inserting records into the request detail

     *

     * @return

     */

    public static String getSQLAddRequestDetail() {

        return "INSERT into "

            + DBConstants.Requestdetail.TABLENAME

            + " ("

            + DBConstants.Requestdetail.REQUEST_ID + ", "

            + DBConstants.Requestdetail.CATEGORY + ", "

            + DBConstants.Requestdetail.ITEM + ", "

            + DBConstants.Requestdetail.FULLFILL_STATUS_DESCRIPTION + ", "

            + DBConstants.Requestdetail.UNIT + ", "

            + DBConstants.Requestdetail.QUANTITY + ", "

            + DBConstants.Requestdetail.PRIORITY_LEVEL  +  ","
            + DBConstants.Requestdetail.REQUEST_STATUS

            + ") "

            + " VALUES "

            + "(?,?,?,?,?,?,?,'Open')";

    }



    /**

     * returns the sql statement for inserting records into the request detail

     *

     * @return

     */

    public static String getSQLAddFulFillRequest() {

        return "INSERT into "

            + DBConstants.Requestfulfill.TABLENAME

            + " ("

            + DBConstants.Requestfulfill.ORG_CODE + ", "

            + DBConstants.Requestfulfill.REQUEST_DETAIL_ID + ", "

            + DBConstants.Requestfulfill.SERVICE_QTY + ", "

            + DBConstants.Requestfulfill.FULLFILL_STATUS

            + ") "

            + " VALUES "

            + "(?,?,?,?)";

    }

    public static String getSQLAddFulFillStausChanged() {

        return "INSERT into "

            + DBConstants.Statushistory.TABLENAME

            + " ("

            + DBConstants.Statushistory.FUlFILL_REAL_ID + ", "

            + DBConstants.Statushistory.STATUS_CHANGED_DATE + ", "

            + DBConstants.Statushistory.CHANGED_STAUS

            + ") "

            + " VALUES "

            + "(?,?,?)";

    }

    public static String SQLupdateFulFillRequest() {

        return "UPDATE "

            + DBConstants.Requestfulfill.TABLENAME

            + " SET "

            + DBConstants.Requestfulfill.FULLFILL_STATUS + "= ?  "

            + "WHERE ("

            + DBConstants.Requestfulfill.REQUEST_FULFILL_ID + "= ? ) ";


    }

    public static String getSQLupdateRequestStatus() {

        return "UPDATE "

            + DBConstants.Requestdetail.TABLENAME

            + " SET "

            + DBConstants.Requestdetail.REQUEST_STATUS + "= ?  "

            + "WHERE ("

            + DBConstants.Requestdetail.REQUEST_DETAIL_ID + "= ? ) ";


    }



    /**

     * Returns the query which will get the request detail To as well the header information.

     *

     * @return

     */

    public static String getSQLGetRequestDetail(String requestDetailID) {



        final String REQ_HEAD = "req_head";

        final String REQ_DET = "req_detail";

        final String REQ_ORG = "org" ;



        return "SELECT "

            // first the detail table details

            + REQ_DET + "." + DBConstants.Requestdetail.REQUEST_DETAIL_ID + ", "

            + REQ_DET + "." + DBConstants.Requestdetail.REQUEST_ID + ", "

            + REQ_DET + "." + DBConstants.Requestdetail.CATEGORY + ", "

            + REQ_DET + "." + DBConstants.Requestdetail.ITEM + ", "

            + REQ_DET + "." + DBConstants.Requestdetail.FULLFILL_STATUS_DESCRIPTION + ", "

            + REQ_DET + "." + DBConstants.Requestdetail.UNIT + ", "

            + REQ_DET + "." + DBConstants.Requestdetail.QUANTITY + ", "

            + REQ_DET + "." + DBConstants.Requestdetail.PRIORITY_LEVEL + ", "

             + REQ_DET + "." + DBConstants.Requestdetail.REQUEST_STATUS + ", "

            // now the header details

            + REQ_HEAD + "." + DBConstants.Requestheader.REQUEST_ID + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.ORG_CODE + ", "



            + REQ_HEAD + "." + DBConstants.Requestheader.CREATE_DATE + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.REQUEST_DATE + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.CALLER_NAME + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.CALLER_ADDRESS + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.CALLER_CONTACT_NO + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.FULLFILL_STATUS_DESCRIPTION + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.SITE_TYPE + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.SITE_DISTRICT + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.SITE_AREA + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.SITE_NAME + ", "

            + REQ_HEAD + "." + DBConstants.Requestheader.SITE_CONTACT + ", "

            + REQ_ORG + "." + DBConstants.Organization.ORG_NAME + ", "

            + REQ_ORG + "." + DBConstants.Organization.ORG_CONTACT_NUMBER

            + " FROM "

            + DBConstants.Requestdetail.TABLENAME + " as " + REQ_DET + ", "

            + DBConstants.Organization.TABLENAME + " as " + REQ_ORG + ", "

            + DBConstants.Requestheader.TABLENAME + " as " + REQ_HEAD



            + " WHERE "

            + REQ_DET + "." + DBConstants.Requestdetail.REQUEST_DETAIL_ID + "=" + requestDetailID

            + " AND "

            + REQ_DET + "." + DBConstants.Requestdetail.REQUEST_ID + "="

            + REQ_HEAD + "." + DBConstants.Requestheader.REQUEST_ID

            + " AND "

            + REQ_HEAD + "." + DBConstants.Requestheader.ORG_CODE + "="

            + REQ_ORG + "." + DBConstants.Organization.ORG_CODE;


    }



    /**

     * Returns the query which will return all the services for that particular request.

     *

     * @return

     */

    public static String getSQLGetServiceDetailsForRequest(String requestDetailID) {



        final String ORG = "ORG";

        final String FULFILL = "FULFILL";



        return "SELECT "

            // first the detail table details

            + ORG + "." + DBConstants.Organization.ORG_CODE + ", "

            + ORG + "." + DBConstants.Organization.ORG_NAME + ", "

            + ORG + "." + DBConstants.Organization.ORG_ADDRESS + ", "

            // now the header details

            + FULFILL + "." + DBConstants.Requestfulfill.SERVICE_QTY + ", "

            + FULFILL + "." + DBConstants.Requestfulfill.FUlFILL_ID + ", "

            + FULFILL + "." + DBConstants.Requestfulfill.FULLFILL_STATUS



            + " FROM "

            + DBConstants.Requestfulfill.TABLENAME + " as " + FULFILL + ", "

            + DBConstants.Organization.TABLENAME + " as " + ORG



            + " WHERE "

            + FULFILL + "." + DBConstants.Requestfulfill.REQUEST_DETAIL_ID + "=" + requestDetailID
            + " AND "

            + FULFILL + "." + DBConstants.Requestfulfill.ORG_CODE + "="

            + ORG + "." + DBConstants.Organization.ORG_CODE;


    }



    /**

     * This method is in progress. need to complete with the appropriate fields.

     * @return

     */

    public static String getSQLForSearchCriteria() {



        final String RQH = "RQH";

        final String RQD = "RQD";



        return "SELECT "

            + RQD + "." + DBConstants.Requestdetail.REQUEST_DETAIL_ID + ", "

            + RQH + "." + DBConstants.Requestheader.FULLFILL_STATUS_DESCRIPTION + ", "

            + RQH + "." + DBConstants.Requestheader.SITE_NAME + ", "

            + RQH + "." + DBConstants.Requestheader.SITE_TYPE + ", "

            + RQH + "." + DBConstants.Requestheader.SITE_DISTRICT + ", "

            + RQH + "." + DBConstants.Requestheader.SITE_AREA + ", "

            + RQD + "." + DBConstants.Requestdetail.CATEGORY + ", "

            + RQD + "." + DBConstants.Requestdetail.REQUEST_STATUS + ", "

            + RQD + "." + DBConstants.Requestdetail.QUANTITY + ", "

            + RQD + "." + DBConstants.Requestdetail.UNIT + ", "

            + RQD + "." + DBConstants.Requestdetail.PRIORITY_LEVEL + ", "

            + RQD + "." + DBConstants.Requestdetail.ITEM

            + " FROM "

            + DBConstants.Requestheader.TABLENAME + " as " + RQH + ", "

            + DBConstants.Requestdetail.TABLENAME + " as " + RQD

            + " WHERE "

            + "(? is null OR (" + DBConstants.Requestdetail.CATEGORY + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.Requestheader.ORG_CODE + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.Requestheader.SITE_NAME + " LIKE ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.Requestheader.SITE_DISTRICT + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.Requestdetail.ITEM + " LIKE ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.Requestdetail.PRIORITY_LEVEL + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.Requestdetail.REQUEST_STATUS + " = ?))"

/*            + " AND "

            + "((? is null OR ? is null) OR (" + DBConstants.TableColumns.REQUEST_DATE + " BETWEEN ? AND ?))"
*/
            + " AND "

            + RQH + "." + DBConstants.Requestheader.REQUEST_ID

            + " = "

            + RQD + "." + DBConstants.Requestdetail.REQUEST_ID

            ;

    }

   /**

    * Gives an sql insert statement to insert values to organization table

    * in following order.

    * OrgCode, ContactPerson, OrgName,Status, OrgAddress, ContactNumber,

    * EmailAddress, CountryOfOrigin, FacilitiesAvailable, WorkingAreas,

    * Comments

    * @return

    */

    public static String getSQLForOrganizationRegistration() {

        return "INSERT into "

            + DBConstants.Organization.TABLENAME

            + " ("

            + DBConstants.Organization.ORG_CODE + ", "

            + DBConstants.Organization.ORG_CONTACT_PERSON + ", "

            + DBConstants.Organization.ORG_NAME + ", "

            + DBConstants.Organization.STATUS + ", "

            + DBConstants.Organization.ORG_ADDRESS + ", "

            + DBConstants.Organization.ORG_CONTACT_NUMBER + ", "

            + DBConstants.Organization.ORG_EMAIL_ADDRESS + ", "

            + DBConstants.Organization.ORG_COUNTRY_OF_ORIGIN + ", "

            + DBConstants.Organization.ORG_FACILITIES_AVAILABLE + ", "

            + DBConstants.Organization.ORG_WORKING_AREAS + ", "

            + DBConstants.Organization.ORG_COMMENTS

            + ") "

            + " VALUES "

            + "(?,?,?,?,?,?,?,?,?,?,?)";

    }



    public static String getSQLForCountOrganizationCode() {

        return "select count(" + DBConstants.Organization.ORG_CODE + ") from " + DBConstants.Organization.TABLENAME +" where "

                + DBConstants.Organization.ORG_CODE + "=?";

    }

    public static String getSQLForLogin(String userName) {
               String ORG = "ORG";
               String USR = "USR";

               String s =  "SELECT "
               + USR + "." + DBConstants.User.USER_NAME + ", "

               + USR + "." + DBConstants.User.PASSWORD + ", "

               + ORG + "." + DBConstants.Organization.ORG_CODE + ", "

               + ORG + "." + DBConstants.Organization.ORG_NAME

               + " FROM "

               + DBConstants.User.TABLENAME + " as " + USR + ", "

               + DBConstants.Organization.TABLENAME + " as " + ORG



               + " WHERE "

               + USR + "." + DBConstants.User.USER_NAME + "='" + userName
                       
               + "' AND "

               + USR + "." + DBConstants.User.ORG_CODE + "="

               + ORG + "." + DBConstants.Organization.ORG_CODE;

//        String s = "SELECT *"
//
//            + " FROM " + DBConstants.Tables.USERS + " WHERE "+DBConstants.TableColumns.USER_NAME+"='"+userName+"'";
//
           return s;

       }



}


