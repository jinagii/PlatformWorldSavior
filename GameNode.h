#pragma once
#include "Image.h"

/// <summary>
/// �� ���� üũ enum ���
/// </summary>
enum class Game_State
{
	Play = 0,	// �÷��� �� ����
	Edit,		// �� ���� ����
	Stop		// ���� ����(�÷��̾��� ���¿� ���� Clear or Dead)
};

class GameNode
{
protected:
	HDC  _hdc;					// ����(��ũ��) DC
	bool _managerInit;			// �Ŵ��� �ʱ�ȭ �Ǻ�

	Game_State _gameState;		// ���� ������Ʈ

	// ���ҽ� �ε�� �н�(���)����
	string _path;

public:
	GameNode();
	virtual ~GameNode();

	virtual HRESULT Init(void);					//�ʱ�ȭ �Լ�
	virtual HRESULT Init(bool managerInit);		//�ʱ�ȭ �Լ�
	virtual void	Release(void);				//�޸� ���� ����
	virtual void	Update(void);				//������Ʈ(����)
	virtual void	Render(void);				//�׷��ִ� �Լ�
	
	// ȭ��(��ũ��) ���� DC ���
	HDC GetMainDC() { return _hdc; }			

	// �޽��� ���ν���
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	const char* ConvertPath(string path, int type = 0);
};