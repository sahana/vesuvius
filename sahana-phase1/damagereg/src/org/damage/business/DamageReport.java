/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.business;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;
import org.apache.commons.lang.builder.ToStringBuilder;

import java.io.Serializable;

/**
 * Class DamageReport bean
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DamageReport implements Serializable {

    private Long damageReportId;
    private Long caseId;
    private Long numberPersonsAffected;
    private String propertyTypeCode;
    private String contactPersonName;
    private String contactPersonId;
    private String damageTypeCode;
    private Double estimatedDamageValue;
    private Long propertyId;
    private Boolean isRelocate;
    private String damageReportTable;
    private DamageCase damageCase;
    private Property property;

    private DamageReportDetailType damageReportDetailObject;

    // Non persistence fields
    private long uniqueId;

    public DamageReport() {
        uniqueId = System.currentTimeMillis();
    }

    public DamageReport(long uid) {
        uniqueId = uid;
    }

    public Long getDamageReportId() {
        return damageReportId;
    }

    public void setDamageReportId(Long damageReportId) {
        this.damageReportId = damageReportId;
    }

    public Long getCaseId() {
        return caseId;
    }

    public void setCaseId(Long caseId) {
        this.caseId = caseId;
    }

    public Long getNumberPersonsAffected() {
        return numberPersonsAffected;
    }

    public void setNumberPersonsAffected(Long numberPersonsAffected) {
        this.numberPersonsAffected = numberPersonsAffected;
    }

    public String getPropertyTypeCode() {
        return propertyTypeCode;
    }

    public void setPropertyTypeCode(String propertyTypeCode) {
        this.propertyTypeCode = propertyTypeCode;
    }

    public String getContactPersonName() {
        return contactPersonName;
    }

    public void setContactPersonName(String contactPersonName) {
        this.contactPersonName = contactPersonName;
    }

    public String getContactPersonId() {
        return contactPersonId;
    }

    public void setContactPersonId(String contactPersonId) {
        this.contactPersonId = contactPersonId;
    }

    public String getDamageTypeCode() {
        return damageTypeCode;
    }

    public void setDamageTypeCode(String damageTypeCode) {
        this.damageTypeCode = damageTypeCode;
    }

    public Double getEstimatedDamageValue() {
        return estimatedDamageValue;
    }

    public void setEstimatedDamageValue(Double estimatedDamageValue) {
        this.estimatedDamageValue = estimatedDamageValue;
    }

    public Long getPropertyId() {
        return propertyId;
    }

    public void setPropertyId(Long propertyId) {
        this.propertyId = propertyId;
    }

    public Boolean getIsRelocate() {
        return isRelocate;
    }

    public void setIsRelocate(Boolean isRelocate) {
        this.isRelocate = isRelocate;
    }


    public DamageCase getDamageCase() {
        return damageCase;
    }

    public void setDamageCase(DamageCase damageCase) {
        this.damageCase = damageCase;
    }


    public Property getProperty() {
        return property;
    }

    public void setProperty(Property property) {
        this.property = property;
    }


    public DamageReportDetailType getDamageDetail() {
        return damageReportDetailObject;
    }

    public void setDamageDetail(DamageReportDetailType damageReportDetailObj) {
        this.damageReportDetailObject = damageReportDetailObj;
    }

    public String getDamageReportTable() {
        return damageReportTable;
    }

    public void setDamageReportTable(String damageReportTable) {
        this.damageReportTable = damageReportTable;
    }

    public String toString() {
        return new ToStringBuilder(this)
                .append("id", uniqueId)
                .toString();
    }

    public boolean equals(Object other) {
        if (!(other instanceof DamageReport)) return false;
        DamageReport castOther = (DamageReport) other;
        return new EqualsBuilder()
                .append(this.uniqueId, castOther.uniqueId)
                .isEquals();
    }

    public int hashCode() {
        return new HashCodeBuilder()
                .append(uniqueId)
                .toHashCode();
    }


    public long getUniqueId() {
        return uniqueId;
    }
}
