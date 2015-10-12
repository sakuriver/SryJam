#include "KeyboardClass.h"
#include "DxLib.h"

//memset��p���Ĕz��̏�����
KeyboardClass::KeyboardClass(){
	memset(mKeyPressingCount,0,sizeof(mKeyPressingCount));
	memset(mKeyReleasingCount,0,sizeof(mKeyReleasingCount));
}

//�X�V
bool KeyboardClass::update(){
	//���̃L�[�̓��͏�Ԃ��擾
	GetHitKeyStateAll(nowKeyStatus);
	for(int i = 0;i<KEY_NUM;++i){
		//i�Ԃ̃L�[��������Ă�����
		if(nowKeyStatus[i]!=0){
			//������J�E���^��0���傫�����
			if(mKeyReleasingCount[i]>0){
				//0�ɖ߂�
				mKeyReleasingCount[i]=0;
			}
			//������J�E���^�𑝂₷
			++mKeyPressingCount[i];//=1
		}
		//i�Ԃ̃L�[��������Ă�����
		else {
			if (mKeyPressingCount[i] > 0){ //������J�E���^��0���傫�����
				mKeyPressingCount[i] = 0;    //0�ɖ߂�
			}
			++mKeyReleasingCount[i];         //������J�E���^�𑝂₷
		}
	}
	return true;
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int KeyboardClass::GetPressingCount(int keyCode){
	if (!KeyboardClass::IsAvailableCode(keyCode)){
		return -1;
	}
	return mKeyPressingCount[keyCode];
}

//keyCode�̃L�[��������Ă���t���[������Ԃ�
int KeyboardClass::GetReleasingCount(int keyCode){
	if (!KeyboardClass::IsAvailableCode(keyCode)){
		return -1;
	}
	return mKeyReleasingCount[keyCode];
}

//keyCode���L���Ȓl���`�F�b�N����
bool KeyboardClass::IsAvailableCode(int keyCode){
	if (!(0 <= keyCode && keyCode<KEY_NUM)){
		return false;
	}
	return true;
}