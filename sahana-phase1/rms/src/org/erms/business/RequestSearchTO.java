package org.erms.business;

import java.sql.Date;


public class RequestSearchTO {
    private String requestDetId;
    private String priority;
    private String siteName;
    private String siteType;
    private String siteDistrict;
    private String category;
    private String item;
    private String siteArea;
    private String status;
    private int quantity;
    private String units;
    private Date date;


    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public RequestSearchTO() {
    }

    public String getRequestDetId() {
        return requestDetId;
    }

    public void setRequestDetId(String requestDetId) {
        this.requestDetId = requestDetId;
    }

    public String getPriority() {
        return priority;
    }

    public void setPriority(String priority) {
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

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quentity) {
        this.quantity = quentity;
    }

    public void setStatus(String staus) {
        this.status = staus;
    }

    public void setUnits(String units) {
        this.units = units;
    }

    public String getUnits() {
        return units;
    }

    public String getStatus() {
        return status;
    }

}
