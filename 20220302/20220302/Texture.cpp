#include "pch.h"
#include "Texture.h"

#include "Core.h"

CTexture::CTexture()
	: m_dc(nullptr)
	, m_hBit(nullptr)
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
	// �����ϸ� C ��Ÿ�� ĳ��Ʈ�� �ƴ� ����ȯ �����ڸ� ����ϴ� ���� ��õ��
	m_hBit = static_cast<HBITMAP>(LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE));
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

	if (nullptr == m_hBit)
	{
		// �̹��� �ε� ���� ��
		assert(false);
	}

	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());
	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(m_dc, m_hBit));
	DeleteObject(hPrevBit); // �����ִ� ������ bitmap ����

	GetRotatedBitmap(0, 0, static_cast<int>(m_bitInfo.bmWidth), static_cast<int>(m_bitInfo.bmHeight), 180.);
}
void CTexture::GetRotatedBitmap(int source_x, int source_y, int dest_width, int dest_height, double degree)
{
	// ���� �������� ����� ���ÿ� �ʱ�ȭ ���ִ� �� ��õ��
	// ������ �ʱ�ȭ���� ���� ������ ���� ����ִ� ������ ������� ������ ��ġ�� ��찡 ����

	HDC source_dc = CreateCompatibleDC(m_dc);
	HDC dest_dc = CreateCompatibleDC(m_dc);
	HBITMAP bm_result = CreateCompatibleBitmap(m_dc, dest_width, dest_height);

	HBITMAP hbm_old_source = static_cast<HBITMAP>(SelectObject(source_dc, m_hBit));
	HBITMAP hbm_old_dest = static_cast<HBITMAP>(SelectObject(dest_dc, bm_result));

	HBRUSH brush_back = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH brush_old = static_cast<HBRUSH>(SelectObject(dest_dc, brush_back));

	PatBlt(dest_dc, 0, 0, dest_width, dest_height, PATCOPY);
	DeleteObject(SelectObject(dest_dc, brush_old));

	// degree �� radian���� ����
	float cos_theta = static_cast<float>(cos(DegreeToRadian(degree)));
	float sin_theta = static_cast<float>(sin(DegreeToRadian(degree)));

	// ������ ��ǥ�� ȸ���� ���� �׷��� Ȯ���� ��ȯ
	SetGraphicsMode(dest_dc, GM_ADVANCED);

	XFORM xform = {};
	xform.eM11 = cos_theta;
	xform.eM12 = sin_theta;
	xform.eM21 = -sin_theta;
	xform.eM22 = cos_theta;
	xform.eDx = static_cast<float>(dest_width) / 2.f;
	xform.eDy = static_cast<float>(dest_height) / 2.f;

	SetWorldTransform(dest_dc, &xform);

	// ȸ�� �̹��� ���
	BitBlt(dest_dc, -(dest_width / 2), -(dest_height / 2), dest_width, dest_height, source_dc, source_x, source_y, SRCCOPY);

	// �ڿ� ����
	SelectObject(source_dc, hbm_old_source);
	SelectObject(dest_dc, hbm_old_dest);
	DeleteObject(source_dc);
	DeleteObject(dest_dc);

	m_hBit = bm_result;
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);

	HBITMAP hPrevBit = static_cast<HBITMAP>(SelectObject(m_dc, m_hBit));
	DeleteObject(hPrevBit); // �����ִ� ������ bitmap ����
}



