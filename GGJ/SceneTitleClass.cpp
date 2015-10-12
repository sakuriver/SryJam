#include "SceneTitleClass.h"
#include "SceneMainClass.h"
#include "DxLib.h"

SceneTitleClass::SceneTitleClass(::Effekseer::Manager* g_manager) {
}

void SceneTitleClass::initialize(::Effekseer::Manager* g_manager) {
	playSoundF = false;

	bgGraphH = LoadGraph("Resources/title_bg.png");
	for (int i = 0; i < 10; i++){
		titleStar[i][0] = LoadGraph("Resources/title_star.png");
		titleStar[i][1] = createTitleStarPos(400, 1, 1600);
		titleStar[i][2] = createTitleStarPos(-100, -1, 800);
	}
	titleLogoFirst = LoadGraph("Resources/title_logo1.png");
	titleLogoSecond = LoadGraph("Resources/title_logo2.png");
	titleLogoThird = LoadGraph("Resources/title_logo3.png");
	titleLogoForth = LoadGraph("Resources/title_logo4.png");
	titleStartButton = LoadGraph("Resources/title_start_button.png");
	favGetH = LoadSoundMem("Resources/fav_get.wav");
	cursor = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/cursor.efk");
	initialized = true;
}

void SceneTitleClass::update(::Effekseer::Manager* g_manager) {
	
	if (!this->initialized) {
	    return;
	}

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
	{
		PlaySoundMem(this->favGetH, DX_PLAYTYPE_BACK);
		nextSceneName = "Main";
		initialized = false;
	}

	for (int i = 0; i < 10; i++){
		if(this->titleStar[i][2]<720){
			titleStar[i][1] -= 4;
			titleStar[i][2] += 4;
		}else{
			titleStar[i][1] = createTitleStarPos(400, 1, 1600);
			titleStar[i][2] = createTitleStarPos(-100, -1, 800);
		}
	}
}

int SceneTitleClass::createTitleStarPos(int base_pos, int base_rate, int rand_max) {
    return base_pos + rand() % rand_max;
}

void SceneTitleClass::render(::Effekseer::Manager* g_manager) {

	if (!initialized) {
	    return;
	}

	DrawGraph(0, 0, bgGraphH, 0);
	for (int i = 0; i < 10; i++){
		DrawGraph(titleStar[i][1], titleStar[i][2], titleStar[i][0], 1);
	}
	DrawGraph(210, 258, titleLogoForth, 1);
	DrawGraph(138, 107, titleLogoFirst, 1);
	DrawGraph(489, 165, titleLogoSecond, 1);
	DrawGraph(759, 225, titleLogoThird, 1);
	DrawGraph(410, 530, titleStartButton, 1);

	if (initialized) {
		int mouse_x, mouse_y;
		int cursor_handle = 0;
		GetMousePoint(&mouse_x, &mouse_y);
		cursor_handle = g_manager->Play(cursor, 0.0f, 0.0f, 0.0f);
		g_manager->SetScale(cursor_handle, 10, 10, 10);
		g_manager->SetLocation(cursor_handle, mouse_x, 720 - mouse_y, 0.0f);
	}

}