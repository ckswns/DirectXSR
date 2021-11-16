#pragma once
#include "Actor.h"

class Cow : public Actor
{
public:		explicit	Cow(void) noexcept { __noop; }
public:		virtual		~Cow(void) noexcept { __noop; }

public:		void		Awake(void) noexcept override;
public:		void		Start(void) noexcept override;
public:		void		FixedUpdate(float fElapsedTime) noexcept override;
public:		void		Update(float fElapsedTime) noexcept override;
public:		void		LateUpdate(float fElapsedTime) noexcept override;
public:		void		OnDestroy(void) noexcept override;
						
public:		void		OnCollisionEnter(Collider* mine, Collider* other) noexcept override;
public:		void		OnCollisionStay(Collider* mine, Collider* other) noexcept override;
public:		void		OnCollisionExit(Collider* mine, Collider* other) noexcept override;

public:		void		GetHit(float damage) noexcept override;
};

