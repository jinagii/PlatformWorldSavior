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
	GameNode* _currentScene;	// ÇöÀç ¾À
	GameNode* _loadingScene;	// ·Îµù ¾À
	GameNode* _readyScene;		// ´ë±â ¾À

	mapSceneList _mSceneList;
	mapSceneList _mnLoadingSceneList;

	
public:
	SceneManager();
	~SceneManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	//¾À Ãß°¡ ÇÔ¼ö
	GameNode* AddScene(string sceneName, GameNode* scene);

	//¾À º¯°æ
	HRESULT ChangeScene(string sceneName);
};

