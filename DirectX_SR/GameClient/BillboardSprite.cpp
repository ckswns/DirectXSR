#include "pch.h"
#include "BillboardSprite.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Transform.h"

BillboardSprite::BillboardSprite(Texture* tex) noexcept :
	_tex(tex)
{

}

void BillboardSprite::Start(void) noexcept
{
	gameObject->AddComponent(new SpriteRenderer(D3D9DEVICE->GetDevice(), _tex));
}

void BillboardSprite::Update(float) noexcept
{
	Transform* cam = Camera::GetMainCamera()->GetTransform();
	transform->SetLocalEulerAngle(cam->GetBillboardEulerAngleY());
}
