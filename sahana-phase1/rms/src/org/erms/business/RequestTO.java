package org.erms.business;

import java.sql.Date;
import java.util.Collection;
import java.util.Vector;


public class RequestTO {
    private Collection requestDetails = new Vector();
    private String requestID="";
    private String orgCode="";
    private String user="";
    private String callerName="";
    private Date createDate = new java.sql.Date(new java.util.Date().getTime());
    private Date requestedDate =  new java.sql.Date(new java.util.Date().getTime());;
    private String callerAddress="";
    private String callerContactNumber="";
    private String description="";
    private String siteType="";
    private String siteDistrict="";
    private String siteArea="";
    private String siteName="";
    private String comment="";
    private String orgName;
    private String orgContact;


    public String getComment() {
        return comment;
    }

    public String getOrgName() {
        return orgName;
    }

    public void setOrgName(String orgName) {
        this.orgName = orgName;
    }

    public String getOrgContact() {
        return orgContact;
    }

    public void setOrgContact(String orgContact) {
        this.orgContact = orgContact;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    public RequestTO() {
    }

    public Collection getRequestDetails() {
        return requestDetails;
    }

    public void setRequestDetails(Collection requestDetails) {
        this.requestDetails = requestDetails;
    }

    public void addRequestDetails(RequestDetailTO requestDetailTO) {
        if (requestDetails == null) {
            requestDetails = new Vector();
        }
        requestDetails.add(requestDetailTO);
    }

    public String getRequestID() {
        return requestID;
    }

    public void setRequestID(String requestID) {
        this.requestID = requestID;
    }

    public String getOrgCode() {
        return orgCode;
    }

    public void setOrgCode(String orgCode) {
        this.orgCode = orgCode;
    }

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }


    public Date getCreateDate() {
        return createDate;
    }

    public void setCreateDate(Date createDate) {
        this.createDate = createDate;
    }

    public String getCallerName() {
        return callerName;
    }

    public void setCallerName(String callerName) {
        this.callerName = callerName;
    }

    public String getCallerAddress() {
        return callerAddress;
    }

    public void setCallerAddress(String callerAddress) {
        this.callerAddress = callerAddress;
    }

    public String getCallerContactNumber() {
        return callerContactNumber;
    }

    public void setCallerContactNumber(String callerContactNumber) {
        this.callerContactNumber = callerContactNumber;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
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

    public String getSiteArea() {
        return siteArea;
    }

    public void setSiteArea(String siteArea) {
        this.siteArea = siteArea;
    }

    public String getSiteName() {
        return siteName;
    }

    public void setSiteName(String siteName) {
        this.siteName = siteName;
    }

    public Date getRequestedDate() {
        return requestedDate;
    }

    public void setRequestedDate(Date requestedDate) {
        this.requestedDate = requestedDate;
    }


}
