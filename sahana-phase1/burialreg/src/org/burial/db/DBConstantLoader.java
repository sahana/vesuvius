package org.burial.db;

import java.util.ResourceBundle;

/**
 * Copyright 2001-2004 The Apache Software Foundation.
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
public class DBConstantLoader {

    private static String dbUserName=null;
    private static String dbPassword=null;
    private static String dbUrl=null;
    private static String dbDriver=null;

    static {
        ResourceBundle dbParamBundle = ResourceBundle.getBundle("org.burial.db.db");
         dbUserName = dbParamBundle.getString("db.username");
         dbPassword = dbParamBundle.getString("db.password");
         dbUrl= dbParamBundle.getString("db.url");
         dbDriver = dbParamBundle.getString("db.driver");
    }

    public static String getDbUserName() {
        return dbUserName;
    }

    public static String getDbPassword() {
        return dbPassword;
    }

    public static String getDbUrl() {
        return dbUrl;
    }

    public static String getDbDriver() {
        return dbDriver;
    }

}
