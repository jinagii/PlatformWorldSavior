#pragma once
#include "GameNode.h"
//#include "Map.h"

class Player;
class ObjectBox;
class Map;

class StartScene : public GameNode
{
public:
	

public:
	StartScene();
	~StartScene();

	HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

public:

public:
	
};