#pragma once

class change{
public:
	change();
	bool move_change();
	void img_move();
	void draw();
private:
	int img_x, img_y;
	int x, y;
	int flash;

};