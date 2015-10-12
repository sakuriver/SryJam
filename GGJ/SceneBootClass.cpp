#include "SceneBootClass.h"
#include "DxLib.h"

void SceneBootClass::initialize(::Effekseer::Manager* g_manager) {
	initialized = true;
	playSoundF = false;
	titleLogoFirst = LoadGraph("Resources/title_logo1.png");
	titleLogoSecond = LoadGraph("Resources/title_logo2.png");
	titleLogoThird = LoadGraph("Resources/title_logo3.png");
	titleLogoForth = LoadGraph("Resources/title_logo4.png");
	favGetH = LoadSoundMem("Resources/fav_get.wav");
	cursor = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/cursor.efk");
	count = 0;
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
	}
	else {
		DrawGraph(210, 288, this->titleLogoForth, 1);
		DrawGraph(138, 137, this->titleLogoFirst, 1);
		DrawGraph(489, 195, this->titleLogoSecond, 1);
		DrawGraph(759, 255, this->titleLogoThird, 1);
	}
	
	if (initialized) {
		int mouse_x, mouse_y;
		int cursor_handle = 0;
		GetMousePoint(&mouse_x, &mouse_y);
		cursor_handle = g_manager->Play(cursor, 0.0f, 0.0f, 0.0f);
		g_manager->SetScale(cursor_handle, 10, 10, 10);
		g_manager->SetLocation(cursor_handle,mouse_x, 720 - mouse_y, 0.0f);
    }
}