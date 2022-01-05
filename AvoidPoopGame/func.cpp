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
	// 회전할 비트맵을 출력받을 DC
	HDC resultDC = CreateCompatibleDC(hdc);

	// 회전할 비트맵을 출력받을 메모리비트맵 핸들 
	HBITMAP resultBitmap = CreateCompatibleBitmap(hdc, dest_width, dest_height);

	HBITMAP oldBitmap = (HBITMAP)SelectObject(resultDC, resultBitmap);
	DeleteObject(oldBitmap);

	// 미리 회전할 비트맵 공간에 색을 채워둠
	// 이유는 회전 시 공백이 생기기 때문에 색을 채워둬야 함
	RECT window = Core::getInstance()->getWindowSize();
	FillRect(resultDC, &window, (HBRUSH)(COLOR_WINDOW + 1));

	// 회전할 각도(360분법)를, 라디안단위의 각도로 변경
	angle = angle * 3.141592f / 180.f;

	// 회전이동변환 행렬에 들어갈 cos세타 값을 구함 
	float cosine = cosf(angle);

	// 회전이동변환 행렬에 들어갈 sin세타 값을 구함 
	float sine = sinf(angle);

	// 윈도우 좌표계의 회전을 위하여, 그래픽모드를 확장모드로 변경합니다.(요구사항:윈98,NT이상) 
	SetGraphicsMode(resultDC, GM_ADVANCED);

	// 방정식을 표현하는 3행3열의 행렬 선언 
	XFORM xform;

	// 1행 1열 성분 설정 (회전성분) 
	xform.eM11 = cosine;

	// 1행 2열 성분 설정 (회전성분) 
	xform.eM12 = sine;

	// 2행 1열 성분 설정 (회전성분) 
	xform.eM21 = -sine;

	// 2행 2열 성분 설정 (회전성분) 
	xform.eM22 = cosine;

	// 3행 1열 성분 설정 (X축 이동 성분) 
	xform.eDx = (FLOAT)dest_width / 2.0f;

	// 3행 2열 성분 설정 (Y축 이동 성분) 
	xform.eDy = (FLOAT)dest_height / 2.0f;
	
	// 설정한 행렬로, 인수DC의 윈도우즈 좌표계를 변환. 
	// 인수DC는 출력대상으로 메모리비트맵을 가지므로, 
	// 선택하고 있는 메모리비트맵의 좌표체계가 회전된다. 
	SetWorldTransform(resultDC, &xform);

	// 회전된 메모리DC에, 인자로 전달 받은 이미지 복사
	BitBlt(resultDC, -(dest_width / 2), -(dest_height / 2), dest_width, dest_height, sourceDC, 0, 0, SRCCOPY);

	// 사용한 메모리DC 해제
	DeleteObject(resultDC);

	// 회전된 비트맵 핸들 리턴
	return resultBitmap;
}