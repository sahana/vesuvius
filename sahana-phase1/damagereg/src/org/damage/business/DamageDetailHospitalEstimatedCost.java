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
 * Class DamageDetailHospitalEstimatedCost bean
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class DamageDetailHospitalEstimatedCost implements Serializable {

    private Long dmgDetailEstimatedCostId;
    private Long damageReportId;
    private Long propertyId;
    private String budgetDescription;
    private Double estimatedValue;

    public DamageDetailHospitalEstimatedCost() {
    }

    public Long getDmgDetailEstimatedCostId() {
        return dmgDetailEstimatedCostId;
    }

    public void setDmgDetailEstimatedCostId(Long dmgDetailEstimatedCostId) {
        this.dmgDetailEstimatedCostId = dmgDetailEstimatedCostId;
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

    public String getBudgetDescription() {
        return budgetDescription;
    }

    public void setBudgetDescription(String budgetDescription) {
        this.budgetDescription = budgetDescription;
    }

    public Double getEstimatedValue() {
        return estimatedValue;
    }

    public void setEstimatedValue(Double estimatedValue) {
        this.estimatedValue = estimatedValue;
    }

    public String toString() {
        return new ToStringBuilder(this)
                .append("id", getDmgDetailEstimatedCostId())
                .toString();
    }

    public boolean equals(Object other) {
        if (!(other instanceof DamageDetailHospitalEstimatedCost)) return false;
        DamageDetailHospitalEstimatedCost castOther = (DamageDetailHospitalEstimatedCost) other;
        return new EqualsBuilder()
                .append(this.getBudgetDescription(), castOther.getBudgetDescription())
                .isEquals();
    }

    public int hashCode() {
        return new HashCodeBuilder()
                .append(getBudgetDescription())
                .toHashCode();
    }


}
