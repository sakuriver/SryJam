#include "SceneMainClass.h"
#include "DxLib.h"

void SceneMainClass::initialize(::Effekseer::Manager* g_manager) {

	this->Time[0] = GetNowCount();

	this->comboNumber = 0;

	this->damage = 0;

	this->favScore = 0;
	this->rtScore = 0;

	this->boss = new Enemy("Resources/boss/boss1.txt");
	this->corona = new Player_K();
	this->bossApeearFlg = false;
	this->bossDeathFlg = false;
	this->stageClearFlg = false;
	this->bossBattleBgmH = LoadSoundMem("Resources/game_boss.ogg");
	this->bgGraphH = LoadGraph("Resources/main_bg.png");

	this->iconWindowH = LoadGraph("Resources/ico_window.png");

	this->comboH = LoadGraph("Resources/combo_window.png");
	this->comboLineH = LoadGraph("Resources/combo_window_line.png");

	this->gaugeH = LoadGraph("Resources/gauge.png");
	this->gaugeBackH = LoadGraph("Resources/gauge_back.png");

	LoadDivGraph("Resources/num_l.png", 11, 11, 1, 60, 100, this->numberlH);

	LoadDivGraph("Resources/num_s.png", 11, 11, 1, 30, 50, this->numbersH);

	this->icoFavH = LoadGraph("Resources/fav_ico_s.png");

	this->icoRtH = LoadGraph("Resources/rt_ico_s.png");

	this->comboNumber = 0;
	this->comboStartTime = 0;

	//(x,y,direction)
	corona->setXY(0, 0, 0);
	

	for (int i = 0; i < 50; i++){
		star.push_back(new MapObject("Resources/fav_ico.png", "Resources/fav_get.wav"));
		rt.push_back(new MapObject("Resources/rt_ico.png", "Resources/rt_get.wav"));
		kuso.push_back(new MapObject("Resources/keee.png", "Resources/kuso_twe.wav"));
		block.push_back(new MapObject("Resources/dkdk.png", "Resources/kuso_twe.wav"));
	}

	this->body_power = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/body_power.efk");
	this->fav_combo_first = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/fav_combo_0.efk");
	this->fav_combo_second = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/fav_combo_2.efk");
	this->rt_combo_first = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/rt_combo_0.efk");
	this->rt_combo_second = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/rt_combo_2.efk");
	this->boss_death = Effekseer::Effect::Create(g_manager, (const EFK_CHAR*)L"Resources/effect/boss_death.efk");
	this->playSoundF = false;

	this->initialized = true;
}

void SceneMainClass::update(::Effekseer::Manager* g_manager) {

	this->Time[1] = GetNowCount();

	for (unsigned int i = 0; i < star.size(); i++){
		
		if (this->corona->getAttackMotionNo() == 1 && star[i]->hitCheck(corona->returnX(), corona->returnY())) {
			int combo_handle = 0; 
			this->comboStartTime = this->Time[1];
			this->comboNumber++;
			if (this->comboNumber >= 3) {
				combo_handle = g_manager->Play(fav_combo_second, 0.0f, 0.0f, 0.0f);
			} else {
				combo_handle = g_manager->Play(fav_combo_first, 0.0f, 0.0f, 0.0f);
			}
			g_manager->SetScale(combo_handle, 20, 20, 20);
			g_manager->SetLocation(combo_handle, corona->returnX() + 140, 720 - corona->returnY() - 90, 0.0f);
			
			this->favScore += (int)(this->comboNumber * 1.5f);
		}
		
		star[i]->updata(corona->returnX(), corona->returnY(), 1);
		
	}

	for (unsigned int i = 0; i < rt.size(); i++){
		
		if (this->corona->getAttackMotionNo() == 1 && rt[i]->hitCheck(corona->returnX(), corona->returnY())) {
			int combo_handle = 0;
			this->comboStartTime = this->Time[1];
			this->comboNumber++;
			if (this->comboNumber >= 3) {
				combo_handle = g_manager->Play(rt_combo_second, 0.0f, 0.0f, 0.0f);
			} else {
				combo_handle = g_manager->Play(rt_combo_first, 0.0f, 0.0f, 0.0f);
			}
			
			g_manager->SetScale(combo_handle, 20, 20, 20);
			g_manager->SetLocation(combo_handle, corona->returnX() + 140, 720 - corona->returnY() - 90, 0.0f);
			this->rtScore+= (int)(this->comboNumber * 1.5f);
		}

		rt[i]->updata(corona->returnX(), corona->returnY(), 3);

	}

	for (unsigned int i = 0; i < kuso.size(); i++){

		if (this->corona->getAttackMotionNo() == 1 && kuso[i]->hitCheck(corona->returnX(), corona->returnY())) {
			this->damage += 20;
		}

		kuso[i]->updata(corona->returnX(), corona->returnY(), 2);

	}

	for (unsigned int i = 0; i < block.size(); i++){

		if (this->corona->getAttackMotionNo() == 1 && block[i]->hitCheck(corona->returnX(), corona->returnY())) {
			this->damage += 24;
		}

		block[i]->updata(corona->returnX(), corona->returnY(), 1);

	}


	if (this->damage <= 99) {
		corona->updata(true);
	}

	if (this->time < 0) {
		
		if (!this->bossApeearFlg) {
			StopSoundMem(this->mainSoundH);
			PlaySoundMem(this->bossBattleBgmH, DX_PLAYTYPE_LOOP);
			this->bossApeearFlg = true;
		}

		this->boss->updata(true);

		if ((this->boss->getState() == EnemyMode::E_ATTACK || this->boss->getState() == EnemyMode::E_MOVE) &&
			this->boss->CD(this->corona) && this->corona->getAttackMotionNo() == 1) {
			this->damage += 30;
		}

	}

	if (this->damage >= 100) {
	    
		if (this->bossApeearFlg) {
			StopSoundMem(this->bossBattleBgmH);
		}
		// ‚±‚ÌŽålŒö‚ÍŽ€‚Ê
		this->nextSceneName = "GameOver";

	}

	// 15•b‚®‚ç‚¢‚É‚µ‚Ä‚¨‚­
	if ((this->Time[0] + 55000) < Time[1] && !this->bossDeathFlg) {
		StopSoundMem(this->bossBattleBgmH);
		this->bossDeathFlg = true;
		int boss_deathH = g_manager->Play(this->boss_death, 0.0f, 0.0f, 0.0f);
		g_manager->SetScale(boss_deathH, 20, 20, 20);
		g_manager->SetLocation(boss_deathH, boss->getCenterX(), boss->getCenterY(), 0.0f);
	}

	if (this->bossDeathFlg && (this->Time[0] + 58000) < Time[1]) {
		this->stageClearFlg = true;
    }

	KeyboardClass* key_ = KeyboardClass::getInstance();
	if (this->stageClearFlg || key_->GetPressingCount(KEY_INPUT_B)) {
		this->nextSceneName = "Tweet";
	}

	if (this->comboStartTime > 0 && this->Time[1] > this->comboStartTime + 1500) {
		this->comboStartTime = 0;
		this->comboNumber = 0;
	}

}


void SceneMainClass::render(::Effekseer::Manager* g_manager) {
	DrawGraph(0, 0, this->bgGraphH, true);

	if (this->time < 0 && this->initialized) {
	    this->boss->render();
	}

	for (unsigned int i = 0; i < star.size(); i++){
		star[i]->render(corona->returnX(), corona->returnY());
	}

	for (unsigned int i = 0; i < rt.size(); i++){
		rt[i]->render(corona->returnX(), corona->returnY());
	}

	for (unsigned int i = 0; i < kuso.size(); i++){
		kuso[i]->render(corona->returnX(), corona->returnY());
	}

	for (unsigned int i = 0; i < block.size(); i++){
		block[i]->render(corona->returnX(), corona->returnY());
	}

	if (this->initialized) {
	    corona->render();
	}

	if (this->initialized && body_power != NULL && corona->getAttackMotionNo() == 1 && corona->getAttackNowMotionFrameNo() == 1) {
		int body_handle = g_manager->Play(body_power, 0.0f, 0.0f, 0.0f);
		g_manager->SetScale(body_handle, 20, 20, 20);
		g_manager->SetLocation(body_handle, corona->returnX() + 140, 720 - corona->returnY() - 90, 0.0f);
	}

	DrawGraph(0, 600, this->comboH, true);
	DrawGraph(0, 600, this->comboLineH, true);

	this->time = (float)(((this->Time[0] + 40000) - this->Time[1]) / 1000.0f);

	int firstTime = (int)(this->time / 10);
	int secondTime = time - (firstTime * 10);

	if (this->initialized ) {
		if (time <= 100 && time >= 0) {
			DrawGraph(1000, 50, this->numberlH[firstTime], true);
			DrawGraph(1060, 50, this->numberlH[secondTime], true);
			DrawGraph(1120, 50, this->numberlH[10], true);
			DrawGraph(1180, 50, this->numberlH[(int)(this->time * 10) % 10], true);
		}
		else {
			DrawGraph(1000, 50, this->numberlH[0], true);
			DrawGraph(1060, 50, this->numberlH[0], true);
			DrawGraph(1120, 50, this->numberlH[10], true);
			DrawGraph(1180, 50, this->numberlH[0], true);
		}
		DrawGraph(690, 610, this->gaugeBackH, true);

		DrawGraph(710, 615, this->iconWindowH, true);

		DrawGraph(730, 620, this->icoFavH, true);

	}


	if (this->favScore > 0) {
		DrawExtendGraph(780, 623, 795, 648, this->numbersH[(int)(this->favScore / 10)], true);
		DrawExtendGraph(800, 623, 815, 648, this->numbersH[(int)(this->favScore % 10)], true);
	}  else if (this->favScore > 99) {
		DrawExtendGraph(780, 623, 795, 648, this->numbersH[9], true);
		DrawExtendGraph(800, 623, 815, 648, this->numbersH[9], true);
    } else{
		DrawExtendGraph(780, 623, 795, 648, this->numbersH[0], true);
		DrawExtendGraph(800, 623, 815, 648, this->numbersH[0], true);
	}

	if (this->rtScore > 0) {
		DrawExtendGraph(950, 623, 965, 648, this->numbersH[(int)(this->rtScore / 10)], true);
		DrawExtendGraph(970, 623, 985, 648, this->numbersH[(int)(this->rtScore % 10)], true);
	} else if (this->rtScore > 99) {
		DrawExtendGraph(950, 623, 965, 648, this->numbersH[9], true);
		DrawExtendGraph(970, 623, 985, 648, this->numbersH[9], true);
	} else {
		DrawExtendGraph(950, 623, 965, 648, this->numbersH[0], true);
		DrawExtendGraph(970, 623, 985, 648, this->numbersH[0], true);
	}

	DrawGraph(900, 620, this->icoRtH, true);

	if (this->initialized) {
		if (this->comboNumber == 0) {
			DrawGraph(65, 630, this->numberlH[0], 1);
			DrawGraph(125, 630, this->numberlH[0], 1);
		}
		else {
			DrawGraph(65, 630, this->numberlH[this->comboNumber / 10], 1);
			DrawGraph(125, 630, this->numberlH[this->comboNumber % 10], 1);
		}

		if (this->damage <= 100) {
			DrawBox(723, 670, 720 + (int)((float)((float)(100 - this->damage) / 100.0f) * 520), 700, GetColor(0, 0, 255), 1);
		}
	}
}