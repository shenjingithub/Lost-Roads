#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/loading_texture.plist");

	auto bg=TMXTiledMap::create("map/red_bg.tmx");
	this->addChild(bg);

	auto logo=Sprite::createWithSpriteFrameName("logo.png");
	this->addChild(logo);
	logo->setPosition(visibleSize/2);

	auto sprite=Sprite::createWithSpriteFrameName("loding4.png");
	this->addChild(sprite);
	sprite->setPosition(logo->getPosition()-Vec2(0,logo->getContentSize().height/2+30));

   //////////////////////////////…Ë÷√∂Øª≠//////////////////////////////
	Animation *animation=Animation::create();
	for(int i=0; i<4;i++)
	{
		String *framename=String::createWithFormat("loding%d.png",i);
		
		SpriteFrame *spriteframe=SpriteFrameCache::getInstance()->getSpriteFrameByName(framename->getCString());

		animation->addSpriteFrame(spriteframe);
	}
	animation->setDelayPerUnit(0.5f);
	animation->setRestoreOriginalFrame(true);
	
	Animate* animate=Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
