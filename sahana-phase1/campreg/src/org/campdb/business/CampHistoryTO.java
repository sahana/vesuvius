package org.campdb.business;

import java.util.Date;

/**
 * Copyright 2001-2004 The Apache Software Foundation.
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
public class CampHistoryTO {
    private String campId;
    private String campHistoryId;
    private String campMen;
    private String campWomen;
    private String campChildren;
    private String campTotal;
    private String campFamily;
    private Date updateDate = new Date(); //initialise to current date
    private Date updateTime = new Date(); //initialise to current date

    public String getCampId() {
        return campId;
    }

    public void setCampId(String campId) {
        this.campId = campId;
    }

    public String getCampHistoryId() {
        return campHistoryId;
    }

    public void setCampHistoryId(String campHistoryId) {
        this.campHistoryId = campHistoryId;
    }

    public String getCampMen() {
        return campMen;
    }

    public void setCampMen(String campMen) {
        this.campMen = campMen;
    }

    public String getCampWomen() {
        return campWomen;
    }

    public void setCampWomen(String campWomen) {
        this.campWomen = campWomen;
    }

    public String getCampChildren() {
        return campChildren;
    }

    public void setCampChildren(String campChildren) {
        this.campChildren = campChildren;
    }

    public String getCampTotal() {
        return campTotal;
    }

    public void setCampTotal(String campTotal) {
        this.campTotal = campTotal;
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

    public Date getUpdateTime() {
        return updateTime;
    }

    public void setUpdateTime(Date updateTime) {
        this.updateTime = updateTime;
    }
}
