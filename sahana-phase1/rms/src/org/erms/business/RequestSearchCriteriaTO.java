package org.erms.business;

import java.sql.Date;


public class RequestSearchCriteriaTO {

    private String organization;
    private Date requestDateFrom;
    private Date requestDateTo;
    private String callerName;
    private String siteName;
    private String siteDistrict;
    private String siteArea;
    private String category;
    private String item;
    private String priority;
    private String status;

    public RequestSearchCriteriaTO() {
    }

    public String getCallerName() {
        return callerName;
    }

    public void setCallerName(String callerName) {
        this.callerName = callerName;
    }

    public String getCategory() {
        return category;
    }

    public String getItem() {
        return item;
    }

    public String getOrganization() {
        return organization;
    }

    public String getPriority() {
        return priority;
    }

    public Date getRequestDateFrom() {
        return requestDateFrom;
    }

    public Date getRequestDateTo() {
        return requestDateTo;
    }

    public String getSiteArea() {
        return siteArea;
    }

    public String getSiteDistrict() {
        return siteDistrict;
    }

    public String getSiteName() {
        return siteName;
    }

    public String getStatus() {
        return status;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public void setItem(String item) {
        this.item = item;
    }

    public void setOrganization(String organization) {
        this.organization = organization;
    }

    public void setPriority(String priority) {
        this.priority = priority;
    }

    public void setRequestDateFrom(Date requestDateFrom) {
        this.requestDateFrom = requestDateFrom;
    }

    public void setRequestDateTo(Date requestDateTo) {
        this.requestDateTo = requestDateTo;
    }

    public void setSiteArea(String siteArea) {
        this.siteArea = siteArea;
    }

    public void setSiteDistrict(String siteDistrict) {
        this.siteDistrict = siteDistrict;
    }

    public void setSiteName(String siteName) {
        this.siteName = siteName;
    }

    public void setStatus(String status) {
        this.status = status;
    }

}
