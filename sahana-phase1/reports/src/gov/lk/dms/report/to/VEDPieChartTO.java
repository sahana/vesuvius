package gov.lk.dms.report.to;

import java.util.HashMap;
import java.util.Map;

/**
 * 
 * @author  Thushera P. Kawdawatta.
 * @version $Revision: 1.1 $, $Date: 2005-01-07 08:53:16 $
 *  
 */
public class VEDPieChartTO extends VEDBaseTO {

    private Map mChartData = new HashMap();

    /**
     * @return Returns the chartData.
     */
    public Map getChartData() {
        return mChartData;
    }

    /**
     * @param chartData The chartData to set.
     */
    public void setChartData(Map chartData) {
        mChartData = chartData;
    }

    public void setValue(Object label, Object value) {
        if (mChartData == null) {
            mChartData = new HashMap();
        }

        mChartData.put(label, value);
    }
}