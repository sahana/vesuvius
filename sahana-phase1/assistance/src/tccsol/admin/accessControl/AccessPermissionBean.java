package tccsol.admin.accessControl;

import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.Statement;
import java.sql.Connection;
import java.sql.SQLException;
import tccsol.sql.DBConnection;
import tccsol.hris.SystemException;
import tccsol.util.Utility;
import java.util.Vector;

public class AccessPermissionBean
{
    private DBConnection conn;

    private String moduleId = "";
    private String moduleName = "";
    private String roleId = "";
    private String roleName = "";
    private String selMode = "";
    private String mode = "";

    private Vector messages;
    private Vector levels;
    private Vector permissions;

    public AccessPermissionBean() throws SQLException
    {
        conn = new DBConnection();
        messages = new Vector();
        levels = new Vector();
        permissions = new Vector();
    }


    //To insert the data into the db table
    public boolean insert() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;
        messages.clear();

        //create sql string
        String sql = "";
        if (mode.equalsIgnoreCase("I"))
          sql = "insert into TBLACCESSPERMISSIONS (PERMISSION, MODULEID, ACCESSLEVEL, ROLEID) values (?, ?, ?, ?)";
        else if (mode.equalsIgnoreCase("U"))
          sql = "update TBLACCESSPERMISSIONS set PERMISSION = ? where MODULEID=? and ACCESSLEVEL=? and ROLEID=?";
        else {
          messages.add("Error retrieving insert information");
          return false;
        }

        if (roleId.trim().length() == 0)
          messages.add("Role not selected/entered");

        if (moduleId.trim().length() == 0)
          messages.add("Module not selected/entered");

        if (permissions.size() == 0 || levels.size() == 0)
          messages.add("Role or module not selected/entered");
        else if (permissions.size() != levels.size())
          messages.add("Error retrieving insert data");

        if (messages.size() > 0)
          return false;

        try
        {
            con = conn.getConnection();
            con.setAutoCommit(false);

            for (int i=0; i<levels.size(); i++)
            {
                stat = con.prepareStatement(sql);
                stat.setString(1, (String) this.permissions.elementAt(i));
                stat.setString(2, this.moduleId);
                stat.setString(3, (String) this.levels.elementAt(i));
                stat.setString(4, this.roleId);

                int co = stat.executeUpdate();

                if (co == 0) {
                  ret = false;
                  break;
                }
            }

            if (ret == false) {
                con.rollback();
                messages.add("Insert Failed");
            }
            else {
                con.commit();
                messages.add("Record Inserted");
            }
        }
        catch(Exception ex)
        {
            ret = false;
            try
            {
            con.rollback();
            }
            catch(Exception e){}
            throw new SystemException("System Error: "+ex.getMessage());
        }
        finally
        {
          try {
            if (stat != null) {
              stat.close();
              stat = null;
            }
            if (con != null) {
              con.setAutoCommit(true);
              con.close();
              con = null;
            }
          }
          catch(Exception e){}
        }

        return ret;
    }


    public void getRoleData()
    {
        Connection con = null;
        PreparedStatement stat = null;
        ResultSet rs = null;
        messages.clear();

        if (this.getModuleId().trim().length() == 0)
        {
            messages.add("Module Id not Entered/Selected");
            return;
        }

        if (this.roleName.length() == 0) {
            messages.add("Role Name not Entered/Selected");
            return;
        }

        try
        {
            con = conn.getConnection();
            stat = con.prepareStatement("select ROLEID from TBLROLES where upper(ROLENAME) = '" + roleName.toUpperCase() + "'");

            try
            {
              if (tccsol.util.Utility.isLong(moduleId) == false)
                messages.add("Invalid Module Id");
              else {
                this.moduleName = conn.getValue(moduleId, "TBLACCESSMODULES", "MODULENAME", "MODULEID", 'S');
                if (moduleName.length() == 0)
                  messages.add("Invalid Module Id");
              }

              rs = stat.executeQuery();
              if (rs.next())
              {
                if (rs.getString(1) != null)
                  this.roleId = rs.getString(1).trim();
              }
              else
                messages.add("Invalid Role Name");
            }
            catch(Exception e) {
              messages.add("Invalid Module Id or Role Name");
            }

            if (messages.size() > 0)
                return;

            //create sql string
            String sql = "select ACCESSLEVEL, PERMISSION from TBLACCESSPERMISSIONS where ROLEID = ? and MODULEID = ?";
            stat = con.prepareStatement(sql);
            stat.setString(1, roleId);
            stat.setString(2, moduleId);
            rs = stat.executeQuery();

            if (rs.next())
            {
              mode = "U";    //Already permission has been set. Going to Update
              levels.clear();
              permissions.clear();
              String s = "";
              if (rs.getString(1) != null)
              {
                levels.add(rs.getString(1).trim());

                if (rs.getString(2) != null)
                  permissions.add(rs.getString(2).trim());
                else
                  permissions.add("-");
              }

              while (rs.next())
              {
                  if (rs.getString(1) != null)
                  {
                    levels.add(rs.getString(1).trim());

                    if (rs.getString(2) != null)
                      permissions.add(rs.getString(2).trim());
                    else
                      permissions.add("-");
                  }
              }

            }
            else {   //First time entry of permissions
              mode = "I";
              sql = "select ACCESSLEVEL from TBLMODULEACCESSLEVELS where MODULEID = ?";
              stat = con.prepareStatement(sql);
              stat.setString(1, moduleId);
              rs = stat.executeQuery();

              if (rs.next())
              {
                levels.clear();
                if (rs.getString(1) != null)
                  levels.add(rs.getString(1).trim());

                while (rs.next()) {
                  if (rs.getString(1) != null)
                    levels.add(rs.getString(1).trim());
                }
              }
              else {
                messages.add("Access Levels not added for module: " + moduleName + ". Contact System Administrator");
              }
            }
        }
        catch(Exception ex)
        {
           messages.add("Error retrieving Access Permission Information");
        }
        finally
        {
          try {
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

        if (levels.size() == 0 && messages.size() == 0)
            messages.add("Error could not retrieve Access Permission data");
    }

    public void closeDBConn()
    {
        conn.closeConnection();
    }


    //Getter Methods
    public Vector getLevels() {
      return levels;
    }
    public Vector getMessages() {
      return messages;
    }
    public String getModuleName() {
      return moduleName;
    }
    public String getModuleId() {
      return moduleId;
    }
    public String getRoleId() {
      return roleId;
    }
    public String getRoleName() {
      return roleName;
    }
    public String getSelMode() {
      return selMode;
    }
    public String getMode() {
      return mode;
    }
    public Vector getPermissions() {
      return permissions;
    }


   //Setter Methods
    public void setRoleName(String roleName) {
      this.roleName = roleName;
    }
    public void setRoleId(String roleId) {
      this.roleId = roleId;
    }
    public void setModuleId(String moduleId) {
      this.moduleId = moduleId;
    }
    public void setModuleName(String moduleName) {
      this.moduleName = moduleName;
    }
    public void setMessages(Vector messages) {
      this.messages = messages;
    }
    public void setLevels(Vector levels) {
      this.levels = levels;
    }
    public void setSelMode(String selMode) {
      this.selMode = selMode;
    }
    public void setMode(String mode) {
      this.mode = mode;
    }
    public void setPermissions(Vector permissions) {
      this.permissions = permissions;
    }
}