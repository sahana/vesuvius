package tccsol.admin.accessControl;

import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.Connection;
import java.sql.SQLException;
import tccsol.sql.DBConnection;
import tccsol.hris.SystemException;
import java.util.Vector;

public class AccessControl
{
    private Vector messages;

    public AccessControl() throws SQLException
    {
        messages = new Vector();
    }

    public boolean hasAccess(long mod, long rol, String lvl, String rolNm, String opName)
    {
        Connection con = null;
        DBConnection cn = null;
        PreparedStatement stat = null;
        ResultSet rs = null;

        boolean ret = false;
        messages.clear();
        String perm = "";

        String sql = "select PERMISSION from TBLACCESSPERMISSIONS where MODULEID=? and ROLEID=? and upper(ACCESSLEVEL) = ?";

        try
        {
            cn = new DBConnection();
            con = cn.getConnection();
            stat = con.prepareStatement(sql);
            stat.setLong(1, mod);
            stat.setLong(2, rol);
            stat.setString(3, lvl.toUpperCase());
            rs = stat.executeQuery();

            if (rs.next()) {
                if (rs.getString(1) != null)
                {
                    perm = rs.getString(1);

                    if (perm.equalsIgnoreCase("Y"))
                      ret = true;
                    else {
                      String str = "";
                      if (rolNm.equalsIgnoreCase("PAGE"))
                        str = "Access Denied: The current user role (" + rolNm + ") does not have permission to access the module";
                      else
                        str = "Access Denied: The current user role (" + rolNm + ") does not have permission to perform the '"
                                + opName +"' operation for the current module";
                      messages.add(str);
                    }
                }
           }
           else
               messages.add("System Error: Module Access Permission for current user role not set. Contact System Administrator");
        }
        catch(Exception ex)
        {
            messages.add("System Error: "+ex.getMessage());
        }
        finally
        {
          try {
            if (cn != null) {
              cn.closeConnection();
              cn = null;
            }
            if (stat != null) {
              stat.close();
              stat = null;
            }
            if (rs != null) {
              rs.close();
              rs = null;
            }
            if (con != null) {
              con.close();
              con = null;
            }
          }
          catch(Exception e){}
        }

        return ret;
    }

    //Getter for messages
    public Vector getMessages() {
      return messages;
    }

    //Setter for messages
    public void setMessages(Vector messages) {
      this.messages = messages;
    }
}