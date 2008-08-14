package sahana.algo.classifiers.misc;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class HyperPipes extends weka.classifiers.misc.HyperPipes implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new HyperPipes(), args).toString();
		}
		catch (Exception e)
		{
			System.err.println(e.getMessage());
			throw e;
		}
	}

}
