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
	// ������ ���̾ �ϳ��̴�.
	// ������ ��� -> ������Ʈ -> UI ������ �����ؾ� �Ѵ�. 
	
	// ���
	// ������Ʈ
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

	// ���߿� ��� ������ �ε��� 1�� ������ ��
	// ������Ʈ�� �浹 ó�� �����ؾ� �ϱ� ����
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
	
	// ���⼭�� clear ����� �Ѵ�. 
	// �ٽ� ���ͼ� ����� �� �ش� ���Ͱ�
	// ����� 0�̾�� ����ϴµ� ���ϴ�.
	// nullptr �ʱ�ȭ x, üũ x
	mLayers.clear();
}