/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import java.io.PrintStream;

/**
 * General purpose application exception.  This class is a modified version
 * of an exception class found in Matt Raible's example app, found at
 * http://raibledesigns.com/wiki/Wiki.jsp?page=AppFuse
 *
 * @author <a href="mailto:nick@systemmobile.com">Nick Heudecker</a>
 */

public class DAOException extends Exception {

    public DAOException() {
        super();
    }

    public DAOException(String message) {
        super(message);
    }

    public DAOException(Exception e) {
        this(e, e.getMessage());
    }

    public DAOException(Exception e, String message) {
        super(message);
        this.exception = e;
    }

    public DAOException(Exception e, String message, boolean fatal) {
        this(e, message);
        setFatal(fatal);
    }

    public boolean isFatal() {
        return this.fatal;
    }

    public void setFatal(boolean fatal) {
        this.fatal = fatal;
    }

    public void printStackTrace() {
        super.printStackTrace();
        if (this.exception != null) {
            System.out.print("%%%% wrapped exception: ");
            this.exception.printStackTrace();
        }
    }

    public void printStackTrace(PrintStream printStream) {
        super.printStackTrace(printStream);
        if (this.exception != null) {
            System.out.print("%%%% wrapped exception: ");
            this.exception.printStackTrace(printStream);
        }
    }

    public String toString() {
        if (exception != null) {
            return super.toString() + " wraps: [" + exception.toString() + "]";
        } else {
            return super.toString();
        }
    }

    protected Exception exception;
    protected boolean fatal;

}

