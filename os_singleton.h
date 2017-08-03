#ifndef SINGLETON_H
#define SINGLETON_H

// 通过宏来控制是导入还是导出
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
** Author  : 吴龙为
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
	static bool			_create_by_instance;	//避免派生类使用 Instance 函数以外的方法创建对象
public:
	static	SubClass *  Instance();
protected:
	Singleton() 
	{
		//if(!_create_by_instance)
		//	AfxMessageBox("数据库文件创建失败(单例类)！");
       // throw std::runtime_error ("this is a singleton,you must create object by call function Instance");			
	}
};

template<class SubClass>
SubClass * Singleton<SubClass>::Instance ()
{
	if( _instance == 0)
	{
		_create_by_instance = true;			//表明调用者身份
		_instance = new SubClass();
		_create_by_instance = false;		//注销调用者身份
	}
	return _instance;
}

template<class SubClass>
SubClass * Singleton<SubClass>::_instance = 0;

template<class SubClass>
bool Singleton<SubClass>::_create_by_instance = 0;


}



#endif //SINGELTON_H
