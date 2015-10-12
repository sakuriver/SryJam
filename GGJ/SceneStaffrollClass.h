
#ifndef _SCENE_STAFROLL_H_
#define _SCENE_STAFROLL_H_
#include "Dxlib.h"
#include <math.h>
#include <list>
#include <stdio.h>
#include "SceneBaseClass.h"

#define MAX_STAFF 6


struct sStaffData
{
	int image;
	int x, y;

	sStaffData()
	:	image( -1 ),
		x( 300 ),
		y( 820 )
	{}
};

class SceneStaffrollClass : public SceneBaseClass
{

public:
    SceneStaffrollClass(){};
	SceneStaffrollClass(int staffrollBgmH);
	~SceneStaffrollClass();
	
	void initialize(::Effekseer::Manager* g_manager);
	void update(::Effekseer::Manager* g_manager);
	void render(::Effekseer::Manager* g_manager);


private:

	// 制御
	enum{
		PROC_INIT,
		PROC_SCROLL,
		PROC_MOVEPLAYER,
		PROC_CHANGE_SCENE,
		_MAX_PROC
	};

	enum {
		//TEX_BG,
		TEX_RESULT,
		TEX_HOME,
		TEX_PLAYER,

		_MAX_TEX
	};

	// 制御
	int mProc;

	int	mTexHandle[_MAX_TEX];		// テクスチャハンドル
	std::list< sStaffData > mStaffData;		// スタッフ文字

	int mResultPosY;
	int mPlayerPosX;
	int mPlayerPosY;
	bool mPlayerRad;
	int mFrameCount;
	int staffrollBgmH;
};

#endif

