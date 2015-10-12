#include "DxLib.h"
#include "Move.h"

/* コンストラクタ */
/* Enemy(画像)のXY値を引数に取り初期化 */
Move::Move(float *e_x, float *e_y){
	this->e_x = e_x;
	this->e_y = e_y;
}

Move::Move(){
}

/* 移動先を設定する */
/* 移動先X値, 移動先Y値, 移動先までにかけるフレーム数 */
/* XY値が-1であればフレーム数だけ待機 */
/* frame値が-1であればE_DEADモードに移行 */
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

/* Moveする際のXの移動量 */
float Move::getDeltaX(){
	return deltaX;
}

/* Moveする際のYの移動量 */
float Move::getDeltaY(){
	return deltaY;
}

/* １移動量に対するフレーム量 */
int Move::getFrame(){
	return frame;
}

/* 経過フレーム */
int Move::getFrameCount(){
	return frameCount;
}

/* フレーム加算 */
void Move::frameCounter(){
	frameCount += 1;
}
