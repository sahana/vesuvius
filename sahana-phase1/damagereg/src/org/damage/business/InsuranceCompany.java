/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.business;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;
import org.apache.commons.lang.builder.ToStringBuilder;

/**
 * Class InsuranceCompany bean
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class InsuranceCompany {

    private Long InsuranceCompanyCode;
    private String InsuranceCompanyName;

    public InsuranceCompany() {
    }

    public Long getInsuranceCompanyCode() {
        return InsuranceCompanyCode;
    }

    public void setInsuranceCompanyCode(Long insuranceCompanyCode) {
        InsuranceCompanyCode = insuranceCompanyCode;
    }

    public String getInsuranceCompanyName() {
        return InsuranceCompanyName;
    }

    public void setInsuranceCompanyName(String insuranceCompanyName) {
        InsuranceCompanyName = insuranceCompanyName;
    }

    public String toString() {
        return new ToStringBuilder(this)
                .append("id", getInsuranceCompanyCode())
                .toString();
    }

    public boolean equals(Object other) {
        if (!(other instanceof InsuranceCompany)) return false;
        InsuranceCompany castOther = (InsuranceCompany) other;
        return new EqualsBuilder()
                .append(this.getInsuranceCompanyCode(), castOther.getInsuranceCompanyCode())
                .isEquals();
    }

    public int hashCode() {
        return new HashCodeBuilder()
                .append(getInsuranceCompanyCode())
                .toHashCode();
    }


}
