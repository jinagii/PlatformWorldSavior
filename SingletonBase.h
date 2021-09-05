#pragma once

/// SingletonBase 클래스
/// 
/// 엔진에서 사용하는 여러 서브 시스템중에 
/// 싱글톤화 시킬것들을 싱글톤화 해줌
/// 
/// 2020.11.16

template <typename T>
class SingletonBase
{
protected:
	// 접근할 인스턴스(1개만 존재)
	static T* _singleton;

	SingletonBase() {};
	virtual ~SingletonBase() {};

public:
	//싱글톤 접근자
	static T* GetSingleton(void);

	//싱글톤 해제 함수
	void ReleaseSingleton(void);

};

//싱글톤 초기화
template <typename T>
T* SingletonBase<T>::_singleton = nullptr;

template <typename T>
T* SingletonBase<T>::GetSingleton()
{
	//만약에 싱글톤화가 되어있지 않다면 싱글톤 화(템플릿 동적할당) 시켜라
	if (!_singleton) _singleton = new T;

	//그리고 반환
	return _singleton;
}


//싱글톤 해제 함수
template <typename T>
void SingletonBase<T>::ReleaseSingleton(void)
{
	//싱글톤이 있다면
	if (_singleton)
	{
		//동적할당했기때문에 메모리에서 해제시켜라
		delete _singleton;

		_singleton = nullptr;
	}
}