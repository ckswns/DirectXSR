#include "pch.h"
#include "CreditScene.h"
#include "GameObject.h"
#include "Text.h"
#include "BGMPlayer.h"
#include "CreditScript.h"
#include "Transform.h"
#include "Image.h"
#include "RectTransform.h"

CreditScene::CreditScene(void) noexcept
{
	_scripts.reserve(200);
}

bool CreditScene::Init(void) noexcept
{
	GameObject* obj = GameObject::Instantiate();
	obj->AddComponent(new UI::Image(ASSETMANAGER->GetTextureData("Asset\\UI\\black.png")));
	obj->GetComponent<UI::RectTransform>(COMPONENT_ID::RECT_TRANSFORM)->SetWidth(1280);
	obj->GetComponent<UI::RectTransform>(COMPONENT_ID::RECT_TRANSFORM)->SetHeight(100);
	obj->SetSortOrder(-1);

	_scripts.push_back("팀장: 전찬준");
	_scripts.push_back("팀원: 임수빈, 조성혜");
	_scripts.push_back("작업기간: 3주");
	_scripts.push_back("담당 파트");
	_scripts.push_back("");
	_scripts.push_back("조성혜");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("파티클 렌더러");
	_scripts.push_back("파티클 툴");
	_scripts.push_back("Navigation Mesh(A*)");
	_scripts.push_back("보스(Mephisto)");
	_scripts.push_back("플레이어(스킬, UI, 조작)");
	_scripts.push_back("소환수 알고리즘");
	_scripts.push_back("상점");
	_scripts.push_back("아이템");
	_scripts.push_back("기타 버그 수정");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");

	_scripts.push_back("임수빈");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("맵툴");
	_scripts.push_back("터레인 Splating Texture");
	_scripts.push_back("인벤토리(Multi Slot)");
	_scripts.push_back("몬스터(마녀)");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");

	_scripts.push_back("전찬준");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("--Engine Base--");
	_scripts.push_back("Custom Assert");
	_scripts.push_back("Log");
	_scripts.push_back("Static Memory Pool");
	_scripts.push_back("INI Manager");
	_scripts.push_back("Registry Manager");
	_scripts.push_back("CSV Parser");
	_scripts.push_back("Easing");
	_scripts.push_back("--Base Component--");
	_scripts.push_back("Animation");
	_scripts.push_back("Behaviour");
	_scripts.push_back("Transform");
	_scripts.push_back("--Rendering Component--");
	_scripts.push_back("Camera");
	_scripts.push_back("Light");
	_scripts.push_back("Renderer");
	_scripts.push_back("--Physics Component--");
	_scripts.push_back("Collider(Sphere, Box)");
	_scripts.push_back("RigidBody");
	_scripts.push_back("--Audio Component--");
	_scripts.push_back("Audio Source(2D, 3D)");
	_scripts.push_back("Audio Listener(3D Sound)");
	_scripts.push_back("--Engine GameSystem--");
	_scripts.push_back("GameObject");
	_scripts.push_back("Scene");
	_scripts.push_back("Ray Casting");
	_scripts.push_back("--Management--");
	_scripts.push_back("AssetManager");
	_scripts.push_back("(filesystem를 통한 탐색으로 리소스를 감지하여 로드및 해제)");
	_scripts.push_back("SceneManger");
	_scripts.push_back("Input");
	_scripts.push_back("TimeManager");
	_scripts.push_back("PhysicsManager");
	_scripts.push_back("--Engine Rendering--");
	_scripts.push_back("Texture");
	_scripts.push_back("Material");
	_scripts.push_back("Cube, Quad, Terrain");
	_scripts.push_back("SkyBox");
	_scripts.push_back("--Engine UI--");
	_scripts.push_back("Image");
	_scripts.push_back("Button");
	_scripts.push_back("Text");
	_scripts.push_back("UI상태에 따른 이벤트 호출");
	_scripts.push_back("--Game Client--");
	_scripts.push_back("Actor base");
	_scripts.push_back("Monster Cow");
	_scripts.push_back("Boss Diablo");
	_scripts.push_back("보스방 카메라");
	_scripts.push_back("GameDataManager");
	_scripts.push_back("멀티스레드를 이용한 로딩 및 충돌검출");
	_scripts.push_back("기타 버그 수정");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("THANKS FOR WATCHING");

	BGMPlayer::Instance()->SetBGM(ASSETMANAGER->GetAudioAsset("Asset\\Audio\\outro.mp3"));

	return true;
}

void CreditScene::FixedUpdate(float fElapsedTime) noexcept
{
	_deltaTime += fElapsedTime;
	if (_deltaTime >= 0.5f && _index < _scripts.size())
	{
		_deltaTime = 0;

		GameObject* obj = GameObject::Instantiate();
		obj->AddComponent(new CreditScript(_scripts[_index].c_str()));
		obj->GetTransform()->SetWorldPosition(0, 900, 0);
		obj->SetSortOrder(_index);
		_index++;
	}
}

void CreditScene::Update(float fElapsedTime) noexcept
{

}

void CreditScene::LateUpdate(float fElapsedTime) noexcept
{

}

void CreditScene::Render(float fElapsedTime) noexcept
{

}

void CreditScene::Release(void) noexcept
{

}
