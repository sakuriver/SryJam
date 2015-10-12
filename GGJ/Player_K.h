#pragma once

#include "Unit.h"
#include "Animation.h"
#include "Config.h"

class Player_K : public Unit{

	//向き
	enum direction{
		FRONT = 0,
		BACK,
		LEFT,
		RIGHT,
	};

public:

	Player_K();
	~Player_K(){
	}

	void render()override;
	void updata(bool through)override;

	//座標&向き　セット
	void setXY(const float x, const float y, const int _dic);

	float returnX(){
		return x_;
	}

	float returnY(){
		return y_;
	}

	int getAttackMotionNo(){ return this->attackMotionNo; };

	int getAttackNowMotionFrameNo(){ return this->attackNowMotionFrameNo; };

private:

	//状態に合わせた描写
	void draw();

	//キーボード操作に合わせた動き
	void move();

	//早さ調整
	void speed();

	void reset();

	void collect();

	direction dic;

	PlayerMode state;

	int stand;

	//使用画像数
	const static int ghNum_ = 4;

	//画像格納用変数
	int gh[ghNum_];

	float x_, y_;

	float cmx;
	float cmy;

	bool comboFlag_;

	float fsin[360], fcos[360];

	int i;

	int angle;

	int attackFrameNo[2];

	int attackMotionNo;

	int attackNowMotionFrameNo;

	bool attackStartFlg;

	int attackMotionList[2];

	Animation pAnim;
};