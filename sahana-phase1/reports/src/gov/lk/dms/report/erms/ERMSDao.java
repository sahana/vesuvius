package gov.lk.dms.report.erms;

import gov.lk.dms.report.dao.BaseDao;

/**
 * 
 * @author  Thushera P. Kawdawatta.
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $
 *  
 */
public final class ERMSDao extends BaseDao {

    private static ERMSDao sInstance;

    private ERMSDao() {

    }

    public static ERMSDao getInstance() {
        return sInstance == null ? sInstance = new ERMSDao() : sInstance;
    }
   
}