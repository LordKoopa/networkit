/*
 * OverlappingCommunityDetectionAlgorithm.cpp
 *
 *  Created on: 14.12.2020
 *      Author: Christian Staudt
 */

#include <networkit/community/OverlappingCommunityDetectionAlgorithm.hpp>

namespace NetworKit {

OverlappingCommunityDetectionAlgorithm::OverlappingCommunityDetectionAlgorithm(const Graph& G) : Algorithm(), G(&G), result(0) {
    // currently our community detection methods are not defined on directed graphs
    if (G.isDirected()) {
        throw std::runtime_error("This community detection method is undefined on directed graphs");
    }
}

OverlappingCommunityDetectionAlgorithm::OverlappingCommunityDetectionAlgorithm(const Graph& G, const Cover baseClustering) : Algorithm(), G(&G), result(baseClustering) {
}

Cover OverlappingCommunityDetectionAlgorithm::getCover() {
    if(!hasRun) {
        throw std::runtime_error("Call run()-function first.");
    }
    return result;
}

std::string OverlappingCommunityDetectionAlgorithm::toString() const {
    return "TODO: string representation of clusterer";
}

} /* namespace NetworKit */
