package org.erms.business;



import java.util.List;

import java.util.LinkedList;
import java.util.ArrayList;
import java.sql.Date;



/**

 * Created by IntelliJ IDEA.

 * User: lsf

 * Date: Dec 31, 2004

 * Time: 8:03:00 PM

 * To change this template use File | Settings | File Templates.

 */

public class OrganizationRegistrationTO {



    private String orgCode;

    private String contactPerson;

    private String orgName;

    private String status;
    
    private String orgAddress;

    private String contactNumber;

    private String emailAddress;

    private String countryOfOrigin;

    private String facilitiesAvailable;

    private ArrayList workingAreas;
//    private String workingAreas;

    private ArrayList sectors;

    private String comments;

    private String orgType;

    private String ngoType;

    private String username;

    private String password;

    private String passwordRe;

    private String lastUpdate;

    private boolean isSriLankan;

    private Date periodEndDate =  new java.sql.Date(new java.util.Date().getTime());

    public String getLastUpdate() {
        return lastUpdate;
    }

    public void setLastUpdate(String lastUpdate) {
        this.lastUpdate = lastUpdate;
    }


    public boolean isSriLankan() {
        return isSriLankan;
    }

    public void setIsSriLankan(boolean sriLankan) {
        isSriLankan = sriLankan;
    }

    public String getUsername() {
        return username;
    }



    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getPasswordRe() {
        return passwordRe;
    }

    public void setPasswordRe(String passwordRe) {
        this.passwordRe = passwordRe;
    }

    public String getNgoType() {
        return ngoType;
    }

    public void setNgoType(String ngoType) {
        this.ngoType = ngoType;
    }


    public String getOrgType() {
        return orgType;
    }

    public void setOrgType(String orgType) {
        this.orgType = orgType;
    }

    public String getOrgCode() {

        return orgCode;

    }



    public void setOrgCode(String orgCode) {

        this.orgCode = orgCode;

    }



    public String getContactPerson() {

        return contactPerson;

    }



    public void setContactPerson(String contactPerson) {

        this.contactPerson = contactPerson;

    }



    public String getOrgName() {

        return orgName;

    }



    public void setOrgName(String orgName) {

        this.orgName = orgName;

    }



    public String getStatus() {

        return status;

    }



    public void setStatus(String status) {

        this.status = status;

    }



    public String getOrgAddress() {

        return orgAddress;

    }



    public void setOrgAddress(String orgAddress) {

        this.orgAddress = orgAddress;

    }



    public String getContactNumber() {

        return contactNumber;

    }



    public void setContactNumber(String contactNumber) {

        this.contactNumber = contactNumber;

    }



    public String getEmailAddress() {

        return emailAddress;

    }



    public void setEmailAddress(String emailAddress) {

        this.emailAddress = emailAddress;

    }



    public String getCountryOfOrigin() {

        return countryOfOrigin;

    }



    public void setCountryOfOrigin(String countryOfOrigin) {

        this.countryOfOrigin = countryOfOrigin;

    }



    public String getFacilitiesAvailable() {

        return facilitiesAvailable;

    }



    public void setFacilitiesAvailable(String facilitiesAvailable) {

        this.facilitiesAvailable = facilitiesAvailable;

    }

//    public String getWorkingAreas() {
//
//           return workingAreas;
//
//       }
//
//
//
//       public void setWorkingAreas(String workingAreas) {
//
//           this.workingAreas = workingAreas;
//
//       }


    public ArrayList getWorkingAreas() {

        if(workingAreas == null){
            workingAreas = new ArrayList();
        }
        return workingAreas;

    }



    public void addWorkingArea(String areaName) {

        if(workingAreas == null){
            workingAreas = new ArrayList();
        }
        this.workingAreas.add(areaName);

    }


    public ArrayList getSectors() {
           if(null ==sectors){
               this.sectors = new ArrayList();
           }
           return sectors;
       }

       public void addSectors(String sectorName) {
           if(null ==sectors){
               this.sectors = new ArrayList();
           }
           sectors.add(sectorName);
       }
    

    public String getComments() {

        return comments;

    }



    public void setComments(String comments) {

        this.comments = comments;

    }





    public boolean isEmpty(String string) {

        if (string == null) return true;

        if (string.trim().length() <= 0) return true;

        return false;

    }


    public Date getPeriodEndDate() {
        return periodEndDate;
    }

    public void setPeriodEndDate(Date periodEndDate) {
        this.periodEndDate = periodEndDate;
    }

    public List validate(boolean userNamePasswordValidate) {

        List result = new LinkedList();


//        if (isEmpty(orgCode)) {
//
//            result.add("Organization Code is required.");
//
//        }

        if (isEmpty(orgName)) {

            result.add("Organisation Name is required.");

        }

        if (isEmpty(contactPerson))  {

            result.add("Contact Person is required");

        }

        if (isEmpty(orgAddress)) {

            result.add("Address is required.");

        }



        if (isEmpty(contactNumber)) {

            result.add("Contact No is required.");

        }



        if (isEmpty(emailAddress)) {

            result.add("Email Address is required.");

        }
        //
        if (! isEmpty(emailAddress)){
            validateEmail(emailAddress,result);
        }



        if (isEmpty(countryOfOrigin)) {

            result.add("Country of origin  is required.");

        }



        if (userNamePasswordValidate) {
            if(isEmpty(username)){
                result.add("User Name is required.");
            }
            if(password==null){
                result.add( "Password is required.");
            }

            if (passwordRe==null) {
                result.add("Re enteredPassword is required.");
            }

            if(password!=null && !password.equals(passwordRe)) {
                result.add("Password does not match.");
            }
        }


        if (result.size() <=0) {
            if(orgAddress != null) {
                if (orgAddress.length() > 255) {

                    result.add("Address length is to long ( maximum allowed is 255 ).");

                }
            }
            if(facilitiesAvailable != null ){
                if (facilitiesAvailable.length() > 255) {

                    result.add("Facilities available list is too long ( maximum allowed is 255 ).");

                }
            }
//            if (workingAreas != null ){
//                if (workingAreas.length() > 255) {
//
//                    result.add("Working areas list is too long ( maximum allowed is 255 ).");
//
//                }
//            }
            if(comments != null ){
                if (comments.length() > 255)

                    result.add("Comment is too long ( maximum allowed is 255 ).");
            }
        }

        return result;

    }


    private void validateEmail(String email, List error){
        char ch1 = '@';
        char ch2 = '.';
        int pos1 = email.indexOf(ch1);
        String subStr ="";
        if(pos1 < 0) {
            error.add("invalid email address");
        } else {
            subStr = email.substring(pos1);
            int pos2 = subStr.indexOf(ch2);
            if(pos2 < 0 ){
                error.add("invalid email address");
            }else if ((pos2 + 1 )== subStr.length()){
                error.add("invalid email address");
            }
        }
    }


}

