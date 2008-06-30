package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;

public class M5Rules extends weka.classifiers.rules.M5Rules implements
		DMAlgorithm
{

	public String mine(String[] args)
	{
		try
		{
			return weka.classifiers.Evaluation.evaluateModel(new M5Rules(), args).toString();
		} catch (Exception e)
		{
			System.err.println(e.getMessage());
			e.printStackTrace();
		}
		return null;
	}
}
