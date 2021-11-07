#include "pch.h"
#include "ParticleSys.h"
#include "Particle.h"
#include "BillBordParticle.h"

void ParticleSys::Start(void) noexcept
{
	gameObject->AddComponent(new BillBordParticle(D3D9DEVICE->GetDevice()));
}
