/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/

package org.damage.common;

import java.util.Locale;
import java.util.MissingResourceException;
import java.util.ResourceBundle;
import java.util.Vector;

/**
 * @author Viraj Samaranayake
 * @version 1.0
 */

public class ConfigReader {

    private static ResourceBundle m_logResourceBundle;
    private static ResourceBundle m_settingsResourceBundle;
    private static ResourceBundle m_queryResourceBundle;

    public static String LOG_RESOURCE_BUNDLE = "resources";
    public static String SETTINGS_RESOURCE_BUNDLE = "application";
    public static String QUERY_RESOURCE_BUNDLE = "hibernateQueries";
    public static final String RESOURCE_KEY_NOT_FOUND = " ?? UNDIFINED  KEY ??";
    public static final String RESOURCE_MESSAGE_NOT_FOUND = " ?? UNDIFINED  MSG ??";

    private static Locale logLocale;

    static {

        try {
            logLocale = new Locale("en", "US");

            m_logResourceBundle = ResourceBundle.getBundle(LOG_RESOURCE_BUNDLE,
                    logLocale);
            m_queryResourceBundle = ResourceBundle.getBundle(QUERY_RESOURCE_BUNDLE);
            m_settingsResourceBundle = ResourceBundle.getBundle(SETTINGS_RESOURCE_BUNDLE);

        } catch (NullPointerException ex) {
            throw  ex;
        } catch (MissingResourceException ex) {
            throw ex;
        }

    }

    /**
     * get the  message from the  resource bundle  for a given key
     *
     * @param key -Resource Bundle  key
     * @return - Message string corrosponding to resource key
     */
    public static String getSettingsValue(String key) {
        String value = null;
        try {
            value = m_settingsResourceBundle.getString(key);
        } catch (Exception ex) {
            return RESOURCE_KEY_NOT_FOUND;
        }

        return value;
    }

    /**
     * Returns an HQL query from the resource bundle.
     *
     * @param key the resource key
     * @return String
     */
    public static String getQueryString(String key) {
        String value;
        try {
            value = m_queryResourceBundle.getString(key);
        } catch (Exception ex) {
            return RESOURCE_KEY_NOT_FOUND;
        }

        return value;
    }


    /**
     * get the  configuration value for a given key
     *
     * @param key -Resource Bundle key
     * @return - string value corrosponding to resource key
     */
    public static String getMessage(String key) {
        String message = null;
        try {
            message = m_logResourceBundle.getString(key);
        } catch (Exception ex) {
            return RESOURCE_MESSAGE_NOT_FOUND;
        }

        return message;
    }

    public static Vector getEnabledClassificationNodes() {
        String[] s = getSettingsValue("selection.hierarchy.enabled.types").split(",");
        Vector nodes = new Vector();
        if (s != null) {
            for (int i = 0; i < s.length; i++)
                nodes.add(s[i]);
        }
        return nodes;
    }

    public static String getActionUpdateHelperClassName(String typecode) {
        try {
            String key = "customdata.processor." + typecode;
            return m_settingsResourceBundle.getString(key);
        } catch (Exception e) {
            return null;
        }
    }

}

