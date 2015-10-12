#include "SceneTitleClass.h"
#include "SceneMainClass.h"
#include "DxLib.h"

SceneTitleClass::SceneTitleClass(::Effekseer::Manager* g_manager) {
}

void SceneTitleClass::initialize(::Effekseer::Manager* g_manager) {
	this->playSoundF = false;

	this->bgGraphH = LoadGraph("Resources/title_bg.png");
	for (int i = 0; i < 10; i++){
		this->titleStar[i][0] = LoadGraph("Resources/title_star.png");
		this->titleStar[i][1] = createTitleStarPos(400, 1, 1600);
		this->titleStar[i][2] = createTitleStarPos(-100, -1, 800);
	}
	this->titleLogoFirst = LoadGraph("Resources/title_logo1.png");
	this->titleLogoSecond = LoadGraph("Resources/title_logo2.png");
	this->titleLogoThird = LoadGraph("Resources/title_logo3.png");
	this->titleLogoForth = LoadGraph("Resources/title_logo4.png");
	this->titleStartButton = LoadGraph("Resources/title_start_button.png");
	this->favGetH = LoadSoundMem("Resources/fav_get.wav");
	this->initialized = true;
}

void SceneTitleClass::update(::Effekseer::Manager* g_manager) {
	
	if (!this->initialized) {
	    return;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		PlaySoundMem(this->favGetH, DX_PLAYTYPE_BACK);
		this->nextSceneName = "Main";
		this->initialized = false;
	}

	for (int i = 0; i < 10; i++){
		if(this->titleStar[i][2]<720){
			this->titleStar[i][1] -= 4;
			this->titleStar[i][2] += 4;
		}else{
			this->titleStar[i][1] = createTitleStarPos(400, 1, 1600);
			this->titleStar[i][2] = createTitleStarPos(-100, -1, 800);
		}
	}
}

int SceneTitleClass::createTitleStarPos(int base_pos, int base_rate, int rand_max) {
    return base_pos + rand() % rand_max;
}

void SceneTitleClass::render(::Effekseer::Manager* g_manager) {

	if (!this->initialized) {
	    return;
	}

	DrawGraph(0, 0, this->bgGraphH, 0);
	for (int i = 0; i < 10; i++){
		DrawGraph(this->titleStar[i][1], this->titleStar[i][2], this->titleStar[i][0], 1);
	}
	DrawGraph(210, 258, this->titleLogoForth, 1);
	DrawGraph(138, 107, this->titleLogoFirst, 1);
	DrawGraph(489, 165, this->titleLogoSecond, 1);
	DrawGraph(759, 225, this->titleLogoThird, 1);
	DrawGraph(410, 530, this->titleStartButton, 1);
}