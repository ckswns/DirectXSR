#include "pch.h"
#include "BillboardTest.h"
#include "Transform.h"
#include "Camera.h"

void BillboardTest::Start(void) noexcept
{

}

void BillboardTest::Update(float) noexcept
{
	Transform* cam = Camera::GetMainCamera()->GetTransform();
	transform->SetLocalEulerAngle(cam->GetBillboardEulerAngle());
}
