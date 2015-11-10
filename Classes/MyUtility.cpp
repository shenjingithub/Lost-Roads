#include "MyUtility.h"

string MyUtility::getCurrentTime()
{
	time_t t;
	time(&t);

	char tmp[64];
	strftime(tmp,sizeof(tmp),"%Y-%m-%d %X",localtime((&t)));
	string timestr=tmp;
	return timestr;
}

string MyUtility::gbk_2_utf8(const string text)
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
	wstring tes= [=](){                         //隐式捕获：=自动值捕获、&自动引用捕获
		setlocale(LC_ALL,"chs");
		const char* _source=text.c_str();
		size_t _Dsize=text.size()+1; //宽字符，最后\n是两字节
		wchar_t *_Dest= new wchar_t[_Dsize];
		wmemset(_Dest,0,_Dsize);
		mbstowcs(_Dest,_source,_Dsize);
		wstring result=_Dest;
		delete []_Dest;
		setlocale(LC_ALL,"C");
		return result;
	}();

	int ascisize=WideCharToMultiByte(CP_UTF8,0,tes.c_str(),tes.size(),NULL,0,NULL,NULL);
	if(ascisize==ERROR_NO_UNICODE_TRANSLATION||ascisize==0)
	{
		return string();
	}
	char *resultstring=new char[ascisize];
	int conveResult=WideCharToMultiByte(CP_UTF8,0,tes.c_str(),tes.size(),resultstring,ascisize,NULL,NULL);
	if(conveResult != ascisize)
	{
		return string();	
	}

	string buffer="";
	buffer.append(resultstring,ascisize);
	delete[] resultstring;
	return buffer;

#else

	return text;

#endif

}

string MyUtility::getUTF8Char(const string key)
{
	auto sharedFileutils=cocos2d::FileUtils::sharedFileUtils();
	std::string fullPathForFilename=sharedFileutils->fullPathForFilename("utf8_char.plist");
	bool isExist=false;
	isExist=sharedFileutils->isFileExist(fullPathForFilename);
	if(!isExist)
	{
		log("utf8_char.plist doesn't exist.");
		return "";
	}

	ValueMap map=sharedFileutils->getValueMapFromFile(fullPathForFilename);
	Value value=map[key];

	if(value.isNull()){
		log("%s doesn't exist."key.c_str());
		return "";
	}
	return value.asString();
}