#pragma once

template <typename T_>
class SingletonClass{
protected:

	SingletonClass(void){};
	virtual ~SingletonClass(){};
	SingletonClass(const SingletonClass& obj){};
	SingletonClass& operator=(const SingletonClass& obj){};

public:
	static T_* getInstance(void){
		static T_ obj;
		return &obj;
	}

};