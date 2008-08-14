package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class Prism extends weka.classifiers.rules.Prism implements DMAlgorithm
{

	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new Prism(), args).toString();
		}
		catch (Exception e)
		{
			System.err.println(e.getMessage());
			throw e;
		}
		//return null;
	}

}
