package org.damage.business;


public class SearchHouseTO {
    private String districtCode;
    private String division;
    private String gsn;
    private String owner;

    public String getDistrictCode() {
        return districtCode;
    }

    public void setDistrictCode(String districtCode) {
        this.districtCode = districtCode;
    }

    public String getDivision() {
        return division;
    }

    public void setDivision(String division) {
        this.division = division;
    }

    public String getGsn() {
        return gsn;
    }

    public void setGsn(String gsn) {
        this.gsn = gsn;
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(String owner) {
        this.owner = owner;
    }

    public String getDistanceFromSea() {
        return distanceFromSea;
    }

    public void setDistanceFromSea(String distanceFromSea) {
        this.distanceFromSea = distanceFromSea;
    }

    public String getDamageType() {
        return damageType;
    }

    public void setDamageType(String damageType) {
        this.damageType = damageType;
    }

 private String distanceFromSea;
    private String damageType;
}
