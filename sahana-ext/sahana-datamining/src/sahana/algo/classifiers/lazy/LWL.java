package sahana.algo.classifiers.lazy;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class LWL extends weka.classifiers.lazy.LWL implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new LWL(), args).toString();
		}
		catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			throw e;
		}
	}

}
