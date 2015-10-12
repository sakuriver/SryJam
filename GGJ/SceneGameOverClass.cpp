#include "SceneGameOverClass.h"
#include "DxLib.h"
#include "KeyBoardClass.h"

SceneGameOverClass::SceneGameOverClass(::Effekseer::Manager* g_manager) {
	this->initialize(g_manager);
}

void SceneGameOverClass::initialize(::Effekseer::Manager* g_manager) {

	this->bgGraphH = LoadGraph("Resources/gameover.png");
	this->continueOffH = LoadGraph("Resources/continue_off.png");
	this->continueOnH = LoadGraph("Resources/continue_on.png");
	this->exitOffH = LoadGraph("Resources/exit_off.png");
	this->exitOnH = LoadGraph("Resources/exit_on.png");
	this->playSoundF = false;
	this->initialized = true;
}

void SceneGameOverClass::update(::Effekseer::Manager* g_manager) {

	KeyboardClass *key = KeyboardClass::getInstance();
	key->update();
	if (key->GetPressingCount(KEY_INPUT_Z)) {
		if (this->menuState == continueSelectMode::continueGame) {
			this->playSoundF = true;
			this->nextSceneName = "Main";
		}
		else if (this->menuState == continueSelectMode::exitGame)
		{
			this->playSoundF = true;
			this->nextSceneName = "Title";
		}
    }

	if (key->GetPressingCount(KEY_INPUT_LEFT)) {
		this->menuState = continueSelectMode::continueGame;
	}

	if (key->GetPressingCount(KEY_INPUT_RIGHT)) {
		this->menuState = continueSelectMode::exitGame;
	}
}


void SceneGameOverClass::render(::Effekseer::Manager* g_manager) {

	DrawGraph(0, 0, this->bgGraphH, 0);
	GetMousePoint(&this->posX, &this->posY);
	if (this->menuState == continueSelectMode::continueGame)
	{
		DrawGraph(580, 640, this->continueOnH, true);
	}
	else {
		DrawGraph(580, 640, this->continueOffH, true);

	}

	if (this->menuState == continueSelectMode::exitGame) {
		DrawGraph(950, 535, this->exitOnH, true);
	}
	else {
		DrawGraph(950, 535, this->exitOffH, true);
	}

}