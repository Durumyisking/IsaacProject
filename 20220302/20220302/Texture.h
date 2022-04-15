#pragma once
#include "Res.h"
class CTexture :
	public CRes
{

private:
	// �� �� 4����Ʈ ����
	HDC			m_dc;
	HBITMAP		m_hBit;
	BITMAP		m_bitInfo;


private: // �츮�� ��ü������ �����Ҵ� �Ұ����ϰ� private���� ��
		// �ϴ� safe delete���� ��� �����ϰ� public �ص�
	CTexture();
	virtual ~CTexture();

	

public:
	void Load(const wstring& _strFilePath);

	UINT Width() { return m_bitInfo.bmWidth; }
	UINT Height() { return m_bitInfo.bmHeight; }

	HDC GetDC() { return m_dc; }
	HBITMAP GetHBIT() { return m_hBit; }

	// HBITMAP Rotate(HDC _dc, HBITMAP _hBit, float _fRadian);

	void GetRotatedBitmap(float angle);


	friend class CResMgr;
};

