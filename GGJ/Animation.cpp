#include "Animation.h"
#include "DxLib.h" 

Animation::Animation(){
	flag_ = false;
	feadInFlag_ = false;
	feadOutFlag_ = false;
	ghNum_ = 0;
	count_ = 0;
	inc_ = 0;
	time_ = 1;
	i_ = 0;
}

void Animation::Reset(){
	flag_ = false;
	feadInFlag_ = false;
	feadOutFlag_ = false;
	ghNum_ = 0;
	count_ = 0;
	inc_ = 0;
	time_ = 1;
	i_ = 0;
}

Animation::~Animation(){
}

void Animation::feadOut(bool isClear){

	if(!feadOutFlag_){
		add_= -1;
		alpha_ = 255;
		feadOutFlag_ = true;
	}

	for( ; i_ < 255 ; i_  ++)
		{
			// •`‰æ‹P“x‚ðƒZƒbƒg
			if(!isClear){
				// •`‰æ‹P“x‚ðƒZƒbƒg
				SetDrawBright(  255-i_ , 255-i_ , 255-i_ ) ;
			}else{
				alpha_ += add_;
				SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha_ ) ;
			}

			feadSet(i_);

			ScreenFlip() ;
		}
}

void Animation::feadIn(bool isClear){

	if(!feadOutFlag_){
		add_= 1;
		alpha_ = 0;
		feadInFlag_ = true;
	}

	for(; i_ < 255 ; i_ ++ )
		{
			if(!isClear){
				// •`‰æ‹P“x‚ðƒZƒbƒg
				SetDrawBright(  i_ , i_ , i_ ) ;
			}else{
				alpha_ += add_;
				SetDrawBlendMode( DX_BLENDMODE_ALPHA, alpha_ ) ;
			}

			feadSet(i_);

			ScreenFlip() ;
		}
}

int Animation::animationIs(int num,double setTime,bool isSpiral){
	if(!flag_){
		time_ = (int)(setTime*100);
		flag_ = true;
	}

	if(count_%time_==0){

		ghNum_ += inc_;

		if(isSpiral){

			if(ghNum_==0)
				inc_ = 1;
			if(ghNum_==num-1)
				inc_ = -1;	

		}else{

			inc_ = 1;
			ghNum_ = ghNum_%num;

		}

	}

	count_++;

	return ghNum_;
}