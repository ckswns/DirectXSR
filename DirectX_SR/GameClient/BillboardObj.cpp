#include "pch.h"
#include "BillboardObj.h"
#include "Transform.h"
#include "Camera.h"

void BillboardObj::Start(void) noexcept
{

}

void BillboardObj::Update(float) noexcept
{
	if (Camera::GetMainCamera() == nullptr)
		return;
	Transform* cam = Camera::GetMainCamera()->GetTransform();
	transform->SetLocalEulerAngle(cam->GetBillboardEulerAngleY());
}
