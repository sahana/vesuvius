package org.erms.business;

/**
 * Created by IntelliJ IDEA.
 * User: Srinath
 * Date: Jan 12, 2005
 * Time: 2:49:42 PM
 * To change this template use File | Settings | File Templates.
 */
public class OfferDetail {

    private String offerID="";
    private String offerDetailID="";
    private String category="";
    private String unit="";
    private int quantity=0;
    private String item="";
    private String targetArea="";



     public OfferDetail(String requestDetailID, String offerID, String category,  String unit, int quantity, String item, String targetArea) {

        this.offerID = offerID;
        this.category = category;
        this.unit = unit;
        this.quantity = quantity;
        this.item = item;
        this.targetArea =targetArea;

    }

    public void setCategory(String category) {
        this.category = category;
    }
    public String getCategory() {
        return category;
    }
    public String getUnit() {
        return unit;
    }

    public void setUnit(String unit) {
        this.unit = unit;

    }
    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }
    public int getQuantity() {
            return quantity;
        }

     public void setItem(String item) {
        this.item = item;
    }

     public String getItem() {
        return item;
    }

    public String getTargetArea() {
           return targetArea;
       }

      public void setTargetArea(String targetArea) {
        this.targetArea = targetArea;
    }

    public String getOfferID() {
           return offerID;
       }

       public void setOfferID(String offerID) {
           this.offerID = offerID;
       }
    public String getOfferDetailID() {
         return offerDetailID;
     }

     public void setOfferDetailID(String offerDetailID) {
         this.offerDetailID = offerDetailID;
     }


}
