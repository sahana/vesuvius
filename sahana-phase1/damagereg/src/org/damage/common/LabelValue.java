/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.common;

/**
 *
 * @author Viraj Samaranayaka
 * @version 1.0
 */

public class LabelValue {
    private final String label;
    private final String value;

    public LabelValue(String label, String value) {
        this.label = label;
        this.value = value;
    }

    public String getLabel() {
        return label;
    }

    public String getValue() {
        return value;
    }
}

