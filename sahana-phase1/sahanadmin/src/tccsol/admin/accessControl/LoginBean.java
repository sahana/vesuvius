package tccsol.admin.accessControl;

import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.Connection;
import java.sql.SQLException;
import tccsol.sql.DBConnection;
import tccsol.hris.SystemException;
import java.util.Vector;
import java.util.Date;
import java.util.Calendar;
import java.util.GregorianCalendar;

public class LoginBean
{
    private String userName = "";
    private String password = "";
    private long roleId = 0;
    private String roleName = "";
    private String orgId = "";
    private String orgName = "";
    private String targetUrl = "";

    private Vector messages;

    public LoginBean() throws SQLException
    {
        messages = new Vector();
    }

    protected boolean isValidUser()
    {
        DBConnection conn = null;
        Connection con = null;
        PreparedStatement stat = null;
        ResultSet rs = null;
        boolean ret = false;
        messages.clear();

        String sql = "SELECT u.username, password, o.Orgcode, OrgName, l.RoleId, RoleName FROM user u, TBLUSERROLES r, "
            + "TBLROLES l, organization o where upper(u.username) = upper(r.username) and o.Orgcode = u.Orgcode and "
                + "r.RoleId = l.RoleId and upper(u.username) = ?";

        try
        {
            conn = new DBConnection();
            con = conn.getConnection();
            stat = con.prepareStatement(sql);
            stat.setString(1, this.userName.toUpperCase());   //User name not case sensitive

            rs = stat.executeQuery();

            if (rs.next()) {
                String pass = "";
                if (rs.getString(1) != null)
                    this.userName = rs.getString(1);
                if (rs.getString(2) != null)
                    pass = rs.getString(2);
                if (rs.getString(3) != null)
                    this.orgId = rs.getString(3);
                if (rs.getString(4) != null)
                    this.orgName = rs.getString(4);
                roleId = rs.getLong(5);
                if (rs.getString(6) != null)
                    this.roleName = rs.getString(6);
          //encrypted
            // if (!tccsol.security.MD5toHexConverter.md5(this.password).equals(pass))
             if (!pass.equals(this.password))
              messages.add("Invalid Password (Password is case sensitive)");
            }
            else
                messages.add("Invalid User Name");
        }
        catch(Exception ex)
        {
            messages.add("Error validating login: " + ex.getMessage());
        }
        finally
        {
            try {
                if (conn != null) {
                    conn.closeConnection();
                    conn = null;
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


    //Getter methods
    public Vector getMessages() {
        return messages;
    }
    public String getPassword() {
        return password;
    }
    public long getRoleId() {
        return roleId;
    }
    public String getRoleName() {
        return roleName;
    }
    public String getUserName() {
        return userName;
    }
    public String getOrgId() {
        return orgId;
    }
    public String getOrgName() {
        return orgName;
    }
    public String getTargetUrl() {
        return targetUrl;
    }

    //Setter methods
    public void setMessages(Vector messages) {
        this.messages = messages;
    }
    public void setPassword(String password) {
        this.password = password;
    }
    public void setRoleId(long roleId) {
        this.roleId = roleId;
    }
    public void setRoleName(String roleName) {
        this.roleName = roleName;
    }
    public void setUserName(String userName) {
        this.userName = userName;
    }
    public void setOrgId(String orgId) {
        this.orgId = orgId;
    }
    public void setOrgName(String orgName) {
        this.orgName = orgName;
    }
    public void setTargetUrl(String targetUrl) {
        this.targetUrl = targetUrl;
    }
}
