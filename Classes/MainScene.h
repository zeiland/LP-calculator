#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"



class MainScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene);
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	void changeToAskConditionScene1(cocos2d::Ref* pSender);
};

class MainScene2 :public cocos2d::Layer                      //询问解决线性规划问题的方法
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainScene2);
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	void do_simplex_method(cocos2d::Ref* pSender);
	void do_dual_simplex_method(cocos2d::Ref* pSender);
	void do_int_programming(cocos2d::Ref* pSender);
	void begin_cal();
};
#endif // __HELLOWORLD_SCENE_H__
