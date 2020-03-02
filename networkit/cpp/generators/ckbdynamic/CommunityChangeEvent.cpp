

#include "CommunityChangeEvent.h"

namespace NetworKit {
	namespace CKBDynamicImpl {
		CommunityChangeEvent::CommunityChangeEvent(CKBDynamicImpl& generator, count numSteps) : active(true), numSteps(numSteps), currentStep(0), generator(generator) {}

		void CommunityChangeEvent::notifyNodeAddedToCommunity(node, CommunityPtr) {}
		void CommunityChangeEvent::notifyNodeRemovedFromCommunity(node, CommunityPtr) {}

		bool CommunityChangeEvent::canRemoveNode() const { return true; }
	}
}