#include "pch.h"
#include "ToolScene.h"
#include "EditorCamera.h"
#include "ParticleSys.h"
#include "Transform.h"

bool ToolScene::Init(void) noexcept
{
    //GameObject* pGameObj;
    //pGameObj = new EditorCamera(g_hWnd);
    //InsertGameObject(pGameObj);

    //pGameObj = new ParticleSys();
    //InsertGameObject(pGameObj);

    GameObject* pGameObj;
    pGameObj = GameObject::Instantiate();
    pGameObj->GetTransform()->SetWorldPosition(0, 0, -2.f);
    pGameObj->AddComponent(new EditorCamera(g_hWnd));

    InsertGameObject(pGameObj);

    //pGameObj = GameObject::Instantiate();
    //pGameObj->GetTransform()->SetWorldPosition(0.f, 0, 5.f);
    //pGameObj->AddComponent(new ParticleSys());
    //InsertGameObject(pGameObj);

    return true;
}

void ToolScene::Render(float fElapsedTime) noexcept
{
}
