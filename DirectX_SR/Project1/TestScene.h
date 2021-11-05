#pragma once
#include "Scene.h"

namespace ce
{
	class Texture;
}

class TestScene : public Scene
{
public:	explicit	TestScene(void) noexcept;
public: virtual		~TestScene(void) noexcept;

public:	bool		Init(void) noexcept override;
public:	void		FixedUpdate(float fElapsedTime) noexcept override;
public:	void		Update(float fElapsedTime) noexcept override;
public:	void		LateUpdate(float fElapsedTime) noexcept override;
public:	void		Render(float fElapsedTime) noexcept override;
public:	void		Release(void) noexcept override;

private: ce::Texture* _texture;
};

