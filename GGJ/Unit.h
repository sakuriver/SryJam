#pragma once
#include <memory>
#include <string>

//�p����ŐF�X�ݒ肷��
class Unit{

protected:

	Unit():sizeX_(0),sizeY_(0){};
	virtual ~Unit(){};

	//�`��
	virtual void render() = 0;
	//�X�V����
	virtual void updata(bool through){};
	
	virtual void updata(int through){};

	//�摜�ǂݍ��ݗp���\�b�h
	//�t�@�C����/�z��/�c��/����
	void loadGh(const std::string& ghName,int* gh,const int ghx,const int ghy,const int index);



protected:

	//�摜�T�C�Y�i�[
	int sizeX_,sizeY_;

};