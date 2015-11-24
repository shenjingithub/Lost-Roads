#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "MyUtility.h"

class GameOver : public cocos2d::Layer
{
	int score;
public:
	GameOver(int score):score(this->score){};

	static GameOver* createWithScore(int score);
	virtual bool init();

	

};
#endif