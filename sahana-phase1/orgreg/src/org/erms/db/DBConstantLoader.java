package org.erms.db;

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

    private static String mamboDbUserName=null;
    private static String mamboDbPassword=null;
    private static String mamboDbUrl=null;
    private static String mamboDbDriver=null;

    static {
        ResourceBundle dbParamBundle = ResourceBundle.getBundle("org.erms.db.db");
        dbUserName = dbParamBundle.getString("db.username");
        dbPassword = dbParamBundle.getString("db.password");
        dbUrl= dbParamBundle.getString("db.url");
        dbDriver = dbParamBundle.getString("db.driver");

        mamboDbUserName = dbParamBundle.getString("db.mambo.username");
        mamboDbPassword = dbParamBundle.getString("db.mambo.password");
        mamboDbUrl= dbParamBundle.getString("db.mambo.url");
        mamboDbDriver = dbParamBundle.getString("db.mambo.driver");



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

    public static String getMamboDbUserName() {
        return mamboDbUserName;
    }

    public static String getMamboDbPassword() {
        return mamboDbPassword;
    }

    public static String getMamboDbUrl() {
        return mamboDbUrl;
    }

    public static String getMamboDbDriver() {
        return mamboDbDriver;
    }
}
