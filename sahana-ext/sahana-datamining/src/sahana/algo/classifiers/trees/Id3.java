package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class Id3 extends weka.classifiers.trees.Id3 implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new Id3(), args).toString();
		}
		catch (Exception e)
		{
			System.err.println(e.getMessage());
			throw e;
		}
	}

}
