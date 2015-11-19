#ifndef __FIGHTER_H__
#define __FIGHTER_H__

#include "cocos2d.h"

class Fighter : public cocos2d::Sprite
{
	CC_SYNTHESIZE(int,hitPoint,HitPoint);
	CC_SYNTHESIZE(cocos2d::Vec2,velocity,Velocity);
public:
	Fighter(): hitPoint(1),velocity(cocos2d::Vec2::ZERO){};
	void setPosition(const cocos2d::Vec2& newPosition);
	static Fighter* createWithSpriteFrameName(const char* spriteFrameName);

};





#endif