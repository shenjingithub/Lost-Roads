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
	auto planet=Enemy::createWithEnemyTypes(EnemyTypePlanet);
	
	this->addChild(planet);

	return true;
}
