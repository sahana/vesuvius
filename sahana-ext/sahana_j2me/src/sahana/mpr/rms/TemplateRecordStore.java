/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  TemplateRecordStore.java
 * @date       24 July 2006
 */


package sahana.mpr.rms;

import javax.microedition.rms.*;
import java.io.*;

/* Author : Thayalan Gugathashan
 */

public class TemplateRecordStore {

    RecordStore recordStore = null;

    public TemplateRecordStore() {
	}

    public TemplateRecordStore(String dbName) {

        try {
            recordStore = RecordStore.openRecordStore(dbName, true);
        }
        catch (RecordStoreException rse) {
            rse.printStackTrace();
        }
    }

    public void close() throws RecordStoreNotOpenException, RecordStoreException {

        if (recordStore.getNumRecords() == 0) {
            String dbName = recordStore.getName();
            recordStore.closeRecordStore();
            recordStore.deleteRecordStore(dbName);
        } else {
		    recordStore.closeRecordStore();
          }
    }

    public synchronized void addTemplate(String record) {

        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream outputStream = new DataOutputStream(baos);

        try {
            outputStream.writeUTF(record);
        }
        catch (IOException ioe) {
            System.out.println(ioe);
            ioe.printStackTrace();
        }

        byte[] b = baos.toByteArray();

        try {
            recordStore.addRecord(b, 0, b.length);
        }
        catch (RecordStoreException rse) {
            System.out.println(rse);
            rse.printStackTrace();
        }
    }

    public synchronized RecordEnumeration enumerate() throws RecordStoreNotOpenException {
        return recordStore.enumerateRecords(null, null, false);
    }

    public synchronized void deleteContact(int recordid) throws RecordStoreNotOpenException, InvalidRecordIDException, RecordStoreException {
        recordStore.deleteRecord(recordid);
    }

    public synchronized void updateTemplate(int recid, String record) throws RecordStoreNotOpenException, InvalidRecordIDException, RecordStoreException {
        System.out.println("updateContact" + record);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        DataOutputStream outputStream = new DataOutputStream(baos);

        try {
            outputStream.writeUTF(record);
        }
        catch (IOException ioe) {
            System.out.println(ioe);
            ioe.printStackTrace();
        }

        byte[] b = baos.toByteArray();
        recordStore.setRecord(recid, b, 0, b.length);
    }

    public synchronized int getRid() throws RecordStoreNotOpenException, RecordStoreException {
        return recordStore.getNextRecordID();
    }

    public String readRecords(byte[] data) throws IOException {

        ByteArrayInputStream bis = new ByteArrayInputStream(data);
        DataInputStream dis = new DataInputStream(bis);
        return DataInputStream.readUTF(dis);
    }
}




