#include "HelloWorldScene.h"
#include "HomeScene.h"
#include "stdio.h"

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
	logo->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

	auto sprite=Sprite::createWithSpriteFrameName("loding4.png");
	this->addChild(sprite);
	sprite->setPosition(logo->getPosition()-Vec2(0,logo->getContentSize().height/2+30));

   //////////////////////////////设置动画//////////////////////////////
	Animation *animation=Animation::create();
	for(int i=1; i<=4;i++)
	{
		__String *framename=__String::createWithFormat("loding%d.png",i);
		
		SpriteFrame *spriteframe=SpriteFrameCache::getInstance()->getSpriteFrameByName(framename->getCString());

		animation->addSpriteFrame(spriteframe);
	}
	animation->setDelayPerUnit(0.5f);
	animation->setRestoreOriginalFrame(true);
	
	Animate* animate=Animate::create(animation);
	sprite->runAction(RepeatForever::create(animate));
	////////////////////////////////////////////////////////////////////////

	///////////////////////////异步加载图片////////////////////////////////

	m_nNumberofloaded=0;
	Director::getInstance()->getTextureCache()->addImageAsync("texture/home_texture.png",
																CC_CALLBACK_1(HelloWorld::loadingTextureCallBack,this));

	Director::getInstance()->getTextureCache()->addImageAsync("texture/setting_texture.png",
																CC_CALLBACK_1(HelloWorld::loadingTextureCallBack,this));
	Director::getInstance()->getTextureCache()->addImageAsync("texture/gameplay_texture.png",
																CC_CALLBACK_1(HelloWorld::loadingTextureCallBack,this));

	/////////////////////////////////////////////////////////////////////


	////////////////////////异步加载声音//////////////////////////////////

	_loadingAudioThread=new std::thread(&HelloWorld::LoadingAudio,this);

////////////////////////////////////////////////////////////////////////
    return true;
///////////////////////////////////////////////////////////////////////



}


void HelloWorld::loadingTextureCallBack(Texture2D* texture)
{
	switch(m_nNumberofloaded++)
	{
		case 0:
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/home_texture.plist",texture);
			break;
		case 1:
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/setting_texture.plist",texture);
			break;
		case 2:
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/gameplay_texture.plist",texture);
			this->schedule(schedule_selector(HelloWorld::delayCall),1,1,3);
			break;

	}



}

void HelloWorld::delayCall(float dt)
{
	auto sc=HomeSceneLayer::createScene();
	Director::getInstance()->replaceScene(sc);

}

void HelloWorld::LoadingAudio()
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music_1);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(bg_music_2);
}

void HelloWorld::onExit()
{
	Layer::onExit();
	_loadingAudioThread->join();
	CC_SAFE_DELETE(_loadingAudioThread);
/////////////////清理loading缓存//////////////////////
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("texture/loading_texture.png");
	Director::getInstance()->getTextureCache()->removeTextureForKey("texture/loading_texture.png");

	this->unschedule(schedule_selector(HelloWorld::delayCall));
}