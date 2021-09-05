#pragma once

/// SingletonBase Ŭ����
/// 
/// �������� ����ϴ� ���� ���� �ý����߿� 
/// �̱���ȭ ��ų�͵��� �̱���ȭ ����
/// 
/// 2020.11.16

template <typename T>
class SingletonBase
{
protected:
	// ������ �ν��Ͻ�(1���� ����)
	static T* _singleton;

	SingletonBase() {};
	virtual ~SingletonBase() {};

public:
	//�̱��� ������
	static T* GetSingleton(void);

	//�̱��� ���� �Լ�
	void ReleaseSingleton(void);

};

//�̱��� �ʱ�ȭ
template <typename T>
T* SingletonBase<T>::_singleton = nullptr;

template <typename T>
T* SingletonBase<T>::GetSingleton()
{
	//���࿡ �̱���ȭ�� �Ǿ����� �ʴٸ� �̱��� ȭ(���ø� �����Ҵ�) ���Ѷ�
	if (!_singleton) _singleton = new T;

	//�׸��� ��ȯ
	return _singleton;
}


//�̱��� ���� �Լ�
template <typename T>
void SingletonBase<T>::ReleaseSingleton(void)
{
	//�̱����� �ִٸ�
	if (_singleton)
	{
		//�����Ҵ��߱⶧���� �޸𸮿��� �������Ѷ�
		delete _singleton;

		_singleton = nullptr;
	}
}