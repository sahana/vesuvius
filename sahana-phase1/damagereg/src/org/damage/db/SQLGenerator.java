package org.damage.db;

import org.sahana.share.db.AbstractSQLGenerator;


public class SQLGenerator extends AbstractSQLGenerator{

    public static String getSQLForAddDamagedHouse(){
        String s = "INSERT into"
                    + DBConstants.Tables.HOUSE
                    +"("
                    +DBConstants.TableColumns.ID + ", "
                    +DBConstants.TableColumns.DISTRICT_CODE + ", "
                    +DBConstants.TableColumns.DIVISION + ", "
                    +DBConstants.TableColumns.GSN + ", "
                    +DBConstants.TableColumns.OWNER + ", "
                    +DBConstants.TableColumns.DISTANCE_FROM_SEA + ", "
                    +DBConstants.TableColumns.CITY + ", "
                    +DBConstants.TableColumns.NO_AND_STREET + ", "
                    +DBConstants.TableColumns.CURRENT_ADDRESS + ", "
                    +DBConstants.TableColumns.FLOOR_AREA + ", "
                    +DBConstants.TableColumns.NO_OF_STORIES + ", "
                    +DBConstants.TableColumns.TYPE_OF_OWNERSHIP + ", "
                    +DBConstants.TableColumns.NO_OF_RESIDENTS + ", "
                    +DBConstants.TableColumns.TYPE_OF_CONSTRUCTION + ", "
                    +DBConstants.TableColumns.PROPERTY_TAX_NO + ", "
                    +DBConstants.TableColumns.TOTAL_DAMAGED_COST + ", "
                    +DBConstants.TableColumns.LAND_AREA + ", "
                    +DBConstants.TableColumns.RELOCATE + ", "
                    +DBConstants.TableColumns.INSURED + ", "
                    +DBConstants.TableColumns.DAMAGE_TYPE + ", "
                    +DBConstants.TableColumns.COMMENTS
                    + ")"
                    +"VALUES"
                    +"(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";

        return s;
    }

    public static String getSQLForAddDamagedHouse_Damage_Moreinfo(){
        String s = "INSERT into"
                    + DBConstants.Tables.HOUSE_DAMAGE_MOREINFO
                    +"("
                    +DBConstants.TableColumns.HOUSE_ID + ", "
                    +DBConstants.TableColumns.DAMAGE_INFO
                    + ")"
                    +"VALUES"
                    +"(?,?)";

        return s;
    }

    public static String getSQLForAddDamagedHouse_Facility_Info(){
        String s = "INSERT into"
                    + DBConstants.Tables.HOUSE_FACILITY_INFO
                    +"("
                    +DBConstants.TableColumns.FACILITY_NAME + ", "
                    +DBConstants.TableColumns.DESCRIPTION
                    + ")"
                    +"VALUES"
                    +"(?,?)";

        return s;
    }
      public static String getSQLForSearchCriteria() {

       String H = "H";
       String H_MORE = "H_MORE";
       String H_F = "HF";

//           private String districtCode;
//    private String division;
//    private String gsn;
//    private String owner;
//    private double distanceFromSea;
//    private String city;
//    private String noAndStreet;
//    private String currentAddress;
//    private double floorArea;
//    private int noOfStories;
//    private String typeOfOwnership;
//    private int noOfResidents;
//    private String typeOfConstruction;
//    private String propertyTaxNo;
//    private double totalDamagedCost;
//    private double landArea;
//    private boolean relocate;
//    private boolean insured;
//    private String damageType;
//    private String comments;

        return "SELECT "
            + DBConstants.TableColumns.DISTRICT_CODE + ","
            + DBConstants.TableColumns.DIVISION + ","
            + DBConstants.TableColumns.GSN + ","
            + DBConstants.TableColumns.OWNER + ","
            + DBConstants.TableColumns.DISTANCE_FROM_SEA + ","
            + DBConstants.TableColumns.FLOOR_AREA + ","
            + DBConstants.TableColumns.NO_OF_STORIES + ","
            + DBConstants.TableColumns.DAMAGE_TYPE + ","
            + DBConstants.TableColumns.TYPE_OF_OWNERSHIP + ","
            + DBConstants.TableColumns.TYPE_OF_CONSTRUCTION + ","
            + DBConstants.TableColumns.PROPERTY_TAX_NO + ","
            + DBConstants.TableColumns.TOTAL_DAMAGED_COST + ","
            + DBConstants.TableColumns.LAND_AREA + ","
            + DBConstants.TableColumns.RELOCATE + ","
            + DBConstants.TableColumns.INSURED + ","
            + DBConstants.TableColumns.DAMAGE_TYPE + ","
            + DBConstants.TableColumns.COMMENTS + ","

            + " FROM "

            + DBConstants.Tables.HOUSE + " as " + H + ", "

            + DBConstants.Tables.HOUSE_DAMAGE_MOREINFO + " as " + H_MORE + ", "

            + DBConstants.Tables.HOUSE_FACILITY_INFO + " as " + H_F     


            + " WHERE "

            + "(? is null OR (" + DBConstants.TableColumns.DISTRICT_CODE + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.DIVISION + " = ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.GSN + " LIKE ?))"

            + " AND "

            + "(? is null OR (" + DBConstants.TableColumns.OWNER + " = ?))"

            + " AND "

            + H + "." + DBConstants.TableColumns.ID

            + " = "

            + H_MORE + "." + DBConstants.TableColumns.HOUSE_ID

            + " AND "

            + H + "." + DBConstants.TableColumns.ID

            + " = "

            + H_F + "." + DBConstants.TableColumns.HOUSE_ID
            ;

    }
}
