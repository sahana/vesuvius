package tccsol.admin.accessControl;

import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.Connection;
import java.sql.SQLException;
import tccsol.sql.DBConnection;
import tccsol.hris.SystemException;
import tccsol.util.Utility;
import java.util.Vector;


public class ChangePasswordBean
{
    private DBConnection conn;

    private String userName = "";
    private String oldPass = "";
    private String pass1 = "";
    private String pass2 = "";

    private Vector messages;

    public ChangePasswordBean() throws SQLException
    {
        conn = new DBConnection();
        messages = new Vector();
    }


    //To validate the input data
    public Vector validate()
    {
        //remove any previous messages
        messages.clear();

        if (this.oldPass.length()==0)
            messages.add("Current Password not entered");
        else {
            try {
              //encrypted//if (!conn.rowExists("select * from USER where upper(USERNAME)='"+userName.toUpperCase()+"' and PASSWORD='"+tccsol.security.MD5toHexConverter.md5(this.oldPass)+"'"))
              if (!conn.rowExists("select * from USER where upper(USERNAME)='"+userName.toUpperCase()+"' and PASSWORD='"+this.oldPass+"'"));
              messages.add("Current Password is Invalid");
            }
            catch(Exception e) {
              messages.add("Error checking current password");
            }
        }

        if (this.pass1.length()==0){
            messages.add("Password not entered");
        }
        else if (Utility.lengthExceeded(this.pass1, 30) == true){
          messages.add("Password: Length exceeded (Maximum - 30)");
        }

        if (!this.pass1.equals(this.pass2)){
          messages.add("Password confirmation does not match. (Password is case sensitive)");
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
        String sql = "update USER set PASSWORD=? where upper(USERNAME)=?";

        try
        {
            con = conn.getConnection();
            stat = con.prepareStatement(sql);
           //encryption
            // stat.setString(1, tccsol.security.MD5toHexConverter.md5(pass1));
            stat.setString(1, pass1);
            stat.setString(2, this.userName.toUpperCase());

            int co=stat.executeUpdate();

            if (co>0) {
                ret = true;
                messages.add("Password has been changed successfully");
            }else {
                ret = false;
                messages.add("Password change Failed");
            }
        }
        catch(SQLException ex)
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
    public String getUserName() {
      return userName;
    }
    public String getOldPass() {
      return oldPass;
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
    public void setUserName(String userName) {
      this.userName = userName;
    }
    public void setOldPass(String oldPass) {
      this.oldPass = oldPass;
    }
}
