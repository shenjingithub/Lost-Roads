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

	Size visibleSize=Director::getInstance()->getVisibleSize();
	Vec2 Origin=Director::getInstance()->getVisibleOrigin();

	auto top=Sprite::createWithSpriteFrameName("help-top.png");
	top->setPosition(Vec2(visibleSize.width/2,visibleSize.height-top->getContentSize().height/2));
	this->addChild(top);

	///²âÊÔÎÄ×Ö
	auto txtTest=Label::createWithTTF(MyUtility::getUTF8Char("test"),"fonts/hanyi.ttf",18);
	txtTest->setColor(Color3B(14,83,204));
	txtTest->setPosition(95,top->getPosition().y-70);
	txtTest->setAnchorPoint(Vec2(0,0));
	this->addChild(txtTest);

	auto Test=Label::createWithTTF("51work6","fonts/hanyi.ttf",18);
	Test->setAnchorPoint(Vec2(0,0));
	Vec2 p1=txtTest->convertToWorldSpace(Vec2(0,-20));
	Test->setColor(Color3B(198,12,0));
	Test->setPosition(p1);
	this->addChild(Test);


	return true;
}
