package org.burial.db;

/**
 * Created by IntelliJ IDEA.
 * User: hemapani
 * Date: Jan 5, 2005
 * Time: 3:32:18 PM
 * To change this template use File | Settings | File Templates.
 */
public interface DataBaseConstants {
    public static String BURIAL_SITE_DETAL_TABLE = "burial_site_detail";
    public static String DISTRICT_TABLE = "district";
    public static String DIVISION_TABLE = "CAMPS_DIVISION";
    public static String PROIVNCE_TABLE = "CAMPS_PROVINCE";
    public static String CAMPS_DISTRICT_TABLE = "CAMPS_DISTRICT";




    public static interface TableColumans{
        public static String BURIAL_SITE_DETAL_CODE = "burial_site_code";
        public static String BURIAL_SITE_DETAL_PROVINCE = "province";
        public static String BURIAL_SITE_DETAL_DISTRICT = "district";
        public static String BURIAL_SITE_DETAL_DEVISION = "division";
        public static String BURIAL_SITE_DETAL_AREA = "area";
        public static String BURIAL_SITE_DETAL_SITE_DESCRIPTION = "sitedescription";
        public static String BURIAL_SITE_DETAL_BURIAL_DETAIL = "burialdetail";
        public static String BURIAL_SITE_DETAL_BODY_COUNT_TOTEL = "body_count_total";
        public static String BURIAL_SITE_DETAL_BODYCOUNT_MEN = "body_count_men";
        public static String BURIAL_SITE_DETAL_BODYCOUNT_WOMEN = "body_count_women";
        public static String BURIAL_SITE_DETAL_BODYCOUNT_CHILDREAN = "body_count_children";

        public static String BURIAL_SITE_DETAL_GPRS_LATTATUDE = "gps_lattitude";
        public static String BURIAL_SITE_DETAL_GPRS_LONGATIUDE = "gps_longitude";
        public static String BURIAL_SITE_DETAL_AUTHORITY_PERSON_NAME = "authority_person_name";
        public static String BURIAL_SITE_DETAL_AUTHORITY_NAME = "authority_name";
        public static String BURIAL_SITE_DETAL_AUTHORITY_PERSON_RANK = "authority_person_rank";
        public static String BURIAL_SITE_DETAL_AUTHORITY_REFERANCE = "authority_reference";

        public static String DIVISION_ID = "DIV_ID";
        public static String DIVISION_NAME = "DIV_NAME";
        public static String DIVISION_CODE = "DIST_CODE";

        public static String PROVINCE_CODE="PROV_CODE";
        public static String PROVINCE_NAME= "PROV_NAME" ;
        public static String CAMPS_DIST_NAME= "DIST_NAME" ;
        public static String CAMPS_DIST_CODE= "DIST_CODE" ;



        public static final String DISTRICT_CODE = "DistrictCode";
        public static final String DISTRICT_NAME = "Name";


    }
}
