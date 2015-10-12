#pragma once
#include "SceneBaseClass.h"
#include "Animation.h"
#include "DxLib.h"

#include "SceneStaffrollClass.h"
#include "Change.h"

#include <string>

class SceneTweetClass :
	public SceneBaseClass,
	public Animation
{
public:

	SceneTweetClass();
	~SceneTweetClass();

	void initialize(::Effekseer::Manager* g_manager);
	void update(::Effekseer::Manager* g_manager);
	void render(::Effekseer::Manager* g_manager);

private:

	enum State : int {
		scene01 = 0,
		scene02,
		scene03,
		scene04,
		scene05,
		unknown
	}state_;

	void loadDataGh();

	void feadSet(int i)override;

	//�_�`��܂�
	void drawCloud();

	//��ɑ��z����box�������Ă���܂�
	void drawFall();

	//box�`OK�{�^�������܂�
	void drawTweet();


	static const int width = 760;

	//BG
	int bg_[2];
	
	//���z
	int sun_;

	int stateNum_;

	int count_;
	int y_;
	bool upY_;

	//�v���C���[�O���t�B�b�N
	int playerGh_;

	//�t�F�[�h�t���O
	bool feadFlag_;

	//tweet
	int tweet_[4];

	int enterCount;

	int bg_mist;

	int speedY;

	int flame;

	int count01;

	int count02;

	Animation *cloud;
	Animation *tweet;

	SceneStaffrollClass *staff;

	change* befor;


};

