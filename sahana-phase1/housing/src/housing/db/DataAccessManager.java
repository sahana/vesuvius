package org.housing.db;

import org.sahana.share.db.AbstractDataAccessManager;
import org.sahana.share.db.DBConnection;
import org.sahana.share.db.DBConstants;
import org.sahana.share.utils.KeyValueDTO;

import java.sql.*;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ArrayList;

/**
 * Created by IntelliJ IDEA.
 * User: nithyakala
 * Date: Jan 18, 2005
 * Time: 4:36:35 PM
 * To change this template use File | Settings | File Templates.
 */


import org.sahana.share.db.AbstractDataAccessManager;
import org.sahana.share.db.DBConstants;
import org.sahana.share.db.DBConnection;
import org.sahana.share.utils.KeyValueDTO;
import org.housing.business.LandTO;
import org.housing.util.LabelValue;

import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;


/**
 * @author Administrator
 *         <p/>
 *         <p/>
 *         <p/>
 *         To change the template for this generated type comment go to
 *         <p/>
 *         Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

public class DataAccessManager extends AbstractDataAccessManager{
    public DataAccessManager() throws Exception {
        super();
    }

    /**
     * Method to add a request.
     *
     * @param request The Request value object which will contain the data that needs to be saved.
     * @throws Exception
     */

    public boolean addLand(LandTO landTO) throws Exception {

       boolean isCommited=false;

        Connection connection = null;

        PreparedStatement preparedStatement = null;

        ResultSet resultSet = null;


        try {

            connection = DBConnection.createConnection();

            connection.setAutoCommit(false);

            // Setting the Request Header data.

            String sqlAddRequestHeaderString = SQLGenerator.getSQLAddLand();

            preparedStatement = connection.prepareStatement(sqlAddRequestHeaderString);

            preparedStatement.setString(1, landTO.getLandName());

            preparedStatement.setInt(2,Integer.parseInt(landTO.getDivisionId()));

            preparedStatement.setString(3, landTO.getDescription());

            preparedStatement.setInt(4, Integer.parseInt(landTO.getAreaId()));

            preparedStatement.setString(5, landTO.getGPS1());

            preparedStatement.setString(6, landTO.getGPS2());

            preparedStatement.setString(7, landTO.getGPS3());

            preparedStatement.setString(8, landTO.getGPS4());

            preparedStatement.setDouble(9, Double.parseDouble(landTO.getMeasurement()));

            preparedStatement.setInt(10,Integer.parseInt(landTO.getTermId()));

            preparedStatement.setInt(11,Integer.parseInt(landTO.getOwnedById()));

            preparedStatement.setString(12,landTO.getOwnedByComment());

            System.out.println("Term id ...."+landTO.getTermId());
            System.out.println("oenws id ...."+landTO.getOwnedById());
            System.out.println("desc  own...."+landTO.getOwnedByComment());
            
            preparedStatement.executeUpdate();

            //System.out.println("checking llllllllllllllllllllllllllllllll");
            // Getting the generated Key from the above statement

            ResultSet generatedKeys = preparedStatement.getGeneratedKeys();


            String generatedKey = new String();


            if (generatedKeys.next()) // We're expecting just one auto genrated key
            {

                generatedKey = generatedKeys.getObject(1).toString();

            }
            // If all is ok then commit.

            connection.commit();

            connection.setAutoCommit(true);

            isCommited=true;

        } catch (Exception e) {

            System.out.println("Exception!!!");

            try {

                if (connection != null)

                // Since an exception has occured lets roll back the partially inserted record.
                {

                    System.out.println("About to rollback");

                    connection.rollback();

                    connection.setAutoCommit(true);

                    System.out.println("After roll back");

                }

            } catch (SQLException e1) {

                System.out.println("rollback exception");

                e1.printStackTrace();

                throw e1;

            }

            e.printStackTrace();

            throw e;

        } finally {

            closeConnections(connection, preparedStatement, resultSet);

            return isCommited;

        }
    }


      public List listDivisions()
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);
            System.out.println("connection **************");
            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForAllDivisions();
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("DIV_NAME");
                String value = resultSet.getString("DIV_ID");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    public List listArea()
               throws SQLException, Exception {
           Connection connection = null;
           PreparedStatement preparedStatement = null;
           ResultSet resultSet = null;

           try {
               connection = DBConnection.createConnection();
               //connection.setAutoCommit(false);

               //todo: modify to optimize preparedStatement
               String sqlString = SQLGenerator.getSQLForAllAreas();
               preparedStatement = connection.prepareStatement(sqlString);

               resultSet = preparedStatement.executeQuery();

               List list = new ArrayList();

               while (resultSet.next()) {
                   String label = resultSet.getString("MEASUREMENT");
                   String value = resultSet.getString("AREA_ID");
                   list.add(new LabelValue(label, value));
               }

               return list;
           } finally {
               closeConnections(connection, preparedStatement, resultSet);
           }
       }

    public List listTerms()
                   throws SQLException, Exception {
               Connection connection = null;
               PreparedStatement preparedStatement = null;
               ResultSet resultSet = null;

               try {
                   connection = DBConnection.createConnection();
                   //connection.setAutoCommit(false);

                   //todo: modify to optimize preparedStatement
                   String sqlString = SQLGenerator.getSQLForAllTerms();
                   preparedStatement = connection.prepareStatement(sqlString);

                   resultSet = preparedStatement.executeQuery();

                   List list = new ArrayList();

                   while (resultSet.next()) {
                       String label = resultSet.getString("DESCRIPTION");
                       String value = resultSet.getString("TERM_ID");
                       list.add(new LabelValue(label, value));
                   }

                   return list;
               } finally {
                   closeConnections(connection, preparedStatement, resultSet);
               }
           }

           public List listOwnedBy()
                      throws SQLException, Exception {
                  Connection connection = null;
                  PreparedStatement preparedStatement = null;
                  ResultSet resultSet = null;

                  try {
                      connection = DBConnection.createConnection();
                      //connection.setAutoCommit(false);

                      //todo: modify to optimize preparedStatement
                      String sqlString = SQLGenerator.getSQLForAllOwnedBy();
                      preparedStatement = connection.prepareStatement(sqlString);

                      resultSet = preparedStatement.executeQuery();

                      List list = new ArrayList();

                      while (resultSet.next()) {
                          String label = resultSet.getString("OWNED_BY_NAME");
                          String value = resultSet.getString("OWNED_BY_ID");
                          list.add(new LabelValue(label, value));
                      }

                      return list;
                  } finally {
                      closeConnections(connection, preparedStatement, resultSet);
                  }
              }





}