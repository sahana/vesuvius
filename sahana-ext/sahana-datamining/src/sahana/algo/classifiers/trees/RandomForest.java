package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class RandomForest extends weka.classifiers.trees.RandomForest implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return Evaluation.evaluateModel(new RandomForest(), args).toString();
	}

}
