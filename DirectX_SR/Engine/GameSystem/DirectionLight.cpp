#include "pch.h"
#include "DirectionLight.h"
#include "Light.h"
#include "ManagerDef.h"

void DirectionLight::Start(void) noexcept
{
	D3DCOLORVALUE c;
	c.a = 1;
	c.r = 1;
	c.g = 1;
	c.b = 1;

	gameObject->AddComponent(new Light(Light::Type::DIRECTIONAL, D3D9DEVICE->GetDevice(), c, 1000));
}

void DirectionLight::Update(float fElapsedTime) noexcept
{

}
