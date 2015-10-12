#pragma once

#include "SingletonClass.h"

class KeyboardClass : public SingletonClass<KeyboardClass>{
	friend SingletonClass<KeyboardClass>;

public:
	bool update();
	//KeyCodeのキーが押されているフレーム数を取得
	int GetPressingCount(int keyCode);
	//KeyCodeのキーが離されているフレーム数を取得
	int GetReleasingCount(int keyCode);

	char* GetKeyStatus(){ return nowKeyStatus; };

private:

	KeyboardClass();

	//キー総数
	static const int KEY_NUM = 256;
	//押されカウンタ
	int mKeyPressingCount[KEY_NUM];
	//離されカウンタ
	int mKeyReleasingCount[KEY_NUM];

	char nowKeyStatus[KEY_NUM];

	//keyCodeが有効なキー番号かどうか
	bool IsAvailableCode(int keyCode);

};