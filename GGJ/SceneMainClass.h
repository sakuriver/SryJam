#pragma once

#include "SceneBaseClass.h"
#include "Player_K.h"
#include <vector>
#include "MapObject.h"
#include "Enemy.h"

using namespace std;
class SceneMainClass : public SceneBaseClass
{
public:
	SceneMainClass(){};
	SceneMainClass(int mainSoundH) { this->mainSoundH = mainSoundH; };
	~SceneMainClass(){};
	void initialize(::Effekseer::Manager* g_manager);
	void update(::Effekseer::Manager* g_manager);
	void render(::Effekseer::Manager* g_manager);
private:
	Enemy* boss;
	int stageTime[3];
	Player_K* corona;
	int Time[2];
	std::vector<MapObject*> star;
	std::vector<MapObject*> rt;
	std::vector<MapObject*> kuso;
	std::vector<MapObject*> block;

	//combo
	int comboH;
	int comboLineH;
	int numberlH[11];
	int numbersH[11];
	float remTime;
	float time;
	int gaugeH;
	int gaugeBackH;
	int damage;
	int iconWindowH;
	int favScore;
	int rtScore;
	int icoFavH;
	int icoRtH;
	//ÉÅÉìÉ^ÉãÉQÅ[ÉW
	int hosiH;
	int bossBattleBgmH; 
	int mainSoundH;
	bool bossApeearFlg;
	bool bossDeathFlg;
	bool stageClearFlg;
	int comboNumber;
	int comboStartTime;
	
	//effect
	Effekseer::Effect* body_power;
	Effekseer::Effect* rt_combo_first;
	Effekseer::Effect* rt_combo_second;
	Effekseer::Effect* fav_combo_first;
	Effekseer::Effect* fav_combo_second;
	Effekseer::Effect* boss_death;
};