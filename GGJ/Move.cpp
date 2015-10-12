#include "DxLib.h"
#include "Move.h"

/* �R���X�g���N�^ */
/* Enemy(�摜)��XY�l�������Ɏ�菉���� */
Move::Move(float *e_x, float *e_y){
	this->e_x = e_x;
	this->e_y = e_y;
}

Move::Move(){
}

/* �ړ����ݒ肷�� */
/* �ړ���X�l, �ړ���Y�l, �ړ���܂łɂ�����t���[���� */
/* XY�l��-1�ł���΃t���[���������ҋ@ */
/* frame�l��-1�ł����E_DEAD���[�h�Ɉڍs */
void Move::setMove(float m_x, float m_y, int frame){
	if (m_x == -1 && m_y == -1){
		destinationX = *(this->e_x);
		destinationY = *(this->e_x);
	}
	else{
		destinationX = m_x;
		destinationY = m_y;
	}
	this->frame = frame;
	frameCount = 0;
	if(frame!=-1){
		deltaX = (m_x - *e_x) / frame;
		deltaY = (m_y - *e_y) / frame;
	}
}

/* Move����ۂ�X�̈ړ��� */
float Move::getDeltaX(){
	return deltaX;
}

/* Move����ۂ�Y�̈ړ��� */
float Move::getDeltaY(){
	return deltaY;
}

/* �P�ړ��ʂɑ΂���t���[���� */
int Move::getFrame(){
	return frame;
}

/* �o�߃t���[�� */
int Move::getFrameCount(){
	return frameCount;
}

/* �t���[�����Z */
void Move::frameCounter(){
	frameCount += 1;
}
