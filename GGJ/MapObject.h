#pragma once
#include <string>

enum Object :int{
	STAR,
	RT,
	BLOCK,
	KUSO,
	UNKNOWN,
};

class MapObject{
public:

	MapObject();
	MapObject(const std::string& ghName, const std::string& musicName);
	virtual ~MapObject(){};

	//‰æ‘œƒ[ƒh
	void loadGH(const std::string& ghName);

	//•`ŽÊ
	virtual void render(const int player_x, const int player_y);

	//XV
	virtual void update(const int player_x, const int player_y, const int stage);

	//X•Žæ“¾
	int getSizeX(){
		return sizeX_;
	}

	//Y•Žæ“¾
	int getSizeY(){
		return sizeY_;
	}

	int getX(){
		return x_;
	}

	int getY() {
		return y_;
	}
	
	bool touch(const int player_x, const int player_y);

	bool hitCheck(const int player_x, const int player_y);

	bool getHitFlag() { return this->hitFlag; }

protected:

	//‰æ‘œŠi”[
	int gh_;

	//‰¹Ši”[
	int catch_;

	int x_,y_;

	int sizeX_,sizeY_;

	int xmc_, ymc_;

	int count;

	int time;

	bool hitFlag;

};