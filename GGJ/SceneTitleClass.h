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
	int createTitleStarPos(int base_pos, int base_rate, int rand_max);
	int titleLogoFirst;
	int titleLogoSecond;
	int titleLogoThird;
	int titleLogoForth;
	int titleStartButton;
	int titleStar[10][3];
	int favGetH;
	Effekseer::Effect* cursor;
};