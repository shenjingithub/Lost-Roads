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

	auto sprite1=Sprite::createWithSpriteFrameName("gameplay.bg.sprite-1.png");
	sprite1->setPosition(Vec2(-50,-50));
	this->addChild(sprite1,0,GameSceneNodeBatchTagBackground);
	FiniteTimeAction *ac1=(FiniteTimeAction*)MoveBy::create(20,Vec2(500,500));
	FiniteTimeAction *ac2=((FiniteTimeAction*)ac1)->reverse();
	ActionInterval *as1=Sequence::create(ac1,ac2,NULL);
	sprite1->runAction(RepeatForever::create(EaseSineInOut::create(as1)));

	auto sprite2=Sprite::createWithSpriteFrameName("gameplay.bg.sprite-2.png");
	sprite2->setPosition(Vec2(visibleSize.width,0));
	this->addChild(sprite2,0,GameSceneNodeBatchTagBackground);
	FiniteTimeAction *ac3=(FiniteTimeAction*)MoveBy::create(10,Vec2(-500,600));
	FiniteTimeAction *ac4=((FiniteTimeAction*)ac3)->reverse();
	ActionInterval *as2=Sequence::create(ac3,ac4,NULL);
	sprite2->runAction(RepeatForever::create(EaseSineInOut::create(as2)));
}

void GamePlayerLayer::onExit()
{
	Layer::onExit();
	
	auto nodes=this->getChildren();

	for(const auto& node : nodes)
		{
			if(node->getTag()!=GameSceneNodeBatchTagBackground)
			{
				this->removeChild(node);
			}
		}

}


void GamePlayerLayer::onEnter()
{
	Layer::onEnter();

	Size visibleSize=Director::getInstance()->getVisibleSize();

	auto Stone1=Enemy::createWithEnemyTypes(EnemyTypeStone);
	Stone1->setVelocity(Vec2(0,-100));
	this->addChild(Stone1,10,GameSceneNodeBatchTagEnemy);

	auto Planet1=Enemy::createWithEnemyTypes(EnemyTypePlanet);
	Planet1->setVelocity(Vec2(0,-50));
	this->addChild(Planet1,10,GameSceneNodeBatchTagEnemy);

	/*auto enemyFighter1=Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
	enemyFighter1->setVelocity(Vec2(0,-50));
	this->addChild(enemyFighter1,10,GameSceneNodeBatchTagEnemy);

	auto enemyFighter2=Enemy::createWithEnemyTypes(EnemyTypeEnemy2);
	enemyFighter2->setVelocity(Vec2(0,-50));
	this->addChild(enemyFighter2,10,GameSceneNodeBatchTagEnemy);
	*/

}

void GamePlayerLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();



}