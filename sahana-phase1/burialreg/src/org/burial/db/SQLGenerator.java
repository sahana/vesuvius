package org.burial.db;

import java.util.Collection;

/**
 * Created by IntelliJ IDEA.
 * User: hemapani
 * Date: Jan 4, 2005
 * Time: 10:35:01 AM
 * To change this template use File | Settings | File Templates.
 */
public class SQLGenerator {

    public static String getSQLForDistrictListWithProvince(String provinceID) {
        return "select " +
                DataBaseConstants.TableColumans.CAMPS_DIST_CODE + "," +
                DataBaseConstants.TableColumans.CAMPS_DIST_NAME + " from " +
                DataBaseConstants.CAMPS_DISTRICT_TABLE +
                " where " +
                DataBaseConstants.TableColumans.PROVINCE_CODE+"="+ provinceID +"" ;
    }

     public static String getSQLForDivisionListforDistrict(String district) {
        return "select " + DataBaseConstants.DIVISION_TABLE+"."+ DataBaseConstants.TableColumans.DIVISION_NAME+", " +
                DataBaseConstants.DIVISION_TABLE+"."+ DataBaseConstants.TableColumans.DIVISION_ID +
                " FROM " + DataBaseConstants.DIVISION_TABLE +" INNER JOIN " + DataBaseConstants.CAMPS_DISTRICT_TABLE +" ON " +
                DataBaseConstants.DIVISION_TABLE+"."+ DataBaseConstants.TableColumans.DIVISION_CODE +"= " +
                DataBaseConstants.CAMPS_DISTRICT_TABLE + "." + DataBaseConstants.TableColumans.DIVISION_CODE +
                " and " +
                DataBaseConstants.CAMPS_DISTRICT_TABLE + "." + DataBaseConstants.TableColumans.CAMPS_DIST_NAME +"="+"'" + district +"'";
    }

//     public static String getSQLForAllDistricts() {
//        String s = "SELECT "+
//               DataBaseConstants.TableColumans.DISTRICT_CODE + "," +
//               DataBaseConstants.TableColumans.DISTRICT_NAME +
//            " FROM " + DataBaseConstants.DISTRICT_TABLE;
//        return s;
//    }

    //todo fix these
    public static String getSQLForDistrictList() {
        return "select DIST_NAME, DIST_CODE from " + DBConstants.Tables.CAMPS_DISTRICT +" order by " + "PROV_CODE";
    }

//    public static String getSQLForDistrictListOrderedByName() {
//        return "select DIST_NAME, DIST_CODE from " + DBConstants.Tables.CAMPS_DISTRICT +" order by " + "PROV_CODE";
//    }

    public static String getSQLForAllDevisions(){
        String s = "SELECT " +
            DataBaseConstants.TableColumans.DIVISION_ID + "," +
            DataBaseConstants.TableColumans.DIVISION_CODE + "," +
            DataBaseConstants.TableColumans.DIVISION_NAME +
            " FROM " + DataBaseConstants.DIVISION_TABLE;
        return s;
    }

    public static String getSQLForAllProivnces(){
        String s = "SELECT " +
                DataBaseConstants.TableColumans.PROVINCE_CODE + "," +
                DataBaseConstants.TableColumans.PROVINCE_NAME +
             " FROM " + DataBaseConstants.PROIVNCE_TABLE;
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

    public static String getSQLForInsertSiteDTO(){
    return "INSERT into "

                + DataBaseConstants.BURIAL_SITE_DETAL_TABLE

                + " ("

                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_PROVINCE + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_DISTRICT + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_DEVISION + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AREA + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_SITE_DESCRIPTION + ", "

                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BURIAL_DETAIL + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODY_COUNT_TOTEL + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_MEN + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_WOMEN + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_CHILDREAN + ", "

            + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_GPRS_LATTATUDE + ", "
            + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_GPRS_LONGATIUDE + ", "
            + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_PERSON_NAME + ", "
            + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_NAME + ", "

            + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_PERSON_RANK + ", "
            + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_REFERANCE
                + ") "

                + " VALUES "

                + "(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
    }

    public static String getSQLForAllSites(){
        return "SELECT " + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_CODE + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_PROVINCE + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_DISTRICT + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_DEVISION + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AREA + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_SITE_DESCRIPTION + ", "

                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BURIAL_DETAIL + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODY_COUNT_TOTEL + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_MEN + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_WOMEN + ", "
                    + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_BODYCOUNT_CHILDREAN + ", "

                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_GPRS_LATTATUDE + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_GPRS_LONGATIUDE + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_PERSON_NAME + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_NAME + ", "

                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_PERSON_RANK + ", "
                + DataBaseConstants.TableColumans.BURIAL_SITE_DETAL_AUTHORITY_REFERANCE 
                    + " FROM " + DataBaseConstants.BURIAL_SITE_DETAL_TABLE ;
    }
}
