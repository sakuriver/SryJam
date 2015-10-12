
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
	this->fadeInFlg = false;
	this->fadeOutFlg = false;
	this->fadeValue = 0;
}

 void  SceneManager::initialize() {

	// ロゴシーンを読み込み
	this->changeScene(new SceneBootClass());
	this->deathSoundH = LoadSoundMem("Resources/game_death.ogg");
	this->staffrollSoundH = LoadSoundMem("Resources/stafflole_bgm.ogg");
	this->fadeInFlg = true;
}


void SceneManager::load() {
}

void SceneManager::update(::Effekseer::Manager* g_manager) {
	
	if (!this->nowScene->getInitialize()) {
		this->nowScene->initialize(g_manager);
	}
	else {

		if (this->fadeInFlg || this->fadeOutFlg) {
			return;
		}

		this->nowScene->update(g_manager);
		if (this->nowScene->getNextSceneName() != "") {
			this->updateScene(g_manager);
		}
	}
}

void SceneManager::render(::Effekseer::Manager* g_manager, ::EffekseerRendererDX9::Renderer* g_renderer) {

	SetDrawBright(fadeValue, fadeValue, fadeValue);
	
	this->nowScene->render(g_manager);

	// 頂点バッファに溜まった頂点データを吐き出す
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
	
	// フェードイン・フェードアウトを呼ぶ
	fadeIn();
	fadeOut();
	fadeDraw();
}


void SceneManager::updateScene(::Effekseer::Manager* g_manager) {

	if (this->fadeOutFlg) {
		return;
	}

	
	if (this->nowScene->getPlaySoundFlag()) {
		PlaySoundMem(this->getMainSoundH(), DX_PLAYTYPE_LOOP);
	}

	if (this->nowScene->getNextSceneName() == "Title") {
		this->fadeOutFlg = true;
		this->nowScene = new SceneTitleClass(g_manager);
	}
	else if (this->nowScene->getNextSceneName() == "Main") {
		this->fadeOutFlg = true;
		this->nowScene = new SceneMainClass(this->mainSoundH);
	}
	else if (this->nowScene->getNextSceneName() == "GameOver") {
		this->fadeOutFlg = true;
		StopSoundMem(this->mainSoundH);
		PlaySoundMem(this->deathSoundH, DX_PLAYTYPE_BACK);
		this->nowScene = new SceneGameOverClass(g_manager);
	}
	else if (this->nowScene->getNextSceneName() == "Tweet") {
		this->fadeOutFlg = true;
		PlaySoundMem(this->staffrollSoundH, DX_PLAYTYPE_LOOP);
		this->nowScene = new SceneTweetClass();
	} else if (this->nowScene->getNextSceneName() == "Staffroll") {
		this->fadeOutFlg = true;
		char* tweetMessage = this->nowScene->getTweetMessage();
		this->nowScene = new SceneStaffrollClass(this->staffrollSoundH);
		this->nowScene->setTweetMessage(tweetMessage);
	}
	
	this->nowScene->setNextSceneName("");

}

void SceneManager::fadeIn() {
	if (!fadeInFlg) {
		return;
	}

	this->fadeValue+=3;

	if (this->fadeValue > 255) {
		this->fadeInFlg = false;
		this->fadeValue = 255;
	}

}

void SceneManager::fadeOut() {
	if (!fadeOutFlg) {
		return;
	}

	this->fadeValue-=3;

	if (this->fadeValue < 0) {
		this->fadeOutFlg = false;
		this->fadeInFlg = true;
		this->fadeValue = 0;
	}

}

void SceneManager::fadeDraw() {

	if (!this->fadeInFlg && !this->fadeOutFlg) {
		return;
	}

	DrawBox(0, 0, 1280, 720, GetColor(255, 255, 255), true);
}

