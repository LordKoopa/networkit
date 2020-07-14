#ifndef EDITINGRUNNER_H
#define EDITINGRUNNER_H

#include <networkit/graph/Graph.hpp>
#include <networkit/auxiliary/SignalHandling.hpp>
#include <networkit/community/QuasiThresholdMover/DynamicForest.hpp>
#include <networkit/community/QuasiThresholdMover/BucketQueue.hpp>

namespace NetworKit {
  
enum Initialization {TRIVIAL, EDITING, RANDOM_INSERT, ASC_DEGREE_INSERT, USER_DEFINED_INSERT};

class EditingRunner {
public:
  EditingRunner(const Graph& G, Initialization initialization, count maxIterations, bool sortPaths, 
    bool randomness, count maxPlateauSize, bool useBucketQueue, std::vector<node> order);
  
  void runLocalMover();
        
  count getNumberOfEdits() const {
    return numEdits;
  };
  
  count getUsedIterations() const {
    return usedIterations;
  };
  
  count getPlateauSize() const {
    return actualMaximumPlateau;
  };
  
  count getRootEqualBestParents() const {
    return rootEqualBestParentsCpy;
  };
  
  Graph getQuasiThresholdGraph() const;
  

private:
  
  
  struct TraversalData{
    count scoreMax;
    count childCloseness;
    count equalBestParents;
    node bestParentBelow;
    
    TraversalData () : scoreMax(0) , childCloseness(0), equalBestParents(1), bestParentBelow(none){};
    
    void reset(){
      scoreMax = 0;
      childCloseness = 0;
      equalBestParents = 1;
      bestParentBelow = none;
    };
    
    std::string toString(){
      std::stringstream ss;
      ss << "\n";
      ss << "scoreMax: " << scoreMax << "\n";
      ss << "childCloseness: " << childCloseness << "\n";
      ss << "equalBestParents: " << equalBestParents << "\n";
      ss << "bestParentBelow: " << bestParentBelow << "\n";
      return ss.str();
    };
  };
  
  const Graph& G;
  count maxIterations;
  count usedIterations;
  bool sortPaths;
  bool randomness;
  std::vector<NetworKit::node> order;
  count maxPlateauSize;
  
  bool insertRun;
  bool useBucketQueue;
  
  count numEdits;
        
  Aux::SignalHandler handler;
  DynamicForest dynamicForest;
  bool hasMoved;
  std::vector<bool> marker;
  
  count level;
  std::vector<node> neighborQueue;
  std::vector<node> currentLevel;
  std::vector<node> nextLevel;

  NetworKit::BucketQueue bucketQueue;
  std::vector<node> neighbors;
  std::vector<node> touchedNodes;
  std::vector<node> lastVisitedDFSNode;
  std::vector<TraversalData> traversalData;
  std::vector<bool> nodeTouched;
  
  TraversalData rootData;
  
  count bestEdits;
  count curEdits;
  node curParent;
  std::vector<node> curChildren;
  std::vector<node> bestChildren;
  
  std::vector<bool> existing;


  count rootEqualBestParentsCpy;
  
  count editsBefore;
  count currentPlateau;
  count actualMaximumPlateau;
  
  count maxDepth;
  
  std::mt19937_64& gen;
  std::uniform_int_distribution<count> dist;
  
  void localMove(node nodeToMove);
  void processNode(node u, node nodeToMove);
  void compareWithQuadratic(node nodeToMove) const;
  NetworKit::count countNumberOfEdits() const;
  NetworKit::count editsIncidentTo(node u) const;
  
  bool randomBool(count options) {
    count x = dist(gen, std::uniform_int_distribution<count>::param_type(0, options-1));
    return options == 0 ? 0 : rand() % options == 0;
  };
  

  
    
};

} // namespace NetworKit

#endif // EDITINGRUNNER_H