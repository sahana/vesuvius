/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.business;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;
import org.apache.commons.lang.builder.ToStringBuilder;

import java.io.Serializable;
import java.util.Iterator;
import java.util.Set;

/**
 * Class DamageReportDetailHospital bean
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DamageReportDetailHospital implements DamageReportDetailType, Serializable {

    private Long damageDetailHospitalId;
    private Long damageReportId;
    private Long propertyId;
    private String propertyTypeCode;
    private String summaryStatus;
    private String summaryFacility;
    private Set damageDetailHospitalEstimatedCosts;
    private String hospitalName;

    // Non persistence fields
    private long uniqueId;

    public DamageReportDetailHospital() {
        uniqueId = System.currentTimeMillis();
    }

    public Long getDamageDetailHospitalId() {
        return damageDetailHospitalId;
    }

    public void setDamageDetailHospitalId(Long damageDetailHospitalId) {
        this.damageDetailHospitalId = damageDetailHospitalId;
    }

    public Long getDamageReportId() {
        return damageReportId;
    }

    public void setDamageReportId(Long damageReportId) {
        this.damageReportId = damageReportId;
    }

    public Long getPropertyId() {
        return propertyId;
    }

    public void setPropertyId(Long propertyId) {
        this.propertyId = propertyId;
    }

    public String getPropertyTypeCode() {
        return propertyTypeCode;
    }

    public void setPropertyTypeCode(String propertyTypeCode) {
        this.propertyTypeCode = propertyTypeCode;
    }

    public String getSummaryStatus() {
        return summaryStatus;
    }

    public void setSummaryStatus(String summaryStatus) {
        this.summaryStatus = summaryStatus;
    }

    public String getSummaryFacility() {
        return summaryFacility;
    }

    public void setSummaryFacility(String summaryFacility) {
        this.summaryFacility = summaryFacility;
    }

    public String getHospitalName() {
        return hospitalName;
    }

    public void setHospitalName(String hospitalName) {
        this.hospitalName = hospitalName;
    }

    public Set getDamageDetailHospitalEstimatedCosts() {
        return damageDetailHospitalEstimatedCosts;
    }

    public void setDamageDetailHospitalEstimatedCosts(Set damageDetailHospitalEstimatedCosts) {
        this.damageDetailHospitalEstimatedCosts = damageDetailHospitalEstimatedCosts;
    }

    public String toString() {
        return new ToStringBuilder(this)
                .append("id", uniqueId)
                .toString();
    }

    public boolean equals(Object other) {
        if (!(other instanceof DamageReportDetailType)) return false;
        DamageReportDetailHospital castOther = (DamageReportDetailHospital) other;
        return new EqualsBuilder()
                .append(this.uniqueId, castOther.uniqueId)
                .isEquals();
    }

    public int hashCode() {
        return new HashCodeBuilder()
                .append(uniqueId)
                .toHashCode();
    }

    public double getEstimatedCost() {
        double totalCost = 0;
        for (Iterator iterator = damageDetailHospitalEstimatedCosts.iterator(); iterator.hasNext();) {
            DamageDetailHospitalEstimatedCost damageDetailHospitalEstimatedCost = (DamageDetailHospitalEstimatedCost) iterator.next();
            totalCost = totalCost + damageDetailHospitalEstimatedCost.getEstimatedValue().doubleValue();
        }
        return totalCost;
    }

}
