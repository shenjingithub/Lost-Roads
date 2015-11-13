#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

typedef enum{
	MenuItemStart,
	MenuItemSetting,
	MenuItemHelp
}ActionType;

#include "cocos2d.h"
#include "SettingLayer.h"
#include "HelpLayer.h"
#include "GamePlayerLayer.h"
#include "SystemHeader.h"

class HomeSceneLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	void menuItemCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(HomeSceneLayer);
};
#endif