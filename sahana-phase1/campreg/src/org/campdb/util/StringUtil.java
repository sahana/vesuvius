/*
 * (C) Copyright 2004 Valista Limited. All Rights Reserved.
 *
 * These materials are unpublished, proprietary, confidential source code of
 * Valista Limited and constitute a TRADE SECRET of Valista Limited.
 *
 * Valista Limited retains all title to and intellectual property rights
 * in these materials.
 */

package org.campdb.util;

public class StringUtil {
    public static String returnEmptyForNull(String s) {
        if (s == null) return "&nbsp;";
        return s;
    }

}
