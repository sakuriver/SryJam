#pragma once

#include <vector>
#include "Animation.h"
#include "Player_K.h"
#include "Unit.h"
#include "Move.h"

enum EnemyMode : int{
	E_IDLE = 0,	//使用していない
	E_RUN,		//使用している（停止状態）
	E_EMERGE,	//出現
	E_MOVE,		//移動中
	E_ATTACK,	//攻撃中
	E_DEAD,		//退場
	E_UNKNWON	//状態不明
};

class Enemy : public Animation, public Unit, public Move{
	public:
		Enemy(char*);
		Enemy();
		~Enemy();

		void render()override;
		void update(bool through)override;

		//Enemyとの衝突判定 CD:collision detection
		bool CD(Player_K*);

		//EnemyのX値を取得する関数
		float getX();
		//EnemyのY値を取得する変数
		float getY();

		float getCenterX();
		float getCenterY();

		int getSizeX();
		int getSizeY();

		void setXY(float x, float y);

		void setState(EnemyMode);

		EnemyMode getState() { return this->state; };

	private:

		//Enemyの画像ハンドル
		int imgHandle[3];

		//Enemyの行動パターンを格納する配列
		int mp_fp[3];

		//X座標
		float x;

		//Y座標
		float y;

		//Enemyの中心座標
		float centerX;
		float centerY;

		//Enemyのサイズ
		int sizeX;
		int	sizeY;

		//Enemyの透明度
		int alpha;

		//Enemyの状態
		EnemyMode state;

		//EnemyでAnimationクラスを扱うための変数
		Animation* aniHandle;

		//Enemyを動かすためのMoveクラスの変数
		Move* m;

		//移動先のXY値
		float move_x;
		float move_y;

		//移動先までにかけるフレーム数
		int move_frame;

		//Enemyの動作関数
		void moving();

		//Enemyの表示関数
		void draw();

		//alpha付き表示関数
		//x座標, y座標, alpha値, imageHandle
		void DrawGraphAlpha(float, float, int, int*);

};
