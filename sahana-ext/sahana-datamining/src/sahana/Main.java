package sahana;
/*
 * Main.java
 *
 * Created on June 3, 2008, 10:50 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

import java.io.File;
import java.io.PrintStream;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 *
 * @author miyuru
 */
public class Main
{
    
    /** Creates a new instance of Main */
    public Main()
    {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        
        System.out.println("Sahana Dataminig engine");
        Statement stmt=DatabaseAccess.getStatement();
        
        while(true)
        {
            String jobid="";
            String data="";
            String algo="";
            String opt="";
            try
            {
                Thread.sleep(5000);
            }
            catch (InterruptedException ex)
            {
                ex.printStackTrace();
            }
            String sql="SELECT MIN(jobid) AS tjob,dataset ,algorithm, params FROM datamine WHERE finished=0 GROUP BY jobid ";
            try
            {
                ResultSet res=stmt.executeQuery(sql);
                if(res.next())
                {
                    System.out.println("gotta dm job..!");
                    jobid=res.getString(1);
                    data=res.getString(2);
                    algo=res.getString(3);
                    opt=res.getString(4);
                    
                    Thread dmJob=new Thread(new DMJob(stmt,jobid,data,algo,opt));
                    dmJob.start();
                    try
                    {
                        dmJob.join();
                    }
                    catch (InterruptedException ex)
                    {
                        ex.printStackTrace();
                    }
                }
                else
                    System.out.println("no dm :(");
            }
            catch (SQLException ex)
            {
                ex.printStackTrace();
            }
        }
    }
}
