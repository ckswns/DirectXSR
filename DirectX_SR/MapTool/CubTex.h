#pragma once
#include "GameObject.h"
class CubTex :  public GameObject
{
public: explicit CubTex();
public: virtual ~CubTex();

public:	bool Init(void) noexcept override;
public: void Update(float fElapsedTime) noexcept override;
public: void Render(void) noexcept override;
public: void Release(void) noexcept override;

};

