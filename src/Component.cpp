#include "Component.h"

namespace ibl {
	void CMyComponent::CTrickyBox::Update() {
		m_Counter.happenings++;
		m_Counter.headline = "Oh no!";
	}

	CMyComponent::CTrickyBox::CTrickyBox()
		: AStatsBox( tricky_id, "tricky_box" ) {
	}

	CValueContainer CMyComponent::CTrickyBox::ToContainer() {
		CValueContainer result;

		set_value( result, "happenings", m_Counter.happenings );
		set_value( result, "headline", m_Counter.headline );

		return result;
	}

	CValueContainer CMyComponent::CTrickyHandler::Handle( AStatsBoxPtr box, CIOCContainer* tools ) {
		auto[ILogger, ISomething] = tools->Resolve();

		ILogger->Log( "We are doing something with external dependency which is not available at the definition point!" );

		CTrickyBoxPtr casted_box = std::dynamic_pointer_cast<CTrickyBox>( box );

		CValueContainer result;

		set_value( result, "strange", 6.47f );

		return result;
	}


	void CMyComponent::CPlainBox::Update() {
		// I'm too lazy to change anything here
	}

	CMyComponent::CPlainBox::CPlainBox()
		: AStatsBox( plain_id, "plain" ) {
	}

	CValueContainer CMyComponent::CPlainBox::ToContainer() {
		CValueContainer result;

		set_value( result, "value", m_Counter.value );

		return result;
	}

	std::list<AStatsBoxPtr> CMyComponent::GetStatBoxes() const {
		return { AStatsBoxPtr(m_TrickyBox), AStatsBoxPtr(m_PlainBox) };
	}


	std::map<handler_id, AStatsHandlerPtr> CMyComponent::GetHandlers() const {
		std::map<handler_id, AStatsHandlerPtr> result;

		result[tricky_id] = AStatsHandlerPtr( new CTrickyHandler() );

		return result;
	}
}