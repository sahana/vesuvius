package org.housing.landreg.business;

/**
 * Created by IntelliJ IDEA.
 * User: nithyakala
 * Date: Jan 18, 2005
 * Time: 7:33:34 PM
 * To change this template use File | Settings | File Templates.
 */
public class DivisionTO {
    private String divId;
    private String divName;
    private String distCode;


      public DivisionTO(){
          
      }

      public DivisionTO (String divId,String divName, String distCode) {
            this.divId =divId;
            this.divName = divName;
            this.distCode = distCode;
        }

        public String getDivId() {
            return divId;
        }

        public void setDivId(String divId) {
            this.divId = divId;
        }

        public String getDivName() {
            return divName;
        }

        public void setDivName(String divName) {
            this.divName = divName;
        }

        public String getDistCode(){
            return distCode;
        }

        public void setDistCode(String distCode){
            this.distCode = distCode;
        }

}
