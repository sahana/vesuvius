package sahana;
import java.sql.*;


public class DatabaseAccess
{
    
    public static Connection getConnection(String ip,String database,String user,String pass)throws SQLException
    {
        String url="jdbc:mysql://"+ip+"/"+database;
        try
        {
            Class.forName("com.mysql.jdbc.Driver");
        }
        catch (ClassNotFoundException ex)
        {
            ex.printStackTrace();
        }
        
        Connection con=null;
        try
        {
            con=DriverManager.getConnection(url,user,pass);
        }
        catch (SQLException ex)
        {
            throw ex;
        }
        
        return con;
    }
    
    public static Statement getStatement(String ip,String database,String user,String pass)throws SQLException
    {
        try
        {
            return getConnection(ip,database,user,pass).createStatement();
        }
        catch (SQLException ex)
        {
            throw ex;
        }
    }
    private static int getResultsetRowCount(ResultSet res)
    {
        int count=0;
        try
        {
            while(res.next())
            {
                ++count;
            }
            res.beforeFirst();
        }
        catch (SQLException ex)
        {
            ex.printStackTrace();
        }
        return count;
        
    }
    
}
