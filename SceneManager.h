#pragma once
#include "SingletonBase.h"

using namespace std;
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*>           mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	GameNode* _currentScene;	// ���� ��
	GameNode* _loadingScene;	// �ε� ��
	GameNode* _readyScene;		// ��� ��

	mapSceneList _mSceneList;
	mapSceneList _mnLoadingSceneList;

	
public:
	SceneManager();
	~SceneManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	//�� �߰� �Լ�
	GameNode* AddScene(string sceneName, GameNode* scene);

	//�� ����
	HRESULT ChangeScene(string sceneName);
};

