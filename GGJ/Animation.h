#pragma once
#include "SingletonClass.h"

class Animation{

public:
	Animation();
	virtual ~Animation();
	int animationIs(int num,double setTime,bool isSpiral);

	void Reset();

protected:

	//フェードアウト
	void feadOut(bool isClear);

	//フェードイン
	void feadIn(bool isClear);

	/*
	フェードイン、フェードアウトした時に
	写している画像や同様にフェードイン、フェードアウト音楽があるとき
	引き継いだクラスでこの関数でセットする
	*/
	virtual void feadSet(int i) {}

	int i_;
	
private:
	int time_;
	int count_;
	bool flag_;
	bool feadInFlag_;
	bool feadOutFlag_;
	int ghNum_;
	int inc_;

	//画像を徐々に透明、又は不透明にするための材料
	unsigned int alpha_;
	int add_;

};