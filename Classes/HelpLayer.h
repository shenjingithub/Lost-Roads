#ifndef __HELP_LAYER_H__
#define __HELP_LAYER_H__
#include "cocos2d.h"
#include "SystemHeader.h"
#include "BaseLayer.h"
#include "MyUtility.h"

class HelpLayer : public BaseLayer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();




	CREATE_FUNC(HelpLayer);

};

#endif