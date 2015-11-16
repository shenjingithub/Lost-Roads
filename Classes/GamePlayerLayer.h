#ifndef __GAME_PLAYER_LAYER_H__
#define __GAME_PLAYER_LAYER_H__

#include "cocos2d.h"
#include "SystemHeader.h"
#include "BaseLayer.h"

class GamePlayerLayer : public BaseLayer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();




	CREATE_FUNC(GamePlayerLayer);

};


#endif