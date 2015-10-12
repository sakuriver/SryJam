#pragma once

#include "SceneBaseClass.h"
#include "KeyboardClass.h"
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>

class SceneManager
{

public: 
	SceneManager();
	~SceneManager();
	void initialize();
	void changeScene(SceneBaseClass* scene);
	void load();
	void update(::Effekseer::Manager* g_manager);
	void render(::Effekseer::Manager* g_manager, ::EffekseerRendererDX9::Renderer* g_renderer);
	void updateScene(::Effekseer::Manager* g_manager);
	void setMainSoundH(int mainSoundH) { this->mainSoundH = mainSoundH; }
	int  getMainSoundH() { return this->mainSoundH ; }
protected:
	KeyboardClass* key;
	SceneBaseClass* nowScene;
	int mainSoundH;
	int deathSoundH;
	int staffrollSoundH;
	int fadeValue;
	void fadeIn();
	void fadeOut();
	void fadeDraw();

};