package gov.lk.dms.report.dao;

import gov.lk.dms.report.common.DBManager;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 * 
 * @author  Thushera P. Kawdawatta.
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $s
 *  
 */
public abstract class BaseDao {

    protected final Connection getConnection() {

        return DBManager.getInstance().getConnection();
    }

    protected final PreparedStatement getPrepareStatement(Connection conn, String sqlStaement) throws SQLException {

        //return getConnection().prepareStatement(sqlStaement);
        
        return conn.prepareStatement(sqlStaement);
    }

    protected ResultSet executeQueryX(String query) throws SQLException {
        PreparedStatement pStat = getPrepareStatement(getConnection(), query);
        
        ResultSet rs = pStat.executeQuery();
        
        pStat.close();
        
        return rs;
    }
    
    protected final void closeConnection(Connection conn) {
        try {
            conn.close();
            //System.out.println("Conn closed");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

}
