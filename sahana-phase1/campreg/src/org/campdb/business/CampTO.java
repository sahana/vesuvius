/*
* (C) Copyright 2005 Sahana. All Rights Reserved.
*
*/

package org.campdb.business;

import java.util.List;
import java.util.LinkedList;
import java.util.Date;
import java.beans.PropertyEditorManager;


public class CampTO {

    private String campId;
    private String areadId;
    private String divisionId;
    private String districtCode;
    private String provienceCode;
    private String campName;
    private String campAccesability;
    private String campMen;
    private String campWomen;
    private String campChildren;
    private String campTotal;
    private String campCapability;
    private String campContactPerson;
    private String campContactNumber;
    private String campComment;
    private Date updateDate = new Date(); //initialise to current date
    private Date updateTime = new Date(); //initialise to current date
    private String provienceName;
    private String districtName;
    private String divionName;
    private String areaName;
    private String campFamily;
    private String countSelect;


    public Date getUpdateTime() {
        return updateTime;
    }

    public void setUpdateTime(Date updateTime) {
        this.updateTime = updateTime;
    }

    public String getCountSelect() {
        return countSelect;
    }

    public void setCountSelect(String countSelect) {
        this.countSelect = countSelect;
    }

    public String getCampFamily() {
        return campFamily;
    }

    public void setCampFamily(String campFamily) {
        this.campFamily = campFamily;
    }

    public Date getUpdateDate() {
        return updateDate;
    }

    public void setUpdateDate(Date updateDate) {
        this.updateDate = updateDate;
    }
    public String getCampId() {
        return campId;
    }

    public void setCampId(String campId) {
        this.campId = campId;
    }

    public String getAreadId() {
        return areadId;
    }

    public void setAreadId(String areadId) {
        this.areadId = areadId;
    }

    public String getCampName() {
        if(campName == null || campName.equals("null")) campName = "";
        return campName;
    }

    public void setCampName(String campName) {
        this.campName = campName;
    }

    public String getCampAccesability() {
        if(campAccesability == null || campAccesability.equals("null")) campAccesability = "";
        return campAccesability;
    }

    public void setCampAccesability(String campAccesability) {
        this.campAccesability = campAccesability==null?"":campAccesability;
    }

    public String getCampMen() {
        if(campMen == null || campMen.equals("null")) campMen = "";
        return campMen;
    }

    public void setCampMen(String campMen) {
        this.campMen = campMen == null?"":campMen;
    }

    public String getCampWomen() {
        if(campWomen == null || campWomen.equals("null")) campWomen = "";
        return campWomen;
    }

    public void setCampWomen(String campWomen) {
        this.campWomen = campWomen;
    }

    public String getCampChildren() {
        if(campChildren == null || campChildren.equals("null")) campChildren = "";
        return campChildren;
    }

    public void setCampChildren(String campChildren) {
        this.campChildren = campChildren;
    }

    public String getCampTotal() {
        if(campTotal == null || campTotal.equals("null")) campTotal = "";
        return campTotal;
    }

    public void setCampTotal(String campTotal) {
        this.campTotal = campTotal;
    }

    public String getCampCapability() {
        if(campCapability == null || campCapability.equals("null")) campCapability = "";
        return campCapability;
    }

    public void setCampCapability(String campCapability) {
        this.campCapability = campCapability;
    }

    public String getCampContactPerson() {
        if(campContactPerson == null || campContactPerson.equals("null")) campContactPerson = "";
        return campContactPerson;
    }

    public void setCampContactPerson(String campContactPerson) {
        this.campContactPerson = campContactPerson;
    }

    public String getCampContactNumber() {
        if(campContactNumber == null || campContactNumber.equals("null")) campContactNumber = "";
        return campContactNumber;
    }

    public void setCampContactNumber(String campContactNumber) {
        this.campContactNumber = campContactNumber;
    }

    public String getCampComment() {
        if(campComment == null || campComment.equals("null")) campComment = "";
        return campComment;
    }

    public void setCampComment(String campComment) {
        this.campComment = campComment;
    }

    public String getDivisionId() {
        return divisionId;
    }

    public void setDivisionId(String divisionId) {
        this.divisionId = divisionId;
    }

    public String getDistrictCode() {
        return districtCode;
    }

    public void setDistrictCode(String districtCode) {
        this.districtCode = districtCode;
    }

    public String getProvienceCode() {
        return provienceCode;
    }

    public void setProvienceCode(String provienceCode) {
        this.provienceCode = provienceCode;
    }

    public String getProvienceName() {
        return provienceName;
    }

    public void setProvienceName(String provienceName) {
        this.provienceName = provienceName;
    }

    public String getDistrictName() {
        return districtName;
    }

    public void setDistrictName(String districtName) {
        this.districtName = districtName;
    }

    public String getDivionName() {
        return divionName;
    }

    public void setDivionName(String divionName) {
        this.divionName = divionName;
    }

    public String getAreaName() {
        if(areaName == null || areaName.equals("null")) areaName = "";
        return areaName;
    }

    public void setAreaName(String areaName) {
        this.areaName = areaName;
    }

    /**
     * Returns list of error messages as strings if
     * values are not valid for datebase insertions/updates.
     *
     * @return
     */
    public List validate() {
        List result = new LinkedList();
        boolean isNumberCorrect = false;

        if(isEmpty(campName)){
            result.add("Camp Name can't be null");
        }


        try{
            Integer.parseInt(campTotal);
            isNumberCorrect = true;
        }catch(Exception e){
            result.add("Total should be an integer");
            isNumberCorrect = false;
        }
        if (!isNumberCorrect){
            try{
                if (campMen!=null && campMen.trim().length()>0) {
                    Integer.parseInt(campMen);
                    isNumberCorrect = true;
                }
                if (campWomen!=null &&  campWomen.trim().length()>0){
                    Integer.parseInt(campWomen );
                    isNumberCorrect = true;
                }
                if (campChildren!=null &&  campChildren.trim().length()>0){
                    Integer.parseInt(campChildren);
                    isNumberCorrect = true;
                }
            }catch(Exception e){
                result.add("Break down figures should be integer");
                isNumberCorrect = false;
            }
        }

        if (isEmpty(areadId)) {
            if (isEmpty(divisionId)) {
                if (isEmpty(districtCode) ) {
                    result.add("Division and Area is required.");
                }
            }
        }
        return result;
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

    public void reset() {
        campId = "";
        areadId = "";
        divisionId = "";
        districtCode = "";
        provienceCode = "";
        campName = "";
        campAccesability = "";
        campMen = "";
        campWomen = "";
        campChildren = "";
        campTotal = "";
        campCapability = "";
        campContactPerson = "";
        campContactNumber = "";
        campComment = "";
        provienceName = "";
        districtName = "";
        divionName = "";
        areaName = "";
    }


    public void setNullValsToEmpty() {
        campId += "";
        areadId += "";
        divisionId += "";
        districtCode += "";
        provienceCode += "";
        campName += "";
        campAccesability += "";
        campMen += "";
        campWomen += "";
        campChildren += "";
        campTotal += "";
        campCapability += "";
        campContactPerson += "";
        campContactNumber += "";
        campComment += "";
        provienceName += "";
        districtName += "";
        divionName += "";
        areaName += "";
    }

    public void copyFrom(CampTO src) {
        campId = src.campId ;
        areadId = src.areadId ;
        divisionId = src.divisionId ;
        districtCode = src.districtCode ;
        provienceCode = src.provienceCode ;
        campName = src.campName ;
        campAccesability = src.campAccesability ;
        campMen = src.campMen ;
        campWomen = src.campWomen ;
        campChildren = src.campChildren ;
        campTotal = src.campTotal ;
        campCapability = src.campCapability ;
        campContactPerson = src.campContactPerson ;
        campContactNumber = src.campContactNumber ;
        campComment = src.campComment ;
        provienceName = src.provienceName ;
        districtName = src.districtName ;
        divionName = src.divionName ;
        areaName = src.areaName ;

    }

}

