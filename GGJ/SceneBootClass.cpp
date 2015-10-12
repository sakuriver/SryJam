#include "SceneBootClass.h"
#include "DxLib.h"

void SceneBootClass::initialize(::Effekseer::Manager* g_manager) {
	this->initialized = true;
	this->playSoundF = false;
	this->titleLogoFirst = LoadGraph("Resources/title_logo1.png");
	this->titleLogoSecond = LoadGraph("Resources/title_logo2.png");
	this->titleLogoThird = LoadGraph("Resources/title_logo3.png");
	this->titleLogoForth = LoadGraph("Resources/title_logo4.png");
	this->favGetH = LoadSoundMem("Resources/fav_get.wav");
	this->count = 0;
}

void SceneBootClass::update(::Effekseer::Manager* g_manager) {
	this->count++;

	if (this->count == 400){
		PlaySoundMem(this->favGetH, DX_PLAYTYPE_BACK);
	}

	if (this->count > 500) {
		// 起動ロゴからタイトルシーンへ遷移する
		this->playSoundF = true;
		this->nextSceneName = "Title";
	}
}


void SceneBootClass::render(::Effekseer::Manager* g_manager) {
	if (this->count < 400) {
		DrawGraph(138, 137 - (400 - this->count), this->titleLogoFirst, 1);
		DrawGraph(489, 195 - (400 - this->count), this->titleLogoSecond, 1);
		DrawGraph(759, 255 - (400 - this->count), this->titleLogoThird, 1);
	} else {
		DrawGraph(210, 288, this->titleLogoForth, 1);
		DrawGraph(138, 137, this->titleLogoFirst, 1);
		DrawGraph(489, 195, this->titleLogoSecond, 1);
		DrawGraph(759, 255, this->titleLogoThird, 1);
	}
}