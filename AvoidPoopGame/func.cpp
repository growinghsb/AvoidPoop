#include "Game.h"
#include "Core.h"
#include "EventManager.h"

void ChangeStage(eEVENT_TYPE type, STAGE_MODE mode)
{
	EVENT_STATE info = {type, (UINT)mode, (DWORD_PTR)nullptr};
	ADD_EVENT(info);
}
void CreateObject() {}
void DeleteObject() {}

HBITMAP GetRotatedBitmap(HDC hdc, HDC sourceDC, HBITMAP sourceBitmap, int dest_width, int dest_height, float angle, COLORREF bkColor) {
	// ȸ���� ��Ʈ���� ��¹��� DC
	HDC resultDC = CreateCompatibleDC(hdc);

	// ȸ���� ��Ʈ���� ��¹��� �޸𸮺�Ʈ�� �ڵ� 
	HBITMAP resultBitmap = CreateCompatibleBitmap(hdc, dest_width, dest_height);

	HBITMAP oldBitmap = (HBITMAP)SelectObject(resultDC, resultBitmap);
	DeleteObject(oldBitmap);

	// �̸� ȸ���� ��Ʈ�� ������ ���� ä����
	// ������ ȸ�� �� ������ ����� ������ ���� ä���־� ��
	RECT window = Core::getInstance()->getWindowSize();
	FillRect(resultDC, &window, (HBRUSH)(COLOR_WINDOW + 1));

	// ȸ���� ����(360�й�)��, ���ȴ����� ������ ����
	angle = angle * 3.141592f / 180.f;

	// ȸ���̵���ȯ ��Ŀ� �� cos��Ÿ ���� ���� 
	float cosine = cosf(angle);

	// ȸ���̵���ȯ ��Ŀ� �� sin��Ÿ ���� ���� 
	float sine = sinf(angle);

	// ������ ��ǥ���� ȸ���� ���Ͽ�, �׷��ȸ�带 Ȯ����� �����մϴ�.(�䱸����:��98,NT�̻�) 
	SetGraphicsMode(resultDC, GM_ADVANCED);

	// �������� ǥ���ϴ� 3��3���� ��� ���� 
	XFORM xform;

	// 1�� 1�� ���� ���� (ȸ������) 
	xform.eM11 = cosine;

	// 1�� 2�� ���� ���� (ȸ������) 
	xform.eM12 = sine;

	// 2�� 1�� ���� ���� (ȸ������) 
	xform.eM21 = -sine;

	// 2�� 2�� ���� ���� (ȸ������) 
	xform.eM22 = cosine;

	// 3�� 1�� ���� ���� (X�� �̵� ����) 
	xform.eDx = (FLOAT)dest_width / 2.0f;

	// 3�� 2�� ���� ���� (Y�� �̵� ����) 
	xform.eDy = (FLOAT)dest_height / 2.0f;
	
	// ������ ��ķ�, �μ�DC�� �������� ��ǥ�踦 ��ȯ. 
	// �μ�DC�� ��´������ �޸𸮺�Ʈ���� �����Ƿ�, 
	// �����ϰ� �ִ� �޸𸮺�Ʈ���� ��ǥü�谡 ȸ���ȴ�. 
	SetWorldTransform(resultDC, &xform);

	// ȸ���� �޸�DC��, ���ڷ� ���� ���� �̹��� ����
	BitBlt(resultDC, -(dest_width / 2), -(dest_height / 2), dest_width, dest_height, sourceDC, 0, 0, SRCCOPY);

	// ����� �޸�DC ����
	DeleteObject(resultDC);

	// ȸ���� ��Ʈ�� �ڵ� ����
	return resultBitmap;
}