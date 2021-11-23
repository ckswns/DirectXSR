#include "pch.h"
#include "FadeController.h"
#include "Image.h"
#include "RectTransform.h"
#include "CETween.h"

FadeController* FadeController::_instance = nullptr;

FadeController::FadeController(void) noexcept
{
	if (FadeController::_instance == nullptr)
		_instance = this;
}

void FadeController::Start(void) noexcept
{
	gameObject->SetDontDestroy(true);
	_image = static_cast<UI::Image*>(gameObject->AddComponent(new UI::Image(ASSETMANAGER->GetTextureData("Asset\\UI\\black.png"))));
	UI::RectTransform* rt = static_cast<UI::RectTransform*>(gameObject->GetComponent(COMPONENT_ID::RECT_TRANSFORM));
	rt->SetWidth(WINCX);
	rt->SetHeight(WINCY);
	gameObject->SetSortOrder(9999);
}

void FadeController::Update(float fElapsedTime) noexcept
{
	if (_doing == false)
		return;

	if (_fadeIn)
	{
		_deltaTime += fElapsedTime;
		_alpha = 255 - CETween::Lerp(0, 255, _deltaTime / _fadeTime);

		_image->SetColor(D3DCOLOR_ARGB((int)_alpha, 255, 255, 255));

		if (_deltaTime >= _fadeTime)
		{
			gameObject->SetActive(false);
			_doing = false;
		}
	}
	
	else if (_fadeOut)
	{
		_deltaTime += fElapsedTime;
		_alpha = CETween::Lerp(0, 255, _deltaTime / _fadeTime);

		_image->SetColor(D3DCOLOR_ARGB((int)_alpha, 255, 255, 255));

		if (_deltaTime >= _fadeTime)
		{
			//gameObject->SetActive(false);
			_doing = false;
		}
	}
}

void FadeController::FadeIn(float time) noexcept
{
	if (_instance == nullptr)
	{
		GameObject* obj = GameObject::Instantiate();
		obj->AddComponent(new FadeController());
	}
	_instance->gameObject->SetActive(true);
	_instance->_doing = true;
	_instance->_fadeIn = true;
	_instance->_fadeOut = false;
	_instance->_deltaTime = 0;
	_instance->_alpha = 255;
	_instance->_fadeTime = time;
}

void FadeController::FadeOut(float time) noexcept
{
	if (_instance == nullptr)
	{
		GameObject* obj = GameObject::Instantiate();
		obj->AddComponent(new FadeController());
	}
	_instance->gameObject->SetActive(true);
	_instance->_doing = true;
	_instance->_fadeIn = false;
	_instance->_fadeOut = true;
	_instance->_deltaTime = 0;
	_instance->_alpha = 0;
	_instance->_fadeTime = time;
}

bool FadeController::IsEnd(void) noexcept
{
	if (_instance == nullptr)
	{
		GameObject* obj = GameObject::Instantiate();
		obj->AddComponent(new FadeController());
		return true;
	}

	if (_instance->_doing == false)
		return true;

	return false;
}
