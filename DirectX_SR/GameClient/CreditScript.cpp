#include "pch.h"
#include "CreditScript.h"
#include "Transform.h"
#include "Text.h"
#include "RectTransform.h"

CreditScript::CreditScript(std::string str) noexcept :
	_str(str)
{

}

void CreditScript::Start(void) noexcept
{
	gameObject->AddComponent(new UI::Text(_str.c_str(), D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER));
	gameObject->GetComponent<UI::RectTransform>(COMPONENT_ID::RECT_TRANSFORM)->SetWidth(1280);
	gameObject->GetComponent<UI::RectTransform>(COMPONENT_ID::RECT_TRANSFORM)->SetHeight(100);
}

void CreditScript::Update(float fElapsedTime) noexcept
{
	transform->Translate(0, -100 * fElapsedTime, 0);
	//if (transform->GetWorldPosition().y < -10)
	//	gameObject->Destroy();
}
