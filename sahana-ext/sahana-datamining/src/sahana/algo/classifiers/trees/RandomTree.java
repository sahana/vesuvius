package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class RandomTree extends weka.classifiers.trees.RandomTree implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return Evaluation.evaluateModel(new RandomTree(), args).toString();
	}

}
