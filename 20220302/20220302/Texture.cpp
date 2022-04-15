#include "pch.h"
#include "Texture.h"

#include "Core.h"

CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
{
}


CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}


void CTexture::Load(const wstring & _strFilePath) // ������ ��ο��� �������� ��ΰ��� ��
{
	/*
		LoadImage(Hinstance, �̹��� ���, �̹��� Ÿ��
			, ���α���, ���α���, �̹��� �ε� �ɼ�
	*/

	// ������ �� ���� �� �̹����� ���� ���θ� �־�� �ϴµ� 
	// �̹����� �̹������� �� �ٸ� ũ�⸦ ������ ������ ���⼭ ��������
	// ���� default�� 0�� �ִ´�

	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP ,0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBit); // �̹��� �ε� ���н�

	// ��Ʈ���� ����� ���� DC ����
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit); // �����ִ� ������ bitmap ����

	//GetRotatedBitmap(0.f);

	// w 468 h 312
	// ���� ���� ����
	// BITMAP : ��Ʈ���� ���� �����带 �����ϴ� ����ü
	// GetObject() : Ư�� OBJ���� ������ �˷��ִ� �Լ�, �̶� �ڵ�� �־��ִ°� �츮�� ��Ʈ��
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

}
void CTexture::GetRotatedBitmap(float radians)
{
	HDC sourceDC, destDC;
	BITMAP bm;

	HBITMAP hbmResult;
	HBITMAP hbmOldSource;
	HBITMAP hbmOldDest;
	HBRUSH hbrBack;
	HBRUSH hbrOld;

	XFORM xform;

	float cosine, sine;
	int x1, y1, x2, y2, x3, y3, minx, miny, maxx, maxy, w, h;

	// 
	sourceDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());


	destDC = CreateCompatibleDC(CCore::GetInst()->GetMainDC());



	GetObject(m_hBit, sizeof(bm), &bm);

	cosine = cos(radians * 3.14 / 180.f);
	sine = sin(radians * 3.14 / 180.f);


	// ȸ���� �̹����� ������ ���Ѵ�.
	// �� 3����� �������� ������ ����
	x1 = (int)(bm.bmHeight * sine);
	y1 = (int)(bm.bmHeight * cosine);

	x2 = (int)(bm.bmWidth * cosine + bm.bmHeight * sine);
	y2 = (int)(bm.bmHeight * cosine - bm.bmWidth * sine);

	x3 = (int)(bm.bmWidth * cosine);
	y3 = (int)(-bm.bmWidth * sine);

	minx = min(0, min(x1, min(x2, x3)));
	miny = min(0, min(y1, min(y2, y3)));
	maxx = max(0, max(x1, max(x2, x3)));
	maxy = max(0, max(y1, max(y2, y3)));


	// ȸ���� �̹����� ����
	w = maxx - minx;
	h = maxy - miny;



	// ȸ���� �̹��� ���� ũ���� btimap ����
	hbmResult = CreateCompatibleBitmap(m_dc, w, h);

	
	hbmOldSource = (HBITMAP)SelectObject(sourceDC, m_hBit);
	hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);


	// dc �ٲٱ����� ���׸� �̹��� ȸ����Ű�� ����� ����ϱ�
	hbrBack = CreateSolidBrush(RGB(255,0,255));
	hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);

	// �츮 bitmap ��ŭ�� �ٽ� �׷���
	PatBlt(destDC, 0, 0, w, h, PATCOPY);

	// ������ ����
	DeleteObject(SelectObject(destDC, hbrOld));

	SetGraphicsMode(destDC, GM_ADVANCED);
	xform.eM11 = cosine;
	xform.eM12 = -sine;

	xform.eM21 = sine;
	xform.eM22 = cosine;

	xform.eDx = (float)-minx;
	xform.eDy = (float)-miny;

	SetWorldTransform(destDC, &xform);


	// ��ǥ�� �ٲ� dc�� ��Ʈ�� ����
	BitBlt(destDC, 0, 0, bm.bmWidth, bm.bmHeight, sourceDC, 0, 0, SRCCOPY);


	// dc ������
	SelectObject(sourceDC, hbmOldSource);
	SelectObject(destDC, hbmOldDest);

	DeleteDC(sourceDC);
	DeleteDC(destDC);



	m_hBit =  hbmResult;
}



