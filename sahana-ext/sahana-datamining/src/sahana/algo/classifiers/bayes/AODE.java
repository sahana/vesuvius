package sahana.algo.classifiers.bayes;

import weka.classifiers.Evaluation;

public class AODE extends weka.classifiers.bayes.AODE implements
		sahana.DMAlgorithm
{

	public String mine(String[] argv)throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new AODE(), argv).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			throw e;
		}
	}

}
