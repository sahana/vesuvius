/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  TemplateRecord.java
 * @date       24 July 2006
 */


package sahana.mpr.rms;

/* Author : Thayalan Gugathashan
 */

public class TemplateRecord {

    private static String name;
    private static int recordid;

    public static void parse(String data) {

        int index = data.indexOf('|');
        name = data.substring(0, index);
        index++;
        recordid = Integer.parseInt(data.substring(index));
    }

    public static String getTemplate(String record) {
        parse(record);
        return (name);
    }

    public static int getRecordid(String record) {
        parse(record);
        return (recordid);
    }
}
