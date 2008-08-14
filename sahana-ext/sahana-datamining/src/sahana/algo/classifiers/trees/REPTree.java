package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class REPTree extends weka.classifiers.trees.REPTree implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return Evaluation.evaluateModel(new REPTree(), args).toString();
	}

}
