#include "Player_K.h"
#include "KeyboardClass.h"
#include "DxLib.h"

#define sp 5

Player_K::Player_K()
	:stand(0)
	, x_(0)
	, y_(0)
	, state(IDLE)
	, i(0)
	, angle(-1)
	, cmx(0.0f)
	, cmy(0.0f)
	, comboFlag_(false)
{
	gh[0] = LoadGraph("Resources/player_normal.png");
	gh[1] = LoadGraph("Resources/player_charge.png");
	gh[2] = LoadGraph("Resources/player_attack.png");
	gh[3] = LoadGraph("Resources/player_atackend.png");

	for (i = 0; i < 360; i++){
		fsin[i] = (float)sin(i*3.1415926535 / 180);
		fcos[i] = (float)cos(i*3.1415926535 / 180);
	}

	this->attackStartFlg = false;
	this->attackMotionNo = 0;
	this->attackNowMotionFrameNo = 0;
	this->attackFrameNo[0] = 12;
	this->attackFrameNo[1] = 30;
	this->attackMotionList[0] = 1;
	this->attackMotionList[1] = 2;

}

void Player_K::setXY(const float x, const float y, const int _dic){
	x_ = x;
	y_ = y;

	switch (_dic){
	case 0:
		dic = FRONT;
		break;
	case 1:
		dic = BACK;
		break;
	case 2:
		dic = LEFT;
		break;
	case 3:
		dic = RIGHT;
		break;
	}
}

void Player_K::render(){
	draw();
}

void Player_K::updata(bool through){
	KeyboardClass* key_ = KeyboardClass::getInstance();
	if (through){
		key_->update();
		move();
		collect();
	}
	else{
		if (key_->GetPressingCount(KEY_INPUT_RIGHT)){
			this->x_ -= sp;
		}
		else if (key_->GetPressingCount(KEY_INPUT_LEFT)){
			this->x_ += sp;
		}
		else if (key_->GetPressingCount(KEY_INPUT_UP)){
			this->y_ += sp;
		}
		else if (key_->GetPressingCount(KEY_INPUT_DOWN))	{
			this->y_ -= sp;
		}
	}

	if (this->attackStartFlg) {
		this->attackNowMotionFrameNo++;
		if (this->attackFrameNo[this->attackMotionNo] < this->attackNowMotionFrameNo) {

			this->attackMotionNo++;
			this->attackNowMotionFrameNo = 0;
			if (this->attackMotionNo > 1) {
				this->attackStartFlg = false;
				this->attackMotionNo = 0;
			}
		}
	}

}

void Player_K::draw(){
	if (this->attackStartFlg) {	    
		DrawGraphF(x_, y_, gh[this->attackMotionList[this->attackMotionNo]], true);
		return;
	}
	switch (state){
	case IDLE:
		DrawGraphF(x_, y_, gh[0], true);
		break;
	case MOVE:
		DrawGraphF(x_, y_, gh[0], true);
		break;
	case COMBO01:

		//ここでコンボとか実装したかった…
		DrawGraphF(x_, y_, gh[pAnim.animationIs(4, 0.05, false)], true);
		break;

	case COMBO02:
		DrawGraphF(x_, y_, gh[2], true);
		break;
	case COMBO_END:
		DrawGraphF(x_, y_, gh[3], true);
		break;

	}
}

void Player_K::move(){
	
	if (this->attackStartFlg) {
		return;
	}
	
	stand = dic + 1;
	KeyboardClass* key = KeyboardClass::getInstance();

	//泥臭さMAX

	if (key->GetPressingCount(KEY_INPUT_RIGHT)){
		dic = RIGHT;
		state = MOVE;
		angle = 0;
		x_ += sp;
		reset();
	}
	else if (key->GetPressingCount(KEY_INPUT_LEFT)){
		dic = LEFT;
		state = MOVE;
		angle = 180;
		x_ -= sp;
		reset();
	}
	else if (key->GetPressingCount(KEY_INPUT_UP)){
		dic = BACK;
		state = MOVE;
		angle = 90;
		y_ -= sp;
		reset();
	}
	else if (key->GetPressingCount(KEY_INPUT_DOWN))	{
		dic = FRONT;
		state = MOVE;
		angle = 270;
		y_ += sp;
		reset();
	}
	else if (key->GetPressingCount(KEY_INPUT_RIGHT) && key->GetPressingCount(KEY_INPUT_UP)){
		dic = RIGHT;
		state = MOVE;
		angle = 45;
		x_ += sp; y_ -= sp;
		reset();
	}
	else if (key->GetPressingCount(KEY_INPUT_LEFT) && key->GetPressingCount(KEY_INPUT_UP)){
		dic = LEFT;
		state = MOVE;
		angle = 135;
		x_ -= sp; y_ -= sp;
		reset();
	}
	else if (key->GetPressingCount(KEY_INPUT_RIGHT) && key->GetPressingCount(KEY_INPUT_DOWN)){
		dic = RIGHT;
		state = MOVE;
		angle = 315;
		x_ += sp; y_ += sp;
		reset();
	}
	else if (key->GetPressingCount(KEY_INPUT_LEFT) && key->GetPressingCount(KEY_INPUT_DOWN)){
		dic = LEFT;
		state = MOVE;
		angle = 225;
		x_ -= sp; y_ += sp;
		reset();
	}
	else if (key->GetPressingCount(KEY_INPUT_Z)){
		dic = RIGHT;
		state = COMBO01;
		comboFlag_ = true;
	}
	else if (!CheckHitKeyAll(DX_CHECKINPUT_KEY)){
		state = IDLE;
		pAnim.Reset();
		speed();
	}

	if (angle != -1){
		cmx += fcos[angle] * mv;
		cmy -= fsin[angle] * mv;
	}


}

void Player_K::reset(){
	cmx = 0;
	cmy = 0;
}

void Player_K::speed(){
	if (cmx < 5&&cmx > -5){
		x_ += cmx;
	}
	if (cmy < 3 && cmy > -3){
		y_ -= cmy;
	}
}


void Player_K::collect() {

	KeyboardClass* key = KeyboardClass::getInstance();

	if (!this->attackStartFlg && key->GetPressingCount(KEY_INPUT_Z)) {
	
		this->attackStartFlg = true;
		this->attackNowMotionFrameNo = 0;
		this->attackMotionNo = 0;

	}
}

