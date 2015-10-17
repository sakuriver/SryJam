#include "MapObject.h"
#include "DxLib.h"

MapObject::MapObject()
:xmc_(0)
,ymc_(0)
,count(0)
,time(0){
}

MapObject::MapObject(const std::string& ghName, const std::string& musicName)
	:gh_(LoadGraph(ghName.c_str()))
	, catch_(LoadSoundMem(musicName.c_str()))
	, xmc_(0)
	, ymc_(0)
	, x_(1280)
	, count(0)
	, time(0)
{
	y_ = GetRand(696) + 64;
	time = GetRand(5000);
	this->loadGH(ghName);
	this->hitFlag = true;
}

void MapObject::loadGH(const std::string& ghName){
	//オブジェクトサイズ取得
	GetGraphSize(gh_,&sizeX_,&sizeY_);
	
}

void MapObject::render(const int player_x, const int player_y){
	//左端まで行き見えなくなったらReset()
	if (x_ == -64){ x_ = 1280, y_ = GetRand(696); count = 0; }
	DrawGraph(x_, y_, gh_, true);

}

void MapObject::update(const int player_x, const int player_y,const int stage){

	if (time < count){

		//移動量変更
		switch (stage){
		case 1:
			xmc_ = 3;
			break;
		case 2:
			xmc_ = 5;
			break;
		case 3:
			xmc_ = 8;
			break;
		default:
			break;
		}

		x_ -= xmc_;
		
	}
	
	count++;
		
}

bool MapObject::hitCheck(const int player_x, const int player_y) {
	if (player_x + 135 < x_ + sizeX_  && player_x + 170 > x_ ){
		if (player_y + 85 < y_ + sizeY_ && player_y + 120 > y_) {
			PlaySoundMem(catch_, DX_PLAYTYPE_BACK);
			x_ = 1280;
			y_ = GetRand(696);
			count = 0;
			return true;
		}
	}
	

	return false;
}