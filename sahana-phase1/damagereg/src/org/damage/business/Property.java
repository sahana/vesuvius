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
 * Class Property bean
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class Property implements Serializable {
    private Long propertyId;
    private String propertyTypeCode;
    private String locationCode;
    private String ownerName;
    private String ownerPersonRef;
    private String ownerAddress;
    private String propertyAddress;
    private Boolean isInsured;
    private String insuranceCompany;
    private String insurencePolicy;
    private Double insurenceValue;

    // Non persistence fields
    private String locationProvince;
    private String locationDistrict;
    private String locationDivision;
    private String locationGSDivision;
    private long uniqueId;

    public Property() {
        propertyTypeCode = "";
        locationCode = "";
        ownerName = "";
        ownerPersonRef = "";
        ownerAddress = "";
        propertyAddress = "";
        insuranceCompany = "";
        insurencePolicy = "";
        locationProvince = "";
        locationDistrict = "";
        locationDivision = "";
        locationGSDivision = "";
        uniqueId = System.currentTimeMillis();
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

    public String getLocationCode() {
        return locationCode;
    }

    public void setLocationCode(String locationCode) {
        this.locationCode = locationCode;
    }

    public String getOwnerName() {
        return ownerName;
    }

    public void setOwnerName(String ownerName) {
        this.ownerName = ownerName;
    }

    public String getOwnerPersonRef() {
        return ownerPersonRef;
    }

    public void setOwnerPersonRef(String ownerPersonRef) {
        this.ownerPersonRef = ownerPersonRef;
    }

    public String getOwnerAddress() {
        return ownerAddress;
    }

    public void setOwnerAddress(String ownerAddress) {
        this.ownerAddress = ownerAddress;
    }

    public String getPropertyAddress() {
        return propertyAddress;
    }

    public void setPropertyAddress(String propertyAddress) {
        this.propertyAddress = propertyAddress;
    }

    public Boolean getIsInsured() {
        return isInsured;
    }

    public void setIsInsured(Boolean insured) {
        isInsured = insured;
    }

    public String getInsuranceCompany() {
        return insuranceCompany;
    }

    public void setInsuranceCompany(String insuranceCompany) {
        this.insuranceCompany = insuranceCompany;
    }

    public String getInsurencePolicy() {
        return insurencePolicy;
    }

    public void setInsurencePolicy(String insurencePolicy) {
        this.insurencePolicy = insurencePolicy;
    }

    public Double getInsurenceValue() {
        return insurenceValue;
    }

    public void setInsurenceValue(Double insurenceValue) {
        this.insurenceValue = insurenceValue;
    }


    public String getLocationProvince() {
        return locationProvince;
    }

    public void setLocationProvince(String locationProvince) {
        this.locationProvince = locationProvince;
    }

    public String getLocationDistrict() {
        return locationDistrict;
    }

    public void setLocationDistrict(String locationDistrict) {
        this.locationDistrict = locationDistrict;
    }

    public String getLocationDivision() {
        return locationDivision;
    }

    public void setLocationDivision(String locationDivision) {
        this.locationDivision = locationDivision;
    }

    public String getLocationGSDivision() {
        return locationGSDivision;
    }

    public void setLocationGSDivision(String locationGSDivision) {
        this.locationGSDivision = locationGSDivision;
    }

    public String toString() {
        return new ToStringBuilder(this)
                .append("id", uniqueId)
                .toString();
    }

    public boolean equals(Object other) {
        if (!(other instanceof Property)) return false;
        Property castOther = (Property) other;
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
