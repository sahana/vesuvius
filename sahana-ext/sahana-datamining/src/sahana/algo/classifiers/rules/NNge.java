package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class NNge extends weka.classifiers.rules.NNge implements DMAlgorithm
{

	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new NNge(), args).toString();
		} catch (Exception e)
		{
			System.err.println(e.getMessage());
			e.printStackTrace();
		}
		return null;
	}

}
