package org.damage.business;


public class HouseFacilityInfoTO {
    private int houseID;
    private String facilityName;
    private String description;

    public HouseFacilityInfoTO(int houseID, String description, String facilityName) {
        this.houseID = houseID;
        this.description = description;
        this.facilityName = facilityName;
    }

    public int getHouseID() {
        return houseID;
    }

    public void setHouseID(int houseID) {
        this.houseID = houseID;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public String getFacilityName() {
        return facilityName;
    }

    public void setFacilityName(String facilityName) {
        this.facilityName = facilityName;
    }
}
