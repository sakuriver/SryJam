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

		//Enemy��XY�l
		float *e_x;
		float *e_y;

		//�ړ���E�ړI�n
		float destinationX;
		float destinationY;

		//XY�ړ���
		float deltaX;
		float deltaY;

		//frame
		int frame;
		int frameCount;
};