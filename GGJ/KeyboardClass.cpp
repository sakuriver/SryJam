#include "KeyboardClass.h"
#include "DxLib.h"

//memsetを用いて配列の初期化
KeyboardClass::KeyboardClass(){
	memset(mKeyPressingCount,0,sizeof(mKeyPressingCount));
	memset(mKeyReleasingCount,0,sizeof(mKeyReleasingCount));
}

//更新
bool KeyboardClass::update(){
	//今のキーの入力状態を取得
	GetHitKeyStateAll(nowKeyStatus);
	for(int i = 0;i<KEY_NUM;++i){
		//i番のキーが押されていたら
		if(nowKeyStatus[i]!=0){
			//離されカウンタが0より大きければ
			if(mKeyReleasingCount[i]>0){
				//0に戻す
				mKeyReleasingCount[i]=0;
			}
			//押されカウンタを増やす
			++mKeyPressingCount[i];//=1
		}
		//i番のキーが離されていたら
		else {
			if (mKeyPressingCount[i] > 0){ //押されカウンタが0より大きければ
				mKeyPressingCount[i] = 0;    //0に戻す
			}
			++mKeyReleasingCount[i];         //離されカウンタを増やす
		}
	}
	return true;
}

//keyCodeのキーが押されているフレーム数を返す
int KeyboardClass::GetPressingCount(int keyCode){
	if (!KeyboardClass::IsAvailableCode(keyCode)){
		return -1;
	}
	return mKeyPressingCount[keyCode];
}

//keyCodeのキーが離されているフレーム数を返す
int KeyboardClass::GetReleasingCount(int keyCode){
	if (!KeyboardClass::IsAvailableCode(keyCode)){
		return -1;
	}
	return mKeyReleasingCount[keyCode];
}

//keyCodeが有効な値かチェックする
bool KeyboardClass::IsAvailableCode(int keyCode){
	if (!(0 <= keyCode && keyCode<KEY_NUM)){
		return false;
	}
	return true;
}