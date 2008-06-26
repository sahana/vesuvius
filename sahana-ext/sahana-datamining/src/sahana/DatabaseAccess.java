package sahana;
import java.sql.*;


public class DatabaseAccess
{
    
    public static Connection getConnection()
    {
        String url="jdbc:mysql://localhost/sahana_dm";
        String user="root";
        String pass="root";
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
            ex.printStackTrace();
        }
        
        return con;
    }
    
    public static Statement getStatement()
    {
        try
        {
            return getConnection().createStatement();
        }
        catch (SQLException ex)
        {
            ex.printStackTrace();
        }
        
        return null;
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
