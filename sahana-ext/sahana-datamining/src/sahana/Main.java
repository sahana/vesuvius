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
import java.io.Console;
import java.util.Arrays;
import java.io.IOException;

import com.mysql.jdbc.CommunicationsException;

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
	 * @param args
	 *            the command line arguments
	 */
	public static void main(String[] args)
	{

		System.out.println("Sahana Dataminig engine\n");
		String[] con = getDBInfo(true);
		Statement stmt = null;

		try
		{
			stmt = DatabaseAccess.getStatement(con[0], con[1], con[2], con[3]);
		} catch (CommunicationsException e)
		{
			System.err
					.println("Unable to connect to database server\nCheck database IP address");
			System.exit(0);
		} catch (SQLException e)
		{
			System.err.println("Unable to connect to database");
			System.out.println(e.getMessage());
			System.exit(0);
		}

		while (true)
		{
			String jobid = "";
			String data = "";
			String algo = "";
			String opt = "";
			try
			{
				Thread.sleep(5000);
			} catch (InterruptedException ex)
			{
				ex.printStackTrace();
			}
			String sql = "SELECT MIN(jobid) AS tjob,dataset ,algorithm, params FROM datamine WHERE finished=0 GROUP BY jobid ";
			try
			{
				ResultSet res = stmt.executeQuery(sql);
				if (res.next())
				{
					jobid = res.getString(1);
					System.out.println("Data mining job received : Job id = "
							+ jobid);
					data = res.getString(2);
					algo = res.getString(3);
					opt = res.getString(4);

					Thread dmJob = new Thread(new DMJob(stmt, jobid, data,
							algo, opt));
					dmJob.start();
					try
					{
						dmJob.join();
					} catch (InterruptedException ex)
					{
						ex.printStackTrace();
					}
				} else
				{
					//System.out.println("no dm :(");
				}
			} catch (SQLException ex)
			{
				ex.printStackTrace();
			}
		}
	}

	static String[] getDBInfo(boolean console)
	{
		if (console)
		{
			Console c = System.console();
			if (c == null)
			{
				System.err.println("Unable to access to console");
				System.exit(1);
			}
			String ip = c.readLine("Enter IP address of database : ");
			String db = c.readLine("Enter database name : ");
			String user = c.readLine("Enter username of database : ");
			char p[] = c.readPassword("Enter password of the database : ");
			String pass = new String(p);

			String[] con = new String[4];
			con[0] = ip;
			con[1] = db;
			con[2] = user;
			con[3] = pass;
			return con;
		} else
		{
			return null;
		}

	}
}
