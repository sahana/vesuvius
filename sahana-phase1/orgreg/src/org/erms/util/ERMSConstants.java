/*

 * Created on Dec 30, 2004

 *

 * To change the template for this generated file go to

 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

 */

package org.erms.util;

import org.erms.db.DBConstantLoader;


/**

 * @author Administrator

 *         <p/>

 *         To change the template for this generated type comment go to

 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments

 */

public interface ERMSConstants {



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
    public interface IMamboDataBaseConstants {
        public static final String dbUserName = "www-data";
        public static final String dbPassword = "EemL5h";
        public static final String dbURLConnectionString = "jdbc:mysql://127.0.0.1/mambo";
        public static final String dbDriver = "com.mysql.jdbc.Driver";

    }


    public interface IContextInfoConstants {
        public static final String ERROR_DESCRIPTION = "error_description";
        public static final String REQUEST_DTO = "request_dto";
        public static final String USER_INFO = "user_info";

        public static final String ACTION = "action";
        public static final String ACTION_ADD = "add";
        public static final String ACTION_EDIT = "edit";
        public static final String ACTION_VIEW = "view";


    }

    public interface ERMSSectorNameConstants{

        public static final String[] SECTORS = {"Water and Sanitation"
                                                , "Construction"
                                                , "Shelter"
                                                , "Infrastructure"
                                                , "Medical supplies and Medicine"
                                                , "Medical personnel"
                                                , "Child care"
                                                , "Education"
                                                , "Psychosocial"
                                                , "Empowerment"
                                                , "Fishing Community Support"
                                                , "Livelihoods"
                                                , "Gender based activities"
                                                , "Food relief"
                                                , "Clothes;utensils etc"
                                                , "Volunteers"
                                                , "Assesments"};
    }

}

