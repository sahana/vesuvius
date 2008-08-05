package sahana.algo.classifiers.lazy;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class IB1 extends weka.classifiers.lazy.IB1 implements DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new IB1(), args).toString();
		} catch (Exception e)
		{
			System.err.println(e.getMessage());
			return e.toString();
		}
	}

}
