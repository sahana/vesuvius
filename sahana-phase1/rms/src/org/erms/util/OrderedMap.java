package org.erms.util;

import org.erms.business.KeyValueDTO;

import java.util.Collection;
import java.util.HashMap;
import java.util.Arrays;
import java.util.ArrayList;

/**
 * Created by IntelliJ IDEA.
 * User: hemapani
 * Date: Jan 11, 2005
 * Time: 3:25:14 PM
 * To change this template use File | Settings | File Templates.
 */
public class OrderedMap {
    private Collection orderedList;
    private HashMap map;

    public OrderedMap(){
        orderedList = new ArrayList();
        map = new HashMap();
    }

    public String toString() {
        return map.toString();
    }

    public void put(String key,String value){
        map.put(key,value);
        KeyValueDTO kvdto = new KeyValueDTO();
        kvdto.setDbTableCode(key);
        kvdto.setDisplayValue(value);
        orderedList.add(kvdto);
    }

    public Object get(String key){
         return map.get(key);
    }

    public Collection getValuesInOrder(){
        return orderedList;
    }
}
