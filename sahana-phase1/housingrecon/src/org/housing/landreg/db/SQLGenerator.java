package org.housing.landreg.db;

/**
 * Created by IntelliJ IDEA.
 * User: nithyakala
 * Date: Jan 18, 2005
 * Time: 4:37:12 PM
 * To change this template use File | Settings | File Templates.
 */
import org.sahana.share.db.AbstractDataAccessManager;
import org.sahana.share.db.DBConstants;

public class SQLGenerator extends AbstractDataAccessManager{

    public SQLGenerator() throws Exception {
    }

    public static String getSQLForAllDivisions() {
        return "SELECT *"
            + " FROM "
            + DBConstants.Division.TABLENAME ;
//            + " where "
//            + DBConstants.Division.DIST_CODE
//            + " = "
//            + distCode;
    }

    public static String getSQLForAllDistricts() {
        return "SELECT *"
            + " FROM "
            + DBConstants.District.TABLENAME;
//            + " where "
//            + DBConstants.District.PROV_CODE
//            + " = "
//            + provCode;
    }

    public static String getSQLForAllProvinces() {
        return "SELECT *"
            + " FROM "
            + DBConstants.Province.TABLENAME;
    }

     public static String getSQLForDistrictListWithProvince(String provinceID) {
        return "select DIST_NAME, DIST_CODE from " + DBConstants.District.TABLENAME + " where PROV_CODE ="+provinceID ;
    }

    public static String getSQLForDivisionListforDistrict(String distrcit) {
        return "select " +  DBConstants.Division.TABLENAME + ".DIV_NAME, " + DBConstants.Division.TABLENAME+ ".DIV_ID " +
                "FROM " +  DBConstants.Division.TABLENAME +  " INNER JOIN " + DBConstants.District.TABLENAME + " ON "+ DBConstants.Division.TABLENAME +
                ".DIST_CODE = " + DBConstants.District.TABLENAME + ".DIST_CODE " +
                " and " + DBConstants.District.TABLENAME + ".DIST_NAME ="+"'" + distrcit +"'";
    }

    public static String getSQLForAllMeasurementType() {
           return "SELECT *"
               + " FROM "
               + DBConstants.MeasurementType.TABLENAME;
       }

    public static String getSQLForAllTerms() {
           return "SELECT *"
               + " FROM "
               + DBConstants.Term.TABLENAME;
       }

     public static String getSQLForAllOwnedBy() {
           return "SELECT *"
               + " FROM "
               + DBConstants.OwnedBy.TABLENAME;
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

    public static String getSQLAddLand() {

        return "INSERT into "

            + DBConstants.Land.TABLENAME

            + " ("

            + DBConstants.Land.LAND_NAME + ","

            + DBConstants.Land.DIVISION_ID + ","

            + DBConstants.Land.DESCRIPTION + ","

            + DBConstants.Land.MEASUREMENT_TYPE_ID +","

            + DBConstants.Land.GPS1 +","

            + DBConstants.Land.GPS2 +","

            + DBConstants.Land.GPS3 +","

            + DBConstants.Land.GPS4 +","

            + DBConstants.Land.AREA  +","

            + DBConstants.Land.TERM_ID +","

            + DBConstants.Land.OWNED_BY_ID +","

            + DBConstants.Land.OWNED_BY_COMMENT

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

     public static String getSQLForSearchCriteria(int landId) {
        return "select * from " + DBConstants.Land.TABLENAME + " where " +
                DBConstants.Land.LAND_ID + "=" + landId;
    }

    public static String getSQLForProvienceName(String provCode) {
        return "select " +
                DBConstants.Province.PROV_NAME  +
                " from " +
                DBConstants.Province.TABLENAME + " where " +
                DBConstants.Province.PROV_CODE + "='" +
                provCode + "'";
    }

    public static String getSQLForDistrictName(String districtCode) {
        return "select " +
                DBConstants.District.DIST_NAME +
                " from " +
                DBConstants.District.TABLENAME +
                " where " +
                DBConstants.District.DIST_CODE + "='"
                + districtCode + "'";
    }

    public static String getSQLForDivisionName(int divisionId) {
        return "select " +
                DBConstants.Division.DIV_NAME +
                " from " +
                DBConstants.Division.TABLENAME + " where " +
                DBConstants.Division.DIV_ID +"=" +
                divisionId;
    }

     public static String getSQLForMeasurementTypeName(int measurementTypeId) {
        return "select " +
                DBConstants.MeasurementType.MEASUREMENT_TYPE_NAME +
                " from " +
                DBConstants.MeasurementType.TABLENAME + " where " +
                DBConstants.MeasurementType.MEASUREMENT_TYPE_NAME +"=" +
                measurementTypeId;
    }

    public static String getSQLForTermName(int termId) {
        return "select " +
                DBConstants.Term.DESCRIPTION +
                " from " +
                DBConstants.Term.TABLENAME + " where " +
                DBConstants.Term.TERM_ID +"=" +
                termId;
    }

    public static String getSQLForOwnedByName(int ownedById) {
        return "select " +
                DBConstants.OwnedBy.OWNED_BY_NAME +
                " from " +
                DBConstants.OwnedBy.TABLENAME + " where " +
                DBConstants.OwnedBy.OWNED_BY_ID +"=" +
                ownedById;
    }


    public static String getSQLForSearchCriteria(String landName, String divisionId, String ownedById, String termId , String area, String measurementTypeId) {

        StringBuffer sqlBuff = new StringBuffer("select lan."+ DBConstants.Land.LAND_ID + ", lan."
                                +  DBConstants.Land.LAND_NAME +",lan."
                                +  DBConstants.Land.DESCRIPTION +",lan."
                                +  DBConstants.Land.DIVISION_ID +",lan."
                                +  DBConstants.Land.AREA +",lan."
                                +  DBConstants.Land.MEASUREMENT_TYPE_ID +",lan."
                                +  DBConstants.Land.OWNED_BY_ID +",lan."
                                +  DBConstants.Land.OWNED_BY_COMMENT +",lan."
                                +  DBConstants.Land.TERM_ID+",lan."

                                +  DBConstants.Land.GPS1 +",lan."
                                +  DBConstants.Land.GPS2 +",lan."
                                +  DBConstants.Land.GPS3 +",lan."
                                +  DBConstants.Land.GPS4 +",pro."

                                +  DBConstants.Province.PROV_CODE +",dis."
                                +  DBConstants.District.DIST_CODE +",pro."

                                +  DBConstants.Province.PROV_NAME +",dis."
                                +  DBConstants.District.DIST_NAME +","+ DBConstants.Division.TABLENAME+"."
                                +  DBConstants.Division.DIV_NAME +",ter."

                                +  DBConstants.Term.DESCRIPTION +",mea."
                                +  DBConstants.MeasurementType.MEASUREMENT_TYPE_NAME +",own."
                                +  DBConstants.OwnedBy.OWNED_BY_NAME

              +" from "

              + DBConstants.Land.TABLENAME +" as lan," + DBConstants.District.TABLENAME +" as dis,"
              + DBConstants.Division.TABLENAME +"," + DBConstants.Province.TABLENAME  +" as pro,"
              + DBConstants.Term.TABLENAME +" as ter," + DBConstants.OwnedBy.TABLENAME  +" as own,"
              + DBConstants.MeasurementType.TABLENAME + " as mea"

              + " where lan."+DBConstants.Land.DIVISION_ID + "= "+ DBConstants.Division.TABLENAME +"."+ DBConstants.Division.DIV_ID
              + " and "+ DBConstants.Division.TABLENAME+"."+DBConstants.Division.DIST_CODE + "= dis." + DBConstants.District.DIST_CODE
              + " and dis."+DBConstants.District.PROV_CODE + "= pro." +DBConstants.Province.PROV_CODE
              + " and lan."+DBConstants.Land.TERM_ID + "= ter."+DBConstants.Term.TERM_ID
              + " and lan."+DBConstants.Land.OWNED_BY_ID + "= own." +  DBConstants.OwnedBy.OWNED_BY_ID
              + " and lan."+DBConstants.Land.MEASUREMENT_TYPE_ID + "= mea."+DBConstants.MeasurementType.MEASUREMENT_TYPE_ID);

        boolean hasWhereClause = true;

        try{
                 int divId  = Integer.parseInt(divisionId);
                sqlBuff.append(" and lan." + DBConstants.Land.DIVISION_ID+"=" + divId + " ");
                 hasWhereClause = true;
        }   catch(Exception e){

        }

//        System.out.println("landname- "+ landName);
//          System.out.println("area "+ area);
//          System.out.println("meas "+ );

        if (landName != null  && landName!="") {
            if (hasWhereClause) {
                sqlBuff.append(" and lan.");
            }else{
                sqlBuff.append(" where ");
            }
            sqlBuff.append(" " +
                    DBConstants.Land.LAND_NAME +
                    " like '%" + landName + "%'");
            hasWhereClause = true;
        }

        try{
            int _area  = Integer.parseInt(area);
            int _measurementId  = Integer.parseInt(measurementTypeId);

            if (hasWhereClause) {
                sqlBuff.append(" and lan.");
            }else{
                sqlBuff.append(" where ");
            }
            sqlBuff.append(" " + DBConstants.Land.AREA+" >= " + _area + " ");
            hasWhereClause = true;

            sqlBuff.append(" and lan." + DBConstants.Land.MEASUREMENT_TYPE_ID+"=" + _measurementId + " ");
            hasWhereClause = true;

        }   catch(Exception e){}

        try{
            int _ownedById  = Integer.parseInt(ownedById);

            if (hasWhereClause) {
                sqlBuff.append(" and lan.");
            }else{
                sqlBuff.append(" where ");
            }
                sqlBuff.append(" " + DBConstants.Land.OWNED_BY_ID+"=" + _ownedById + " ");
                 hasWhereClause = true;
        }   catch(Exception e){
        }

        try{
            int _termId  = Integer.parseInt(termId);

            if (hasWhereClause) {
                sqlBuff.append(" and lan.");
            }else{
                sqlBuff.append(" where ");
            }
                sqlBuff.append(" " + DBConstants.Land.TERM_ID+"=" + _termId + " ");
                 hasWhereClause = true;
        }   catch(Exception e){
        }

            return sqlBuff.toString();
        }




}



