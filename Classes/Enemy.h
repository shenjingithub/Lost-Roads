#include "cocos2d.h"

#define Enemy_Stone "gameplay.stone1.png"
#define Enemy_1 "gameplay.enemy-1.png"
#define Enemy_2 "gamepaly.enemy-2.png"
#define Enemy_plane "gamepaly.enemy.plane.png"

typedef enum
{
	EnemyTypeStone=0,
	EnemyTypeEnemy1,
	EnemyTypeEnemy2,
	EnemyTypePlanet
}EnemyTypes;

class Enemy : public cocos2d::Sprite
{
	CC_SYNTHESIZE(EnemyTypes,enemyType,EnemyType);    //敌人的种类          //保护设置的变量
	CC_SYNTHESIZE(int,initialHitPoints,InitialHitPoints);          //初始的生命值
	CC_SYNTHESIZE(int,hitPoints,HitPoints);						//当前生命值
	CC_SYNTHESIZE(cocos2d::Vec2,velocity,Velocity);				//速度

public:
	Enemy(EnemyTypes enemyType): enemyType(enemyType),initialHitPoints(1),velocity(cocos2d::Vec2::ZERO){};//Enemy(EnemyTypes enemyType);

	void spawn();												//产生敌人函数
	virtual void update(float dt);								//游戏循环调用的默认函数
	static Enemy* createWithEnemyTypes(EnemyTypes enemyType);	//静态创建敌人函数

};