package org.damage.business;

import java.util.ArrayList;

public class DamagedHouseTO {

    private int id;
    private String districtCode;
    private String division;
    private String gsn;
    private String owner;
    private double distanceFromSea;
    private String city;
    private String noAndStreet;
    private String currentAddress;
    private double floorArea;
    private int noOfStories;
    private String typeOfOwnership;
    private int noOfResidents;
    private String typeOfConstruction;
    private String propertyTaxNo;
    private double totalDamagedCost;
    private double landArea;
    private boolean relocate;
    private boolean insured;
    private String damageType;
    private String comments;

    private ArrayList  damagedHouseMoreInfoList;
    private ArrayList houseFacilityInfoList;

    public DamagedHouseTO(int id, String districtCode, String division, String gsn, String owner, double distanceFromSea, String city, String noAndStreet, String currentAddress, double floorArea, int noOfStories, String typeOfOwnership, int noOfResidents, String typeOfConstruction, String propertyTaxNo, double totalDamagedCost, double landArea, boolean relocate, boolean insured, String damageType, String comments, ArrayList damagedHouseMoreInfoList, ArrayList houseFacilityInfoList) {
        this.id = id;
        this.districtCode = districtCode;
        this.division = division;
        this.gsn = gsn;
        this.owner = owner;
        this.distanceFromSea = distanceFromSea;
        this.city = city;
        this.noAndStreet = noAndStreet;
        this.currentAddress = currentAddress;
        this.floorArea = floorArea;
        this.noOfStories = noOfStories;
        this.typeOfOwnership = typeOfOwnership;
        this.noOfResidents = noOfResidents;
        this.typeOfConstruction = typeOfConstruction;
        this.propertyTaxNo = propertyTaxNo;
        this.totalDamagedCost = totalDamagedCost;
        this.landArea = landArea;
        this.relocate = relocate;
        this.insured = insured;
        this.damageType = damageType;
        this.comments = comments;
        this.damagedHouseMoreInfoList = damagedHouseMoreInfoList;
        this.houseFacilityInfoList = houseFacilityInfoList;
    }

    public void addDamagedHouseMoreInfo(DamagedHouseMoreInfoTO dhmInfoTO){
       this.damagedHouseMoreInfoList.add(dhmInfoTO);
    }

    public void addHouseFacilityInfo(HouseFacilityInfoTO hfInfoTO){
        this.houseFacilityInfoList.add(hfInfoTO);
    }

    public ArrayList getDamagedHouseMoreInfoList() {
        return damagedHouseMoreInfoList;
    }

    public void setDamagedHouseMoreInfoList(ArrayList damagedHouseMoreInfoList) {
        this.damagedHouseMoreInfoList = damagedHouseMoreInfoList;
    }

    public ArrayList getHouseFacilityInfoList() {
        return houseFacilityInfoList;
    }

    public void setHouseFacilityInfoList(ArrayList houseFacilityInfoList) {
        this.houseFacilityInfoList = houseFacilityInfoList;
    }

    public DamagedHouseTO() {
    }



    public String getGsn() {
        return gsn;
    }

    public void setGsn(String gsn) {
        this.gsn = gsn;
    }



    public int getId() {
        return id;
    }

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

    public String getGSN() {
        return gsn;
    }

    public double getDistanceFromSea() {
        return distanceFromSea;
    }

    public void setDistanceFromSea(double distanceFromSea) {
        this.distanceFromSea = distanceFromSea;
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(String owner) {
        this.owner = owner;
    }

    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getNoAndStreet() {
        return noAndStreet;
    }

    public void setNoAndStreet(String noAndStreet) {
        this.noAndStreet = noAndStreet;
    }

    public String getCurrentAddress() {
        return currentAddress;
    }

    public void setCurrentAddress(String currentAddress) {
        this.currentAddress = currentAddress;
    }

    public double getFloorArea() {
        return floorArea;
    }

    public void setFloorArea(double floorArea) {
        this.floorArea = floorArea;
    }

    public int getNoOfStories() {
        return noOfStories;
    }

    public void setNoOfStories(int noOfStories) {
        this.noOfStories = noOfStories;
    }

    public String getTypeOfOwnership() {
        return typeOfOwnership;
    }

    public void setTypeOfOwnership(String typeOfOwnership) {
        this.typeOfOwnership = typeOfOwnership;
    }

    public int getNoOfResidents() {
        return noOfResidents;
    }

    public void setNoOfResidents(int noOfResidents) {
        this.noOfResidents = noOfResidents;
    }

    public String getTypeOfConstruction() {
        return typeOfConstruction;
    }

    public void setTypeOfConstruction(String typeOfConstruction) {
        this.typeOfConstruction = typeOfConstruction;
    }

    public String getPropertyTaxNo() {
        return propertyTaxNo;
    }

    public void setPropertyTaxNo(String propertyTaxNo) {
        this.propertyTaxNo = propertyTaxNo;
    }

    public double getTotalDamagedCost() {
        return totalDamagedCost;
    }

    public void setTotalDamagedCost(double totalDamagedCost) {
        this.totalDamagedCost = totalDamagedCost;
    }

    public double getLandArea() {
        return landArea;
    }

    public void setLandArea(double landArea) {
        this.landArea = landArea;
    }

    public boolean getRelocate() {
        return relocate;
    }

    public void setRelocate(boolean relocate) {
        this.relocate = relocate;
    }

    public boolean getInsured() {
        return insured;
    }

    public void setInsured(boolean insured) {
        this.insured = insured;
    }

    public String getDamageType() {
        return damageType;
    }

    public void setDamagedType(String damagedType) {
        this.damageType = damagedType;
    }

    public String getComments() {
        return comments;
    }

    public void setComments(String comments) {
        this.comments = comments;
    }
}
