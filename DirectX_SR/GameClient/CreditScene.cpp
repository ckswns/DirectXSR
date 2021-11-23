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

	_scripts.push_back("����: ������");
	_scripts.push_back("����: �Ӽ���, ������");
	_scripts.push_back("�۾��Ⱓ: 3��");
	_scripts.push_back("��� ��Ʈ");
	_scripts.push_back("");
	_scripts.push_back("������");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("��ƼŬ ������");
	_scripts.push_back("��ƼŬ ��");
	_scripts.push_back("Navigation Mesh(A*)");
	_scripts.push_back("����(Mephisto)");
	_scripts.push_back("�÷��̾�(��ų, UI, ����)");
	_scripts.push_back("��ȯ�� �˰���");
	_scripts.push_back("����");
	_scripts.push_back("������");
	_scripts.push_back("��Ÿ ���� ����");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");

	_scripts.push_back("�Ӽ���");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("����");
	_scripts.push_back("�ͷ��� Splating Texture");
	_scripts.push_back("�κ��丮(Multi Slot)");
	_scripts.push_back("����(����)");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");
	_scripts.push_back("");

	_scripts.push_back("������");
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
	_scripts.push_back("(filesystem�� ���� Ž������ ���ҽ��� �����Ͽ� �ε�� ����)");
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
	_scripts.push_back("UI���¿� ���� �̺�Ʈ ȣ��");
	_scripts.push_back("--Game Client--");
	_scripts.push_back("Actor base");
	_scripts.push_back("Monster Cow");
	_scripts.push_back("Boss Diablo");
	_scripts.push_back("������ ī�޶�");
	_scripts.push_back("GameDataManager");
	_scripts.push_back("��Ƽ�����带 �̿��� �ε� �� �浹����");
	_scripts.push_back("��Ÿ ���� ����");
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
