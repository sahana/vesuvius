/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.business;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;
import org.apache.commons.lang.builder.ToStringBuilder;

import java.io.Serializable;
import java.sql.Date;
import java.util.Set;


/**
 * Class DamageCase bean
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DamageCase implements Serializable {

    private Long caseId;
    private String reportedPersonId;
    private Date reportedDate;
    private Date damageDate;
    private String causeOfDamage;
    private String reporterNicPassportId;
    private String reporterName;
    private String reporterTelNo;
    private String reporterAddress;
    private String reporterLocation;
    private String authOfficerId;
    private String institutionId;
    private String referenceNumber;
    private Set damageReports;

    // Non persistence fields
    private String reporterProvince;
    private String reporterDistrict;
    private String reporterDivision;
    private String reporterGSDivision;
    private long uniqueId;
    private String customDataType;

    public DamageCase() {
        reportedPersonId = "";
        causeOfDamage = "";
        reporterNicPassportId = "";
        reporterName = "";
        reporterTelNo = "";
        reporterAddress = "";
        reporterLocation = "";
        authOfficerId = "";
        institutionId = "";
        referenceNumber = "";
        reportedDate = new java.sql.Date(new java.util.Date().getTime());
        damageDate = new java.sql.Date(new java.util.Date().getTime());
        uniqueId = System.currentTimeMillis();
    }

    public Long getCaseId() {
        return caseId;
    }

    public void setCaseId(Long caseId) {
        this.caseId = caseId;
    }

    public String getReportedPersonId() {
        return this.reportedPersonId;
    }

    public void setReportedPersonId(String reportedPersonId) {
        this.reportedPersonId = reportedPersonId;
    }

    public Date getReportedDate() {
        return this.reportedDate;
    }

    public void setReportedDate(Date reportedDate) {
        this.reportedDate = reportedDate;
    }

    public Date getDamageDate() {
        return this.damageDate;
    }

    public void setDamageDate(Date damageDate) {
        this.damageDate = damageDate;
    }

    public String getCauseOfDamage() {
        return this.causeOfDamage;
    }

    public void setCauseOfDamage(String causeOfDamage) {
        this.causeOfDamage = causeOfDamage;
    }

    public String getReporterNicPassportId() {
        return this.reporterNicPassportId;
    }

    public void setReporterNicPassportId(String reporterNicPassportId) {
        this.reporterNicPassportId = reporterNicPassportId;
    }

    public String getReporterName() {
        return this.reporterName;
    }

    public void setReporterName(String reporterName) {
        this.reporterName = reporterName;
    }

    public String getReporterTelNo() {
        return this.reporterTelNo;
    }

    public void setReporterTelNo(String reporterTelNo) {
        this.reporterTelNo = reporterTelNo;
    }

    public String getReporterAddress() {
        return this.reporterAddress;
    }

    public void setReporterAddress(String reporterAddress) {
        this.reporterAddress = reporterAddress;
    }

    public String getReporterLocation() {
        return this.reporterLocation;
    }

    public void setReporterLocation(String reporterLocation) {
        this.reporterLocation = reporterLocation;
    }

    public String getAuthOfficerId() {
        return this.authOfficerId;
    }

    public void setAuthOfficerId(String authOfficerId) {
        this.authOfficerId = authOfficerId;
    }

    public String getInstitutionId() {
        return this.institutionId;
    }

    public void setInstitutionId(String institutionId) {
        this.institutionId = institutionId;
    }

    public String getReferenceNumber() {
        return this.referenceNumber;
    }

    public void setReferenceNumber(String referenceNumber) {
        this.referenceNumber = referenceNumber;
    }


    public Set getDamageReports() {
        return damageReports;
    }

    public void setDamageReports(Set damageReports) {
        this.damageReports = damageReports;
    }


    //******************* Non persistence fields ***********************//

    public String getReporterProvince() {
        return this.reporterProvince;
    }

    public void setReporterProvince(String reporterProvince) {
        this.reporterProvince = reporterProvince;
    }

    public String getReporterGSDivision() {
        return this.reporterGSDivision;
    }

    public void setReporterGSDivision(String reporterGSDivision) {
        this.reporterGSDivision = reporterGSDivision;
    }

    public String getReporterDistrict() {
        return this.reporterDistrict;
    }

    public void setReporterDistrict(String reporterDistrict) {
        this.reporterDistrict = reporterDistrict;
    }

    public String getReporterDivision() {
        return this.reporterDivision;
    }

    public void setReporterDivision(String reporterDivision) {
        this.reporterDivision = reporterDivision;
    }

    public String getCustomDataType() {
        return customDataType;
    }

    public void setCustomDataType(String customDataType) {
        this.customDataType = customDataType;
    }

    public String toString() {
        return new ToStringBuilder(this)
                .append("id", uniqueId)
                .toString();
    }

    public boolean equals(Object other) {
        if (!(other instanceof DamageCase)) return false;
        DamageCase castOther = (DamageCase) other;
        return new EqualsBuilder()
                .append(this.uniqueId, castOther.uniqueId)
                .isEquals();
    }

    public int hashCode() {
        return new HashCodeBuilder()
                .append(uniqueId)
                .toHashCode();
    }

}

