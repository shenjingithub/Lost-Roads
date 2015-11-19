#include "Enemy.h"

USING_NS_CC;

Enemy* Enemy::createWithEnemyTypes(EnemyTypes enemytype)
{
	Enemy *enemy=new Enemy(enemytype);

	const char* enemyFramName=Enemy_Stone;

	switch(enemytype)
	{
	case EnemyTypeStone:
		enemyFramName=Enemy_Stone;
		enemy->setInitialHitPoints(3);
		break;
	case EnemyTypeEnemy1:
		enemyFramName=Enemy_1;
		enemy->setInitialHitPoints(5);
		break;
	case EnemyTypeEnemy2:
		enemyFramName=Enemy_2;
		enemy->setInitialHitPoints(10);
		break;
	case EnemyTypePlanet:
		enemyFramName=Enemy_plane;
		enemy->setInitialHitPoints(15);
		break;
	}

	if(enemy&&enemy->createWithSpriteFrameName(enemyFramName))
	{
		enemy->autorelease();
		
		auto body=PhysicsBody::create();

		if(enemytype==EnemyTypeStone||enemytype==EnemyTypePlanet)
		{
			body->addShape(PhysicsShapeCircle::create(enemy->getContentSize().width/2-5));
		}
		else if(enemytype==EnemyTypeEnemy1)
		{
			Vec2 verts[]={
				Vec2(-2.5,-45.75),
				Vec2(-29.5,-27.35),
				Vec2(-53,-0.25),
				Vec2(-34,43.25),
				Vec2(28,44.25),
				Vec2(55,-2.25)			};
			body->addShape(PhysicsShapePolygon::create(verts,6));
		}
		else if(enemytype==EnemyTypeEnemy1)
		{
			Vec2 verts[]={
				Vec2(1.25,32.25),
				Vec2(36.75,-4.75),
				Vec2(2.75,-31.75),
				Vec2(-31.75,-3.25)			};
			body->addShape(PhysicsShapePolygon::create(verts,4));
		}
		
		body->setCategoryBitmask(0x01);
		body->setCollisionBitmask(0x02);
		body->setContactTestBitmask(0x01);

		enemy->setPhysicsBody(body);   
		enemy->setVisible(false);
		enemy->spawn();
		enemy->unscheduleUpdate();
		enemy->scheduleUpdate();
		
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;

}



void Enemy::update(float dt)
{
	switch(enemyType)
	{
	case EnemyTypeStone:
		this->setRotation(this->getRotation()-0.5);
		break;
	case EnemyTypePlanet:
		this->setRotation(this->getRotation()+1);
		break;
	}
	Vec2 movelen=velocity*dt;
	this->setPosition(this->getPosition()+movelen);

	if(this->getPosition().y+this->getContentSize().height/2<0){
			this->spawn();
	}
}

void Enemy::spawn()
{
	Size screen=Director::getInstance()->getVisibleSize();
	float yPos=screen.height+this->getContentSize().height/2;
	float xPos=(screen.width-this->getContentSize().width)*CCRANDOM_0_1();

	this->setPosition(Vec2(xPos,yPos));
	this->setAnchorPoint(Vec2(0.5,0.5));

	this->setHitPoints(this->getInitialHitPoints());
	this->setVisible(true);
}