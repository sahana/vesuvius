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

public class SetAccessPermissionBean
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
    private Vector modIds;
    private Vector modules;
    private Vector types;    //Stores whether insert or update

    public SetAccessPermissionBean() throws SQLException
    {
        conn = new DBConnection();
        messages = new Vector();
        levels = new Vector();
        permissions = new Vector();
        modIds = new Vector();
        modules = new Vector();
        types = new Vector();
    }

    //To insert the data into the db table
    public boolean insert() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;
        messages.clear();

        //create sql string
        String sql1 = "insert into TBLACCESSPERMISSIONS (PERMISSION, MODULEID, ACCESSLEVEL, ROLEID) values (?, ?, ?, ?)";
        String sql2 = "update TBLACCESSPERMISSIONS set PERMISSION = ? where MODULEID=? and ACCESSLEVEL=? and ROLEID=?";

        if (types.size() != modIds.size()) {
          messages.add("Error retrieving insert information");
          return false;
        }

        if (roleId.trim().length() == 0)
          messages.add("Role not selected/entered");

        if (permissions.size() == 0 || modIds.size() == 0 || levels.size() == 0)
          messages.add("Role or modules not selected/entered");
        else if (permissions.size() != modIds.size())
          messages.add("Error retrieving insert data");

        if (messages.size() > 0)
          return false;

        try
        {
            con = conn.getConnection();
            con.setAutoCommit(false);
            String md = "";
            Vector lv = null;
            for (int i=0; i<modIds.size(); i++)
            {
                md = (String) types.elementAt(i);
                if (md.equalsIgnoreCase("I"))
                  stat = con.prepareStatement(sql1);
                else if (md.equalsIgnoreCase("U"))
                  stat = con.prepareStatement(sql2);
                else {
                  ret = false;
                  break;
                }
                lv = Utility.splitString((String) this.permissions.elementAt(i), '|');
                if (lv != null)
                {
                    for (int j=0; j<lv.size(); j++)
                    {
                       if (String.valueOf(lv.elementAt(j)).equalsIgnoreCase("Y") || String.valueOf(lv.elementAt(j)).equalsIgnoreCase("N"))
                       {
                          stat.setString(1, (String) lv.elementAt(j));
                          stat.setString(2, (String) modIds.elementAt(i));
                          stat.setString(3, (String) levels.elementAt(j));
                          stat.setString(4, this.roleId);

                          int co = stat.executeUpdate();

                          if (co == 0) {
                            ret = false;
                            break;
                          }
                      }
                  }
               }
               else
                 ret = false;
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
        permissions.clear();
        levels.clear();
        modIds.clear();
        modules.clear();
        types.clear();

        if (this.moduleId.trim().length() == 0)
        {
            messages.add("Module Id(s) not Entered/Selected");
            return;
        }

        if (this.roleName.length() == 0) {
            messages.add("Role Name not Entered/Selected");
            return;
        }

        try
        {
            con = conn.getConnection();

            //Verify the module Ids
            try
            {
              modIds = Utility.splitString(moduleId.trim(), ',');
              stat = con.prepareStatement("select MODULENAME from TBLACCESSMODULES where MODULEID = ?");

              String iv = "";
              for (int i=0; i<modIds.size(); i++)
              {
                if (Utility.isLong((String)modIds.elementAt(i)) == true)
                {
                  stat.setString(1, (String)modIds.elementAt(i));
                  rs = stat.executeQuery();
                  if (rs.next())
                  {
                    if (rs.getString(1) != null)
                      modules.add(rs.getString(1).trim());
                  }
                  else
                    iv = iv + modIds.elementAt(i) + ", ";
                }
                else
                  iv = iv + modIds.elementAt(i) + ", ";
              }

              if (iv.length() > 0)
                  messages.add("Following Module Id(s) are Invalid: " + iv);
            }
            catch(Exception e) {
              messages.add("Error validating Module Ids");
            }
            finally
            {
              if (rs != null)
                rs.close();
              if (stat != null)
                stat.close();
            }

            //Get the role id
            if (messages.size() == 0)
            {
                try
                {
                  stat = con.prepareStatement("select ROLEID from TBLROLES where upper(ROLENAME) = '" + roleName.toUpperCase() + "'");
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
                  messages.add("Error verifying Role Name");
                }
                finally
                {
                  if (rs != null)
                    rs.close();
                  if (stat != null)
                    stat.close();
                }
            }


            //get the access levels
            if (messages.size() == 0)
            {
                try
                {
                  stat = con.prepareStatement("select * from TBLACCESSLEVELS");
                  rs = stat.executeQuery();
                  if (rs.next())
                  {
                    if (rs.getString(1) != null)
                      this.levels.add(rs.getString(1).trim());

                    while (rs.next()) {
                      this.levels.add(rs.getString(1).trim());
                    }
                  }
                  else
                    messages.add("Access Levels not initilised. Contact System Administrator");
                }
                catch(Exception e) {
                  messages.add("Error retrieving Access Levels");
                }
                finally
                {
                  if (rs != null)
                    rs.close();
                  if (stat != null)
                    stat.close();
                }
            }


            if (messages.size() == 0)
            {
              //Already there - modify
              String sql1 = "select PERMISSION from TBLACCESSPERMISSIONS where ROLEID=? "
                + "and MODULEID=? and ACCESSLEVEL=?";

              //Setting for the First time
              String sql2 = "select ACCESSLEVEL from TBLMODULEACCESSLEVELS where MODULEID=? and ACCESSLEVEL=?";

              String pstr = "";

              for (int i=0; i<this.modIds.size(); i++)
              {
                pstr = "";

                //already inserted, will be an update
                if (conn.rowExists("select * from TBLACCESSPERMISSIONS where ROLEID='"+this.roleId+"' and MODULEID='"+modIds.elementAt(i)+"'"))
                {
                    types.add("U");
                    for (int j=0; j<this.levels.size(); j++)
                    {
                        stat = con.prepareStatement(sql1);
                        stat.setString(1, roleId);
                        stat.setString(2, (String)this.modIds.elementAt(i));
                        stat.setString(3, (String)this.levels.elementAt(j));
                        rs = stat.executeQuery();

                        if (rs.next())
                        {
                          if (rs.getString(1).trim().length() > 0)
                            pstr = pstr + rs.getString(1).trim() + "|";
                          else
                            pstr = pstr + "N|";
                        }
                        else
                          pstr = pstr + "-|";

                        if (rs != null)
                          rs.close();
                        if (stat != null)
                          stat.close();
                    }
                }
                else  //Entering access permission for the very first time
                {
                    types.add("I");
                    for (int j=0; j<this.levels.size(); j++)
                    {
                        stat = con.prepareStatement(sql2);
                        stat.setString(1, (String)this.modIds.elementAt(i));
                        stat.setString(2, (String)this.levels.elementAt(j));
                        rs = stat.executeQuery();

                        if (rs.next())
                          pstr = pstr + "N|";
                        else
                          pstr = pstr + "-|";

                        rs.close();
                        stat.close();
                    }
                }
                this.permissions.add(pstr);
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

        if ((levels.size() == 0 || permissions.size() == 0) && messages.size() == 0){
            messages.add("Error: could not retrieve Access Permission data");
        }

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
    public Vector getModIds() {
      return modIds;
    }
    public Vector getModules() {
      return modules;
    }
    public Vector getTypes() {
      return types;
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
    public void setModIds(Vector modIds) {
      this.modIds = modIds;
    }
    public void setModules(Vector modules) {
      this.modules = modules;
    }
    public void setTypes(Vector types) {
      this.types = types;
    }
}