#include "Unit.h"
#include "DxLib.h"

void Unit::loadGh(const std::string& ghName,int* gh,const int ghx,const int ghy,const int index){
	int handle = LoadGraph(ghName.c_str());
	//�摜�T�C�Y�擾
	GetGraphSize(handle,&sizeX_,&sizeY_);
	//�摜�𕪊��ǂݍ���
	LoadDivGraph(ghName.c_str(),index,ghx,ghy,sizeX_/ghx,sizeY_/ghy,gh,true);
}

