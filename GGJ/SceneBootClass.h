#pragma once

#include "SceneBaseClass.h"


class SceneBootClass : public SceneBaseClass
{
public:
	SceneBootClass(){};
	~SceneBootClass(){};
	void initialize(::Effekseer::Manager* g_manager);
	void update(::Effekseer::Manager* g_manager);
	void render(::Effekseer::Manager* g_manager);
private:
	int titleLogoFirst;
	int titleLogoSecond;
	int titleLogoThird;
	int titleLogoForth;
	int count;
	int favGetH;
};