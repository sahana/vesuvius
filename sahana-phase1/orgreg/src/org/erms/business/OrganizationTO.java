package org.erms.business;

/**
 * Copyright 2001-2004 The Apache Software Foundation.
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
public class OrganizationTO {
    private String orgCode;
    private String contactPerson;
    private String orgName;
    private String status;
    private String orgAddress;
    private String contactNumber;
    private String emailAddress;
    private String countryOfOrigin;
    private String facilitiesAvailable;
    private String workingAreas;
    private String comments;
    private String orgType;
    private String ngoType;

    public OrganizationTO() {
    }

    public OrganizationTO(String orgCode, String contactPerson, String orgName, String status, String orgAddress, String contactNumber, String emailAddress, String countryOfOrigin, String facilitiesAvailable, String workingAreas, String comments, String orgType, String ngoType) {
        this.orgCode = orgCode;
        this.contactPerson = contactPerson;
        this.orgName = orgName;
        this.status = status;
        this.orgAddress = orgAddress;
        this.contactNumber = contactNumber;
        this.emailAddress = emailAddress;
        this.countryOfOrigin = countryOfOrigin;
        this.facilitiesAvailable = facilitiesAvailable;
        this.workingAreas = workingAreas;
        this.comments = comments;
        this.orgType = orgType;
        this.ngoType = ngoType;
    }

    public String getOrgCode() {
        return orgCode;
    }

    public void setOrgCode(String orgCode) {
        this.orgCode = orgCode;
    }

    public String getContactPerson() {
        return contactPerson;
    }

    public void setContactPerson(String contactPerson) {
        this.contactPerson = contactPerson;
    }

    public String getOrgName() {
        return orgName;
    }

    public void setOrgName(String orgName) {
        this.orgName = orgName;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getOrgAddress() {
        return orgAddress;
    }

    public void setOrgAddress(String orgAddress) {
        this.orgAddress = orgAddress;
    }

    public String getContactNumber() {
        return contactNumber;
    }

    public void setContactNumber(String contactNumber) {
        this.contactNumber = contactNumber;
    }

    public String getEmailAddress() {
        return emailAddress;
    }

    public void setEmailAddress(String emailAddress) {
        this.emailAddress = emailAddress;
    }

    public String getCountryOfOrigin() {
        return countryOfOrigin;
    }

    public void setCountryOfOrigin(String countryOfOrigin) {
        this.countryOfOrigin = countryOfOrigin;
    }

    public String getFacilitiesAvailable() {
        if(facilitiesAvailable == null ){
            return "&nbsp;";
        }   else
            return facilitiesAvailable;
    }

    public void setFacilitiesAvailable(String facilitiesAvailable) {
        this.facilitiesAvailable = facilitiesAvailable;
    }

    public String getWorkingAreas() {
        if(workingAreas == null ){
            return "&nbsp;";
        } else
        return workingAreas;
    }

    public void setWorkingAreas(String workingAreas) {
        this.workingAreas = workingAreas;
    }

    public String getComments() {
        return comments;
    }

    public void setComments(String comments) {
        this.comments = comments;
    }

    public String getOrgType() {
        return orgType;
    }

    public void setOrgType(String orgType) {
        this.orgType = orgType;
    }

    public String getNgoType() {
        return ngoType;
    }

    public void setNgoType(String ngoType) {
        this.ngoType = ngoType;
    }

}
