package org.assistance.db;


import org.assistance.business.AddOfferAssistanceTO;
import org.assistance.business.SearchRequestTo;

import org.assistance.model.User;


import java.sql.*;

import java.util.ArrayList;

import java.util.List;
import java.util.Collection;


/*

 * Created on Jan 2, 2005

 *

 */


public class DataAccessManager {

    private static final String dbUserName = DBConstantLoader.getDbUserName();


    private static final String dbPassword = DBConstantLoader.getDbPassword();


    private static final String dbURLConnectionString = DBConstantLoader.getDbUrl();


    private static final String dbDriver = DBConstantLoader.getDbDriver();


    private static DataAccessManager instance = null;


    private DataAccessManager() {
    }


    public static DataAccessManager getInstance() {

        if (instance == null)

            instance = new DataAccessManager();

        return instance;

    }


    private Connection createConnection() throws SQLException {

        String userName = dbUserName;

        String password = dbPassword;

        String url = dbURLConnectionString;


        try {

            Class.forName(dbDriver).newInstance();

        } catch (Exception e) {

            e.printStackTrace();

            throw new RuntimeException(e);

        }


        return DriverManager.getConnection(url, userName, password);

    }


    public ResultSet executeQuery(Statement stmt, String sql) throws SQLException {

        return stmt.executeQuery(sql);

    }


    protected int executeUpdate(String sql) throws SQLException {

        Statement stmt = null;
        Connection con = null;

        try {
            con = createConnection();
            stmt = con.createStatement();
            return stmt.executeUpdate(sql);
        } finally {
            close(con, stmt, null);
        }

    }


    public boolean insert(AddOfferAssistanceTO tuple) throws SQLException {

        ResultSet rs = null;

        Connection connection = createConnection();
        Statement stmt = connection.createStatement();

        try {

            if (stmt.executeUpdate(tuple.getInsertSQL()) == 1) {

                rs = stmt.executeQuery("SELECT LAST_INSERT_ID()");

                if (rs.next()) {

                    tuple.setId(rs.getInt(1));

                    return true;

                }

            }

            return false;

        } finally {

            close(connection, stmt, rs);

        }

    }


    public boolean delete(AddOfferAssistanceTO tuple) throws SQLException {

        return executeUpdate(tuple.getDeleteSQL()) == 1;

    }


    public boolean update(AddOfferAssistanceTO tuple) throws SQLException {

        return executeUpdate(tuple.getUpdateSQL()) == 1;

    }


    private List fetchOffers(String sql) throws SQLException {

        List list = new ArrayList();

        Connection con = createConnection();
        Statement stmt = con.createStatement();
        ResultSet rs = executeQuery(stmt, sql);

        while (rs.next())

            list.add(new AddOfferAssistanceTO(rs));

        close(con, stmt, rs);

        return list;

    }


    public List getAllOffers() throws SQLException {

        return fetchOffers("SELECT * FROM offers JOIN organization ON agency = OrgCode");

    }


    /*
public AddOfferAssistanceTO getOfferById(int id) throws SQLException {

 List list= fetchOffers("SELECT * FROM offers WHERE id = "+id);
 if (list.size() == 1)
     return (AddOfferAssistanceTO)list.get(0);
 else
     throw new IllegalArgumentException();
}
      */



    private void close(Connection con, Statement stmt, ResultSet rs) throws SQLException {

        if (stmt != null) {
            stmt.close();
        }
        if (rs != null) {
            rs.close();
        }
        if (con != null) {
            con.close();
        }
    }


    public User loginSuccess(String userName, String password) throws SQLException, Exception {
        Connection conn = createConnection();
        Statement s = null;
        ResultSet rs = null;
        try {
            String sql = SQLGenerator.getSQLForLogin(userName);
            s = conn.createStatement();
            rs = s.executeQuery(sql);
            if (rs.next()) {
                String realpassword = rs.getString(2);
                String orgCode = rs.getString(3);
                String organization = rs.getString(4);
                System.out.println(realpassword);
                System.out.println(organization);
                User user = new User(userName, organization);
                user.setOrgCode(orgCode);
                if (realpassword.equals(password)) {
                    return user;
                }
            }

        } finally {
            close(conn, s, rs);
        }

        return null;
    }

    public AddOfferAssistanceTO getAddOfferAssistanceTO(AddOfferAssistanceTO to, int id) throws SQLException {

        Connection con = null;
        Statement stmt = null;
        ResultSet rs = null;

        try {
            con = createConnection();
            stmt = con.createStatement();
            String queryString = "SELECT * FROM offers JOIN organization ON agency = OrgCode WHERE id = " + id;
            rs = executeQuery(stmt, queryString);

            if (rs.next()) {
                to.setUnique(true);

                to.setId(rs.getInt(1));

                to.setAgency(rs.getString(2));

                to.setDate(rs.getDate(3));

                to.setSectors(rs.getString(4));

                to.setPartners(rs.getString(5));

                to.setReliefCommittedDetails(rs.getString(6));

                to.setReliefCommittedTotal(rs.getString(7));

                to.setReliefDisbursedDetails(rs.getString(8));

                to.setReliefDisbursedTotal(rs.getString(9));

                to.setHumanResourcesCommitted(rs.getString(10));

                to.setNeedsAssessments(rs.getString(11));

                to.setOtherActivities(rs.getString(12));

                to.setPlannedActivities(rs.getString(13));

                to.setOtherIssues(rs.getString(14));

                to.setOrgName(rs.getString(15));

            }

        } finally {
            close(con, stmt, rs);
        }
        return to;
    }

    public Collection searchOffers(SearchRequestTo req) throws SQLException {
        Collection results = new ArrayList();
        String sql = SQLGenerator.getSQLForSearchCriteria();
        Connection con = createConnection();
        PreparedStatement st = con.prepareStatement(sql);

        st.setString(0, req.getAgancy());
        st.setString(1, req.getAgancy());
        st.setString(2, req.getPartners());
        st.setString(3, req.getPartners());
        st.setDate(4, req.getRequestDateFrom());
        st.setDate(5, req.getRequestDateTo());
        st.setDate(6, req.getRequestDateFrom());
        st.setDate(7, req.getRequestDateTo());

        ResultSet resultSet = st.executeQuery();

        while (resultSet.next()) {
            AddOfferAssistanceTO offer = new AddOfferAssistanceTO();
            offer.setId(Integer.parseInt(resultSet.getString(DBConstants.TableColumns.OFFER_ID)));

            offer.setAgency(resultSet.getString(DBConstants.TableColumns.OFFER_AGANCY));

            offer.setDate(resultSet.getDate((DBConstants.TableColumns.OFFER_DATE)));

            offer.setSectors(resultSet.getString(DBConstants.TableColumns.OFFER_SECTOR));

            offer.setPartners(resultSet.getString(DBConstants.TableColumns.OFFER_PARTNERS));

            offer.setReliefCommittedDetails(resultSet.getString(DBConstants.TableColumns.OFFER_RELIEF_COMMITED_DETAIL));

            offer.setReliefCommittedTotal(resultSet.getString(DBConstants.TableColumns.OFFER_RELIEF_COMMITED_TOTEL));

            offer.setReliefDisbursedDetails(resultSet.getString(DBConstants.TableColumns.OFFER_RELIEF_DISBURSED_DETAIL));

            offer.setReliefDisbursedTotal(resultSet.getString(DBConstants.TableColumns.OFFER_RELIEF_DISBURSED_TOTEL));

            offer.setHumanResourcesCommitted(resultSet.getString(DBConstants.TableColumns.OFFER_HR_COMMITED));

            offer.setNeedsAssessments(resultSet.getString(DBConstants.TableColumns.OFFER_NEEDSASSESMENT));

            offer.setOtherActivities(resultSet.getString(DBConstants.TableColumns.OFFER_OTHER_ACTIVITIES));

            offer.setPlannedActivities(resultSet.getString(DBConstants.TableColumns.OFFER_PLANNED_ACTIVITES));

            offer.setOtherIssues(resultSet.getString(DBConstants.TableColumns.OFFER_OTHER_ISSUES));

            results.add(offer);
        }
        return results;

    }


}

