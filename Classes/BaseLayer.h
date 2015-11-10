#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include "SystemHeader.h"
#include "cocos2d.h"
USING_NS_CC;
class BaseLayer : public cocos2d::Layer
{
public:
	
	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	void menuBackCallback(cocos2d::Ref *pSender);

	CREATE_FUNC(BaseLayer);


};


#endif