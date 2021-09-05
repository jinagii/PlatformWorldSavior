#include "pch.h"
#include "SceneManager.h"
#include "GameNode.h"


// 씬 초기화
//GameNode* SceneManager::_currentScene = NULL;
//GameNode* SceneManager::_loadingScene = NULL;
//GameNode* SceneManager::_readyScene = NULL;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

HRESULT SceneManager::Init(void)
{
	_currentScene = NULL;
	_loadingScene = NULL;
	_readyScene = NULL;

	return S_OK;
}

void SceneManager::Release(void)
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			//만약 현재 돌아가는 씬일 경우
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->Release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}
	_mSceneList.clear();
}

void SceneManager::Update(void)
{
	if (_currentScene) _currentScene->Update();
}

void SceneManager::Render(void)
{
	if (_currentScene) _currentScene->Render();
}

//씬 추가 함수
GameNode* SceneManager::AddScene(string sceneName, GameNode* scene)
{
	if (!scene) return NULL;
	
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}
//씬 변경
HRESULT SceneManager::ChangeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//이터레이터가 맵의 끝까지 갔다 == 찾고자 하는게 없다 
	if (find == _mSceneList.end()) return E_FAIL;

	// 현재 씬으로 바꾸려고 할때는 그냥 리턴한다.
	if (find->second == _currentScene) return S_OK;

	// 찾은 씬의 초기화가 성공하면
	if (SUCCEEDED(find->second->Init()))
	{
		//만약 현재씬에 다른 씬이 있다면 해제 해주고
		if (_currentScene) _currentScene->Release();

		//바꾸려는 씬으로 체인지 한다.
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
