#pragma once

#include "Animation.h"
#include "Gocart.h"
#include "Mirror.h"
#include "Merry.h"
#include "Ferriswheel.h"
#include "HospitalMgr.h"
#include <vector>

class Gocart;
class Mirror;
class Merry;
class Ferriswheel;
class HospitalMgr;

class Text{
public:
	Gocart* gocart;
	Mirror* mirror;
	Merry*  merry;
	Ferriswheel* ferriswheel;
	HospitalMgr* mgr;
	Text();
	int txtMain(int scene);
private:
	enum {OFF,ON};
	enum {right,left};
	enum {Y_normal,Y_egao,Y_odoroki,Y_naki,Y_konwaku,Y_kizetu};
	enum {W_normal,W_egao,W_odoroki,W_mukanzyo,W_human,W_aseri,W_ikari};
	enum {M_normal,M_egao,M_takawarai,M_nayami,M_ikari};
	int key_flag[3];
	int txt_pic;
	int chara_pic[3][7];
	int fp;
	int n;
	int my_scene;
	int window_LR;
	int txtcount;
	int picflag[2];
	int mode;
	int Eventpic[7];
	int m_window;
	int textset[2];
	int picframe;

	char string_a[66];
	char string_b[66];
	char chara[11];
	char c[2];

	void txtLoad();
	void txtCheck();
	void txtDraw();
	void txtDrawpic();
	void txtKey();
	void txtreset();

	Animation pic;
};