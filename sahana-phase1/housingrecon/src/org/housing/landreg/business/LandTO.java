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
        private String planId;
        private String landId;
        //private String planNo;
        private String landName;
        private String landTypeId;
        private String divisionId;
        private String description;
        //private String measurementTypeId;
        private String area;
        //private String measurementTypeId1;
        private String area1;
        //private String measurementTypeId2;
        private String area2;

        private String GPS1;
        private String GPS2;
        private String GPS3;
        private String GPS4;
        private String termId;
        private String ownedById;
        private String ownedByComment;
        private String districtId;
        private String provinceCode;
        private String remarks;
        private String infractureId;
        private String proposedUseAsPerZonPlan;

        private String provinceName;
        private String districtName;
        private String divisionName;
        private String measurementTypeName;
        private String termName;
        private String ownedByName;
        private String landTypeName;
        private String infractureName;
        private String subDivisionId;
        private String subDivisionName;

        private String infractureIds;


        /*public LandTO (String landId,String landName, String divisionId, String description, String areaId) {
            this.landId =landId;
            this.landName = landName;
            this.divisionId = divisionId;
            this.description =description;
            this.areaId =areaId;

        } */

        public String getSubDivisionName() {
            return subDivisionName;
        }

        public void setSubDivisionName(String subDivisionName) {
            this.subDivisionName =subDivisionName ;
        }

        public String getSubDivisionId(){
            return subDivisionId;
        }

        public void setSubDivisionId(String subDivisionId){
            this.subDivisionId = subDivisionId;
        }

        public String getInfractureName() {
            return infractureName;
        }

        public void setInfractureName(String infractureName) {
            this.infractureName = infractureName;
        }

        public String getLandTypeName() {
            return landTypeName;
        }

        public void setLandTypeName(String landTypeName) {
            this.landTypeName = landTypeName;
        }
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

     /*   public String setPlanNo() {
            return planNo;
        }

        public void getPlanNo(String planNo) {
            this.planNo = planNo;
        } */

        public String getPlanId() {
            return planId;
        }

        public void setPlanId(String planId) {
            this.planId = planId;
        }

        public String getLandName() {
            return landName;
        }

        public void setLandName(String landName) {
            this.landName = landName;
        }

        public String getLandTypeId() {
            return landTypeId;
        }

        public void setLandTypeId(String landTypeId) {
            this.landTypeId = landTypeId;
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

/*        public String getMeasurementTypeId(){
            return measurementTypeId;
        }

        public void setMeasurementTypeId(String measurementTypeId){
            this.measurementTypeId =measurementTypeId;
        }                                             */

        public String getArea(){
            if(isEmpty(area)){
               area="0";
            }
            return area;
        }

        public void setArea(String area){
            this.area =area;
        }

        /*public String getMeasurementTypeId1(){
            return measurementTypeId1;
        }

        public void setMeasurementTypeId1(String measurementTypeId1){
            this.measurementTypeId1 =measurementTypeId1;
        } */

        public String getArea1(){
            if(isEmpty(area1)){
               area1="0";
            }
            return area1;
        }

        public void setArea1(String area1){
            this.area1 =area1;
        }

       /* public String getMeasurementTypeId2(){
            return measurementTypeId2;
        }

        public void setMeasurementTypeId2(String measurementTypeId2){
            this.measurementTypeId2 =measurementTypeId2;
        }*/

        public String getArea2(){
            if(isEmpty(area2)){
               area2="0";
            }

            return area2;
        }

        public void setArea2(String area2){
            this.area2 =area2;
        }

       public void setGPS1(String GPS1){
            this.GPS1 =GPS1;
       }

        public String getGPS1(){
          //  if(GPS1.equals("-1")){
           //    GPS1="-1";
           // }
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
          //  if(GPS3.equals("-1")){
          //     GPS3="";
           // }
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

       public void setRemarks(String remarks){
               this.remarks =remarks;
       }

       public String getRemarks(){
            return remarks;
       }

       public void setInfractureId(String infractureId){
               this.infractureId =infractureId;
       }

       public String getInfractureId(){
            return infractureId;
       }

       public void setInfractureIds(String infractureIds){
               this.infractureIds =infractureIds;
       }

       public String getInfractureIds(){
            return infractureIds;
       }

       public void setProposedUseAsPerZonPlan(String proposedUseAsPerZonPlan){
               this.proposedUseAsPerZonPlan =proposedUseAsPerZonPlan;
       }

       public String getProposedUseAsPerZonPlan(){
            return proposedUseAsPerZonPlan;
       }

        public void reset() {

            landId = "";
            landName = "";
            divisionId = "";
            description = "";
   //         measurementTypeId = "";
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

    //         measurementTypeName="";
            termName="";
            ownedByName="";

            planId="";
    //        measurementTypeId1="";
            area1 ="";
   //         measurementTypeId2="";
            area2="";
            remarks="";
            infractureId="";
            infractureIds="";
            proposedUseAsPerZonPlan="";
            infractureName ="";
            subDivisionId ="";

            subDivisionName ="";

       }

    public LandTO() {

    }

    public void setNullValsToEmpty() {
        landId += "";
        landTypeName+="";
        landName += "";
        divisionId += "";
        description += "";
    //    measurementTypeId  += "";
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
     //   measurementTypeName+="";
        termName+="";
        ownedByName+="";
        planId+="";
      //  measurementTypeId1+="";
        area1 +="";
      //  measurementTypeId2+="";
        area2+="";
        remarks+="";
        infractureId+="";
        infractureName+="";
        proposedUseAsPerZonPlan+="";
        infractureIds+="";
        subDivisionId+="";
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

        if(isEmpty(planId)){
            result.add("Plan No can't be empty");
        }

        if(isEmpty(provinceCode)){
            result.add("Select a Province");
        }

        if(isEmpty(districtId)){
            result.add("Select a District");
        }

        if(isEmpty(divisionId)){
            result.add("Select a Local Authority");
        }

        if(isEmpty(subDivisionId)){
            result.add("Select a G N Division");
        }
        /*if(isEmpty(area)){
            result.add("Area can't be null");
        }
        if(isEmpty(measurementTypeId)){
            result.add("Unit can't be null");
        } */

        if(isEmpty(infractureId)){
            result.add("Select a Infracture");
        }
        if(isEmpty(landTypeId)){
            result.add("Select a Land Type");
        }
        if(isEmpty(ownedById)){
            result.add("Select Ownership");
        }
        if(isEmpty(termId)){
            result.add("Select a Term");
        }
        try{
            if(!isEmpty(area)){
                Double.parseDouble(area);
            }
        }catch(Exception e){
            result.add("Acres should be an integer");
        }
        try{
            if(!isEmpty(area1)){
               Double.parseDouble(area1);
            }
        }catch(Exception e){
            result.add("Roods should be an integer");
        }
        try{
            if(!isEmpty(area2)){
               Double.parseDouble(area2);
            }
        }catch(Exception e){
            result.add("Perches should be an integer");
        }

        return result;
    }

     public void copyFrom(LandTO src) {

        proposedUseAsPerZonPlan=src.getProposedUseAsPerZonPlan();

        landId =src.getLandId();
        landName = src.getLandName();
        divisionId =src.getDivisionId();
        description =src.getDescription();
        GPS1   = src.getGPS1();
        GPS2   = src.getGPS2();
        GPS3    = src.getGPS3();
        GPS4    = src.getGPS4();
        area= src.getArea();
        termId =src.getTermId();
        ownedById =src.getOwnedById();
        ownedByComment = src.getOwnedByComment();
        districtId = src.getDistrictId();
        provinceCode = src.getProvinceCode();
        provinceName = src.getprovinceName();
        districtName= src.getDistrictName();
        divisionName =src.getdivisionName();
        subDivisionId =src.getSubDivisionId();
        subDivisionName =src.getSubDivisionName();
        termName = src.getTermName();
        ownedByName = src.getOwnedByName();
        planId = src.getPlanId();
        area1 =src.getArea1();
        area2 =src.getArea2();
        remarks =src.getRemarks();
        infractureId =src.getInfractureIds(); 
        infractureId =src.getInfractureId();

        landTypeId =src.getLandTypeId();
        landTypeName =src.getLandTypeName();
        infractureName=src.getInfractureName();
        infractureIds=src.getInfractureIds();

        System.out.println(infractureIds+"infractureIds  haiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii ");

        System.out.println(proposedUseAsPerZonPlan+"haiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii proosed Land");
        System.out.println(remarks+"haiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii remarks");
        System.out.println(infractureId+"infractureId  haiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii ");

        // measurementTypeId  = src.getMeasurementTypeId();
        //  measurementTypeId2=src.getMeasurementTypeId2();
        // measurementTypeId1=src.getMeasurementTypeId1();
        // measurementTypeName = src.getMeasurementTypeName();
    }

}
