/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import net.sf.hibernate.HibernateException;
import net.sf.hibernate.Session;
import net.sf.hibernate.Transaction;
import org.damage.business.*;

import java.sql.SQLException;
import java.util.Iterator;
import java.util.Set;

/**
 * Class handling saving of DamageCase bean with all contained beans
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DataAccessManager extends BaseDAO {
    public void saveCase(DamageCase damageCase) throws DAOException {
        Set damageReports;

        damageReports = damageCase.getDamageReports();
        Transaction transaction = null;

        try {

            Session session = sessionFactory.openSession();

            transaction = session.beginTransaction();

            System.out.println("**START INSERTING CASE**");
            session.saveOrUpdate(damageCase);
            System.out.println("**FINISH INSERTING CASE**");

            //////////////SAVE DAMAGE REPORTS COLLECTION START////////////////////////////////
            for (Iterator iterator = damageReports.iterator(); iterator.hasNext();) {
                System.out.println("**START INSERTING REPORTS**");

                DamageReport damagedReport = (DamageReport) iterator.next();

                Long temp1 = damageCase.getCaseId();
                damagedReport.setCaseId(temp1);
                System.out.println("**CASE ID IS@@*" + damagedReport.getCaseId());
                ////////////////////////////////////////////////////
                Property property = damagedReport.getProperty();
                if (property != null) {
                    session.saveOrUpdate(property);
                }
                ////////////////////////////////////////////////////
                //Long temp = property.getPropertyId();
                if (property != null) {
                    damagedReport.setPropertyId(property.getPropertyId());
                    System.out.println("**PROPERTY ID IS@@*" + property.getPropertyId());
                }
                session.saveOrUpdate(damagedReport);
                System.out.println("**FINISH INSERTING REPORTS**");

                //////////SAVE INSERTING DMG_DETAIL_HOSPITAL START////////////////////////////////
                if (damagedReport.getDamageDetail() instanceof DamageReportDetailHospital) {
                    DamageReportDetailHospital damageDetailHospital = (DamageReportDetailHospital) damagedReport.getDamageDetail();
                    if (damageDetailHospital != null) {
                        damageDetailHospital.setDamageReportId(damagedReport.getDamageReportId());
                        damageDetailHospital.setPropertyId(damagedReport.getPropertyId());
                        System.out.println("**DamageReportId IS@@*" + damagedReport.getDamageReportId());
                        session.saveOrUpdate(damageDetailHospital);
                        /////////SAVE DAMAGE_DETAIL_ESTIMATED_COST START//////////////////////////////////
                        Set damageDetailHospitalEstimatedCosts;
                        damageDetailHospitalEstimatedCosts = damageDetailHospital.getDamageDetailHospitalEstimatedCosts();

                        System.out.println("DamageDetailHospitalEstimatedCost= " + damageDetailHospitalEstimatedCosts.size());
                        if (damageDetailHospitalEstimatedCosts != null)
                            for (Iterator iterator1 = damageDetailHospitalEstimatedCosts.iterator(); iterator1.hasNext();) {
                                System.out.println("**START DAMAGE_DETAIL_ESTIMATED_COST*");
                                DamageDetailHospitalEstimatedCost damageDetailHospitalEstimatedCost = (DamageDetailHospitalEstimatedCost) iterator1.next();
                                damageDetailHospitalEstimatedCost.setDamageReportId(damagedReport.getDamageReportId());
                                damageDetailHospitalEstimatedCost.setPropertyId(damagedReport.getPropertyId());
                                session.saveOrUpdate(damageDetailHospitalEstimatedCost);
                                System.out.println("**DAMAGE_DETAIL_ESTIMATED_COST ID*" + damageDetailHospitalEstimatedCost.getDmgDetailEstimatedCostId());
                                System.out.println("**FINISH DAMAGE_DETAIL_ESTIMATED_COST*");
                            }
                        /////////SAVE DAMAGE_DETAIL_ESTIMATED_COST FINISH//////////////////////////////////
                    }
                }
                //////////SAVE INSERTING DMG_DETAIL_HOSPITAL END////////////////////////////////
            }
            ///////////////SAVE DAMAGE REPORTS COLLECTION FINISH///////////////////////////////

            transaction.commit();
            session.flush();
            session.connection().commit();

        } catch (HibernateException he) {
            if (transaction != null) {
                try {
                    transaction.rollback();
                } catch (HibernateException h) {
                    //log he and rethrow e
                    h.printStackTrace();
                    throw new DAOException(h);
                }
            }
            throw new DAOException(he);
        } catch (SQLException sqle) {
            if (transaction != null) {
                try {
                    transaction.rollback();
                } catch (HibernateException h) {
                    //log he and rethrow e
                    h.printStackTrace();
                    throw new DAOException(h);
                }
            }
            sqle.printStackTrace();
            throw new DAOException(sqle);
        } finally {
            closeSession();
        }
    }


}
