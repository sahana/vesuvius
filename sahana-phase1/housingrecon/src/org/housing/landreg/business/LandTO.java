package org.housing.landreg.business;

import java.util.List;
import java.util.LinkedList;

/**
 * Created by IntelliJ IDEA.
 * User: nithyakala
 * Date: Jan 18, 2005
 * Time: 4:34:42 PM
 * To change this template use File | Settings | File Templates.
 */
public class LandTO {

        private String landId;
        private String landName;
        private String divisionId;
        private String description;
        private String measurementTypeId;
        private String area;
        private String GPS1;
        private String GPS2;
        private String GPS3;
        private String GPS4;
        private String termId;
        private String ownedById;
        private String ownedByComment;
        private String districtId;
        private String provinceCode;

        private String provinceName;
        private String districtName;
        private String divisionName;
        private String measurementTypeName;
        private String termName;
        private String ownedByName;


        /*public LandTO (String landId,String landName, String divisionId, String description, String areaId) {
            this.landId =landId;
            this.landName = landName;
            this.divisionId = divisionId;
            this.description =description;
            this.areaId =areaId;

        } */

     public String getprovinceName() {
            return provinceName;
        }

        public void setProvinceName(String provinceName) {
            this.provinceName = provinceName;
        }

     public String getDistrictName() {
            return districtName;
        }

        public void setDistrictName(String districtName) {
            this.districtName = districtName;
        }
     public String getdivisionName() {
            return divisionName;
        }

        public void setDivisionName(String divisionName) {
            this.divisionName = divisionName;
        }
        public String getMeasurementTypeName() {
            return measurementTypeName;
        }

        public void setMeasurementTypeName(String measurementTypeName) {
            this.measurementTypeName = measurementTypeName;
        }
         public String getTermName() {
            return termName;
        }

        public void setTermName(String termName) {
            this.termName = termName;
        }
        public String getOwnedByName() {
            return ownedByName;
        }

        public void setOwnedByName(String ownedByName) {
            this.ownedByName = ownedByName;
        }

        public String getLandId() {
            return landId;
        }

        public void setLandId(String landId) {
            this.landId = landId;
        }

        public String getLandName() {
            return landName;
        }

        public void setLandName(String landName) {
            this.landName = landName;
        }

        public String getDivisionId(){
            return divisionId;
        }

        public void setDivisionId(String divisionId){
            this.divisionId = divisionId;
        }

        public String getDescription(){
             return description;
        }

        public void setDescription(String description){
            this.description =description;
        }

        public String getMeasurementTypeId(){
            return measurementTypeId;
        }

        public void setMeasurementTypeId(String measurementTypeId){
            this.measurementTypeId =measurementTypeId;
        }

        public String getArea(){
            return area;
        }

        public void setArea(String area){
            this.area =area;
        }


       public void setGPS1(String GPS1){
            this.GPS1 =GPS1;
        }

        public String getGPS1(){
            return GPS1;
        }


       public void setGPS2(String GPS2){
            this.GPS2 =GPS2;
        }

        public String getGPS2(){
            return GPS2;
        }


       public void setGPS3(String GPS3){
            this.GPS3 =GPS3;
        }

        public String getGPS3(){
            return GPS3;
        }

       public void setGPS4(String GPS4){
            this.GPS4 =GPS4;
        }

        public String getGPS4(){
            return GPS4;
        }

       public void setTermId(String termId){
            this.termId =termId;
       }

       public String getTermId(){
            return termId;
       }

       public void setOwnedById(String ownedById){
               this.ownedById =ownedById;
       }

       public String getOwnedById(){
            return ownedById;
       }

       public void setownedByComment(String ownedByComment){
               this.ownedByComment =ownedByComment;
       }

       public String getOwnedByComment(){
            return ownedByComment;
       }

       public void setDistrictId(String districtId){
               this.districtId =districtId;
       }

       public String getDistrictId(){
            return districtId;
       }


       public void setProvinceCode(String provienceCode){
               this.provinceCode =provienceCode;
       }

       public String getProvinceCode(){
            return provinceCode;
       }


        public void reset() {
            landId = "";
            landName = "";
            divisionId = "";
            description = "";
            measurementTypeId = "";
            GPS1  ="";
            GPS2  ="";
            GPS3  ="";
            GPS4  ="";
            area    ="";
            termId         ="";
            ownedById      ="";
            ownedByComment ="";
            districtId     ="";
            provinceCode    ="";

            provinceName="";
            districtName="";
            divisionName="";
             measurementTypeName="";
            termName="";
            ownedByName="";

       }

    public LandTO() {
    }

    public void setNullValsToEmpty() {
        landId += "";
        landName += "";
        divisionId += "";
        description += "";
        measurementTypeId  += "";
        GPS1   +="";
        GPS2   +="";
        GPS3    +="";
        GPS4    +="";
        area +="";
        termId +="";
        ownedById +="";
        ownedByComment +="";
        districtId +="";
        provinceCode +="";

        provinceName+="";
        districtName+="";
        divisionName+="";
         measurementTypeName+="";
        termName+="";
        ownedByName+="";
    }

    public boolean isEmpty(String s) {
        if (s == null) {
            return true;
        }
        if (s.trim().length() <= 0) {
            return true;
        }
        return false;
    }


    public List validate() {
        List result = new LinkedList();

        if(isEmpty(landName)){
            result.add("Land Name can't be null");
        }

//        if(isEmpty(provinceCode)){
//            result.add("Provience can't be null");
//        }
//
//        if(isEmpty(districtId)){
//            result.add("District can't be null");
//        }

        if(isEmpty(divisionId)){
            result.add("Division can't be null");
        }
        if(isEmpty(area)){
            result.add("Area can't be null");
        }
        if(isEmpty(measurementTypeId)){
            result.add("Unit can't be null");
        }

        if(isEmpty(ownedById)){
            result.add("Owned By can't be null");
        }
        if(isEmpty(termId)){
            result.add("Term can't be null");
        }

        try{
            Integer.parseInt(area);
        }catch(Exception e){
            result.add("Area should be an integer");
        }

        return result;
    }
}
