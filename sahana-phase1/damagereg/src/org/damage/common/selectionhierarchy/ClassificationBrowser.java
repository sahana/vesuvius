/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/

package org.damage.common.selectionhierarchy;

import org.damage.common.ConfigReader;
import org.damage.util.SessionUtils;
import org.damage.util.myXML;

import javax.servlet.http.HttpServletRequest;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Stack;
import java.util.TreeMap;
import java.util.Vector;

/**
 * Class to read in the custom category selection hierarchy
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */
public class ClassificationBrowser {

    private static boolean debug;
    private static Vector elements;
    private static TreeMap leafElements;
    private static Vector enabledTypes;
    private static final String CATEGORY_FILE_KEY = "selection.hierarchy.xml.file";

    public static void load(HttpServletRequest request) {

        if ((elements != null) && (elements.size() > 0)) return;

        try {

            String filename = SessionUtils.getRealPath(request, ConfigReader.getSettingsValue(CATEGORY_FILE_KEY));

            enabledTypes = ConfigReader.getEnabledClassificationNodes();

            BufferedReader in = new BufferedReader(new FileReader(filename));
            myXML xmlroot = new myXML((BufferedReader) in);

            elements = new Vector();
            leafElements = new TreeMap();
            setChildElements(xmlroot, -1, elements);

            if (debug) System.out.println("elements size=" + elements.size());
            if (debug) System.out.println("leaf nodes size=" + leafElements.size());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static Vector getTreeElements() {
        return elements;
    }

    public static boolean isDebug() {
        return debug;
    }

    public static void setDebug(boolean debug) {
        ClassificationBrowser.debug = debug;
    }

    public static TreeElement getNodeById(int id) {
        return (TreeElement) elements.get(id);
    }

    public static TreeElement getNodeByType(String type) {
        TreeElement leafNode = (TreeElement) leafElements.get(type);
        if (leafNode != null) {
            return (TreeElement) elements.get(leafNode.getId());
        } else {
            return null;
        }
    }

    public static Stack getParentHierarchy(int id) {
        TreeElement node;
        Stack parentTree = new Stack();

        do {
            node = (TreeElement) elements.get(id);
            parentTree.push(node.getLabel());
            id = node.getParentId();
        } while (id != -1);

        return parentTree;
    }

    /**
     * Recursively browses the XML tree
     *
     * @param parent
     * @param parentId
     * @param elements
     */
    private static void setChildElements(myXML parent, int parentId, Vector elements) {
        myXML element;

        if (parent.size() == 0) {

            // leaf node
            addToList(parent, elements, parentId);
            return;

        } else {

            int id = elements.size();
            addToList(parent, elements, parentId); // ancestor node

            for (int i = 0; i < parent.size(); i++) {
                element = parent.getElement(i);
                setChildElements(element, id, elements);
            }
        }
    }

    private static void addToList(myXML element, Vector elements, int parentId) {
        int id;
        String label;
        String typeCode;
        String schemaRelation;
        TreeElement treeElement;

        // An element contains <Private label="Private"> OR
        // <Primary label="Primary School" typecode="SchlPrvPrm" schemarelation="DAMAGE_DETAIL_SCHOOL"/>

        label = element.Attribute.find("label");
        if (label != "") { // not a closing tag i.e. </Hospital>

            treeElement = new TreeElement();
            id = elements.size(); // need to set a unique id in sequence..
            treeElement.setId(id);
            treeElement.setParentId(parentId);
            treeElement.setLabel(label);
            if (debug) {
                System.out.println("----------");
                System.out.println("label=" + label);
                System.out.println("Id=" + id);
                System.out.println("parentId=" + parentId);
            }

            typeCode = element.Attribute.find("typecode");
            if (typeCode != null) { // a leaf node

                schemaRelation = element.Attribute.find("schemarelation");
                treeElement.setLeaf(true);
                treeElement.setKey(typeCode);
                treeElement.setTableName(schemaRelation);
                if (enabledTypes.contains(typeCode)) treeElement.setEnabled(true);
                leafElements.put(treeElement.getKey(), treeElement);

                if (debug) {
                    System.out.println("schemaRelation=" + schemaRelation);
                    System.out.println("typecode=" + typeCode);
                    System.out.println("enabled=" + treeElement.isEnabled());
                }
            }

            elements.add(treeElement);
        }

    }

}
