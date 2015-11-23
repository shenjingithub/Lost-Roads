#include "GamePlayerLayer.h"
USING_NS_CC;

Scene* GamePlayerLayer::createScene()
{
	auto scene=Scene::createWithPhysics();
	PhysicsWorld* phyWorld=scene->getPhysicsWorld();
	phyWorld->setGravity(Vect(0,0));

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
	
	Director::getInstance()->getEventDispatcher()->removeEventListener(touchFighterlistener);
	auto nodes=this->getChildren();

	for(const auto& node : nodes)
		{
			if(node->getTag()!=GameSceneNodeBatchTagBackground)
			{
				this->removeChild(node);
			}
		}
	this->unschedule(schedule_selector(GamePlayerLayer::shootBullet));
}


void GamePlayerLayer::onEnter()
{
	Layer::onEnter();

	Size visibleSize=Director::getInstance()->getVisibleSize();
///////////////////////ÔÝÍ£
	auto pauseSprite=Sprite::createWithSpriteFrameName("gameplay.button.pause.png");
	auto menuItempause=MenuItemSprite::create(pauseSprite,pauseSprite,CC_CALLBACK_1(GamePlayerLayer::menuPauseCallback,this));
	auto pauseMenu=Menu::create(menuItempause,NULL);
	pauseMenu->setPosition(Vec2(30,visibleSize.height-28));
	this->addChild(pauseMenu,20,999);
///////////////////////
	auto Stone1=Enemy::createWithEnemyTypes(EnemyTypeStone);
	Stone1->setVelocity(Vec2(0,-100));
	this->addChild(Stone1,10,GameSceneNodeBatchTagEnemy);

	auto Planet1=Enemy::createWithEnemyTypes(EnemyTypePlanet);
	Planet1->setVelocity(Vec2(0,-50));
	this->addChild(Planet1,10,GameSceneNodeBatchTagEnemy);

	auto enemyFighter1=Enemy::createWithEnemyTypes(EnemyTypeEnemy1);
	enemyFighter1->setVelocity(Vec2(0,-50));
	this->addChild(enemyFighter1,10,GameSceneNodeBatchTagEnemy);

	auto enemyFighter2=Enemy::createWithEnemyTypes(EnemyTypeEnemy2);
	enemyFighter2->setVelocity(Vec2(0,-50));
	this->addChild(enemyFighter2,10,GameSceneNodeBatchTagEnemy);
	
	fighter=Fighter::createWithSpriteFrameName("gameplay.fighter.png");
	fighter->setHitPoint(5);
	fighter->setPosition(Vec2(visibleSize.width/2,70));
	this->addChild(fighter,10,GameSceneNodeTagFighter);

	this->updateStatusBarFighter();
	this->updateStatusBarScore();
	///×¢²á´¥Ãþ·É»úÊÂ¼þ¼àÌýÆ÷
	touchFighterlistener=EventListenerTouchOneByOne::create();
	touchFighterlistener->setSwallowTouches(true);
	touchFighterlistener->onTouchBegan=[](Touch* touch,Event* event){
		return true;
	};
	touchFighterlistener->onTouchMoved=[](Touch* touch,Event* event){
		auto target=event->getCurrentTarget();
		target->setPosition(target->getPosition()+touch->getDelta());  
	};

	touchFighterlistener->onTouchEnded=[](Touch* touch,Event* event){
		
	};

	EventDispatcher* eventdispatcher=Director::getInstance()->getEventDispatcher();
	eventdispatcher->addEventListenerWithSceneGraphPriority(touchFighterlistener,this->fighter);
	//×¢²á¼ì²âÅö×²×¢²áÆ÷
	contactListener=EventListenerPhysicsContact::create();
	contactListener->onContactBegin=[this](PhysicsContact& contact){
		auto spriteA=contact.getShapeA()->getBody()->getNode();
		auto spriteB=contact.getShapeB()->getBody()->getNode();

		////////////////////////////¼ì²â·É»úÓëµÐÈËÏà×²////////////////////////////////

		Node* enemy1=nullptr;
		if(spriteA->getTag()==GameSceneNodeTagFighter&&
			spriteB->getTag()==GameSceneNodeBatchTagEnemy)
		{
			enemy1=spriteB;
		}
		if(spriteA->getTag()==GameSceneNodeBatchTagEnemy&&
			spriteB->getTag()==GameSceneNodeTagFighter)
		{
			enemy1=spriteA;
		}
		if(enemy1!=nullptr)
		{
			this->handleFighterCollidingWithEnemy((Enemy*)enemy1);
			return false;
		
		}
		////////////////////////////¼ì²âÅÚµ¯ÓëµÐÈËÏà×²////////////////////////////////

		Node* enemy2=nullptr;

		if(spriteA->getTag()==GameSceneNodeBatchTagBullet&&
			spriteB->getTag()==GameSceneNodeBatchTagEnemy)
		{
			if(!spriteA->isVisible())
				return false;
			spriteA->setVisible(false);
			enemy2=spriteB;
		}
		if(spriteA->getTag()==GameSceneNodeBatchTagEnemy&&
			spriteB->getTag()==GameSceneNodeBatchTagBullet)
		{
			if(!spriteB->isVisible())
				return false;		
			spriteB->setVisible(false);
			enemy2=spriteA;
		}
		if(enemy2!=nullptr)
		{
			this->handleBulletCollidingWithEnemy((Enemy*)enemy2);
			return false;
		}
		return false;
	};
	eventdispatcher->addEventListenerWithFixedPriority(contactListener,1);

	//Ã¿0.2sµ÷ÓÃshootBulletº¯Êý·¢Éä1·¢ÅÚµ¯
	this->schedule(schedule_selector(GamePlayerLayer::shootBullet),0.2f);
}

void GamePlayerLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();



}

void GamePlayerLayer::shootBullet(float dt)
{
	if(fighter&&fighter->isVisible())
	{
		Bullet* bullet=Bullet::createwithSpriteFrameName("gameplay.bullet.png");	
		bullet->setVelocity(Vec2(0,GameSceneBulletVelocity));
		this->addChild(bullet,0,GameSceneNodeBatchTagBullet);
		bullet->shootBulletFromFighter(fighter);
	
	}
		
}

void GamePlayerLayer::handleBulletCollidingWithEnemy(Enemy* enemy)
{
	enemy->setHitPoints(enemy->getHitPoints()-1);
	
	if(enemy->getHitPoints()<=0)
	{
		/// ±¬Õ¨ºÍÒôÐ§
		Node* node=this->getChildByTag(GameSceneNodeTagExplosionParticleSystem);
		if(node){
			this->removeChild(node);
		}
		ParticleSystem* explosion=ParticleSystemQuad::create("particle/explosion.plist");
		explosion->setPosition(enemy->getPosition());
		this->addChild(explosion,2,GameSceneNodeTagExplosionParticleSystem);
		if(UserDefault::getInstance()->getBoolForKey(SOUND_KEY)){
		
			SimpleAudioEngine::getInstance()->playEffect(sound_2);
		}
		switch(enemy->getEnemyType())
		{
		case EnemyTypeStone:
			score+=EnemyStone_score;
			scorePlaceholder+=EnemyStone_score;
			break;
		case EnemyTypeEnemy1:
			score+=Enemy1_score;
			scorePlaceholder+=Enemy1_score;
			break;
		case EnemyTypeEnemy2:
			score+=Enemy2_score;
			scorePlaceholder+=Enemy2_score;
			break;
		case EnemyTypePlanet:
			score+=EnemyPlanet_score;
			scorePlaceholder+=EnemyPlanet_score;
			break;
		
		}

		if(scorePlaceholder>=1000)
		{
			fighter->setHitPoint(fighter->getHitPoint()+1);
			this->updateStatusBarFighter();
			scorePlaceholder-=1000;
		}
		this->updateStatusBarScore();
		enemy->setVisible(false);
		enemy->spawn();

	}
	
}

void GamePlayerLayer::handleFighterCollidingWithEnemy(Enemy* enemy)
{
	Size visibleSize=Director::getInstance()->getVisibleSize();
	fighter->setHitPoint(fighter->getHitPoint()-1);
	this->updateStatusBarFighter();
	////×²ÉÏ·É»úÖ±½Ó½áÊø
		Node* node=this->getChildByTag(GameSceneNodeTagExplosionParticleSystem);
		if(node){
			this->removeChild(node);
		}
		ParticleSystem* explosion=ParticleSystemQuad::create("particle/explosion.plist");
		explosion->setPosition(enemy->getPosition());
		this->addChild(explosion,2,GameSceneNodeTagExplosionParticleSystem);
		if(UserDefault::getInstance()->getBoolForKey(SOUND_KEY)){
		
			SimpleAudioEngine::getInstance()->playEffect(sound_2);
		}
		enemy->setVisible(false);
		enemy->spawn();
	////////////////
	
	if(fighter->getHitPoint()<=0)
	{
		auto sc=GameOver::createScene();
		Director::getInstance()->replaceScene(sc);
	
	
	}
	else{
		fighter->setPosition(Vec2(visibleSize.width/2,70)); 
		auto ac1=Show::create();
		auto ac2=FadeIn::create(1.0f);
		auto seq=Sequence::create(ac1,ac2,NULL);
		fighter->runAction(seq);
	
	}




}

void GamePlayerLayer::menuPauseCallback(Ref* pSender)
{
	Size visibleSzie=Director::getInstance()->getVisibleSize();

	if(UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}

	this->pause();
	for(const auto& node : this->getChildren())
	{
		node->pause();
	}

	auto backNormal=Sprite::createWithSpriteFrameName("gameplay.button.back.png");
	auto backSelect=Sprite::createWithSpriteFrameName("gameplay.button.back-on.png");
	auto backMenuItem=MenuItemSprite::create(backNormal,backSelect,CC_CALLBACK_1(GamePlayerLayer::menuBackCallback,this));

	auto resumeNormal=Sprite::createWithSpriteFrameName("gameplay.button.resume.png");
	auto resumeSelect=Sprite::createWithSpriteFrameName("gameplay.button.resume-on.png");
	auto resumeMenuItem=MenuItemSprite::create(resumeNormal,resumeSelect,CC_CALLBACK_1(GamePlayerLayer::menuResumeCallback,this));

	menu=Menu::create(backMenuItem,resumeMenuItem,NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSzie/2));
	this->addChild(menu,20,100);

}


void GamePlayerLayer::menuBackCallback(Ref* pSender)
{
	Director::getInstance()->popScene();
	if(UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}
}

void GamePlayerLayer::menuResumeCallback(Ref* pSender)
{
	if(UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(sound_1);
	}

	this->resume();
	for(const auto& node : this->getChildren())
	{
		node->resume();
	}
	removeChild(menu);

}

void GamePlayerLayer::updateStatusBarFighter()
{
	Size visibleSize=Director::getInstance()->getVisibleSize();

	Node* n1=this->getChildByTag(GameSceneNodeTagStatusBarFighterNode);
	if(n1)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarFighterNode);
	}

	Sprite* fg=Sprite::createWithSpriteFrameName("gameplay.life.png");
	fg->setPosition(Vec2(visibleSize.width-60,visibleSize.height-28));
	this->addChild(fg,20,GameSceneNodeTagStatusBarFighterNode);

	Node* n2=this->getChildByTag(GameSceneNodeTagStatusBarLifeNode);
	if(n2)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarLifeNode);
	}
	if(this->fighter->getHitPoint()<0)
	{
		this->fighter->setHitPoint(0);
	}

	__String* life=__String::createWithFormat("X %d",this->fighter->getHitPoint()); 
	auto lblLife=Label::createWithTTF(life->getCString(),"fonts/hanyi.ttf",18);
	lblLife->setPosition(fg->getPosition()+Vec2(30,0));
	this->addChild(lblLife,20,GameSceneNodeTagStatusBarLifeNode);
}

void GamePlayerLayer::updateStatusBarScore()
{
	Size visibleSzie=Director::getInstance()->getVisibleSize();
	Node* n=this->getChildByTag(GameSceneNodeTagStatusBarScore);
	if(n)
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarScore);
	}
	if(this->score<0)
	{
		this->score=0;
	}
	__String* score=__String::createWithFormat("%d",this->score);
	auto lblString=Label::createWithTTF(score->getCString(),"fonts/hanyi.ttf",18);
	lblString->setPosition(Vec2(visibleSzie.width/2,visibleSzie.height-28));
	this->addChild(lblString,20,GameSceneNodeTagStatusBarScore);

}