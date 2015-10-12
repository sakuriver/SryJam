#pragma once

#include "SceneBaseClass.h"


class SceneTitleClass : public SceneBaseClass
{
public:
	SceneTitleClass(::Effekseer::Manager* g_manager);
	~SceneTitleClass(){};
	void initialize(::Effekseer::Manager* g_manager);
	void update(::Effekseer::Manager* g_manager);
	void render(::Effekseer::Manager* g_manager);
private:
	int titleLogoFirst;
	int titleLogoSecond;
	int titleLogoThird;
	int titleLogoForth;
	int titleStartButton;
	int titleStar[10][3];
};