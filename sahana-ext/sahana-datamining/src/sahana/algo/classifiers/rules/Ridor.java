package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class Ridor extends weka.classifiers.rules.Ridor implements DMAlgorithm
{

	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new Ridor(), args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
		}
		return null;
	}

}
