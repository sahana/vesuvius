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

public interface DBConstants {

    public interface User{
        public static final String TABLENAME = "user";
        public static final String USER_NAME = "UserName";

        public static final String PASSWORD = "Password";
          public static final String ORG_CODE = "OrgCode";
    }

    public interface District {
        public static final String TABLENAME = "camps_district";
        public static final String DIST_NAME = "DIST_NAME";
        public static final String DIST_CODE = "DIST_CODE";
        public static final String PROV_CODE = "PROV_CODE";
    }

     public interface Division {
            public static final String TABLENAME = "camps_division";
            public static final String DIV_NAME = "DIV_NAME";
            public static final String DIV_ID = "DIV_ID";
            public static final String DIST_CODE = "DIST_CODE";
        }

     public interface Province {
        public static final String TABLENAME = "camps_province";
        public static final String PROV_CODE = "PROV_CODE";
        public static final String PROV_NAME = "PROV_NAME";
    }

     public interface Area {
        public static final String TABLENAME = "hse_area_mst";
        public static final String AREA_ID = "AREA_ID";
        public static final String MEASUREMENT = "MEASUREMENT";
    }

    public interface Term {
        public static final String TABLENAME = "hse_term_mst";
        public static final String TERM_ID = "TERM_ID";
        public static final String DESCRIPTION = "DESCRIPTION";
    }

    public interface OwnedBy{
        public static final String TABLENAME = "hse_owned_by_mst";
        public static final String OWNED_BY_ID = "OWNED_BY_ID";
        public static final String OWNED_BY_NAME = "OWNED_BY_NAME";
    }




    public interface Category {
        public static final String TABLENAME = "category";
        public static final String CAT_CODE = "CatCode";
        public static final String CAT_DESCRIPTION = "CatDescription";
    }

    public interface Priority {
        public static final String TABLENAME = "priority";
        public static final String PRIORITY_LEVEL = "Priority";
        public static final String PRIORITY_DESCRIPTION = "Description";
    }

   public interface Land{
       public static final String TABLENAME = "HSE_LAND_MST";
       public static final String LAND_NAME = "LAND_NAME";
       public static final String DIVISION_ID = "DIVISION_ID";
       public static final String DESCRIPTION = "DESCRIPTION";
       public static final String AREA_ID = "AREA_ID";
       public static final String GPS1 = "GPS1";
       public static final String GPS2 = "GPS2";
       public static final String GPS3 = "GPS3";
       public static final String GPS4 = "GPS4";
       public static final String MEASUREMENT ="MEASUREMENT";
       public static final String TERM_ID = "TERM_ID";
       public static final String OWNED_BY_ID = "OWNED_BY_ID";
       public static final String OWNED_BY_COMMENT = "OWNED_BY_COMMENT";
   }

    public interface Requestheader {
        public static final String TABLENAME = "requestheader";
        public static final String REQUEST_ID = "RequestID";
        public static final String ORG_COMMENTS = "Comments";
        public static final String CREATE_DATE = "CreateDate";
        public static final String REQUEST_DATE = "RequestDate";
        public static final String CALLER_NAME = "CallerName";
        public static final String CALLER_ADDRESS = "CallerAddress";
        public static final String CALLER_CONTACT_NO = "CallerContactNo";

        public static final String SITE_TYPE = "SiteType";
        public static final String SITE_DISTRICT = "SiteDistrict";
        public static final String SITE_AREA = "SiteArea";
        public static final String SITE_NAME = "SiteName";
        public static final String SITE_CONTACT = "SiteContact";

        public static final String ORG_CODE = "OrgCode";
        public static final String FULLFILL_STATUS_DESCRIPTION = "Description";
    }


    public interface Requestdetail {
        public static final String REQUEST_ID = "RequestID";
        public static final String TABLENAME = "requestdetail";
        public static final String REQUEST_DETAIL_ID = "RequestDetailId";
        public static final String REQUEST_FULFILL_ID = "FulfullId";
        public static final String CATEGORY = "Category";
        public static final String ITEM = "Item";
        public static final String UNIT = "Unit";
        public static final String QUANTITY = "Quantity";

        public static final String CAT_CODE = "CatCode";
        public static final String CAT_DESCRIPTION = "CatDescription";
        //public static final String SERVICE_QTY = "serviceQty";

        public static final String REQUEST_STATUS_DESCRIPTION = "Description";
        public static final String FULLFILL_STATUS_DESCRIPTION = "Description";
         public static final String PRIORITY_LEVEL = "Priority";
          public static final String REQUEST_STATUS = "Status";



    }



    public interface Organization {
        public static final String TABLENAME = "organization";
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
        public static final String STATUS = "Status";


    }

    public interface Fulfillstatus {
        public static final String TABLENAME = "fulfillstatus";
        public static final String FULLFILL_STATUS = "Status";
        public static final String FULLFILL_STATUS_DESCRIPTION = "Description";
    }


    public interface Requestfulfill {
        public static final String TABLENAME = "requestfulfill";
        public static final String FUlFILL_ID = "FulfullID";
        public static final String ORG_CODE = "OrgCode";
        public static final String REQUEST_DETAIL_ID = "RequestDetailId";
         public static final String SERVICE_QTY = "serviceQty";
        public static final String FULLFILL_STATUS = "Status";
         public static final String REQUEST_FULFILL_ID = "FulfullId";
    }

    public interface Requeststatus {
        public static final String TABLENAME = "requeststatus";
        public static final String REQUEST_STATUS = "Status";
        public static final String REQUEST_STATUS_DESCRIPTION = "Description";

    }


    public interface Sitetype {
        public static final String TABLENAME = "sitetype";
        public static final String SITE_TYPE_CODE = "SiteTypeCode";
        public static final String SITE_TYPE = "SiteType";
    }

    public interface Statushistory {
        public static final String TABLENAME = "statushistory";
        public static final String FUlFILL_REAL_ID = "FulfillID";
        public static final String STATUS_CHANGED_DATE = "ChangedDate";
        public static final String CHANGED_STAUS = "ChangedStatus";

    }


    public interface SQL {

        public static final String SELECT = "select";

    }
}
