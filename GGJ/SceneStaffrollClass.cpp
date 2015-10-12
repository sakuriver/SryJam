
#include "SceneStaffrollClass.h"

SceneStaffrollClass::SceneStaffrollClass(int staffrollBgmH)
:	mProc( PROC_INIT ),
	mResultPosY( 0 ),
	mPlayerPosX( -100 ),
	mPlayerPosY( 250 ),
	mPlayerRad( true ),
	mFrameCount( 0 )
{
	// テクスチャパス
	const char* path[ _MAX_TEX ] = {
		"Resources/result.png",
		"Resources/button_home.png",
		"Resources/player_normal.png"
	};

	// 背景
	for( int i = 0; i < _MAX_TEX; i++ ) {
		mTexHandle[ i ] = LoadGraph( path[ i ] );
	}

	// スタッフ文字情報
	this->staffrollBgmH = staffrollBgmH;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 1024; j++  ) {
			if (this->tweetFont_[i][j] < 0) {
			    this->tweetFont_[i][j] = '\0';
			}
		}
	}

}

SceneStaffrollClass::~SceneStaffrollClass()
{
}

void SceneStaffrollClass::initialize(::Effekseer::Manager* g_manager)
{
	this->initialized = true;
}

void SceneStaffrollClass::update(::Effekseer::Manager* g_manager)
{
	//int scrollSpeed;
	switch( mProc )
	{
	case PROC_INIT:
		mFrameCount += 2;
		if( mFrameCount >= 100 ){
			mFrameCount = 0;
			mProc = PROC_SCROLL;
		}
		break;

	case PROC_SCROLL:

		// スピード調整
		mResultPosY -= ( CheckHitKey( KEY_INPUT_SPACE ) ) ? 30 : 1;

		// スクロール処理
		if( mResultPosY <= -2000 ) {
			mProc = PROC_MOVEPLAYER;
		}
		break;

	case PROC_MOVEPLAYER:
		if( mPlayerPosY >= 350 ) mPlayerRad = false;
		if( mPlayerPosY <= 200 ) mPlayerRad = true;

		mPlayerPosX += 5;

		if( mPlayerPosX >= 1380 ){
			mProc = PROC_CHANGE_SCENE;
		}
		break;

	case PROC_CHANGE_SCENE:

		// キー入力待機
		if( CheckHitKey( KEY_INPUT_SPACE ) ) {
			// タイトル画面移行
			StopSoundMem(this->staffrollBgmH);
			this->playSoundF = true;
			this->nextSceneName = "Title";
		}
		break;
	}
}

void SceneStaffrollClass::render(::Effekseer::Manager* g_manager)
{
	// 背景描画
	DrawGraph( 0, mResultPosY, mTexHandle[ TEX_RESULT ], true);

	switch( mProc )
	{
	case PROC_INIT:
		break;

	case PROC_SCROLL:

		// 文字描画
		if( !mStaffData.empty() ){
			std::list< sStaffData >::iterator it = mStaffData.begin();
			DrawGraph( it->x, it->y, it->image, true);
		}
		SetFontSize(30);
		ChangeFont("メイリオ");
		for (int i = 0; i < 5; i++) {
			if (tweetFont_[i][0] != -51 && tweetFont_[i][0] != 0) {
				DrawFormatString(275, 260 + mResultPosY + (50 * i), GetColor(0, 0, 0), "%s", tweetFont_[i]);
			}
		}
		SetFontSize(45);
		DrawFormatString(255, 535 + mResultPosY, GetColor(0, 0, 0), "%d", rtNumber);
		DrawFormatString(735, 535 + mResultPosY, GetColor(0, 0, 0), "%d", favNumer);
		break;

	case PROC_MOVEPLAYER:
		DrawGraph( mPlayerPosX, mPlayerPosY, mTexHandle[ TEX_PLAYER ], true);
		break;

	case PROC_CHANGE_SCENE:
		DrawGraph( 400, 500, mTexHandle[ TEX_HOME ], true);
		break;
	}

}