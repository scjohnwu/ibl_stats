#pragma once

#include<cstdint>
#include<list>
#include<vector>
#include<map>
#include<memory>

#include "ValueContainer.h"
#include "IOCContainer.h"

namespace ibl {
	using handler_id = std::uint64_t;

	/**
		Serializable value
	*/
	class AStatsBox {
	protected:
		handler_id m_Id{ 0 };
		std::string m_Destination;
	public:
		AStatsBox( handler_id id, std::string dst );
		virtual ~AStatsBox() = default;

		// Knows WHO can handle it
		// If no handler with such id is provided by the associated component
		// then just use ToContainer which has to store values in a plain manner
		handler_id GetHandlerId() const;
		// Knows where it has to be in the final output
		std::string GetDestination() const;

		virtual CValueContainer ToContainer() = 0;
	};
	using AStatsBoxPtr = std::shared_ptr<AStatsBox>;

	/**
		A visitor pattern implementation
	*/
	class AStatsHandler {
	public:
		virtual ~AStatsHandler() = default;

		// Can handle (visit actually) a box and use any tools provided via IOC
		virtual CValueContainer Handle( AStatsBoxPtr box, CIOCContainer* tools ) = 0;
	};
	using AStatsHandlerPtr = std::shared_ptr<AStatsHandler>;

	/**
		A container in the wild
	*/
	class AStatsComponent {
	public:
		// Can output a custom list of valuable boxes
		virtual std::list<AStatsBoxPtr> GetStatBoxes() const = 0;
		// And a set of "smart" handlers for the specific logic
		virtual std::map<handler_id, AStatsHandlerPtr> GetHandlers() const = 0;
	};
	using AStatsComponentPtr = std::shared_ptr<AStatsComponent>;

	/**
		A big guy who collects the statistics
	*/
	class CStatsCollector {
	protected:
		std::vector<AStatsComponentPtr> m_StatComponents;
	public:
		// To create an hierarchy
		void AddComponent( AStatsComponentPtr component );

		// Give the user apropriate tooling for his needs!
		CValueContainer Gather(CIOCContainer* tools);
	};
}