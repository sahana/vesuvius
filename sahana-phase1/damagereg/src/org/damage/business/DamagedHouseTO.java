package org.damage.business;

import java.util.ArrayList;

public class DamagedHouseTO {

    private int id;
    private String districtCode;
    private String division;
    private String gsn;
    private String owner;
    private String address;
    private String distanceFromSea;
    private String floorArea;
    private String noOfStories;
    private String typeOfOwnership;
    private String noOfResidents;
    private String typeOfConstruction;
    private String propertyTaxNo;
    private String estimatedValue;
    private String totalDamagedCost;
    private String landArea;
    private String relocate;
    private String insured;
    private String damageType;
    private String comments;

    private ArrayList  damagedHouseMoreInfoList= new ArrayList();
    private ArrayList houseFacilityInfoList=new ArrayList();

   public DamagedHouseTO(){}

    public void addDamagedHouseMoreInfo(DamagedHouseMoreInfoTO dhmInfoTO){
       this.damagedHouseMoreInfoList.add(dhmInfoTO);
    }

    public void addHouseFacilityInfo(HouseFacilityInfoTO hfInfoTO){
        this.houseFacilityInfoList.add(hfInfoTO);
    }

    public DamagedHouseTO(int id, String districtCode, String division, String gsn, String owner, String address, String distanceFromSea, String floorArea, String noOfStories, String typeOfOwnership, String noOfResidents, String typeOfConstruction, String propertyTaxNo, String estimatedValue, String totalDamagedCost, String landArea, String relocate, String insured, String damageType, String comments, ArrayList damagedHouseMoreInfoList, ArrayList houseFacilityInfoList) {
        this.id = id;
        this.districtCode = districtCode;
        this.division = division;
        this.gsn = gsn;
        this.owner = owner;
        this.address = address;
        this.distanceFromSea = distanceFromSea;
        this.floorArea = floorArea;
        this.noOfStories = noOfStories;
        this.typeOfOwnership = typeOfOwnership;
        this.noOfResidents = noOfResidents;
        this.typeOfConstruction = typeOfConstruction;
        this.propertyTaxNo = propertyTaxNo;
        this.estimatedValue = estimatedValue;
        this.totalDamagedCost = totalDamagedCost;
        this.landArea = landArea;
        this.relocate = relocate;
        this.insured = insured;
        this.damageType = damageType;
        this.comments = comments;
        this.damagedHouseMoreInfoList = damagedHouseMoreInfoList;
        this.houseFacilityInfoList = houseFacilityInfoList;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
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

    public void setGSN(String gsn) {
        this.gsn = gsn;
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(String owner) {
        this.owner = owner;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getDistanceFromSea() {
        return distanceFromSea;
    }

    public void setDistanceFromSea(String distanceFromSea) {
        this.distanceFromSea = distanceFromSea;
    }

    public String getFloorArea() {
        return floorArea;
    }

    public void setFloorArea(String floorArea) {
        this.floorArea = floorArea;
    }

    public String getNoOfStories() {
        return noOfStories;
    }

    public void setNoOfStories(String noOfStories) {
        this.noOfStories = noOfStories;
    }

    public String getTypeOfOwnership() {
        return typeOfOwnership;
    }

    public void setTypeOfOwnership(String typeOfOwnership) {
        this.typeOfOwnership = typeOfOwnership;
    }

    public String getNoOfResidents() {
        return noOfResidents;
    }

    public void setNoOfResidents(String noOfResidents) {
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

    public String getEstimatedValue() {
        return estimatedValue;
    }

    public void setEstimatedValue(String estimatedValue) {
        this.estimatedValue = estimatedValue;
    }

    public String getTotalDamagedCost() {
        return totalDamagedCost;
    }

    public void setTotalDamagedCost(String totalDamagedCost) {
        this.totalDamagedCost = totalDamagedCost;
    }

    public String getLandArea() {
        return landArea;
    }

    public void setLandArea(String landArea) {
        this.landArea = landArea;
    }

    public String getRelocate() {
        return relocate;
    }

    public void setRelocate(String relocate) {
        this.relocate = relocate;
    }

    public String getInsured() {
        return insured;
    }

    public void setInsured(String insured) {
        this.insured = insured;
    }

    public String getDamageType() {
        return damageType;
    }

    public void setDamageType(String damageType) {
        this.damageType = damageType;
    }

    public String getComments() {
        return comments;
    }

    public void setComments(String comments) {
        this.comments = comments;
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

}
