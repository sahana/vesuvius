/*
 * Created on Dec 30, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.campdb.db;

/**
 * @author Administrator
 * <p/>
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public interface DBConstants {

    public interface SQL {
        public static final String SELECT = "select";
		
//		public static final String
    }

    public interface Tables {
        public static final String CAMPS_PROVINCE = "CAMPS_PROVINCE";
        public static final String CAMPS_DISTRICT = "CAMPS_DISTRICT";
        public static final String CAMPS_DIVISION = "CAMPS_DIVISION";
        public static final String CAMPS_AREA = "CAMPS_AREA";
        public static final String CAMPS_CAMP = "CAMPS_CAMP";
        public static final String DISTRICT = "district";
        public static final String CATOGORY = "category";
        public static final String PRIORITIES = "priority";
        public static final String REQUEST_HEADER = "requestheader";
        public static final String REQUEST_DETAIL = "requestdetail";
        public static final String ORGANIZATION = "organization";
        public static final String USERS = "user";
        public static final String REQUEST_FULFILL = "requestfulfill";
        public static final String FULFILL_STATUS = "fulfillstatus";
    }

    public interface TableColumns {

        public static final String USER_NAME = "UserName";
        public static final String PASSWORD = "Password";
        public static final String ORGANIZATION = "OrgCode";
        public static final String DISTRICT_CODE = "DistrictCode";
        public static final String NAME = "Name";
        public static final String REQUEST_ID = "RequestID";
        public static final String ORG_CODE = "OrgCode";
        public static final String ORG_NAME = "OrgName";
        public static final String ORG_ADDRESS = "OrgAddress";
        public static final String ORG_CONTACT_PERSON = "ContactPerson";
        public static final String ORG_STATUS ="Status";
        public static final String ORG_CONTACT_NUMBER = "ContactNumber";
        public static final String ORG_EMAIL_ADDRESS = "EmailAddress";
        public static final String ORG_COUNTRY_OF_ORIGIN = "CountryOfOrigin";
        public static final String ORG_FACILITIES_AVAILABLE = "FacilitiesAvailable";
        public static final String ORG_WORKING_AREAS = "WorkingAreas";
        public static final String ORG_COMMENTS = "Comments";
        public static final String CREATE_DATE = "CreateDate";
        public static final String REQUEST_DATE = "RequestDate";
        public static final String CALLER_NAME = "CallerName";
        public static final String CALLER_ADDRESS = "CallerAddress";
        public static final String CALLER_CONTACT_NO = "CallerContactNo";
        public static final String DESCRIPTION = "Description";
        public static final String SITE_TYPE = "SiteType";
        public static final String SITE_DISTRICT = "SiteDistrict";
        public static final String SITE_AREA = "SiteArea";
        public static final String SITE_NAME = "SiteName";
        public static final String REQUEST_DETAIL_ID = "RequestDetailId";
        public static final String CATEGORY = "Category";
        public static final String ITEM = "Item";
        public static final String UNIT = "Unit";
        public static final String QUANTITY = "Quantity";
        public static final String PRIORITY_DESCRIPTION = "Description";
        public static final String CAT_CODE = "CatCode";
        public static final String CAT_DESCRIPTION = "CatDescription";
        public static final String PRIORITY_LEVEL = "Priority";
        public static final String SERVICE_QTY = "serviceQty";
        public static final String STATUS = "status";


        public static final String CAMP_AREANAME = "AREA_NAME";
        public static final String CAMP_DIV_ID = "DIV_ID";
        public static final String CAMP_DIST_CODE = "DIST_CODE";
        public static final String CAMP_PROV_CODE = "PROV_CODE";
        public static final String CAMP_CAMP_NAME = "CAMP_NAME";
        public static final String CAMP_CAMP_ACCESABILITY = "CAMP_ACCESABILITY";
        public static final String CAMP_CAMP_MEN = "CAMP_MEN";
        public static final String CAMP_CAMP_WOMEN = "CAMP_WOMEN";
        public static final String CAMP_CAMP_CHILDREN = "CAMP_CHILDREN";
        public static final String CAMP_CAMP_TOTAL = "CAMP_TOTAL";
        public static final String CAMP_CAMP_CAPABILITY = "CAMP_CAPABILITY";
        public static final String CAMP_CAMP_CONTACT_PERSON = "CAMP_CONTACT_PERSON";
        public static final String CAMP_CAMP_CONTACT_NUMBER = "CAMP_CONTACT_NUMBER";
        public static final String CAMP_CAMP_COMMENT = "CAMP_COMMENT";
        public static final String CAMP_LAST_UPDATE_DATE = "LAST_UPDATE_DATE";
        public static final String CAMP_LAST_UPDATE_TIME = "LAST_UPDATE_TIME";
        public static final String CAMP_CAMP_FAMILY = "CAMP_FAMILY";
        public static final String CAMP_CAMP_ID = "CAMP_ID";

    }
}
