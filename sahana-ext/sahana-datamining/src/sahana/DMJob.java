package sahana;

/*
 * DMJob.java
 *
 * Created on June 3, 2008, 11:14 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.StringTokenizer;

/**
 * 
 * @author miyuru
 */
public class DMJob implements Runnable
{

	/**
	 * Creates a new instance of DMJob
	 */
	Statement stmt;
	String jobid;
	String data;
	String algo;
	String args;

	public DMJob(Statement stmt, String jobid, String data, String algo,
			String args)
	{
		this.stmt = stmt;
		this.jobid = jobid;
		this.data = data;
		this.algo = algo;
		this.args = args;
	}

	public void run()
	{
		createDataFile(data, "test.arff");
		args += " test.arff";
		StringTokenizer token = new StringTokenizer(args);
		String[] input = new String[token.countTokens()];

		int i = 0;
		while (token.hasMoreTokens())
		{
			input[i] = token.nextToken();
			++i;
		}

		String res;
		String sql = "";
		try
		{
			res = Miner.mineData(algo, input);
			sql = "UPDATE datamine SET finished=1 , result='" + res
					+ "' WHERE jobid='" + jobid + "'";
		}
		catch (Exception e)
		{
			res = e.getMessage();
			res=res.replace('\'', ',');
			sql = "UPDATE datamine set finished=1 , result='" + res
					+ "' WHERE jobid='" + jobid + "'";
			System.out.println(sql);
		}

		// System.out.println(sql);
		try
		{
			stmt.executeUpdate(sql);
		}
		catch (SQLException ex)
		{
			System.err
					.println("Database connection error - Unable to update data mining result");
		}
	}

	public static void createDataFile(String data, String fileName)
	{
		try
		{
			BufferedWriter write = new BufferedWriter(new FileWriter(fileName));
			write.write(data);
			write.close();
		}
		catch (IOException ex)
		{
			System.err.println("Unable to create a data file for data mine;");
		}
	}
}
