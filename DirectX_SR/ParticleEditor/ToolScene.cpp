#include "pch.h"
#include "ToolScene.h"
#include "EditorCamera.h"
#include "Particle.h"

bool ToolScene::Init(void) noexcept
{
    GameObject* pGameObj;
    pGameObj = new EditorCamera(g_hWnd);
    InsertGameObject(pGameObj);

    pGameObj = new Particle();
    InsertGameObject(pGameObj);

    return true;
}

void ToolScene::Render(float fElapsedTime) noexcept
{
}
