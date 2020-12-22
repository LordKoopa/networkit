/*
 * LFM.cpp
 *
 *  Created on: 10.12.2020
 *      Author: jgelkoops
 */

#include <networkit/community/LFM.hpp>

namespace NetworKit {
    
LFM::LFM(const Graph &G, SelectiveCommunityDetector &scd) : OverlappingCommunityDetectionAlgorithm(G), scd(scd) {}

void LFM::run() {
    count z = G->upperNodeIdBound();

    Cover zeta(z);
    index o = 0;
    zeta.setUpperBound(o);
    std::vector<bool> inCommunity(z + 1, false);

    G->forNodesInRandomOrder([&](node u) {
        if (!inCommunity[u]){
            std::set<node> community = scd.expandOneCommunity(u);
            o++;
            zeta.setUpperBound(o);

            for (auto n : community) {
                zeta.addToSubset(o - 1, n);
                inCommunity[u] = true;
            }
        }
    });

    result = std::move(zeta);
    hasRun = true;
}

std::string LFM::toString() const {
    return "LFM()";
}

} /* namespace NetworKit */
