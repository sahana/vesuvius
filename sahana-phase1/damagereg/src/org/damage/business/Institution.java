/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.business;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;
import org.apache.commons.lang.builder.ToStringBuilder;

/**
 * Class Institution bean
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class Institution {
    private Long institutionCode;
    private String institutionName;

    public Institution() {
    }

    public Long getInstitutionCode() {
        return institutionCode;
    }

    public void setInstitutionCode(Long institutionCode) {
        this.institutionCode = institutionCode;
    }

    public String getInstitutionName() {
        return institutionName;
    }

    public void setInstitutionName(String institutionName) {
        this.institutionName = institutionName;
    }


    public String toString() {
        return new ToStringBuilder(this)
                .append("id", getInstitutionCode())
                .toString();
    }

    public boolean equals(Object other) {
        if (!(other instanceof Institution)) return false;
        Institution castOther = (Institution) other;
        return new EqualsBuilder()
                .append(this.getInstitutionCode(), castOther.getInstitutionCode())
                .isEquals();
    }

    public int hashCode() {
        return new HashCodeBuilder()
                .append(getInstitutionCode())
                .toHashCode();
    }

}
