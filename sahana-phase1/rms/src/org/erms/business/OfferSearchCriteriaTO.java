package org.erms.business;

import java.sql.Date;

/**
 * Created by IntelliJ IDEA.
 * User: Srinath
 * Date: Jan 13, 2005
 * Time: 6:54:44 PM
 * To change this template use File | Settings | File Templates.
 */


import java.sql.Date;
import java.util.Collection;
import java.util.Vector;


public class OfferSearchCriteriaTO {

        private Collection offerDetails = new Vector();
        private String offerID="";
        private String orgCode="";
        private String orgName="";
        private String targetArea="";
        private String offeringIndividual="";
        private String offeringEntityType="Organization";

    public void setContactName(String contactName) {
        this.contactName = contactName;
    }

    public String getContactName() {
        return contactName;
    }

    private  String contactName="";

        private String category="";
        private String item="";
        private String quantity="";



    private String contactAddress="";

        public String getOrgName() {
            return orgName;
        }

        public void setOrgName(String orgName) {
            this.orgName = orgName;
        }



       public Collection getOfferDetails() {
            return offerDetails;
        }

        public void setRequestDetails(Collection requestDetails) {
            this.offerDetails = requestDetails;
        }

        public void addOfferDetails(OfferDetail offerDetail) {
            if (offerDetails == null) {
                offerDetails = new Vector();
            }
            offerDetails.add(offerDetail);
        }


        public String getOrgCode() {
            return orgCode;
        }

        public void setOrgCode(String orgCode) {
            this.orgCode = orgCode;
        }

        public void setOfferID(String offerID) {
            this.offerID = offerID;
       }


        public String getOfferID() {
            return offerID;
        }

        public String getTargetArea() {
                return targetArea;
        }

        public void setTargetArea(String targetArea) {
           this.targetArea = targetArea;
        }

        public void setOfferDetails(Collection offerDetails) {
            this.offerDetails = offerDetails;
        }
        public String getContactAddress() {
            return contactAddress;
        }

        public void setContactAddress(String contactAddress) {
            this.contactAddress = contactAddress;
        }


        public String getOfferingEntityType() {
            return offeringEntityType;
        }

        public void setOfferingEntityType(String offeringEntityType) {
            this.offeringEntityType = offeringEntityType;
        }


        public String getOfferingIndividual() {
            return offeringIndividual;
        }

        public void setOfferingIndividual(String offeringIndividual) {
            this.offeringIndividual = offeringIndividual;
        }
        public String getItem() {
               return item;
           }

        public void setItem(String item) {
               this.item = item;
           }

        public String getCategory() {
              return category;
          }

          public void setCategory(String category) {
              this.category = category;
          }


        public void setQuantity(String quantity) {
            this.quantity = quantity;
        }

        public String getQuantity() {
            return quantity;
        }


}
