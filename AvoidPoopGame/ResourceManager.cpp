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
	L"defaultBullet1" }
{
	enum { LENGTH = 256 };

	mAbsolutePullPath.reserve(LENGTH);

	wchar_t pullpath[LENGTH] = {};
	GetCurrentDirectory(LENGTH, pullpath);

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
	// 소멸자이기 때문에 포인터만 해제해도 된다. 
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
		// 현재 들어온 이름으로 생성된 텍스처가 없을 때 텍스처 생성
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