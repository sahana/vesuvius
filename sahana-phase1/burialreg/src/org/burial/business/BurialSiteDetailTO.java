package org.burial.business;

/**
 * Created by IntelliJ IDEA.
 * User: hemapani
 * Date: Jan 5, 2005
 * Time: 3:27:26 PM
 * To change this template use File | Settings | File Templates.
 */
public class BurialSiteDetailTO {
    private int burialSiteCode;

    private String provinceCode;
    private String districtCode;
    private String divisionCode;
    private String area;

    private String sitedescription;
    private String burialdetail;
    private int bodyCountTotal;
    private int bodyCountMmen;

    private int bodyCountWomen;
    private int bodyCountChildren;

    private String gpsLattitude;
    private String gpsLongitude;

    private String authorityPersonName;
    private String authorityName;
    private String authorityPersonRank;
    private String authorityReference;

    public String getGpsLattitude() {
        return gpsLattitude;
    }

    public void setGpsLattitude(String gpsLattitude) {
        this.gpsLattitude = gpsLattitude;
    }

    public String getGpsLongitude() {
        return gpsLongitude;
    }

    public void setGpsLongitude(String gpsLongitude) {
        this.gpsLongitude = gpsLongitude;
    }

    public int getBurialSiteCode() {
        return burialSiteCode;
    }

    public void setBurialSiteCode(int burialSiteCode) {
        this.burialSiteCode = burialSiteCode;
    }

    public String getProvinceCode() {
        return provinceCode;
    }

    public void setProvinceCode(String provinceCode) {
        this.provinceCode = provinceCode;
    }

    public String getDistrictCode() {
        return districtCode;
    }

    public void setDistrictCode(String districtCode) {
        this.districtCode = districtCode;
    }

    public String getDivisionCode() {
        return divisionCode;
    }

    public void setDivisionCode(String divisionCode) {
        this.divisionCode = divisionCode;
    }

    public String getArea() {
        return area;
    }

    public void setArea(String area) {
        this.area = area;
    }

    public String getSitedescription() {
        return sitedescription;
    }

    public void setSitedescription(String sitedescription) {
        this.sitedescription = sitedescription;
    }

    public String getBurialdetail() {
        return burialdetail;
    }

    public void setBurialdetail(String burialdetail) {
        this.burialdetail = burialdetail;
    }

    public int getBodyCountTotal() {
        return bodyCountTotal;
    }

    public void setBodyCountTotal(int bodyCountTotal) {
        this.bodyCountTotal = bodyCountTotal;
    }

    public int getBodyCountMmen() {
        return bodyCountMmen;
    }

    public void setBodyCountMmen(int bodyCountMmen) {
        this.bodyCountMmen = bodyCountMmen;
    }

    public int getBodyCountWomen() {
        return bodyCountWomen;
    }

    public void setBodyCountWomen(int bodyCountWomen) {
        this.bodyCountWomen = bodyCountWomen;
    }

    public int getBodyCountChildren() {
        return bodyCountChildren;
    }

    public void setBodyCountChildren(int bodyCountChildren) {
        this.bodyCountChildren = bodyCountChildren;
    }


    public String getAuthorityPersonName() {
        return authorityPersonName;
    }

    public void setAuthorityPersonName(String authorityPersonName) {
        this.authorityPersonName = authorityPersonName;
    }

    public String getAuthorityName() {
        return authorityName;
    }

    public void setAuthorityName(String authorityName) {
        this.authorityName = authorityName;
    }

    public String getAuthorityPersonRank() {
        return authorityPersonRank;
    }

    public void setAuthorityPersonRank(String authorityPersonRank) {
        this.authorityPersonRank = authorityPersonRank;
    }

    public String getAuthorityReference() {
        return authorityReference;
    }

    public void setAuthorityReference(String authorityReference) {
        this.authorityReference = authorityReference;
    }
}
