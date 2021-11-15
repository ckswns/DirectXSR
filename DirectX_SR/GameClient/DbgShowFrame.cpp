#include "pch.h"
#include "DbgShowFrame.h"
#include "Text.h"

DbgShowFrame::DbgShowFrame(void) noexcept :
	_text(nullptr)
{
}

void DbgShowFrame::Start(void) noexcept
{
	_text = static_cast<UI::Text*>(gameObject->AddComponent(new UI::Text("", D3DCOLOR_ARGB(255, 255, 0, 0))));
}

void DbgShowFrame::Update(float) noexcept
{
	_text->SetText(std::to_string(TIMEMANAGER->GetFPSCount()).c_str());
}
