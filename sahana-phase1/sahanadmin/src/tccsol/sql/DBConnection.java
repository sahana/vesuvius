package tccsol.sql;

import tccsol.hris.SystemException;
import tccsol.util.Utility;

import java.sql.*;
import java.util.Vector;

/*
class has methods to...
-----------------------
1) Load the driver & establish the connection to the database
2) Execute various queries (insert / update / delete / select)
3) Check the existance of a given value in a given column of a given table
4) Check the existance of a given row in a given column of a given table
5) Generate a new numeric id for a given table column
6) Close the connection
7) Retrive a value when another is given
8) Check if connection is closed
*/

public class DBConnection
{
    private  Connection con;


    private static String  dsn = "oracle.jdbc.OracleDriver";
    private static String url = "jdbc:oracle:oci8:@hrissagt";
    private static String  user = "HRISSAGT";
    private static String  pass = "HRISSAGT";

    //Default constructor
    public DBConnection() throws SQLException
    {
           openConnection();
    }

//
//    static
//    {
//        try
//        {
//
//         new tccsol.sql.pool.JDCConnectionDriver("hris",dsn,url,user,pass);
//        }
//        catch(Exception e)
//        {}
//   }


/*
Load the driver and establish a connection to the database with given user name and password.
*/
    public void openConnection() throws SQLException
    {
      try {
        con = this.getConnection();
      }catch(SystemException ex){throw new SQLException(ex.getMessage());}
    }

/*
find out if connection is open or not
*/
    public boolean isClosed() throws SQLException
    {
        try
        {
            return con.isClosed();
        }
        catch(SQLException sqle)
        {
            throw sqle;
        }
    }


/*
return connection it.
*/
    public Connection getConnection() throws SystemException {
        try {
            return org.sahana.DBConnection.createConnection();
        } catch (SQLException e) {
            throw new SystemException(e.getMessage());
        }
    }


/*
Checks for the existance of a value in a giventable in a given column
*/
    public boolean exists(String value, String table, String column) throws SQLException
    {
        Statement stat = null;
        ResultSet resultset = null;
        boolean res = false;

        try
        {


            stat = con.createStatement();
            resultset = stat.executeQuery("select * from " + table.trim()
                    + " where " + column.trim() + " = '" + value.trim() + "'");

            if (resultset.next()){
                res = true;
            }
        }
        catch(SQLException ex){
            // rethrow the thrown exception
            throw ex;
        }
        finally
        {
            try {
                if (stat != null)
                    stat.close();
                if (resultset != null)
                    resultset.close();

                stat = null;
                resultset = null;
            }catch(SQLException ex){}

        }
        return res;
    }


/*
Checks for the existance of a giventable row
*/
    public boolean rowExists(String statement) throws SQLException
    {
        Statement stat = null;
        ResultSet resultset = null;
        boolean res = false;

        try
        {


            stat = con.createStatement();
            resultset = stat.executeQuery(statement);

            if (resultset.next()){
                res = true;
            }
        }
        catch(SQLException ex){
            // rethrow the thrown exception
            throw ex;
        }
        finally
        {
            try {
                if (stat != null)
                    stat.close();
                if (resultset != null)
                    resultset.close();

                stat = null;
                resultset = null;
            }catch(SQLException ex){}

        }
        return res;
    }



/*
Retrieves the corresponding value of one column that matches the
value of another column
*/

//value = the value to be compared
//tbl = table name
//col1 = column from which value will be retrieved
//col2 = column in which value will be checked
//typ = Type: N for Numeric / S for String / D for date
    public String getValue(String value, String tbl, String col1, String col2, char typ) throws Exception
    {
        Statement stat = null;
        ResultSet resultset = null;
        String val = "";

        try
        {


          stat = con.createStatement();

            if ((typ == 'N') || (typ == 'n')) {
                resultset = stat.executeQuery("select " + col1 + " from " + tbl + " where " + col2 + " = " + value);
            }
            else {
                resultset = stat.executeQuery("select " + col1 + " from " + tbl + " where " + col2 + " = '" + value + "'");
            }

            if (typ == 'D' || typ == 'd') {
                if (resultset.next()){
                    if (resultset.getString(1) != null)
                        val = tccsol.util.Utility.getDBDate(resultset.getDate(1));
                }
            }
            else if (typ == 'N' || typ == 'S' || typ == 's' || typ == 'n')
            {
                if (resultset.next()){
                    if (resultset.getString(1) != null)
                        val = resultset.getString(1).trim();
                }
            }
        }
        catch(SQLException ex){
            // rethrow the thrown exception
            throw ex;
        }
        catch(SystemException ex2){
            // rethrow the thrown exception
            throw ex2;
        }
        finally
        {
            try {
                if (stat != null)
                    stat.close();
                if (resultset != null)
                    resultset.close();

                stat = null;
                resultset = null;
            }catch(SQLException ex){}

        }
        return val;
    }


/*
Generates a new numeric id for given table column
*/
    public static synchronized String newIdGen(String tablenm, String colnm) throws SQLException
    {
        Statement stat = null;
        ResultSet resultset = null;
        DBConnection cn = null;
        Connection c = null;

        try
        {
            cn = new DBConnection();
            c = cn.getConnection();
            stat = c.createStatement();
            resultset = stat.executeQuery("select max(" + colnm + ") from " + tablenm);

            if (resultset.next())
            {
                if (resultset.getString(1) == null)
                {
                    return "1";
                }
                else
                {
                    return String.valueOf(Long.parseLong(resultset.getString(1)) + 1);
                }
            }
            else {
                return "1";
            }
        }
        catch(Exception ex){
            throw new SQLException(ex.getMessage());
        }
        finally
        {
            try {
                if (stat != null)
                    stat.close();
                if (resultset != null)
                    resultset.close();
                if (cn != null)
                    cn.closeConnection();
                if (c != null)
                    c.close();

                resultset = null;
                stat = null;
                cn = null;
                c = null;
            }
            catch(SQLException ex){}

        }
    }

    //Insert / Update / Delete the value given by the Query to the Database.
    //Maintains transactional integrity
    public int executeUpdateTransaction(String query, Vector rows, String []flags, String AutoTbl, String AutoCol) throws SQLException
    {
        Vector row = new Vector();
        PreparedStatement stat = null;
        con.setAutoCommit(false);
        int valueIns=0;

        try
        {
            for (int i=0; i<rows.size(); i++)
            {
                row = Utility.splitString((String) rows.elementAt(i), '/');

                stat = con.prepareStatement(query);

                for(int j=0; j<row.size(); j++) //Set columns according to data type
                {
                    if (flags[j].equals("I"))
                        stat.setInt(j+1, Integer.parseInt((String) row.elementAt(j)));
                    else if (flags[j].equals("L"))
                        stat.setLong(j+1, Long.parseLong((String) row.elementAt(j)));
                    else if (flags[j].equals("F"))
                        stat.setFloat(j+1, Float.parseFloat((String) row.elementAt(j)));
                    else if (flags[j].equals("D"))
                        stat.setDouble(j+1, Double.parseDouble((String) row.elementAt(j)));
                    else if (flags[j].equals("S"))
                        stat.setString(j+1, (String) row.elementAt(j));
                    else if (flags[j].equals("Dt"))
                        stat.setString(j+1, Utility.formatDateToDB((String) row.elementAt(j)));
                    else if (flags[j].equals("A"))
                        stat.setLong(j+1, Long.parseLong(this.newIdGen(AutoTbl, AutoCol)));
                }

                valueIns = valueIns + stat.executeUpdate();
            }

            con.commit();
            return valueIns;
        }
        catch (Throwable ex)
        {
            if (con != null)
            {
                try
                {
                    con.rollback();
                    valueIns = 0;
                }
                catch(SQLException excep)
                {}
            }
        }
        finally
        {
            try {
                if (con != null)
                {
                    con.setAutoCommit(true);
                    con.close();
                }
                if (stat != null)
                    stat.close();
            }
            catch(SQLException ex){}
        }
        return valueIns;
    }



    //Insert / Update / Delete the value given by the Query to the Database.
    public int executeUpdate(String query) throws SQLException
    {
        Statement stat = null;
        int valueIns=0;
        try
        {
            stat = con.createStatement();
            valueIns = stat.executeUpdate(query);
        }
        catch (SQLException ex)
        {
            //re-throw the exception
            throw ex;
        }
        finally
        {
            try {
                if (stat != null)
                    stat.close();
            }catch(SQLException ex){}
            //never return a value in a finally clause--supresses the thrown exception
        }
        return valueIns;
    }

//This method is used to close the Database connection, Satement and Resultset.
    public void closeConnection()
    {
        try
        {
            if(con != null)
                con.close();
        }
        catch(SQLException ex)
        {}
    }
} //End of Class DBConnection
