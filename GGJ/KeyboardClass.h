#pragma once

#include "SingletonClass.h"

class KeyboardClass : public SingletonClass<KeyboardClass>{
	friend SingletonClass<KeyboardClass>;

public:
	bool update();
	//KeyCode�̃L�[��������Ă���t���[�������擾
	int GetPressingCount(int keyCode);
	//KeyCode�̃L�[��������Ă���t���[�������擾
	int GetReleasingCount(int keyCode);

	char* GetKeyStatus(){ return nowKeyStatus; };

private:

	KeyboardClass();

	//�L�[����
	static const int KEY_NUM = 256;
	//������J�E���^
	int mKeyPressingCount[KEY_NUM];
	//������J�E���^
	int mKeyReleasingCount[KEY_NUM];

	char nowKeyStatus[KEY_NUM];

	//keyCode���L���ȃL�[�ԍ����ǂ���
	bool IsAvailableCode(int keyCode);

};