package org.erms.business;



import java.util.List;

import java.util.LinkedList;



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

    private String workingAreas;

    private String comments;



    public String getOrgCode() 
	{
        if ( isEmpty(this.orgCode) )
		  return "" ;
        return orgCode;

    }



    public void setOrgCode(String orgCode) {

        this.orgCode = orgCode;

    }



    public String getContactPerson() {
        if ( isEmpty(this.contactPerson) )
		  return "" ;
        return contactPerson;

    }



    public void setContactPerson(String contactPerson) {

        this.contactPerson = contactPerson;

    }



    public String getOrgName() {
        if ( isEmpty(this.orgName) )
		  return "" ;
        return orgName;

    }



    public void setOrgName(String orgName) {

        this.orgName = orgName;

    }



    public String getStatus() {
        if ( isEmpty(this.status) )
		  return "" ;
        return status;

    }



    public void setStatus(String status) {

        this.status = status;

    }



    public String getOrgAddress() {
        if ( isEmpty(this.orgAddress) )
		  return "" ;
        return orgAddress;

    }



    public void setOrgAddress(String orgAddress) {

        this.orgAddress = orgAddress;

    }



    public String getContactNumber() {
        if ( isEmpty(this.contactNumber) )
		  return "" ;
        return contactNumber;

    }



    public void setContactNumber(String contactNumber) {

        this.contactNumber = contactNumber;

    }



    public String getEmailAddress() {
        if ( isEmpty(this.emailAddress) )
		  return "" ;
        return emailAddress;

    }



    public void setEmailAddress(String emailAddress) {

        this.emailAddress = emailAddress;

    }



    public String getCountryOfOrigin() {
        if ( isEmpty(this.countryOfOrigin) )
		  return "" ;
        return countryOfOrigin;

    }



    public void setCountryOfOrigin(String countryOfOrigin) {

        this.countryOfOrigin = countryOfOrigin;

    }



    public String getFacilitiesAvailable() {
        if ( isEmpty(this.facilitiesAvailable) )
		  return "" ;
        return facilitiesAvailable;

    }



    public void setFacilitiesAvailable(String facilitiesAvailable) {

        this.facilitiesAvailable = facilitiesAvailable;

    }



    public String getWorkingAreas() {
        if ( isEmpty(this.workingAreas) )
		  return "" ;        
        return workingAreas;

    }



    public void setWorkingAreas(String workingAreas) {

        this.workingAreas = workingAreas;

    }



    public String getComments() {
        if ( isEmpty(this.comments) )
		  return "" ; 
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



    public List validate() {

        List result = new LinkedList();

        if (isEmpty(orgCode)) {

            result.add("Organization Code is required.");

        }

        if (isEmpty(orgName)) {

            result.add("Organisation Name is required.");

        }

        if (isEmpty(contactPerson))  {

            result.add("Contact Person.");

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



        if (isEmpty(countryOfOrigin)) {

            result.add("Country of origin  is required.");

        }



        if (result.size() <=0) {

            if (orgAddress.length() > 255) {

                result.add("Address length is to long ( maximum allowed is 255 ).");

            }

            if (facilitiesAvailable.length() > 255) {

                result.add("Facilities available list is too long ( maximum allowed is 255 ).");

            }

            if (workingAreas.length() > 255) {

                result.add("Working areas list is too long ( maximum allowed is 255 ).");

            }

            if (comments.length() > 255)

                result.add("Comment is too long ( maximum allowed is 255 ).");

        }

        return result;

    }



}

