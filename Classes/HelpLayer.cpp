#include "HelpLayer.h"
USING_NS_CC;

Scene* HelpLayer::createScene()
{
	auto scene=Scene::create();
	auto layer=HelpLayer::create();
	scene->addChild(layer);

	return scene;
}

bool HelpLayer::init()
{
	if(!BaseLayer::init())
	{
		return false;
	}

	return true;
}
