/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.common.selectionhierarchy;

/**
 * Represents a Node element in the category browser
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */
public class TreeElement implements Comparable {

    private int parentId;
    private int id;
    private String label;
    private String tableName;
    private String key;
    private boolean isLeaf;
    private boolean enabled;

    public int getParentId() {
        return parentId;
    }

    public void setParentId(int parentId) {
        this.parentId = parentId;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
    }

    public String getTableName() {
        return tableName;
    }

    public void setTableName(String tableName) {
        this.tableName = tableName;
    }

    public String getKey() {
        return key;
    }

    public void setKey(String key) {
        this.key = key;
    }

    public boolean isLeaf() {
        return isLeaf;
    }

    public void setLeaf(boolean leaf) {
        isLeaf = leaf;
    }

    public void setEnabled(boolean enabled) {
        this.enabled = enabled;
    }

    public boolean isEnabled() {
        return enabled;
    }

    public int compareTo(Object o) {
        String s1 = this.key;
        String s2 = ((TreeElement) o).key;

        return s1.compareTo(s2);
    }
}
