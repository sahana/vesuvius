package org.erms.business;

import java.sql.Date;
import java.util.Collection;
import java.util.Vector;


public class Offer {

    private Collection offerDetails = new Vector();

    private String offerID="";
    private String orgCode="";
    private String orgName="";
    private String orgContact="";

    private String user="";
    private String contactName="";
    private String contactNumber="";
    private String description="";


    private String emailAddress="";
    private String eqValue="";
    private String targetArea="";
    private String offeringIndividual="";
    private String offeringEntityType="Organization";
    private String timeFrame="";
    private String unit="";
    private String category="";
    private String item="";
    private String quantity="";

    private String targetSpecific="No";



    private String contactAddress="";

    public String getOrgName() {
        return orgName;
    }

    public void setOrgName(String orgName) {
        this.orgName = orgName;
    }

    public String getOrgContact() {
        return orgContact;
    }

    public void setOrgContact(String orgContact) {
        this.orgContact = orgContact;
    }


    public Offer() {
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

    public String getUser() {
        return user;
    }

    public void setUser(String user) {
        this.user = user;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setOfferID(String offerID) {
        this.offerID = offerID;
   }


    public String getOfferID() {
        return offerID;
    }
      public String getConatactName() {
        return contactName;
    }

    public void setContactName(String conatactName) {
        this.contactName = conatactName;
    }

    public String getContactNumber() {
           return contactNumber;
       }
    public void setContactNumber(String contactNumber) {
          this.contactNumber = contactNumber;
      }
      public void setEmailAddress(String emailAddress) {
        this.emailAddress = emailAddress;
    }

    public String getEmailAddress() {
        return emailAddress;
    }

     public String getEqValue() {
        return eqValue;
    }

    public void setEqValue(String eqValue) {
        this.eqValue = eqValue;
    }
    public String getTargetArea() {
            return targetArea;
    }

    public void setTargetArea(String targetArea) {
       this.targetArea = targetArea;
    }

    public String getContactName() {
        return contactName;
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

      public String getUnit() {
            return unit;
        }

      public void setUnit(String unit) {
            this.unit = unit;
        }

    public String getTimeFrame() {
        return timeFrame;
    }

    public void setTimeFrame(String timeFrame) {
        this.timeFrame = timeFrame;
    }


    public void setQuantity(String quantity) {
        this.quantity = quantity;
    }

    public String getQuantity() {
        return quantity;
    }

    public String getTargetSpecific() {
          return targetSpecific;
    }

        public void setTargetSpecific(String targetSpecific) {
            this.targetSpecific = targetSpecific;
        }

    public void clear()
    {
        offerID="";
           orgCode="";
           orgName="";
            orgContact="";

           user="";
              contactName="";
              contactNumber="";
              description="";


              emailAddress="";
              eqValue="";
              targetArea="";
              offeringIndividual="";
              offeringEntityType="Organization";
              timeFrame="";
             unit="";
              category="";
              item="";
              quantity="";

              targetSpecific="No";
              offerDetails = new Vector();


    }



}
