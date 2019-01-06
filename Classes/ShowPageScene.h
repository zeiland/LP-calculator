#pragma once

#include "cocos2d.h"

class ShowPageScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ShowPageScene);
	void menuCloseCallback(cocos2d::Ref* pSender);

	static bool tag;
	static bool wrong_tag;
private:
	void add_var(cocos2d::Ref* pSender);
	void add_condition(cocos2d::Ref* pSender);
	void sen_analysis(cocos2d::Ref* pSender);
	void restart(cocos2d::Ref* pSender);
};