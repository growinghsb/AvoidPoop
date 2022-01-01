#include "ResourceManager.h"
#include "Texture.h"

ResourceManager* ResourceManager::mResourceManager = nullptr;

ResourceManager::ResourceManager()
	: mAbsolutePullPath{}
	, mLoadResourceList{
	L"player1",
	L"player2",
	L"player3",
	L"player4",
	L"player5",
	L"enemy1",
	L"enemy2",
	L"enemy3",
	L"enemy4",
	L"enemy5",
	L"HPPotion1",
	L"MPPotion1",
	L"bulletPowerPotion1",
	L"bullet0",
	L"bullet1",
	L"bullet2",
	L"bullet3",
	L"bullet4",
	L"missile1",
	L"missileCountUp",
	L"obstacle1",
    L"obstacle2",
    L"obstacle3",
    L"obstacle4",
    L"obstacle5" }
{
	enum { LENGTH = 256 };

	mAbsolutePullPath.reserve(LENGTH);

	wchar_t pullpath[LENGTH] = {};
	GetCurrentDirectory(LENGTH, pullpath);

	int len = (int)wcslen(pullpath);

	for (int i = len - 1; i >= 0; --i)
	{
		if ('\\' == pullpath[i])
		{
			pullpath[i] = '\0';
			break;
		}
	}

	mAbsolutePullPath = pullpath;
	mAbsolutePullPath += L"\\texture";
}

ResourceManager::~ResourceManager()
{
	auto iter = mResources.begin();
	auto endIter = mResources.end();

	while (iter != endIter)
	{
		delete (*iter).second;
		++iter;
	}
	// �Ҹ����̱� ������ �����͸� �����ص� �ȴ�. 
}

ResourceManager* ResourceManager::getInstance()
{
	if (nullptr == mResourceManager)
	{
		mResourceManager = new ResourceManager;
	}
	return mResourceManager;
}

void ResourceManager::deleteInstance()
{
	if (nullptr != mResourceManager)
	{
		delete mResourceManager;
		mResourceManager = nullptr;
	}
}

void ResourceManager::init()
{
	for (int i = 0; i < RESOURCE_COUNT; ++i)
	{
		roadTexture(mLoadResourceList[i]);
	}
}

void ResourceManager::roadTexture(const wchar_t* tag)
{
	auto iter = mResources.find(tag);

	if (iter == mResources.end())
	{
		// ���� ���� �̸����� ������ �ؽ�ó�� ���� �� �ؽ�ó ����
		Texture* texture = new Texture(tag);

		if (texture->load())
		{
			mResources.insert(make_pair(tag, texture));
		}
	}
}

void ResourceManager::roadSound()
{
}