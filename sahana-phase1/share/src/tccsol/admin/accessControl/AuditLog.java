package tccsol.admin.accessControl;

import tccsol.hris.SystemException;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.util.Date;
import java.text.SimpleDateFormat;

/**
 * Copyright 2001-2004 The Apache Software Foundation.
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * <p/>
 * Jan 13, 2005
 * 6:11:26 PM
 */
public class AuditLog {

    public AuditLog()
    {}

    public void logEntry(String user, String modId, String lvl)
    {
        try
        {
         tccsol.sql.DBConnection dcon = new tccsol.sql.DBConnection();
         Connection con = dcon.getConnection();
         PreparedStatement stat = con.prepareStatement("insert into TBLAUDITLOG (UserName,ModuleId,AccessLevel,"
            + "AccessDateTime) values (?, ?, ?, ?)");
         stat.setString(1, user);
         stat.setString(2, modId);
         stat.setString(3, lvl);
         stat.setString(4, formatDate());
         stat.executeUpdate();
         dcon.closeConnection();
        }
        catch(Exception e)
        {
             e.printStackTrace();
        }

    }

    private String formatDate() throws SystemException
    {
        String st = "";
        try
        {
            SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy HH:mm");
            st = formatter.format(new java.util.Date());
        }
        catch(Exception ex)
        {
             ex.printStackTrace();
        }
        return st;
    }             
}
