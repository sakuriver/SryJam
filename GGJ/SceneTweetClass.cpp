#include "SceneTweetClass.h"
#include "DxLib.h"
#include "KeyBoardClass.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

#define KEY_GET KeyboardClass *key = KeyboardClass::getInstance();

SceneTweetClass::SceneTweetClass()
	:cloud(new Animation)
	, tweet(new Animation)
	, staff(new SceneStaffrollClass)
	, stateNum_(0)
	, upY_(false)
	, feadFlag_(false)
	, befor(new change)
	, count01(0)
	, count02(0)
{
	state_ = scene01;

	count_ = 0;
	y_ = 0;
	speedY = 0;
	enterCount = 0;
	flame = 0;

	loadDataGh();
}


SceneTweetClass::~SceneTweetClass()
{
}

void SceneTweetClass::loadDataGh()
{
	 bg_[0]=LoadGraph("Resources/cloud1.png");
	 bg_[1] = LoadGraph("Resources/cloud2.png");

	 sun_ = LoadGraph("Resources/sun.png");

	 tweet_[0] = LoadGraph("Resources/back2.png");
	 tweet_[1] = LoadGraph("Resources/message.png");
	 tweet_[2] = LoadGraph("Resources/tweet_window.png");
	 tweet_[3] = LoadGraph("Resources/tweet_button.png");

	 playerGh_ = LoadGraph("Resources/player_normal.png");

	 bg_mist = LoadGraph("Resources/flash.png");
}

void SceneTweetClass::render(::Effekseer::Manager* g_manager){
	switch (state_){

	case scene01:
		if (befor->move_change()){
			drawCloud();
		}
		befor->draw();
		break;

	case scene02:
		drawFall();
		break;

	case scene03:
		drawTweet();
		break;

	default:
		break;
	}
}

void SceneTweetClass::update(::Effekseer::Manager* g_manager){
	KEY_GET

	key->update();

	switch (state_){
	case scene04:
		SetFontSize(30);
		ChangeFont("‚l‚r –¾’©");
		DrawGraph(0, 0, tweet_[0], TRUE);
		DrawGraph(137, 177, tweet_[2], TRUE);
		SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(255, 255, 255), GetColor(255, 255, 255)
			, GetColor(255, 255, 255), GetColor(255, 255, 255), GetColor(255, 255, 255)
			, GetColor(255, 255, 255), GetColor(255, 255, 255), GetColor(255, 255, 255)
			, GetColor(255, 255, 255), GetColor(255, 255, 255));
		for (int i = 0; i < 5; i++){
			if (tweetFont_[i ] != 0){
				DrawFormatString(300,280 + i  * 30+speedY, GetColor(0, 0, 0), "%s", tweetFont_[i]);
			}
		}
		flame++;
		if (flame >= 50){
			speedY--;
		}
		break;
	case scene05:
		this->nextSceneName = "Staffroll";
		break;
	default:
		break;
	}

}

void SceneTweetClass::drawCloud(){

	KEY_GET

	if (key->GetPressingCount(KEY_INPUT_RETURN)){
		state_ = scene02;
	}

	DrawGraph(0, 0, tweet_[0], TRUE);


	if (y_ < 500){

		DrawGraph(-count_+300, y_, bg_[0], TRUE);
		DrawGraph(-count_+300 + width, y_, bg_[0], TRUE);
		DrawGraph(-count_+300, y_, bg_[1], TRUE);
		DrawGraph(-count_+300 + width, y_, bg_[1], TRUE);

		DrawGraph(150+y_*3, y_+400+cloud->animationIs(30,0.05,true), playerGh_, TRUE);

		DrawGraph(-1300 - count_*4, 0, bg_mist, TRUE);
	
		if (count_ == 1000){
			upY_ = true;
		}
	
		if (upY_){
			y_++;
		}
		else{
			count_++;
		}
	
	}
	else{
		state_ = scene02;
	}

}

void SceneTweetClass::drawFall(){
	KEY_GET

	DrawGraph(0, 0, tweet_[0], TRUE);

	if (!feadFlag_){
		feadIn(true);
	}
	else{
		DrawGraph(140, 235, tweet_[1], TRUE);
	}

	if (key->GetPressingCount(KEY_INPUT_RETURN)){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		state_ = scene03;
	}

	if (count01 > 100){
		state_ = scene03;
	}

	count01++;

}

void SceneTweetClass::feadSet(int i){

	KEY_GET

	key->update();

	DrawGraph(140, 235, tweet_[1], TRUE);

	if (i_ == 100){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		i_ = 254;
		feadFlag_ = true;
	}

}

void SceneTweetClass::initialize(::Effekseer::Manager* g_manager)
{
	this->initialized = true;
}


void SceneTweetClass::drawTweet(){
	KEY_GET

	SetFontSize(30);
	ChangeFont("‚l‚r –¾’©");
	DrawGraph(0, 0, tweet_[0], TRUE);
	DrawGraph(137, 177, tweet_[2], TRUE);
	SetKeyInputStringColor(GetColor(0, 0, 0), GetColor(255, 255, 255), GetColor(255, 255, 255)
		, GetColor(255, 255, 255), GetColor(255, 255, 255), GetColor(255, 255, 255)
		, GetColor(255, 255, 255), GetColor(255, 255, 255), GetColor(255, 255, 255)
		, GetColor(255, 255, 255), GetColor(255, 255, 255));


	for (int i = 0; i < 5; i++){
		KeyInputString(180, 220 + i * 30, 280, tweetFont_[i], FALSE);
		if (tweetFont_[i][0] != 0){			
			DrawFormatString(180, 220 + i* 30, GetColor(0, 0, 0), "%s", tweetFont_[i]);
		} else {
			state_ = scene05;
			break;
		}
		
	}


	if (count02 > 100){
		state_ = scene04;
	}

	count02++;


}
