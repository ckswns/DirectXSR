#include "pch.h"
#include "ParticleRenderer.h"
#include "CEMath.h"
#include "TypeDefine.h"
#include <fstream>
#include "GameObject.h"
#include "Assertion.h"

namespace ce
{
    ParticleRenderer::ParticleRenderer(LPDIRECT3DDEVICE9 pDev, std::string fileName) noexcept
		:Component(COMPONENT_ID::RENDERER), _pGraphicDev(pDev),
		_bAwake(true), _bPlay(true), _bLoop(true), _fSpeed(1.f), _fEmitTime(0), _fTime(0),
		_iMaxParticles(50), _fEmitRate(5), _fDuration(5.f), _vBox(Vector3::one), _fRadius(1), _fAngle(25.f), _fHeight(5.f),
		_fileName(fileName)
    {
    }

    void ParticleRenderer::Init(void) noexcept
    {
		//버퍼 최대값 
		_dwVbSize = 4056; //쿼드 1024개
		_dwIbSize = _dwVbSize * 0.5f;

		InitBuffer();

		_dwVbOffset = 0;
		_dwVbBathSize = 1024;//쿼드 256개

		_dwIbOffset = 0;
		_dwIbBathSize = _dwVbBathSize * 0.5f;

		_pTrans = GetGameObject()->GetTransform();

		if (FAILED(D3DXCreateTextureFromFile(_pGraphicDev, L"Asset/SS.tga", &_pTexture)))
		{
			MessageBoxW(NULL, L"Failed", L"Texture Error", MB_OK);
		}

		LoadFromData();
    }

    void ParticleRenderer::FixedUpdate(float) noexcept
    {
    }

    void ParticleRenderer::LateUpdate(float) noexcept
    {
    }

    void ParticleRenderer::Update(float fElapsedTime) noexcept
    {
		fElapsedTime *= 4;

		if (!_bLoop && _bPlay)
		{
			_fTime += fElapsedTime;

			if (_fTime >= _fDuration)
			{
				_bPlay = false;
				//	Reset();
				//	return;
			}
		}

		//초당 파티클 추가
		if (_bPlay)
		{
			_fEmitTime += fElapsedTime;
			if (_fEmitTime >= (1.f / _fEmitRate))
			{
				_fEmitTime = 0;
				AddParticle();
			}
		}

		//파티클 이동
		std::list<Attribute*>::iterator iter;
		//while (iter != _pParticles.end())
		for (iter = _pParticles.begin(); iter != _pParticles.end(); iter++)
		{
			if ((*iter)->_bIsAlive)
			{
				//	(*iter)->_vPosition += (((*iter)->_vVelocity * _fSpeed) + (_vGravity * fElapsedTime)) * fElapsedTime;
				(*iter)->_vPosition += (*iter)->_vVelocity * _fSpeed * fElapsedTime;
				if (_fGravity != 0)
				{
					//float y = -(0.5f * (0.98f * _fGravity) * (*iter)->_fAge * (*iter)->_fAge); //-(((*iter)->_vVelocity.y * (*iter)->_fAge)
					float y = -(0.1f * (0.98f * _fGravity * 100) * (*iter)->_fAge * (*iter)->_fAge);
					(*iter)->_vPosition.y += y;
				}
				(*iter)->_fAge += fElapsedTime;

				if ((*iter)->_fAge > (*iter)->_fLifeTime)
				{
					(*iter)->_bIsAlive = false;
					if (_bLoop && _bPlay)
					{
						ResetParticle(*iter);
					}
				}
				//++iter;
			}
		}

		//빌보드
		D3DXMATRIX	matWorld, matView, matBill;
		D3DXMatrixIdentity(&matBill);

		matWorld = _pTrans->GetWorldMatrix();
		_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

		matBill._11 = matView._11;
		matBill._13 = matView._13;
		matBill._31 = matView._31;
		matBill._33 = matView._33;

		D3DXMatrixInverse(&matBill, NULL, &matBill);
    }

    void ParticleRenderer::Render(void) noexcept
    {
		_pGraphicDev->SetRenderState(D3DRS_LIGHTING, false);

		_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		//_pGraphicDev->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

		_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, false);

		_pGraphicDev->SetTexture(0, _pTexture);

		_pGraphicDev->SetFVF(FVF_VTXCOLTEX);
		_pGraphicDev->SetStreamSource(0, _pVB, 0, sizeof(VTXCOLTEX));
		_pGraphicDev->SetIndices(_pIB);

		D3DXMATRIX	matWorld;
		matWorld = _pTrans->GetWorldMatrix();
		_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);

		if (_dwVbOffset >= _dwVbSize)
		{
			_dwVbOffset = 0;
			_dwIbOffset = 0;
		}
		VTXCOLTEX* v = 0;
		_pVB->Lock(_dwVbOffset * sizeof(VTXCOLTEX),
			_dwVbBathSize * sizeof(VTXCOLTEX),
			(void**)&v,
			_dwVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		INDEX16* pIndex = nullptr;
		_pIB->Lock(_dwIbOffset * sizeof(INDEX16),
			_dwIbBathSize * sizeof(INDEX16),
			(void**)&pIndex,
			_dwIbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		std::list<Attribute*>::iterator iter = _pParticles.begin();
		while (iter != _pParticles.end())
		{
			if ((*iter)->_bIsAlive)
			{
				float size = (*iter)->_fSize * 0.5f;
				v->vPosition = (*iter)->_vPosition + D3DXVECTOR3(-size, size, 0.f);
				v->dwColor = ((*iter)->_dwColor);
				v->vTexUV = D3DXVECTOR2(0.f, 0.f);
				pIndex->_0 = numParticlesInBatch;
				++v;

				v->vPosition = (*iter)->_vPosition + D3DXVECTOR3(size, size, 0.f);
				v->dwColor = ((*iter)->_dwColor);
				v->vTexUV = D3DXVECTOR2(1.f, 0.f);
				pIndex->_1 = numParticlesInBatch + 1;
				++v;

				v->vPosition = (*iter)->_vPosition + D3DXVECTOR3(size, -size, 0.f);
				v->dwColor = ((*iter)->_dwColor);
				v->vTexUV = D3DXVECTOR2(1.f, 1.f);
				pIndex->_2 = numParticlesInBatch + 2;
				++v;

				v->vPosition = (*iter)->_vPosition + D3DXVECTOR3(-size, -size, 0.f);
				v->dwColor = ((*iter)->_dwColor);
				v->vTexUV = D3DXVECTOR2(0.f, 1.f);
				++v;
				++pIndex;

				pIndex->_0 = numParticlesInBatch;
				pIndex->_1 = numParticlesInBatch + 2;
				pIndex->_2 = numParticlesInBatch + 3;
				++pIndex;

				numParticlesInBatch += 4;

				if (numParticlesInBatch == _dwVbBathSize)
				{
					_pVB->Unlock();
					_pIB->Unlock();

					//_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, _dwVbOffset, _dwVbBathSize);
					_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, _dwVbOffset, numParticlesInBatch, _dwIbOffset, (numParticlesInBatch / 2));

					_dwVbOffset += _dwVbBathSize;
					_dwIbOffset += (_dwIbBathSize);
					if (_dwVbOffset >= _dwVbSize)
					{
						_dwVbOffset = 0;
						_dwIbOffset = 0;
					}
					_pVB->Lock(_dwVbOffset * sizeof(VTXCOLTEX),
						_dwVbBathSize * sizeof(VTXCOLTEX),
						(void**)&v,
						_dwVbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					_pIB->Lock(_dwIbOffset * sizeof(INDEX16),
						_dwIbBathSize * sizeof(INDEX16),
						(void**)&pIndex,
						_dwIbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

					numParticlesInBatch = 0;
				}
				++iter;
			}
			else
			{
				Attribute* pParticle = *iter;
				delete pParticle;
				pParticle = nullptr;

				iter = _pParticles.erase(iter);
			}
		}
		_pVB->Unlock();
		_pIB->Unlock();

		if (numParticlesInBatch)
		{
			//_pGraphicDev->DrawPrimitive(D3DPT_TRIANGLESTRIP, _dwVbOffset, numParticlesInBatch);
			_pGraphicDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, _dwVbOffset, numParticlesInBatch, _dwIbOffset, (numParticlesInBatch / 2));
		}
		_dwVbOffset += _dwVbBathSize;

		_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, true);
		_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

		_pGraphicDev->SetRenderState(D3DRS_LIGHTING, true);
    }

    void ParticleRenderer::Release(void) noexcept
    {
		Reset();

		_pVB->Release();
		_pIB->Release();
    }

    void ParticleRenderer::InitBuffer()
    {
		if (FAILED(_pGraphicDev->CreateVertexBuffer(_dwVbSize * sizeof(VTXCOLTEX),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			FVF_PARTICLE,
			D3DPOOL_DEFAULT,
			&_pVB, NULL)))
		{
			MessageBoxW(NULL, L"Failed", L"VertexBuffer Error", MB_OK);
		}

		if (FAILED(_pGraphicDev->CreateIndexBuffer(_dwIbSize * sizeof(INDEX16),
			0, D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&_pIB, NULL)))
		{
			MessageBoxW(NULL, L"Failed", L"IndexBuffer Error", MB_OK);
		}
    }

	inline float ParticleRenderer::SignedRandomf(float max)noexcept
	{
		if (max < 1) return max;

		float f = ce::CE_MATH::Random(1000);
		f *= 0.001f;

		float value = ce::CE_MATH::Random((max * 2));
		if (value >= max)
		{
			value -= max;
			value *= -1;
			value -= f;
		}
		else
			value += f;
		return value;

	}

	inline float ParticleRenderer::UnsignedRandomf(float max)noexcept
	{
		if (max < 1) return max;

		float f = ce::CE_MATH::Random(1000);
		f *= 0.001f;

		float value = ce::CE_MATH::Random(max);

		return value + f;
	}

    void ParticleRenderer::ResetParticle(Attribute* attribute)
    {
		*attribute = _tOrign;

		switch ((SHAPE)_iShape)
		{
		case SHAPE_BOX:
			attribute->_vPosition.x += SignedRandomf((_vBox.x * 0.5f));
			attribute->_vPosition.y += SignedRandomf((_vBox.y * 0.5f));
			attribute->_vPosition.z += SignedRandomf((_vBox.z * 0.5f));
			attribute->_vVelocity = Vector3(0, 1, 0);
			break;
		case SHAPE_CONE:
		{
			float fX = SignedRandomf(_fRadius);
			float fZ = SignedRandomf(_fRadius);
			attribute->_vPosition.x = fX;
			attribute->_vPosition.y = 0;
			attribute->_vPosition.z = fZ;

			float angleX = (_fAngle * (fabs(fX) / _fRadius)) * (CE_MATH::PI / 180);
			float addX = sinf(angleX) * (_fHeight / cosf(angleX));
			if (fX > 0) fX += addX;
			else	fX -= addX;

			float angleZ = (_fAngle * (fabs(fZ) / _fRadius)) * (CE_MATH::PI / 180);
			float addZ = sinf(angleZ) * (_fHeight / cosf(angleZ));
			if (fZ > 0) fZ += addZ;
			else	fZ -= addZ;

			D3DXVECTOR3 vUpper(fX, _fHeight, fZ);
			D3DXVECTOR3 vDir = vUpper - attribute->_vPosition;
			D3DXVec3Normalize(&vDir, &vDir);
			attribute->_vVelocity = vDir;

		}break;

		case SHAPE_SPHERE:
		{
			float x = SignedRandomf(_fRadius);
			float z = SignedRandomf(_fRadius);

			attribute->_vPosition.x += x;
			attribute->_vPosition.z += z;
			/*
			z = r * cos(theta) >> theta = acos(z/r)
			x = sin(theta) * cos(phi)*r >> phi = acos(x / (sin(theta)*r))
			y = r*cos(theta)
			*/
			float theta = acosf((z / _fRadius));

			float maxY = _fRadius * cosf(theta);

			if (maxY < 0) maxY = 1;
			attribute->_vPosition.y += SignedRandomf(maxY);

			Vector3 vDir = attribute->_vPosition - _pTrans->GetLocalPosition();
			attribute->_vVelocity = vDir.Nomalized();
		}	break;

		}
    }

    void ParticleRenderer::AddParticle()
    {
		if (_pParticles.size() >= _iMaxParticles) return;

		Attribute* attribute = new Attribute;
		ResetParticle(attribute);

		_pParticles.push_back(attribute);
    }

    void ParticleRenderer::Reset()
    {
		_fTime = 0.0f;
		_fEmitTime = 0;

		for (auto iter = _pParticles.begin(); iter != _pParticles.end();)
		{
			delete* iter;
			*iter = nullptr;

			iter = _pParticles.erase(iter);
		}

		//for each (auto pParticle in _pParticles)
		//{
		//	delete pParticle;
		//	pParticle = nullptr;
		//}
		//_pParticles.clear();
    }

	void ParticleRenderer::LoadFromData(void) noexcept
	{
		std::ifstream is(_fileName, std::ifstream::binary);

		if (is)
		{
			is.seekg(0, is.end);
			int length = (int)is.tellg();
			is.seekg(0, is.beg);

			byte* buffer = (byte*)malloc(length);

			is.read((char*)buffer, length);
			is.close();

			int index = 0;

			bool awake;
			bool loop;
			float duration;
			float speed;
			float gravity;
			float emitRate;
			int maxParticle;
			int shape;
			D3DXVECTOR3 box;
			float radius;
			float angle;
			float lifeTime;
			float size;
			unsigned long color;

			memcpy(&awake, buffer, sizeof(bool));
			index += sizeof(bool);
			memcpy(&loop, (buffer + index), sizeof(bool));
			index += sizeof(bool);
			memcpy(&duration, (buffer + index), sizeof(float));
			index += sizeof(float);
			memcpy(&speed, (buffer + index), sizeof(float));
			index += sizeof(float);
			memcpy(&gravity, (buffer + index), sizeof(float));
			index += sizeof(float);
			memcpy(&emitRate, (buffer + index), sizeof(float));
			index += sizeof(float);
			memcpy(&maxParticle, (buffer + index), sizeof(int));
			index += sizeof(int);
			memcpy(&shape, (buffer + index), sizeof(int));
			index += sizeof(int);
			memcpy(&box, (buffer + index), sizeof(D3DXVECTOR3));
			index += sizeof(D3DXVECTOR3);
			memcpy(&radius, (buffer + index), sizeof(float));
			index += sizeof(float);
			memcpy(&angle, (buffer + index), sizeof(float));
			index += sizeof(float);
			memcpy(&lifeTime, (buffer + index), sizeof(float));
			index += sizeof(float);
			memcpy(&size, (buffer + index), sizeof(float));
			index += sizeof(float);
			memcpy(&color, (buffer + index), sizeof(unsigned long));
			index += sizeof(unsigned long);

			SetPlayOnAWake(awake);
			SetLoop(loop);
			SetDuration(duration);
			SetSpeed(speed);
			SetGravity(gravity);
			SetEmitRate(emitRate);
			SetMaxParticles(maxParticle);
			SetShape(shape);
			SetBoxSize(box);
			SetRadius(radius);
			SetAngle(angle);
			SetLifeTime(lifeTime);
			SetSize(size);
			SetColor(color);

			free(buffer);
		}
		else
			CE_ASSERT("ckswns", "ParticleRenderer에서 데이터를 읽어오는데에 실패하였습니다");
	}

    void ParticleRenderer::Play()
    {
		_fTime = 0.0f;
		_fEmitTime = 0;
		Reset();
		_bPlay = true;
    }

    void ParticleRenderer::Stop()
    {
		_bPlay = false;

		Reset();
    }
}