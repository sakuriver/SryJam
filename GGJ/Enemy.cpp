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
boss1.txt����boss��\��������̂ɕK�v�ȉ摜�̃t�@�C���p�X��
�������܂�Ă���

Enemy* e = new Enemy("Resources/boss/boss1.txt");

e->updata(true);
e->render()

*/

/* �R���X�g���N�^ */
/* boss�̉摜�t�@�C���p�X���L�q���ꂽ�e�L�X�g�t�@�C���������Ɏ�� */
Enemy::Enemy(char *str){
	int fp = FileRead_open(str), i=0;

	/* boss�̉摜�n���h�����i�[ */
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
	
	/* Move�N���X���g�p���邽��Enemy��XY�l�̃A�h���X�������ɗ^���� */
	m = new Move(&(this->x), &(this->y));
}

Enemy::Enemy(){
}

/* �f�R���X�g���N�^ */
Enemy::~Enemy(){
}

/* Enemy��XY�l��ݒ� */
void Enemy::setXY(float x, float y){
	this->x = x;
	this->y = y;
}

/* Enemy��state��ݒ� */
void Enemy::setState(EnemyMode state){
	this->state = state;
}

void Enemy::render(){
	draw();
}

/* Enemy��X�l�擾 */
float Enemy::getX(){
	return x;
}

/* Enemy��Y�l�擾 */
float Enemy::getY(){
	return y;
}

float Enemy::getCenterX(){
	return centerX;
}

float Enemy::getCenterY(){
	return centerY;
}

/* Enemy�̉摜�T�C�YX */
int Enemy::getSizeX(){
	return sizeX;
}

/* Enemy�̉摜�T�C�YY */
int Enemy::getSizeY(){
	return this->sizeY;
}

/* �v���C���[�Ƃ̏Փ˔��� */
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

/* updata�֐�(���t���[���Ăяo��) */
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

/* �ϓ����x�t��DrawGraphF */
void Enemy::DrawGraphAlpha(float x, float y, int alpha, int* img_handle){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraphF(x, y, img_handle[aniHandle->animationIs(3, 0.16, true)], true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

/* Enemy�̈ړ��֐� (�ړ��ʌv�Z��Move_class) */
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