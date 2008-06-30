package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class PART extends weka.classifiers.rules.PART implements DMAlgorithm
{

	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new PART(), args).toString();
		} catch (Exception e)
		{
			System.out.println(e.getMessage());
		}
		return null;
	}

}
