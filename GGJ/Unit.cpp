#include "Unit.h"
#include "DxLib.h"

void Unit::loadGh(const std::string& ghName,int* gh,const int ghx,const int ghy,const int index){
	int handle = LoadGraph(ghName.c_str());
	//‰æ‘œƒTƒCƒYæ“¾
	GetGraphSize(handle,&sizeX_,&sizeY_);
	//‰æ‘œ‚ğ•ªŠ„“Ç‚İ‚İ
	LoadDivGraph(ghName.c_str(),index,ghx,ghy,sizeX_/ghx,sizeY_/ghy,gh,true);
}

