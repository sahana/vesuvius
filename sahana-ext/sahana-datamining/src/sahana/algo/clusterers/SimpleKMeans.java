package sahana.algo.clusterers;

import sahana.DMAlgorithm;
import weka.clusterers.ClusterEvaluation;

public class SimpleKMeans extends weka.clusterers.SimpleKMeans implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return ClusterEvaluation.evaluateClusterer(new SimpleKMeans(), args).toString();
		
	}

}
