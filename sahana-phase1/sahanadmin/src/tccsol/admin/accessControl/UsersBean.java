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

    private String userName = "";
    private String oldUserName = "";
    private String pass1 = "";
    private String pass2 = "";
    private String role = "";
    private String oldRole = "";
    private String roleId = "";
    private int updCnt = 0;

    private Vector messages;
    private String orgId="";

    public UsersBean() throws SQLException
    {
        conn = new DBConnection();
        messages = new Vector();

    }


    //To validate the input data
    public Vector validate(String nm)
    {
        messages.clear();

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
            if(!("U".equals(nm) || "D".equals(nm))){
                try
                {
                    String sql = "select * from user where upper(USERNAME) = '" + this.userName.toUpperCase() + "'";

                    if (conn.rowExists(sql) == true){
                        messages.add("User Name already exists");
                    }
                }
                catch(Exception e)
                {

                    messages.add("Error checking duplicate User Name");
                }
            }
        }

        if (nm.equalsIgnoreCase("I") || (nm.equalsIgnoreCase("U") && this.pass2.length()!=0)){


            if (this.pass1.length() == 0) {
                messages.add("Password not entered");
            }
            else {
                if (Utility.lengthExceeded(this.pass1, 30) == true){
                    messages.add("Password: Length exceeded (Maximum - 30)");
                }
                if (!this.pass1.equals(this.pass2)){
                    messages.add("Password confirmation does not match. (Password is case sensitive)");
                }
            }
            if (this.roleId.length() == 0) {
                messages.add("Role not entered");
            }
            else {
                try {
                    String sql = "select * from TBLROLES where roleid="+this.roleId;

                    if (!conn.rowExists(sql) == true) {
                        messages.add("Role doesnt exists");
                    }
                }
                catch (Exception e) {

                    messages.add("Error checking Role Name");
                }



            }
            if (this.orgId.length() == 0) {
                messages.add("Organization not entered");
            }else{
                try {
                    String sql = "select orgcode from organization  where orgcode='"+this.orgId+"'";

                    if (!conn.rowExists(sql) == true) {
                        messages.add("Orgarnization doesnt exists");
                    }
                }
                catch (Exception e) {

                    messages.add("Error checking Orgarnization ");
                }

            }

        }




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
        String sql="";

        try
        {
            con = conn.getConnection();
            con.setAutoCommit(false);
            stat = con.prepareStatement("insert into user (USERNAME, PASSWORD,ORGCODE) values (?, ?, ?)");
            stat.setString(1, this.userName);
            //encrypted
            // stat.setString(2, tccsol.security.MD5toHexConverter.md5(pass1));
            stat.setString(2, pass1);
            stat.setString(3, this.orgId);

            int co=stat.executeUpdate();
            stat.close();
            sql = "insert into TBLUSERROLES (ROLEID, USERNAME) values (?, ?)";
            stat = con.prepareStatement(sql);
            stat.setString(1, this.roleId);
            stat.setString(2, this.userName);


            co = co+stat.executeUpdate();

            if(co>1)ret=true;

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
        /*    messages.clear();
        try
        {
        roleId = conn.getValue(nm, "TBLROLES", "ROLEID", "ROLENAME", 'S');
        if (roleId.length() == 0)
        messages.add("Invalid User Role");
        }
        catch (Exception e)
        {
        messages.add("Invalid User Role");
        }*/
    }

    public void getUserData(String md) throws SystemException
    {
        md = md.trim();
        Connection con = null;
        PreparedStatement stat = null;
        ResultSet rs = null;
        String sql = "";

        sql = "select roleid,orgcode from user u,TBLUSERROLES ur"
                +" where upper(u.username)=upper(ur.username) and u.username=?";
        try
        {
            con = conn.getConnection();
            stat = con.prepareStatement(sql);

            stat.setString(1, this.userName.toUpperCase());

            rs = stat.executeQuery();

            if (rs.next()) {

                this.oldUserName = this.userName.toUpperCase();
                this.roleId = rs.getString(1);
                this.orgId = rs.getString(2);

            }
            else {
                rs.close();
                stat.close();
                sql = "select orgcode from user "
                        + " where upper(username)=?";
                stat = con.prepareStatement(sql);
                stat.setString(1, this.userName.toUpperCase());
                rs = stat.executeQuery();
                if (rs.next()) {
                    this.orgId = rs.getString(1);
                    this.oldUserName = this.userName.toUpperCase();
                }
                else {
                    messages.add("Invalid User Name");
                }
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
    {/*
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
    */
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
            sql = "update user set ORGCODE = ?";

            if (this.pass1.length() > 0)
                sql = sql + ", PASSWORD = ?";


            stat = con.prepareStatement(sql + " where upper(username) = ?");
            stat.setString(1,this.orgId);


            if (this.pass1.length() > 0)
            {
                stat.setString(2, pass1);
                //stat.setString(2, tccsol.security.MD5toHexConverter.md5(pass1));
                stat.setString(3, this.userName.toUpperCase());
            }else{
                stat.setString(2, this.userName.toUpperCase());
            }


            int co=stat.executeUpdate();

            if (co>0)
            {
                sql = "delete from TBLUSERROLES where upper(USERNAME) = ?";
                stat = con.prepareStatement(sql);
                stat.setString(1, userName.toUpperCase());
                co = stat.executeUpdate();
                if (co>0)
                {
                    sql = "insert into TBLUSERROLES (ROLEID, USERNAME) values (?, ?)";
                    stat = con.prepareStatement(sql);
                    stat.setString(1,this.roleId);
                    stat.setString(2, this.userName);
                    co = stat.executeUpdate();
                    if (co == 0)
                        ret = false;

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

            stat = con.prepareStatement("delete from user where upper(USERNAME) = ?");
            stat.setString(1, this.userName.toUpperCase());
            int co=stat.executeUpdate();
            if (co == 0)
                ret = false;


            if (ret == true)
            {
                if (conn.rowExists("select * from TBLUSERROLES where upper(USERNAME) = '" + this.userName.toUpperCase() + "'"))
                {
                    stat = con.prepareStatement("delete from TBLUSERROLES where upper(USERNAME) = ?");
                    stat.setString(1, this.userName.toUpperCase());

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
    public String getUserName() {
        return userName;
    }
    public String getRoleId() {
        return roleId;
    }
    public String getOldUserName() {
        return oldUserName;
    }
    public String getOldRole() {
        return oldRole;
    }
    public int getUpdCnt() {
        return updCnt;
    }



    //Setter Methods
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
    public void setUserName(String userName) {
        this.userName = userName;
    }
    public void setRoleId(String roleId) {
        this.roleId = roleId;
    }
    public void setOldUserName(String oldUserName) {
        this.oldUserName = oldUserName;
    }
    public void setOldRole(String oldRole) {
        this.oldRole = oldRole;
    }
    public void setUpdCnt(int updCnt) {
        this.updCnt = updCnt;
    }
    public String getOrgId() {
        return orgId;
    }
    public void setOrgId(String orgId) {
        this.orgId = orgId;
    }
}
