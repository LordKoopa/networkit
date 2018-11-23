#ifndef CKB_DYNAMIC_H
#define CKB_DYNAMIC_H

#include "../graph/Graph.h"
#include "../structures/Cover.h"
#include "../dynamics/GraphEvent.h"
#include "../dynamics/CommunityEvent.h"
#include "../base/Algorithm.h"

namespace NetworKit {
	class CKBDynamic : public Algorithm {
	public:
		CKBDynamic(count n, count minCommunitySize, count maxCommunitySize, double communitySizeExponent, double minSplitRatio, count minCommunityMembership, count maxCommunityMembership, double communityMembershipExponent, double communityEventProbability, double nodeEventProbability, double perturbationProbability, double intraCommunityEdgeProbability, double intraCommunityEdgeExponent, double epsilon, double edgeSharpness, count numTimesteps);

		virtual void run() override;

		const std::vector<GraphEvent>& getGraphEvents() const;
		const std::vector<CommunityEvent>& getCommunityEvents() const;

		struct param_type {
			count n;
			count minCommunitySize;
			count maxCommunitySize;
			double communitySizeExponent;
			double minSplitRatio;
			count minCommunityMembership;
			count maxCommunityMembership;
			double communityMembershipExponent;
			double communityEventProbability;
			double nodeEventProbability;
			double perturbationProbability;
			double intraCommunityEdgeProbability;
			double intraCommunityEdgeExponent;
			double epsilon;
			double edgeSharpness;
			count numTimesteps;
		};
	private:
		std::vector<GraphEvent> graphEvents;
		std::vector<CommunityEvent> communityEvents;
		param_type parameters;

	};

} // namespace NetworKit

#endif
