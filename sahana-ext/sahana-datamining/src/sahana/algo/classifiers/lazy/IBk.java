package sahana.algo.classifiers.lazy;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class IBk extends weka.classifiers.lazy.IBk implements DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new IBk(), args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			return e.toString();
		}
	}

}
