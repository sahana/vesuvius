package org.sahana.burialreg;

import junit.framework.TestCase;
import org.burial.db.DataAccessManager;
import org.burial.business.KeyValueDTO;
import org.burial.business.BurialSiteDetailTO;

import java.sql.SQLException;
import java.util.Collection;
import java.util.Iterator;

import sun.text.CompactShortArray;

/**
 * Created by IntelliJ IDEA.
 * User: hemapani
 * Date: Jan 5, 2005
 * Time: 5:45:39 PM
 * To change this template use File | Settings | File Templates.
 */
public class DataBaseTest extends TestCase{
    private DataAccessManager dam;
    public DataBaseTest(String s) {
        super(s);
        dam = DataAccessManager.getInstance();
    }

    public void testGetDistricts() throws SQLException {
        Iterator it= dam.getAllDistricts().iterator();
        while(it.hasNext()){
            KeyValueDTO kv = (KeyValueDTO)it.next();
            assertNotNull(kv.getDbTableCode());
            assertNotNull(kv.getDbTableCode());
        }
    }

    public void testDevisions() throws SQLException {
        Iterator it= dam.getAllDivisions().iterator();
        while(it.hasNext()){
            KeyValueDTO kv = (KeyValueDTO)it.next();
            assertNotNull(kv.getDbTableCode());
            assertNotNull(kv.getDbTableCode());
        }
    }

    public void testGetProvinces() throws SQLException {
        Iterator it= dam.getAllProvinces().iterator();
        while(it.hasNext()){
            KeyValueDTO kv = (KeyValueDTO)it.next();
            assertNotNull(kv.getDbTableCode());
            assertNotNull(kv.getDbTableCode());
        }
    }

    public void testAddSite() throws SQLException {
          BurialSiteDetailTO site =  new BurialSiteDetailTO();
          site.setArea("Area");
          site.setAuthorityName("AName");
          site.setAuthorityPersonName("APName");
          site.setAuthorityPersonRank("Rank");
          site.setAuthorityReference("referance");
          site.setBodyCountChildren(0);
          site.setBodyCountMmen(0);
          site.setBodyCountWomen(0);
          site.setBodyCountTotal(0);
          site.setBurialdetail("Detail");
          site.setDistrictCode("Galle");
          site.setDivisionCode("Ampara");
          site.setGpsLattitude(12);
          site.setGpsLongitude(34);
          site.setProvinceCode("westen");
          site.setSitedescription("des");
          dam.insertSite(site);

          Iterator it = dam.getAllSites().iterator();
          while(it.hasNext()){
              BurialSiteDetailTO site1 = (BurialSiteDetailTO)it.next();
              if(site1.getArea().equals(site.getArea())){
                  assertEquals(site1.getAuthorityReference(),site.getAuthorityReference());
                  break;
              }
              fail("site not found");
          }
    }


}
