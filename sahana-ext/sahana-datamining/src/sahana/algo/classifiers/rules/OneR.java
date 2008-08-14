package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class OneR extends weka.classifiers.rules.OneR implements DMAlgorithm
{

	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new OneR(), args).toString();
		}
		catch (Exception e)
		{
			System.err.println(e.getMessage());
			throw e;
		}
		//return null;
	}

}
