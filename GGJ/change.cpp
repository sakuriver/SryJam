#include "Change.h"
#include "DxLib.h"

change::change(){
	flash = LoadGraph("Resources/flash.png");
	x = 0;
	y = 0;
	GetGraphSize(flash,&img_x,&img_y);
};

void change::draw(){
	DrawGraph(this->x, this->y, flash,1);
}

bool change::move_change(){
	img_move();
	if (x<-860){
		return  true;
	}
	else{
		return false;
	}
}

void change::img_move(){
	this->x =this->x -4;
}

