#include "SettingLayer.h"

USING_NS_CC;

Scene* SettingLayer::createScene()
{
	auto scene=Scene::create();
	auto layer=SettingLayer::create();
	scene->addChild(layer);

	return scene;

}

bool SettingLayer::init()
{
	if(!BaseLayer::init())
	{
		return false;
	}
	Size visibleSize=Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin=Director::getInstance()->getVisibleOrigin();

	auto settingtop=Sprite::createWithSpriteFrameName("setting-top.png");
	settingtop->setPosition(Vec2(visibleSize.width/2,visibleSize.height-settingtop->getContentSize().height/2));
	this->addChild(settingtop);

	//音效
	auto soundOnSprite=Sprite::createWithSpriteFrameName("setting.check-on.png");
	auto soundOffSprite=Sprite::createWithSpriteFrameName("setting.check-off.png");
	auto soundonMenuItem=MenuItemSprite::create(soundOnSprite,NULL);
	auto soundoffMenuItem=MenuItemSprite::create(soundOffSprite,NULL);
	auto soundtoggleMenuItem=MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuSoundToggleCallback,this),soundoffMenuItem,soundonMenuItem,NULL);
	soundtoggleMenuItem->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2)+Vec2(70,50));
	
	//音乐
	auto musicOnSprite=Sprite::createWithSpriteFrameName("setting.check-on.png");
	auto musicOffSprite=Sprite::createWithSpriteFrameName("setting.check-off.png");
	auto musicOnMenuItem=MenuItemSprite::create(musicOnSprite,NULL);
	auto musicOffMenuItem=MenuItemSprite::create(musicOffSprite,NULL);
	auto musictoggleMenuItem=MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuMusicToggleCallback,this),musicOffMenuItem,musicOnMenuItem,NULL);

	auto mn=Menu::create(soundtoggleMenuItem,musictoggleMenuItem,NULL);
	mn->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2)+Vec2(70,50));
	mn->alignItemsVerticallyWithPadding(20.0f);
	this->addChild(mn,1);


	auto lblSound=Label::createWithTTF(MyUtility::getUTF8Char("lblSound"),"fonts/hanyi.ttf",36);
	lblSound->setColor(Color3B(14,83,204));
	lblSound->setPosition(mn->getPosition()-Vec2(100,-30));
	this->addChild(lblSound,1);

	auto lblMusic=Label::createWithTTF(MyUtility::getUTF8Char("lblMusic"),"fonts/hanyi.ttf",36);
	lblMusic->setColor(Color3B(14,83,204));
	lblMusic->setPosition(lblSound->getPosition()-Vec2(0,60));
	this->addChild(lblMusic,1); 

	//设置音效和音乐选中后的状态
	auto defaults=UserDefault::getInstance();
	if(defaults->getBoolForKey(MUSIC_KEY))
	{
		musictoggleMenuItem->setSelectedIndex(1);
	}
	else
	{
		musictoggleMenuItem->setSelectedIndex(0);
	}
	if(defaults->getBoolForKey(SOUND_KEY))
	{
		soundtoggleMenuItem->setSelectedIndex(1);
	}
	else
	{
		soundtoggleMenuItem->setSelectedIndex(0);
	}

	return true;

}

void SettingLayer::menuSoundToggleCallback(Ref* pSender)
{
	auto defaults=UserDefault::getInstance();
	if(defaults->getBoolForKey(SOUND_KEY))
	{
		defaults->setBoolForKey(SOUND_KEY,false);
	}
	else
	{
		defaults->setBoolForKey(SOUND_KEY,true);
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}

}

void SettingLayer::menuMusicToggleCallback(Ref* pSender)
{
	auto defaults=UserDefault::getInstance();
	if(defaults->getBoolForKey(MUSIC_KEY))
	{
		defaults->setBoolForKey(MUSIC_KEY,false);
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
	else
	{
		defaults->setBoolForKey(MUSIC_KEY,true);
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_2,true);
	}



}