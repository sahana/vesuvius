package tccsol.util;

import java.sql.ResultSet;
import java.sql.PreparedStatement;
import java.sql.Connection;
import java.sql.SQLException;
import tccsol.sql.DBConnection;
import tccsol.hris.SystemException;
import java.util.Vector;

public class ListSingleBean
{
    private String type = "";
    private String url = "";
    private String sqlStat = "";
    private String id = "";
    private String name = "";
    private String col3 = "";
    private String col4 = "";
    private String col5 = "";
    private long num = 0;
    private int pageVal = 0;

    private Vector messages;
    private Vector titles;
    private Vector values;

    public ListSingleBean() throws SQLException
    {
        messages = new Vector();
        titles = new Vector();
        values = new Vector();
    }

    //Getter Methods
    public Vector getMessages() {
      return messages;
    }
    public long getNum() {
      return num;
    }
    public String getSqlStat() {
      return sqlStat;
    }
    public Vector getTitles() {
      return titles;
    }
    public String getType() {
      return type;
    }
    public String getUrl() {
      return url;
    }
    public Vector getValues() {
      return values;
    }
    public String getId() {
      return id;
    }
    public String getName() {
      return name;
    }
    public int getPageVal() {
      return pageVal;
    }
    public String getCol3() {
      return col3;
    }
    public String getCol4() {
      return col4;
    }
    public String getCol5() {
      return col5;
    }

    //Setter Methods
    public void setMessages(Vector messages) {
      this.messages = messages;
    }
    public void setNum(long num) {
      this.num = num;
    }
    public void setSqlStat(String sqlStat) {
      this.sqlStat = sqlStat;
    }
    public void setTitles(Vector titles) {
      this.titles = titles;
    }
    public void setType(String type) {
      this.type = type;
    }
    public void setUrl(String url) {
      this.url = url;
    }
    public void setValues(Vector values) {
      this.values = values;
    }
    public void setId(String id) {
      this.id = id;
    }
    public void setName(String name) {
      this.name = name;
    }
    public void setPageVal(int pageVal) {
      this.pageVal = pageVal;
    }
    public void setCol3(String col3) {
      this.col3 = col3;
    }
    public void setCol4(String col4) {
      this.col4 = col4;
    }
    public void setCol5(String col5) {
      this.col5 = col5;
    }


    //To get the available vales to be displayed
    public Vector retrieveList(Vector v, String sql, String type)
    {
        Vector msgs = new Vector();
        this.values.clear();


        PreparedStatement pstat = null;
        ResultSet res = null;
        Connection con = null;
        DBConnection cn = null;

        //IMPORTANT: Always retrieve the Id 1st and th name 2nd & then what
        //ever you want. SQL statement and columns list must be in same order!

        try
        {
            cn = new DBConnection();
            con = cn.getConnection();
            pstat = con.prepareStatement(sql);
            res = pstat.executeQuery();

            if (res.next())
            {
              String row = "";
              String cell = "";
              String cl = "";
              for (int i=1; i<=v.size(); i++) {
                cl = (String) v.elementAt(i-1);

                if (res.getString(i) != null) {
                  byte st = 0;
                  if (cl.indexOf("Date ") == 0 || cl.indexOf("date ") == 0 || cl.indexOf("DATE ") == 0)
                    st = 1;
                  else if (cl.indexOf(" Date") >=0 || cl.indexOf(" date") >=0 || cl.indexOf(" DATE") >=0)
                    st = 1;
                  else if (cl.indexOf(" Date ") >=0 || cl.indexOf(" date ") >=0 || cl.indexOf(" DATE ") >=0)
                    st = 1;

                  if (st == 1) {
                    cell = Utility.getDBDate(res.getDate(i));
                  }
                  else {
                    cell = res.getString(i).trim();
                  }
                }
                else
                  cell = "-";

                row = row + cell + "|";
              }
              values.add(row);
              row = "";

              while (res.next())
              {
                  for (int i=1; i<=v.size(); i++) {
                    cl = (String) v.elementAt(i-1);

                    if (res.getString(i) != null) {
                      byte st = 0;
                      if (cl.indexOf("Date ") == 0 || cl.indexOf("date ") == 0 || cl.indexOf("DATE ") == 0)
                        st = 1;
                      else if (cl.indexOf(" Date") >=0 || cl.indexOf(" date") >=0 || cl.indexOf(" DATE") >=0)
                        st = 1;
                      else if (cl.indexOf(" Date ") >=0 || cl.indexOf(" date ") >=0 || cl.indexOf(" DATE ") >=0)
                        st = 1;

                      if (st == 1) {
                        cell = Utility.getDBDate(res.getDate(i));
                      }
                      else {
                        if (res.getString(i).trim().length() == 0)
                          cell = "-";
                        else
                          cell = res.getString(i).trim();
                      }
                    }
                    else
                      cell = "-";

                    row = row + cell + "|";
                  }
                  values.add(row);
                  row = "";
            }
          }
          else {
                  msgs.add("There are no " + type + " records in the system. "
                      +"First enter the data into the system.");
          }
        }
        catch(Exception ex)
        {

          msgs.add("Error retrieving " + type + " data: " + ex);
        }
        finally
        {
            try {
                if (cn != null)
                    cn.closeConnection();
                if (con != null)
                    con.close();
                if (pstat != null)
                    pstat.close();
                if (res != null)
                    res.close();

                pstat = null;
                res = null;
                con = null;
                cn = null;
            }catch(SQLException ex){}
        }

        return msgs;
    }
}
