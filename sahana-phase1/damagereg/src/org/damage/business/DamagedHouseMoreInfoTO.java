package org.damage.business;


public class DamagedHouseMoreInfoTO {

    private int houseID;
    private String damageInfo;

    public int getHouseID() {
        return houseID;
    }

    public void setHouseID(int houseID) {
        this.houseID = houseID;
    }

    public String getDamageInfo() {
        return damageInfo;
    }

    public void setDamageInfo(String damageInfo) {
        this.damageInfo = damageInfo;
    }

    public DamagedHouseMoreInfoTO(int houseID, String damageInfo) {
        this.houseID = houseID;
        this.damageInfo = damageInfo;
    }
}
