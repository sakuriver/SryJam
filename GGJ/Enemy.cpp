#include <vector>
#include <Math.h>
#include "DxLib.h"
#include "Enemy.h"
#include "Move.h"
#include "Animation.h"
#include "KeyboardClass.h"
#include "Player_K.h"
#include "Unit.h"

/*
boss1.txt内にbossを表示させるのに必要な画像のファイルパスが
書き込まれている

Enemy* e = new Enemy("Resources/boss/boss1.txt");

e->updata(true);
e->render()

*/

/* コンストラクタ */
/* bossの画像ファイルパスが記述されたテキストファイルを引数に取る */
Enemy::Enemy(char *str){
	int fp = FileRead_open(str), i=0;

	/* bossの画像ハンドルを格納 */
	imgHandle[0] = LoadGraph("Resources/tori_normal.png");
	imgHandle[1] = LoadGraph("Resources/tori_charge.png");
	imgHandle[2] = LoadGraph("Resources/tori_attack.png");
	mp_fp[0] = FileRead_open("Resources/boss/move_pattern/attack.txt");

	x = 850;
	y = 150;
	GetGraphSize(imgHandle[0], &sizeX, &sizeY);
	centerX = x + sizeX/2;
	centerY = y + sizeY/2;
	alpha = 0;
	state = E_IDLE;

	aniHandle = new Animation();
	
	/* Moveクラスを使用するためEnemyのXY値のアドレスを引数に与える */
	m = new Move(&(this->x), &(this->y));
}

Enemy::Enemy(){
}

/* デコンストラクタ */
Enemy::~Enemy(){
}

/* EnemyのXY値を設定 */
void Enemy::setXY(float x, float y){
	this->x = x;
	this->y = y;
}

/* Enemyのstateを設定 */
void Enemy::setState(EnemyMode state){
	this->state = state;
}

void Enemy::render(){
	draw();
}

/* EnemyのX値取得 */
float Enemy::getX(){
	return x;
}

/* EnemyのY値取得 */
float Enemy::getY(){
	return y;
}

float Enemy::getCenterX(){
	return centerX;
}

float Enemy::getCenterY(){
	return centerY;
}

/* Enemyの画像サイズX */
int Enemy::getSizeX(){
	return sizeX;
}

/* Enemyの画像サイズY */
int Enemy::getSizeY(){
	return this->sizeY;
}

/* プレイヤーとの衝突判定 */
bool Enemy::CD(Player_K* player){
	if (fabs(player->returnX() +140 - this->getCenterX()) < this->getSizeX() / 2 || 
		fabs(player->returnX()+170 - this->getCenterX()) < this->getSizeX() / 2){
		if (fabs(player->returnY() - this->getCenterY() + 90) < this->getSizeY() / 2 ||
			fabs(player->returnY() + 120 - this->getCenterY()) < this->getSizeY() / 2){
			return true;
		}
	}
	return false;
}

/* updata関数(毎フレーム呼び出す) */
void Enemy::updata(bool through){
	KeyboardClass* key = KeyboardClass::getInstance();

	switch (state){
		case E_IDLE:
			state = E_EMERGE;
			break;
		case E_EMERGE:
			if(alpha<255){
				alpha++;
			}else{
				state = E_RUN;
			}
			break;
		case E_RUN:
			if(FileRead_scanf(mp_fp[0], "%f,%f,%d", &move_x, &move_y, &move_frame)==3){
				m->setMove(move_x, move_y, move_frame);
				state = E_MOVE;
			}
			break;
		case E_MOVE:
			moving();
			break;
		case E_ATTACK:
			break;
		case E_DEAD:
			if(alpha>0){
				alpha--;
			}else{
				state = E_UNKNWON;
			}
			break;
		case E_UNKNWON:
			break;
	}
}

void Enemy::draw(){
	switch (state){
		case E_EMERGE:
			DrawGraphAlpha(x, y, alpha, imgHandle);
			break;
		case E_RUN:
			DrawGraphAlpha(x, y, alpha, imgHandle);
			break;
		case E_MOVE:
			DrawGraphAlpha(x, y, alpha, imgHandle);
			break;
		case E_ATTACK:
			DrawGraphAlpha(x, y, alpha, imgHandle);
			break;
		case E_DEAD:
			DrawGraphAlpha(x, y, alpha, imgHandle);
			break;
		case E_UNKNWON:
			break;
	}
}

/* 可変透明度付きDrawGraphF */
void Enemy::DrawGraphAlpha(float x, float y, int alpha, int* img_handle){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraphF(x, y, img_handle[aniHandle->animationIs(3, 0.16, true)], true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

/* Enemyの移動関数 (移動量計算はMove_class) */
void Enemy::moving(){
	setXY(this->x+m->getDeltaX(), this->y+m->getDeltaY());
	if (m->getFrame() == -1){
		state = E_DEAD;
	}else if (m->getFrame()==m->getFrameCount()){
		state = E_RUN;
	}else{
		m->frameCounter();
	}
}