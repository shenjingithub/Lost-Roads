#ifndef __MY_UTILITY_H__
#define __MY_UTILITY_H__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class MyUtility
{
public:
	static string getCurrentTime();
	static string gbk_2_utf8(const string text);
	static string getUTF8Char(const string key);
};


#endif