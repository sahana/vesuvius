package org.assistance.db;

/**
 * Created by IntelliJ IDEA.
 * User: hemapani
 * Date: Jan 4, 2005
 * Time: 10:35:01 AM
 * To change this template use File | Settings | File Templates.
 */
public class SQLGenerator {
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


    public static String getSQLForSearchCriteria() {
        final String OFFER = "OFR";


        return "SELECT "
            + OFFER + "." + DBConstants.TableColumns.OFFER_ID + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_AGANCY + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_DATE + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_SECTOR + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_PARTNERS + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_RELIEF_COMMITED_DETAIL + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_RELIEF_COMMITED_TOTEL + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_RELIEF_DISBURSED_DETAIL + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_RELIEF_DISBURSED_TOTEL + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_HR_COMMITED + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_NEEDSASSESMENT + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_OTHER_ACTIVITIES + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_PLANNED_ACTIVITES + ", "

            + OFFER + "." + DBConstants.TableColumns.OFFER_OTHER_ISSUES

            + " FROM "

            + DBConstants.Tables.OFFERS + " as " + OFFER

            + " WHERE "

            + "(? is null OR (" + DBConstants.TableColumns.OFFER_AGANCY + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.OFFER_PARTNERS + " LIKE ?))"

            + " AND "

            + "((? is null OR ? is null) OR (" + DBConstants.TableColumns.OFFER_DATE + " BETWEEN ? AND ?))";

    }


}
