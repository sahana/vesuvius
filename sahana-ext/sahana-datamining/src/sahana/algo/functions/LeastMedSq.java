package sahana.algo.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class LeastMedSq extends weka.classifiers.functions.LeastMedSq implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new LeastMedSq(), args).toString();			
		} catch (Exception e)
		{
			System.out.println(e.getMessage());
			e.printStackTrace();
			return e.toString();			
		}
	}
}
