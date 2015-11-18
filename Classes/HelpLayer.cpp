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

	///测试文字
	auto txtTest=Label::createWithTTF(MyUtility::getUTF8Char("test"),"fonts/hanyi.ttf",18);
	txtTest->setColor(Color3B(14,83,204));
	txtTest->setPosition(95,top->getPosition().y-70);
	txtTest->setAnchorPoint(Vec2(0,0));
	this->addChild(txtTest);

	auto Test=Label::createWithTTF("SJ.com","fonts/hanyi.ttf",18);
	Test->setAnchorPoint(Vec2(0,0));
	Vec2 p1=txtTest->convertToWorldSpace(Vec2(0,-20));
	Test->setColor(Color3B(198,12,0));
	Test->setPosition(p1);
	this->addChild(Test);

	///音乐文字
	auto txtMusic=Label::createWithTTF(MyUtility::getUTF8Char("music"),"fonts/hanyi.ttf",18);
	txtMusic->setColor(Color3B(14,83,204));
	Vec2 p2=Test->convertToWorldSpace(Vec2(0,-40));
	txtMusic->setPosition(p2);
	txtMusic->setAnchorPoint(Vec2(0,0));
	this->addChild(txtMusic);

	auto Music1=Label::createWithTTF("shenjin","fonts/hanyi.ttf",18);
	Music1->setColor(Color3B(198,12,0));
	Music1->setAnchorPoint(Vec2(0,0));
	Vec2 p3=txtMusic->convertToWorldSpace(Vec2(0,-20));
	Music1->setPosition(p3);
	this->addChild(Music1);

	auto Music2=Label::createWithTTF("yun long","fonts/hanyi.ttf",18);
	Music2->setColor(Color3B(198,12,0));
	Music2->setAnchorPoint(Vec2(0,0));
	Vec2 p4=txtMusic->convertToWorldSpace(Vec2(0,-40));
	Music2->setPosition(p4);
	this->addChild(Music2);

	///音效文字
	auto txtSound=Label::createWithTTF(MyUtility::getUTF8Char("sound"),"fonts/hanyi.ttf",18);
	txtSound->setColor(Color3B(14,83,204));
	Vec2 p5=Music2->convertToWorldSpace(Vec2(0,-40));
	txtSound->setPosition(p5);
	txtSound->setAnchorPoint(Vec2(0,0));
	this->addChild(txtSound);

	auto Sound1=Label::createWithTTF("Mr. Shen","fonts/hanyi.ttf",18);
	Sound1->setColor(Color3B(198,12,0));
	Sound1->setAnchorPoint(Vec2(0,0));
	Vec2 p6=txtSound->convertToWorldSpace(Vec2(0,-20));
	Sound1->setPosition(p6);
	this->addChild(Sound1);

	auto Sound2=Label::createWithTTF("yun long","fonts/hanyi.ttf",18);
	Sound2->setColor(Color3B(198,12,0));
	Sound2->setAnchorPoint(Vec2(0,0));
	Vec2 p7=txtSound->convertToWorldSpace(Vec2(0,-40));
	Sound2->setPosition(p7);
	this->addChild(Sound2);

	//信息与服务文字
	auto txtInfoService=Label::createWithTTF(MyUtility::getUTF8Char("info_service"),"fonts/hanyi.ttf",18);
	txtInfoService->setColor(Color3B(14,83,204));
	Vec2 p8=Sound2->convertToWorldSpace(Vec2(0,-40));
	txtInfoService->setPosition(p8);
	txtInfoService->setAnchorPoint(Vec2(0,0));
	this->addChild( txtInfoService);

	auto InfoService=Label::createWithTTF("www.SJ-work.com","fonts/hanyi.ttf",18);
	InfoService->setColor(Color3B(198,12,0));
	InfoService->setAnchorPoint(Vec2(0,0));
	Vec2 p9=txtInfoService->convertToWorldSpace(Vec2(0,-20));
	InfoService->setPosition(p9);
	this->addChild(InfoService);

	return true;
}
