/*
 * (C) Copyright 2004 Valista Limited. All Rights Reserved.
 *
 * These materials are unpublished, proprietary, confidential source code of
 * Valista Limited and constitute a TRADE SECRET of Valista Limited.
 *
 * Valista Limited retains all title to and intellectual property rights
 * in these materials.
 */

package org.housing.util;

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

