package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class ADTree extends weka.classifiers.trees.ADTree implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new ADTree(), args).toString();
		}
		catch (Exception e)
		{
			System.err.println(e.getMessage());
			throw e;
		}
	}

}
