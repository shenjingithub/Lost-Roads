#include "GameOver.h"

USING_NS_CC;



GameOver* GameOver::createWithScore(int score)       //#define CREATE_FUNC(__TYPE__) static __TYPE__* create()
{
	GameOver* Ret=new GameOver(score);
	if(Ret&&Ret->init())
	{
		Ret->autorelease();
		return Ret;
	}
	delete Ret;
	Ret=nullptr;
	return nullptr;
}
bool GameOver::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize=Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin=Director::getInstance()->getVisibleOrigin();
	auto bg=TMXTiledMap::create("map/red_bg.tmx");
	this->addChild(bg);

	ParticleSystem *ps = ParticleSystemQuad::create("particle/light.plist");
	ps->setPosition(Vec2(visibleSize.width, visibleSize.height - 200) / 2);
	this->addChild(ps);

	auto GameOverbg=Sprite::createWithSpriteFrameName("gameover.top.png");
	GameOverbg->setPosition(visibleSize/2);
	this->addChild(GameOverbg,0);

	auto ScoreString=__String::createWithFormat("Score: %d",score);
	auto Score=LabelTTF::create(ScoreString->getCString(),"fonts/hanyi.ttf",18);
	Score->setColor(Color3B(14,83,204));
	Score->setPosition(GameOverbg->getPosition()-Vec2(0,GameOverbg->getContentSize().height/2));
	this->addChild(Score,20);

	return true;

}