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

        public static final String ORGANIZATION_DISTRICT = "organization_district";


        public static final String ORGANIZATION_SECTOR = "organization_sector";

        public static final String CATOGORY = "category";



        public static final String PRIORITIES = "priority";



        public static final String REQUEST_HEADER = "requestheader";



        public static final String REQUEST_DETAIL = "requestdetail";



        public static final String ORGANIZATION = "organization";

        String USERDB = "user";

        String USER_ROLEDB = "tbluserroles";



        public static final String USERS = "user";



        /**

         * Request fulfill table

         */

        public static final String REQUEST_FULFILL = "requestfulfill";



        public static final String FULFILL_STATUS = "fulfillstatus";

    }



    public interface TableColumns {

        public static final String USER_NAME = "UserName";

        String ROLE_ID = "RoleId";



        public static final String PASSWORD = "Password";

        public static final String ORGANIZATION = "OrgCode";



        

        public static final String DISTRICT_CODE = "DistrictCode";
        public static final String DISTRICT_NAME = "Name";

        public static final String ORGANIZATION_DISTRICT_ORG_CODE = "OrgCode";
        public static final String ORGANIZATION_DISTRICT_DISTRICT_NAME = "DistrictName";

        public static final String ORGANIZATION_SECTOR_ORG_CODE = "OrgCode";
        public static final String ORGANIZATION_SECTOR_SECTOR = "Sector";

        /**

         * request id

         */

        public static final String REQUEST_ID = "RequestID";



        /**

         * Org Code

         */


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
        public static final String ORG_LAST_UPDATE = "LastUpdate";
        public static final String ORG_IS_SRILANKAN = "IsSriLankan";
        public static final String ORG_TYPE = "OrgType";
        public static final String ORG_SUBTYPE = "OrgSubType";
        public static final String ORG_UNTILDATE = "UntilDate";
        /**
         * Create Date
         */
        public static final String CREATE_DATE = "CreateDate";



        /**

         * Request Date

         */

        public static final String REQUEST_DATE = "RequestDate";



        /**

         * Caller Name

         */

        public static final String CALLER_NAME = "CallerName";



        /**

         * Caller Address

         */

        public static final String CALLER_ADDRESS = "CallerAddress";



        /**

         * Caller Contact No

         */

        public static final String CALLER_CONTACT_NO = "CallerContactNo";



        /**

         * Description

         */

        public static final String DESCRIPTION = "Description";



        /**

         * Site Type

         */

        public static final String SITE_TYPE = "SiteType";



        /**

         * Site District

         */

        public static final String SITE_DISTRICT = "SiteDistrict";



        /**

         * Site Area

         */

        public static final String SITE_AREA = "SiteArea";



        /**

         * Site Name

         */

        public static final String SITE_NAME = "SiteName";



        /**

         * Request Detail ID

         */

        public static final String REQUEST_DETAIL_ID = "RequestDetailId";



        /**

         * Category

         */

        public static final String CATEGORY = "Category";



        /**

         * Item

         */

        public static final String ITEM = "Item";



        /**

         * Unit

         */

        public static final String UNIT = "Unit";



        /**

         * Quantity

         */

        public static final String QUANTITY = "Quantity";



        /**

         * Priority

         */

        public static final String PRIORITY_DESCRIPTION = "Description";



        public static final String CAT_CODE = "CatCode";



        public static final String CAT_DESCRIPTION = "CatDescription";



        public static final String PRIORITY_LEVEL = "Priority";

        /**

         * Service Quatity

         */

        public static final String SERVICE_QTY = "serviceQty";



        /**

         * Status

         */

        public static final String STATUS = "status";



    }

}

