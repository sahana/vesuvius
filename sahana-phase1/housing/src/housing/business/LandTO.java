package org.housing.business;

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
        private String areaId;
        private String measurement;
        private String GPS1;
        private String GPS2;
        private String GPS3;
        private String GPS4;
        private String termId;
        private String ownedById;
        private String ownedByComment;


        /*public LandTO (String landId,String landName, String divisionId, String description, String areaId) {
            this.landId =landId;
            this.landName = landName;
            this.divisionId = divisionId;
            this.description =description;
            this.areaId =areaId;

        } */

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

        public String getAreaId(){
            return areaId;
        }

        public void setAreaId(String areaId){
            this.areaId =areaId;
        }

        public String getMeasurement(){
            return measurement;
        }

        public void setMeasurement(String measurement){
            this.measurement =measurement;
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

        public void reset() {
            landId = "";
            landName = "";
            divisionId = "";
            description = "";
            areaId = "";
            GPS1  ="";
            GPS2  ="";
            GPS3  ="";
            GPS4  ="";
            measurement ="";
            termId ="";
            ownedById="";
            ownedByComment="";
       }

    public LandTO() {
    }

    public void setNullValsToEmpty() {
        landId += "";
        landName += "";
        divisionId += "";
        description += "";
        areaId  += "";
        GPS1   +="";
        GPS2   +="";
        GPS3    +="";
        GPS4    +="";
        measurement +="";
        termId +="";
        ownedById +="";
        ownedByComment +="";
    }
}
