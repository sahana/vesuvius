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

public interface DBConstants {



    public interface SQL {

        public static final String SELECT = "select";



//		public static final String

    }



    public interface Tables {

        public static final String DISTRICT = "district";
        public static final String CATOGORY = "category";
        public static final String PRIORITIES = "priority";
        public static final String REQUEST_HEADER = "requestheader";
        public static final String REQUEST_DETAIL = "requestdetail";
        public static final String ORGANIZATION = "organization";
        String USERDB = "user";
        public static final String USERS = "user";
        public static final String REQUEST_FULFILL = "requestfulfill";
        public static final String REQUEST_STAUS_HISTORY = "statushistory";
        public static final String FULFILL_STATUS = "fulfillstatus";
        public static final String REQUEST_STATUS = "requeststatus";

    }



    public interface TableColumns {

        public static final String USER_NAME = "UserName";

        public static final String PASSWORD = "Password";
        public static final String ORGANIZATION = "OrgCode";

        public static final String DISTRICT_CODE = "DistrictCode";
        public static final String DISTRICT_NAME = "Name";
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

        public static final String FUlFILL_ID = "FulfullID";
        public static final String FUlFILL_REAL_ID = "FulfillID";
        public static final String STATUS_CHANGED_DATE = "ChangedDate";
        public static final String CHANGED_STAUS = "ChangedStatus";

        public static final String ORG_COMMENTS = "Comments";
        public static final String CREATE_DATE = "CreateDate";
        public static final String REQUEST_DATE = "RequestDate";
        public static final String CALLER_NAME = "CallerName";
        public static final String CALLER_ADDRESS = "CallerAddress";
        public static final String CALLER_CONTACT_NO = "CallerContactNo";
        public static final String FULLFILL_STATUS_DESCRIPTION = "Description";
        public static final String SITE_TYPE = "SiteType";
        public static final String SITE_DISTRICT = "SiteDistrict";
        public static final String SITE_AREA = "SiteArea";
        public static final String SITE_NAME = "SiteName";
        public static final String REQUEST_DETAIL_ID = "RequestDetailId";
        public static final String REQUEST_FULFILL_ID = "FulfullId";
        public static final String CATEGORY = "Category";
        public static final String ITEM = "Item";
        public static final String UNIT = "Unit";
        public static final String QUANTITY = "Quantity";
        public static final String PRIORITY_DESCRIPTION = "Description";
        public static final String CAT_CODE = "CatCode";
        public static final String CAT_DESCRIPTION = "CatDescription";
        public static final String PRIORITY_LEVEL = "Priority";
        public static final String SERVICE_QTY = "serviceQty";
        public static final String FULLFILL_STATUS = "Status";
        public static final String REQUEST_STATUS = "Status";
        public static final String REQUEST_STATUS_DESCRIPTION = "Description";


        String ORG_TYPE = "OrgType";
        String ORG_SUBTYPE = "OrgSubType";
    }

}

