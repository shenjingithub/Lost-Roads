#ifndef __GAME_PLAYER_LAYER_H__
#define __GAME_PLAYER_LAYER_H__

#define GameSceneNodeTagStatusBarFighterNode		301
#define GameSceneNodeTagStatusBarLifeNode			302
#define GameSceneNodeTagStatusBarScore				303

#define GameSceneNodeBatchTagBackground				800
#define GameSceneNodeTagFighter						900
#define GameSceneNodeTagExplosionParticleSystem		901
#define GameSceneNodeBatchTagBullet					902
#define GameSceneNodeBatchTagEnemy					903

//�����ڵ����ٶ�
#define GameSceneBulletVelocity						300

#include "cocos2d.h"
#include "SystemHeader.h"
#include "BaseLayer.h"
#include "Enemy.h"
#include "Fighter.h"
#include "Bullet.h"
#include "GameOver.h"

typedef enum{
		EnemyStone_score=5,
		Enemy1_score=15,
		Enemy2_score=10,
		EnemyPlanet_score=20
}Enemyscores;


class GamePlayerLayer : public cocos2d::Layer
{
	Fighter* fighter;
	Menu* menu;
	EventListenerTouchOneByOne*  touchFighterlistener;
	EventListenerPhysicsContact* contactListener;
	int score,scorePlaceholder;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void BGinit();
	virtual void onExit();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();

	void shootBullet(float dt);

	void handleBulletCollidingWithEnemy(Enemy* enemy);
	void handleFighterCollidingWithEnemy(Enemy* enemy);
	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuResumeCallback(cocos2d::Ref* pSender);
	void updateStatusBarFighter();
	void updateStatusBarScore();

	CREATE_FUNC(GamePlayerLayer);

};


#endif