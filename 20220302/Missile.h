#pragma once
#include "Object.h"
#include "Texture.h"

class CAnimation;

class CMissile :
	public CObject
{
private:
	float		m_fTheta;	
	Vec2		m_vDir;
	Vec2		m_vStartvec;
	MISSILE_TYPE m_eType;	
	float		m_fModifyXDir;
	float		m_fModifyYDir;

	float		m_fSpeed;

	float		m_fAccFall;

	CTexture*	m_pTex;

	CAnimation*		m_pAnim;
	wstring		m_strAnimName;


public:
	CMissile();
	~CMissile();
public:
	void SetDir(float _fTheta) { m_fTheta = _fTheta; }
	void SetDir(Vec2 _vDir)
	{
		m_vDir = _vDir;
		m_vDir.Normalize();
	}

	void SetType(MISSILE_TYPE _eType) { m_eType = _eType; }
	void SetStartVec(Vec2 _vec) { m_vStartvec = _vec; }

	virtual void PlayAnim(CAnimation* _pAnim, const wstring& _AnimName, Vec2 _vOffset);

public:
	virtual void update();
	virtual void render(HDC _dc);
public:
	void CreateMissile(MISSILE_TYPE _eType, Vec2 _vStartPos, GROUP_TYPE _eShooter);
	CLONE(CMissile);
public:
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
};