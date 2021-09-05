#include "pch.h"
#include "SceneManager.h"
#include "GameNode.h"


// �� �ʱ�ȭ
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
			//���� ���� ���ư��� ���� ���
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

//�� �߰� �Լ�
GameNode* SceneManager::AddScene(string sceneName, GameNode* scene)
{
	if (!scene) return NULL;
	
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}
//�� ����
HRESULT SceneManager::ChangeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//���ͷ����Ͱ� ���� ������ ���� == ã���� �ϴ°� ���� 
	if (find == _mSceneList.end()) return E_FAIL;

	// ���� ������ �ٲٷ��� �Ҷ��� �׳� �����Ѵ�.
	if (find->second == _currentScene) return S_OK;

	// ã�� ���� �ʱ�ȭ�� �����ϸ�
	if (SUCCEEDED(find->second->Init()))
	{
		//���� ������� �ٸ� ���� �ִٸ� ���� ���ְ�
		if (_currentScene) _currentScene->Release();

		//�ٲٷ��� ������ ü���� �Ѵ�.
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
