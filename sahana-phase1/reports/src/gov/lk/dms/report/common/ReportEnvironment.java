package gov.lk.dms.report.common;

import java.io.IOException;
import java.util.Enumeration;
import java.util.Properties;

/**
 * 
 * @author  Thushera P. Kawdawatta.
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $
 *  
 */
public final class ReportEnvironment {

    private static ReportEnvironment sInstance;

    private static Properties sProperties;

    private ReportEnvironment() {
        load();
    }

    private static void load() {
        sProperties = new Properties();

        try {
            sProperties.load(ReportEnvironment.class.getResourceAsStream("/config/report-config.properties"));
        } catch (IOException e) {
            e.printStackTrace();

            return;
        }
        //ResourceBundle bundle = ResourceBundle.getBundle("config.ved-config");
        //bundle = PropertyResourceBundle.getBundle("config.ved-config");

        Enumeration keys = sProperties.keys();
        String key = null;

        while (keys.hasMoreElements()) {
            key = (String) keys.nextElement();

            System.out.println("Key " + key + " value = " + sProperties.getProperty(key));
        }
    }

    public String getProperty(String key) {
        return sProperties.getProperty(key);
    }

    public static final ReportEnvironment getInstance() {

        return sInstance == null ? sInstance = new ReportEnvironment() : sInstance;
    }

}