/*

 * Created on Dec 30, 2004

 *

 * To change the template for this generated file go to

 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

 */

package org.erms.db;



/**

 * @author Administrator

 * <p/>

 * To change the template for this generated type comment go to

 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

 */

public class SQLGenerator {



    public static String getSQLForAllDistricts() {

        String s = "SELECT *"

            + " FROM " + DBConstants.Tables.DISTRICT + " order by "+DBConstants.TableColumns.DISTRICT_NAME;

        return s;

    }



    public static String getSQLForAllCategories() {

        String s = "SELECT *"

            + " FROM " + DBConstants.Tables.CATOGORY + " order by "+ DBConstants.TableColumns.CAT_DESCRIPTION;

        return s;

    }



    public static String getSQLForAllPriorities() {

        String s = "SELECT *"

            + " FROM " + DBConstants.Tables.PRIORITIES;

        return s;

    }





    public static String getSQLForLogin(String userName) {
            String ORG = "ORG";
            String USR = "USR";

            String s =  "SELECT "
            + USR + "." + DBConstants.TableColumns.USER_NAME + ", "

            + USR + "." + DBConstants.TableColumns.PASSWORD + ", "

            + ORG + "." + DBConstants.TableColumns.ORG_CODE + ", "

            + ORG + "." + DBConstants.TableColumns.ORG_NAME

            + " FROM "

            + DBConstants.Tables.USERS + " as " + USR + ", "

            + DBConstants.Tables.ORGANIZATION + " as " + ORG



            + " WHERE "

            + USR + "." + DBConstants.TableColumns.USER_NAME + "='" + userName
            + "' AND "

            + USR + "." + DBConstants.TableColumns.ORG_CODE + "="

            + ORG + "." + DBConstants.TableColumns.ORG_CODE;

//        String s = "SELECT *"
//
//            + " FROM " + DBConstants.Tables.USERS + " WHERE "+DBConstants.TableColumns.USER_NAME+"='"+userName+"'";
//
        return s;

    }



    public static String getSQLForAllOrganizationNames() {

        return "SELECT "

            + DBConstants.TableColumns.ORG_CODE + ","

            + DBConstants.TableColumns.ORG_NAME

            + " FROM "

            + DBConstants.Tables.ORGANIZATION;

    }



    public static String getSQLForAllStatuses() {
        return "SELECT "
            + DBConstants.TableColumns.FULLFILL_STATUS + ","
            + DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION
            + " FROM "
            + DBConstants.Tables.FULFILL_STATUS;
    }

     public static String getSQLForAllSearchStatuses() {
        return "SELECT "
            + DBConstants.TableColumns.REQUEST_STATUS + ","
            + DBConstants.TableColumns.REQUEST_STATUS_DESCRIPTION
            + " FROM "
            + DBConstants.Tables.REQUEST_STATUS;

    }


    /**

     * returns the sql statement for inserting records into the request header

     *

     * @return

     */

    public static String getSQLAddRequestHeader() {

        return "INSERT into "

            + DBConstants.Tables.REQUEST_HEADER

            + " ("

            + DBConstants.TableColumns.ORG_CODE + ", "

            + DBConstants.TableColumns.CREATE_DATE + ", "

            + DBConstants.TableColumns.REQUEST_DATE + ", "

            + DBConstants.TableColumns.CALLER_NAME + ", "

            + DBConstants.TableColumns.CALLER_ADDRESS + ", "

            + DBConstants.TableColumns.CALLER_CONTACT_NO + ", "

            + DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION + ", "

            + DBConstants.TableColumns.SITE_TYPE + ", "

            + DBConstants.TableColumns.SITE_DISTRICT + ", "

            + DBConstants.TableColumns.SITE_AREA + ", "

            + DBConstants.TableColumns.SITE_NAME

            + ") "

            + " VALUES "

            + "(?,?,?,?,?,?,?,?,?,?,?)";

    }



    /**

     * returns the sql statement for inserting records into the request detail

     *

     * @return

     */

    public static String getSQLAddRequestDetail() {

        return "INSERT into "

            + DBConstants.Tables.REQUEST_DETAIL

            + " ("

            + DBConstants.TableColumns.REQUEST_ID + ", "

            + DBConstants.TableColumns.CATEGORY + ", "

            + DBConstants.TableColumns.ITEM + ", "

            + DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION + ", "

            + DBConstants.TableColumns.UNIT + ", "

            + DBConstants.TableColumns.QUANTITY + ", "

            + DBConstants.TableColumns.PRIORITY_LEVEL  +  ","
            + DBConstants.TableColumns.FULLFILL_STATUS

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

            + DBConstants.Tables.REQUEST_FULFILL

            + " ("

            + DBConstants.TableColumns.ORG_CODE + ", "

            + DBConstants.TableColumns.REQUEST_DETAIL_ID + ", "

            + DBConstants.TableColumns.SERVICE_QTY + ", "

            + DBConstants.TableColumns.FULLFILL_STATUS

            + ") "

            + " VALUES "

            + "(?,?,?,?)";

    }

    public static String getSQLAddFulFillStausChanged() {

        return "INSERT into "

            + DBConstants.Tables.REQUEST_STAUS_HISTORY

            + " ("

            + DBConstants.TableColumns.FUlFILL_REAL_ID + ", "

            + DBConstants.TableColumns.STATUS_CHANGED_DATE + ", "

            + DBConstants.TableColumns.CHANGED_STAUS

            + ") "

            + " VALUES "

            + "(?,?,?)";

    }

    public static String SQLupdateFulFillRequest() {

        return "UPDATE "

            + DBConstants.Tables.REQUEST_FULFILL

            + " SET "

            + DBConstants.TableColumns.FULLFILL_STATUS + "= ?  "

            + "WHERE ("

            + DBConstants.TableColumns.REQUEST_FULFILL_ID + "= ? ) ";


    }

    public static String getSQLupdateRequestStatus() {

        return "UPDATE "

            + DBConstants.Tables.REQUEST_DETAIL

            + " SET "

            + DBConstants.TableColumns.REQUEST_STATUS + "= ?  "

            + "WHERE ("

            + DBConstants.TableColumns.REQUEST_DETAIL_ID + "= ? ) ";


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

            + REQ_DET + "." + DBConstants.TableColumns.REQUEST_DETAIL_ID + ", "

            + REQ_DET + "." + DBConstants.TableColumns.REQUEST_ID + ", "

            + REQ_DET + "." + DBConstants.TableColumns.CATEGORY + ", "

            + REQ_DET + "." + DBConstants.TableColumns.ITEM + ", "

            + REQ_DET + "." + DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION + ", "

            + REQ_DET + "." + DBConstants.TableColumns.UNIT + ", "

            + REQ_DET + "." + DBConstants.TableColumns.QUANTITY + ", "

            + REQ_DET + "." + DBConstants.TableColumns.PRIORITY_LEVEL + ", "

             + REQ_DET + "." + DBConstants.TableColumns.REQUEST_STATUS + ", "

            // now the header details

            + REQ_HEAD + "." + DBConstants.TableColumns.REQUEST_ID + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.ORG_CODE + ", "



            + REQ_HEAD + "." + DBConstants.TableColumns.CREATE_DATE + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.REQUEST_DATE + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.CALLER_NAME + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.CALLER_ADDRESS + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.CALLER_CONTACT_NO + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.SITE_TYPE + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.SITE_DISTRICT + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.SITE_AREA + ", "

            + REQ_HEAD + "." + DBConstants.TableColumns.SITE_NAME + ", "

            + REQ_ORG + "." + DBConstants.TableColumns.ORG_NAME + ", "

            + REQ_ORG + "." + DBConstants.TableColumns.ORG_CONTACT_NUMBER

            + " FROM "

            + DBConstants.Tables.REQUEST_DETAIL + " as " + REQ_DET + ", "

            + DBConstants.Tables.ORGANIZATION + " as " + REQ_ORG + ", "

            + DBConstants.Tables.REQUEST_HEADER + " as " + REQ_HEAD



            + " WHERE "

            + REQ_DET + "." + DBConstants.TableColumns.REQUEST_DETAIL_ID + "=" + requestDetailID

            + " AND "

            + REQ_DET + "." + DBConstants.TableColumns.REQUEST_ID + "="

            + REQ_HEAD + "." + DBConstants.TableColumns.REQUEST_ID

            + " AND "

            + REQ_HEAD + "." + DBConstants.TableColumns.ORG_CODE + "="

            + REQ_ORG + "." + DBConstants.TableColumns.ORG_CODE;


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

            + ORG + "." + DBConstants.TableColumns.ORG_CODE + ", "

            + ORG + "." + DBConstants.TableColumns.ORG_NAME + ", "

            + ORG + "." + DBConstants.TableColumns.ORG_ADDRESS + ", "

            // now the header details

            + FULFILL + "." + DBConstants.TableColumns.SERVICE_QTY + ", "

            + FULFILL + "." + DBConstants.TableColumns.FUlFILL_ID + ", "

            + FULFILL + "." + DBConstants.TableColumns.FULLFILL_STATUS



            + " FROM "

            + DBConstants.Tables.REQUEST_FULFILL + " as " + FULFILL + ", "

            + DBConstants.Tables.ORGANIZATION + " as " + ORG



            + " WHERE "

            + FULFILL + "." + DBConstants.TableColumns.REQUEST_DETAIL_ID + "=" + requestDetailID
            + " AND "

            + FULFILL + "." + DBConstants.TableColumns.ORG_CODE + "="

            + ORG + "." + DBConstants.TableColumns.ORG_CODE;


    }



    /**

     * This method is in progress. need to complete with the appropriate fields.

     * @return

     */

    public static String getSQLForSearchCriteria() {



        final String RQH = "RQH";

        final String RQD = "RQD";



        return "SELECT "

            + RQD + "." + DBConstants.TableColumns.REQUEST_DETAIL_ID + ", "

            + RQH + "." + DBConstants.TableColumns.FULLFILL_STATUS_DESCRIPTION + ", "

            + RQH + "." + DBConstants.TableColumns.SITE_NAME + ", "

            + RQH + "." + DBConstants.TableColumns.SITE_TYPE + ", "

            + RQH + "." + DBConstants.TableColumns.SITE_DISTRICT + ", "

            + RQH + "." + DBConstants.TableColumns.SITE_AREA + ", "

            + RQD + "." + DBConstants.TableColumns.CATEGORY + ", "

            + RQD + "." + DBConstants.TableColumns.FULLFILL_STATUS + ", "

            + RQD + "." + DBConstants.TableColumns.QUANTITY + ", "

            + RQD + "." + DBConstants.TableColumns.UNIT + ", "

            + RQD + "." + DBConstants.TableColumns.PRIORITY_LEVEL + ", "

            + RQD + "." + DBConstants.TableColumns.ITEM

            + " FROM "

            + DBConstants.Tables.REQUEST_HEADER + " as " + RQH + ", "

            + DBConstants.Tables.REQUEST_DETAIL + " as " + RQD

            + " WHERE "

            + "(? is null OR (" + DBConstants.TableColumns.CATEGORY + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.ORG_CODE + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.SITE_NAME + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.SITE_DISTRICT + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.ITEM + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.PRIORITY_LEVEL + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.FULLFILL_STATUS + " = ?))"

/*            + " AND "

            + "((? is null OR ? is null) OR (" + DBConstants.TableColumns.REQUEST_DATE + " BETWEEN ? AND ?))"
*/
            + " AND "

            + RQH + "." + DBConstants.TableColumns.REQUEST_ID

            + " = "

            + RQD + "." + DBConstants.TableColumns.REQUEST_ID

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

            + DBConstants.Tables.ORGANIZATION

            + " ("

            + DBConstants.TableColumns.ORG_CODE + ", "

            + DBConstants.TableColumns.ORG_CONTACT_PERSON + ", "

            + DBConstants.TableColumns.ORG_NAME + ", "

            + DBConstants.TableColumns.FULLFILL_STATUS + ", "

            + DBConstants.TableColumns.ORG_ADDRESS + ", "

            + DBConstants.TableColumns.ORG_CONTACT_NUMBER + ", "

            + DBConstants.TableColumns.ORG_EMAIL_ADDRESS + ", "

            + DBConstants.TableColumns.ORG_COUNTRY_OF_ORIGIN + ", "

            + DBConstants.TableColumns.ORG_FACILITIES_AVAILABLE + ", "

            + DBConstants.TableColumns.ORG_WORKING_AREAS + ", "

            + DBConstants.TableColumns.ORG_COMMENTS

            + ") "

            + " VALUES "

            + "(?,?,?,?,?,?,?,?,?,?,?)";

    }



    public static String getSQLForCountOrganizationCode() {

        return "select count(" + DBConstants.TableColumns.ORG_CODE + ") from " + DBConstants.Tables.ORGANIZATION +" where "

                + DBConstants.TableColumns.ORG_CODE + "=?";

    }


}


