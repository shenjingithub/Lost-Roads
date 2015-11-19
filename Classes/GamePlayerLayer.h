#ifndef __GAME_PLAYER_LAYER_H__
#define __GAME_PLAYER_LAYER_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "BaseLayer.h"
#include "Enemy.h"

class GamePlayerLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();




	CREATE_FUNC(GamePlayerLayer);

};


#endif