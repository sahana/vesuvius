package org.housing.landreg.db;

import org.sahana.share.db.AbstractDataAccessManager;
import org.sahana.share.db.DBConnection;
import org.sahana.share.db.DBConstants;
import org.sahana.share.utils.KeyValueDTO;

import java.sql.*;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;
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
import org.housing.landreg.business.LandTO;
import org.housing.landreg.util.LabelValue;

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

            preparedStatement.setString(1, landTO.getPlanId());

            preparedStatement.setString(2, landTO.getLandName());

            preparedStatement.setInt(3,Integer.parseInt(landTO.getSubDivisionId()));

            preparedStatement.setString(4, landTO.getDescription());

            //preparedStatement.setInt(5, Integer.parseInt(landTO.getMeasurementTypeId()));

            preparedStatement.setString(5, landTO.getGPS1());

            preparedStatement.setString(6, landTO.getGPS2());

            preparedStatement.setString(7, landTO.getGPS3());

            preparedStatement.setString(8, landTO.getGPS4());

            preparedStatement.setDouble(9, Double.parseDouble(landTO.getArea()));

            preparedStatement.setDouble(10, Double.parseDouble(landTO.getArea1()));

            preparedStatement.setDouble(11, Double.parseDouble(landTO.getArea2()));

            preparedStatement.setInt(12,Integer.parseInt(landTO.getTermId()));

            preparedStatement.setInt(13,Integer.parseInt(landTO.getOwnedById()));

            preparedStatement.setString(14,landTO.getOwnedByComment());

            preparedStatement.setInt(15,Integer.parseInt(landTO.getLandTypeId()));

            preparedStatement.setInt(16,Integer.parseInt(landTO.getInfractureId()));

            preparedStatement.setString(17, landTO.getProposedUseAsPerZonPlan());

            preparedStatement.setString(18, landTO.getRemarks());

            preparedStatement.executeUpdate();

            //System.out.println("checking llllllllllllllllllllllllllllllll");
            // Getting the generated Key from the above statement

            ResultSet generatedKeys = preparedStatement.getGeneratedKeys();

            String generatedKey = new String();

            if (generatedKeys.next()) // We're expecting just one auto genrated key
            {

                generatedKey = generatedKeys.getObject(1).toString();
            }

             String infractureId="";
             boolean inserted = false;
             String strInfractureName = landTO.getInfractureIds();

             System.out.println(strInfractureName+" ");

             StringTokenizer st = new StringTokenizer(strInfractureName,"_");

             while ( st.hasMoreTokens() )
             {
                 infractureId = st.nextToken();
                 inserted = addLandInfracture(landTO,generatedKey,infractureId);
             }

             if (inserted)
             {

             // If all is ok then commit.

             connection.commit();

             connection.setAutoCommit(true);

             isCommited=true;

            }

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

    public boolean addLandInfracture(LandTO landTO, String landId ,String infractureId) throws Exception {

       boolean isCommited=false;

        Connection connection = null;

        PreparedStatement preparedStatement = null;

        ResultSet resultSet = null;


        try {

            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);
            // Setting the Request Header data.
            String sqlAddRequestHeaderString = SQLGenerator.getSQLAddLandInfracture();
            preparedStatement = connection.prepareStatement(sqlAddRequestHeaderString);
            preparedStatement.setInt(1,Integer.parseInt(landId));
            preparedStatement.setInt(2,Integer.parseInt(infractureId));
            preparedStatement.executeUpdate();

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

    public List listAllInfractureNameForLandIds(String landId)
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            // Setting the Request Header data.
            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForInfractuteListforLand(landId);
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("INFRACTURE_ID");
                String value = resultSet.getString("INFRACTURE_DESC");
                list.add(new LabelValue(label,value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }

    public List listGNDforDivisions(String divCode)
                throws SQLException, Exception {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;

            try {
                connection = DBConnection.createConnection();
                //connection.setAutoCommit(false);

                // Setting the Request Header data.
                //todo: modify to optimize preparedStatement
                String sqlString = SQLGenerator.getSQLForSubDivisionListforDivision(divCode);
                preparedStatement = connection.prepareStatement(sqlString);

                resultSet = preparedStatement.executeQuery();

                List list = new ArrayList();

                while (resultSet.next()) {
                    String label = resultSet.getString("SUB_DIV_NAME");
                    String value = resultSet.getString("SUB_DIV_ID");
                    list.add(new LabelValue(label, value));
                }

                return list;
            } finally {
                closeConnections(connection, preparedStatement, resultSet);
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

     public List listDistrict()
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);
            System.out.println("connection **************");
            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForAllDistricts();
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("DIST_NAME");
                String value = resultSet.getString("DIST_CODE");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }


    public List listProvicences()
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForAllProvinces();
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("PROV_NAME");
                String value = resultSet.getString("PROV_CODE");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }


    public List listDivisionsforDistrcit(String disstrictName)
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            // Setting the Request Header data.
            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForDivisionListforDistrict(disstrictName);
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


    public List listDistrictwithProvince(String provinceID)
            throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DBConnection.createConnection();
            //connection.setAutoCommit(false);

            //todo: modify to optimize preparedStatement
            String sqlString = SQLGenerator.getSQLForDistrictListWithProvince(provinceID);
            preparedStatement = connection.prepareStatement(sqlString);

            resultSet = preparedStatement.executeQuery();

            List list = new ArrayList();

            while (resultSet.next()) {
                String label = resultSet.getString("DIST_NAME");
                String value = resultSet.getString("DIST_CODE");
                list.add(new LabelValue(label, value));
            }

            return list;
        } finally {
            closeConnections(connection, preparedStatement, resultSet);
        }
    }


    public List listMeasurementTypes()
               throws SQLException, Exception {
           Connection connection = null;
           PreparedStatement preparedStatement = null;
           ResultSet resultSet = null;

           try {
               connection = DBConnection.createConnection();
               //connection.setAutoCommit(false);

               //todo: modify to optimize preparedStatement
               String sqlString = SQLGenerator.getSQLForAllMeasurementType();
               preparedStatement = connection.prepareStatement(sqlString);

               resultSet = preparedStatement.executeQuery();

               List list = new ArrayList();

               while (resultSet.next()) {
                   String label = resultSet.getString(DBConstants.MeasurementType.MEASUREMENT_TYPE_NAME);
                   String value = resultSet.getString(DBConstants.MeasurementType.MEASUREMENT_TYPE_ID);
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

        public List listLandType()
                      throws SQLException, Exception {
                  Connection connection = null;
                  PreparedStatement preparedStatement = null;
                  ResultSet resultSet = null;

                  try {
                      connection = DBConnection.createConnection();
                      //connection.setAutoCommit(false);

                      //todo: modify to optimize preparedStatement
                      String sqlString = SQLGenerator.getSQLForAllLandType();
                      preparedStatement = connection.prepareStatement(sqlString);

                      resultSet = preparedStatement.executeQuery();

                      List list = new ArrayList();

                      while (resultSet.next()) {
                          String label = resultSet.getString("LAND_TYPE_NAME");
                          String value = resultSet.getString("LAND_TYPE_ID");
                          list.add(new LabelValue(label, value));
                      }

                      return list;
                  } finally {
                      closeConnections(connection, preparedStatement, resultSet);
                  }
              }

        public List listInfrastructures()
                      throws SQLException, Exception {
                  Connection connection = null;
                  PreparedStatement preparedStatement = null;
                  ResultSet resultSet = null;

                  try {
                      connection = DBConnection.createConnection();
                      //connection.setAutoCommit(false);

                      //todo: modify to optimize preparedStatement
                      String sqlString = SQLGenerator.getSQLForAllInfracture();
                      preparedStatement = connection.prepareStatement(sqlString);

                      resultSet = preparedStatement.executeQuery();

                      List list = new ArrayList();

                      while (resultSet.next()) {
                          String label = resultSet.getString("INFRACTURE_DESC");
                          String value = resultSet.getString("INFRACTURE_ID");
                          list.add(new LabelValue(label, value));
                      }

                      return list;
                  } finally {
                      closeConnections(connection, preparedStatement, resultSet);
                  }
         }

          public List listProviences()
                   throws SQLException, Exception {
               Connection connection = null;
               PreparedStatement preparedStatement = null;
               ResultSet resultSet = null;

               try {
                   connection = DBConnection.createConnection();
                   //connection.setAutoCommit(false);

                   //todo: modify to optimize preparedStatement
                   String sqlString = SQLGenerator.getSQLForAllProvinces();
                   preparedStatement = connection.prepareStatement(sqlString);
                   resultSet = preparedStatement.executeQuery();

                   List list = new ArrayList();

                   while (resultSet.next()) {
                       String label = resultSet.getString("PROV_NAME");
                       String value = resultSet.getString("PROV_CODE");
                       list.add(new LabelValue(label, value));
                   }

                   return list;
               } finally {
                   closeConnections(connection, preparedStatement, resultSet);
               }
           }

    public List validateLandTOforInsert(LandTO landTO) throws SQLException, Exception {
           List result = landTO.validate();

           return result;
       }

//    public LandTO searchLand(int landId)
//                throws SQLException, Exception {
//            Connection connection = null;
//            PreparedStatement preparedStatement = null;
//            ResultSet resultSet = null;
//
//            try {
//                connection = DBConnection.createConnection();
//                //connection.setAutoCommit(false);
//
//                String sqlString = SQLGenerator.getSQLForSearchCriteria(landId);
//                preparedStatement = connection.prepareStatement(sqlString);
//
//                resultSet = preparedStatement.executeQuery();
//
//                LandTO landTO = null;
//
//                if (resultSet.next()) {
//                    landTO = new LandTO();
//                    landTO.setLandId(resultSet.getString(DBConstants.Land.LAND_ID));
//                    landTO.setLandName(resultSet.getString(DBConstants.Land.LAND_NAME));
//                    landTO.setDivisionId(resultSet.getString(DBConstants.Land.DIVISION_ID));
//                    landTO.setDescription(resultSet.getString(DBConstants.Land.DESCRIPTION));
//                    landTO.setMeasurementTypeId(resultSet.getString(DBConstants.Land.MEASUREMENT_TYPE_ID));
//                    landTO.setGPS1(resultSet.getString(DBConstants.Land.GPS1));
//                    landTO.setGPS2(resultSet.getString(DBConstants.Land.GPS2));
//                    landTO.setGPS3(resultSet.getString(DBConstants.Land.GPS3));
//                    landTO.setGPS4(resultSet.getString(DBConstants.Land.GPS4));
//                    landTO.setArea(resultSet.getString(DBConstants.Land.AREA));
//                    landTO.setTermId(resultSet.getString(DBConstants.Land.TERM_ID));
//                    landTO.setOwnedById(resultSet.getString(DBConstants.Land.OWNED_BY_ID));
//                    landTO.setownedByComment(resultSet.getString(DBConstants.Land.OWNED_BY_COMMENT));
//
//                } else {
//                    return null;
//                }
//                //todo: should use outer joint
//                sqlString = SQLGenerator.getSQLForProvienceName(landTO.getProvinceCode());
//                preparedStatement = connection.prepareStatement(sqlString);
//                resultSet = preparedStatement.executeQuery();
//                if (resultSet.next()) {
//                    landTO.setProvinceName(resultSet.getString(DBConstants.Province.PROV_NAME));
//                }
//
//                sqlString = SQLGenerator.getSQLForDistrictName(landTO.getDistrictId());
//                preparedStatement = connection.prepareStatement(sqlString);
//                resultSet = preparedStatement.executeQuery();
//                if (resultSet.next()) {
//                    landTO.setDistrictName(resultSet.getString(DBConstants.District.DIST_NAME));
//                }
//
//                sqlString = SQLGenerator.getSQLForDivisionName(Integer.parseInt(landTO.getDivisionId()));
//                preparedStatement = connection.prepareStatement(sqlString);
//                resultSet = preparedStatement.executeQuery();
//                if (resultSet.next()) {
//                    landTO.setDivisionName(resultSet.getString(DBConstants.Division.DIV_NAME));
//                }
//
//                sqlString = SQLGenerator.getSQLForDivisionName(Integer.parseInt(landTO.getDivisionId()));
//                preparedStatement = connection.prepareStatement(sqlString);
//                resultSet = preparedStatement.executeQuery();
//                if (resultSet.next()) {
//                    landTO.setDivisionName(resultSet.getString(DBConstants.Division.DIV_NAME));
//                }
//
//                sqlString = SQLGenerator.getSQLForDivisionName(Integer.parseInt(landTO.getDivisionId()));
//                preparedStatement = connection.prepareStatement(sqlString);
//                resultSet = preparedStatement.executeQuery();
//                if (resultSet.next()) {
//                    landTO.setDivisionName(resultSet.getString(DBConstants.Division.DIV_NAME));
//                }
//
//
//                return landTO;
//            } finally {
//                closeConnections(connection, preparedStatement, resultSet);
//            }
//        }


   public String getDivNameByDivId(int divId)
                throws SQLException, Exception {

        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

            try {
                connection = DBConnection.createConnection();

                // Setting the Request Header data.
                String sqlSearchString = SQLGenerator.getSQLForDivisionName(divId);

                System.out.println("sss "+ sqlSearchString);

                 preparedStatement = connection.prepareStatement(sqlSearchString);
                 resultSet = preparedStatement.executeQuery();

               return resultSet.getString(DBConstants.Land.AREA);

            } finally {
                closeConnections(connection, preparedStatement, resultSet);
            }
    }

  

    public List searchLands(String landName,String planId,String description,String subDivisionId,String landTypeId,
                            String infractureId,String infractureIds,
                            String ownedById,String termId, String area,String area1,String area2,String measurementTypeId,
                            String remarks,String proposedAsPerZonPlan )
                throws SQLException, Exception {

        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

            try {
                connection = DBConnection.createConnection();

                // Setting the Request Header data.
                String sqlSearchString = SQLGenerator.getSQLForSearchCriteria(landName,planId,description,
                       subDivisionId,landTypeId,infractureId,infractureIds,ownedById, termId,area,area1,area2, measurementTypeId,remarks,proposedAsPerZonPlan);

                System.out.println("s_criteria "+ sqlSearchString);

                 preparedStatement = connection.prepareStatement(sqlSearchString);
                 resultSet = preparedStatement.executeQuery();

                List returnSearchTOs = new ArrayList();
                LandTO landTO;

                while (resultSet.next()) {
                    landTO = new LandTO();

                    landTO.setLandName(resultSet.getString(DBConstants.Land.LAND_NAME));
                    landTO.setPlanId(resultSet.getString(DBConstants.Land.PLAN_NO));
                    landTO.setArea(resultSet.getString(DBConstants.Land.AREA));
                    landTO.setArea1(resultSet.getString(DBConstants.Land.AREA1));
                    landTO.setArea2(resultSet.getString(DBConstants.Land.AREA2));
                    landTO.setDescription(resultSet.getString("LAND_DESCRIPTION"));

                    landTO.setDistrictId(resultSet.getString(DBConstants.District.DIST_CODE));
                    landTO.setDistrictName(resultSet.getString(DBConstants.District.DIST_NAME));

                    landTO.setDivisionId(resultSet.getString(DBConstants.Division.DIV_ID));
                    landTO.setDivisionName(resultSet.getString(DBConstants.Division.DIV_NAME));

                    landTO.setSubDivisionId(resultSet.getString(DBConstants.Land.SUB_DIVISION_ID));
                    landTO.setSubDivisionName(resultSet.getString(DBConstants.SubDivision.SUB_DIV_NAME));

                    landTO.setGPS1(resultSet.getString(DBConstants.Land.GPS1));
                    landTO.setGPS2(resultSet.getString(DBConstants.Land.GPS2));
                    landTO.setGPS3(resultSet.getString(DBConstants.Land.GPS3));
                    landTO.setGPS4(resultSet.getString(DBConstants.Land.GPS4));
                    landTO.setLandId(resultSet.getString(DBConstants.Land.LAND_ID));
                    //landTO.setMeasurementTypeId(resultSet.getString(DBConstants.Land.MEASUREMENT_TYPE_ID));
                    //landTO.setMeasurementTypeName(resultSet.getString(DBConstants.MeasurementType.MEASUREMENT_TYPE_NAME));
                    landTO.setownedByComment(resultSet.getString(DBConstants.Land.OWNED_BY_COMMENT));
                    landTO.setOwnedById(resultSet.getString(DBConstants.Land.OWNED_BY_ID));
                    landTO.setOwnedByName(resultSet.getString(DBConstants.OwnedBy.OWNED_BY_NAME));
                    landTO.setProvinceCode(resultSet.getString(DBConstants.Province.PROV_CODE));
                    landTO.setProvinceName(resultSet.getString(DBConstants.Province.PROV_NAME));
                    landTO.setTermId(resultSet.getString(DBConstants.Land.TERM_ID));

                    landTO.setTermName(resultSet.getString("TERM_DESCRIPTION"));
                    landTO.setLandTypeId(resultSet.getString(DBConstants.Land.LAND_TYPE));
                    landTO.setLandTypeName(resultSet.getString("LANDTYPE_DESCRIPTION"));
                    // landTO.setInfractureId(resultSet.getString(DBConstants.Land.INFRACTURE));
                    //landTO.setInfractureIds(resultSet.getString(DBConstants.Land.INFRACTURE));
                    landTO.setInfractureName(resultSet.getString("INFRACTURE_DESCRIPTION"));
                    landTO.setProposedUseAsPerZonPlan(resultSet.getString(DBConstants.Land.PROPOSED_USE_ASPERZONPLAN));
                    landTO.setRemarks(resultSet.getString(DBConstants.Land.REMARKS));
                    returnSearchTOs.add(landTO);
                }
                return returnSearchTOs;
            } finally {
                closeConnections(connection, preparedStatement, resultSet);

            }
    }

    public LandTO searchLand(int landId)
                    throws SQLException, Exception {

            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;

                try {
                    connection = DBConnection.createConnection();

                    // Setting the Request Header data.
                    String sqlSearchString = SQLGenerator.getSQLForSearchCriteria(landId);

                     preparedStatement = connection.prepareStatement(sqlSearchString);
                     resultSet = preparedStatement.executeQuery();

//                    List returnSearchTOs = new ArrayList();
                    LandTO landTO;
                    landTO = new LandTO();

                    while (resultSet.next()) {

                        landTO.setLandName(resultSet.getString(DBConstants.Land.LAND_NAME));
                        landTO.setPlanId(resultSet.getString(DBConstants.Land.PLAN_NO));
                        landTO.setArea(resultSet.getString(DBConstants.Land.AREA));
                        landTO.setArea1(resultSet.getString(DBConstants.Land.AREA1));
                        landTO.setArea2(resultSet.getString(DBConstants.Land.AREA2));
                        landTO.setDescription(resultSet.getString("LAND_DESCRIPTION"));
                        landTO.setDistrictId(resultSet.getString(DBConstants.District.DIST_CODE));
                        landTO.setDistrictName(resultSet.getString(DBConstants.District.DIST_NAME));
                        //landTO.setDivisionId(resultSet.getString(DBConstants.Land.DIVISION_ID));
                        //landTO.setDivisionName(resultSet.getString(DBConstants.Division.DIV_NAME));

                        landTO.setDivisionId(resultSet.getString(DBConstants.Division.DIV_ID));
                        landTO.setDivisionName(resultSet.getString(DBConstants.Division.DIV_NAME));
                        landTO.setSubDivisionId(resultSet.getString(DBConstants.Land.SUB_DIVISION_ID));
                        landTO.setSubDivisionName(resultSet.getString(DBConstants.SubDivision.SUB_DIV_NAME));

                        landTO.setGPS1(resultSet.getString(DBConstants.Land.GPS1));
                        landTO.setGPS2(resultSet.getString(DBConstants.Land.GPS2));
                        landTO.setGPS3(resultSet.getString(DBConstants.Land.GPS3));
                        landTO.setGPS4(resultSet.getString(DBConstants.Land.GPS4));
                        landTO.setLandId(resultSet.getString(DBConstants.Land.LAND_ID));
                       // landTO.setMeasurementTypeId(resultSet.getString(DBConstants.Land.MEASUREMENT_TYPE_ID));
                        //landTO.setMeasurementTypeName(resultSet.getString(DBConstants.MeasurementType.MEASUREMENT_TYPE_NAME));
                        landTO.setownedByComment(resultSet.getString(DBConstants.Land.OWNED_BY_COMMENT));
                        landTO.setOwnedById(resultSet.getString(DBConstants.Land.OWNED_BY_ID));
                        landTO.setOwnedByName(resultSet.getString(DBConstants.OwnedBy.OWNED_BY_NAME));
                        landTO.setProvinceCode(resultSet.getString(DBConstants.Province.PROV_CODE));
                        landTO.setProvinceName(resultSet.getString(DBConstants.Province.PROV_NAME));
                        landTO.setTermId(resultSet.getString(DBConstants.Land.TERM_ID));
                        landTO.setTermName(resultSet.getString("TERM_DESCRIPTION"));
                        landTO.setLandTypeId(resultSet.getString(DBConstants.Land.LAND_TYPE));
                        landTO.setLandTypeName(resultSet.getString("LANDTYPE_DESCRIPTION"));
                       // landTO.setInfractureId(resultSet.getString(DBConstants.Land.INFRACTURE));
                        landTO.setInfractureName(resultSet.getString("INFRACTURE_DESCRIPTION"));
                        landTO.setProposedUseAsPerZonPlan(resultSet.getString(DBConstants.Land.PROPOSED_USE_ASPERZONPLAN));
                        landTO.setRemarks(resultSet.getString(DBConstants.Land.REMARKS));

//                        returnSearchTOs.add(landTO);
                    }

                    return landTO;
                } finally {
                    closeConnections(connection, preparedStatement, resultSet);


                }
        }

        public boolean editLand(LandTO landTO) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement pstmt = null;
        boolean returnValue = false;

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);

            String sqlString = SQLGenerator.getSQLEditLand();
            pstmt = connection.prepareStatement(sqlString);

            //get the original data
//            LandTO tempLandTO = searchLand(Integer.parseInt(landTO.getLandId()));

            pstmt.setString(1, landTO.getLandName());
            pstmt.setString(2, landTO.getSubDivisionId());
            pstmt.setString(3, landTO.getDescription());
           // pstmt.setString(4, landTO.getMeasurementTypeId());
            pstmt.setString(4, landTO.getGPS1());
            pstmt.setString(5, landTO.getGPS2());
            pstmt.setString(6, landTO.getGPS3());
            pstmt.setString(7, landTO.getGPS4());
            pstmt.setString(8, landTO.getArea());
            pstmt.setString(9, landTO.getArea1());
            pstmt.setString(10, landTO.getArea2());
            pstmt.setString(11,landTO.getTermId());
            pstmt.setString(12,landTO.getOwnedById());
            pstmt.setString(13,landTO.getOwnedByComment());
            pstmt.setInt(14,Integer.parseInt(landTO.getLandTypeId()));
            pstmt.setInt(15,Integer.parseInt(landTO.getInfractureId()));
            pstmt.setString(16, landTO.getProposedUseAsPerZonPlan());
            pstmt.setString(17, landTO.getRemarks());
            pstmt.setString(18, landTO.getPlanId());
            pstmt.setInt(19, Integer.parseInt(landTO.getLandId()));

            pstmt.execute();

            //connection.commit();
            //returnValue = true;

             String infractureId="";

             returnValue = removeLandInfrastructure(landTO);
             System.out.println(returnValue +"remove result true or false .................");

             String strInfractureName = landTO.getInfractureIds();
             StringTokenizer st = new StringTokenizer(strInfractureName,"_");

            if (returnValue)
             {

                 while ( st.hasMoreTokens() )
                 {
                     infractureId = st.nextToken();
                     returnValue = addLandInfracture(landTO,landTO.getLandId(),infractureId);
                     System.out.println(returnValue +"add for update result true or false .................");
                 }

            }

            if (returnValue)
             {

             // If all is ok then commit.

             connection.commit();
                System.out.println(returnValue +"commit edit  true or false .................");

             connection.setAutoCommit(true);

             returnValue=true;

            }
        }catch(Exception e){
            returnValue = false;
            e.printStackTrace();
            connection.rollback();
        } finally {
            connection.setAutoCommit(true);
            closeConnections(connection, pstmt, null);
        }

        return returnValue;
    }

        public boolean editLandInfrastructure(LandTO landTO,String infrastructureId) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement pstmt = null;
        boolean returnValue = false;

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);

            String sqlString = SQLGenerator.getSQLEditLandInfrastucture();
            pstmt = connection.prepareStatement(sqlString);

            //get the original data
           // LandTO tempLandTO = searchLand(Integer.parseInt(landTO.getLandId()));

            pstmt.setString(1,infrastructureId);
            pstmt.setInt(2, Integer.parseInt(landTO.getLandId()));

            pstmt.execute();

            connection.commit();
            returnValue = true;
        }catch(Exception e){
            returnValue = false;
            e.printStackTrace();
            connection.rollback();
        } finally {
            connection.setAutoCommit(true);
            closeConnections(connection, pstmt, null);
        }

        return returnValue;
    }


    public boolean removeLandInfrastructure(LandTO landTO) throws SQLException, Exception {
        Connection connection = null;
        PreparedStatement pstmt = null;
        boolean returnValue = false;

        try {
            connection = DBConnection.createConnection();
            connection.setAutoCommit(false);

            String sqlString = SQLGenerator.getSQLRemoveLandInfrastucture();

            System.out.println(sqlString+"sql string .................");
            pstmt = connection.prepareStatement(sqlString);


            //get the original data
           // LandTO tempLandTO = searchLand(Integer.parseInt(landTO.getLandId()));

            pstmt.setInt(1, Integer.parseInt(landTO.getLandId()));

            pstmt.execute();

            connection.commit();
            returnValue = true;
        }catch(Exception e){
            returnValue = false;
            e.printStackTrace();
            connection.rollback();
        } finally {
            connection.setAutoCommit(true);
            closeConnections(connection, pstmt, null);
        }

        return returnValue;
    }


}