package tccsol.admin.accessControl;

import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.Connection;
import java.sql.SQLException;
import tccsol.sql.DBConnection;
import tccsol.hris.SystemException;
import tccsol.util.Utility;
import java.util.Vector;

public class UsersBean
{
    private DBConnection conn;

    private String empId = "";
    private String empNic = "";
    private String userName = "";
    private String oldUserName = "";
    private String pass1 = "";
    private String pass2 = "";
    private String role = "";
    private String oldRole = "";
    private String roleId = "";
    private int updCnt = 0;

    private Vector messages;
    private Vector roles;
    private Vector roleIds;
    private Vector selRoles;
    private Vector selRoleIds;

    public UsersBean() throws SQLException
    {
        conn = new DBConnection();
        messages = new Vector();
        roles = new Vector();
        roleIds = new Vector();
        selRoles = new Vector();
        selRoleIds = new Vector();
    }


    //To validate the input data
    public Vector validate(String nm)
    {
        messages.clear();

        if (empId.length() == 0) {
          messages.add("Enter the Employee Id");
        }

        if (messages.size() == 0 && nm.equalsIgnoreCase("I"))
        {
          try
          {
            String sql = "select * from TBLUSERS where upper(EMPNIC) = '" + this.empNic.toUpperCase() + "'";

            if (conn.rowExists(sql) == true)
              messages.add("A User Name has already been assigned to this employee. You may Delete it and create a new one or assign new 'Roles' to it");
          }
          catch(Exception e)
          {
            messages.add("Error checking duplicate Employee User Accounts");
          }
        }

        if (this.userName.length()==0){
          messages.add("User Name not entered");
        }
        else if (Utility.lengthExceeded(this.userName, 50) == true){
          messages.add("User Name: Length exceeded (Maximum - 50)");
        }
        else if (Utility.isIllegalChar(this.userName)) {
          messages.add("Invalid characters in User Name");
        }
        else
        {
          try
          {
            String sql = "select * from TBLUSERS where upper(USERNAME) = '" + this.userName.toUpperCase() + "'";
            if (nm.equalsIgnoreCase("U"))
              sql = sql + " and EMPNIC != '"+ this.empNic+"'";

            if (conn.rowExists(sql) == true){
              messages.add("User Name already exists");
            }
          }
          catch(Exception e)
          {
            messages.add("Error checking duplicate User Name");
          }
        }

        if (this.pass1.length()==0){
          if (nm.equalsIgnoreCase("I") || (nm.equalsIgnoreCase("U") && this.pass2.length()!=0))
            messages.add("Password not entered");
        }
        else if (Utility.lengthExceeded(this.pass1, 30) == true){
          messages.add("Password: Length exceeded (Maximum - 30)");
        }

        if (!this.pass1.equals(this.pass2)){
          messages.add("Password confirmation does not match. (Password is case sensitive)");
        }

        if (this.selRoleIds.size() == 0)
            messages.add("At least one 'Role' has to be assigned to each user");


        return messages;
    }



    //To insert the data into the db table
    public boolean insert() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;
        messages.clear();

        //create sql string
        String sql = "insert into TBLUSERROLES (ROLEID, USERNAME) values (?, ?)";

        try
        {
            con = conn.getConnection();
            con.setAutoCommit(false);
            stat = con.prepareStatement("insert into TBLUSERS (EMPNIC, USERNAME, PASSWORD) values (?, ?, ?)");
            stat.setString(1, this.empNic);
            stat.setString(2, this.userName);
            stat.setString(3, this.pass1);

            int co=stat.executeUpdate();

            if (co>0)
            {
               for (int i=0; i<selRoleIds.size(); i++)
               {
                  stat = con.prepareStatement(sql);
                  stat.setInt(1, Integer.parseInt((String) selRoleIds.elementAt(i)));
                  stat.setString(2, this.userName);
                  co = stat.executeUpdate();

                  if (co == 0){
                    ret = false;
                    break;
                  }
               }

            }
            else {
              ret = false;
            }

            if (ret == true) {
                con.commit();
                messages.add("Record Inserted");
            }else {
                con.rollback();
                messages.add("Insert failed");
            }
        }
        catch(SQLException ex)
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

    public void retrieveRoleId(String nm)
    {
        messages.clear();
        try
        {
            roleId = conn.getValue(nm, "TBLROLES", "ROLEID", "ROLENAME", 'S');
            if (roleId.length() == 0)
              messages.add("Invalid User Role");
        }
        catch (Exception e)
        {
            messages.add("Invalid User Role");
        }
    }

    public void getUserData(String md) throws SystemException
    {
        md = md.trim();
        Connection con = null;
        PreparedStatement stat = null;
        ResultSet rs = null;
        String sql = "";

        sql = "select u.EMPNIC, EMPID, EMPSTATUS from TBLUSERS u, "
         + "TBLPERSONALINFORMATION p where u.empNIc = p.empNIc and upper(userName) = ?";

        try
        {
          con = conn.getConnection();
          stat = con.prepareStatement(sql);

          stat.setString(1, this.userName.toUpperCase());

          rs = stat.executeQuery();

          if (rs.next()) {
              this.setEmpNic(rs.getString(1));
              this.setEmpId(rs.getString(2));

              String empStat = "";
              if (rs.getString(3) != null)
                empStat = rs.getString(3).trim();

              this.oldUserName = this.userName;

              if (empStat.equalsIgnoreCase("ACTIVE"))
              {
                sql = "select u.ROLEID, ROLENAME from TBLROLES r, TBLUSERROLES u where r.ROLEID = u.ROLEID and upper(USERNAME) = ?";
                stat = con.prepareStatement(sql);
                stat.setString(1, this.userName.toUpperCase());
                rs = stat.executeQuery();
                roles.clear();
                roleIds.clear();
                selRoles.clear();
                selRoleIds.clear();

                if (rs.next())
                {
                  if (rs.getString(1) != null && rs.getString(2) != null )
                  {
                    this.oldRole = rs.getString(2).trim();
                    if (md.equalsIgnoreCase("U"))
                    {
                      selRoles.add(rs.getString(2).trim());
                      selRoleIds.add(rs.getString(1).trim());
                    }
                    else if (md.equalsIgnoreCase("D"))
                    {
                      roles.add(rs.getString(2).trim());
                      roleIds.add(rs.getString(1).trim());
                    }
                  }

                  while (rs.next())
                  {
                      if (rs.getString(1) != null && rs.getString(2) != null )
                      {
                        this.oldRole = this.oldRole + ", " + rs.getString(2).trim();
                        if (md.equalsIgnoreCase("U"))
                        {
                          selRoles.add(rs.getString(2).trim());
                          selRoleIds.add(rs.getString(1).trim());
                        }
                        else if (md.equalsIgnoreCase("D"))
                        {
                          roles.add(rs.getString(2).trim());
                          roleIds.add(rs.getString(1).trim());
                        }
                      }
                  }
                }
                this.updCnt = 1;
             }
             else if (empStat.length() == 0)
                messages.add("User's Employee status has not been set. Cannot update");
             else
                messages.add("User's Employee status is not 'Active'. Cannot update");
          }
          else {
            messages.add("Invalid User Name");
          }
        }
        catch(Exception ex) {
          messages.add("Error retrieving User data");
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
            if (rs != null) {
              rs.close();
              rs = null;
            }
          }
          catch(Exception e){}
        }
    }


    public void getAllRoles(String md)
    {
        md = md.trim();
        DBConnection c = null;
        Connection con = null;
        PreparedStatement stat = null;
        ResultSet rs = null;
        String sql = "";
        messages.clear();

        if (md.equalsIgnoreCase("I"))
          sql = "select ROLEID, ROLENAME from TBLROLES";
        else if (md.equalsIgnoreCase("U"))
        {
          sql = "select distinct ROLEID, ROLENAME from TBLROLES where ROLEID "
            + "not in (select nvl(ROLEID, 0) from TBLUSERROLES where upper(USERNAME) = '"
            + userName.toUpperCase() + "')";
          this.updCnt = 0;
        }

        try
        {
          c = new DBConnection();
          con = c.getConnection();
          stat = con.prepareStatement(sql);
          rs = stat.executeQuery();

          if (rs.next())
          {
            roles.clear();
            roleIds.clear();

            if (rs.getString(1) != null && rs.getString(2) != null )
            {
              roles.add(rs.getString(2).trim());
              roleIds.add(rs.getString(1).trim());
            }

            while (rs.next()) {
                if (rs.getString(1) != null && rs.getString(2) != null )
                {
                  roles.add(rs.getString(2).trim());
                  roleIds.add(rs.getString(1).trim());
                }
            }
          }
          else {
            if (md.equalsIgnoreCase("I"))
              messages.add("There are no Roles in the system");
            else if (md.equalsIgnoreCase("U"))
              messages.add("All Roles in system have been assigned to the ueser");
          }
        }
        catch(Exception ex) {
            messages.add("Error retrieving User Role data");
        }
        finally
        {
          try {
            if (c != null) {
              c.closeConnection();
              c = null;
            }
            if (stat != null) {
              stat.close();
              stat = null;
            }
            if (con != null) {
              con.close();
              con = null;
            }
            if (rs != null) {
              rs.close();
              rs = null;
            }
          }
          catch(Exception e){}
        }
    }




    //To Update the User Data data
    public boolean update() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;
        messages.clear();
        String sql = "";

        try
        {
            con = conn.getConnection();
            con.setAutoCommit(false);
            sql = "update TBLUSERS set USERNAME = ?";

            if (this.pass1.length() > 0)
              sql = sql + ", PASSWORD = ?";

            stat = con.prepareStatement(sql + " where EMPNIC = ?");
            stat.setString(1, this.userName);

            if (this.pass1.length() > 0)
            {
              stat.setString(2, this.pass1);
              stat.setString(3, this.empNic);
            }
            else
              stat.setString(2, this.empNic);

            int co=stat.executeUpdate();

            if (co>0)
            {
              sql = "delete TBLUSERROLES where upper(USERNAME) = ?";
              stat = con.prepareStatement(sql);
              stat.setString(1, oldUserName.toUpperCase());
              co = stat.executeUpdate();

              if (co>0)
              {
                 sql = "insert into TBLUSERROLES (ROLEID, USERNAME) values (?, ?)";
                 for (int i=0; i<selRoleIds.size(); i++)
                 {
                    stat = con.prepareStatement(sql);
                    stat.setInt(1, Integer.parseInt((String) selRoleIds.elementAt(i)));
                    stat.setString(2, this.userName);
                    co = stat.executeUpdate();

                    if (co == 0){
                      ret = false;
                      break;
                    }
                 }
              }
              else {
                ret = false;
              }
            }
            else {
              ret = false;
            }

            if (ret == true) {
                con.commit();
                messages.add("Record Updated");
            }else {
                con.rollback();
                messages.add("Update failed");
            }
        }
        catch(SQLException ex)
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


    //To Delete the User or remove role data
    public boolean delete() throws SystemException
    {
        Connection con = null;
        PreparedStatement stat = null;
        boolean ret = true;
        messages.clear();

        try
        {
            con = conn.getConnection();
            con.setAutoCommit(false);

            stat = con.prepareStatement("delete TBLUSERS where upper(USERNAME) = ?");
            stat.setString(1, this.oldUserName.toUpperCase());
            int co=stat.executeUpdate();
            if (co == 0)
                ret = false;


            if (ret == true)
            {
              if (conn.rowExists("select * from TBLUSERROLES where upper(USERNAME) = '" + this.oldUserName.toUpperCase() + "'"))
              {
                stat = con.prepareStatement("delete TBLUSERROLES where upper(USERNAME) = ?");
                stat.setString(1, this.oldUserName.toUpperCase());

                co=stat.executeUpdate();
                if (co == 0)
                    ret = false;
              }
            }

            if (ret == true) {
                con.commit();
                messages.add("Record Deleted");
            }
            else {
                con.rollback();
                messages.add("Delete Failed");
            }
        }
        catch(SQLException ex)
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


    public void closeDBConn()
    {
        conn.closeConnection();
    }


    //Getter Methods
    public String getEmpId() {
      return empId;
    }
    public String getEmpNic() {
      return empNic;
    }
    public Vector getMessages() {
      return messages;
    }
    public String getPass1() {
      return pass1;
    }
    public String getPass2() {
      return pass2;
    }
    public String getRole() {
      return role;
    }
    public Vector getRoles() {
      return roles;
    }
    public String getUserName() {
      return userName;
    }
    public String getRoleId() {
      return roleId;
    }
    public Vector getRoleIds() {
      return roleIds;
    }
    public String getOldUserName() {
      return oldUserName;
    }
    public String getOldRole() {
      return oldRole;
    }
    public Vector getSelRoleIds() {
      return selRoleIds;
    }
    public Vector getSelRoles() {
      return selRoles;
    }
    public int getUpdCnt() {
      return updCnt;
    }



    //Setter Methods
    public void setEmpId(String empId) {
      this.empId = empId;
    }
    public void setEmpNic(String empNic) {
      this.empNic = empNic;
    }
    public void setMessages(Vector messages) {
      this.messages = messages;
    }
    public void setPass1(String pass1) {
      this.pass1 = pass1;
    }
    public void setPass2(String pass2) {
      this.pass2 = pass2;
    }
    public void setRole(String role) {
      this.role = role;
    }
    public void setRoles(Vector roles) {
      this.roles = roles;
    }
    public void setUserName(String userName) {
      this.userName = userName;
    }
    public void setRoleId(String roleId) {
      this.roleId = roleId;
    }
    public void setRoleIds(Vector roleIds) {
      this.roleIds = roleIds;
    }
    public void setOldUserName(String oldUserName) {
      this.oldUserName = oldUserName;
    }
    public void setOldRole(String oldRole) {
      this.oldRole = oldRole;
    }
    public void setSelRoleIds(Vector selRoleIds) {
      this.selRoleIds = selRoleIds;
    }
    public void setSelRoles(Vector selRoles) {
      this.selRoles = selRoles;
    }
    public void setUpdCnt(int updCnt) {
      this.updCnt = updCnt;
    }
}