#include "Statistics.h"

namespace ibl {
	AStatsBox::AStatsBox( handler_id id, std::string dst )
		: m_Id{ id }
		, m_Destination{ dst }{
	}

	handler_id AStatsBox::GetHandlerId() const {
		return m_Id;
	}

	std::string AStatsBox::GetDestination() const {
		return m_Destination;
	}

	void CStatsCollector::AddComponent( AStatsComponentPtr component ) {
		m_StatComponents.push_back( component );

	}
	CValueContainer CStatsCollector::Gather(CIOCContainer* tools) {
		CValueContainer result;

		for ( auto& component : m_StatComponents ) {
			auto handlers = component->GetHandlers();
			auto boxes = component->GetStatBoxes();

			for ( auto& box : boxes ) {
				auto id = box->GetHandlerId();
				auto dst = box->GetDestination();
				if ( handlers.find( id ) != std::end( handlers ) ) {
					result.Insert( dst, handlers[id]->Handle( box, tools ) );
				}
				else {
					result.Insert( dst, box->ToContainer() );
				}
			}
		}

		return result;
	}
}
