/*

 * Created on Dec 30, 2004

 *

 * To change the template for this generated file go to

 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

 */

package org.sahana.share.db;



/**

 * @author Administrator

 * <p/>

 * To change the template for this generated type comment go to

 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

 */

public class AbstractSQLGenerator {



    public static String getSQLForAllDistricts() {

        String s = "SELECT *"

            + " FROM " + DBConstants.District.TABLENAME + " order by "+ DBConstants.District.DISTRICT_NAME;

        return s;

    }



    public static String getSQLForAllCategories() {

        String s = "SELECT *"

            + " FROM " + DBConstants.Category.TABLENAME + " order by "+ DBConstants.Category.CAT_DESCRIPTION;

        return s;

    }


    public static String getSQLForAllSites() {
         String s = "SELECT " +  DBConstants.Sitetype.SITE_TYPE_CODE + "," + DBConstants.Sitetype.SITE_TYPE
             + " FROM " + DBConstants.Sitetype.TABLENAME + " order by "+ DBConstants.Sitetype.SITE_TYPE;
         return s;
     }



    public static String getSQLForAllPriorities() {

        String s = "SELECT *"

            + " FROM " + DBConstants.Priority.TABLENAME;

        return s;

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

            + USR + "." + DBConstants.Organization.ORG_CODE + "="

            + ORG + "." + DBConstants.Organization.ORG_CODE;

//        String s = "SELECT *"
//
//            + " FROM " + DBConstants.Tables.USERS + " WHERE "+DBConstants.TableColumns.USER_NAME+"='"+userName+"'";
//
        return s;

    }



    public static String getSQLForAllOrganizationNames() {

        return "SELECT "

            + DBConstants.Organization.ORG_CODE + ","

            + DBConstants.Organization.ORG_NAME

            + " FROM "

            + DBConstants.Organization.TABLENAME;

    }



    public static String getSQLForAllStatuses() {
        return "SELECT "
            + DBConstants.Fulfillstatus.FULLFILL_STATUS + ","
            + DBConstants.Fulfillstatus.FULLFILL_STATUS_DESCRIPTION
            + " FROM "
            + DBConstants.Fulfillstatus.TABLENAME;
    }

     public static String getSQLForAllSearchStatuses() {
        return "SELECT "
            + DBConstants.Requeststatus.REQUEST_STATUS + ","
            + DBConstants.Requeststatus.REQUEST_STATUS_DESCRIPTION
            + " FROM "
            + DBConstants.Requeststatus.TABLENAME;

    }



}


