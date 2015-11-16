#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SystemHeader.h"

class HelloWorld : public cocos2d::Layer
{

	int m_nNumberofloaded;
private:
	std::thread* _loadingAudioThread;


public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    void delayCall(float dt);

	void loadingTextureCallBack(cocos2d::Texture2D* texture);

	void LoadingAudio();

	virtual void onExit();

    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
