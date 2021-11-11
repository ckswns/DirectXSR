#pragma once
#include "Scene.h"
#include "Texture.h"

namespace ce
{
	class Texture;
	namespace UI
	{
		class Image;
	}
}

class LoadingScene : public Scene
{
public:		explicit		LoadingScene(void) noexcept;
public:		virtual			~LoadingScene(void) noexcept { __noop; }

public:		bool			Init(void) noexcept override;
public:		void			FixedUpdate(float fElapsedTime) noexcept override;
public:		void			Update(float fElapsedTime) noexcept override;
public:		void			LateUpdate(float fElapsedTime) noexcept override;
public:		void			Render(float fElapsedTime) noexcept override;
public:		void			Release(void) noexcept override;

//public:		void			Test(void) noexcept;

public:		ce::UI::Image*	_imgLogo;
public:		ce::UI::Image*	_imgProgressFront;

private:	ce::Texture*	_texProgressBarBack;
private:	ce::Texture*	_texProgressBarFront;
private:	ce::Texture*	_texBg;
private:	ce::Texture*	_logo[15];

private:	float			_aniTime = 0;
private:	int				_aniIndex = 0;
};

