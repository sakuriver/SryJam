#pragma once

#include <Effekseer.h>
#include <EffekseerRendererDX9.h>

using namespace std;

class EffectObject
{
public :
	EffectObject(){};
	~EffectObject(){};
	void setX(float X) {};
	void setY() {};
	void setZ() {};
	float getX(){ return this->x; };
	float getY(){ return this->y; };
	float getZ(){ return this->z; };
private:
	::Effekseer::Effect *effect;
	float x;
	float y;
	float z;
};


class SceneBaseClass
{
public:
	SceneBaseClass(){};
	virtual ~SceneBaseClass(){};
	virtual void initialize(::Effekseer::Manager* g_manager){ };
	virtual void update(::Effekseer::Manager* g_manager){};
	virtual void render(::Effekseer::Manager* g_manager){};
	bool getInitialize() { return this->initialized; };
	void setInitialize(bool initialize);
	char* getNextSceneName(){ return this->nextSceneName; };
	char* getTweetMessage() { return &this->tweetFont_[0][0]; };
	void setNextSceneName(char* nextSceneName){ this->nextSceneName = nextSceneName; };
	bool getPlaySoundFlag() { return this->playSoundF; };
	void setPlaySoundFlag(bool playSoundF) { this->playSoundF = playSoundF; }
	void setTweetMessage(char* tweetFont_) { memcpy(&this->tweetFont_[0][0], tweetFont_, strlen(tweetFont_)); };
protected:
	char* nextSceneName = "";
	bool initialized = false;
	int  bgGraphH = 0;
	bool playSoundF = false;
	char tweetFont_[5][1024];
};