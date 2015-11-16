#ifndef __SETTING_LAYER_H__
#define __SETTING_LAYER_H__
#include "cocos2d.h"
#include "BaseLayer.h"
#include "MyUtility.h"
#include "SystemHeader.h"

class SettingLayer : public BaseLayer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);


	CREATE_FUNC(SettingLayer);

};

#endif