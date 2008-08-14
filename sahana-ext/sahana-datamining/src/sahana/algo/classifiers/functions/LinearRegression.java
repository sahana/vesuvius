package sahana.algo.classifiers.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class LinearRegression extends
		weka.classifiers.functions.LinearRegression implements DMAlgorithm
{

	@Override
	public String mine(String[] args)throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new LinearRegression(), args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.out.println(e.getMessage());
			throw e;
		}
	}

}
