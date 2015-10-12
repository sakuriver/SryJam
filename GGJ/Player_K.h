#pragma once

#include "Unit.h"
#include "Animation.h"
#include "Config.h"

class Player_K : public Unit{

	//����
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

	//���W&�����@�Z�b�g
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

	//��Ԃɍ��킹���`��
	void draw();

	//�L�[�{�[�h����ɍ��킹������
	void move();

	//��������
	void speed();

	void reset();

	void collect();

	direction dic;

	PlayerMode state;

	int stand;

	//�g�p�摜��
	const static int ghNum_ = 4;

	//�摜�i�[�p�ϐ�
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