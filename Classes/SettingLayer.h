#ifndef __SETTING_LAYER_H__
#define __SETTING_LAYER_H__
#include "cocos2d.h"
#include "SystemHeader.h"

class SettingLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();




	CREATE_FUNC(SettingLayer);

};

#endif