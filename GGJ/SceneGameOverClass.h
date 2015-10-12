#pragma once

#include "SceneBaseClass.h"

enum continueSelectMode {
	continueGame = 0,
	exitGame = 1
};

class SceneGameOverClass : public SceneBaseClass
{
public:
	SceneGameOverClass(::Effekseer::Manager* g_manager);
	~SceneGameOverClass(){};
	void initialize(::Effekseer::Manager* g_manager);
	void update(::Effekseer::Manager* g_manager);
	void render(::Effekseer::Manager* g_manager);
private:
	int continueOffH;
	int continueOnH;
	int exitOffH;
	int exitOnH;
	int posX;
	int posY;
	
	continueSelectMode menuState;
};