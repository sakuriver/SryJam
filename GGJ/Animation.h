#pragma once
#include "SingletonClass.h"

class Animation{

public:
	Animation();
	virtual ~Animation();
	int animationIs(int num,double setTime,bool isSpiral);

	void Reset();

protected:

	//�t�F�[�h�A�E�g
	void feadOut(bool isClear);

	//�t�F�[�h�C��
	void feadIn(bool isClear);

	/*
	�t�F�[�h�C���A�t�F�[�h�A�E�g��������
	�ʂ��Ă���摜�⓯�l�Ƀt�F�[�h�C���A�t�F�[�h�A�E�g���y������Ƃ�
	�����p�����N���X�ł��̊֐��ŃZ�b�g����
	*/
	virtual void feadSet(int i) {}

	int i_;
	
private:
	int time_;
	int count_;
	bool flag_;
	bool feadInFlag_;
	bool feadOutFlag_;
	int ghNum_;
	int inc_;

	//�摜�����X�ɓ����A���͕s�����ɂ��邽�߂̍ޗ�
	unsigned int alpha_;
	int add_;

};