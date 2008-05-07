/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  Filter.java
 * @date       24 July 2006
 */


package sahana.rms.db;

import javax.microedition.rms.*;
import java.io.*;

/* Authors : Kasun T Karunanayake
 */

public class Filter implements RecordFilter {

    private String search = null;
    private ByteArrayInputStream inputStream = null ;
    private DataInputStream datainputStream = null ;

    public Filter(String search) {
        this.search = search;
    }

    public boolean matches(byte[] candidate) {
        String string = new String(candidate , 0 , candidate.length);

        if ( string != null && string.indexOf(search) != -1 ) {
            return true ;
	    } else {
            return false;
        }
    }

    public void filterClose() {
        try {
            if ( inputStream != null ) {
                inputStream.close();
            }

            if ( datainputStream != null ) {
                datainputStream.close();
            }

        } catch( Exception error) {
		}
    }
}