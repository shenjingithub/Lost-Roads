#include "BaseLayer.h"

bool BaseLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Size visibleSize=Director::getInstance()->getVisibleSize();
	Vec2 origin=Director::getInstance()->getVisibleOrigin();

	auto bg=TMXTiledMap::create("hd/map/red_bg.tmx");
	this->addChild(bg);
	

	auto glassSprite=Sprite::createWithSpriteFrameName("setting.glass.png");
	glassSprite->setPosition(Vec2(visibleSize.width-glassSprite->getContentSize().width/2,160));
	this->addChild(glassSprite);

	auto handSprite=Sprite::createWithSpriteFrameName("setting.hand.png");
	handSprite->setPosition(Vec2(visibleSize.width-handSprite->getContentSize().width/2,60));
	this->addChild(handSprite);

	auto okNormal=Sprite::createWithSpriteFrameName("setting.button.ok.png");
	auto okSelected=Sprite::createWithSpriteFrameName("setting.button.ok-on.png");
	auto okMenuItem=MenuItemSprite::create(okNormal,okSelected,CC_CALLBACK_1(BaseLayer::menuBackCallback,this));

	auto mn=Menu::create(okMenuItem,NULL);
	mn->setPosition(Vec2(visibleSize.width-mn->getContentSize().width/2+60,60));
	this->addChild(mn);


	return true;

}


void BaseLayer::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	if(UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	
	}

}

void BaseLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BaseLayer onEnterTrationDidFinish");

	UserDefault *defaults=UserDefault::getInstance();
	if(defaults->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(bg_music_1,true);
	}
}