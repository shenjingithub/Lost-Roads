#include "GamePlayerLayer.h"
USING_NS_CC;

Scene* GamePlayerLayer::createScene()
{
	auto scene=Scene::create();
	auto layer=GamePlayerLayer::create();
	scene->addChild(layer);

	return scene;

}

bool GamePlayerLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	this->BGinit();

	return true;
}


void GamePlayerLayer::BGinit()
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
	auto bg=TMXTiledMap::create("map/blue_bg.tmx");
	this->addChild(bg,0,GameSceneNodeBatchTagBackground);

	ParticleSystem *ps=ParticleSystemQuad::create("particle/light.plist");
	ps->setPosition(Vec2(visibleSize.width,visibleSize.height)/2);
	this->addChild(ps,0,GameSceneNodeBatchTagBackground);


}

void GamePlayerLayer::onExit()
{



}

void GamePlayerLayer::onEnterTransitionDidFinish()
{




}