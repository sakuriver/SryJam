
#include "SceneManager.h"
#include "SceneBootClass.h"
#include "SceneTitleClass.h"
#include "SceneMainClass.h"
#include "SceneGameOverClass.h"
#include "SceneTweetClass.h"
#include "SceneStaffrollClass.h"
#include "DxLib.h"

SceneManager::SceneManager() {
}


void SceneManager::changeScene(SceneBaseClass* scene) {

	this->nowScene = scene;
	this->fadeValue = 255;
}

 void  SceneManager::initialize() {

	// ロゴシーンを読み込み
	this->changeScene(new SceneBootClass());
	this->deathSoundH = LoadSoundMem("Resources/game_death.ogg");
	this->staffrollSoundH = LoadSoundMem("Resources/stafflole_bgm.ogg");
}


void SceneManager::load() {
}

void SceneManager::update(::Effekseer::Manager* g_manager) {
	
	if (!this->nowScene->getInitialize()) {
		this->nowScene->initialize(g_manager);
	}
	else {

		this->nowScene->update(g_manager);
		if (this->nowScene->getNextSceneName() != "") {
			this->updateScene(g_manager);
		}
	}
}

void SceneManager::render(::Effekseer::Manager* g_manager, ::EffekseerRendererDX9::Renderer* g_renderer) {

	SetDrawBright(fadeValue, fadeValue, fadeValue);
	
	this->nowScene->render(g_manager);

	// 頂点バッファに溜まった頂点データを吐き出す/*
	RenderVertex();

	// エフェクトの更新処理を行う
	g_manager->Update();

	// エフェクトの描画開始処理を行う。
	g_renderer->BeginRendering();

	// エフェクトの描画を行う。
	g_manager->Draw();

	// エフェクトの描画終了処理を行う。
	g_renderer->EndRendering();

	// DXライブラリの設定を戻す。
	RefreshDxLibDirect3DSetting();
	
}


void SceneManager::updateScene(::Effekseer::Manager* g_manager) {

	
	if (this->nowScene->getPlaySoundFlag()) {
		PlaySoundMem(this->getMainSoundH(), DX_PLAYTYPE_LOOP);
	}

	if (this->nowScene->getNextSceneName() == "Title") {
		this->nowScene = new SceneTitleClass(g_manager);
	}
	else if (this->nowScene->getNextSceneName() == "Main") {
		this->nowScene = new SceneMainClass(this->mainSoundH);
	}
	else if (this->nowScene->getNextSceneName() == "GameOver") {
		StopSoundMem(this->mainSoundH);
		PlaySoundMem(this->deathSoundH, DX_PLAYTYPE_BACK);
		this->nowScene = new SceneGameOverClass(g_manager);
	}
	else if (this->nowScene->getNextSceneName() == "Tweet") {
		PlaySoundMem(this->staffrollSoundH, DX_PLAYTYPE_LOOP);
		int favNumber = this->nowScene->getFavNumber();
		int rtNumber = this->nowScene->getRtNumber();
		this->nowScene = new SceneTweetClass();
		this->nowScene->setRtNumber(rtNumber);
		this->nowScene->setFavNumber(favNumber);
	} else if (this->nowScene->getNextSceneName() == "Staffroll") {
		char* tweetMessage = this->nowScene->getTweetMessage();
		int favNumber = this->nowScene->getFavNumber();
		int rtNumber = this->nowScene->getRtNumber();
		this->nowScene = new SceneStaffrollClass(this->staffrollSoundH);
		this->nowScene->setTweetMessage(tweetMessage);
		this->nowScene->setRtNumber(rtNumber);
		this->nowScene->setFavNumber(favNumber);
	}
	
	this->nowScene->setNextSceneName("");

}

