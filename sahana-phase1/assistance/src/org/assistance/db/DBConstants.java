package org.assistance.db;


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



        public static final String OFFERS = "offers";



    }



    public interface TableColumns {
        public static final String OFFER_ID = "id";
        public static final String OFFER_AGANCY = "agency";
        public static final String OFFER_DATE = "date";
        public static final String OFFER_SECTOR = "sectors";
        public static final String OFFER_PARTNERS = "partners";
        public static final String OFFER_RELIEF_COMMITED_DETAIL = "relief_committed_details";
        public static final String OFFER_RELIEF_COMMITED_TOTEL = "relief_committed_total";
        public static final String OFFER_RELIEF_DISBURSED_DETAIL = "relief_disbursed_details";
        public static final String OFFER_RELIEF_DISBURSED_TOTEL = "relief_disbursed_total";
        public static final String OFFER_HR_COMMITED = "human_resources_committed";
        public static final String OFFER_NEEDSASSESMENT = "needs_assessments";
        public static final String OFFER_OTHER_ACTIVITIES = "other_activities";
        public static final String OFFER_PLANNED_ACTIVITES = "planned_activities";
        public static final String OFFER_OTHER_ISSUES = "other_issues";

//        id
//  `agency
//  `date` date
//  `sectors
//  `partners
//  `relief_committed_details
//  `relief_committed_total
//  `relief_disbursed_details
//  `relief_disbursed_total
//  `human_resources_committed
//  `needs_assessments
//  `other_activities
//  `planned_activities
//  `other_issues






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

        public static final String FUlFILL_ID = "FulfillID";
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

