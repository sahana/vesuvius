/*
 * Created on Dec 30, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.campdb.db;

import org.campdb.business.CampTO;

/**
 * @author Administrator
 * <p/>
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class SQLGenerator {

    public static String getSQLForAllDistricts() {
        String s = "SELECT *"
            + " FROM " + DBConstants.Tables.DISTRICT;
        return s;
    }

    public static String getSQLForAllCategories() {
        String s = "SELECT *"
            + " FROM " + DBConstants.Tables.CATOGORY;
        return s;
    }

    public static String getSQLForAllPriorities() {
        String s = "SELECT *"
            + " FROM " + DBConstants.Tables.PRIORITIES;
        return s;
    }


    public static String getSQLForLogin(String userName) {
        String s = "SELECT *"
            + " FROM " + DBConstants.Tables.USERS + " WHERE "+DBConstants.TableColumns.USER_NAME+"='"+userName+"'";
        return s;
    }

    public static String getSQLForAllOrganizationNames() {
        return "SELECT "
            + DBConstants.TableColumns.ORG_CODE + ","
            + DBConstants.TableColumns.ORG_NAME
            + "FROM"
            + DBConstants.Tables.ORGANIZATION;
    }

    public static String getSQLForAllStatuses() {
        return "SELECT "
            + DBConstants.TableColumns.STATUS + ","
            + DBConstants.TableColumns.DESCRIPTION
            + "FROM"
            + DBConstants.Tables.FULFILL_STATUS;
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
            + DBConstants.TableColumns.DESCRIPTION + ", "
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
            + DBConstants.TableColumns.DESCRIPTION + ", "
            + DBConstants.TableColumns.UNIT + ", "
            + DBConstants.TableColumns.QUANTITY + ", "
            + DBConstants.TableColumns.PRIORITY_LEVEL
            + ") "
            + " VALUES "
            + "(?,?,?,?,?,?,?)";
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
            + DBConstants.TableColumns.STATUS
            + ") "
            + " VALUES "
            + "(?,?,?,?)";
    }

    /**
     * Returns the query which will get the request detail To as well the header information.
     *
     * @return
     */
    public static String getSQLGetRequestDetail(String requestDetailID) {

        final String REQ_HEAD = "req_head";
        final String REQ_DET = "req_detail";

        return "SELECT "
            // first the detail table details
            + REQ_DET + "." + DBConstants.TableColumns.REQUEST_DETAIL_ID + ", "
            + REQ_DET + "." + DBConstants.TableColumns.REQUEST_ID + ", "
            + REQ_DET + "." + DBConstants.TableColumns.CATEGORY + ", "
            + REQ_DET + "." + DBConstants.TableColumns.ITEM + ", "
            + REQ_DET + "." + DBConstants.TableColumns.DESCRIPTION + ", "
            + REQ_DET + "." + DBConstants.TableColumns.UNIT + ", "
            + REQ_DET + "." + DBConstants.TableColumns.QUANTITY + ", "
            + REQ_DET + "." + DBConstants.TableColumns.PRIORITY_DESCRIPTION + ", "
            // now the header details
            + REQ_HEAD + "." + DBConstants.TableColumns.REQUEST_ID + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.ORG_CODE + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.CREATE_DATE + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.REQUEST_DATE + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.CALLER_NAME + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.CALLER_ADDRESS + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.CALLER_CONTACT_NO + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.DESCRIPTION + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.SITE_TYPE + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.SITE_DISTRICT + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.SITE_AREA + ", "
            + REQ_HEAD + "." + DBConstants.TableColumns.SITE_NAME

            + " FROM "
            + DBConstants.Tables.REQUEST_DETAIL + " as " + REQ_DET + ", "
            + DBConstants.Tables.REQUEST_HEADER + " as " + REQ_HEAD

            + " WHERE "
            + REQ_DET + "." + DBConstants.TableColumns.REQUEST_DETAIL_ID + "=" + requestDetailID
            + " AND "
            + REQ_DET + "." + DBConstants.TableColumns.REQUEST_ID + "="
            + REQ_HEAD + "." + DBConstants.TableColumns.REQUEST_ID;

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
            + FULFILL + "." + DBConstants.TableColumns.STATUS

            + " FROM "
            + DBConstants.Tables.REQUEST_FULFILL + " as " + FULFILL + ", "
            + DBConstants.Tables.ORGANIZATION + " as " + ORG

            + " WHERE "
            + FULFILL + "." + DBConstants.TableColumns.REQUEST_DETAIL_ID + "=" + requestDetailID
            + " AND "
            + FULFILL + "." + DBConstants.TableColumns.ORG_CODE + "="
            + ORG + "." + DBConstants.TableColumns.ORG_CODE;

    }


    public static String getSQLAddCamp() {
        return "insert into " +
                DBConstants.Tables.CAMPS_CAMP +
                " (" +
                 DBConstants.TableColumns.CAMP_AREANAME + ","+
                 DBConstants.TableColumns.DIV_ID + ","+
                 DBConstants.TableColumns.DIST_CODE + ","+
                 DBConstants.TableColumns.PROV_CODE + ","+
                 DBConstants.TableColumns.CAMP_CAMP_NAME + ","+
                 DBConstants.TableColumns.CAMP_CAMP_ACCESABILITY + ","+
                 DBConstants.TableColumns.CAMP_CAMP_MEN + ","+
                 DBConstants.TableColumns.CAMP_CAMP_WOMEN + ","+
                 DBConstants.TableColumns.CAMP_CAMP_CHILDREN + ","+
                 DBConstants.TableColumns.CAMP_CAMP_TOTAL + ","+
                 DBConstants.TableColumns.CAMP_CAMP_CAPABILITY + ","+
                 DBConstants.TableColumns.CAMP_CAMP_CONTACT_PERSON + ","+
                 DBConstants.TableColumns.CAMP_CAMP_CONTACT_NUMBER + ","+
                 DBConstants.TableColumns.CAMP_CAMP_COMMENT + ","+
                 DBConstants.TableColumns.CAMP_LAST_UPDATE_DATE + ","+
                 DBConstants.TableColumns.CAMP_LAST_UPDATE_TIME + ","+
                 DBConstants.TableColumns.CAMP_CAMP_FAMILY +
                 ") values (" +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?," +
                "?)";
    }

    public static String getSQLInsertHistory(){
         return "insert into " +
                 DBConstants.Tables.CAMPS_HISTORY +
                 "(" +
                 DBConstants.TableColumns.HISTORY_CAMP_ID + ","+
                 DBConstants.TableColumns.HISTORY_CAMP_MEN + ","+
                 DBConstants.TableColumns.HISTORY_CAMP_WOMEN + ","+
                 DBConstants.TableColumns.HISTORY_CAMP_CHILDREN + ","+
                 DBConstants.TableColumns.HISTORY_CAMP_TOTAL + ","+
                 DBConstants.TableColumns.HISTORY_CAMP_FAMILY + ","+
                 DBConstants.TableColumns.HISTORY_UPDATED_DATE + ","+
                 DBConstants.TableColumns.HISTORY_UPDATED_TIME +
                 ") values (" +
                 "?,?,?,?,?,?,?,?)";
    }

    public static String getSQLEditCamp() {
            return "update " +
                    DBConstants.Tables.CAMPS_CAMP +
                    " set " +
                     DBConstants.TableColumns.CAMP_AREANAME + "=?, "+
                     DBConstants.TableColumns.DIV_ID + "=?, "+
                     DBConstants.TableColumns.DIST_CODE + "=?, "+
                     DBConstants.TableColumns.PROV_CODE + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_NAME + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_ACCESABILITY + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_MEN + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_WOMEN + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_CHILDREN + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_TOTAL + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_CAPABILITY + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_CONTACT_PERSON + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_CONTACT_NUMBER + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_COMMENT + "=?, "+
                     DBConstants.TableColumns.CAMP_LAST_UPDATE_DATE + "=?, "+
                     DBConstants.TableColumns.CAMP_LAST_UPDATE_TIME + "=?, "+
                     DBConstants.TableColumns.CAMP_CAMP_FAMILY  + "=?" +
                     " where " + DBConstants.TableColumns.CAMP_CAMP_ID + "=?";

        }


    public static String getSQLDeleteCamp() {
        return "delete from " +
                DBConstants.Tables.CAMPS_CAMP +
                "where " +
                 DBConstants.TableColumns.CAMP_CAMP_ID +
                "= ?";
    }


    /**
     */
    public static String getSQLForSearchCriteria(String campName, String provinceCode,
                            String districtCode, int divisionId) {

        StringBuffer sqlBuff = new StringBuffer("select * from " + DBConstants.Tables.CAMPS_CAMP + " where ");
        boolean hasWhereClause = false;

        if (divisionId != -1) {
            sqlBuff.append(" " + DBConstants.TableColumns.DIV_ID+"=" + divisionId + " ");
             hasWhereClause = true;
        }

        if (districtCode != null) {
            if (hasWhereClause) {
                sqlBuff.append(" and ");
            } else {
                hasWhereClause = true;
            }
            sqlBuff.append(" " + DBConstants.TableColumns.DIST_CODE +
                    "='" + districtCode + "'");
        }

        if (provinceCode != null) {
            if (hasWhereClause) {
                sqlBuff.append(" and ");
            } else {
                hasWhereClause = true;
            }
            sqlBuff.append(" " +
                    DBConstants.TableColumns.PROV_CODE +
                    "='" + provinceCode + "'");
        }

        if (campName != null) {
            if (hasWhereClause) {
                sqlBuff.append(" and ");
            }
            sqlBuff.append(" " +
                    DBConstants.TableColumns.CAMP_CAMP_NAME +
                    " like '%" + campName + "%'");
        }

        return sqlBuff.toString();
    }

    /**
     */
    public static String getSQLForSearchCriteria(int campId) {
        return "select * from " + DBConstants.Tables.CAMPS_CAMP + " where " +
                DBConstants.TableColumns.CAMP_CAMP_ID+"=" + campId;
    }

    public static String getSQLForProvienceName(String provCode) {
        return "select " +
                DBConstants.TableColumns.PROV_NAME  +
                " from " +
                DBConstants.Tables.CAMPS_PROVINCE + " where " +
                DBConstants.TableColumns.PROV_CODE + "='" +
                provCode + "'";
    }

    public static String getSQLForDistrictName(String districtCode) {
        return "select " +
                DBConstants.TableColumns.DIST_NAME +
                " from " +
                DBConstants.Tables.CAMPS_DISTRICT +
                " where " +
                DBConstants.TableColumns.DIST_CODE + "='"
                + districtCode + "'";
    }

    public static String getSQLForDivisionName(int divisionId) {
        return "select " +
                DBConstants.TableColumns.DIV_NAME +
                " from " +
                DBConstants.Tables.CAMPS_DIVISION + " where " +
                DBConstants.TableColumns.DIV_ID +"=" +
                divisionId;
    }

    public static String getSQLForAreaName(int areaId) {
        return "select AREA_NAME from " + DBConstants.Tables.CAMPS_AREA + " where AREA_ID=" + areaId;
    }

    public static String getSQLForProvienceList() {
        return "select PROV_NAME, PROV_CODE from " + DBConstants.Tables.CAMPS_PROVINCE;
    }

    public static String getSQLForDistrictList() {
        return "select DIST_NAME, DIST_CODE from " + DBConstants.Tables.CAMPS_DISTRICT ;
    }

    public static String getSQLForDistrictListWithProvince(String provinceID) {
        return "select DIST_NAME, DIST_CODE from " + DBConstants.Tables.CAMPS_DISTRICT + " where PROV_CODE ="+provinceID ;
    }

    public static String getSQLForDivisionList() {
        return "select DIV_NAME, DIV_ID from " + DBConstants.Tables.CAMPS_DIVISION;
    }

    public static String getSQLForDivisionListforDistrict(String distrcit) {
        return "select " +  DBConstants.Tables.CAMPS_DIVISION + ".DIV_NAME, " + DBConstants.Tables.CAMPS_DIVISION+ ".DIV_ID " +
                "FROM " +  DBConstants.Tables.CAMPS_DIVISION +  " INNER JOIN " + DBConstants.Tables.CAMPS_DISTRICT + " ON "+ DBConstants.Tables.CAMPS_DIVISION +
                ".DIST_CODE = " + DBConstants.Tables.CAMPS_DISTRICT + ".DIST_CODE " +
                " and " + DBConstants.Tables.CAMPS_DISTRICT + ".DIST_NAME ="+"'" + distrcit +"'";
    }

    public static String getSQLForAreaList() {
        return "select AREA_NAME, AREA_ID from " + DBConstants.Tables.CAMPS_AREA;
    }

     public static String getSQLForDistrictProvince(String districtCode) {
        return "select * from " + DBConstants.Tables.CAMPS_DISTRICT + " where DIST_CODE='"  + districtCode + "'";
    }

    public static String getSQLForDivisionDistrict(String divisionID) {
        return "select * from " + DBConstants.Tables.CAMPS_DIVISION + " where DIV_ID='"  + divisionID   + "'";
    }

    public static String getSQLForAreaDivision(String areaID) {
        return "select * from " + DBConstants.Tables.CAMPS_AREA + " where AREA_ID='"  + areaID  + "'";
    }

    public static String getSQLForEditCamp(String campId) {
        return "select * from " + DBConstants.Tables.CAMPS_CAMP + " where CAMP_ID='"  + campId  + "'";
    }

    public static String getSQLForDistrictCode(String divisionId) {
        return "select * from " + DBConstants.Tables.CAMPS_DIVISION + " where DIV_ID='"  + divisionId  + "'";
    }

    public static String getSQLForProvinceCode(String districtCode) {
        String temp = "select * from " + DBConstants.Tables.CAMPS_DISTRICT + " where DIST_CODE='"  + districtCode  + "'";;
        return temp;
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
            + DBConstants.TableColumns.STATUS + ", "
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

    public static String getSQLForDivisionInfo() {
            return "SELECT DIV_ID, DIST_NAME, PROV_NAME FROM "+ DBConstants.Tables.CAMPS_DIVISION +
                    " inner join "+ DBConstants.Tables.CAMPS_DISTRICT+ " inner join "+
                    DBConstants.Tables.CAMPS_PROVINCE + " where "+
                    DBConstants.Tables.CAMPS_DIVISION + ".DIST_CODE = "+ DBConstants.Tables.CAMPS_DISTRICT+".DIST_CODE and "+
                    DBConstants.Tables.CAMPS_DISTRICT+".PROV_CODE = "+DBConstants.Tables.CAMPS_PROVINCE +".PROV_CODE order by DIV_ID";
        }
    
}
