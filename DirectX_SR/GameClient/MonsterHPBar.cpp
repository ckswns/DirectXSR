#include "pch.h"
#include "MonsterHPBar.h"
#include "Image.h"
#include "Text.h"
#include "Transform.h"
#include "RectTransform.h"

MonsterHPBar* MonsterHPBar::_instance = nullptr;

MonsterHPBar::MonsterHPBar(void) noexcept
{

}

void MonsterHPBar::Start(void) noexcept
{
	GameObject* obj = GameObject::Instantiate();
	obj->GetTransform()->SetParent(transform);
	_frame = static_cast<UI::Image*>(obj->AddComponent(
		new UI::Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Monster\\HPBarFrame.png"))));
	obj->SetSortOrder(0);
	obj->GetTransform()->SetLocalPosition(WINCX / 2 - (_frame->GetTexture()->Width() / 2), 50, 0);
	obj->SetDontDestroy(true);

	obj = GameObject::Instantiate();
	obj->GetTransform()->SetParent(_frame->GetGameObject()->GetTransform());
	_hpBar = static_cast<UI::Image*>(obj->AddComponent(
		new UI::Image(ASSETMANAGER->GetTextureData("Asset\\UI\\Monster\\hpbar.png"))));
	obj->SetSortOrder(1);
	obj->GetTransform()->SetLocalPosition(24, 22, 0);
	obj->SetDontDestroy(true);

	obj = GameObject::Instantiate();
	obj->GetTransform()->SetParent(_hpBar->GetGameObject()->GetTransform());
	obj->SetSortOrder(2);
	_text = static_cast<UI::Text*>(obj->AddComponent(new UI::Text("", D3DCOLOR_ARGB(255, 255, 255, 255), DT_CENTER | DT_VCENTER | DT_NOCLIP)));
	static_cast<UI::RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM))->SetWidth(_hpBar->GetTexture()->Width());
	static_cast<UI::RectTransform*>(obj->GetComponent(COMPONENT_ID::RECT_TRANSFORM))->SetHeight(_hpBar->GetTexture()->Height());

	obj->GetTransform()->SetLocalPosition(0, 0, 0);
	obj->SetDontDestroy(true);
}

void MonsterHPBar::Update(float) noexcept
{
	if (_monster != nullptr)
	{
		_hpBar->SetFillAmount(_monster->GetCurrentHp() / (float)_monster->GetData().maxHP);
	}
}

void MonsterHPBar::SetMonster(Actor* monster) noexcept
{
	_monster = monster;

	if (_monster == nullptr)
	{
		_hpBar->GetGameObject()->SetActive(false);
		_frame->GetGameObject()->SetActive(false);
		_text->GetGameObject()->SetActive(false);
		_text->SetText("");
	}
	else
	{
		_hpBar->GetGameObject()->SetActive(true);
		_frame->GetGameObject()->SetActive(true);
		_text->GetGameObject()->SetActive(true);
		_text->SetText(_monster->GetData().name);
	}
}

MonsterHPBar* const MonsterHPBar::Instance(void) noexcept
{
	if (_instance == nullptr)
	{
		_instance = new MonsterHPBar();
		GameObject* obj = GameObject::Instantiate();
		obj->AddComponent(_instance);
		obj->SetDontDestroy(true);
	}

	return _instance;
}