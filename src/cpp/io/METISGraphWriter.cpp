/*
 * METISGraphWriter.cpp
 *
 *  Created on: 30.01.2013
 *      Author: Christian Staudt (christian.staudt@kit.edu)
 */

#include "METISGraphWriter.h"

#include "../auxiliary/Enforce.h"

namespace NetworKit {

void METISGraphWriter::write(Graph& G, const std::string& path) {
	this->write(G, G.isWeighted(), path);
}
void METISGraphWriter::write(Graph& G, bool weighted, std::string path) {
	if (G.isDirected()) {
		throw std::invalid_argument{"METIS does not support directed graphs"};
	}
	std::ofstream file(path);
	Aux::enforceOpened(file);

	count n = G.numberOfNodes();
	count m = G.numberOfEdges();

	file << n << " " << m << " " << int{weighted} << '\n';

	if (weighted == false) {
		G.forNodes([&](node u) {
			G.forNeighborsOf(u, [&](node v){
				file << v + 1 << " ";
			});
			file << '\n';
		});
	} else {
			G.forNodes([&](node u) {
			G.forNeighborsOf(u, [&](node v){
				file << v + 1 << " " << G.weight(u, v) <<"\t";
			});
			file << '\n';
		});
	}
}

} /* namespace NetworKit */