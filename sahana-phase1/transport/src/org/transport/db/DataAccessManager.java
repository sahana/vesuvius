/*
* Created on Dec 30, 2004
*
* To change the template for this generated file go to
* Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
*/
package org.transport.db;


import org.transport.business.*;
//import org.transport.util.LabelValue;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Collection;
import java.util.Vector;

import org.transport.business.ConsignmentTO;

/**
 * @author Administrator
 *         <p/>
 *         To change the template for this generated type comment go to
 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */
public class DataAccessManager {


    public User loginSuccess(String userName, String password) throws SQLException, Exception {
        Connection conn = DBConnection.createConnection();
        try {
            String sql = SQLGenerator.getSQLForLogin(userName);
            Statement s = conn.createStatement();
            ResultSet rs = s.executeQuery(sql);
            if (rs.next()) {
                String realpassword = rs.getString(DBConstants.TableColumns.PASSWORD);
                String organization = rs.getString(DBConstants.TableColumns.ORGANIZATION);

                User user = new User(userName, organization);
                if (realpassword.equals(password)) {
                    return user;
                }
            }
        } finally {
            conn.close();
        }

        return null;
    }

    public void addConsignment(ConsignmentTO consignmentObj)
    {

    }

    public Collection getAllCamps()
    {
        Collection camps = new Vector();
        KeyValueDTO camp1 = new KeyValueDTO();
        camp1.setDbTableCode("1");
        camp1.setDisplayValue("Indigolla");
        camps.add(camp1);

        KeyValueDTO camp2 = new KeyValueDTO();
        camp2.setDbTableCode("2");
        camp2.setDisplayValue("Nakkawita");
        camps.add(camp2);

        KeyValueDTO camp3 = new KeyValueDTO();
        camp3.setDbTableCode("3");
        camp3.setDisplayValue("Ulapona");
        camps.add(camp3);

        return camps;

    }

    public Collection getAllDivisions()
    {
        Collection divisions = new Vector();
        KeyValueDTO dtoDiv1 = new KeyValueDTO();
        dtoDiv1.setDbTableCode("1");
        dtoDiv1.setDisplayValue("kalutara");
        divisions.add(dtoDiv1);

        KeyValueDTO dtoDiv2 = new KeyValueDTO();
        dtoDiv2.setDbTableCode("2");
        dtoDiv2.setDisplayValue("panadura");
        divisions.add(dtoDiv2);

        KeyValueDTO dtoDiv3 = new KeyValueDTO();
        dtoDiv3.setDbTableCode("3");
        dtoDiv3.setDisplayValue("dehiwala");
        divisions.add(dtoDiv3);

        return divisions;
    }

    public Collection getAllUoM()
    {
        Collection UoM = new Vector();
        KeyValueDTO uom1 = new KeyValueDTO();
        uom1.setDbTableCode("1");
        uom1.setDisplayValue("kilo grams");
        UoM.add(uom1);

        KeyValueDTO uom2 = new KeyValueDTO();
        uom2.setDbTableCode("2");
        uom2.setDisplayValue("pounds");
        UoM.add(uom2);

        KeyValueDTO uom3 = new KeyValueDTO();
        uom3.setDbTableCode("3");
        uom3.setDisplayValue("feet");
        UoM.add(uom3);

        return UoM;

    }

    public Collection getAllItems()
    {
        Collection items = new Vector();

        KeyValueDTO item1 = new KeyValueDTO();
        item1.setDbTableCode("1");
        item1.setDisplayValue("dhal");
        items.add(item1);

        KeyValueDTO item2 = new KeyValueDTO();
        item2.setDbTableCode("2");
        item2.setDisplayValue("rice");
        items.add(item2);

        KeyValueDTO item3 = new KeyValueDTO();
        item3.setDbTableCode("3");
        item3.setDisplayValue("dried fish");
        items.add(item3);


        return items;  //To change body of created methods use File | Settings | File Templates.
    }
}
