package sahana.algo.classifiers.lazy;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class KStar extends weka.classifiers.lazy.KStar implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new KStar(), args).toString();
		}
		catch (Exception e)
		{
			// System.err.println(e.getMessage());
			e.printStackTrace();
			throw e;
		}
	}

}
