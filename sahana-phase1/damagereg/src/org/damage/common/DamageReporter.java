/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.common;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * This is used by the UI for display purposes
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public class DamageReporter implements Serializable {

    private ArrayList damageObjectCollection;

    /**
     * To retrive and display query results
     *
     * @return list of rows containing Hashtable of the column data
     */
    public ArrayList getCurrentReport() {
        return damageObjectCollection;
    }

    public void setCurrentReport(ArrayList results) {
        this.damageObjectCollection = results;
    }
}
