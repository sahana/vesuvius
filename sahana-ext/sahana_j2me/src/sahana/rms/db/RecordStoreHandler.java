/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  RecordStoreHandler.java
 * @date       24 July 2006
 */



package sahana.rms.db;

import sahana.rms.db.Filter;
import javax.microedition.rms.*;
import javax.microedition.lcdui.*;

/* Authors : Kasun T Karunanayake
 */

public class RecordStoreHandler {

    private RecordStore primaryStore,secondaryStore;
    private RecordStore recordStore;
    private Alert alert;
    private int primaryRecordID,secondaryRecordID;

    public RecordStoreHandler() {
	    primaryRecordID=-1;
	    secondaryRecordID=-1;
    }

    /*Method which opens a record store*/
    public void openRecordStore(String rec ) {
        try {
            recordStore = RecordStore.openRecordStore( rec , true );
        } catch(Exception error) {
        }
    }/*end open Record Store method*/

    /*Method for opneRecordsSrore*/
    public void openRecordStore(String recordStore1,String recordStore2) {
        try {
	  	    primaryStore = RecordStore.openRecordStore(recordStore1,true);
		    secondaryStore = RecordStore.openRecordStore(recordStore2,true);
	    } catch (RecordStoreException e) {
		    e.printStackTrace();
	    }
    }/*end openRecordStore method*/

    /*Method for search records*/
    public int searchRecords( String str ) {
        try {
            Filter filter = new Filter(str);
            int numOfRecords = recordStore.getNumRecords();

            for (int x = 1 ; x <= numOfRecords  ; x++ ) {
                if ( filter.matches(recordStore.getRecord(x)) == true) {
                    return x;
                }
            }
        } catch( Exception error ) {
		}
        return 0;
    } /*end search records method*/

    /*Method for closeRecordStore*/
    public int colseRecordStore() {
	    try {
		    recordStore.closeRecordStore();
		    return 0;
	    } catch(RecordStoreException e) {
		    //e.printStackTrace();
		    return -1;
	    }
    }//end closeRecordStore method


    public int colseRecordStores() {
	    try {
		    primaryStore.closeRecordStore();
		    secondaryStore.closeRecordStore();
		    return 0;
	    } catch(RecordStoreException e) {
		    //e.printStackTrace();
		    return -1;
	    }
    }


    public int addPrimaryRecord(int searchID1,String strData1) {
	    byte[] arrayData1=strData1.getBytes();

	        if(searchID1==0)
		        try {
			    primaryRecordID = recordStore.addRecord(arrayData1,0,arrayData1.length);
		    } catch(RecordStoreException e) {
			    primaryRecordID=-1;
			    e.printStackTrace();
		    }
	    return primaryRecordID;
    }


    public int addSecondaryRecord(int searchID1,String strData2) {
	    byte[] arrayData1=null;
	    byte[] arrayData2=null;


	    if(strData2!=null)
		    arrayData2=strData2.getBytes();


	    if(strData2!=null)
			try {
			    secondaryRecordID = secondaryStore.addRecord(arrayData2,0,arrayData2.length);
			} catch(RecordStoreException e) {
				e.printStackTrace();
			}

	    if(searchID1>0) {
		    byte[] recordDataArray=null;
		    String tempRecord="";

		        try {
			        recordDataArray=primaryStore.getRecord(searchID1);
			        tempRecord=	new String(recordDataArray,0,recordDataArray.length);
					tempRecord=tempRecord+"$"+Integer.toString(secondaryRecordID);
					arrayData1=tempRecord.getBytes();
					primaryStore.setRecord(searchID1,arrayData1,0,arrayData1.length);
				} catch(RecordStoreException e) {
				    e.printStackTrace();
				}
        }

    return secondaryRecordID;
    }


    public String getId() {
	    return new String("Primery Id = " + primaryRecordID + " Secondary Id = " + secondaryRecordID);
    }

    public String getPrimaryRecord(int priRecId) {
	    try {
		    byte[] arryRecord=primaryStore.getRecord(priRecId);
		    return arryRecord.toString();
	    } catch(RecordStoreException e) {
		    e.printStackTrace();
		    return "Error";
	    }

    }


    public String getSecondaryRecord(int secRecId) {
	    try {
		    byte[] arryRecord=secondaryStore.getRecord(secRecId);
		    return arryRecord.toString();
	    } catch(RecordStoreException e) {
		    e.printStackTrace();
		    return "Error";
	    }
    }

    private void deletePrimaryRecord(int priRecId) {
	    try {
		    primaryStore.deleteRecord(priRecId);
	    } catch(RecordStoreException e) {
		    e.printStackTrace();
	    }
    }

    private void deleteSecondaryRecord(int secRecId) {
	    try {
		    secondaryStore.deleteRecord(secRecId);
	    } catch(RecordStoreException e) {
		    e.printStackTrace();
	    }
    }

    private String removeSecondaryLink(int priRecId) {
	    try {
		    String strPri=this.getPrimaryRecord(priRecId);

		    if(strPri.indexOf("$")<=0) {
			    this.deletePrimaryRecord(priRecId);
			    return "No secondary record delete primary record";
		    }

		    String tmpSecRecList=strPri.substring(strPri.indexOf("$")+1,strPri.length());
		    int tmpSecRec=Integer.parseInt(tmpSecRecList.substring(1,tmpSecRecList.indexOf("$")));
		    tmpSecRecList=tmpSecRecList.substring(tmpSecRecList.indexOf("$")+1,tmpSecRecList.length());
 	    	strPri=strPri.substring(1,strPri.indexOf("$"))+tmpSecRecList;

		    byte[] tempRecord=strPri.getBytes();
		    primaryStore.setRecord(priRecId,tempRecord,0,tempRecord.length);
		    String tmpSecRecord = this.getSecondaryRecord(tmpSecRec);
 		    this.deleteSecondaryRecord(tmpSecRec);
  		    return tmpSecRecord;

	    } catch(RecordStoreException e) {
		    e.printStackTrace();
		    return "Error";
	    }
    }

    public String removeRecord(int priRecId) {
	    String strPri=this.getPrimaryRecord(priRecId);
	    strPri=strPri.substring(1,strPri.indexOf("$"));
	    strPri=strPri+this.removeSecondaryLink(priRecId);
	    return strPri;
    }
}

