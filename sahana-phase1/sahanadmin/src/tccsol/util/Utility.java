package tccsol.util;

import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Calendar;
import java.util.Vector;
import java.text.SimpleDateFormat;
import java.text.ParsePosition;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.Connection;
import java.sql.SQLException;
import tccsol.sql.DBConnection;
import tccsol.hris.SystemException;
import tccsol.hris.BusinessException;

public class Utility
{
    private static String [] frmt;
    static
    {
        try
        {
            //Get the required format from the database
            frmt = getFormats();
        }
        catch (SystemException ex)
        {
            frmt = null;
        }
    }


    public static boolean isTimeEmpty(String time)
    {
        boolean ret = false;

        if (time.length() != 4)
            ret = true;
        else if (time.equals("0000"))
            ret = true;

        return ret;
    }

    //Checks if valid time
    public static boolean isTime(String time)
    {
        boolean ret = true;

        if (time.length() != 4)
            ret = false;
        else if (isInt(time) == false)
            ret = false;

        return ret;
    }

    public static String getLastDate(String dat) throws Exception
    {
        String ldat = "";
        DBConnection con = null;
        Connection c = null;
        Statement stat = null;
        ResultSet res = null;
        try
        {
            con = new DBConnection();
            c = con.getConnection();
            stat = c.createStatement();

            res = stat.executeQuery("select last_day('" + dat.trim() + "') from dual");

            if (res.next())
            {
                if (res.getString(1) != null)
                    ldat = res.getString(1).trim();
            }
            if (stat != null)
                stat.close();
            if (res != null)
                res.close();

            if (ldat.length() == 0)
                throw new Exception("Invalid Date");
        }
        catch(SQLException e)
        {
            throw new Exception("Database Error: " + e.getMessage());
        }
        catch(Exception e)
        {
            throw new Exception("Invalid Day of the month");
        }
        finally
        {
            try
            {
                if (stat != null)
                    stat.close();
                if (res != null)
                    res.close();
                if (con != null)
                    con.closeConnection();
                if (c != null)
                    c.close();
            }
            catch(Exception e)
            {}
        }

        return ldat;
    }


    //Overload: 1
    //Converts the web page date to the format accepted by the database
    //Also checks for valid Date
    public static String formatDateToDB(String dat) throws SystemException
    {
        try
        {
            dat = dat.trim();

            if (dat.length() != 10)
                throw new Exception("Invalid date length");
            else if (!isInt(dat.substring(0, 2)))
                throw new Exception("Invalid Day");
            else if (!isInt(dat.substring(3, 5)))
                throw new Exception("Invalid Month");
            else if (!isLong(dat.substring(6, dat.length())))
                throw new Exception("Invalid Year");
            else
            {
                long ly = Long.parseLong(dat.substring(6, dat.length()));
                int im = Integer.parseInt(dat.substring(3, 5));

                if (im < 1 || im > 12)
                    throw new Exception("Month should be between 01-12");
                if (ly < 1900 || ly > 2300)
                    throw new Exception("Year should be between 1900-2300");
            }

            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]);

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(dat, pos);

            //Convert to the format accepted by the DB
            formatter = new SimpleDateFormat(frmt[0]);

            int mn = Integer.parseInt(dat.substring(3, 5));
            String mon = "";
            mon = getMonthShortName(mn);

            String s = getLastDate(dat.substring(0, 2) + "-" + mon + "-" + dat.substring(6, dat.length()));

            return formatter.format(dt);
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format for date check or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            String msg = "Date should be enetered in 'dd-MM-yyyy' format. ";
            if (ex.getMessage() != null)
                msg = msg + ex.getMessage();
            throw new SystemException(msg);
        }
    }

    //Overload: 2
    //Converts the web page date to the format accepted by the database
    //Also checks for valid Date
    public static String formatDateToDB(Date dat) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Convert to the format accepted by the DB
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[0]);
            return formatter.format(dat);
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format for date check or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Date should be enetered in 'dd-MM-yyyy' format");
        }
    }


    //Converts the database date to the format displayed by the web page
    public static String getDBDate(Date dat) throws SystemException
    {
        try
        {
            return formatDateToDisplay(formatDateToDB(dat));
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format from db, or databse date formats not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Errors Occured. " + ex.getMessage());
        }
    }

    //Overload: 1
    //Converts the database date to the format displayed by the web page
    //Also checks for valid Date
    public static String formatDateToDisplay(String dat) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Convert to the format accepted by the DB
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[0]);

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(dat, pos);

            //Set the format accepted by the website
            formatter = new SimpleDateFormat(frmt[1]);
            return formatter.format(dt);
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format for date check or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Date should be enetered in 'dd-MM-yyyy' format");
        }
    }

    //OVERLOAD 2
    //Converts the database date to the format displayed by the web page
    //Also checks for valid Date
    public static String formatDateToDisplay(Date dat) throws SystemException
    {


        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Convert to the format to display
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]);
            return formatter.format(dat);
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format for date check or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Date should be enetered in 'dd-MM-yyyy' format");
        }
    }


    //Adds the given number of Days to the given date
    public static String dateAdd(String dat, int num) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]);

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(dat, pos);

            //Add the given number to the given date
            GregorianCalendar cal = new GregorianCalendar();
            cal.setTime(dt);

            cal.add(Calendar.DAY_OF_MONTH, num);

            String dy = String.valueOf(cal.get(Calendar.DAY_OF_MONTH));
            if (dy.length() == 1)
                dy = "0" + dy;

            //VERY IMPORTANT
            //This version of JDK requires the 1 to be added to the month to get the correct value
            //if using a future vertion will have to remove the moneth (+ 1) statement
            String mn = String.valueOf(cal.get(Calendar.MONTH) + 1);
            if (mn.length() == 1)
                mn = "0" + mn;

            String yr = String.valueOf(cal.get(Calendar.YEAR));

            return dy + "-" + mn + "-" + yr;
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format for date addition or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Date should be enetered in 'dd-MM-yyyy' format");
        }
    }


    //Retrieves the Day from the given date
    public static String getDay(String dat) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]);

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(dat, pos);

            GregorianCalendar cal = new GregorianCalendar();
            cal.setTime(dt);

            String dy = String.valueOf(cal.get(Calendar.DAY_OF_MONTH));
            if (dy.length() == 1)
                dy = "0" + dy;

            return dy;
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format from db, or databse date formats not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("If Date is typed, use 'dd-MM-yyyy' format");
        }
    }


    //Retrieves the Time (24 hour format) from the given date
    public static String getTime(Date dat) throws SystemException
    {
        try
        {
            GregorianCalendar cal = new GregorianCalendar();
            cal.setTime(dat);

            String hr = String.valueOf(cal.get(Calendar.HOUR_OF_DAY));
            if (hr.length() == 1)
                hr = "0" + hr;

            String mn = String.valueOf(cal.get(Calendar.MINUTE));
            if (mn.length() == 1)
                mn = "0" + mn;

            return hr + mn;
        }
        catch(Exception ex)
        {
            throw new SystemException("Invalid Date format. Date should be in 'dd-MM-yyyy' format");
        }
    }


    //Retrieves the Month from the given date
    public static String getMonth(String dat) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]);

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(dat, pos);

            GregorianCalendar cal = new GregorianCalendar();
            cal.setTime(dt);

            //VERY IMPORTANT
            //This version of JDK requires the 1 to be added to the month to get the correct value
            //if using a future vertion will have to remove the moneth (+ 1) statement
            String mn = String.valueOf(cal.get(Calendar.MONTH) + 1);
            if (mn.length() == 1)
                mn = "0" + mn;

            return mn;
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format from db, or databse date formats not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("If Date is typed, use 'dd-MM-yyyy' format");
        }
    }


    //Retrieves the Year from the given date
    public static String getYear(String dat) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]);

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(dat, pos);

            GregorianCalendar cal = new GregorianCalendar();
            cal.setTime(dt);

            return String.valueOf(cal.get(Calendar.YEAR));
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format from db, or databse date formats not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("If Date is typed, use 'dd-MM-yyyy' format");
        }
    }



    //gets the db and web site formats from the db
    private static synchronized String[] getFormats() throws SystemException
    {
        Statement stat = null;
        ResultSet res = null;
        DBConnection con = null;
        String []frmt = new String[2];
        Connection cn = null;

        try
        {
            con = new DBConnection();
            cn = con.getConnection();
            stat = cn.createStatement();
            res = stat.executeQuery("Select DBFORMAT, DISPLAYFORMAT from TBLDATEFORMAT");
            res.next();
            frmt[0] = res.getString(1);
            frmt[1] = res.getString(2);
            if (stat != null)
                stat.close();
            if (res != null)
                res.close();
        }
        catch(Exception ex)
        {
            throw new SystemException("" + ex.getMessage());
        }
        finally
        {
            try {
                if (res != null)
                    res.close();
                if (stat != null)
                    stat.close();
                if (con != null)
                    con.closeConnection();
                if (cn != null)
                    cn.close();

                stat = null;
                res = null;
                con = null;
                cn = null;
            }catch(SQLException ex){}
        }
        return frmt;
    }


    //returns the day of the week (1 to 7) for a given date
    //Starts with sunday
    public static int dayOfWeek(String dat) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]);

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(dat, pos);

            GregorianCalendar cal = new GregorianCalendar();
            cal.setTime(dt);

            return cal.get(Calendar.DAY_OF_WEEK);
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format from db, or databse date formats not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("If Date is typed, use 'dd-MM-yyyy' format");
        }
    }


    public static Vector splitString(String str, char delim)
    {
        Vector strs = new Vector();
        int pos=0;
        for(int i=0; i<str.length(); i++)
        {
            if (str.charAt(i) == delim)
            {
                if (str.substring(pos, i).trim().length() != 0)
                {
                    strs.add(str.substring(pos, i).trim());
                    pos = i + 1;
                }
            }
            if (i == str.length() - 1 && str.charAt(str.length() - 1) != delim)
            {
                if (str.substring(pos, i + 1).trim().length() != 0)
                {
                    strs.add(str.substring(pos, i + 1).trim());
                }
            }
        }

        return strs;
    }

    public static Vector splitStringSpace(String str, char delim)
    {
        Vector strs = new Vector();
        int pos=0;
        for(int i=0; i<str.length(); i++)
        {
            if (str.charAt(i) == delim)
            {
                strs.add(str.substring(pos, i));
                pos = i + 1;
            }
            if (i == str.length() - 1 && str.charAt(str.length() - 1) != delim)
                strs.add(str.substring(pos, i + 1));
        }

        return strs;
    }

    public static boolean isInt(String num)
    {
        try{
            int number = Integer.parseInt(num);
            return true;
        }
        catch(Exception ex){  //NumberFormat & NullPointer
            return false;
        }
    }

    public static boolean isLong(String num)
    {
        try{
            long number = Long.parseLong(num);
            return true;
        }
        catch(Exception ex){
            return false;
        }
    }

    public static boolean isFloat(String num)
    {
        try{
            float number = Float.parseFloat(num);
            return true;
        }
        catch(Exception ex){
            return false;
        }
    }

    public static boolean isDouble(String num)
    {
        try{
            double number = Double.parseDouble(num);
            return true;
        }
        catch(Exception ex){
            return false;
        }
    }

    public static boolean lengthExceeded(String str, int max)
    {
        if (str.length() > max)
            return true;
        else
            return false;
    }

    //Overload: 2.1 returns date object
    //Converts the web page date to the format accepted by the database
    public static Date formatDateToDB2(String dat) throws SystemException
    {
        try
        {
            dat = dat.trim();

            if (dat.length() != 10)
                throw new Exception("Invalid date length");
            else if (!isInt(dat.substring(0, 2)))
                throw new Exception("Invalid Day");
            else if (!isInt(dat.substring(3, 5)))
                throw new Exception("Invalid Month");
            else if (!isLong(dat.substring(6, dat.length())))
                throw new Exception("Invalid Year");
            else
            {
                long ly = Long.parseLong(dat.substring(6, dat.length()));
                int im = Integer.parseInt(dat.substring(3, 5));

                if (im < 1 || im > 12)
                    throw new Exception("Month should be between 01-12");
                if (ly < 1900 || ly > 2300)
                    throw new Exception("Year should be between 1900-2300");
            }

            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }
            //Convert to the format accepted by the DB
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]);

            int mn = Integer.parseInt(dat.substring(3, 5));
            String mon = "";
            switch (mn) {
                case 1:{ mon = "Jan";
                    break;
                }
                case 2:{ mon = "Feb";
                    break;
                }
                case 3:{ mon = "Mar";
                    break;
                }
                case 4:{ mon = "Apr";
                    break;
                }
                case 5:{ mon = "May";
                    break;
                }
                case 6:{ mon = "Jun";
                    break;
                }
                case 7:{ mon = "Jul";
                    break;
                }
                case 8:{ mon = "Aug";
                    break;
                }
                case 9:{ mon = "Sep";
                    break;
                }
                case 10:{ mon = "Oct";
                    break;
                }
                case 11:{ mon = "Nov";
                    break;
                }
                case 12:{ mon = "Dec";
                    break;
                }
            }
            String s = getLastDate(dat.substring(0, 2) + "-" + mon + "-" + dat.substring(6, dat.length()));

            return formatter.parse(dat);
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format for date check or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {

            String msg = "Date should be enetered in 'dd-MM-yyyy' format.";
            if (ex.getMessage() != null)
                msg = msg + ex.getMessage();
            throw new SystemException(msg);
        }
    }

    //Checks if a date is between two dates
    public static boolean isDateBetween(Date chDt, Date dt1, Date dt2) throws SystemException
    {
        if (chDt == null || dt1 == null || dt2 == null)
            return false;
        else {
            if (chDt.equals(dt1) || chDt.equals(dt2))
                return true;
            else if (chDt.after(dt1) && chDt.before(dt2))
                return true;
            else
                return false;
        }
    }

    public static Date getDateWithTime(String displayDate, String time) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]+" "+"HHmm");

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(displayDate+" "+time, pos);

            return dt;
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Date should be enetered in 'dd-MM-yyyy' format");
        }
    }


    public static long convDurationToMin(String time) throws SystemException
    {
        try
        {
            int mid = time.indexOf(":");
            long h = 0;
            long m = 0;

            if (mid < 0)
                throw new SystemException("Invalid Time format");
            else {
                if (time.substring(0,mid).length() != 0)
                    h = Long.parseLong(time.substring(0,mid));

                if (time.substring(mid+1, time.length()).length() != 0)
                    m = Long.parseLong(time.substring(mid+1, time.length()));

                if (h < 0 || m < 0)
                    throw new SystemException("Invalid Time entry");
                if (m >= 60)
                    throw new SystemException("Invalid Time entry: Minutes cannot exceed 59");

                return ((h * 60) + m);
            }
        }
        catch(SystemException ex)
        {
            throw new SystemException(ex.getMessage());
        }
        catch(NumberFormatException nex)
        {
            throw new SystemException("Invalid numbers in Time entry");
        }
        catch(Exception e)
        {
            throw new SystemException(e.getMessage());
        }
    }


    public static String convDurationToHrsMin(long time) throws SystemException
    {
        try
        {
            String h = "";
            String m = "";
            if (time/60 < 10)
                h = "0" + String.valueOf(time/60);
            else
                h = String.valueOf(time/60);

            if (time%60 < 10)
                m = "0" + String.valueOf(time%60);
            else
                m = String.valueOf(time%60);

            return h + ":" + m;
        }
        catch(Exception e)
        {
            throw new SystemException(e.getMessage());
        }
    }

    public static long getDuration(Date startDate, Date endDate)
    {
        long start=0, end=0;
        start=startDate.getTime();
        end=endDate.getTime();
        return (startDate!=null && endDate!=null)?(end-start)/(60*1000):0;
    }


    public static long getDurationDays(Date startDate, Date endDate)
    {
        long start=0, end=0;
        start=startDate.getTime();
        end=endDate.getTime();
        return (startDate!=null && endDate!=null)?(end-start)/(60*1000*60*24):0;
    }

    public static boolean emailAddressCheck(String adrs)
    {
        if (adrs.trim().length() > 0)
        {
            int at, dot;
            at = adrs.indexOf('@');               //Must have 1 @ symbol
            if(at < 0)
                return false;
            else {
                String ad = adrs.substring(at+1);      //Not more than 1 @ symbol
                if (ad.indexOf('@') >= 0)
                    return false;
            }

            //Must have . (dot)
            if (adrs.indexOf('.') < 0)
                return false;
        }

        return true;
    }

    //from janagan
    public static float convTimeToFloat(String time) throws SystemException
    {
        if (time.length() != 4)
            throw new SystemException("Invalid Time format");
        else
            return Float.parseFloat(time.substring(0,2) + "." + time.substring(2, time.length()));
    }
    public static Date formatDateToDisplay2(String dbDate) throws SystemException
    {


        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            SimpleDateFormat formatter = new SimpleDateFormat(frmt[0]);

            return formatter.parse(dbDate);
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format for date check or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Date should be enetered in 'dd-MM-yyyy' format");
        }
    }

    public  static String findEmpNic(String empId) throws SystemException,BusinessException{

        DBConnection dbconn = null;
        Connection conn = null;
        Statement s=null;
        ResultSet rs=null;
        String empNic=null;
        String sql = "select EMPNIC from TBLPERSONALINFORMATION where EMPID='"
                +empId+"'";
        try {
            dbconn = new DBConnection();
            conn = dbconn.getConnection();
            s = conn.createStatement();
            rs = s.executeQuery(sql);

            if(rs.next()){
                empNic=rs.getString(1);
            }
            else{
                throw new BusinessException("EMP No not found");
            }
            rs.close();
        }catch(SQLException ex){
            throw new SystemException(ex.getMessage());
        }

        finally{
            try {
                if(s!=null){
                    s.close();
                }
                if(dbconn!=null){
                    dbconn.closeConnection();
                    conn=null;
                }

            }catch(SQLException ex){}
        }

        if(empNic==null){
            throw new BusinessException("EMP No not found");
        }
        return empNic;
    }


    public static Date getDateWithTime(java.util.Date date,String time) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }
            String displayDate = Utility.formatDateToDisplay(date);
            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]+" "+"HHmm");

            ParsePosition pos = new ParsePosition(0);
            Date dt = formatter.parse(displayDate+" "+time, pos);

            return dt;
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format for date check or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Date should be enetered in 'dd-MM-yyyy' format");
        }
    }


    public static String dateAdd(Date d, int unit, int count) throws SystemException
    {
        Calendar c = new GregorianCalendar();
        c.setTime(d);

        if (unit == Calendar.YEAR)
            c.add(Calendar.YEAR, count);
        else if (unit == Calendar.MONTH)
            c.add(Calendar.MONTH, count);
        else if (unit == Calendar.DAY_OF_MONTH)
            c.add(Calendar.DAY_OF_MONTH, count);
        else
            throw new SystemException("Invalid Unit for Date Arithmatic");

        String date = "";
        if (c.get(java.util.Calendar.DAY_OF_MONTH) < 10)
            date = "0" + c.get(java.util.Calendar.DAY_OF_MONTH);
        else
            date = "" + c.get(java.util.Calendar.DAY_OF_MONTH);

        int mn = c.get(java.util.Calendar.MONTH) + 1;  //+1 is depending on version of java
        if (mn < 10)
            date = date + "-0" + mn + "-" + c.get(java.util.Calendar.YEAR);
        else
            date = date + "-" + mn + "-" + c.get(java.util.Calendar.YEAR);

        return date;
    }


    //24 hour format
    public static Date timeAdd(String dt, String tm, int counth, int countm) throws SystemException
    {
        try
        {
            if (frmt == null)
            {
                //Get the required format from the database
                frmt = getFormats();
            }

            //Set the format accepted by the website
            SimpleDateFormat formatter = new SimpleDateFormat(frmt[1]+" "+"HHmm");

            ParsePosition pos = new ParsePosition(0);

            Calendar c = new GregorianCalendar();
            c.setTime(formatter.parse(dt+" "+tm, pos));

            c.add(Calendar.HOUR, counth);
            c.add(Calendar.MINUTE, countm);

            return c.getTime();
        }
        catch(SystemException ex)
        {
            throw new SystemException("Could not retrieve date format or databse date format not set: " + ex.getMessage());
        }
        catch(Exception ex)
        {
            throw new SystemException("Date should be enetered in 'dd-MM-yyyy' format");
        }
    }


    public static String getMonthName(int monthNo)
    {
        String month = "";
        switch (monthNo) {
            case 1:{ month = "January";
                break;
            }
            case 2:{ month = "February";
                break;
            }
            case 3:{ month = "March";
                break;
            }
            case 4:{ month = "April";
                break;
            }
            case 5:{ month = "May";
                break;
            }
            case 6:{ month = "June";
                break;
            }
            case 7:{ month = "July";
                break;
            }
            case 8:{ month = "August";
                break;
            }
            case 9:{ month = "September";
                break;
            }
            case 10:{ month = "October";
                break;
            }
            case 11:{ month = "November";
                break;
            }
            case 12:{ month = "December";
                break;
            }
        }
        return month;
    }


    public static String getMonthShortName(int mn)
    {
        String mon = "";
        switch (mn) {
            case 1:{ mon = "Jan";
                break;
            }
            case 2:{ mon = "Feb";
                break;
            }
            case 3:{ mon = "Mar";
                break;
            }
            case 4:{ mon = "Apr";
                break;
            }
            case 5:{ mon = "May";
                break;
            }
            case 6:{ mon = "Jun";
                break;
            }
            case 7:{ mon = "Jul";
                break;
            }
            case 8:{ mon = "Aug";
                break;
            }
            case 9:{ mon = "Sep";
                break;
            }
            case 10:{ mon = "Oct";
                break;
            }
            case 11:{ mon = "Nov";
                break;
            }
            case 12:{ mon = "Dec";
                break;
            }
        }
        return mon;
    }

    public static String getDayOfWeekName(int dayNo)
    {
        String day = "";
        switch (dayNo) {
            case 1:{ day = "Sunday";
                break;
            }
            case 2:{ day = "Monday";
                break;
            }
            case 3:{ day = "Tuesday";
                break;
            }
            case 4:{ day = "Wednesday";
                break;
            }
            case 5:{ day = "Thursday";
                break;
            }
            case 6:{ day = "Friday";
                break;
            }
            case 7:{ day = "Saturday";
                break;
            }
        }
        return day;
    }


    public static boolean isIllegalChar(String str)
    {
        boolean ret = false;

        String illegal = "/\\|{}'\"";

        for (int i=0; i<illegal.length(); i++)
        {
            if (str.indexOf(illegal.charAt(i)) >= 0)
            {
                ret = true;
                break;
            }
        }

        return ret;
    }


    public static String echoChar(char let, int num)
    {
        String ps = "";
        for (int i=0; i<num; i++)
            ps = ps + let;

        return ps;
    }
}
