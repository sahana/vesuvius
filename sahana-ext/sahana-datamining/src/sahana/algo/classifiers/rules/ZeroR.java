package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class ZeroR extends weka.classifiers.rules.ZeroR implements DMAlgorithm
{

	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new ZeroR(), args).toString();
		}
		catch (Exception e)
		{
			System.err.println(e.getMessage());
			throw e;
		}
		//return null;
	}

}
