package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;

public class M5P extends weka.classifiers.trees.M5P implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return weka.classifiers.Evaluation.evaluateModel(new M5P(), args)
				.toString();
	}
}
