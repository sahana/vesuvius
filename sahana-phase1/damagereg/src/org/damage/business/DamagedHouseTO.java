package org.damage.business;
public class DamagedHouseTO {

    private String id;
    private String districtCode;
    private String division;
    private String gsn;
    private String owner;
    private String distanceFromSea;
    private String city;
    private String noAndStreet;
    private String currentAddress;
    private String floorArea;
    private String noOfStories;
    private String typeOfOwnership;
    private String noOfResidents;
    private String typeOfConstruction;
    private String propertyTaxNo;
    private String totalDamagedCost;
    private String landArea;
    private String relocate;
    private String insured;
    private String damageType;
    private String comments;

    public DamagedHouseTO(){
    }
    
    public DamagedHouseTO(String id, String districtCode, String division, String gsn, String owner, String distanceFromSea, String city, String noAndStreet, String currentAddress, String floorArea, String noOfStories, String typeOfOwnership, String noOfResidents, String typeOfConstruction, String propertyTaxNo, String totalDamagedCost, String landArea, String relocate, String insured,  String damagedType, String comments){
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
        this.damageType = damagedType;
        this.comments = comments;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
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

    public String getDistanceFromSea() {
        return distanceFromSea;
    }

    public void setDistanceFromSea(String distanceFromSea) {
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
