#include "HomeScene.h"

USING_NS_CC;

Scene* HomeSceneLayer::createScene()
{
	auto scene=Scene::create();
	auto layer=HomeSceneLayer::create();
	scene->addChild(layer);

	return scene;
}

bool HomeSceneLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Size visibleSize=Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin=Director::getInstance()->getVisibleOrigin();

	auto bg=TMXTiledMap::create("map/red_bg.tmx");
	this->addChild(bg);

	auto top=Sprite::createWithSpriteFrameName("home-top.png");
	top->setPosition(Vec2(visibleSize.width/2,visibleSize.height-top->getContentSize().height/2));
	this->addChild(top);
	auto end=Sprite::createWithSpriteFrameName("home-end.png");
	end->setPosition(Vec2(visibleSize.width/2,top->getContentSize().height/2));
	this->addChild(end);
	//////////////////////////////²Ëµ¥//////////////////////////////////

	auto StartSpriteNormal=Sprite::createWithSpriteFrameName("home.button.start.png");
	auto StartSpriteSelect=Sprite::createWithSpriteFrameName("home.button.start-on.png");
	auto StartMenuItem=MenuItemSprite::create(StartSpriteNormal,StartSpriteSelect,CC_CALLBACK_1(HomeSceneLayer::menuItemCallback,this));
	StartMenuItem->setTag(ActionType::MenuItemStart);

	auto SettingSpriteNormal=Sprite::createWithSpriteFrameName("home.button.setting.png");
	auto SettingSpriteSelect=Sprite::createWithSpriteFrameName("home.button.setting-on.png");
	auto SettingMenuItem=MenuItemSprite::create(SettingSpriteNormal,SettingSpriteSelect,CC_CALLBACK_1(HomeSceneLayer::menuItemCallback,this));
	SettingMenuItem->setTag(ActionType::MenuItemSetting);

	auto HelpSpriteNormal=Sprite::createWithSpriteFrameName("home.button.help.png");
	auto HelpSpriteSelect=Sprite::createWithSpriteFrameName("home.button.help-on.png");
	auto HelpMenuItem=MenuItemSprite::create(HelpSpriteNormal,HelpSpriteSelect,CC_CALLBACK_1(HomeSceneLayer::menuItemCallback,this));
	HelpMenuItem->setTag(ActionType::MenuItemHelp);

	auto mn=Menu::create(StartMenuItem,SettingMenuItem,HelpMenuItem,NULL);
	mn->setPosition(visibleSize/2);
	mn->alignItemsVerticallyWithPadding(12);
	this->addChild(mn);
	return true;
}

void HomeSceneLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	UserDefault* userdefault=UserDefault::getInstance();

	if(userdefault->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bg_music_1",true);	
	}

}

void HomeSceneLayer::menuItemCallback(Ref* pSender)
{
	if(UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect("sound_1");
	}
	Scene* tsc=nullptr;
	auto menuitem=(MenuItem*)pSender;
	switch(menuitem->getTag())
	{
	case ActionType::MenuItemStart:
		//tsc=TransitionFade::create(1.0f,GamePlayerLayer::createScene());
		break;
	case ActionType::MenuItemSetting:
		tsc=TransitionFade::create(1.0f,SettingLayer::createScene());
		break;
	case ActionType::MenuItemHelp:
		//tsc=TransitionFade::create(1.0f,HelpLayer::createScene());
		break;
	}
	if(tsc)
	{
		Director::getInstance()->pushScene(tsc);
	}



}