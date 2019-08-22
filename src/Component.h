#pragma once

#include "Statistics.h"

namespace ibl {
	class CMyComponent : public AStatsComponent {
		struct SMyTrickyCounter {
			int happenings{ 0 };
			std::string headline;
		};

		struct SMyPlainCounter {
			float value{ 3.14f };
		};

		static const handler_id tricky_id = 1;
		static const handler_id plain_id = 2;
	public:
		// One box per stat struct, have to be hidden with utility code
		// macroses and templates
		class CTrickyBox : public AStatsBox {
			SMyTrickyCounter m_Counter;
		public:
			CTrickyBox();
			void Update();
			CValueContainer ToContainer() override;
		};
		using CTrickyBoxPtr = std::shared_ptr<CTrickyBox>;
		CTrickyBoxPtr m_TrickyBox{ new CTrickyBox() };

		// It's tricky so it has a handler
		class CTrickyHandler : public AStatsHandler {
		public:
			CValueContainer Handle( AStatsBoxPtr box, CIOCContainer* tools ) override;
		};

		// Also, just for demonstration purposes
		// This one has no designated handler
		class CPlainBox : public AStatsBox {
			SMyPlainCounter m_Counter;
		public:
			CPlainBox();
			void Update();
			CValueContainer ToContainer() override;
		};
		using CPlainBoxPtr = std::shared_ptr<CPlainBox>;
		CPlainBoxPtr m_PlainBox{ new CPlainBox() };

		std::list<AStatsBoxPtr> GetStatBoxes() const override;
		// And a set of "smart" handlers for the specific logic
		std::map<handler_id, AStatsHandlerPtr> GetHandlers() const override;
	};
	using CMyComponentPtr = std::shared_ptr<CMyComponent>;
}
