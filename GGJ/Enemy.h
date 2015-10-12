#pragma once

#include <vector>
#include "Animation.h"
#include "Player_K.h"
#include "Unit.h"
#include "Move.h"

enum EnemyMode : int{
	E_IDLE = 0,	//�g�p���Ă��Ȃ�
	E_RUN,		//�g�p���Ă���i��~��ԁj
	E_EMERGE,	//�o��
	E_MOVE,		//�ړ���
	E_ATTACK,	//�U����
	E_DEAD,		//�ޏ�
	E_UNKNWON	//��ԕs��
};

class Enemy : public Animation, public Unit, public Move{
	public:
		Enemy(char*);
		Enemy();
		~Enemy();

		void render()override;
		void updata(bool through)override;

		//Enemy�Ƃ̏Փ˔��� CD:collision detection
		bool CD(Player_K*);

		//Enemy��X�l���擾����֐�
		float getX();
		//Enemy��Y�l���擾����ϐ�
		float getY();

		float getCenterX();
		float getCenterY();

		//Enemy�̉摜X�T�C�Y���擾����֐�
		int getSizeX();
		//Enemy�̉摜Y�T�C�Y���擾����֐�
		int getSizeY();

		//Enemy��XY�l��ݒ�
		void setXY(float x, float y);

		//Enemy��state�l��ݒ�
		void setState(EnemyMode);

		//Enemy��State�l��ݒ�
		EnemyMode getState() { return this->state; };

	private:
		//Enemy�̕\���֐�
		void draw();

		//alpha�t���\���֐�
		//x���W, y���W, alpha�l, imageHandle
		void DrawGraphAlpha(float, float, int, int*);

		//Enemy�̉摜�n���h��
		int imgHandle[3];

		//Enemy�̍s���p�^�[�����i�[����z��
		int mp_fp[3];

		//Enemy�̍��W
		float x, y;

		//Enemy�̒��S���W
		float centerX, centerY;

		//Enemy�̃T�C�Y
		int sizeX, sizeY;

		//Enemy�̓����x
		int alpha;

		//Enemy�̏��
		EnemyMode state;

		//Enemy��Animation�N���X���������߂̕ϐ�
		Animation* aniHandle;

		//Enemy�𓮂������߂�Move�N���X�̕ϐ�
		Move* m;

		//Enemy�̓���֐�
		void moving();

		//�ړ����XY�l
		float move_x, move_y;
		//�ړ���܂łɂ�����t���[����
		int move_frame;
};
