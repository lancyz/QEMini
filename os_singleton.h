#ifndef SINGLETON_H
#define SINGLETON_H

// ͨ�����������ǵ��뻹�ǵ���
#ifndef UIUTIL_EXPORTS
#define UIUTIL_DLL __declspec(dllimport)
#define UIUTIL_TEMPLATE
#else //EXPORT
#define UIUTIL_DLL __declspec(dllexport)
#define UIUTIL_TEMPLATE __declspec(dllexport)
#endif


#include <stdexcept>
/**************************************************************************
** Program : Singleton pattern
** Author  : ����Ϊ
** Version : 2.0
** Date    : 2003-3-23

  Copyright(c) 2003, all rights reserved.
**************************************************************************/

namespace onesec
{

template<class SubClass>
class UIUTIL_TEMPLATE Singleton
{
private:
	static SubClass		*_instance;
	static bool			_create_by_instance;	//����������ʹ�� Instance ��������ķ�����������
public:
	static	SubClass *  Instance();
protected:
	Singleton() 
	{
		//if(!_create_by_instance)
		//	AfxMessageBox("���ݿ��ļ�����ʧ��(������)��");
       // throw std::runtime_error ("this is a singleton,you must create object by call function Instance");			
	}
};

template<class SubClass>
SubClass * Singleton<SubClass>::Instance ()
{
	if( _instance == 0)
	{
		_create_by_instance = true;			//�������������
		_instance = new SubClass();
		_create_by_instance = false;		//ע�����������
	}
	return _instance;
}

template<class SubClass>
SubClass * Singleton<SubClass>::_instance = 0;

template<class SubClass>
bool Singleton<SubClass>::_create_by_instance = 0;


}



#endif //SINGELTON_H
