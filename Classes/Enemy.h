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
	CC_SYNTHESIZE(EnemyTypes,enemyType,EnemyType);    //���˵�����          //�������õı���
	CC_SYNTHESIZE(int,initialHitPoints,InitialHitPoints);          //��ʼ������ֵ
	CC_SYNTHESIZE(int,hitPoints,HitPoints);						//��ǰ����ֵ
	CC_SYNTHESIZE(cocos2d::Vec2,velocity,Velocity);				//�ٶ�

public:
	Enemy(EnemyTypes enemyType): enemyType(enemyType),initialHitPoints(1),velocity(cocos2d::Vec2::ZERO){};//Enemy(EnemyTypes enemyType);

	void spawn();												//�������˺���
	virtual void update(float dt);								//��Ϸѭ�����õ�Ĭ�Ϻ���
	static Enemy* createWithEnemyTypes(EnemyTypes enemyType);	//��̬�������˺���

};