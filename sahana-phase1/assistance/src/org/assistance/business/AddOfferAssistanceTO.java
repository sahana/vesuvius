package org.assistance.business;


import org.assistance.db.DataAccessManager;

import java.sql.Date;

import java.sql.ResultSet;

import java.sql.SQLException;

import java.math.BigDecimal;

import java.util.regex.Pattern;


/**
 * Copyright 2001-2004 The Apache Software Foundation.
 * <p/>
 * <p/>
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * <p/>
 * you may not use this file except in compliance with the License.
 * <p/>
 * You may obtain a copy of the License at
 * <p/>
 * <p/>
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * <p/>
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * <p/>
 * distributed under the License is distributed on an "AS IS" BASIS,
 * <p/>
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * <p/>
 * See the License for the specific language governing permissions and
 * <p/>
 * limitations under the License.
 * <p/>
 * <p/>
 * <p/>
 * Jan 4, 2005
 * <p/>
 * 9:45:43 AM
 */

public class AddOfferAssistanceTO {
    boolean unique;
    int id;
    String agency;
    Date date;
    String sectors;
    String partners;
    String reliefCommittedDetails;
    String reliefCommittedTotal;
    String reliefDisbursedDetails;
    String reliefDisbursedTotal;
    String humanResourcesCommitted;
    String needsAssessments;
    String otherActivities;
    String plannedActivities;
    String otherIssues;

    String orgName;


    Pattern pattern = Pattern.compile("'");

    public boolean isUnique() {
        return unique;
    }

    public void setOrgName(String orgName) {
        this.orgName = orgName;
    }

    public AddOfferAssistanceTO() {

        unique = false;

    }

    public String getReliefCommittedTotal() {
        return reliefCommittedTotal;
    }

    public void setReliefCommittedTotal(String reliefCommittedTotal) {
        this.reliefCommittedTotal = reliefCommittedTotal;
    }

    public String getReliefDisbursedTotal() {
        return reliefDisbursedTotal;
    }

    public void setReliefDisbursedTotal(String reliefDisbursedTotal) {
        this.reliefDisbursedTotal = reliefDisbursedTotal;
    }
//
//
//
//    public AddOfferAssistanceTO(
//
//            String agency,
//
//            Date date,
//
//            String sectors,
//
//            String partners,
//
//            String reliefCommittedDetails,
//
//            BigDecimal reliefCommittedTotal,
//
//            String reliefDisbursedDetails,
//
//            BigDecimal reliefDisbursedTotal,
//
//            String humanResourcesCommitted,
//
//            String needsAssessments,
//
//            String otherActivities,
//
//            String plannedActivities,
//
//            String otherIssues) {
//
//        this();
//
//        this.agency= agency;
//
//        this.date= date;
//
//        this.sectors= sectors;
//
//        this.partners= partners;
//
//        this.reliefCommittedDetails= reliefCommittedDetails;
//
//        this.reliefCommittedTotal= reliefCommittedTotal;
//
//        this.reliefDisbursedDetails= reliefDisbursedDetails;
//
//        this.reliefDisbursedTotal= reliefDisbursedTotal;
//
//        this.humanResourcesCommitted= humanResourcesCommitted;
//
//        this.needsAssessments= needsAssessments;
//
//        this.otherActivities= otherActivities;
//
//        this.plannedActivities= plannedActivities;
//
//        this.otherIssues= otherIssues;
//
//    }
//
//

    public AddOfferAssistanceTO(ResultSet rs) throws SQLException {

        unique = true;

        id = rs.getInt(1);

        agency = rs.getString(2);

        date = rs.getDate(3);

        sectors = rs.getString(4);

        partners = rs.getString(5);

        reliefCommittedDetails = rs.getString(6);

        reliefCommittedTotal = rs.getString(7);

        reliefDisbursedDetails = rs.getString(8);

        reliefDisbursedTotal = rs.getString(9);

        humanResourcesCommitted = rs.getString(10);

        needsAssessments = rs.getString(11);

        otherActivities = rs.getString(12);

        plannedActivities = rs.getString(13);

        otherIssues = rs.getString(14);

        orgName = rs.getString(15);

    }


    public void read(int id) throws SQLException {
        DataAccessManager.getInstance().getAddOfferAssistanceTO(this, id);
    }

    public String getOrgName() {
        return orgName;
    }

    /**
     * @return
     */
    public String getAgency() {

        return agency;

    }


    /**
     * @return
     */

    public Date getDate() {

        return date;

    }


    /**
     * @return
     */

    public String getHumanResourcesCommitted() {

        return humanResourcesCommitted;

    }


    /**
     * @return
     */

    public String getNeedsAssessments() {

        return needsAssessments;

    }


    /**
     * @return
     */

    public String getOtherActivities() {

        return otherActivities;

    }


    /**
     * @return
     */

    public String getOtherIssues() {

        return otherIssues;

    }


    /**
     * @return
     */

    public String getPartners() {

        return partners;

    }


    /**
     * @return
     */

    public String getPlannedActivities() {

        return plannedActivities;

    }


    /**
     * @return
     */

    public String getReliefCommittedDetails() {

        return reliefCommittedDetails;

    }



    /**

     * @return

     */



    /**
     * @return
     */

    public String getReliefDisbursedDetails() {

        return reliefDisbursedDetails;

    }


    /**
     * @return
     */

    public String getSectors() {

        return sectors;

    }


    /**
     * @param string
     */

    public void setAgency(String string) {

        agency = string;

    }


    /**
     * @param date
     */

    public void setDate(Date date) {

        this.date = date;

    }


    /**
     * @param string
     */

    public void setHumanResourcesCommitted(String string) {
        humanResourcesCommitted = string;

    }


    /**
     * @param string
     */

    public void setNeedsAssessments(String string) {

        needsAssessments = string;

    }


    /**
     * @param string
     */

    public void setOtherActivities(String string) {

        otherActivities = string;

    }


    /**
     * @param string
     */

    public void setOtherIssues(String string) {

        otherIssues = string;

    }


    /**
     * @param string
     */

    public void setPartners(String string) {

        partners = string;

    }


    /**
     * @param string
     */

    public void setPlannedActivities(String string) {

        plannedActivities = string;

    }


    /**
     * @param string
     */

    public void setReliefCommittedDetails(String string) {

        reliefCommittedDetails = string;

    }


    /**
     * @param string
     */

    public void setReliefDisbursedDetails(String string) {

        reliefDisbursedDetails = string;

    }


    /**
     * @param string
     */

    public void setSectors(String string) {

        sectors = string;

    }


    /**
     * @return
     */

    public int getId() {

        return id;

    }


    /**
     * @param i
     */

    public void setId(int i) {

        id = i;
        unique = true;

    }


    private String addQuotes(String s) {

        return '\'' + pattern.matcher(s).replaceAll("\\\\'") + '\'';

    }


    public String getInsertSQL() {

        StringBuffer sql1 = new StringBuffer("INSERT INTO offers(");

        StringBuffer sql2 = new StringBuffer("VALUES(");

        int count = 0;


        if (agency != null) {

            sql1.append("agency, ");

            sql2.append(addQuotes(agency));

            sql2.append(", ");

            count++;

        }


        if (date != null) {

            sql1.append("date, ");

            sql2.append(addQuotes(date.toString()));

            sql2.append(", ");

            count++;

        }


        if (sectors != null) {

            sql1.append("sectors, ");

            sql2.append(addQuotes(sectors));

            sql2.append(", ");

            count++;

        }


        if (partners != null) {

            sql1.append("partners, ");

            sql2.append(addQuotes(partners));

            sql2.append(", ");

            count++;

        }


        if (reliefCommittedDetails != null) {

            sql1.append("relief_committed_details, ");

            sql2.append(addQuotes(reliefCommittedDetails));

            sql2.append(", ");

            count++;

        }


        if (reliefCommittedTotal != null) {
            sql1.append("relief_committed_total, ");
            // sql2.append(reliefCommittedTotal);
            sql2.append(reliefCommittedTotal);

            sql2.append(", ");

            count++;

        }


        if (reliefDisbursedDetails != null) {

            sql1.append("relief_disbursed_details, ");

            sql2.append(addQuotes(reliefDisbursedDetails));

            sql2.append(", ");

            count++;

        }


        if (reliefDisbursedTotal != null) {

            sql1.append("relief_disbursed_total, ");
//            System.out.println("  " + reliefDisbursedTotal);
//            sql2.append( new String(reliefDisbursedTotal.toString())) ;
            sql2.append(reliefDisbursedTotal);
            sql2.append(", ");

            count++;

        }


        if (humanResourcesCommitted != null) {

            sql1.append("human_resources_committed, ");

            sql2.append(addQuotes(humanResourcesCommitted));

            sql2.append(", ");

            count++;

        }


        if (needsAssessments != null) {

            sql1.append("needs_assessments, ");

            sql2.append(addQuotes(needsAssessments));

            sql2.append(", ");

            count++;

        }


        if (otherActivities != null) {

            sql1.append("other_activities, ");

            sql2.append(addQuotes(otherActivities));

            sql2.append(", ");

            count++;

        }


        if (plannedActivities != null) {

            sql1.append("planned_activities, ");

            sql2.append(addQuotes(plannedActivities));

            sql2.append(", ");

            count++;

        }


        if (otherIssues != null) {

            sql1.append("other_issues, ");

            sql2.append(addQuotes(otherIssues));

            sql2.append(", ");

            count++;

        }


        if (count == 0)

            throw new UnsupportedOperationException();


        sql1.setCharAt(sql1.length() - 2, ')');

        sql2.setCharAt(sql2.length() - 2, ')');

        return sql1.toString() + sql2;

    }


    public String getUpdateSQL() {

        if (!unique)

            throw new UnsupportedOperationException();


        StringBuffer sql = new StringBuffer("UPDATE offers SET ");


        sql.append("agency = ");

        if (agency != null) {

            sql.append(addQuotes(agency));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("date = ");

        if (date != null) {

            sql.append(addQuotes(date.toString()));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("sectors = ");

        if (sectors != null) {

            sql.append(addQuotes(sectors));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("partners = ");

        if (partners != null) {

            sql.append(addQuotes(partners));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("relief_committed_details = ");

        if (reliefCommittedDetails != null) {

            sql.append(addQuotes(reliefCommittedDetails));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("relief_committed_total = ");

        if (reliefCommittedTotal != null) {

            sql.append(reliefCommittedTotal);

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("relief_disbursed_details = ");

        if (reliefDisbursedDetails != null) {

            sql.append(addQuotes(reliefDisbursedDetails));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("relief_disbursed_total = ");

        if (reliefDisbursedTotal != null) {

            sql.append(reliefDisbursedTotal);

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("human_resources_committed = ");

        if (humanResourcesCommitted != null) {

            sql.append(addQuotes(humanResourcesCommitted));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("needs_assessments = ");

        if (needsAssessments != null) {

            sql.append(addQuotes(needsAssessments));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("other_activities = ");

        if (otherActivities != null) {

            sql.append(addQuotes(otherActivities));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("planned_activities = ");

        if (plannedActivities != null) {

            sql.append(addQuotes(plannedActivities));

            sql.append(", ");

        } else

            sql.append("NULL, ");


        sql.append("other_issues = ");

        if (otherIssues != null) {

            sql.append(addQuotes(otherIssues));

            sql.append(" ");

        } else

            sql.append("NULL ");


        sql.append("WHERE id = " + id);


        return sql.toString();

    }


    public String getDeleteSQL() {

        if (unique)

            return "DELETE FROM offers WHERE id = " + id;

        else

            throw new UnsupportedOperationException();

    }

    public void setUnique(boolean isUnique) {
        this.unique = isUnique;
    }

}

