package gov.lk.dms.report.common;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;

/**
 * 
 * @author  Thushera P. Kawdawatta.
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $
 *  
 */
public final class DBManager {

    private static DBManager sInstance = null;

    private static Map sConnections = new HashMap(10);
    
    private static DataSource sDataSource = null;
    
    public interface Property {
        String DATA_SOURCE = "datasource";
        
        String ENV_CONTEXT = "java:/comp/env";
    }

    private DBManager() {

    }

    public static final DBManager getInstance() {
        return sInstance == null ? sInstance = new DBManager() : sInstance;
    }

    public Connection getConnection() {
       
        Connection conn = null;
        
        try {
            conn = getDataSource().getConnection();
        } catch (SQLException e) {
            e.printStackTrace();
        } catch (NamingException e) {
            e.printStackTrace();
        }
        
        return conn;
    }
    
    public DataSource getDataSource() throws NamingException {
        
        if (sDataSource == null) {
            sDataSource = createDataSource();
        }
        
        return sDataSource;
    }
    
    private DataSource createDataSource() throws NamingException {
        Context initContext = new InitialContext();
        Context envContext  = (Context) initContext.lookup(Property.ENV_CONTEXT);
        System.out.println("EC created");
        String datasource = ReportEnvironment.getInstance().getProperty(Property.DATA_SOURCE);
        
        return (DataSource) envContext.lookup(datasource);
    }
}