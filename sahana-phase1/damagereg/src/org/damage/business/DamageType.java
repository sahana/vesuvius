/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.business;

import org.apache.commons.lang.builder.EqualsBuilder;
import org.apache.commons.lang.builder.HashCodeBuilder;
import org.apache.commons.lang.builder.ToStringBuilder;

/**
 * Class DamageType bean
 *
 * @author Viraj Samaranayaka
 * @version 1.0
 */
public class DamageType {

    private Long damageTypeCode;
    private String damageDescription;

    public DamageType() {
    }

    public Long getDamageTypeCode() {
        return damageTypeCode;
    }

    public void setDamageTypeCode(Long damageTypeCode) {
        this.damageTypeCode = damageTypeCode;
    }

    public String getDamageDescription() {
        return damageDescription;
    }

    public void setDamageDescription(String damageDescription) {
        this.damageDescription = damageDescription;
    }

    public String toString() {
        return new ToStringBuilder(this)
                .append("id", getDamageTypeCode())
                .toString();
    }

    public boolean equals(Object other) {
        if (!(other instanceof DamageType)) return false;
        DamageType castOther = (DamageType) other;
        return new EqualsBuilder()
                .append(this.getDamageTypeCode(), castOther.getDamageTypeCode())
                .isEquals();
    }

    public int hashCode() {
        return new HashCodeBuilder()
                .append(getDamageTypeCode())
                .toHashCode();
    }


}
