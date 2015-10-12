#pragma once

class Move{
	public:
		Move(float*, float*);
		Move();

		void setMove(float, float, int);

		float getDeltaX();
		float getDeltaY();

		int getFrame();
		int getFrameCount();

		void frameCounter();

	private:

		//EnemyのXY値
		float *e_x;
		float *e_y;

		//移動先・目的地
		float destinationX;
		float destinationY;

		//XY移動量
		float deltaX;
		float deltaY;

		//frame
		int frame;
		int frameCount;
};