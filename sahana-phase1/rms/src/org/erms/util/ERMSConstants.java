package org.erms.util;


import org.sahana.share.db.DBConstantLoader;

public interface ERMSConstants {

    public static final String REQUEST_DETAIL_ID = "RequestDetailID";
    public static final String REQUEST_FULFIL_INFO = "RequestFulfilInfo";
    public static final String REQUEST_OBJECT = "RequestObject";
    public static final String REQUEST_DETAIL_OBJECT = "REQUEST_DETAIL_OBJECT";
    public static final String REQUEST_FULFILL_MODEL = "REQUEST_FULFILL_MODEL";





    public interface DataFields {
        public static final String DISTRICT = "District";
        public static final String CATEGORY = "Category";
        public static final String PRIORITY = "Priority";
        public static final String ORG_NAMES = "OrgnizationNames";

    }



    public interface IDataBaseConstants {
        public static final String dbUserName = DBConstantLoader.getDbUserName();
        public static final String dbPassword = DBConstantLoader.getDbPassword();
        public static final String dbURLConnectionString = DBConstantLoader.getDbUrl();
        public static final String dbDriver =DBConstantLoader.getDbDriver();

    }



    public interface IContextInfoConstants {
        public static final String ERROR_DESCRIPTION = "error_description";
        public static final String REQUEST_DTO = "request_dto";
        public static final String USER_INFO = "user_info";

    }
	public interface ISearchConstants {
			public static final String SEARCH_REQUEST = "Search=MAIN";
			public static final String SEARCH = "Search";
			public static final String MAIN_REQUEST = "MAIN";
		}

}


