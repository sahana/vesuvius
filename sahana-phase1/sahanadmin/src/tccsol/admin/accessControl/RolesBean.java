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

public class RolesBean
{
    private DBConnection conn;

    private String roleId = "";
    private String roleName = "";
    private String description = "";
    private String modeVal = "";

    private Vector messages;
    private Vector users;


    public RolesBean() throws SQLException
    {
        conn = new DBConnection();
        messages = new Vector();
        users = new Vector();
    }


    //To insert the data into the db table
    public boolean insert() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;
        messages.clear();

        //create sql string
        String sql = "insert into TBLROLES (ROLEID, ROLENAME, DESCRIPTION) "
          + "values (?, ?, ?)";
        try
        {
            this.roleId = conn.newIdGen("TBLROLES", "ROLEID");
            con = conn.getConnection();
            stat = con.prepareStatement(sql);
            stat.setString(1, this.roleId);
            stat.setString(2, this.roleName);
            stat.setString(3, this.description);

            int co=stat.executeUpdate();
            if (co == 0) {
                ret = false;
                messages.add("Insert Failed");
            }
            else
                messages.add("Record Inserted");
        }
        catch(Exception ex)
        {
            ret = false;
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
              con.close();
              con = null;
            }
          }
          catch(Exception e){}
        }

        return ret;
    }


    public void getRoleData(String rname)
    {
        Connection con = null;
        PreparedStatement stat = null;
        ResultSet rs = null;
        messages.clear();

        rname = rname.trim();

        if (rname.length() == 0) {
            messages.add("Role Name not Entered/Selected");
            return;
        }

        //create sql string
        String sql = "select ROLEID, DESCRIPTION from TBLROLES where upper(ROLENAME) = ?";
        try
        {
            con = conn.getConnection();
            stat = con.prepareStatement(sql);
            stat.setString(1, rname.toUpperCase());
            rs = stat.executeQuery();

            if (rs.next())
            {
              if (rs.getString(1) != null)
                this.roleId = rs.getString(1);

              if (rs.getString(2) != null)
                this.description = rs.getString(2);
            }
            else
              messages.add("Invalid Role Name");
        }
        catch(Exception ex)
        {
           messages.add("Error retrieving User Role Information");
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
    }


    //To Update the Role Data
    public boolean update() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;

        messages.clear();

        //create sql string
        String sql = "update TBLROLES set ROLENAME = ?, DESCRIPTION = ? where ROLEID = ?";

        try
        {
            con = conn.getConnection();
            stat = con.prepareStatement(sql);
            stat.setString(1, this.roleName);
            stat.setString(2, this.description);
            stat.setString(3, this.roleId);

            int co=stat.executeUpdate();

            if (co == 0) {
              ret = false;
              messages.add("Update failed");
            }
            else
              messages.add("Record Udated");
        }
        catch(SQLException ex)
        {
            ret = false;
            throw new SystemException("System Error: " + ex.getMessage());
        }
        finally
        {
          try
          {
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



    //To Delete the Function Level data
    public boolean delete() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;

        messages.clear();

        String sql = "delete from TBLROLES where ROLEID = ?";

        try
        {
            if (conn.rowExists("select * from TBLUSERROLES where ROLEID = '" + this.roleId + "'") == true)
            {
                messages.add("Role has been assigned to users. Cannot delete");
                return false;
            }

            con = conn.getConnection();
            stat = con.prepareStatement(sql);

            stat.setInt(1, Integer.parseInt(this.roleId));

            int co=stat.executeUpdate();
            if (co == 0)
            {
                ret = false;
                messages.add("Delete failed");
            }
            else
                messages.add("Record Deleted");
        }
        catch(SQLException ex)
        {
            ret = false;
            throw new SystemException("System Error: " + ex.getMessage());
        }
        finally
        {
          try
          {
            if (stat != null) {
              stat.close();
              stat = null;
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


    //To Add users to a role
    public boolean addUsers() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;
        messages.clear();

        //create sql string
        String sql = "insert into TBLUSERROLES (ROLEID, USERNAME) values (?, ?)";
        try
        {
            if (users.size() > 0)
            {
              con = conn.getConnection();
              con.setAutoCommit(false);
              int co = 0;
              for (int i=0; i<users.size(); i++)
              {
                if(conn.exists(((String)users.elementAt(i)).toUpperCase(),"tbluserroles","upper(username)")) {
                  messages.add("Role already assigned for user :"+((String)users.elementAt(i)));;
                  break;
                 }
                stat = con.prepareStatement(sql);
                stat.setString(1, this.roleId);
                stat.setString(2, ((String)users.elementAt(i)).toUpperCase());
                co=stat.executeUpdate();
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
                messages.add(users.size() + " User(s) added to Role");
              }
           }
           else {
             messages.add("You ust select at least one user to be added to the role");
           }
        }
        catch(Exception ex)
        {
          try
          {
            ret = false;
            con.rollback();
            throw new SystemException("System Error: "+ex.getMessage());
          }
          catch(Exception e){}
        }
        finally
        {
          try {
            if (stat != null) {
              stat.close();
              stat = null;
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


    //To Remove users from a role
    public boolean removeUsers() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;
        messages.clear();

        //create sql string
        String sql = "delete from TBLUSERROLES where ROLEID=? and upper(USERNAME)=?";
        try
        {
            if (users.size() > 0)
            {
              con = conn.getConnection();
              con.setAutoCommit(false);
              int co = 0;
              for (int i=0; i<users.size(); i++)
              {
                stat = con.prepareStatement(sql);
                stat.setString(1, this.roleId);
                stat.setString(2, ((String)users.elementAt(i)).toUpperCase());
                co=stat.executeUpdate();
                if (co == 0) {
                  ret = false;
                  break;
                }
              }

              if (ret == false) {
                con.rollback();
                messages.add("Removal Failed");
              }
              else {
                con.commit();
                messages.add(users.size() + " Users(s) Removed from Role");
              }
           }
           else {
             messages.add("You ust select at least one user to be removed from the role");
           }
        }
        catch(Exception ex)
        {
          try
          {
            ret = false;
            con.rollback();
            throw new SystemException("System Error: "+ex.getMessage());
          }
          catch(Exception e){}
        }
        finally
        {
          try {
            if (stat != null) {
              stat.close();
              stat = null;
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


    public boolean getSelectedRoleId()
    {
        boolean ret = false;

        if (roleName.trim().length() == 0)
          messages.add("Role Name not entered/selected");
        else
        {
            try
            {
              roleId = conn.getValue(roleName.toUpperCase(), "TBLROLES", "ROLEID", "upper(ROLENAME)", 'S').trim();
            }
            catch(Exception e)
            {
              messages.add("Error validating Role: " + e.getMessage());
            }

            if (messages.size() == 0)
            {
              if (roleId.length() == 0)
                messages.add("Invalid Role Name");
              else
                ret = true;
            }
        }

        return  ret;
    }

    //To validate the input data
    public Vector validate(String nm)
    {
        messages.clear();

        if (nm.equals("U"))
        {
            if (this.roleId.length() == 0) {
              messages.add("Enter the Role Id");
            }
        }

        if (this.roleName.length()==0)
          messages.add("Role Name not entered");
        else if (Utility.lengthExceeded(this.roleName, 30) == true)
          messages.add("Role Name: Length exceeded (Maximum - 30)");
        else if (Utility.isIllegalChar(this.roleName) == true)
          messages.add("Illegal characters in Role Name");
        else
        {
          try
          {
            String sql = "select * from TBLROLES where upper(ROLENAME) = '" + this.roleName.toUpperCase() + "'";
            if (nm.equalsIgnoreCase("U"))
                sql = sql + " and ROLEID != '" + this.roleId + "'";

            if (conn.rowExists(sql) == true){
              messages.add("Role Name already exists");
            }
          }
          catch(Exception e)
          {
            messages.add("Error checking duplicate Role Name");
          }
        }

        if (this.description.length()==0)
          messages.add("Description not entered");
        else if (Utility.lengthExceeded(this.description, 100) == true)
          messages.add("Description: Length exceeded (Maximum - 100)");

        return messages;
    }


    public void closeDBConn()
    {
        conn.closeConnection();
    }


    //Getter Methods
    public String getDescription() {
      return description;
    }
    public Vector getMessages() {
      return messages;
    }
    public String getRoleId() {
      return roleId;
    }
    public String getRoleName() {
      return roleName;
    }
    public Vector getUsers() {
      return users;
    }
    public String getModeVal() {
      return modeVal;
    }


   //Setter Methods
    public void setRoleName(String roleName) {
      this.roleName = roleName;
    }
    public void setRoleId(String roleId) {
      this.roleId = roleId;
    }
    public void setMessages(Vector messages) {
      this.messages = messages;
    }
    public void setDescription(String description) {
      this.description = description;
    }
    public void setUsers(Vector users) {
      this.users = users;
    }
    public void setModeVal(String modeVal) {
      this.modeVal = modeVal;
    }
}
