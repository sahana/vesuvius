package sahana.algo.clusterers;

import sahana.DMAlgorithm;
import weka.clusterers.ClusterEvaluation;

public class Cobweb extends weka.clusterers.Cobweb implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return ClusterEvaluation.evaluateClusterer(new Cobweb(),args).toString();
	}
}
