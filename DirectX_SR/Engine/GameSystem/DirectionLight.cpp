#include "pch.h"
#include "DirectionLight.h"
#include "Light.h"
#include "ManagerDef.h"

bool DirectionLight::Init(void) noexcept
{
	D3DCOLORVALUE c;
	c.a = 1;
	c.r = 1;
	c.g = 1;
	c.b = 1;
	AddComponent(new Light(this, Light::Type::DIRECTIONAL, D3D9DEVICE->GetDevice(), c, 1000));

	_eLayer = GameObjectLayer::OBJECT;

	return true;
}

void DirectionLight::Update(float fElapsedTime) noexcept
{

}

void DirectionLight::Render(void) noexcept
{

}

void DirectionLight::Release(void) noexcept
{

}
