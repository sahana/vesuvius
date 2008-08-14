package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class ConjunctiveRule extends weka.classifiers.rules.ConjunctiveRule
		implements DMAlgorithm
{

	public String mine(String[] args)throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new ConjunctiveRule(), args)
					.toString();
		}
		catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			throw e;
		}
		//return null;
	}
}
