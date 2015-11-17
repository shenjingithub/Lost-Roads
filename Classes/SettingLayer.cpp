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
	//ÒôÐ§
	auto soundOnSprite=Sprite::createWithSpriteFrameName("setting.check-on.png");
	auto soundOffSprite=Sprite::createWithSpriteFrameName("setting.check-off.png");
	auto soundonMenuItem=MenuItem::create(soundOnSprite,NULL);
	auto soundoffMenuItem=MenuItem::create(soundOffSprite,NULL);
	auto soundtoggleMenuItem=MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuSoundToggleCallback,this),soundonMenuItem,soundoffMenuItem,NULL);
	//ÒôÀÖ
	auto musicOnSprite=Sprite::createWithSpriteFrameName("setting.check-on.png");
	auto musicOffSprite=Sprite::createWithSpriteFrameName("setting.check-off.png");
	auto musicOnMenuItem=MenuItem::create(musicOnSprite,NULL);
	auto musicOffMenuItem=MenuItem::create(musicOffSprite,NULL);
	auto musictoggleMenuItem=MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingLayer::menuMusicToggleCallback,this),musicOnMenuItem,musicOffMenuItem,NULL);

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

	return true;

}

void SettingLayer::menuSoundToggleCallback(Ref* pSender)
{


}

void SettingLayer::menuMusicToggleCallback(Ref* pSender)
{




}