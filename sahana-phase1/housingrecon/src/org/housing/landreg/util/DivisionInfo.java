package org.housing.landreg.util;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: Jan 6, 2005
 * Time: 12:22:33 AM
 * To change this template use File | Settings | File Templates.
 */
public class DivisionInfo {
    private String divCode;
    private String districtName;
    private String provinceName;

    public DivisionInfo(String divCode, String districtName, String provinceName) {
        this.divCode = divCode;
        this.districtName = districtName;
        this.provinceName = provinceName;
    }

    public String getDivCode() {
        return divCode;
    }

    public void setDivCode(String divCode) {
        this.divCode = divCode;
    }

    public String getDistrictName() {
        return districtName;
    }

    public void setDistrictName(String districtName) {
        this.districtName = districtName;
    }

    public String getProvinceName() {
        return provinceName;
    }

    public void setProvinceName(String provinceName) {
        this.provinceName = provinceName;
    }
}
