#include "GameOver.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	auto scene=Scene::create();
	auto layer=GameOver::create();

	scene->addChild(layer);
	return scene;
}

GameOver* GameOver::create()       //#define CREATE_FUNC(__TYPE__) static __TYPE__* create()
{
	GameOver* pRet= new GameOver();
	if(pRet&&pRet->init())
	{
		pRet->autorelease();	
		return pRet;
	}
	else
	{
		delete pRet;
		pRet=nullptr;
		return NULL;
	}
}

bool GameOver::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize=Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin=Director::getInstance()->getVisibleOrigin();
	auto bg=TMXTiledMap::create("map/blue_bg.tmx");
	this->addChild(bg);
	auto GameOverbg=Sprite::createWithSpriteFrameName("gameover.top.png");
	GameOverbg->setPosition(visibleSize/2);
	this->addChild(GameOverbg,0);

	return true;

}