#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class GameOver : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();
	static GameOver* create();
	virtual bool init();

	

};
#endif