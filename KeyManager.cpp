#include "pch.h"
#include "KeyManager.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

HRESULT KeyManager::Init()
{
    // ��� Ű�� ���ؼ� �ȴ��� ���·� ����
    for (int i = 0; i < KEYMAX; i++)
    {
        this->SetKeyUp(i, false);
        this->SetKeyDown(i, false);

    }
    return S_OK;
}

void KeyManager::Release()
{
}

bool KeyManager::IsOnceKeyDown(int key)
{
    // �̹� �����ӿ� key�� ��������
    if (GetAsyncKeyState(key) & 0x8000)
    {
        // ���� ���ð��� false(�ȴ������־��ٸ�)
        if (!_keyDown[key])
        {
            // key down ���·� ����
            this->SetKeyDown(key, true);

            // IsOnceKeyDown(key) == true
            return true;
        }

        // �������� ������ �־��ٸ�
        // �ƹ��͵� ����
    }

    // �̹� �����ӿ� key�� ������ �ʾҴٸ� 
    else
    {
        this->SetKeyDown(key, false);
    }

    // IsOnceKeyDown(key) == false
    return false;
}

/// <summary>
/// keyUp�� ���� �ʿ�
/// ���� ���� �۵����� ����
/// </summary>
bool KeyManager::IsOnceKeyUp(int key)
{
    // �̹��� ������ �ʾҰ�
    if (!(GetAsyncKeyState(key) & 0x8000))
    {
        // ������ ���õ� ���� true���
        // �������� up ���¿��ٸ�
        if(this->GetKeyUp(key))
        
        return false;
    }

    // �̹��� key�� ������ ���¸�
    else
    {
        this->SetKeyUp(key, false);
    }

    return false;
}
/// ���� �ڵ�� �����ʿ�(�۵�X)


bool KeyManager::IsStayKeyDown(int key)
{
    // �̹� ������ Ű�� ������ �ִٸ�
    if (GetAsyncKeyState(key) & 0x8000)
    {
        this->SetKeyDown(key, true);
        return true;
    }

    // �������� �������
    return false;
}
