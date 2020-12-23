/*
 * LFM.cpp
 *
 *  Created on: 10.12.2020
 *      Author: jgelkoops
 */

#include <networkit/community/LFM.hpp>
#include <iostream>

namespace NetworKit {
    
LFM::LFM(const Graph &G, SelectiveCommunityDetector &scd) : OverlappingCommunityDetectionAlgorithm(G), scd(scd) {}

void LFM::run() {
    count z = G->upperNodeIdBound();

    Cover zeta(z);
    index o = 0;
    zeta.setUpperBound(o);

    G->forNodesInRandomOrder([&](node u) {
        if (!zeta.contains(u)/*inCommunity[u]*/){
            std::set<node> community = scd.expandOneCommunity(u);
            o++;
            zeta.setUpperBound(o);

            for (auto n : community) {
                zeta.addToSubset(o - 1, n);
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
