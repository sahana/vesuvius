package org.erms.business;


public class RequestSearchTO {
    private int priority;
    private String siteName;
    private String siteType;
    private String siteDistrict;
    private String category;
    private String item;
    private String siteArea;
    private String status;
    private int quantity;
    private String units;

    public RequestSearchTO() {
    }

    public int getPriority() {
        return priority;
    }

    public void setPriority(int priority) {
        this.priority = priority;
    }

    public String getSiteName() {
        return siteName;
    }

    public void setSiteName(String siteName) {
        this.siteName = siteName;
    }

    public String getSiteType() {
        return siteType;
    }

    public void setSiteType(String siteType) {
        this.siteType = siteType;
    }

    public String getSiteDistrict() {
        return siteDistrict;
    }

    public void setSiteDistrict(String siteDistrict) {
        this.siteDistrict = siteDistrict;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getItem() {
        return item;
    }

    public void setItem(String item) {
        this.item = item;
    }

    public String getSiteArea() {
        return siteArea;
    }

    public void setSiteArea(String siteArea) {
        this.siteArea = siteArea;
    }

    public int getQuentity() {
        return quantity;
    }

    public void setQuentity(int quentity) {
        this.quantity = quentity;
    }

    public void setStaus(String staus) {
        this.status = staus;
    }

    public void setUnits(String units) {
        this.units = units;
    }

    public String getUnits() {
        return units;
    }

    public String getStaus() {
        return status;
    }

}
