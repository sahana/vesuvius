/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.common;

import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

/**
 *
 * @author Viraj Samaranayaka
 * @version 1.0
 */
public class CustomTextReader {

    private static final String CUSTOM_KEY = "custom.text";
    private List m_listCategory = null;

    public CustomTextReader() {

    }

    /**
     * Get the List of given the type and custom parameter
     *
     * @return List
     */
    public List getCustomDropDownValues(String dataType, String customString) {

        try {

            Vector vtFacilitiesCategory = new Vector();
            boolean flagCategory = true;

            int k = 1;
            while (flagCategory) {
                String strValueCate = ConfigReader.getMessage(CUSTOM_KEY + "." + dataType + "." + customString + k);
                flagCategory = (!strValueCate.equals(ConfigReader.RESOURCE_MESSAGE_NOT_FOUND));
                if (flagCategory) {
                    vtFacilitiesCategory.add(strValueCate);
                }
                k++;
            }

            m_listCategory = new ArrayList();
            int intSize = vtFacilitiesCategory.size();
            for (int j = 0; j < intSize; j++) {
                m_listCategory.add(new LabelValue(vtFacilitiesCategory.get(j).toString(),
                        new Integer(j).toString()));
            }

            return m_listCategory;

        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

}
