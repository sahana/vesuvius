/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import net.sf.hibernate.Hibernate;
import net.sf.hibernate.HibernateException;
import net.sf.hibernate.Session;
import net.sf.hibernate.SessionFactory;
import net.sf.hibernate.cfg.Configuration;
import net.sf.hibernate.type.Type;
import org.damage.common.ConfigReader;

import java.sql.SQLException;
import java.util.List;

/**
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public abstract class BaseDAO {

    protected SessionFactory sessionFactory;

    protected BaseDAO() {
        try {
            System.out.println("Initializing Hibernate");
            sessionFactory = new Configuration().configure().buildSessionFactory();
            System.out.println("Finished Initializing Hibernate");
        } catch (HibernateException e) {
            e.printStackTrace();
        }
    }

    /**
     * Removes the object from the database with with specified class
     * type and <code>id</code>.
     *
     * @param c  the class type to remove
     * @param id the id of the class type
     * @throws DAOException
     */
    protected void removeObj(Class c, Long id) throws DAOException {
        try {
            Session session = sessionFactory.openSession();
            // first load the object with the current session.
            // the object must be loaded in this session before it
            //   is deleted.
            Object obj = session.load(c, id);
            session.delete(obj);
            session.flush();
            session.connection().commit();
        } catch (Exception e) {
            rollback();
            throw new DAOException(e);
        } finally {
            closeSession();
        }
    }

    /**
     * Retrieves and <code>Object</code> of the class type specified
     * by <code>c</code>, and having the given <code>id</code>.
     *
     * @param c  the class to load
     * @param id
     * @return Object may be null if object with ID doesn't exist
     * @throws DAOException
     */
    protected Object retrieveObj(Class c, Long id) throws DAOException {
        Object obj = null;

        try {
            Session session = sessionFactory.openSession();
            obj = session.load(c, id);
        } catch (HibernateException he) {
            he.printStackTrace();
            throw new DAOException(he);
        } finally {
            closeSession();
        }
        return obj;
    }

    /**
     * Retrieves an <code>Object</code> from the database.
     *
     * @param key   the key used to lookup the query in the resource bundle
     * @param value the value that is inserted into the query.  May be null
     *              if the desired query does not take a parameter.
     * @return Object
     * @throws DAOException
     */
    protected Object retrieveObj(String key, String value) throws DAOException {
        List objects = retrieveObjs(key, value);
        if (objects != null) {
            if (objects.size() == 0) {
                return null;
            } else {
                return objects.get(0);
            }
        } else {
            return null;
        }
    }

    /**
     * Retrieves a <code>List</code> of <code>Object</code>s from the database.
     *
     * @param key   the key used to lookup the query in the resource bundle
     * @param value the value that is inserted into the query.  May be null
     *              if the desired query does not take a parameter.
     * @return List will be null if no objects are retrieved
     * @throws DAOException
     */
    protected List retrieveObjs(String key, String value) throws DAOException {
        List results = null;

        try {
            Session session = sessionFactory.openSession();
            if (value != null) {
                results = (List) session.find(getQuery(key), value, Hibernate.STRING);
            } else {
                results = (List) session.find(getQuery(key));
            }
        } catch (HibernateException he) {
            he.printStackTrace();
            throw new DAOException(he);
        } finally {
            closeSession();
        }
        return results;
    }

    /**
     * Retrieves a <code>List</code> of <code>Object</code>s from the database.
     *
     * @param key   the key used to lookup the query in the resource bundle
     * @param value the value that is inserted into the query.  May be null
     *              if the desired query does not take a parameter.
     * @return List will be null if no objects are retrieved
     * @throws DAOException
     */

    protected List retrieveObjs(String key, Object[] value, Type[] type) throws DAOException {
        List results = null;

        try {
            Session session = sessionFactory.openSession();
            if (value != null) {
                results = (List) session.find(getQuery(key), value, type);
            } else {
                results = (List) session.find(getQuery(key));
            }
        } catch (HibernateException he) {
            he.printStackTrace();
            throw new DAOException(he);
        } finally {
            closeSession();
        }
        return results;
    }


    /**
     * Stores <code>obj</code>, making it persistent.
     *
     * @param obj
     * @throws DAOException
     */
    protected void storeObj(Object obj) throws DAOException {
        try {
            Session session = sessionFactory.openSession();
            session.saveOrUpdate(obj);
            session.flush();
            session.connection().commit();
        } catch (HibernateException he) {
            rollback();
            throw new DAOException(he);
        } catch (SQLException sqle) {
            rollback();
            throw new DAOException(sqle);
        } finally {
            closeSession();
        }
    }

    /**
     * Closes the current session.
     */
    protected void closeSession() {
        try {
            sessionFactory.close();
        } catch (HibernateException he) {
        }
    }


    /**
     * Performs a rollback on the current session. Exceptions
     * are logged.
     *
     * @throws DAOException if the current session can't be
     *                      retrieved or an exception is thrown while performing
     *                      the rollback.
     */
    protected void rollback() throws DAOException {
        try {
            Session session = sessionFactory.openSession();
            if (session != null) {
                session.connection().rollback();
            }
        } catch (HibernateException he) {
            throw new DAOException(he);
        } catch (SQLException sqle) {
            throw new DAOException(sqle);
        }
    }

    /**
     * Retrieves the HQL query from the resource bundle.
     *
     * @param key the HQL query to lookup
     */
    protected String getQuery(String key) {
        return ConfigReader.getQueryString(key);
    }

}

