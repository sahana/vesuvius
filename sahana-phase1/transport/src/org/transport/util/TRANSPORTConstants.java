/*
 * Created on Dec 30, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
package org.transport.util;

/**
 * @author Administrator
 *         <p/>
 *         To change the template for this generated type comment go to
 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public interface TRANSPORTConstants {

    public interface DataFields {

        public static final String DISTRICT = "District";

        public static final String CATEGORY = "Category";

        public static final String PRIORITY = "Priority";

        public static final String ORG_NAMES = "OrgnizationNames";
    }

    public interface IDataBaseConstants {
        /**
         * The data base user name
         */
        public static final String dbUserName = "root";

        /* The data base password */
        public static final String dbPassword = "";


        /* The data base URL */
        public static final String dbURLConnectionString = "jdbc:mysql://192.168.101.14/transport";

        /* The MySQL Driver */
        public static final String dbDriver = "com.mysql.jdbc.Driver";
    }

    public interface IContextInfoConstants {
        public static final String ERROR_DESCRIPTION = "error_description";
        public static final String TRANSPORT_DTO = "transport_dto";
        public static final String USER_INFO = "user_info";
    }

}
