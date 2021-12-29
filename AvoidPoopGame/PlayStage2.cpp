#include "PlayStage2.h"
#include "ObjLayer.h"

PlayStage2::PlayStage2(int order)
	:Stage(order)
{
	mLayers.reserve(3);
}

PlayStage2::~PlayStage2()
{
	stageClear();
}

void PlayStage2::enter()
{
	init();
}

void PlayStage2::init()
 { 
	// 아직은 레이어가 하나이다.
	// 순서는 배경 -> 오브젝트 -> UI 순으로 저장해야 한다. 
	
	// 배경
	// 오브젝트
	mLayers.push_back(new ObjLayer); 	
	// UI

	int size = (int)mLayers.size();
	for (int i = 0; i < size; ++i)
	{
		mLayers[i]->init();
	}
}

void PlayStage2::update()
{
	int size = (int)mLayers.size();
	for (int i = 0; i < size; ++i)
	{
		mLayers[i]->update();
	}

	// 나중에 배경 들어오면 인덱스 1로 변경할 것
	// 오브젝트들 충돌 처리 진행해야 하기 때문
	ObjLayer* objLayer = (ObjLayer*)mLayers[0];
	objLayer->collision();
}

void PlayStage2::render(HDC backDC)
{
	int size = (int)mLayers.size();
	for (int i = 0; i < size; ++i)
	{
		mLayers[i]->render(backDC);
	}
}

void PlayStage2::exit()
{
	stageClear();
}

void PlayStage2::stageClear()
{
	int size = (int)mLayers.size();
	for (int i = 0; i < size; ++i)
	{
		delete mLayers[i];
	}
	
	// 여기서는 clear 해줘야 한다. 
	// 다시 들어와서 사용할 때 해당 벡터가
	// 사이즈가 0이어야 사용하는데 편하다.
	// nullptr 초기화 x, 체크 x
	mLayers.clear();
}


