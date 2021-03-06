#pragma once
#include "Behaviour.h"

class Portal : public Behaviour
{
public:		explicit		Portal(const char* key) noexcept;
public:		virtual			~Portal(void) noexcept { __noop; }

public:		void			Start(void) noexcept override;
public:		void			Update(float) noexcept override;

private:	Transform*		_player;
private:	std::string		_sceneKey;
private:	bool			_changeScene = false;
};

